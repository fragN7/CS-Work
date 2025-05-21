namespace backend.Model.DTO;

public class CertificateDTO
{
    public string Sender { get; set; } = string.Empty;
    public string Receiver { get; set; } = string.Empty;
    public string Standard { get; set; } = string.Empty;
    public string HostName { get; set; } = string.Empty;
    public string Port { get; set; } = string.Empty;
}