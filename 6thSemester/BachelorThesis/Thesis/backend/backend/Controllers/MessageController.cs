using System.Diagnostics;
using System.Text;
using System.Text.Json;
using System.Xml.Serialization;
using backend.Model;
using backend.Model.DTO;
using backend.Repository;
using EdiFabric.Framework.Readers;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Exception = System.Exception;

namespace backend.Controllers;

[ApiController]
[Route("api/[controller]")]
public class MessageController : ControllerBase
{
    private readonly DatabaseContext context;

    public MessageController(DatabaseContext context)
    {
        this.context = context;
    }
    
    private async Task AddStepToMessage(List<WorkflowStep> steps, IFormFile file, Message message)
    {
        var now = DateTime.UtcNow;
        var archiveRoot = Path.Combine(Directory.GetCurrentDirectory(), "archive");
        var tempFolder = Path.Combine(archiveRoot, "temp");

        var ext = Path.GetExtension(file.FileName).TrimStart('.').ToLower();

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
                StepName = steps[i].Name,
                StartedTime = DateTime.UtcNow,
                EndedTime = DateTime.UtcNow,
                Result = "READY",
                Message = message,
                FilePath = i == 0 ? relativeFilePath : string.Empty
            };

            await this.context.MessageSteps.AddAsync(step);
            await this.context.SaveChangesAsync();
        }

        Ok("Steps added and file saved");
    }
    
    private static string CopyFile(string filePath, string fileName)
    {
        var now = DateTime.UtcNow;
        var archiveRoot = Path.Combine(Directory.GetCurrentDirectory(), "archive");

        var allFiles = Directory.GetFiles(archiveRoot, "*", SearchOption.AllDirectories);
        var normalizedPath = filePath.TrimStart(Path.DirectorySeparatorChar).Replace('\\', '/');

        var sourceFilePath = allFiles
            .FirstOrDefault(f => f.Replace('\\', '/').EndsWith(normalizedPath, StringComparison.OrdinalIgnoreCase));

        if (sourceFilePath == null || !System.IO.File.Exists(sourceFilePath))
        {
            throw new Exception("Source file not found under archive directory.");
        }

        var ext = Path.GetExtension(fileName).TrimStart('.').ToLower();

        string targetFolder;
        if (ext.Length >= 2 && ext.StartsWith("20"))
        {
            var yearFolder = now.Year.ToString();
            var monthFolder = now.Month.ToString("D2");
            targetFolder = Path.Combine(archiveRoot, yearFolder, monthFolder);
        }
        else
        {
            targetFolder = Path.Combine(archiveRoot, "temp");
        }

        if (!Directory.Exists(targetFolder))
        {
            Directory.CreateDirectory(targetFolder);
        }
        

        var finalFilePath = Path.Combine(targetFolder, fileName);
        Console.WriteLine(finalFilePath);

        using (var sourceStream = new FileStream(sourceFilePath, FileMode.Open, FileAccess.Read, FileShare.ReadWrite))
        using (var destinationStream = new FileStream(finalFilePath, FileMode.Create, FileAccess.Write, FileShare.ReadWrite))
        {
            sourceStream.CopyTo(destinationStream);
            destinationStream.Flush();
        }
        
        var relativeFilePath = Path.Combine(
            "archive",
            targetFolder[archiveRoot.Length..].TrimStart(Path.DirectorySeparatorChar),
            fileName);

        return relativeFilePath;
    }
    
    private static void AddFileToArchiveIn(string filePath, string fileName)
    {
        Console.WriteLine(fileName);
        var archiveRoot = Path.Combine(Directory.GetCurrentDirectory(), "archive");
        
        Console.WriteLine(archiveRoot);
        var targetFolder = Path.Combine(archiveRoot, "in");

        if (!Directory.Exists(targetFolder))
        {
            Directory.CreateDirectory(targetFolder);
        }

        var sourceFilePath = Path.GetFullPath(filePath);
        if (!System.IO.File.Exists(sourceFilePath))
        {
            throw new Exception("Source file does not exist.");
        }

        var finalFilePath = Path.Combine(targetFolder, fileName);
        System.IO.File.Copy(sourceFilePath, finalFilePath, overwrite: true);
    }

    private async Task PrepareNextStep(MessageStep currentStep, string filePath)
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
            step.StartedTime = DateTime.UtcNow.AddMilliseconds(100);
        }
        
        await this.context.SaveChangesAsync();

        Ok("Prepared next step");
    }
    
    private async Task RunShellScriptAsync(string filePath, string fileName)
    {
        var scriptPath = Path.Combine(Directory.GetCurrentDirectory(), "archive", "scripts", "shell", fileName);

        if (!System.IO.File.Exists(scriptPath))
            throw new Exception($"Shell script not found {scriptPath}.");
        
        
        Console.WriteLine($"{scriptPath} --- {filePath}");
        
        var psi = new ProcessStartInfo
        {
            FileName = "powershell.exe",
            Arguments = $"-ExecutionPolicy Bypass -File \"{scriptPath}\" -FilePath \"{filePath}\"",
            RedirectStandardOutput = true,
            RedirectStandardError = true,
            UseShellExecute = false,
            CreateNoWindow = true
        };
        
        Console.WriteLine("Script started");

        using var process = new Process { StartInfo = psi, EnableRaisingEvents = true };
        
        Console.WriteLine("Script is ongoing");

        var outputBuilder = new StringBuilder();
        var errorBuilder = new StringBuilder();

        var timeout = TimeSpan.FromSeconds(30);
        using var cts = new CancellationTokenSource(timeout);

        process.OutputDataReceived += (_, e) =>
        {
            if (string.IsNullOrEmpty(e.Data)) return;
            Console.WriteLine($"OUTPUT: {e.Data}");
            outputBuilder.AppendLine(e.Data);
        };

        process.ErrorDataReceived += (_, e) =>
        {
            if (string.IsNullOrEmpty(e.Data)) return;
            Console.WriteLine($"ERROR: {e.Data}");
            errorBuilder.AppendLine(e.Data);
        };

        process.Start();

        process.BeginOutputReadLine();
        process.BeginErrorReadLine();

        await process.WaitForExitAsync(cts.Token); 
        
        if (process.ExitCode != 0)
            throw new Exception($"Script execution failed: {errorBuilder}");
    }
    
    /*
     * ENDPOINTS
     */
    
    [HttpGet("messages/{pattern}")]
    [Authorize]
    public async Task<ActionResult<List<Message>>> GetMessages(string pattern)
    {
        var likePattern = pattern.Replace('*', '%');
        var messages = await this.context.Messages
            .Include(m => m.User)
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

    [HttpPost("message/step/file")]
    [Authorize]
    public async Task<ActionResult> GetFileContent([FromBody] FilePathDTO file)
    {
        var path = Path.Combine(Directory.GetCurrentDirectory(), file.FilePath);
        
        if (string.IsNullOrWhiteSpace(path))
            throw new Exception("File path doesn't exist");
        
        if (!System.IO.File.Exists(path))
            throw new Exception("File not found.");
        
        var content = await System.IO.File.ReadAllTextAsync(path);

        if (content == null)
        {
            throw new Exception($"Error reading file");
        }
        
        return Ok(content);
    }
    
    [HttpPut("message/user/assign/{id}")]
    [Authorize]
    public async Task<ActionResult<Message>> AssignMessageToUser(string id, [FromBody] AssignMessageRequestDTO  messageAssign)
    {
        var message = await this.context.Messages.FirstOrDefaultAsync(m => m.Id.ToString() == messageAssign.MessageId);

        if (message == null)
        {
            throw new Exception("Message doesn't exist");
        }

        var user = await this.context.Users.FirstOrDefaultAsync(u => u.Id.ToString() == id);

        if (user == null)
        {
            throw new Exception("User doesn't exist");
        }

        message.User = user;
        message.UserId = user.Id;
        
        await this.context.SaveChangesAsync();

        return Ok(message);
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
        
        return files.Length > 0 ? Ok(new { message = "Files found", count = files.Length }) : Ok(new { message = "No files found" });
    }
    
    [HttpGet("messages/in/check")]
    public IActionResult CheckForInFiles()
    {
        var path = Path.Combine(Directory.GetCurrentDirectory(), "archive", "in");

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

        var workflow = await this.context.Workflows
            .Include(workflow => workflow.WorkflowSteps)
            .FirstOrDefaultAsync(w => w.Id == rule.WorkflowId);

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

        
        await this.AddStepToMessage(workflow.WorkflowSteps.ToList(), file, addMessage);
        

        return Ok(addMessage);
    }
    
    [HttpPost("message/restart")]
    [Authorize]
    public async Task<ActionResult<string>> RestartMessage([FromForm] RestartMessageDTO restartMessage)
    {
        var rule = await this.context.Rules.FirstOrDefaultAsync(r => r.Id.ToString() == restartMessage.RuleId);

        if (rule == null)
        {
            throw new Exception("Rule doesn't exist");
        }

        var workflow = await this.context.Workflows
            .Include(workflow => workflow.WorkflowSteps)
            .FirstOrDefaultAsync(w => w.Id == rule.WorkflowId);

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

        await using var stream = new FileStream(restartMessage.FilePath, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
        var file = new FormFile(stream, 0, stream.Length, "file", Path.GetFileName(restartMessage.FilePath));

        await this.AddStepToMessage(workflow.WorkflowSteps.ToList(), file, addMessage);
        
        return Ok(addMessage);
    }

    [HttpPut("message/process/step/{id}")]
    [Authorize]
    public async Task<ActionResult<MessageStep>> ProcessStep([FromForm] string filePath, [FromForm] string fileName, string id, [FromForm] string step)
    {
        var messageStep = await this.context.MessageSteps.Include(messageStep => messageStep.Message)
            .ThenInclude(message => message.Rule).ThenInclude(rule => rule.CommunicationChannel)
            .ThenInclude(communicationChannel => communicationChannel.Partner)
            .Include(messageStep => messageStep.Message).ThenInclude(message => message.Rule)
            .ThenInclude(rule => rule.Workflow).ThenInclude(workflow => workflow.WorkflowSteps).FirstOrDefaultAsync(ms => ms.Id.ToString() == id);

        if (messageStep == null)
        {
            throw new Exception("Message step doesn't exist");
        }
        
        messageStep.Result = "ACTIVE";

        switch (step)
        {
            case "COPY":
            {
                try
                {
                    var relativeFilePath = CopyFile(filePath, fileName);

                    messageStep.Result = "OK";
                    messageStep.EndedTime = DateTime.UtcNow;
                    messageStep.FilePath = relativeFilePath;
                    await this.context.SaveChangesAsync();

                    await this.PrepareNextStep(messageStep, relativeFilePath);
                    await this.context.SaveChangesAsync();
                }
                catch (Exception ex)
                {
                    messageStep.Result = $"ERROR {ex.Message}";
                    messageStep.EndedTime = DateTime.UtcNow;
                    await this.context.SaveChangesAsync(); 
                }
                
                break;
            }
            case "REMOVE":
            {
                try
                {
                    await this.DeleteMessage(messageStep.MessageId.ToString());
                }
                catch (Exception ex)
                {
                    messageStep.Result = $"ERROR {ex.Message}";
                    messageStep.EndedTime = DateTime.UtcNow;
                    await this.context.SaveChangesAsync(); 
                }
                
                break;
            }
            case "CONVERT":
            {
                try
                {
                    var relativeFilePath = CopyFile(filePath, fileName);
                    
                    var partnerCertificate = messageStep.Message.Rule.CommunicationChannel.Partner.Certificate;
                    var partnerCertificateFilePath = Path.Combine("archive", "certificates", partnerCertificate);
                    var jsonString = await System.IO.File.ReadAllTextAsync(partnerCertificateFilePath);
                    var certInfo = JsonSerializer.Deserialize<CertificateDTO>(jsonString);

                    if (certInfo == null)
                    {
                        throw new Exception("Standard not available at the moment");
                    }
                    
                    await using var ediStream = System.IO.File.OpenRead(relativeFilePath);
                    using var ediReader = new X12Reader(ediStream, "EdiFabric.Templates.X12");
                    var ediTransaction = new Object();
                    
                    while (await ediReader.ReadAsync())
                    {
                        ediTransaction = ediReader.Item;
                        break;
                    }
                    
                    if (ediTransaction == null)
                        throw new Exception("No transaction set found in the EDI file.");
                    
                    var serializer = new XmlSerializer(ediTransaction.GetType());
                    await using var stringWriter = new StringWriter();
                    serializer.Serialize(stringWriter, ediTransaction);
                }
                catch (Exception ex)
                {
                    messageStep.Result = $"ERROR {ex.Message}";
                    messageStep.EndedTime = DateTime.UtcNow;
                    await this.context.SaveChangesAsync();
                }
                break;
            }
            case "SHELL":
            {
                try
                {
                    var relativeFilePath = CopyFile(filePath, fileName);
                    var scriptFile =
                        messageStep.Message.Rule.Workflow.WorkflowSteps.FirstOrDefault(ws => ws.Name == "SHELL")!
                            .FilePath;
                    await this.context.SaveChangesAsync();
                    await this.RunShellScriptAsync(relativeFilePath, scriptFile);

                    messageStep.Result = "OK";
                    messageStep.EndedTime = DateTime.UtcNow;
                    await this.context.SaveChangesAsync();

                    await this.PrepareNextStep(messageStep, relativeFilePath);
                }
                catch (Exception ex)
                {
                    messageStep.Result = $"ERROR {ex.Message}";
                    messageStep.EndedTime = DateTime.UtcNow;
                    await this.context.SaveChangesAsync();
                }
                
                break;
            }
            case "SEND":
            {
                try
                {
                    var relativeFilePath = CopyFile(filePath, fileName);
                    var sender = messageStep.Message.Rule.Sender;
                    var receiver = messageStep.Message.Rule.Receiver;
                    var certificate = await this.context.Certificates
                        .FirstOrDefaultAsync(c => 
                            c.Sender == sender &&
                            c.Receiver == receiver);

                    if (certificate == null)
                    {
                        messageStep.Result = "ERROR";
                        messageStep.EndedTime = DateTime.UtcNow;
                        await this.context.SaveChangesAsync();
                        throw new Exception($"Certificate for this partner combination {sender} -> {receiver} doesn't exist");
                    }
                    
                    messageStep.Result = "OK";
                    messageStep.EndedTime = DateTime.UtcNow;
                    AddFileToArchiveIn(relativeFilePath, fileName);
                    await this.context.SaveChangesAsync();
                    await this.PrepareNextStep(messageStep, relativeFilePath);
                }
                catch (Exception ex)
                {
                    messageStep.Result = "ERROR";
                    messageStep.EndedTime = DateTime.UtcNow;
                    await this.context.SaveChangesAsync();
                    throw new Exception($"ERROR: {ex.Message}");
                }
                
                break;
            }
        }

        if (messageStep.Message.Rule.TimeStamp != "PRE-DEFAULT") 
            return Ok(messageStep);
        
        var rule = await this.context.Rules.Where(r => r.TimeStamp == "PRE-DEFAULT")
            .FirstOrDefaultAsync(r => r.Id == messageStep.Message.RuleId);
        if (rule != null) rule.TimeStamp = "DEFAULTS";
        await this.context.SaveChangesAsync();

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