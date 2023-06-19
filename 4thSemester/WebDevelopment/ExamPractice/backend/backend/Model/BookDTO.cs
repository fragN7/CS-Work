namespace backend.Model;

public class BookDTO
{
    public int Id { get; set; }
    public string Title { get; set; } = string.Empty;
    public string Brand { get; set; } = string.Empty;
    public int ReleaseYear { get; set; }
    public int AuthorId { get; set; }
}