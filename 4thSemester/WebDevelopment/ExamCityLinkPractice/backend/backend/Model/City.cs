using System.ComponentModel.DataAnnotations;

namespace backend.Model;

public class City
{
    [Key]
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Country { get; set; } = string.Empty;
    public ICollection<Link> FirstLinks { get; set; } = null!;
    public ICollection<Link> SecondLinks { get; set; } = null!;
}