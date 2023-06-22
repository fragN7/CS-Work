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
}