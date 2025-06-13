using backend.Model;
using backend.Model.DTO;
using backend.Repository;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace backend.Controllers;

[ApiController]
[Route("api/[controller]")]
public class CommunicationChannelController : ControllerBase
{
    private readonly DatabaseContext context;

    public CommunicationChannelController(DatabaseContext context)
    {
        this.context = context;
    }
    
    [HttpPost("channel/add")]
    [Authorize]
    public async Task<ActionResult<CommunicationChannel>> AddChannel([FromBody] CommunicationChannelDTO channel)
    {
        var partner = await this.context.Partners.FirstOrDefaultAsync(p => p.Id == channel.PartnerId);
        
        if (partner == null)
        {
            throw new Exception("There is no partner to be assigned with this communication channel");
        }

        var addChannel = new CommunicationChannel
        {
            Id = new Guid(),
            PartnerId = partner.Id
        };

        await this.context.CommunicationChannels.AddAsync(addChannel);
        await this.context.SaveChangesAsync();

        return Ok(addChannel);
    }
    
    [HttpPut("channel/update/{id}")]
    [Authorize]
    public async Task<ActionResult<CommunicationChannel>> UpdateChannel([FromBody] CommunicationChannelDTO channel, string id)
    {
        var actualChannel = await this.context.CommunicationChannels.FirstOrDefaultAsync(c => c.Id.ToString() == id);

        if (actualChannel == null)
        {
            throw new Exception("There doesn't exist a communication channel with this partner");
        }
        
        var partner = await this.context.Partners.FirstOrDefaultAsync(p => p.Id == channel.PartnerId);
        
        if (partner == null)
        {
            throw new Exception("There is no partner to be assigned with this communication channel");
        }

        actualChannel.PartnerId = channel.PartnerId;
        actualChannel.Partner = partner;

        await this.context.SaveChangesAsync();

        return Ok(actualChannel);
    }
    
    [HttpDelete("channel/delete/{id}")]
    [Authorize]
    public async Task<ActionResult<CommunicationChannel>> DeleteChannel(string partnerId) 
    {
        var actualChannel = await this.context.CommunicationChannels.FirstOrDefaultAsync(c => c.PartnerId.ToString() == partnerId);

        if (actualChannel == null)
        {
            throw new Exception("There doesn't exist a communication channel with this partner");
        }

        this.context.CommunicationChannels.Remove(actualChannel);
        await this.context.SaveChangesAsync();

        return Ok(actualChannel);
    }
}