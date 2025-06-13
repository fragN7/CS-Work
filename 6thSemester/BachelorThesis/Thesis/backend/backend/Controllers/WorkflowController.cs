using backend.Model;
using backend.Model.DTO;
using backend.Repository;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace backend.Controllers;

[ApiController]
[Route("api/[controller]")]
public class WorkflowController : ControllerBase
{
    private readonly DatabaseContext context;

    public WorkflowController(DatabaseContext context)
    {
        this.context = context;
    }
    
    [HttpGet("workflows/{pattern}")]
    [Authorize]
    public async Task<ActionResult<List<Workflow>>> GetWorkflows(string pattern)
    {
        var likePattern = pattern.Replace('*', '%');
        var workflows = await this.context.Workflows
            .Where(w => EF.Functions.Like(w.Name, likePattern) &&
                        w.Id.ToString() != "d6ef4e0b-e070-48a4-a466-a45426eeb135").ToListAsync();

        if (workflows == null)
        {
            throw new Exception("There are no workflows");
        }

        return Ok(workflows);
    }
    
    [HttpGet("workflow/{id}")]
    [Authorize]
    public async Task<ActionResult<Workflow>> GetWorkflowById(string id)
    {
        var workflow = await this.context.Workflows
            .Include(w => w.WorkflowSteps)
            .FirstOrDefaultAsync(w => w.Id.ToString() == id);

        if (workflow == null)
        {
            throw new Exception("There is no workflow");
        }

        return Ok(workflow);
    }
    
    [HttpPost("workflow/add")]
    [Authorize]
    public async Task<ActionResult<Workflow>> AddWorkflow([FromForm] WorkflowDTO workflow)
    {
        var actualWorkflow = await this.context.Workflows.FirstOrDefaultAsync(w => w.Name == workflow.Name);

        if (actualWorkflow != null)
        {
            throw new Exception("There already exists a workflow with this name");
        }
        
        var addWorkflow = new Workflow
        {
            Id = new Guid(),
            Name = workflow.Name
        };
        
        await this.context.Workflows.AddAsync(addWorkflow);
        await this.context.SaveChangesAsync();
        
        var xslFolder = Path.Combine("archive", "scripts", "xsl");
        var shellFolder = Path.Combine("archive", "scripts", "shell");
        
        Directory.CreateDirectory(xslFolder);
        Directory.CreateDirectory(shellFolder);
        
        foreach (var step in workflow.WorkflowSteps)
        {
            var addWorkflowStep = new WorkflowStep
            {
                Id = new Guid(),
                Name = step.Name,
                FilePath = step.FilePath,
                Command = step.Command,
                Workflow = addWorkflow,
                WorkflowId = addWorkflow.Id
            };

            if (step.File.Length > 0)
            {
                var ext = Path.GetExtension(step.File.FileName).ToLowerInvariant();
                var folderPath = ext switch
                {
                    ".xsl" => xslFolder,
                    ".sh" => shellFolder,
                    ".ps1" => shellFolder,
                    _ => null
                };

                if (folderPath != null)
                {
                    var uniqueFileName = $"{step.File.FileName}";
                    var fullPath = Path.Combine(folderPath, uniqueFileName);

                    await using var stream = new FileStream(fullPath, FileMode.Create);
                    await step.File.CopyToAsync(stream);
                }
            }

            await this.context.WorkflowSteps.AddAsync(addWorkflowStep);
            await this.context.SaveChangesAsync();
        }
        
        return Ok(addWorkflow);
    }
    
    [HttpPut("workflow/update/{id}")]
    [Authorize]
    public async Task<ActionResult<Workflow>> UpdateWorkflow([FromForm] WorkflowEditDTO workflow, string id)
    {
        var actualWorkflow= await this.context.Workflows.FirstOrDefaultAsync(w => w.Id.ToString() == id);

        if (actualWorkflow == null)
        {
            throw new Exception("Workflow doesn't exist");
        }

        actualWorkflow.Name = workflow.Name;

        await this.context.SaveChangesAsync();

        return Ok(actualWorkflow);
    }
    
    [HttpDelete("workflow/delete/{id}")]
    [Authorize]
    public async Task<ActionResult<Workflow>> DeleteWorkflow(string id) 
    {
        var actualWorkflow = await this.context.Workflows.FirstOrDefaultAsync(w => w.Id.ToString() == id);

        if (actualWorkflow == null)
        {
            throw new Exception("Workflow doesn't exist");
        }
        
        var warningWorkflow = await this.context.Workflows
            .FirstOrDefaultAsync(r => r.Id.ToString() == "d6ef4e0b-e070-48a4-a466-a45426eeb135");

        if (warningWorkflow == null)
        {
            throw new Exception("This workflow cannot be deleted");
        }

        var rule = await this.context.Rules.FirstOrDefaultAsync(r => r.WorkflowId.ToString() == id);

        if (rule != null)
        {
            throw new Exception("Workflow in use");
        }

        this.context.Workflows.Remove(actualWorkflow);
        await this.context.SaveChangesAsync();

        return Ok(actualWorkflow);
    }
}