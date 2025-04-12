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
    public async Task<ActionResult<List<Message>>> GetMessaages(string pattern)
    {
        var likePattern = pattern.Replace('*', '%');
        var messages = await this.context.Messages.Where(m => EF.Functions.Like(m.FilePath, likePattern)).ToListAsync();

        return Ok(messages);
    }
    
    [HttpPost("message/store")]
    [Authorize]
    public async Task<ActionResult<Message>> AddMessaage([FromBody] Message message)
    {
        await this.context.Messages.AddAsync(message);
        await this.context.SaveChangesAsync();

        return Ok(message);
    }
    
    [HttpDelete("message/delete/{id}")]
    [Authorize]
    public async Task<ActionResult<Message>> DeleteMessaage(string id)
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