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
    private readonly IConfiguration configuration;

    public WorkflowController(DatabaseContext context, IConfiguration configuration)
    {
        this.context = context;
        this.configuration = configuration;
    }
    
    [HttpGet("workflows/{pattern}")]
    [Authorize]
    public async Task<ActionResult<List<Workflow>>> GetWorkflows(string pattern)
    {
        var likePattern = pattern.Replace('*', '%');
        var workflows = await this.context.Workflows.Where(w => EF.Functions.Like(w.Name, likePattern)).ToListAsync();

        if (workflows == null)
        {
            throw new Exception("There are no workflows");
        }

        return Ok(workflows);
    }
    
    [HttpPost("workflow/add")]
    [Authorize]
    public async Task<ActionResult<Workflow>> AddWorkflow([FromBody] WorkflowDTO workflow)
    {
        var actualWorkflow = await this.context.Workflows.FirstOrDefaultAsync(w => w.Name == workflow.Name);

        if (actualWorkflow != null)
        {
            throw new Exception("There already exists a workflow with this name");
        }

        var addWorkflow = new Workflow
        {
            Id = new Guid(),
            Name = workflow.Name,
            Steps = workflow.Steps
        };

        await this.context.Workflows.AddAsync(addWorkflow);
        await this.context.SaveChangesAsync();

        return Ok(addWorkflow);
    }
    
    [HttpPut("workflow/update/{id}")]
    [Authorize]
    public async Task<ActionResult<Workflow>> UpdateWorkflow([FromBody] WorkflowDTO workflow, [FromQuery] string id)
    {
        var actualWorkflow= await this.context.Workflows.FirstOrDefaultAsync(w => w.Id.ToString() == id);

        if (actualWorkflow == null)
        {
            throw new Exception("Workflow doesn't exist");
        }

        actualWorkflow.Name = workflow.Name;
        actualWorkflow.Steps = workflow.Steps;

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

        this.context.Workflows.Remove(actualWorkflow);
        await this.context.SaveChangesAsync();

        return Ok(actualWorkflow);
    }
}