namespace backend.Model;

public class ArticleDTO
{
    public int Id { get; set; }
    public string Title { get; set; } = string.Empty;
    public string Type { get; set; } = string.Empty;
    public int NumPages { get; set; }
    public int AuthorId { get; set; }
}