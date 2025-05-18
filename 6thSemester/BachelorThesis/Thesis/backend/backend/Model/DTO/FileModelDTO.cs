namespace backend.Model.DTO;

public class FileModelDTO
{
    public string Filename { get; set; } = string.Empty;
    public string Filetype { get; set; } = string.Empty;
    public string Filedata { get; set; } = string.Empty;
    public DateTime UploadedAt { get; set; }

}