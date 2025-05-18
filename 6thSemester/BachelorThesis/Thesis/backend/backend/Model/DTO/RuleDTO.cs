namespace backend.Model.DTO;

public class RuleDTO
{
    public string Sender { get; set; } = string.Empty;
    public string ObjectType { get; set; } = string.Empty;
    public string Receiver { get; set; } = string.Empty;
    public string TimeStamp { get; set; } = string.Empty;
    
    public Guid WorkflowId { get; set; }
}