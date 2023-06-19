using backend.Model;
using backend.Repo;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace backend.Controllers;

[Route("api")]
public class MyController : ControllerBase
{
    private readonly DatabaseContext _context;

    public MyController(DatabaseContext context)
    {
        _context = context;
    }

    private static BookDTO BookToDTO(Book book) =>
        new BookDTO
        {
            Id = book.Id,
            Title = book.Title,
            Brand = book.Brand,
            ReleaseYear = book.ReleaseYear,
            AuthorId = book.AuthorId
        };
    
    private static ArticleDTO ArticleToDTO(Article article) =>
        new ArticleDTO
        {
            Id = article.Id,
            Title = article.Title,
            Type = article.Type,
            NumPages = article.NumPages,
            AuthorId = article.AuthorId
        };

    [HttpGet]
    [AllowAnonymous]
    public ActionResult<ResponseDTO> GetArticlesBooks(string firstAuthor, string? secondAuthor)
    {
        var author1 = _context.Persons.FirstOrDefault(p => p.Name == firstAuthor);

        if (author1 == null)
        {
            throw new Exception("Author not found");
        }

        var books1 = _context.Books
            .Where(p => p.AuthorId == author1.Id)
            .Select(x => BookToDTO(x))
            .ToList();
        
        var articles1 = _context.Articles
            .Where(p => p.AuthorId == author1.Id)
            .Select(x => ArticleToDTO(x))
            .ToList();

        var result = new ResponseDTO();

        if (secondAuthor == null)
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
            throw new Exception("Second author not found");
        }

        var books2 = _context.Books
            .Where(p => p.AuthorId == author2.Id)
            .Select(x => BookToDTO(x))
            .ToList();
        
        var articles2 = _context.Articles
            .Where(p => p.AuthorId == author2.Id)
            .Select(x => ArticleToDTO(x))
            .ToList();

        result.Books = books1.Count > books2.Count ? books1 : books2;
        result.Articles = articles1.Count > articles2.Count ? articles1 : articles2;
        
        return result;
    }
}