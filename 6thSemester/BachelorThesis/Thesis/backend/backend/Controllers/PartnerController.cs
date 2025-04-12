using backend.Model;
using backend.Repository;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace backend.Controllers;

[ApiController]
[Route("api/[controller]")]
public class PartnerController : ControllerBase
{
    private readonly DatabaseContext context;
    private readonly IConfiguration configuration;

    public PartnerController(DatabaseContext context, IConfiguration configuration)
    {
        this.context = context;
        this.configuration = configuration;
    }
    
    [HttpGet("partners/{name}/{ipAddress}/{certificate}")]
    [Authorize]
    public async Task<ActionResult<List<Partner>>> GetPartners(string name, string ipAddress, string certificate)
    {
        var namePattern = name.Replace('*', '%');
        var ipAddressPattern = ipAddress.Replace('*', '%');
        var certificatePattern = certificate.Replace('*', '%');

        var partners = await this.context.Partners.Where
        (p => EF.Functions.Like(p.Name, namePattern) && 
              EF.Functions.Like(p.IpAddress, ipAddressPattern) && 
              EF.Functions.Like(p.Certificate, certificatePattern)).ToListAsync();
        
        if (partners == null)
        {
            throw new Exception("There are no partners");
        }

        return Ok(partners);
    }
    
    [HttpPost("partner/add")]
    [Authorize]
    public async Task<ActionResult<Partner>> AddPartner([FromBody] PartnerDTO partner)
    {
        var actualPartner = await this.context.Partners.FirstOrDefaultAsync(p => p.IpAddress == partner.IpAddress);

        if (actualPartner != null)
        {
            throw new Exception("There already exists a partner with this IP Address");
        }

        var addPartner = new Partner
        {
            Id = new Guid(),
            Name = partner.Name,
            IpAddress = partner.IpAddress,
            Certificate = partner.Certificate
        };

        await this.context.Partners.AddAsync(addPartner);
        await this.context.SaveChangesAsync();

        return Ok(addPartner);
    }
    
    [HttpPut("partner/update/{id}")]
    [Authorize]
    public async Task<ActionResult<Partner>> UpdatePartner([FromBody] PartnerDTO partner, [FromQuery] string id)
    {
        var actualPartner = await this.context.Partners.FirstOrDefaultAsync(p => p.Id.ToString() == id);

        if (actualPartner == null)
        {
            throw new Exception("There are no partners with this IP address");
        }

        actualPartner.Name = partner.Name;
        actualPartner.IpAddress = partner.IpAddress;
        actualPartner.Certificate = partner.Certificate;

        await this.context.SaveChangesAsync();

        return Ok(actualPartner);
    }
    
    [HttpDelete("partner/delete/{id}")]
    [Authorize]
    public async Task<ActionResult<Partner>> DeletePartner(string id) 
    {
        var actualPartner = await this.context.Partners.FirstOrDefaultAsync(p => p.Id.ToString() == id);

        if (actualPartner == null)
        {
            throw new Exception("Partner doesn't exist");
        }

        this.context.Partners.Remove(actualPartner);
        await this.context.SaveChangesAsync();

        return Ok(actualPartner);
    }
}