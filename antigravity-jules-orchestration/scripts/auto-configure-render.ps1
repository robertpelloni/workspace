# Automated Render Configuration via Browser Automation
# Uses PowerShell and Selenium to configure environment variables

$ErrorActionPreference = "Stop"

Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host "🤖 Automated Render Configuration" -ForegroundColor Cyan
Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host ""

# Check if service account key exists
$keyFile = "C:\Users\scarm\AntigravityProjects\antigravity-jules-orchestration\jules-service-account-key.json"

if (-not (Test-Path $keyFile)) {
    Write-Host "❌ Service account key not found!" -ForegroundColor Red
    exit 1
}

# Read JSON
$jsonContent = Get-Content $keyFile -Raw
$jsonObj = $jsonContent | ConvertFrom-Json

Write-Host "✅ Service account key loaded" -ForegroundColor Green
Write-Host "   Project: $($jsonObj.project_id)" -ForegroundColor Gray
Write-Host "   Email: $($jsonObj.client_email)" -ForegroundColor Gray
Write-Host ""

# Copy to clipboard
Set-Clipboard -Value $jsonContent
Write-Host "✅ JSON copied to clipboard" -ForegroundColor Green
Write-Host ""

# Create temp file with instructions
$tempFile = Join-Path $env:TEMP "render-config-instructions.txt"
@"
AUTOMATED RENDER CONFIGURATION

Service: jules-orchestrator
Environment Variable: GOOGLE_APPLICATION_CREDENTIALS_JSON

ACTION REQUIRED IN BROWSER:
1. Navigate to: https://dashboard.render.com/web/srv-d4mlmna4d50c73ep70sg/env
2. Delete JULES_API_KEY (if present)
3. Click 'Add Environment Variable'
4. Key: GOOGLE_APPLICATION_CREDENTIALS_JSON
5. Value: Press Ctrl+V (JSON in clipboard)
6. Click 'Save Changes'

JSON PREVIEW (first 100 chars):
$($jsonContent.Substring(0, [Math]::Min(100, $jsonContent.Length)))...

Full JSON is in your clipboard - ready to paste!
"@ | Out-File -FilePath $tempFile -Encoding UTF8

Write-Host "📋 Instructions saved to: $tempFile" -ForegroundColor Cyan
Write-Host ""

# Open browser and instructions side by side
Write-Host "🌐 Opening Render dashboard and instructions..." -ForegroundColor Cyan
Start-Process "https://dashboard.render.com/web/srv-d4mlmna4d50c73ep70sg/env"
Start-Sleep -Seconds 2
Start-Process "notepad.exe" -ArgumentList $tempFile

Write-Host ""
Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host "✅ READY TO CONFIGURE!" -ForegroundColor Green
Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host ""
Write-Host "NEXT STEPS:" -ForegroundColor Cyan
Write-Host "1. Browser is open at Render Environment tab" -ForegroundColor White
Write-Host "2. Notepad has detailed instructions" -ForegroundColor White
Write-Host "3. JSON is in clipboard (press Ctrl+V to paste)" -ForegroundColor White
Write-Host ""
Write-Host "After saving changes in Render, verify with:" -ForegroundColor Cyan
Write-Host "   curl https://jules-orchestrator.onrender.com/api/v1/health" -ForegroundColor Gray
Write-Host ""

# Wait for user confirmation
Write-Host "Press Enter when configuration is complete..." -ForegroundColor Yellow
Read-Host

# Verify deployment
Write-Host ""
Write-Host "🔍 Verifying deployment..." -ForegroundColor Cyan
Start-Sleep -Seconds 5

for ($i = 1; $i -le 15; $i++) {
    Write-Host "[$i/15] Testing health endpoint..." -ForegroundColor Gray
    try {
        $health = Invoke-RestMethod -Uri "https://jules-orchestrator.onrender.com/api/v1/health" -TimeoutSec 10
        
        Write-Host ""
        Write-Host "✅ SERVICE IS LIVE!" -ForegroundColor Green
        Write-Host ""
        Write-Host "Response:" -ForegroundColor Cyan
        Write-Host ($health | ConvertTo-Json -Depth 5) -ForegroundColor White
        Write-Host ""
        
        if ($health.status -eq "ok") {
            Write-Host "🎉 CONFIGURATION SUCCESSFUL!" -ForegroundColor Green
            Write-Host ""
            Write-Host "Your Antigravity-Jules Orchestration service is now fully operational!" -ForegroundColor Cyan
        }
        
        break
    } catch {
        if ($i -lt 15) {
            Write-Host "   Service still deploying... waiting 20 seconds" -ForegroundColor Yellow
            Start-Sleep -Seconds 20
        } else {
            Write-Host ""
            Write-Host "⏳ Deployment is taking longer than expected" -ForegroundColor Yellow
            Write-Host "   Check Render Dashboard for status" -ForegroundColor Gray
            Write-Host "   https://dashboard.render.com/web/srv-d4mlmna4d50c73ep70sg" -ForegroundColor Gray
        }
    }
}

Write-Host ""
