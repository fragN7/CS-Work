using System.ComponentModel.DataAnnotations;

namespace backend.Model;

public class SoftwareDeveloper
{
    [Key]
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public int Age { get; set; }
    public string Skills { get; set; } = string.Empty;
    public ICollection<Project> Projects { get; set; } = null!;
}