namespace backend.Model.DTO;

public class WorkflowDTO
{
    public string Name { get; set; } = string.Empty;
    public List<string> Steps { get; set; } = new List<string>();
}