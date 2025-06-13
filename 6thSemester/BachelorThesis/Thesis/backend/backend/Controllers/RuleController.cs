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

    public RuleController(DatabaseContext context)
    {
        this.context = context;
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
                    EF.Functions.Like(r.TimeStamp, timestampPattern) &&
                    r.Id.ToString() != "61351627-73e5-420b-a829-2f83740f6ee6")
            .Include(r => r.Workflow)
            .ToListAsync();

        if (rules == null)
        {
            throw new Exception("There are no rules");
        }

        return Ok(rules);
    }
    
    [HttpGet("rule/{id}")]
    [Authorize]
    public async Task<ActionResult<Rule>> GetRule(string id)
    {
        var rule = await this.context.Rules
            .Include(r => r.Workflow)
            .FirstOrDefaultAsync(r => r.Id.ToString() == id);

        if (rule == null)
        {
            throw new Exception("There is no rule");
        }

        return Ok(rule);
    }
    
    [HttpPost("rule/add")]
    [Authorize]
    public async Task<ActionResult<Rule>> AddRule([FromBody] RuleDTO rule)
    {
        var actualRule = await this.context.Rules.FirstOrDefaultAsync(r => 
            r.Sender == rule.Sender && 
            r.ObjectType == rule.ObjectType &&
            r.Receiver == rule.Receiver);

        if (actualRule != null)
        {
            throw new Exception("There already exists a rule with these configurations");
        }

        var workflow = await this.context.Workflows.FirstOrDefaultAsync(w => w.Id == rule.WorkflowId);

        if (workflow == null)
        {
            throw new Exception("This workflow doesn't exist");
        }
        
        var partner = await this.context.Partners
            .Include(p => p.CommunicationChannel)
            .FirstOrDefaultAsync(p => p.Name == rule.Sender);
        
        if (partner == null)
        {
            throw new Exception("This partner is not assigned to any communication channel or it doesn't exist");
        }
        
        var addRule = new Rule
        {
            Id = new Guid(),
            Sender = rule.Sender,
            ObjectType = rule.ObjectType,
            Receiver = rule.Receiver,
            TimeStamp = rule.TimeStamp,
            WorkflowId = workflow.Id,
            Workflow = workflow,
            CommunicationChannelId = partner.CommunicationChannelId,
            CommunicationChannel = partner.CommunicationChannel
        };

        await this.context.Rules.AddAsync(addRule);
        await this.context.SaveChangesAsync();

        return Ok(addRule);
    }
    
    [HttpPut("rule/update/{id}")]
    [Authorize]
    public async Task<ActionResult<Rule>> UpdateRule([FromBody] RuleUpdateDTO rule, string id)
    {
        var actualRule = await this.context.Rules.FirstOrDefaultAsync(r => r.Id.ToString() == id);

        if (actualRule == null)
        {
            throw new Exception("There doesn't exist a rule with these configurations");
        }

        var workflow = await this.context.Workflows.FirstOrDefaultAsync(w => w.Id == rule.WorkflowId);
        
        if (workflow == null)
        {
            throw new Exception("Workflow doesn't exist");
        }

        actualRule.WorkflowId = rule.WorkflowId;
        actualRule.Workflow = workflow;
        actualRule.TimeStamp = rule.TimeStamp;
        
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
        
        var warningRule = await this.context.Rules.FirstOrDefaultAsync(r => r.Id.ToString() == "61351627-73e5-420b-a829-2f83740f6ee6");

        if (warningRule == null)
        {
            throw new Exception("This rule cannot be deleted");
        }

        var message = await this.context.Messages.FirstOrDefaultAsync(m => m.RuleId.ToString() == id);
        
        if (message != null)
        {
            throw new Exception("Cannot delete rule because there are messages still being processed by it");
        }

        this.context.Rules.Remove(actualRule);
        await this.context.SaveChangesAsync();

        return Ok(actualRule);
    }
}