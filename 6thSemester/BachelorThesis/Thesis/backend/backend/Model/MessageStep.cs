using System.Text.Json.Serialization;

namespace backend.Model;

public class MessageStep
{
    public Guid Id { get; set; }
    public string StepName { get; set; } = string.Empty;
    public DateTime StartedTime { get; set; }
    public DateTime EndedTime { get; set; }
    public string Result { get; set; } = string.Empty;
    public string FilePath { get; set; } = string.Empty;
    public Guid MessageId { get; set; }
    [JsonIgnore]
    public Message Message { get; set; } = null!;
}