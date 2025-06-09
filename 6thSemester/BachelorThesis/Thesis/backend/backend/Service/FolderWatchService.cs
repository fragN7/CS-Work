using backend.Model;
using backend.Repository;
using Microsoft.EntityFrameworkCore;

namespace backend.Service;

public class FolderWatchService : BackgroundService
{
    private readonly ILogger<FolderWatchService> _logger;
    private readonly string _outFolderPath;
    private readonly string _inFolderPath;
    private readonly IServiceProvider _services;
    private readonly IHttpClientFactory _httpClientFactory;

    public FolderWatchService(ILogger<FolderWatchService> logger, IServiceProvider services, IHttpClientFactory httpClientFactory)
    {
        _logger = logger;
        _outFolderPath = Path.Combine(Directory.GetCurrentDirectory(), "archive", "out");
        _inFolderPath = Path.Combine(Directory.GetCurrentDirectory(), "archive", "in");
        _services = services;
        _httpClientFactory = httpClientFactory;
    }

    private async Task TryDeleteFileAsync(string filePath)
    {
        const int maxRetries = 5;
        const int delayMs = 200;

        for (int i = 0; i < maxRetries; i++)
        {
            try
            {
                if (File.Exists(filePath))
                {
                    var attributes = File.GetAttributes(filePath);
                    if ((attributes & FileAttributes.Directory) == FileAttributes.Directory)
                    {
                        _logger.LogWarning("Attempted to delete a directory instead of a file: {FilePath}", filePath);
                        return;
                    }
                    
                    File.Delete(filePath);
                    _logger.LogInformation("Deleted uploaded file: {FilePath}", filePath);
                }
                return;
            }
            catch (IOException ex)
            {
                _logger.LogWarning(ex, "Attempt {Attempt} failed to delete file: {FilePath}", i + 1, filePath);
                await Task.Delay(delayMs);
            }
        }
        _logger.LogError("Failed to delete file after {Retries} attempts: {FilePath}", maxRetries, filePath);
    }

    
    private async Task SendOutMessage(string filePath, Certificate certificate, Rule rule, CancellationToken cancellationToken)
    {
        using var fileStream = new FileStream(filePath, FileMode.Open, FileAccess.Read);
        using var streamContent = new StreamContent(fileStream); // explicitly dispose this
        using var content = new MultipartFormDataContent();

        content.Add(streamContent, "file", Path.GetFileName(filePath));
        content.Add(new StringContent(rule.Id.ToString()), "ruleId");

        var client = _httpClientFactory.CreateClient("InsecureClient");
        var token = certificate.Password;
        client.DefaultRequestHeaders.Authorization =
            new System.Net.Http.Headers.AuthenticationHeaderValue("Bearer", token);

        var response = await client.PostAsync($"https://{certificate.HostName}:{certificate.Port}/api/Message/message/store", content, cancellationToken);

        if (response.IsSuccessStatusCode)
        {
            var responseContent = await response.Content.ReadAsStringAsync(cancellationToken);
            _logger.LogInformation("Successfully uploaded file. Response: {Response}", responseContent);

            try
            {
                _logger.LogInformation("Deleted uploaded file: {FilePath}", filePath);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Failed to delete file after upload: {FilePath}", filePath);
            }
        }
        else
        {
            var error = await response.Content.ReadAsStringAsync(cancellationToken);
            _logger.LogWarning("Upload failed: {StatusCode}, {Error}", response.StatusCode, error);
        }
    }
    
    private async Task SendInMessage(string filePath, Certificate certificate, Rule rule, CancellationToken cancellationToken)
    {
        await using var fileStream = new FileStream(filePath, FileMode.Open, FileAccess.Read);
        using var streamContent = new StreamContent(fileStream); // explicitly dispose this
        using var content = new MultipartFormDataContent();

        content.Add(streamContent, "file", Path.GetFileName(filePath));
        content.Add(new StringContent(rule.Id.ToString()), "ruleId");

        var client = _httpClientFactory.CreateClient("InsecureClient");
        var token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiJhbGVuIiwianRpIjoiNDNlYzU3ODQtYWUyZS00N2QwLWIwYzItYTg2ZGEwY2VkYjBhIiwiaWQiOiI3YmZjNjdlNy1iZjc5LTQwNmYtOTNhMC1kMmNiNmRiNDJhNDkiLCJ1c2VybmFtZSI6ImFsZW4iLCJleHAiOjE3NzkzOTM5MDJ9.pjcLjSiidLO6mcg5amWs06rp6IrHEbhWTK0Jh5MB7Ig";
        client.DefaultRequestHeaders.Authorization =
            new System.Net.Http.Headers.AuthenticationHeaderValue("Bearer", token);

        var response = await client.PostAsync($"https://localhost:7003/api/Message/message/store", content, cancellationToken);

        if (response.IsSuccessStatusCode)
        {
            var responseContent = await response.Content.ReadAsStringAsync(cancellationToken);
            _logger.LogInformation("Successfully uploaded file. Response: {Response}", responseContent);

            try
            {
                _logger.LogInformation("Deleted uploaded file: {FilePath}", filePath);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Failed to delete file after upload: {FilePath}", filePath);
            }
        }
        else
        {
            var error = await response.Content.ReadAsStringAsync(cancellationToken);
            _logger.LogWarning("Upload failed: {StatusCode}, {Error}", response.StatusCode, error);
        }
    }

    
    private async Task ProcessFileAsync(string filePath, CancellationToken cancellationToken, string folder)
    {
        try
        {
            
            using var scope = _services.CreateScope();
            var dbContext = scope.ServiceProvider.GetRequiredService<DatabaseContext>();
            
            var content = await File.ReadAllTextAsync(filePath, cancellationToken);
            var sender = "WARNING";
            var receiver = "WARNING";
            var objectType = "WARNING";

            if (content.StartsWith("ISA"))
            {
                // ANSI X12
                var segments = content.Split('*');
                if (segments.Length >= 9)
                {
                    sender = segments[6];
                    receiver = segments[8];
                }
                
                Console.WriteLine(sender, receiver);

                segments = content.Split('~', StringSplitOptions.RemoveEmptyEntries);
                var stSegment = segments.FirstOrDefault(s => s.TrimStart().StartsWith("ST"));

                if (stSegment != null)
                {
                    var stFields = stSegment.Split('*');
                    if (stFields.Length >= 2)
                    {
                        objectType = stFields[1]; // e.g., 830
                    }
                }
            }
            else if (content.StartsWith("UNA") || content.StartsWith("UNB"))
            {
                // EDIFACT
                var segments = content.Split('\'', StringSplitOptions.RemoveEmptyEntries);

                var unbSegment = segments.FirstOrDefault(s => s.TrimStart().StartsWith("UNB+"));
                if (unbSegment != null)
                {
                    var unbFields = unbSegment.Split('+');
                    if (unbFields.Length >= 4)
                    {
                        sender = unbFields[2];
                        receiver = unbFields[3];
                    }
                }

                var unhSegment = segments.FirstOrDefault(s => s.TrimStart().StartsWith("UNH+"));
                if (unhSegment != null)
                {
                    var unhFields = unhSegment.Split('+');
                    if (unhFields.Length >= 3)
                    {
                        objectType = unhFields[2];
                    }
                }

            }

            var certificate = await dbContext.Certificates
                .FirstOrDefaultAsync(c => c.Sender == sender && c.Receiver == receiver, cancellationToken: cancellationToken);

            if (certificate == null)
            {
                certificate = await dbContext.Certificates
                    .FirstOrDefaultAsync(c => c.Sender == "WARNING", cancellationToken: cancellationToken);
            }
            
            var rule = await dbContext.Rules
                .FirstOrDefaultAsync(r => r.Sender == sender && r.Receiver == receiver && r.ObjectType == objectType, cancellationToken: cancellationToken);

            if (rule == null)
            {
                rule = await dbContext.Rules
                    .FirstOrDefaultAsync(c => c.Sender == "WARNING", cancellationToken: cancellationToken);
            }

            if (folder == "out")
            {
                await this.SendOutMessage(filePath, certificate!, rule!, cancellationToken: cancellationToken);
                await TryDeleteFileAsync(filePath);
            }
            else
            {
                await this.SendInMessage(filePath, certificate!, rule!, cancellationToken: cancellationToken);
                await TryDeleteFileAsync(filePath);
            }

            _logger.LogInformation("Certificate: {certificate.sender}, Rule: {rule.receiver}",
                certificate.Sender, rule.ObjectType);
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error processing file {FileName}", Path.GetFileName(filePath));
        }
    }

    
    protected override async Task ExecuteAsync(CancellationToken stoppingToken)
    {
        _logger.LogInformation("Folder watcher started.");

        while (!stoppingToken.IsCancellationRequested)
        {
            try
            {
                var files = Directory.GetFiles(_outFolderPath);
                foreach (var file in files)
                {
                    await ProcessFileAsync(file, stoppingToken, "out");
                }
                
                var inFiles = Directory.GetFiles(_inFolderPath);
                foreach (var file in inFiles)
                {
                    await ProcessFileAsync(file, stoppingToken, "in");
                }
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error watching folders.");
            }

            await Task.Delay(10000, stoppingToken); 
        }

        _logger.LogInformation("Folder watcher stopped.");
    }
}