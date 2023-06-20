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

    private static ProjectDTO ProjectToDTO(Project project) =>
        new ProjectDTO
        {
            Id = project.Id,
            Name = project.Name,
            Description = project.Name,
            Members = project.Members,
            ProjectManagerId = project.ProjectManagerId
        };

    [HttpGet]
    [AllowAnonymous]
    public ActionResult<List<ProjectDTO>> GetAllProjects()
    {
        return _context.Projects
            .Select(x => ProjectToDTO(x))
            .ToList();
    }

    [HttpGet("{name}")]
    [AllowAnonymous]
    public ActionResult<List<ProjectDTO>> GetProjectsUser(string name)
    {
        return _context.Projects
            .Where(x => x.Members.Contains(name))
            .Select(x => ProjectToDTO(x))
            .ToList();
    }

    [HttpPost("assign/{name}")]
    [AllowAnonymous]
    public async Task<ActionResult> AssignDevelopers(string name, List<int> projectsIds)
    {
        var developer = await _context.SoftwareDevelopers
            .FirstOrDefaultAsync(x => x.Name == name);

        if (developer == null)
        {
            throw new Exception("Developer doesn't exist");
        }
        
        foreach (var projectId in projectsIds)
        {
            var actualProject = await _context.Projects.FirstOrDefaultAsync(x => x.Id == projectId);
            if (actualProject == null)
            {
                throw new Exception("Project doesn't exist");
            }
            
            actualProject.ProjectManagerId = developer.Id;
            actualProject.ProjectManager = developer;
        }
        
        await _context.SaveChangesAsync();

        return NoContent();
    }
}