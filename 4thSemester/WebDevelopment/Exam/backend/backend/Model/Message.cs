using System.ComponentModel.DataAnnotations;

namespace backend.Model;

public class Message
{
    [Key]
    public int Id { get; set; }
    public string Sender { get; set; } = string.Empty;
    public string Receivers { get; set; } = string.Empty;
    public string Type { get; set; } = string.Empty;
    public string Text { get; set; } = string.Empty;
    public string Views { get; set; } = string.Empty;
}