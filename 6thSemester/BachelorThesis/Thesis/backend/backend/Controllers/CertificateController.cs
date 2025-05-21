using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using System.Text;
using backend.Model;
using backend.Model.DTO;
using backend.Repository;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.IdentityModel.Tokens;

namespace backend.Controllers;

[ApiController]
[Route("api/[controller]")]
public class CertificateController : ControllerBase
{
    private readonly DatabaseContext context;
    private readonly IConfiguration configuration;

    public CertificateController(DatabaseContext context, IConfiguration configuration)
    {
        this.context = context;
        this.configuration = configuration;
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
    
    [HttpPost("certificate/create/{id}")]
    [Authorize]
    public async Task<ActionResult<Certificate>> GenerateCertificate([FromBody] CertificateDTO certificate, string id)
    {
        var validCertificate = await this.context.Certificates
            .FirstOrDefaultAsync(c => c.Sender == certificate.Sender && c.Receiver == certificate.Receiver);

        if (validCertificate != null)
        {
            throw new Exception("This certificate is already implemented");
        }

        var user = await this.context.Users.FirstOrDefaultAsync(u => u.Id.ToString() == id);

        if (user == null)
        {
            throw new Exception("Can not create certificate password");
        }

        var addCertificate = new Certificate
        {
            Id = new Guid(),
            Sender = certificate.Sender,
            Receiver = certificate.Receiver,
            Standard = certificate.Standard,
            HostName = certificate.HostName,
            Port = certificate.Port,
            Password = this.CreateCertificatePassword(user)
        };

        return Ok(addCertificate);
    }
    
    
}