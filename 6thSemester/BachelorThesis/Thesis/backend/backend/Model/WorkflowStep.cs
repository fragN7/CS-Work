using System.Text.Json.Serialization;

namespace backend.Model;

public class WorkflowStep
{
    public Guid Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public string FilePath { get; set; } = string.Empty;
    public string Command { get; set; } = string.Empty;
    public Guid WorkflowId { get; set; }
    [JsonIgnore]
    public Workflow Workflow { get; set; } = null!;
}