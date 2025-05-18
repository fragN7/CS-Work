using System.Text.Json.Serialization;

namespace backend.Model;

public class Rule
{
    public Guid Id { get; set; }
    public string Sender { get; set; } = string.Empty;
    public string ObjectType { get; set; } = string.Empty;
    public string Receiver { get; set; } = string.Empty;
    public string TimeStamp { get; set; } = string.Empty;
    
    public Guid WorkflowId { get; set; }
    public Workflow Workflow { get; set; } = null!;
    
    public Guid CommunicationChannelId { get; set; } 
    [JsonIgnore]
    public CommunicationChannel CommunicationChannel { get; set; } = null!;

    [JsonIgnore]
    public ICollection<Message> Messages { get; set; } = null!;
}