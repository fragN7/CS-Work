using System.ComponentModel.DataAnnotations;

namespace backend.Model;

public class Game
{
    [Key] public string GameId { get; set; } = string.Empty;
    public int Letters { get; set; }
    public int Lives { get; set; }
    public string Word { get; set; } = string.Empty;
}