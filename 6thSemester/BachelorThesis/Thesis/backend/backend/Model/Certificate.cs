namespace backend.Model;

public class Certificate
{
    public Guid Id { get; set; }
    public string Sender { get; set; } = string.Empty;
    public string Receiver { get; set; } = string.Empty;
    public string Standard { get; set; } = string.Empty;
    public string HostName { get; set; } = string.Empty;
    public string Port { get; set; } = string.Empty;
    public string Password { get; set; } = string.Empty;
}