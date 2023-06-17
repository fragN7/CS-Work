using System.ComponentModel.DataAnnotations;

namespace backend.Model;

public class Person
{
    [Key]
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public int Age { get; set; }
    public int Salary { get; set; }
    public ICollection<Article> Articles { get; set; } = null!;
    public ICollection<Book> Books { get; set; } = null!;
}