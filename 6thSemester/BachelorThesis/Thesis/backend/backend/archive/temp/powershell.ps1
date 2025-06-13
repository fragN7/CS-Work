param (
    [Parameter(Mandatory=$true)]
    [string]$FilePath
)

# Check if file exists
if (-Not (Test-Path $FilePath)) {
    Write-Error "File not found: $FilePath"
    exit 1
}

# Read the file content
$content = Get-Content -Path $FilePath -Raw

# Remove all '*' characters
$updatedContent = $content -replace '\*', ''

# Overwrite the file with updated content
Set-Content -Path $FilePath -Value $updatedContent

Write-Output "Removed all '*' characters from file: $FilePath"
