# PowerShell script to deploy MCP configuration files from tools_config_files to their target locations
# This deploys the working configurations to the proper directories

# Change to the tools_config_files directory
Set-Location "C:\Users\hyper\fwber\tools_config_files"

# List of configuration files and their target locations
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
    "lingma_mcp.json" = "C:\Users\hyper\.lingma\lingma_mcp.json"
    "lmstudio_mcp.json" = "C:\Users\hyper\.lmstudio\mcp.json"
    "qwen_settings.json" = "C:\Users\hyper\.qwen\settings.json"
    "witsy_settings.json" = "C:\Users\hyper\AppData\Roaming\Witsy\settings.json"
    "kilo_code_mcp_settings.json" = "C:\Users\hyper\AppData\Roaming\Cursor\User\globalStorage\kilocode.kilo-code\settings\mcp_settings.json"
}

Write-Host "Deploying MCP configuration files..." -ForegroundColor Green

foreach ($sourceFile in $configFiles.Keys) {
    $targetPath = $configFiles[$sourceFile]
    
    # Check if source file exists
    if (Test-Path $sourceFile) {
        try {
            # Create target directory if it doesn't exist
            $targetDir = Split-Path $targetPath -Parent
            if (!(Test-Path $targetDir)) {
                New-Item -ItemType Directory -Path $targetDir -Force | Out-Null
                Write-Host "Created directory: $targetDir" -ForegroundColor Yellow
            }
            
            # Copy the file
            Copy-Item $sourceFile $targetPath -Force
            Write-Host "Deployed: $sourceFile -> $targetPath" -ForegroundColor Green
        }
        catch {
            Write-Host "Failed to deploy $sourceFile : $($_.Exception.Message)" -ForegroundColor Red
        }
    }
    else {
        Write-Host "Source file not found: $sourceFile" -ForegroundColor Red
    }
}

Write-Host "`nConfiguration deployment completed!" -ForegroundColor Green
Write-Host "All working config files have been deployed to their target locations." -ForegroundColor Cyan
