using System.Runtime.CompilerServices;
using System.Runtime.ConstrainedExecution;
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
    public virtual DbSet<WorkflowStep> WorkflowSteps { get; set; } = null!;
    public virtual DbSet<Rule> Rules { get; set; } = null!;
    public virtual DbSet<Message> Messages { get; set; } = null!;
    public virtual DbSet<MessageStep> MessageSteps { get; set; } = null!;
    public virtual DbSet<Partner> Partners { get; set; } = null!;
    public virtual DbSet<CommunicationChannel> CommunicationChannels { get; set; } = null!;
    public virtual DbSet<Certificate> Certificates { get; set; } = null!;
    
    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<Certificate>()
            .HasKey(c => c.Id);

        modelBuilder.Entity<Message>()
            .HasOne(m => m.User)
            .WithMany(u => u.Messages)
            .HasForeignKey(m => m.UserId);
        
        modelBuilder.Entity<Message>()
            .HasOne(m => m.Rule)
            .WithMany(r => r.Messages)
            .HasForeignKey(m => m.RuleId);
        
        modelBuilder.Entity<MessageStep>()
            .HasOne(m => m.Message)
            .WithMany(m => m.MessageSteps)
            .HasForeignKey(m => m.MessageId);

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

        modelBuilder.Entity<WorkflowStep>()
            .HasOne(ws => ws.Workflow)
            .WithMany(w => w.WorkflowSteps)
            .HasForeignKey(ws => ws.WorkflowId);

    }
}