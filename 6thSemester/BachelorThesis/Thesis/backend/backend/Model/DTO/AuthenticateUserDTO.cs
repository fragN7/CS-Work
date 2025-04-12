namespace backend.Model.DTO;

public class AuthenticateUserDTO
{
    public string UserName { get; set; } = string.Empty;
    public string Password { get; set; } = string.Empty;
}