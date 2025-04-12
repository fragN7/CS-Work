namespace backend.Model.DTO;

public class LoginResponseDTO
{
    public Guid Id { get; set; }
    public string Token { get; set; } = string.Empty;
}