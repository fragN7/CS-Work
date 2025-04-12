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
    private readonly IConfiguration configuration;

    public CommunicationChannelController(DatabaseContext context, IConfiguration configuration)
    {
        this.context = context;
        this.configuration = configuration;
    }
    
    [HttpPost("channel/add")]
    [Authorize]
    public async Task<ActionResult<CommunicationChannel>> AddChannel([FromBody] CommunicationChannelDTO channel)
    {
        var actualChannel = await this.context.CommunicationChannels.FirstOrDefaultAsync(c => c.PartnerId == channel.PartnerId);

        if (actualChannel != null)
        {
            throw new Exception("There already exists a communication channel with this partner");
        }

        var addChannel = new CommunicationChannel
        {
            Id = new Guid(),
            Partner = channel.Partner,
            PartnerId = channel.PartnerId
        };

        await this.context.CommunicationChannels.AddAsync(addChannel);
        await this.context.SaveChangesAsync();

        return Ok(addChannel);
    }
    
    [HttpPut("channel/update/{id}")]
    [Authorize]
    public async Task<ActionResult<CommunicationChannel>> UpdateChannel([FromBody] CommunicationChannelDTO channel, [FromQuery] string id)
    {
        var actualChannel = await this.context.CommunicationChannels.FirstOrDefaultAsync(c => c.Id.ToString() == id);

        if (actualChannel == null)
        {
            throw new Exception("There doesn't exist a communication channel with this partner");
        }

        actualChannel.PartnerId = channel.PartnerId;
        actualChannel.Partner = channel.Partner;

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