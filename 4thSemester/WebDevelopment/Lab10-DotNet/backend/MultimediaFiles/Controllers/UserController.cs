using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using System.Text;
using Lab10_Dotnet.Data;
using Lab10_Dotnet.Repository;
using Microsoft.AspNetCore.Mvc;
using Microsoft.IdentityModel.Tokens;

namespace Lab10_Dotnet.Controllers;

[ApiController]
[Route("api/[controller]")]
public class UserController : ControllerBase
{
    private readonly MultimediaDbContext context;
    private readonly IConfiguration configuration;

    public UserController(MultimediaDbContext context, IConfiguration configuration)
    {
        this.context = context;
        this.configuration = configuration;
    }
    
    [HttpPost("login")]
    public ActionResult<string> Login([FromBody] UserDTO user)
    {
        var actualUser = this.context.Users.FirstOrDefault(u => u.Username == user.Username);
            
        if (actualUser is null) 
        {
            throw new Exception("User doesn't exist");
        }

        if (user.Password != actualUser.Password)
        {
            throw new Exception("Password is incorrect.");
        }

        var token = CreateJwtToken(actualUser);

        return token;
    }

    private string CreateJwtToken(User user) 
    {   
        List<Claim> claims = new List<Claim> {
            new Claim(ClaimTypes.NameIdentifier, user.Username)
        };

        var key = new SymmetricSecurityKey(
            Encoding.UTF8.GetBytes(this.configuration.GetSection("AppSettings:Key").Value!
            ));

        var creds = new SigningCredentials(key, SecurityAlgorithms.HmacSha512Signature);

        var token = new JwtSecurityToken(
            claims: claims,
            expires: DateTime.Now.AddHours(1),
            signingCredentials: creds
        );

        var jwt = new JwtSecurityTokenHandler().WriteToken(token);

        return jwt;
    }
}