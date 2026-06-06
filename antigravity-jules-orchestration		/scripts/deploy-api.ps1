# Render API Deployment Script
# Uses Render API to create Blueprint deployment programmatically

$ErrorActionPreference = "Stop"

Write-Host "🚀 Deploying to Render via API..." -ForegroundColor Cyan
Write-Host ""

# Configuration
$RENDER_API_KEY = $env:RENDER_API_KEY
$REPO_URL = "https://github.com/Scarmonit/antigravity-jules-orchestration"
$BRANCH = "Scarmonit"
$BLUEPRINT_PATH = "render.yaml"

if (-not $RENDER_API_KEY) {
    Write-Host "❌ RENDER_API_KEY not found in environment" -ForegroundColor Red
    exit 1
}

Write-Host "✅ Render API Key: Configured" -ForegroundColor Green
Write-Host "📦 Repository: $REPO_URL" -ForegroundColor Yellow
Write-Host "🌿 Branch: $BRANCH" -ForegroundColor Yellow
Write-Host ""

# Step 1: Fetch owner info
Write-Host "1️⃣  Fetching account information..." -ForegroundColor Cyan
$headers = @{
    "Authorization" = "Bearer $RENDER_API_KEY"
    "Accept" = "application/json"
}

try {
    $ownerResponse = Invoke-RestMethod -Uri "https://api.render.com/v1/owners" -Headers $headers -Method Get
    $ownerId = $ownerResponse[0].owner.id
    Write-Host "   ✅ Owner ID: $ownerId" -ForegroundColor Green
} catch {
    Write-Host "   ❌ Failed to fetch owner info: $($_.Exception.Message)" -ForegroundColor Red
    exit 1
}

Write-Host ""

# Step 2: Create Blueprint deployment
Write-Host "2️⃣  Creating Blueprint deployment..." -ForegroundColor Cyan

$blueprintPayload = @{
    repo = $REPO_URL
    branch = $BRANCH
    autoDeploy = "yes"
} | ConvertTo-Json

try {
    $deployResponse = Invoke-RestMethod `
        -Uri "https://api.render.com/v1/blueprints" `
        -Headers $headers `
        -Method Post `
        -ContentType "application/json" `
        -Body $blueprintPayload
    
    Write-Host "   ✅ Blueprint deployment initiated!" -ForegroundColor Green
    Write-Host "   📋 Blueprint ID: $($deployResponse.id)" -ForegroundColor White
} catch {
    Write-Host "   ❌ Failed to create blueprint: $($_.Exception.Message)" -ForegroundColor Red
    Write-Host ""
    Write-Host "   Response body:" -ForegroundColor Yellow
    Write-Host $_.ErrorDetails.Message -ForegroundColor Gray
    exit 1
}

Write-Host ""

# Step 3: List services to get service IDs
Write-Host "3️⃣  Fetching created services..." -ForegroundColor Cyan

try {
    $servicesResponse = Invoke-RestMethod -Uri "https://api.render.com/v1/services?limit=10" -Headers $headers -Method Get
    
    $julesService = $servicesResponse | Where-Object { $_.service.name -eq "jules-orchestrator" } | Select-Object -First 1
    
    if ($julesService) {
        $serviceId = $julesService.service.id
        Write-Host "   ✅ Found service: jules-orchestrator" -ForegroundColor Green
        Write-Host "   🆔 Service ID: $serviceId" -ForegroundColor White
        Write-Host "   🌐 URL: https://$($julesService.service.slug).onrender.com" -ForegroundColor Cyan
        
        # Save service info for later use
        $serviceInfo = @{
            serviceId = $serviceId
            serviceName = $julesService.service.name
            serviceUrl = "https://$($julesService.service.slug).onrender.com"
            createdAt = Get-Date -Format "yyyy-MM-ddTHH:mm:ssZ"
        } | ConvertTo-Json
        
        $serviceInfo | Out-File -FilePath "render-service-info.json" -Encoding UTF8
        Write-Host "   💾 Service info saved to: render-service-info.json" -ForegroundColor Gray
    } else {
        Write-Host "   ⚠️  Service not found yet (may still be creating)" -ForegroundColor Yellow
        Write-Host "   💡 Check Render dashboard for status" -ForegroundColor Cyan
    }
} catch {
    Write-Host "   ⚠️  Could not fetch services: $($_.Exception.Message)" -ForegroundColor Yellow
}

Write-Host ""
Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host "🎉 Deployment Initiated Successfully!" -ForegroundColor Green
Write-Host ""
Write-Host "📊 Next Steps:" -ForegroundColor Yellow
Write-Host "   1. Monitor deployment: https://dashboard.render.com" -ForegroundColor White
Write-Host "   2. Set environment variables (JULES_API_KEY, GITHUB_TOKEN)" -ForegroundColor White
Write-Host "   3. Wait for build to complete (~5-10 minutes)" -ForegroundColor White
Write-Host "   4. Verify deployment with: bash scripts/verify-deployment.sh" -ForegroundColor White
Write-Host ""
Write-Host "📚 Documentation: docs/RENDER_DEPLOYMENT.md" -ForegroundColor Cyan
Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
