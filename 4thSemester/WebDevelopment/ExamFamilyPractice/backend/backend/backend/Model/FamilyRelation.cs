using System.ComponentModel.DataAnnotations;

namespace backend.Model;

public class FamilyRelation
{
    [Key]
    public int Id { get; set; }
    public string Mother { get; set; } = string.Empty;
    public string Father { get; set; } = string.Empty;
    public int UserId { get; set; }
    public User User { get; set; } = null!;
}