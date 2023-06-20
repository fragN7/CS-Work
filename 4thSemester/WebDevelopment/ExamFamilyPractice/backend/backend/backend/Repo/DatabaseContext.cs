using backend.Model;
using Microsoft.EntityFrameworkCore;

namespace backend.Repo;

public class DatabaseContext : DbContext
{
    public DatabaseContext() { }
    public DatabaseContext(DbContextOptions opt) : base(opt) { }

    public virtual DbSet<User> Users { get; set; } = null!;
    public virtual DbSet<FamilyRelation> FamilyRelations { get; set; } = null!;

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<FamilyRelation>()
            .HasOne<User>(f => f.User)
            .WithMany(u => u.FamilyRelation)
            .HasForeignKey(f => f.UserId);

        modelBuilder.Entity<User>()
            .HasKey(u => u.Id);

    }
}