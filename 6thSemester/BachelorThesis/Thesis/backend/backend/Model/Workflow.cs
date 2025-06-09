using System.Text.Json.Serialization;

namespace backend.Model;

public class Workflow
{
    public Guid Id { get; set; }
    public string Name { get; set; } = string.Empty;
    
    public ICollection<WorkflowStep> WorkflowSteps { get; set; } = null!;
    [JsonIgnore]
    public ICollection<Rule> Rules { get; set; } = null!;
}