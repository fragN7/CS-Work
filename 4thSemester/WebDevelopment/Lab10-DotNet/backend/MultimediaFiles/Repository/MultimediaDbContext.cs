using Lab10_Dotnet.Data;
using Microsoft.EntityFrameworkCore;

namespace Lab10_Dotnet.Repository;

public class MultimediaDbContext : DbContext
{
    public MultimediaDbContext()
    {
    }

    public MultimediaDbContext(DbContextOptions<MultimediaDbContext> options) : base(options)
    {
        
    }

    public virtual DbSet<Multimedia> MultimediaFiles { get; set; } = null!;
    public virtual DbSet<User> Users { get; set; } = null!;

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<Multimedia>()
            .HasKey(m => m.ID);
        
        modelBuilder.Entity<User>()
            .HasKey(u => u.ID);
    }
}