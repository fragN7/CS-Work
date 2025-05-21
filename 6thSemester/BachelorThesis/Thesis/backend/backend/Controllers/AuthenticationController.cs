using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using System.Text;
using backend.Model;
using backend.Model.DTO;
using backend.Repository;
using Microsoft.AspNetCore.Mvc;
using Microsoft.IdentityModel.Tokens;

namespace backend.Controllers;

[ApiController]
[Route("api/[controller]")]
public class AuthenticationController : ControllerBase
{
    private readonly DatabaseContext context;
    private readonly IConfiguration configuration;

    public AuthenticationController(DatabaseContext context, IConfiguration configuration)
    {
        this.context = context;
        this.configuration = configuration;
    }

    [HttpPost("register")]
    public async Task<ActionResult<RegisterResponseDTO>> RegisterAsync(AuthenticateUserDTO user)
    {
        if (this.context.Users.Any(u => u.UserName == user.UserName))
        {
            throw new Exception("Username already in use.");
        }
        
        var newUser = new User()
        {   
            Id = Guid.NewGuid(),
            UserName = user.UserName,
            Password = user.Password
        };
        
        var passwordHash = BCrypt.Net.BCrypt.HashPassword(user.Password);
        newUser.Password = passwordHash;

        this.context.Users.Add(newUser);
        await this.context.SaveChangesAsync();

        var response = new RegisterResponseDTO()
        {
            Id = newUser.Id,
            UserName = user.UserName
        };
        
        return Ok(response);
    }
    
    [HttpPost("login")]
    public ActionResult<LoginResponseDTO> LoginAsync([FromBody] AuthenticateUserDTO user)
    {
        var actualUser = this.context.Users.FirstOrDefault(u => u.UserName == user.UserName);

        if (actualUser is null)
        {
            throw new Exception("User doesn't exist");
        }

        if (!BCrypt.Net.BCrypt.Verify(user.Password, actualUser.Password))
        {
            throw new Exception("Passwords is incorrect");
        }
        
        var token = CreateJwtToken(actualUser);

        var response = new LoginResponseDTO()
        {
            Id = actualUser.Id,
            UserName = actualUser.UserName,
            Token = token
        };
        
        return Ok(response);
    }
    
    private string CreateJwtToken(User user) 
    {   
        var claims = new[]
        {
            new Claim(JwtRegisteredClaimNames.Sub, user.UserName),
            new Claim(JwtRegisteredClaimNames.Jti, Guid.NewGuid().ToString()),
            new Claim("id", user.Id.ToString()),
            new Claim("username", user.UserName)
        };
        
        var key = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(this.configuration.GetSection("AppSettings:Key").Value!));
        var creds = new SigningCredentials(key, SecurityAlgorithms.HmacSha256);
        
        var token = new JwtSecurityToken(
            claims: claims,
            expires: DateTime.UtcNow.AddHours(2),
            signingCredentials: creds
        );

        return new JwtSecurityTokenHandler().WriteToken(token);
    }
    
    private string CreateCertificatePassword(User user) 
    {   
        var claims = new[]
        {
            new Claim(JwtRegisteredClaimNames.Sub, user.UserName),
            new Claim(JwtRegisteredClaimNames.Jti, Guid.NewGuid().ToString()),
            new Claim("id", user.Id.ToString()),
            new Claim("username", user.UserName)
        };
        
        var key = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(this.configuration.GetSection("AppSettings:Key").Value!));
        var creds = new SigningCredentials(key, SecurityAlgorithms.HmacSha256);
        
        var token = new JwtSecurityToken(
            claims: claims,
            expires: DateTime.UtcNow.AddYears(1),
            signingCredentials: creds
        );

        return new JwtSecurityTokenHandler().WriteToken(token);
    }
}