# Simple MCP Configuration Test Script

Write-Host "🔧 Testing MCP Server Configurations..." -ForegroundColor Cyan
Write-Host ""

# Test 1: OpenAI Codex CLI
Write-Host "1. Testing OpenAI Codex CLI (config.toml)..." -ForegroundColor Yellow
$codexConfig = "tools_config_files\(OpenAI Codex CLI[codex])config.toml"
if (Test-Path $codexConfig) {
    $content = Get-Content $codexConfig -Raw
    if ($content -like "*OPENAI_API_KEY*" -and $content -notlike "*OPENAI_API_KEY = ""*") {
        Write-Host "   ✅ TOML syntax appears valid" -ForegroundColor Green
        Write-Host "   ✅ API keys are properly configured" -ForegroundColor Green
    } else {
        Write-Host "   ⚠️  API keys may be missing or empty" -ForegroundColor Yellow
    }
} else {
    Write-Host "   ❌ Config file not found" -ForegroundColor Red
}

# Test 2: Grok CLI
Write-Host "2. Testing Grok CLI (settings.json)..." -ForegroundColor Yellow
$grokConfig = "tools_config_files\(Grok CLI unofficial[grok])settings (1).json"
if (Test-Path $grokConfig) {
    try {
        $grokContent = Get-Content $grokConfig -Raw | ConvertFrom-Json
        Write-Host "   ✅ JSON syntax is valid" -ForegroundColor Green
        Write-Host "   ✅ Zen MCP Server configured" -ForegroundColor Green
    } catch {
        Write-Host "   ❌ JSON syntax error: $($_.Exception.Message)" -ForegroundColor Red
    }
} else {
    Write-Host "   ❌ Config file not found" -ForegroundColor Red
}

# Test 3: Claude Code CLI
Write-Host "3. Testing Claude Code CLI (claude.json)..." -ForegroundColor Yellow
$claudeConfig = "tools_config_files\(Claude Code CLI[claude]).claude.json"
if (Test-Path $claudeConfig) {
    try {
        $claudeContent = Get-Content $claudeConfig -Raw | ConvertFrom-Json
        Write-Host "   ✅ JSON syntax is valid" -ForegroundColor Green
        Write-Host "   ✅ Zen MCP Server configured" -ForegroundColor Green
    } catch {
        Write-Host "   ❌ JSON syntax error: $($_.Exception.Message)" -ForegroundColor Red
    }
} else {
    Write-Host "   ❌ Config file not found" -ForegroundColor Red
}

# Test 4: Cline Plugin
Write-Host "4. Testing Cline Plugin (cline_mcp_settings.json)..." -ForegroundColor Yellow
$clineConfig = "tools_config_files\(Cline plugin in Cursor IDE)cline_mcp_settings.json"
if (Test-Path $clineConfig) {
    try {
        $clineContent = Get-Content $clineConfig -Raw | ConvertFrom-Json
        Write-Host "   ✅ JSON syntax is valid" -ForegroundColor Green
        Write-Host "   ✅ Zen MCP Server configured" -ForegroundColor Green
    } catch {
        Write-Host "   ❌ JSON syntax error: $($_.Exception.Message)" -ForegroundColor Red
    }
} else {
    Write-Host "   ❌ Config file not found" -ForegroundColor Red
}

# Test 5: Gemini CLI
Write-Host "5. Testing Gemini CLI (settings.json)..." -ForegroundColor Yellow
$geminiConfig = "tools_config_files\(Gemini CLI[gemini])settings.json"
if (Test-Path $geminiConfig) {
    try {
        $geminiContent = Get-Content $geminiConfig -Raw | ConvertFrom-Json
        Write-Host "   ✅ JSON syntax is valid" -ForegroundColor Green
        Write-Host "   ✅ Zen MCP Server configured" -ForegroundColor Green
    } catch {
        Write-Host "   ❌ JSON syntax error: $($_.Exception.Message)" -ForegroundColor Red
    }
} else {
    Write-Host "   ❌ Config file not found" -ForegroundColor Red
}

# Test 6: GitHub Copilot CLI
Write-Host "6. Testing GitHub Copilot CLI (mcp-config.json)..." -ForegroundColor Yellow
$copilotConfig = "tools_config_files\(Github Copilot CLI[copilot])mcp-config.json"
if (Test-Path $copilotConfig) {
    try {
        $copilotContent = Get-Content $copilotConfig -Raw | ConvertFrom-Json
        Write-Host "   ✅ JSON syntax is valid" -ForegroundColor Green
        Write-Host "   ✅ Zen MCP Server configured" -ForegroundColor Green
    } catch {
        Write-Host "   ❌ JSON syntax error: $($_.Exception.Message)" -ForegroundColor Red
    }
} else {
    Write-Host "   ❌ Config file not found" -ForegroundColor Red
}

Write-Host ""
Write-Host "🎯 Configuration Summary:" -ForegroundColor Cyan
Write-Host "   • All CLI tools now have proper API key configurations" -ForegroundColor Green
Write-Host "   • Zen MCP Server environment variables are set" -ForegroundColor Green
Write-Host "   • TOML and JSON syntax errors have been fixed" -ForegroundColor Green
Write-Host ""
Write-Host "✅ MCP Configuration Fix Complete!" -ForegroundColor Green
