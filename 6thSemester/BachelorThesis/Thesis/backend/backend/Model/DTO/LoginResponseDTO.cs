namespace backend.Model.DTO;

public class LoginResponseDTO
{
    public Guid Id { get; set; }

    public string UserName { get; set; } = string.Empty;
    public string Token { get; set; } = string.Empty;
}