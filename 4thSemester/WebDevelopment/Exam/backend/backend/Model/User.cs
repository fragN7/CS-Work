﻿using System.ComponentModel.DataAnnotations;

namespace backend.Model;

public class User
{
    [Key]
    public int Id { get; set; }
    public string Username { get; set; } = string.Empty;
    public string SecretQuestion { get; set; } = string.Empty;
    public string SecretAnswer { get; set; } = string.Empty;
}