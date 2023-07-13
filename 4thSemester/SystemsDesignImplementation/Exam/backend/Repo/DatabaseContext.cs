using backend.Model;
using Microsoft.EntityFrameworkCore;

namespace backend.Repo;

public class DatabaseContext : DbContext
{
    public DatabaseContext() { }
    public DatabaseContext(DbContextOptions opt) : base(opt) { }

    public virtual DbSet<Game> Games { get; set; } = null!;

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<Game>()
            .HasKey(p => p.GameId);
    }
}