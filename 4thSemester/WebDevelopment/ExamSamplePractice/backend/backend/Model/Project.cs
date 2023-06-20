using System.ComponentModel.DataAnnotations;

namespace backend.Model;

public class Project
{
    [Key]
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public string Members { get; set; } = string.Empty;
    public int ProjectManagerId { get; set; }
    public SoftwareDeveloper ProjectManager { get; set; } = null!;
}