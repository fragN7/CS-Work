using backend.Model;
using backend.Model.DTO;
using backend.Repository;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace backend.Controllers;

[ApiController]
[Route("api/[controller]")]
public class RuleController : ControllerBase
{
    private readonly DatabaseContext context;
    private readonly IConfiguration configuration;

    public RuleController(DatabaseContext context, IConfiguration configuration)
    {
        this.context = context;
        this.configuration = configuration;
    }
    
    
    [HttpGet("rules/{sender}/{objectType}/{receiver}/{workflow}/{timestamp}")]
    [Authorize]
    public async Task<ActionResult<List<Rule>>> GetRules(string sender, string objectType, string receiver, string workflow, string timestamp)
    {
        var senderPattern = sender.Replace('*', '%');
        var objectTypePattern = objectType.Replace('*', '%');
        var receiverPattern = receiver.Replace('*', '%');
        var workflowPattern = workflow.Replace('*', '%');
        var timestampPattern = timestamp.Replace('*', '%');

        var rules = await this.context.Rules.Where
            (r => EF.Functions.Like(r.Sender, senderPattern) && 
                    EF.Functions.Like(r.ObjectType, objectTypePattern) && 
                    EF.Functions.Like(r.Receiver, receiverPattern) && 
                    EF.Functions.Like(r.Workflow.Name, workflowPattern) && 
                    EF.Functions.Like(r.Timestamp, timestampPattern)).ToListAsync();

        if (rules == null)
        {
            throw new Exception("There are no rules");
        }

        return Ok(rules);
    }
    
    [HttpPost("rule/add")]
    [Authorize]
    public async Task<ActionResult<Rule>> AddRule([FromBody] RuleDTO rule)
    {
        var actualRule = await this.context.Rules.FirstOrDefaultAsync(r => 
            r.Sender == rule.Sender && 
            r.ObjectType == rule.ObjectType &&
            r.Receiver == rule.Receiver &&
            r.WorkflowId == rule.WorkflowId);

        if (actualRule != null)
        {
            throw new Exception("There already exists a rule with these configurations");
        }

        var addRule = new Rule
        {
            Id = new Guid(),
            Sender = rule.Sender,
            ObjectType = rule.ObjectType,
            Receiver = rule.Receiver
        };

        await this.context.Rules.AddAsync(addRule);
        await this.context.SaveChangesAsync();

        return Ok(addRule);
    }
    
    [HttpPut("rule/update/{id}")]
    [Authorize]
    public async Task<ActionResult<Rule>> UpdateRule([FromBody] RuleDTO rule, [FromQuery] string id)
    {
        var actualRule = await this.context.Rules.FirstOrDefaultAsync(r => r.Id.ToString() == id);

        if (actualRule == null)
        {
            throw new Exception("There doesn't exist a rule with these configurations");
        }

        var workflow = await this.context.Workflows.FirstOrDefaultAsync(w => w.Id == rule.WorkflowId);
        
        if (workflow != null)
        {
            throw new Exception("Workflow doesn't exist");
        }

        actualRule.Sender = rule.Sender;
        actualRule.ObjectType = rule.ObjectType;
        actualRule.Receiver = rule.Receiver;
        actualRule.WorkflowId = rule.WorkflowId;
        actualRule.Workflow = workflow;
        
        await this.context.SaveChangesAsync();

        return Ok(actualRule);
    }
    
    [HttpDelete("rule/delete/{id}")]
    [Authorize]
    public async Task<ActionResult<Rule>> DeleteRule(string id)
    {
        var actualRule = await this.context.Rules.FirstOrDefaultAsync(r => r.Id.ToString() == id);

        if (actualRule == null)
        {
            throw new Exception("There doesn't exist a rule with these configurations");
        }

        this.context.Rules.Remove(actualRule);
        await this.context.SaveChangesAsync();

        return Ok(actualRule);
    }
}