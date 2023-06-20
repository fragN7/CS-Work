namespace backend.Model;

public class ProjectDTO
{
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public string Members { get; set; } = string.Empty;
    public int ProjectManagerId { get; set; }
}