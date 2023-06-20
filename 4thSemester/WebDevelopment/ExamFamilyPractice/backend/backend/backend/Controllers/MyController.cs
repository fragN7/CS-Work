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

    private static FamilyRelationDTO RelationToDTO(FamilyRelation relation) => new FamilyRelationDTO
    {
        Father = relation.Father,
        Mother = relation.Mother,
        UserId = relation.UserId
    };

    [HttpGet("login")]
    [AllowAnonymous]
    public ActionResult Login(string username, string? mother, string? father)
    {
        var user = _context.Users.FirstOrDefault(x => x.Username == username);

        if (user == null)
        {
            throw new Exception("User not found");
        }

        var relation = _context.FamilyRelations
            .Where(x => x.Mother == mother || x.Father == father)
            .Select(x => RelationToDTO(x));

        if (relation == null)
        {
            throw new Exception("Relation not found");
        }

        return Ok(relation);
    }

    [HttpPost("add")]
    [AllowAnonymous]
    public ActionResult AddRelation(FamilyRelationDTO relation)
    {
        var user = _context.Users.FirstOrDefault(x => x.Id == relation.UserId);

        if (user == null)
        {
            throw new Exception("User not found");
        }

        var addRelation = new FamilyRelation
        {
            Mother = relation.Mother,
            Father = relation.Father,
            UserId = relation.UserId,
            User = user
        };

        _context.FamilyRelations.Add(addRelation);
        _context.SaveChanges();

        return Ok(relation);
    }

    [HttpGet("siblings")]
    [AllowAnonymous]
    public ActionResult<HashSet<string>> GetSiblings(int userId)
    {
        var userParents = _context.FamilyRelations.FirstOrDefault(x => x.UserId == userId);

        if (userParents == null)
        {
            throw new Exception("User not part of a family");
        }
        
        var mother = userParents.Mother;
        var father = userParents.Father;

        var siblingRelations = _context.FamilyRelations
            .Where(x => x.Mother == mother || x.Father == father)
            .Select(x => RelationToDTO(x))
            .ToList();
        
        var siblings = new HashSet<string>(); 
        
        foreach (var relation in siblingRelations)
        {
            var sibling = _context.Users.FirstOrDefault(x => x.Id == relation.UserId);

            if (sibling != null)
            {
                siblings.Add(sibling.Username);
            }
        }

        return Ok(siblings);
    }

    [HttpGet("father")]
    [AllowAnonymous]
    public ActionResult<HashSet<string>> GetFathers(int userId)
    {
        var userFather = _context.FamilyRelations.FirstOrDefault(x => x.UserId == userId);

        if (userFather == null)
        {
            throw new Exception("User not part of a family");
        }
        
        var father = userFather.Father;
        var fathers = new HashSet<string>();
        if (father == string.Empty)
        {
            return Ok(fathers);
        }
        
        fathers.Add(father);
        while (true)
        {
            var fatherUser = _context.Users.FirstOrDefault(x => x.Username == father);
            
            if (fatherUser == null)
            {
                return Ok(fathers);
            }

            var parents = _context.FamilyRelations.FirstOrDefault(x => x.UserId == fatherUser.Id);

            if (parents == null)
            {
                return Ok(fathers);
            }

            if (parents.Father == string.Empty)
            {
                return Ok(fathers);
            }

            father = parents.Father;
            fathers.Add(father);
        }
    }
    
    [HttpGet("mother")]
    [AllowAnonymous]
    public ActionResult<HashSet<string>> GetMothers(int userId)
    {
        var userMother = _context.FamilyRelations.FirstOrDefault(x => x.UserId == userId);

        if (userMother == null)
        {
            throw new Exception("User not part of a family");
        }
        
        var mother = userMother.Mother;
        var mothers = new HashSet<string>();
        if (mother == string.Empty)
        {
            return Ok(mothers);
        }
        
        mothers.Add(mother);
        while (true)
        {
            var motherUser = _context.Users.FirstOrDefault(x => x.Username == mother);
            
            if (motherUser == null)
            {
                return Ok(mothers);
            }

            var parents = _context.FamilyRelations.FirstOrDefault(x => x.UserId == motherUser.Id);

            if (parents == null)
            {
                return Ok(mothers);
            }

            if (parents.Mother == string.Empty)
            {
                return Ok(mothers);
            }

            mother = parents.Mother;
            mothers.Add(mother);
        }
    }
}