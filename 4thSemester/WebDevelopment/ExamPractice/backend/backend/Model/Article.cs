using System.ComponentModel.DataAnnotations;

namespace backend.Model;

public class Article
{
    [Key]
    public int Id { get; set; }
    public string Title { get; set; } = string.Empty;
    public string Type { get; set; } = string.Empty;
    public int NumPages { get; set; }
    public int AuthorId { get; set; }
    public Person Author { get; set; } = null!;
}