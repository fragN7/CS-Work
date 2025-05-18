using System.Text.Json.Serialization;

namespace backend.Model;

public class Workflow
{
    public Guid Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public List<string> Steps { get; set; } = new List<string>();
    [JsonIgnore]
    public ICollection<Rule> Rules { get; set; } = null!;
}