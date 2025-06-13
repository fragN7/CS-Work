using System.Text.Json;
using backend.Model;
using backend.Model.DTO;
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

    public PartnerController(DatabaseContext context)
    {
        this.context = context;
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
              EF.Functions.Like(p.Certificate, certificatePattern) &&
              p.Id.ToString() != "26a31e0a-1c62-46a8-a716-a6e8fe18a158")
            .ToListAsync();
        
        if (partners == null)
        {
            throw new Exception("There are no partners");
        }

        return Ok(partners);
    }
    
    [HttpGet("partners/{id}")]
    [Authorize]
    public async Task<ActionResult<List<Partner>>> GetPartnerById(string id)
    {
        var partner = await this.context.Partners.FirstOrDefaultAsync(p => p.Id.ToString() == id);
        
        if (partner == null)
        {
            throw new Exception("There are no partners");
        }

        return Ok(partner);
    }
    
    private async void CopyCertificate(IFormFile file)
    {
        if (file == null || file.Length == 0)
        {
            throw new ArgumentException("Uploaded file is null or empty.");
        }

        var archiveRoot = Path.Combine(Directory.GetCurrentDirectory(), "archive");
        var targetFolder = Path.Combine(archiveRoot, "certificates");

        if (!Directory.Exists(targetFolder))
        {
            Directory.CreateDirectory(targetFolder);
        }

        var fileName = Path.GetFileName(file.FileName);
        var finalFilePath = Path.Combine(targetFolder, fileName);

        await using var stream = new FileStream(finalFilePath, FileMode.Create);
        await file.CopyToAsync(stream);
    }
    
    private static void DeleteCertificate(string fileName)
    {
        var archiveRoot = Path.Combine(Directory.GetCurrentDirectory(), "archive");
        var certificatesFolder = Path.Combine(archiveRoot, "certificates");

        var fullFilePath = Path.Combine(certificatesFolder, fileName);

        if (System.IO.File.Exists(fullFilePath))
        {
            System.IO.File.Delete(fullFilePath);
        }
        else
        {
            throw new FileNotFoundException("Certificate file not found.", fullFilePath);
        }
    }

    private async Task AddCertificate(IFormFile certificate)
    {
        if (certificate == null || certificate.Length == 0)
        {
            throw new Exception("Invalid file");
        }

        using var stream = new StreamReader(certificate.OpenReadStream());
        var content = await stream.ReadToEndAsync();

        var cert = JsonSerializer.Deserialize<Certificate>(content, new JsonSerializerOptions
        {
            PropertyNameCaseInsensitive = true
        });

        if (cert == null)
        {
            throw new Exception("Cannot parse file");
        }

        cert.Id = Guid.NewGuid();

        this.context.Certificates.Add(cert);
        await this.context.SaveChangesAsync();

        Ok(cert);
    }
    
    [HttpPost("partner/add")]
    [Authorize]
    public async Task<ActionResult<Partner>> AddPartner([FromForm] PartnerDTO partner)
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

        await this.AddCertificate(partner.CertificateFile);
        this.CopyCertificate(partner.CertificateFile);

        await this.context.Partners.AddAsync(addPartner);
        await this.context.SaveChangesAsync();

        return Ok(addPartner);
    }
    
    [HttpPut("partner/update/{id}")]
    [Authorize]
    public async Task<ActionResult<Partner>> UpdatePartner([FromForm] PartnerDTO partner, string id)
    {
        var actualPartner = await this.context.Partners.FirstOrDefaultAsync(p => p.Id.ToString() == id);

        if (actualPartner == null)
        {
            throw new Exception("This partner doesn't exist");
        }

        try
        {
            DeleteCertificate(actualPartner.Certificate);
        }
        catch (Exception ex)
        {
            // ignored
        }

        actualPartner.Name = partner.Name;
        actualPartner.IpAddress = partner.IpAddress;
        actualPartner.Certificate = partner.Certificate;
        
        this.CopyCertificate(partner.CertificateFile);

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
        
        var warningPartner = await this.context.Partners
            .FirstOrDefaultAsync(r => r.Id.ToString() == "d6ef4e0b-e070-48a4-a466-a45426eeb135");

        if (warningPartner == null)
        {
            throw new Exception("This partner cannot be deleted");
        }

        var certificate = await this.context.Certificates.FirstOrDefaultAsync(c => c.Sender == actualPartner.Name);

        if (certificate == null)
        {
            throw new Exception("Certificate doesn't exist");
        }
        
        this.context.Certificates.Remove(certificate);
        DeleteCertificate(actualPartner.Certificate);
        this.context.Partners.Remove(actualPartner);
        await this.context.SaveChangesAsync();

        return Ok(actualPartner);
    }
}