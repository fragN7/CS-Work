namespace backend.Model;

public class ResponseDTO
{
    public List<BookDTO> Books { get; set; } = null!;
    public List<ArticleDTO> Articles { get; set; } = null!;
}