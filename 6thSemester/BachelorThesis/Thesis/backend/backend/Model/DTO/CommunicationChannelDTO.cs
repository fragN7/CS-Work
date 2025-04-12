namespace backend.Model.DTO;

public class CommunicationChannelDTO
{
    public Guid Id { get; set; }
    public Guid PartnerId { get; set; }
    public Partner Partner { get; set; } = null!;
}