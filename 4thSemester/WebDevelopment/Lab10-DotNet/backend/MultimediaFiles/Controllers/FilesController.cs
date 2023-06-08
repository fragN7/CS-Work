using Lab10_Dotnet.Data;
using Lab10_Dotnet.Repository;
using Lab10_Dotnet.Validation;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace Lab10_Dotnet.Controllers;

[ApiController]
[Route("api/[controller]")]
public class FilesController : ControllerBase
{
    private readonly MultimediaDbContext context;
    private readonly Validator validator;

    public FilesController(MultimediaDbContext context, Validator validator)
    {
        this.context = context;
        this.validator = validator;
    }

    [HttpGet("genre/{genre}")]
    [Authorize]
    public async Task<ActionResult<IEnumerable<Multimedia>>> GetFiles(string genre)
    {
        List<Multimedia>? files = null;

        if (genre != "all")
        {
            files = await this.context.MultimediaFiles.Where(f => f.Genre == genre).ToListAsync();
        }
        else
        {
            files = await this.context.MultimediaFiles.ToListAsync();
        }
        
        return Ok(files);
    }
    
    [HttpGet("{id}")]
    [Authorize]
    public async Task<ActionResult<Multimedia>> GetFile(int id)
    {
        var file = await this.context.MultimediaFiles.FindAsync(id);
        return Ok(file);
    }

    [HttpPost]
    [Authorize]
    public async Task<ActionResult<MultimediaDTO>> AddFile(Multimedia file)
    {
        var newFile = new Multimedia
        {
            Title = file.Title,
            Format = file.Format,
            Genre = file.Genre,
            Path = file.Path
        };

        var result = this.validator.validate(file);
        if (result != string.Empty)
        {
            throw new Exception(result);
        }

        this.context.MultimediaFiles.Add(newFile);
        await this.context.SaveChangesAsync();

        return CreatedAtAction(nameof(GetFile), new { id = newFile.ID }, newFile);
    }

    [HttpPut("{id}")]
    [Authorize]
    public async Task<ActionResult<Multimedia>> UpdateFile(int id, Multimedia file)
    {
        var fileToUpdate = await this.context.MultimediaFiles.FindAsync(id);
        if (fileToUpdate == null)
        {
            throw new Exception("File doesn't exist");
        }

        fileToUpdate.Title = file.Title;
        fileToUpdate.Format = file.Format;
        fileToUpdate.Genre = file.Genre;
        fileToUpdate.Path = file.Path;

        var result = this.validator.validate(file);
        if (result != string.Empty)
        {
            throw new Exception(result);
        }

        await this.context.SaveChangesAsync();
        return Ok(fileToUpdate);
    }

    [HttpDelete("{id}")]
    [Authorize]
    public async Task<ActionResult> DeleteFile(int id)
    {
        var file = await this.context.MultimediaFiles.FindAsync(id);

        if (file is null)
        {
            throw new Exception("File not found");
        }

        this.context.MultimediaFiles.Remove(file);
        await this.context.SaveChangesAsync();

        return NoContent();
    }
}