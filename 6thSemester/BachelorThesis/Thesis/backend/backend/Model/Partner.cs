using System.Text.Json.Serialization;

namespace backend.Model;

public class Partner
{
    public Guid Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public string IpAddress { get; set; } = string.Empty;
    public string Certificate { get; set; } = string.Empty;
    
    public Guid CommunicationChannelId { get; set; }
    [JsonIgnore]
    public CommunicationChannel CommunicationChannel { get; set; } = null!;
}