using System.Text.Json.Serialization;

namespace backend.Model;

public class CommunicationChannel
{
    public Guid Id { get; set; }

    [JsonIgnore]
    public ICollection<Rule> Rules { get; set; } = null!;
    
    public Guid PartnerId { get; set; }
    public Partner Partner { get; set; } = null!;
}