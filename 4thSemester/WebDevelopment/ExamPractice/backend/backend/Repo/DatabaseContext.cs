using backend.Model;
using Microsoft.EntityFrameworkCore;

namespace backend.Repo;

public class DatabaseContext : DbContext
{
    public DatabaseContext() { }
    public DatabaseContext(DbContextOptions opt) : base(opt) { }

    public virtual DbSet<Person> Persons { get; set; } = null!;
    public virtual DbSet<Book> Books { get; set; } = null!;
    public virtual DbSet<Article> Articles { get; set; } = null!;

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<Book>()
            .HasOne<Person>(b => b.Author)
            .WithMany(p => p.Books)
            .HasForeignKey(b => b.AuthorId);

        modelBuilder.Entity<Article>()
            .HasOne<Person>(a => a.Author)
            .WithMany(p => p.Articles)
            .HasForeignKey(a => a.AuthorId);

        modelBuilder.Entity<Person>()
            .HasKey(p => p.Id);
    }
}