namespace backend.Model.DTO;

public class WorkflowStepDTO
{
    public string Name { get; set; } = string.Empty;
    public string FilePath { get; set; } = string.Empty;
    public string Command { get; set; } = string.Empty;

    public IFormFile File { get; set; } = null!;
}