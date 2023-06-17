namespace backend.Model;

public class ResponseDTO
{
    public List<Book> Books { get; set; } = null!;
    public List<Article> Articles { get; set; } = null!;
}