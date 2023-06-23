using backend.Model;
using backend.Repo;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace backend.Controllers;

[Route("api")]
public class MyController : ControllerBase
{
    private readonly DatabaseContext _context;   
    
    public MyController(DatabaseContext context)
    {
        _context = context;
    }
    
    [HttpGet("login")]
    [AllowAnonymous]
    public ActionResult Login(string username)
    {
        var user = _context.Users.FirstOrDefault(x => x.Username == username);
            
        if (user == null)
        {
            throw new Exception("User not found");
        }

        return Ok(user);
    }
    
    [HttpGet("security")]
    [AllowAnonymous]
    public ActionResult LoginSecurity(string username, string answer)
    {
        var user = _context.Users.FirstOrDefault(x => x.Username == username);
            
        if (user == null)
        {
            throw new Exception("User not found");
        }

        if (user.SecretAnswer != answer)
        {
            throw new Exception("Answer doesn't match");
        }

        return Ok(user);
    }

    [HttpGet("messages")]
    [AllowAnonymous]
    public ActionResult GetMessages(string username)
    {
        var messages = _context.Messages.Where(x => x.Receivers.Contains(username)).ToList();
        return Ok(messages);
    }

    [HttpPost("send/{username}/{message}/{receiver}")]
    [AllowAnonymous]
    public ActionResult SendMessageMulticast(string username, string message, string receiver)
    {
        var user = _context.Users.FirstOrDefault(x => x.Username == username);
        
        if (user == null)
        {
            throw new Exception("User not found");
        }

        var userReceiver = _context.Users.Where(x => receiver.Contains(x.Username)).ToList();

        if (userReceiver.Count == 0)
        {
            throw new Exception("Not found any valid receiver");
        }

        var type = "unicast";

        if (userReceiver.Count > 1)
        {
            type = "multicast";
        }
        
        var sendMessage = new Message
        {
            Sender = username,
            Receivers = receiver,
            Text = message,
            Type = type,
            Views = "0"
        };

        _context.Messages.Add(sendMessage);
        _context.SaveChanges();
        
        return Ok(sendMessage);
    }

    [HttpGet("remove/{receiver}")]
    [AllowAnonymous]
    public ActionResult DeleteMessage(string receiver)
    {
        var user = _context.Users.FirstOrDefault(x => x.Username == receiver);

        if (user == null)
        {
            throw new Exception("User nor found");
        }

        var messages = _context.Messages.Where(x => x.Receivers == receiver).ToList();
        foreach (var message in messages)
        {
            _context.Messages.Remove(message);
        }

        _context.SaveChanges();
        return NoContent();
    }

}