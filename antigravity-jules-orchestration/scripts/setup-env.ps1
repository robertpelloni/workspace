# scripts/setup-env.ps1
# Interactive environment setup for Windows

Write-Host "🔧 Jules Orchestrator Environment Setup" -ForegroundColor Cyan
Write-Host "======================================="
Write-Host ""

# Function to prompt for input
function Prompt-Input {
    param (
        [string]$VarName,
        [string]$PromptText,
        [string]$DefaultValue,
        [bool]$IsSecret = $false
    )

    $CurrentValue = (Get-Item env:$VarName -ErrorAction SilentlyContinue).Value
    
    if ([string]::IsNullOrEmpty($CurrentValue)) {
        if ($IsSecret) {
            $InputVal = Read-Host -Prompt "$PromptText (Secret) [$DefaultValue]" -AsSecureString
            if ($InputVal) {
                $BSTR = [System.Runtime.InteropServices.Marshal]::SecureStringToBSTR($InputVal)
                $InputVal = [System.Runtime.InteropServices.Marshal]::PtrToStringBSTR($BSTR)
                [System.Runtime.InteropServices.Marshal]::ZeroFreeBSTR($BSTR)
            }
        }
        else {
            $InputVal = Read-Host -Prompt "$PromptText [$DefaultValue]"
        }

        if ([string]::IsNullOrEmpty($InputVal)) {
            $InputVal = $DefaultValue
        }
        
        [Environment]::SetEnvironmentVariable($VarName, $InputVal, "Process")
        return $InputVal
    }
    else {
        Write-Host "$PromptText`: [Already set]" -ForegroundColor Gray
        return $CurrentValue
    }
}

# GitHub Token
if (-not $env:GITHUB_TOKEN) {
    Write-Host "📝 GitHub Personal Access Token"
    Write-Host "   Generate at: https://github.com/settings/tokens"
    Write-Host "   Required scopes: repo, workflow, admin:org_hook"
    $env:GITHUB_TOKEN = Prompt-Input "GITHUB_TOKEN" "GitHub Token" "" $true
} else {
    Write-Host "✓ GITHUB_TOKEN already set" -ForegroundColor Green
}

# Jules API Key
if (-not $env:JULES_API_KEY) {
    Write-Host "`n🤖 Jules API Key"
    Write-Host "   Get from: https://jules.google.com/settings"
    $env:JULES_API_KEY = Prompt-Input "JULES_API_KEY" "Jules API Key" "" $true
} else {
    Write-Host "✓ JULES_API_KEY already set" -ForegroundColor Green
}

# Database URL
$env:DATABASE_URL = Prompt-Input "DATABASE_URL" "Database URL" "postgresql://localhost:5432/jules_orchestrator"

# Redis URL
$env:REDIS_URL = Prompt-Input "REDIS_URL" "Redis URL" "redis://localhost:6379"

# Slack Webhook
$env:SLACK_WEBHOOK_URL = Prompt-Input "SLACK_WEBHOOK_URL" "Slack Webhook URL (Optional)" ""

# Webhook Secret
$RandomSecret = -join ((65..90) + (97..122) + (48..57) | Get-Random -Count 32 | % {[char]$_})
$env:WEBHOOK_SECRET = Prompt-Input "WEBHOOK_SECRET" "GitHub Webhook Secret" $RandomSecret

# Port & Node Env
$env:PORT = Prompt-Input "PORT" "API Port" "3000"
$env:NODE_ENV = Prompt-Input "NODE_ENV" "Node Environment" "production"

# Save to .env
Write-Host "`n💾 Saving to .env file..."
$EnvContent = @"
# Jules Orchestrator Environment Variables
# Generated: $(Get-Date)

GITHUB_TOKEN=$env:GITHUB_TOKEN
JULES_API_KEY=$env:JULES_API_KEY
DATABASE_URL=$env:DATABASE_URL
REDIS_URL=$env:REDIS_URL
SLACK_WEBHOOK_URL=$env:SLACK_WEBHOOK_URL
WEBHOOK_SECRET=$env:WEBHOOK_SECRET
PORT=$env:PORT
NODE_ENV=$env:NODE_ENV
"@

$EnvContent | Out-File -FilePath ".env" -Encoding utf8

Write-Host "✅ Environment configured!" -ForegroundColor Green
Write-Host "📄 Variables saved to .env"
Write-Host "🔒 Security reminder: Never commit .env to git"
