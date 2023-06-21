using System.ComponentModel.DataAnnotations;

namespace backend.Model;

public class Link
{
    [Key]
    public int Id { get; set; }
    public int Duration { get; set; }
    public int Distance { get; set; }
    public int FirstCityId { get; set; }
    public City FirstCity { get; set; } = null!;
    public int SecondCityId { get; set; }
    public City SecondCity { get; set; } = null!;
}