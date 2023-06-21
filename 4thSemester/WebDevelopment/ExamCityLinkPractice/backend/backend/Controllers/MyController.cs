using backend.Model;
using backend.Repo;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore.Query.SqlExpressions;

namespace backend.Controllers;

[Route("api")]
public class MyController : ControllerBase
{
    private readonly DatabaseContext _context;

    public MyController(DatabaseContext context)
    {
        _context = context;
    }

    private static CityDTO CityToDTO(City city) => new CityDTO
    {
        Id = city.Id,
        Name = city.Name,
        Country = city.Country
    };

    private static LinkDTO LinkToDTO(Link link) => new LinkDTO
    {
        Id = link.Id,
        Duration = link.Duration,
        Distance = link.Distance,
        FirstCityId = link.FirstCityId,
        SecondCityId = link.SecondCityId
    };

    [HttpGet("cities")]
    [AllowAnonymous]
    public ActionResult<List<CityDTO>> GetAllCities()
    {
        return _context.Cities
            .Select(x => CityToDTO(x))
            .ToList();
    }

    [HttpGet("links/{name}")]
    [AllowAnonymous]
    public ActionResult GetLinkCity(string name)
    {
        var city = _context.Cities.FirstOrDefault(x => x.Name == name);

        if (city == null)
        {
            throw new Exception("City not found");
        }

        var links = _context.Links
            .Where(x => x.FirstCityId == city.Id || x.SecondCityId == city.Id)
            .Select(x => LinkToDTO(x));    
        
        return Ok(links);
    }
}