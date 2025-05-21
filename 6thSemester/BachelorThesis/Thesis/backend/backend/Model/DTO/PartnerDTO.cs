namespace backend.Model.DTO;

public class PartnerDTO
{
    public string Name { get; set; } = string.Empty;
    public string IpAddress { get; set; } = string.Empty;
    public string Certificate { get; set; } = string.Empty;
    public IFormFile CertificateFile { get; set; } = null!;
}