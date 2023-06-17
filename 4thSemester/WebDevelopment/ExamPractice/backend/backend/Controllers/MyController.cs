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

    [HttpGet]
    [AllowAnonymous]
    public ActionResult<ResponseDTO> GetArticlesBooks(string firstAuthor, string secondAuthor = "")
    {
        var author1 = _context.Persons.FirstOrDefault(p => p.Name == firstAuthor);

        if (author1 == null)
        {
            throw new Exception("Author not found");
        }

        var books1 = author1.Books.ToList();
        var articles1 = author1.Articles.ToList();

        var result = new ResponseDTO();

        if (secondAuthor == string.Empty)
        {
            if (books1.Count > articles1.Count)
            {
                result.Books = books1;
                return result;
            }

            result.Articles = articles1;
            return result;
        }

        var author2 = _context.Persons.FirstOrDefault(p => p.Name == secondAuthor);
        if (author2 == null)
        {
            throw new Exception("Author not found");
        }

        var books2 = author2.Books.ToList();
        var articles2 = author2.Articles.ToList();

        result.Books = books1.Count > books2.Count ? books1 : books2;
        result.Articles = articles1.Count > articles2.Count ? articles1 : articles2;

        return result;
    }
}