using System.ComponentModel.DataAnnotations;

namespace Server.Model;

public class ChessRecord
{
    [Key]
    public int Id { get; set; }
    public int Rating { get; set; }
    public string OpponentName { get; set; } = string.Empty;
    public int OpponentRating { get; set; }
    public string OpponentProfile { get; set; } = string.Empty;
    public string GameOutcome { get; set; } = string.Empty;
    public string GameOpening { get; set; } = string.Empty;
    public string GameTag { get; set; } = string.Empty;
    public string Notes { get; set; } = string.Empty;
}
