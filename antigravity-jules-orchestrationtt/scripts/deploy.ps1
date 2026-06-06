# scripts/deploy.ps1
# Master deployment script for Windows

$ErrorActionPreference = "Stop"

Write-Host "🚀 Jules Orchestrator Deployment Script" -ForegroundColor Cyan
Write-Host "========================================"
Write-Host ""

# Load .env if exists
if (Test-Path ".env") {
    Get-Content ".env" | ForEach-Object {
        if ($_ -match "^([^#=]+)=(.*)$") {
            [Environment]::SetEnvironmentVariable($matches[1], $matches[2], "Process")
        }
    }
    Write-Host "✓ Loaded .env file" -ForegroundColor Green
}

# Prerequisites Check
Write-Host "📋 Checking prerequisites..."
if (-not (Get-Command git -ErrorAction SilentlyContinue)) { Write-Error "git is required"; exit 1 }
if (-not (Get-Command node -ErrorAction SilentlyContinue)) { Write-Error "node is required"; exit 1 }
if (-not (Get-Command docker -ErrorAction SilentlyContinue)) { Write-Error "docker is required"; exit 1 }

Write-Host "✓ All prerequisites met" -ForegroundColor Green
Write-Host ""

# Step 1: Create Repo
Write-Host "📦 Step 1: Creating GitHub repository..."
if (-not $env:GITHUB_TOKEN) {
    Write-Error "GITHUB_TOKEN not set. Run scripts/setup-env.ps1 first."
    exit 1
}

node scripts/create-repo.js
Write-Host "✓ Repository created" -ForegroundColor Green
Write-Host ""

# Step 2: Clone & Setup
Write-Host "📥 Step 2: Cloning and setting up repository..."
if (Test-Path "jules-orchestrator") {
    Remove-Item "jules-orchestrator" -Recurse -Force
}

# Retrieve repo name from create-repo output or assume standard
$RepoUrl = "https://github.com/scarmonit/jules-orchestrator.git"
git clone $RepoUrl
Set-Location jules-orchestrator

# Copy implementation files
Write-Host "  Copying implementation files..."
Copy-Item ..\orchestrator-api\src\index.js src\index.js
Copy-Item ..\orchestrator-api\src\metrics.js src\metrics.js

New-Item -ItemType Directory -Path migrations -Force | Out-Null
Copy-Item ..\orchestrator-api\migrations\001_initial_schema.sql migrations\001_initial_schema.sql
Copy-Item ..\orchestrator-api\migrations\002_seed_templates.sql migrations\002_seed_templates.sql

Copy-Item ..\orchestrator-api\Dockerfile Dockerfile
Copy-Item ..\orchestrator-api\render.yaml render.yaml
Copy-Item ..\orchestrator-api\package.json package.json

New-Item -ItemType Directory -Path .github\workflows -Force | Out-Null
Copy-Item ..\orchestrator-api\.github\workflows\deploy.yml .github\workflows\deploy.yml

New-Item -ItemType Directory -Path monitoring -Force | Out-Null
Copy-Item ..\orchestrator-api\monitoring\prometheus.yml monitoring\prometheus.yml
Copy-Item ..\orchestrator-api\monitoring\alerts.yml monitoring\alerts.yml
Copy-Item ..\orchestrator-api\monitoring\docker-compose.monitoring.yml docker-compose.monitoring.yml

Write-Host "✓ Files copied" -ForegroundColor Green
Write-Host ""

# Step 3: Install Deps
Write-Host "🔧 Step 3: Installing dependencies..."
npm install
Write-Host "✓ Dependencies installed" -ForegroundColor Green
Write-Host ""

# Step 4: Database Setup
if ($env:DATABASE_URL) {
    Write-Host "💾 Step 4: Setting up database..."
    if (Get-Command psql -ErrorAction SilentlyContinue) {
        Get-Content migrations\001_initial_schema.sql | psql $env:DATABASE_URL
        Get-Content migrations\002_seed_templates.sql | psql $env:DATABASE_URL
        Write-Host "✓ Database initialized" -ForegroundColor Green
    } else {
        Write-Warning "psql not found, skipping DB initialization"
    }
} else {
    Write-Warning "DATABASE_URL not set, skipping DB initialization"
}
Write-Host ""

# Step 5: Commit & Push
Write-Host "📤 Step 5: Committing and pushing..."
git add .
git commit -m "Initial implementation of Jules Orchestrator"
git push origin main
Write-Host "✓ Code pushed to GitHub" -ForegroundColor Green
Write-Host ""

# Step 6: Build Docker
Write-Host "🏗️  Step 6: Building Docker image..."
docker build -t scarmonit/jules-orchestrator:local .
Write-Host "✓ Docker image built" -ForegroundColor Green
Write-Host ""

# Step 7: Monitoring
Write-Host "📊 Step 7: Deploying monitoring stack..."
docker-compose -f docker-compose.monitoring.yml up -d
Write-Host "✓ Monitoring stack deployed" -ForegroundColor Green
Write-Host ""

# Step 8: Dashboard
Write-Host "🎨 Step 8: Building Mission Control dashboard..."
New-Item -ItemType Directory -Path dashboard -Force | Out-Null
Set-Location dashboard

# Copy pre-built dashboard files
Write-Host "  Copying pre-built dashboard files..."
Copy-Item -Recurse -Force ..\..\dashboard\* .

# Install dependencies (should already be installed, but good for CI)
if (-not (Test-Path "node_modules")) {
    npm install
}

npm run build
Write-Host "✓ Dashboard built" -ForegroundColor Green

Set-Location ..\..

Write-Host "✅ Deployment preparation complete!" -ForegroundColor Green
Write-Host "Next steps:"
Write-Host "1. Go to https://dashboard.render.com and connect the repo"
Write-Host "2. Deploy dashboard/dist to Cloudflare Pages"
