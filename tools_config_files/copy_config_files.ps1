# PowerShell script to copy all MCP configuration files
# This doesn't require administrator privileges

# Change to the tools_config_files directory
Set-Location "C:\Users\hyper\fwber\tools_config_files"

# List of configuration files and their target names
$configFiles = @{
    "claude.json" = "C:\Users\hyper\.claude.json"
    "cursor_mcp.json" = "C:\Users\hyper\.cursor\mcp.json"
    "cline_mcp_settings.json" = "C:\Users\hyper\AppData\Roaming\Cursor\User\globalStorage\saoudrizwan.claude-dev\settings\cline_mcp_settings.json"
    "codex_config.toml" = "C:\Users\hyper\.codex\config.toml"
    "gemini_settings.json" = "C:\Users\hyper\.gemini\settings.json"
    "copilot_mcp_config.json" = "C:\Users\hyper\.copilot\mcp-config.json"
    "grok_settings.json" = "C:\Users\hyper\.grok\settings.json"
    "webstorm_llm_mcpServers.xml" = "C:\Users\hyper\AppData\Roaming\JetBrains\WebStorm2025.3\options\llm.mcpServers.xml"
    "claude_desktop_config.json" = "C:\Users\hyper\AppData\Roaming\Claude\claude_desktop_config.json"
    "github_copilot_intellij_mcp.json" = "C:\Users\hyper\AppData\Local\github-copilot\intellij\mcp.json"
    "grok_user_settings.json" = "C:\Users\hyper\.grok\user-settings.json"
    "serena_config.yml" = "C:\Users\hyper\.serena\serena_config.yml"
    "code_config.toml" = "C:\Users\hyper\.code\config.toml"
    "gemini_mcp_config.json" = "C:\Users\hyper\.gemini\mcp-config.json"
    "lingma_mcp.json" = "C:\Users\hyper\.lingma\lingma_mcp.json"
    "lmstudio_mcp.json" = "C:\Users\hyper\.lmstudio\mcp.json"
    "qwen_settings.json" = "C:\Users\hyper\.qwen\settings.json"
    "witsy_settings.json" = "C:\Users\hyper\AppData\Roaming\Witsy\settings.json"
    "kilo_code_mcp_settings.json" = "C:\Users\hyper\AppData\Roaming\Cursor\User\globalStorage\kilocode.kilo-code\settings\mcp_settings.json"
}

Write-Host "Copying MCP configuration files..." -ForegroundColor Green

foreach ($linkName in $configFiles.Keys) {
    $targetPath = $configFiles[$linkName]
    
    # Check if target file exists
    if (Test-Path $targetPath) {
        try {
            # Copy the file
            Copy-Item $targetPath $linkName -Force
            Write-Host "Copied: $linkName <- $targetPath" -ForegroundColor Green
        }
        catch {
            Write-Host "Failed to copy $linkName : $($_.Exception.Message)" -ForegroundColor Red
        }
    }
    else {
        Write-Host "Target file not found: $targetPath" -ForegroundColor Red
    }
}

Write-Host "`nFile copying completed!" -ForegroundColor Green
Write-Host "You can now add these files to git tracking." -ForegroundColor Cyan
