namespace backend.Model;

public class PartnerDTO
{
    public Guid Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public string IpAddress { get; set; } = string.Empty;
    public string Certificate { get; set; } = string.Empty;
    
}