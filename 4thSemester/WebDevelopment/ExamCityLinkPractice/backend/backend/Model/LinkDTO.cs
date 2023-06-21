namespace backend.Model;

public class LinkDTO
{
    public int Id { get; set; }
    public int Duration { get; set; }
    public int Distance { get; set; }
    public int FirstCityId { get; set; }
    public string FirstCity { get; set; } = string.Empty;
    public int SecondCityId { get; set; }
    public string SecondCity { get; set; } = string.Empty;
}