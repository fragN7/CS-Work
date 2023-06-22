using backend.Model;
using Microsoft.EntityFrameworkCore;

namespace backend.Repo;

public class DatabaseContext : DbContext
{
    public DatabaseContext() { }
    public DatabaseContext(DbContextOptions opt) : base(opt) { }
    
    public virtual DbSet<User> Users { get; set; } = null!;
    public virtual DbSet<CHANGEENTITY> CHANGETHIS { get; set; } = null!;

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<CHANGEENTITY>()
            .HasOne<User>(x => x.User)
            .WithMany(u => u.CHANGEENTITY)
            .HasForeignKey(x => x.UserId);
        
        modelBuilder.Entity<User>()
            .HasKey(u => u.Id);

    }
}