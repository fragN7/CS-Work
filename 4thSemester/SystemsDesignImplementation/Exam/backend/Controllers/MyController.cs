using System.Text.RegularExpressions;
using backend.Model;
using backend.Repo;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace backend.Controllers;

[Route("api")]
public class MyController : ControllerBase
{
    private readonly DatabaseContext _context;

    public MyController(DatabaseContext context)
    {
        _context = context;
    }

    [HttpPost("validate/{gameId}")]
    [AllowAnonymous]
    public ActionResult ValidateGame(string gameId)
    {
        var game = _context.Games.FirstOrDefault(x => x.GameId == gameId);
        if (game == null)
        {
            throw new Exception("Game doesn't exist");
        }

        return Ok(game);
    }
    
    [HttpPost("game/{gameId}/{word}/{lives}")]
    [AllowAnonymous]
    public ActionResult PostGame(string gameId, string word, int lives)
    {
        var existsGame = _context.Games.FirstOrDefault(x => x.GameId == gameId);
        if (existsGame != null)
        {
            throw new Exception("Game already exists!");
        }
        
        var pattern = @"^[a-zA-Z0-9]{6}$";
        if (!Regex.IsMatch(gameId, pattern))
        {
            throw new Exception("Game doesn't have 6 alphanumerical characters!");
        }
        
        var numberPattern = @"\d";
        if (word.Length < 3 || Regex.IsMatch(word, numberPattern))
        {
            throw new Exception("Word is too short or it contains numbers!");
        }

        if (lives < 2)
        {
            throw new Exception("There should be at least 2 lives!");
        }

        var game = new Game
        {
            GameId = gameId,
            Word = word.ToUpper(),
            Letters = word.Length,
            Lives = lives
        };
        
        _context.Games.Add(game);
        _context.SaveChanges();
        return Ok(game);
    }
}