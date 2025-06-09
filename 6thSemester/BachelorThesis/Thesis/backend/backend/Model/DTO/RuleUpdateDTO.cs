namespace backend.Model.DTO;

public class RuleUpdateDTO
{
    public Guid WorkflowId { get; set; }
    
    public string TimeStamp { get; set; } = string.Empty;
}