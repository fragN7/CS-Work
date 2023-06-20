using backend.Model;
using Microsoft.EntityFrameworkCore;

namespace backend.Repo;

public class DatabaseContext : DbContext
{
    public DatabaseContext() { }
    public DatabaseContext(DbContextOptions opt) : base(opt) { }

    public virtual DbSet<SoftwareDeveloper> SoftwareDevelopers { get; set; } = null!;
    public virtual DbSet<Project> Projects { get; set; } = null!;

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<Project>()
            .HasOne<SoftwareDeveloper>(p => p.ProjectManager)
            .WithMany(d => d.Projects)
            .HasForeignKey(p => p.ProjectManagerId);

        modelBuilder.Entity<SoftwareDeveloper>()
            .HasKey(d => d.Id);
    }

}