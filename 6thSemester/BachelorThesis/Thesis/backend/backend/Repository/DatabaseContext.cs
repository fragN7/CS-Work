using System.Runtime.CompilerServices;
using backend.Model;
using Microsoft.EntityFrameworkCore;

namespace backend.Repository;

public class DatabaseContext : DbContext
{
    public DatabaseContext()
    {
    }

    public DatabaseContext(DbContextOptions<DatabaseContext> options) : base(options)
    {
        
    }

    public virtual DbSet<User> Users { get; set; } = null!;
    public virtual DbSet<Workflow> Workflows { get; set; } = null!;
    public virtual DbSet<Rule> Rules { get; set; } = null!;
    public virtual DbSet<Message> Messages { get; set; } = null!;
    public virtual DbSet<Partner> Partners { get; set; } = null!;
    public virtual DbSet<CommunicationChannel> CommunicationChannels { get; set; } = null!;
    
    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<User>()
            .HasKey(u => u.Id);

        modelBuilder.Entity<Message>()
            .HasOne(m => m.Rule)
            .WithMany(r => r.Messages)
            .HasForeignKey(m => m.RuleId);

        modelBuilder.Entity<Rule>()
            .HasOne(r => r.CommunicationChannel)
            .WithMany(c => c.Rules)
            .HasForeignKey(r => r.CommunicationChannelId);

        modelBuilder.Entity<Rule>()
            .HasOne(r => r.Workflow)
            .WithMany(w => w.Rules)
            .HasForeignKey(r => r.WorkflowId);

        modelBuilder.Entity<Partner>()
            .HasOne(p => p.CommunicationChannel)
            .WithOne(c => c.Partner)
            .HasForeignKey<CommunicationChannel>(p => p.PartnerId);
    }
}