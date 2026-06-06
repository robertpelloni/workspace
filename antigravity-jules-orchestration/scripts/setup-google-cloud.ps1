# Automated Google Cloud Service Account Creation
# This script creates the entire Google Cloud setup for Jules API

$ErrorActionPreference = "Stop"

Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host "🔐 Automated Google Cloud Setup for Jules API" -ForegroundColor Cyan
Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host ""

# Configuration
$PROJECT_ID = "jules-orchestrator-$(Get-Random -Minimum 1000 -Maximum 9999)"
$SERVICE_ACCOUNT_NAME = "jules-agent"
$SERVICE_ACCOUNT_DISPLAY_NAME = "Jules API Service Account"
$ROLE = "roles/editor"
$KEY_FILE = "jules-service-account-key.json"

Write-Host "📋 Configuration:" -ForegroundColor Cyan
Write-Host "   Project ID: $PROJECT_ID" -ForegroundColor White
Write-Host "   Service Account: $SERVICE_ACCOUNT_NAME" -ForegroundColor White
Write-Host "   Role: $ROLE" -ForegroundColor White
Write-Host ""

# Step 1: Initialize gcloud
Write-Host "1️⃣  Initializing gcloud CLI..." -ForegroundColor Cyan
try {
    $gcloudPath = "C:\Program Files (x86)\Google\Cloud SDK\google-cloud-sdk\bin\gcloud.cmd"
    
    # Check if already authenticated
    $authList = & $gcloudPath auth list --format=json 2>&1 | ConvertFrom-Json
    
    if (-not $authList -or $authList.Count -eq 0) {
        Write-Host "   🔐 Opening browser for authentication..." -ForegroundColor Yellow
        & $gcloudPath auth login --no-launch-browser
    } else {
        Write-Host "   ✅ Already authenticated as: $($authList[0].account)" -ForegroundColor Green
    }
} catch {
    Write-Host "   ❌ Authentication required. Run: gcloud auth login" -ForegroundColor Red
    Write-Host "   Error: $($_.Exception.Message)" -ForegroundColor Gray
    exit 1
}

Write-Host ""

# Step 2: Create Project
Write-Host "2️⃣  Creating Google Cloud Project..." -ForegroundColor Cyan
try {
    & $gcloudPath projects create $PROJECT_ID --name="Jules Orchestrator" 2>&1 | Out-Null
    Write-Host "   ✅ Project created: $PROJECT_ID" -ForegroundColor Green
} catch {
    if ($_.Exception.Message -like "*already exists*") {
        Write-Host "   ℹ️  Project already exists, continuing..." -ForegroundColor Yellow
    } else {
        Write-Host "   ⚠️  Project creation warning: $($_.Exception.Message)" -ForegroundColor Yellow
    }
}

# Set active project
& $gcloudPath config set project $PROJECT_ID

Write-Host ""

# Step 3: Enable Billing (Note: This requires manual setup if not already configured)
Write-Host "3️⃣  Checking billing..." -ForegroundColor Cyan
try {
    $billingInfo = & $gcloudPath billing projects describe $PROJECT_ID --format=json | ConvertFrom-Json
    if ($billingInfo.billingEnabled) {
        Write-Host "   ✅ Billing enabled" -ForegroundColor Green
    } else {
        Write-Host "   ⚠️  Billing not enabled - some APIs may not work" -ForegroundColor Yellow
        Write-Host "   💡 Enable at: https://console.cloud.google.com/billing/linkedaccount?project=$PROJECT_ID" -ForegroundColor Cyan
    }
} catch {
    Write-Host "   ℹ️  Could not check billing status" -ForegroundColor Yellow
}

Write-Host ""

# Step 4: Enable Required APIs
Write-Host "4️⃣  Enabling required APIs..." -ForegroundColor Cyan

$apis = @(
    "iam.googleapis.com",
    "cloudresourcemanager.googleapis.com"
)

foreach ($api in $apis) {
    try {
        Write-Host "   Enabling $api..." -ForegroundColor Gray
        & $gcloudPath services enable $api --project=$PROJECT_ID 2>&1 | Out-Null
        Write-Host "   ✅ $api enabled" -ForegroundColor Green
    } catch {
        Write-Host "   ⚠️  Warning: $api - $($_.Exception.Message)" -ForegroundColor Yellow
    }
}

# Try to enable Jules API (may not exist publicly yet)
try {
    Write-Host "   Attempting to enable Jules API..." -ForegroundColor Gray
    & $gcloudPath services enable jules.googleapis.com --project=$PROJECT_ID 2>&1 | Out-Null
    Write-Host "   ✅ Jules API enabled" -ForegroundColor Green
} catch {
    Write-Host "   ℹ️  Jules API not available (expected - may be in preview)" -ForegroundColor Yellow
}

Write-Host ""

# Step 5: Create Service Account
Write-Host "5️⃣  Creating service account..." -ForegroundColor Cyan

$SERVICE_ACCOUNT_EMAIL = "$SERVICE_ACCOUNT_NAME@$PROJECT_ID.iam.gserviceaccount.com"

try {
    & $gcloudPath iam service-accounts create $SERVICE_ACCOUNT_NAME `
        --display-name="$SERVICE_ACCOUNT_DISPLAY_NAME" `
        --project=$PROJECT_ID 2>&1 | Out-Null
    
    Write-Host "   ✅ Service account created: $SERVICE_ACCOUNT_EMAIL" -ForegroundColor Green
} catch {
    if ($_.Exception.Message -like "*already exists*") {
        Write-Host "   ℹ️  Service account already exists, continuing..." -ForegroundColor Yellow
    } else {
        Write-Host "   ❌ Failed to create service account: $($_.Exception.Message)" -ForegroundColor Red
        exit 1
    }
}

Write-Host ""

# Step 6: Grant Permissions
Write-Host "6️⃣  Granting permissions..." -ForegroundColor Cyan

try {
    & $gcloudPath projects add-iam-policy-binding $PROJECT_ID `
        --member="serviceAccount:$SERVICE_ACCOUNT_EMAIL" `
        --role="$ROLE" `
        --condition=None 2>&1 | Out-Null
    
    Write-Host "   ✅ Role $ROLE granted to service account" -ForegroundColor Green
} catch {
    Write-Host "   ⚠️  Permission grant warning: $($_.Exception.Message)" -ForegroundColor Yellow
}

Write-Host ""

# Step 7: Create and Download Key
Write-Host "7️⃣  Creating service account key..." -ForegroundColor Cyan

$KEY_PATH = Join-Path $PSScriptRoot "..\$KEY_FILE"

try {
    & $gcloudPath iam service-accounts keys create $KEY_PATH `
        --iam-account=$SERVICE_ACCOUNT_EMAIL `
        --project=$PROJECT_ID 2>&1 | Out-Null
    
    Write-Host "   ✅ Key file created: $KEY_FILE" -ForegroundColor Green
    Write-Host "   📂 Location: $KEY_PATH" -ForegroundColor Gray
} catch {
    Write-Host "   ❌ Failed to create key: $($_.Exception.Message)" -ForegroundColor Red
    exit 1
}

Write-Host ""

# Step 8: Add to .gitignore
Write-Host "8️⃣  Securing key file..." -ForegroundColor Cyan

$gitignorePath = Join-Path $PSScriptRoot "..\.gitignore"

if (Test-Path $gitignorePath) {
    $gitignoreContent = Get-Content $gitignorePath -Raw
    if ($gitignoreContent -notlike "*$KEY_FILE*") {
        Add-Content -Path $gitignorePath -Value "`n# Google Cloud Service Account Key`n$KEY_FILE"
        Write-Host "   ✅ Added $KEY_FILE to .gitignore" -ForegroundColor Green
    } else {
        Write-Host "   ℹ️  Already in .gitignore" -ForegroundColor Yellow
    }
} else {
    "$KEY_FILE" | Out-File -FilePath $gitignorePath -Encoding UTF8
    Write-Host "   ✅ Created .gitignore with $KEY_FILE" -ForegroundColor Green
}

Write-Host ""

# Step 9: Configure Render
Write-Host "9️⃣  Configuring Render environment..." -ForegroundColor Cyan

if (Test-Path $KEY_PATH) {
    $jsonContent = Get-Content $KEY_PATH -Raw
    Set-Clipboard -Value $jsonContent
    Write-Host "   ✅ JSON key copied to clipboard" -ForegroundColor Green
    Write-Host "   💡 Opening Render dashboard..." -ForegroundColor Cyan
    
    Start-Sleep -Seconds 2
    Start-Process "https://dashboard.render.com/web/srv-d4mlmna4d50c73ep70sg/env"
    
    Write-Host ""
    Write-Host "   📝 Next steps in browser:" -ForegroundColor Yellow
    Write-Host "      1. Delete JULES_API_KEY variable (if present)" -ForegroundColor White
    Write-Host "      2. Add new variable:" -ForegroundColor White
    Write-Host "         Key: GOOGLE_APPLICATION_CREDENTIALS_JSON" -ForegroundColor Gray
    Write-Host "         Value: <Press Ctrl+V to paste>" -ForegroundColor Gray
    Write-Host "      3. Click 'Save Changes'" -ForegroundColor White
} else {
    Write-Host "   ❌ Key file not found" -ForegroundColor Red
}

Write-Host ""
Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host "✅ Google Cloud Setup Complete!" -ForegroundColor Green
Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
Write-Host ""
Write-Host "📊 Summary:" -ForegroundColor Cyan
Write-Host "   ✅ Project ID: $PROJECT_ID" -ForegroundColor White
Write-Host "   ✅ Service Account: $SERVICE_ACCOUNT_EMAIL" -ForegroundColor White
Write-Host "   ✅ Key File: $KEY_FILE (in clipboard)" -ForegroundColor White
Write-Host "   ✅ Role: $ROLE" -ForegroundColor White
Write-Host ""
Write-Host "🔐 Security:" -ForegroundColor Cyan
Write-Host "   ✅ Key file added to .gitignore" -ForegroundColor White
Write-Host "   ⚠️  Keep $KEY_FILE secure - do NOT share" -ForegroundColor Yellow
Write-Host ""
Write-Host "🎯 Next Action:" -ForegroundColor Cyan
Write-Host "   Complete Render configuration in the opened browser window" -ForegroundColor White
Write-Host ""
Write-Host "📚 Documentation: GOOGLE_CLOUD_SETUP.md" -ForegroundColor Gray
Write-Host "═══════════════════════════════════════════════════════" -ForegroundColor Magenta
