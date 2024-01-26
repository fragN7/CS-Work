using Microsoft.EntityFrameworkCore;
using Server.Model;

namespace Server.Repo;

public class DatabaseContext : DbContext
{
    public DatabaseContext() { }
    public DatabaseContext(DbContextOptions opt) : base(opt) { }
    
    public virtual DbSet<ChessRecord> Records { get; set; } = null!;
    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<ChessRecord>()
            .HasKey(u => u.Id);
    }
}