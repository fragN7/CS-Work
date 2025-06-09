namespace backend.Model.DTO;

public class WorkflowDTO
{
    public string Name { get; set; } = string.Empty;
    public ICollection<WorkflowStepDTO> WorkflowSteps { get; set; } = null!;
}