using System.Xml.Linq;
using backend.Model;
using backend.Model.DTO;
using backend.Repository;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace backend.Controllers;

[ApiController]
[Route("api/[controller]")]
public class MessageController : ControllerBase
{
    private readonly DatabaseContext context;
    private readonly IConfiguration configuration;

    public MessageController(DatabaseContext context, IConfiguration configuration)
    {
        this.context = context;
        this.configuration = configuration;
    }
    
    [HttpGet("messages/{pattern}")]
    [Authorize]
    public async Task<ActionResult<List<Message>>> GetMessages(string pattern)
    {
        var likePattern = pattern.Replace('*', '%');
        var messages = await this.context.Messages
            .Include(m => m.Rule)
            .Include(m => m.MessageSteps)
            .ToListAsync();

        return Ok(messages);
    }
    
    [HttpGet("message/{id}")]
    [Authorize]
    public async Task<ActionResult<Message>> GetMessageById(string id)
    {
        var message = await this.context.Messages
            .Include(m => m.Rule)
            .Include(m => m.MessageSteps)
            .FirstOrDefaultAsync(m => m.Id.ToString() == id);

        if (message == null)
        {
            throw new Exception("Message doesn't exist");
        }
        
        return Ok(message);
    }

    private async Task<ActionResult<string>> AddStepToMessage(List<string> steps, IFormFile file, Message message)
    {
        var now = DateTime.UtcNow;
        var archiveRoot = Path.Combine(Directory.GetCurrentDirectory(), "archive");
        var tempFolder = Path.Combine(archiveRoot, "temp");

        var ext = Path.GetExtension(file.FileName)?.TrimStart('.').ToLower() ?? "";

        string targetFolder;

        if (ext.Length >= 2 && ext.StartsWith("20"))
        {
            var yearFolder = now.Year.ToString();
            var monthFolder = now.Month.ToString("D2");
            targetFolder = Path.Combine(archiveRoot, yearFolder, monthFolder);
        }
        else
        {
            targetFolder = tempFolder;
        }
        
        if (!Directory.Exists(targetFolder))
        {
            Directory.CreateDirectory(targetFolder);
        }

        var fileName = Path.GetFileName(file.FileName);
        var filePath = Path.Combine(targetFolder, fileName);

        await using (var stream = new FileStream(filePath, FileMode.Create))
        {
            await file.CopyToAsync(stream);
        }

        var relativeFilePath = Path.Combine("archive",
            targetFolder[archiveRoot.Length..].TrimStart(Path.DirectorySeparatorChar),
            fileName);
        
        for (var i = 0; i < steps.Count; i++)
        {
            var step = new MessageStep
            {
                Id = Guid.NewGuid(),
                StepName = steps[i],
                StartedTime = DateTime.UtcNow,
                EndedTime = DateTime.UtcNow,
                Result = "READY",
                Message = message,
                FilePath = i == 0 ? relativeFilePath : string.Empty
            };

            await this.context.MessageSteps.AddAsync(step);
            await this.context.SaveChangesAsync();
        }

        return Ok("Steps added and file saved");
    }
    
    [HttpGet("messages/out/check")]
    public IActionResult CheckForOutFiles()
    {
        var path = Path.Combine(Directory.GetCurrentDirectory(), "archive", "out");

        if (!Directory.Exists(path))
        {
            return NotFound("Directory does not exist.");
        }

        var files = Directory.GetFiles(path);
        
        if (files.Length > 0)
        {
            // Process files
            return Ok(new { message = "Files found", count = files.Length });
        }

        return Ok(new { message = "No files found" });
    }
    
    [HttpPost("message/store")]
    [Authorize]
    public async Task<ActionResult<string>> AddMessage([FromForm] IFormFile file, [FromForm] string ruleId)
    {
        var rule = await this.context.Rules.FirstOrDefaultAsync(r => r.Id.ToString() == ruleId);

        if (rule == null)
        {
            throw new Exception("Rule doesn't exist");
        }

        var workflow = await this.context.Workflows.FirstOrDefaultAsync(w => w.Id == rule.WorkflowId);

        if (workflow == null)
        {
            throw new Exception("Workflow doesn't exist");
        }

        var id = new Guid();

        var addMessage = new Message
        {
            Id = id,
            RuleId = rule.Id,
            Rule = rule
        };
        
        await this.context.Messages.AddAsync(addMessage);
        await this.context.SaveChangesAsync();

        
        await this.AddStepToMessage(workflow.Steps.ToList(), file, addMessage);
        

        return Ok(addMessage);
    }
    
    private static string CopyFile(string filePath, string fileName)
    {
        var now = DateTime.UtcNow;
        var archiveRoot = Path.Combine(Directory.GetCurrentDirectory(), "archive");

        // Recursively find the source file anywhere inside "archive"
        var allFiles = Directory.GetFiles(archiveRoot, "*", SearchOption.AllDirectories);
        var normalizedPath = filePath.TrimStart(Path.DirectorySeparatorChar).Replace('\\', '/');

        var sourceFilePath = allFiles
            .FirstOrDefault(f => f.Replace('\\', '/').EndsWith(normalizedPath, StringComparison.OrdinalIgnoreCase));

        if (sourceFilePath == null || !System.IO.File.Exists(sourceFilePath))
        {
            throw new Exception("Source file not found under archive directory.");
        }

        var ext = Path.GetExtension(fileName)?.TrimStart('.').ToLower() ?? "";

        string targetFolder;
        if (ext.Length >= 2 && ext.StartsWith("20"))
        {
            var yearFolder = now.Year.ToString();
            var monthFolder = now.Month.ToString("D2");
            targetFolder = Path.Combine(archiveRoot, yearFolder, monthFolder);
        }
        else
        {
            targetFolder = Path.Combine(archiveRoot, "temp");;
        }

        if (!Directory.Exists(targetFolder))
        {
            Directory.CreateDirectory(targetFolder);
        }

        var finalFilePath = Path.Combine(targetFolder, fileName);
        System.IO.File.Copy(sourceFilePath, finalFilePath, overwrite: true);

        var relativeFilePath = Path.Combine(
            "archive",
            targetFolder[archiveRoot.Length..].TrimStart(Path.DirectorySeparatorChar),
            fileName);

        return relativeFilePath;
    }

    private async Task<ActionResult<string>> PrepareNextStep(MessageStep currentStep, string filePath)
    {
        var messageSteps = await this.context.MessageSteps
            .Where(ms => ms.MessageId == currentStep.MessageId)
            .ToListAsync();
        
        var messageStepNext = messageSteps
            .Where(ms => ms.StartedTime > currentStep.StartedTime && ms.Id != currentStep.Id)
            .MinBy(ms => ms.StartedTime);

        if (messageStepNext != null && messageStepNext.StepName != "REMOVE")
        {
            messageStepNext.FilePath = filePath;
            await this.context.SaveChangesAsync();
        }
        
        messageStepNext!.StartedTime = DateTime.UtcNow;
        await this.context.SaveChangesAsync();
        
        var messageStepsAfter = messageSteps
            .Where(ms => ms.StartedTime > currentStep.StartedTime && ms.Id != currentStep.Id && ms.Id != messageStepNext.Id)
            .OrderBy(ms => ms.StartedTime)
            .ToList();

        foreach (var step in messageStepsAfter)
        {
            step.StartedTime = DateTime.UtcNow;
        }
        
        await this.context.SaveChangesAsync();
        
        return Ok("Prepared next step");

    }

    [HttpPut("message/process/step/{id}")]
    [Authorize]
    public async Task<ActionResult<MessageStep>> ProcessStep([FromForm] string filePath, [FromForm] string fileName, string id, [FromForm] string step)
    {
        var messageStep = await this.context.MessageSteps.FirstOrDefaultAsync(ms => ms.Id.ToString() == id);

        if (messageStep == null)
        {
            throw new Exception("Message step doesn't exist");
        }

        switch (step)
        {
            case "COPY":
            {
                var relativeFilePath = CopyFile(filePath, fileName);

                messageStep.Result = "OK";
                messageStep.EndedTime = DateTime.UtcNow;
                messageStep.FilePath = relativeFilePath;
                await this.context.SaveChangesAsync();

                await this.PrepareNextStep(messageStep, relativeFilePath);
                await this.context.SaveChangesAsync();
                break;
            }
            case "REMOVE":
            {
                await this.DeleteMessage(messageStep.MessageId.ToString());
                break;
            }
            case "CONVERT":
            {
                var convertFilePath = messageStep.FilePath;
                var partnerCertificate = messageStep.Message.Rule.CommunicationChannel.Partner.Certificate;
                Console.WriteLine(partnerCertificate);
                break;
            }
            case "SHELL":
            {
                break;
            }
        }

        return Ok(messageStep);
    }
    
    [HttpDelete("message/delete/{id}")]
    [Authorize]
    public async Task<ActionResult<Message>> DeleteMessage(string id)
    {
        var actualMessage = await this.context.Messages.FirstOrDefaultAsync(m => m.Id.ToString() == id);

        if (actualMessage == null)
        {
            throw new Exception("Message doesn't exist");
        }

        this.context.Messages.Remove(actualMessage);
        await this.context.SaveChangesAsync();

        return Ok(actualMessage);
    }
}