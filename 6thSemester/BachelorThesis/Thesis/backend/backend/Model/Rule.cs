namespace backend.Model;

public class Rule
{
    public Guid Id { get; set; }
    public string Sender { get; set; } = string.Empty;
    public string ObjectType { get; set; } = string.Empty;
    public string Receiver { get; set; } = string.Empty;
    public string Timestamp { get; set; } = string.Empty;
    
    public Guid WorkflowId { get; set; }
    public Workflow Workflow { get; set; } = null!;
    
    public Guid CommunicationChannelId { get; set; }
    public CommunicationChannel CommunicationChannel { get; set; } = null!;

    public ICollection<Message> Messages { get; set; } = null!;
}