namespace backend.Model;

public class Message
{
    public Guid Id { get; set; }
    public DateTime TimeStamp { get; set; } = DateTime.Now;
    public string FilePath { get; set; } = string.Empty;
    
    public Guid RuleId { get; set; }
    public Rule Rule { get; set; } = null!;
}