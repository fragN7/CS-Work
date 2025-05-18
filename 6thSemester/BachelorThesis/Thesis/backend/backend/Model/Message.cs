using System.Text.Json.Serialization;

namespace backend.Model;

public class Message
{
    public Guid Id { get; set; }
    public DateTime TimeStamp { get; set; } = DateTime.UtcNow;
    public Guid RuleId { get; set; }
    public Rule Rule { get; set; } = null!;
    public ICollection<MessageStep> MessageSteps { get; set; } = null!;
}