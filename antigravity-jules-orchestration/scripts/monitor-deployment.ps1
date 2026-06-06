# Render Deployment Monitor
# Monitors the Jules Orchestrator service deployment

$ErrorActionPreference = "Continue"

Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host "📊 Render Deployment Monitor" -ForegroundColor Cyan
Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host ""

$SERVICE_URL = "https://jules-orchestrator.onrender.com"
$HEALTH_ENDPOINT = "$SERVICE_URL/api/v1/health"
$RENDER_DASHBOARD = "https://dashboard.render.com/web/srv-d4mlmna4d50c73ep70sg"

Write-Host "Service: jules-orchestrator" -ForegroundColor Yellow
Write-Host "URL: $SERVICE_URL" -ForegroundColor Yellow
Write-Host "Health Check: $HEALTH_ENDPOINT" -ForegroundColor Yellow
Write-Host ""

# Function to check service status
function Test-ServiceHealth {
    try {
        $response = Invoke-RestMethod -Uri $HEALTH_ENDPOINT -TimeoutSec 15 -ErrorAction Stop
        return @{
            Success = $true
            Response = $response
            StatusCode = 200
        }
    } catch {
        $statusCode = 0
        if ($_.Exception.Response) {
            $statusCode = $_.Exception.Response.StatusCode.value__
        }
        return @{
            Success = $false
            StatusCode = $statusCode
            Error = $_.Exception.Message
        }
    }
}

# Monitor deployment
$maxAttempts = 10
$interval = 30

Write-Host "🔍 Monitoring deployment (max $maxAttempts attempts, ${interval}s interval)..." -ForegroundColor Cyan
Write-Host ""

for ($i = 1; $i -le $maxAttempts; $i++) {
    Write-Host "[$i/$maxAttempts] Checking service..." -ForegroundColor Cyan
    
    $result = Test-ServiceHealth
    
    if ($result.Success) {
        Write-Host "✅ SERVICE IS LIVE!" -ForegroundColor Green
        Write-Host ""
        Write-Host "Response:" -ForegroundColor Cyan
        Write-Host ($result.Response | ConvertTo-Json -Depth 5) -ForegroundColor White
        Write-Host ""
        Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
        Write-Host "🎉 DEPLOYMENT SUCCESSFUL!" -ForegroundColor Green
        Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
        Write-Host ""
        Write-Host "Service URL: $SERVICE_URL" -ForegroundColor Cyan
        Write-Host "Health Check: $HEALTH_ENDPOINT" -ForegroundColor Cyan
        Write-Host ""
        exit 0
    } else {
        $statusMessage = switch ($result.StatusCode) {
            0 { "Connection failed (service not reachable)" }
            502 { "Bad Gateway (service building/starting)" }
            503 { "Service Unavailable (temporarily down)" }
            504 { "Gateway Timeout (service slow to start)" }
            default { "HTTP $($result.StatusCode)" }
        }
        
        Write-Host "⏳ Status: $statusMessage" -ForegroundColor Yellow
        
        if ($i -lt $maxAttempts) {
            Write-Host "   Retrying in ${interval} seconds..." -ForegroundColor Gray
            Start-Sleep -Seconds $interval
        }
    }
}

# If we get here, deployment didn't complete successfully
Write-Host ""
Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host "⚠️  Deployment Still In Progress" -ForegroundColor Yellow
Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host ""
Write-Host "The service has not responded after $maxAttempts attempts." -ForegroundColor Yellow
Write-Host ""
Write-Host "Next Steps:" -ForegroundColor Cyan
Write-Host "1. Check Render Dashboard for deployment status:" -ForegroundColor White
Write-Host "   $RENDER_DASHBOARD" -ForegroundColor Gray
Write-Host ""
Write-Host "2. View deployment logs:" -ForegroundColor White
Write-Host "   $RENDER_DASHBOARD/logs" -ForegroundColor Gray
Write-Host ""
Write-Host "3. Check for errors in the Events tab:" -ForegroundColor White
Write-Host "   $RENDER_DASHBOARD/events" -ForegroundColor Gray
Write-Host ""
Write-Host "4. Manual health check:" -ForegroundColor White
Write-Host "   curl $HEALTH_ENDPOINT" -ForegroundColor Gray
Write-Host ""

# Open dashboard
Write-Host "Opening Render Dashboard..." -ForegroundColor Cyan
Start-Process $RENDER_DASHBOARD

Write-Host ""
Write-Host "Note: Large builds can take 5-10 minutes." -ForegroundColor Gray
Write-Host "Run this script again to continue monitoring." -ForegroundColor Gray
Write-Host ""
