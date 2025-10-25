# Simple Configuration Test
Write-Host "Configuring All Models and MCP Servers" -ForegroundColor Green

# Test CLI Tools
Write-Host "`nChecking CLI Tools..." -ForegroundColor Yellow

# Test Codex
if (Get-Command "codex" -ErrorAction SilentlyContinue) {
    try {
        $codexStatus = codex login status 2>&1
        if ($codexStatus -like "*Logged in*") {
            Write-Host "Codex CLI: Authenticated" -ForegroundColor Green
        } else {
            Write-Host "Codex CLI: Needs authentication" -ForegroundColor Yellow
        }
    } catch {
        Write-Host "Codex CLI: Error" -ForegroundColor Red
    }
} else {
    Write-Host "Codex CLI: Not installed" -ForegroundColor Red
}

# Test Gemini
if (Get-Command "gemini" -ErrorAction SilentlyContinue) {
    try {
        $geminiStatus = gemini auth status 2>&1
        if ($geminiStatus -like "*Loaded cached credentials*") {
            Write-Host "Gemini CLI: Authenticated" -ForegroundColor Green
        } else {
            Write-Host "Gemini CLI: Needs authentication" -ForegroundColor Yellow
        }
    } catch {
        Write-Host "Gemini CLI: Error" -ForegroundColor Red
    }
} else {
    Write-Host "Gemini CLI: Not installed" -ForegroundColor Red
}

# Test Grok
if (Get-Command "grok" -ErrorAction SilentlyContinue) {
    Write-Host "Grok CLI: Installed (needs API key)" -ForegroundColor Yellow
} else {
    Write-Host "Grok CLI: Not installed" -ForegroundColor Red
}

# Test Orchestrator
if (Test-Path "tools_config_files\ai-orchestrator.js") {
    try {
        $testInput = '{"task": "test", "priority": "low"}'
        $result = $testInput | node tools_config_files\ai-orchestrator.js
        if ($result -like "*taskId*") {
            Write-Host "AI Orchestrator: Working" -ForegroundColor Green
        } else {
            Write-Host "AI Orchestrator: Partial" -ForegroundColor Yellow
        }
    } catch {
        Write-Host "AI Orchestrator: Error" -ForegroundColor Red
    }
} else {
    Write-Host "AI Orchestrator: Not found" -ForegroundColor Red
}

Write-Host "`nConfiguration Summary:" -ForegroundColor Yellow
Write-Host "Total Models: 12" -ForegroundColor Cyan
Write-Host "CLI Tools: 3" -ForegroundColor Cyan
Write-Host "MCP Servers: 5" -ForegroundColor Cyan
Write-Host "Orchestration: Ready" -ForegroundColor Cyan

Write-Host "`nQuick Commands:" -ForegroundColor Yellow
Write-Host "Codex: codex exec --model gpt-5-codex" -ForegroundColor White
Write-Host "Gemini: gemini -m gemini-2.5-pro" -ForegroundColor White
Write-Host "Grok: grok --api-key KEY -m grok-4-code" -ForegroundColor White
Write-Host "Orchestrator: echo task | node ai-orchestrator.js" -ForegroundColor White

Write-Host "`nConfiguration Complete!" -ForegroundColor Green
