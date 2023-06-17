using System.ComponentModel.DataAnnotations;

namespace backend.Model;

public class Book
{
    [Key]
    public int Id { get; set; }
    public string Title { get; set; } = string.Empty;
    public string Brand { get; set; } = string.Empty;
    public int ReleaseYear { get; set; }
    public int AuthorId { get; set; }
    public Person Author { get; set; } = null!;
}