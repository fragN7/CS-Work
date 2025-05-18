namespace backend.Model.DTO;

public class MessageDTO
{
    public Guid RuleId { get; set; }
    public IFormFile File { get; set; } = null!;
}