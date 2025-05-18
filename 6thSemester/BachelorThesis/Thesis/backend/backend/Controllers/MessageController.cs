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
                var now = DateTime.UtcNow;
                var archiveRoot = Path.Combine(Directory.GetCurrentDirectory(), "archive");
                var tempFolder = Path.Combine(archiveRoot, "temp");

                var sourceFilePath = Path.Combine(tempFolder, filePath.TrimStart(Path.DirectorySeparatorChar));

                if (!System.IO.File.Exists(sourceFilePath))
                {
                    return NotFound("Source file not found in temp folder.");
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
                    targetFolder = tempFolder;
                }

                if (!Directory.Exists(targetFolder))
                {
                    Directory.CreateDirectory(targetFolder);
                }

                // Copy and rename the file to the new destination
                var finalFilePath = Path.Combine(targetFolder, fileName);
                System.IO.File.Copy(sourceFilePath, finalFilePath, overwrite: true);

                // Set the relative path to store in DB
                var relativeFilePath = Path.Combine(
                    "archive",
                    targetFolder[archiveRoot.Length..].TrimStart(Path.DirectorySeparatorChar),
                    fileName);

                // Update DB fields
                messageStep.Result = "OK";
                messageStep.EndedTime = DateTime.UtcNow;
                messageStep.FilePath = relativeFilePath;

                var messageSteps = await this.context.MessageSteps.Where(ms => ms.Id == messageStep.MessageId).ToListAsync();
                foreach (var stepMessage in messageSteps)
                {
                    stepMessage.FilePath = relativeFilePath;
                    await this.context.SaveChangesAsync();
                }
                
                await this.context.SaveChangesAsync();
                break;
            }
            case "REMOVE":
            {
                await this.DeleteMessage(messageStep.MessageId.ToString());
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