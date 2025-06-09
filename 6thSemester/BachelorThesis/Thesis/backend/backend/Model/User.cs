using System.Runtime.InteropServices.JavaScript;
using System.Text.Json.Serialization;

namespace backend.Model;

public class User
{
    public Guid Id { get; set; }
    public string UserName { get; set; } = string.Empty;
    public string Password { get; set; } = string.Empty;
    [JsonIgnore]
    public ICollection<Message> Messages { get; set; } = null!;
}