using backend.Model;
using Microsoft.EntityFrameworkCore;

namespace backend.Repo;

public class DatabaseContext : DbContext
{
    public DatabaseContext() { }
    public DatabaseContext(DbContextOptions opt) : base(opt) { }

    public virtual DbSet<Link> Links { get; set; } = null!;
    public virtual DbSet<City> Cities { get; set; } = null!;

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<Link>()
            .HasOne<City>(l => l.FirstCity)
            .WithMany(c => c.FirstLinks)
            .HasForeignKey(l => l.FirstCityId)
            .OnDelete(DeleteBehavior.Restrict);
        
        modelBuilder.Entity<Link>()
            .HasOne<City>(l => l.SecondCity)
            .WithMany(c => c.SecondLinks)
            .HasForeignKey(l => l.SecondCityId)
            .OnDelete(DeleteBehavior.Restrict);

        modelBuilder.Entity<City>()
            .HasKey(c => c.Id);

    }
}