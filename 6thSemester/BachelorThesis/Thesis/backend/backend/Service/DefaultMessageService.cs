using System.Data;
using System.Text.Json;
using backend.Model;
using backend.Repository;
using Microsoft.EntityFrameworkCore;

namespace backend.Service;

public class DefaultMessageService : BackgroundService
{
    private readonly ILogger<FolderWatchService> _logger;
    private readonly IServiceProvider _services;
    private readonly IHttpClientFactory _httpClientFactory;

    public DefaultMessageService(ILogger<FolderWatchService> logger, IServiceProvider services, IHttpClientFactory httpClientFactory)
    {
        _logger = logger;
        _services = services;
        _httpClientFactory = httpClientFactory;
    }

    protected override async Task ExecuteAsync(CancellationToken stoppingToken)
    {
        var client = _httpClientFactory.CreateClient("InsecureClient");
        var token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiJhbGVuIiwianRpIjoiNDNlYzU3ODQtYWUyZS00N2QwLWIwYzItYTg2ZGEwY2VkYjBhIiwiaWQiOiI3YmZjNjdlNy1iZjc5LTQwNmYtOTNhMC1kMmNiNmRiNDJhNDkiLCJ1c2VybmFtZSI6ImFsZW4iLCJleHAiOjE3NzkzOTM5MDJ9.pjcLjSiidLO6mcg5amWs06rp6IrHEbhWTK0Jh5MB7Ig";
        client.DefaultRequestHeaders.Authorization =
            new System.Net.Http.Headers.AuthenticationHeaderValue("Bearer", token);
        
        while (!stoppingToken.IsCancellationRequested)
        {
            try
            {
                using var scope = _services.CreateScope();
                var dbContext = scope.ServiceProvider.GetRequiredService<DatabaseContext>();

                var messageSteps = await dbContext.MessageSteps
                    .Where(ms => ms.Message.Rule.TimeStamp == "DEFAULTS")
                    .Include(ms => ms.Message).ThenInclude(message => message.Rule)
                    .OrderBy(ms => ms.StartedTime)
                    .ToListAsync(cancellationToken: stoppingToken);
                
                for (int i = 0; i < messageSteps.Count; i++)
                {
                    var step = messageSteps[i];
                    var now = DateTime.UtcNow;
                    var formatted = now.ToString("yyyyMMddHHmmss");
                    var fileName = step.Message.Rule.Sender + "_" + step.Message.Rule.ObjectType + "_" + step.Message.Rule.Receiver +
                                   (step.StepName is "CONVERT" or "SHELL" ? "TF" : "") + "." +
                                   formatted + "_" + step.MessageId;
                    
                    var form = new MultipartFormDataContent();
                    form.Add(new StringContent(step.FilePath), "filePath");
                    form.Add(new StringContent(Path.GetFileName(fileName)), "fileName");
                    form.Add(new StringContent(step.StepName), "step");


                    var url = $"https://localhost:7003/api/Message/message/process/step/{step.Id}";

                    try
                    {
                        var response = await client.PutAsync(url, form, stoppingToken);
                        if (response.IsSuccessStatusCode)
                        {
                            var responseContent = await response.Content.ReadAsStringAsync(stoppingToken);
                            var updatedStep = JsonSerializer.Deserialize<MessageStep>(responseContent, new JsonSerializerOptions
                            {
                                PropertyNameCaseInsensitive = true
                            });
                            
                            if (updatedStep != null && i + 1 < messageSteps.Count)
                            {
                                messageSteps[i + 1].FilePath = updatedStep.FilePath;
                            }
                        }
                        else
                        {
                            var rule = await dbContext.Rules
                                .FirstOrDefaultAsync(r => r.Id == step.Message.RuleId, stoppingToken);
                                    
                            rule!.TimeStamp = "PRE-DEFAULT";
                            await dbContext.SaveChangesAsync(stoppingToken);
                            return;
                        }
                    }
                    catch (Exception ex)
                    {
                        _logger.LogError(ex, $"Error processing {step.StepName} step for message {step.MessageId}");
                        var rule = await dbContext.Rules
                            .FirstOrDefaultAsync(r => r.Id == step.Message.RuleId, stoppingToken);
                                    
                        rule!.TimeStamp = "PRE-DEFAULT";
                        await dbContext.SaveChangesAsync(stoppingToken);
                        return;
                    }
                } 
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error checking messages.");
            }

            await Task.Delay(TimeSpan.FromSeconds(5), stoppingToken); 
        }

    }

}