# Quick Render Deployment Script
# Opens dashboard and prepares environment variable config

$ErrorActionPreference = "Stop"

Write-Host "🚀 Render Deployment Setup" -ForegroundColor Cyan
Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host ""

# Configuration
$REPO = "Scarmonit/antigravity-jules-orchestration"
$BRANCH = "Scarmonit"

# Get GitHub token
$GITHUB_TOKEN = $env:GITHUB_TOKEN
if (-not $GITHUB_TOKEN) {
    if (Test-Path "C:\Users\scarm\IdeaProjects\LLM\.env") {
        $GITHUB_TOKEN = (Get-Content C:\Users\scarm\IdeaProjects\LLM\.env | Select-String "GITHUB_TOKEN" | ForEach-Object { $_.ToString().Split("=")[1] })
    }
}

Write-Host "📦 Repository: $REPO" -ForegroundColor Yellow
Write-Host "🌿 Branch: $BRANCH" -ForegroundColor Yellow
Write-Host ""

# Prompt for Jules API Key
Write-Host "🔐 Environment Variables:" -ForegroundColor Cyan
Write-Host ""
$JULES_KEY = Read-Host "Enter your JULES_API_KEY (or press Enter to set later)"

Write-Host ""
Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host "📋 Environment Variables to Set in Render:" -ForegroundColor Green
Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host ""

if ($JULES_KEY) {
    Write-Host "JULES_API_KEY=$JULES_KEY" -ForegroundColor White
    # Copy to clipboard
    Set-Clipboard -Value $JULES_KEY
    Write-Host "✅ JULES_API_KEY copied to clipboard!" -ForegroundColor Green
} else {
    Write-Host "JULES_API_KEY=<your_key_here>" -ForegroundColor Gray
}

Write-Host ""

if ($GITHUB_TOKEN) {
    Write-Host "GITHUB_TOKEN=$GITHUB_TOKEN" -ForegroundColor White
} else {
    Write-Host "GITHUB_TOKEN=<your_token_here>" -ForegroundColor Gray
}

Write-Host ""
Write-Host "SLACK_WEBHOOK_URL=<optional>" -ForegroundColor Gray
Write-Host ""
Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host ""

# Create env file for reference
$envContent = @"
# Environment Variables for Render Dashboard
# Copy these values when setting up the service

JULES_API_KEY=$($JULES_KEY ? $JULES_KEY : 'your_jules_api_key')
GITHUB_TOKEN=$($GITHUB_TOKEN ? $GITHUB_TOKEN : 'your_github_token')
SLACK_WEBHOOK_URL=

# Auto-configured (DO NOT SET):
# DATABASE_URL
# REDIS_URL
"@

$envContent | Out-File -FilePath "render-env-vars.txt" -Encoding UTF8
Write-Host "💾 Saved to: render-env-vars.txt" -ForegroundColor Cyan
Write-Host ""

# Open Render dashboard
Write-Host "🌐 Opening Render Dashboard..." -ForegroundColor Cyan
Start-Process "https://dashboard.render.com/select-repo?type=blueprint"

Start-Sleep -Seconds 2

Write-Host ""
Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host "📝 Manual Deployment Steps:" -ForegroundColor Yellow
Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host ""
Write-Host "1️⃣  In the browser:" -ForegroundColor White
Write-Host "   - Connect GitHub repository: $REPO" -ForegroundColor Gray
Write-Host "   - Select branch: $BRANCH" -ForegroundColor Gray
Write-Host "   - Render will auto-detect render.yaml" -ForegroundColor Gray
Write-Host ""
Write-Host "2️⃣  Set Environment Variables:" -ForegroundColor White
Write-Host "   - Click on 'jules-orchestrator' service" -ForegroundColor Gray
Write-Host "   - Add the environment variables shown above" -ForegroundColor Gray
Write-Host "   - Values are in: render-env-vars.txt" -ForegroundColor Gray
if ($JULES_KEY) {
    Write-Host "   - JULES_API_KEY is in your clipboard!" -ForegroundColor Green
}
Write-Host ""
Write-Host "3️⃣  Deploy:" -ForegroundColor White
Write-Host "   - Click 'Apply' to start deployment" -ForegroundColor Gray
Write-Host "   - Wait 5-10 minutes for build to complete" -ForegroundColor Gray
Write-Host ""
Write-Host "4️⃣  Verify:" -ForegroundColor White
Write-Host "   bash scripts/verify-deployment.sh" -ForegroundColor Gray
Write-Host ""
Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host "✨ Ready to deploy!" -ForegroundColor Green
Write-Host ""
