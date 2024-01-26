using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Server.Model;
using Server.Repo;

namespace Server.Controllers;

[ApiController]
public class ChessController : ControllerBase
{
    private readonly DatabaseContext _context;
    
    public ChessController(DatabaseContext context)
    {
        _context = context;
    }

    [HttpGet("records/all")]
    [AllowAnonymous]
    public ActionResult GetRecords()
    {
        var records = _context.Records.ToList();
        return Ok(records);
    }
    
    [HttpGet("record/{id}")]
    [AllowAnonymous]
    public ActionResult GetRecord(int id)
    {
        var record = _context.Records.FirstOrDefault(x => x.Id == id);
        return Ok(record);
    }

    [HttpPost("records/add")]
    [AllowAnonymous]
    public Task<ActionResult> AddRecord([FromBody] ChessRecord record)
    {
        _context.AddAsync(record);
        _context.SaveChangesAsync();

        return Task.FromResult<ActionResult>(Ok(record));
    }
    
    [HttpPut("records/update/{id}")]
    [AllowAnonymous]
    public ActionResult UpdateRecord(int id, [FromBody] ChessRecord updatedRecord)
    {
        var existingRecord = _context.Records.FirstOrDefault(x => x.Id == id);

        if (existingRecord == null)
        {
            throw new Exception("Record doesn't exist");
        }
        
        existingRecord.Rating = updatedRecord.Rating;
        existingRecord.OpponentName = updatedRecord.OpponentName;
        existingRecord.OpponentRating = updatedRecord.OpponentRating;
        existingRecord.OpponentProfile = updatedRecord.OpponentProfile;
        existingRecord.GameOutcome = updatedRecord.GameOutcome;
        existingRecord.GameOpening = updatedRecord.GameOpening;
        existingRecord.GameTag = updatedRecord.GameTag;
        existingRecord.Notes = updatedRecord.Notes;
        
        _context.SaveChangesAsync();

        return Ok(existingRecord);
    }
    
    [HttpDelete("records/remove/{id}")]
    [AllowAnonymous]
    public ActionResult DeleteRecord(int id)
    {
        var existingRecord = _context.Records.FirstOrDefault(x => x.Id == id);

        if (existingRecord == null)
        {
            throw new Exception("Record doesn't exist");
        }

        _context.Records.Remove(existingRecord);
        _context.SaveChanges();
        
        return Ok(existingRecord);
    }
}