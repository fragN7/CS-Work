namespace Lab10_Dotnet.Data;

public abstract class MultimediaDTO
{
    public string Title { get; set; } = string.Empty;
    public string Format { get; set; } = string.Empty;
    public string Genre { get; set; } = string.Empty;
    public string Path { get; set; } = string.Empty;
}