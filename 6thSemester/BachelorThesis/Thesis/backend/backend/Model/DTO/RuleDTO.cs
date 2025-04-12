namespace backend.Model.DTO;

public class RuleDTO
{
    public Guid Id { get; set; }
    public string Sender { get; set; } = string.Empty;
    public string ObjectType { get; set; } = string.Empty;
    public string Receiver { get; set; } = string.Empty;
    public string Timestamp { get; set; } = string.Empty;
    
    public Guid WorkflowId { get; set; }
    public Guid CommunicationChannelId { get; set; }
}