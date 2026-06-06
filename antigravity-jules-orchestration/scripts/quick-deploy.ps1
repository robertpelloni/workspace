# scripts/quick-deploy.ps1
# SINGLE COMMAND DEPLOYMENT (PowerShell)
# Run this script to deploy Jules Orchestrator immediately

$ErrorActionPreference = "Stop"

# Prompt for credentials if not set
if (-not $env:GITHUB_TOKEN) {
    $env:GITHUB_TOKEN = Read-Host -Prompt "Enter GitHub Token (from github.com/settings/tokens)" -AsSecureString | ConvertFrom-SecureString -AsPlainText
}

if (-not $env:JULES_API_KEY) {
    $env:JULES_API_KEY = Read-Host -Prompt "Enter Jules API Key (from jules.google.com/settings)" -AsSecureString | ConvertFrom-SecureString -AsPlainText
}

Write-Host "Creating repository..." -ForegroundColor Cyan
$Headers = @{
    Authorization = "Bearer $env:GITHUB_TOKEN"
    Accept = "application/vnd.github.v3+json"
}
$Body = @{
    name = "jules-orchestrator"
    auto_init = $true
} | ConvertTo-Json

try {
    Invoke-RestMethod -Uri "https://api.github.com/user/repos" -Headers $Headers -Method Post -Body $Body -ContentType "application/json" | Out-Null
} catch {
    Write-Warning "Repository might already exist."
}

# Temp dir
$WorkDir = "temp_quick_deploy_$(Get-Date -Format 'yyyyMMddHHmmss')"
New-Item -ItemType Directory -Path $WorkDir -Force | Out-Null
Set-Location $WorkDir

git clone https://github.com/Scarmonit/jules-orchestrator.git
Set-Location jules-orchestrator

# Create package.json
$PackageJson = @{
    name = "jules-orchestrator"
    version = "1.0.0"
    type = "module"
    main = "src/index.js"
    scripts = @{ start = "node src/index.js" }
    dependencies = @{
        express = "^4.18.2"
        ws = "^8.16.0"
    }
} | ConvertTo-Json
$PackageJson | Out-File -FilePath "package.json" -Encoding utf8

# Create src directory and index.js
New-Item -ItemType Directory -Path "src" -Force | Out-Null
$IndexJs = @"
import express from 'express';
import { createServer } from 'http';
import { WebSocketServer } from 'ws';

const app = express();
app.use(express.json());

app.get('/api/v1/health', (req, res) => {
    res.json({ status: 'healthy', timestamp: new Date().toISOString() });
});

app.post('/api/v1/workflows/execute', async (req, res) => {
    const { template_name, context } = req.body;
    res.json({ workflow_id: Date.now(), status: 'pending', template: template_name });
});

app.post('/api/v1/webhooks/github', (req, res) => {
    console.log('Webhook:', req.headers['x-github-event']);
    res.json({ received: true });
});

const server = createServer(app);
const wss = new WebSocketServer({ server });
wss.on('connection', (ws) => ws.send(JSON.stringify({ type: 'connected' })));

const PORT = process.env.PORT || 3000;
server.listen(PORT, () => console.log('Running on port', PORT));
"@
$IndexJs | Out-File -FilePath "src\index.js" -Encoding utf8

# Create Dockerfile
$Dockerfile = @"
FROM node:20-alpine
WORKDIR /app
COPY package*.json ./
RUN npm ci --only=production
COPY src/ ./src/
EXPOSE 3000
CMD ["node", "src/index.js"]
"@
$Dockerfile | Out-File -FilePath "Dockerfile" -Encoding utf8

# Create render.yaml
$RenderYaml = @"
services:
  - type: web
    name: jules-orchestrator
    runtime: docker
    region: oregon
    healthCheckPath: /api/v1/health
    envVars:
      - key: JULES_API_KEY
        sync: false
      - key: GITHUB_TOKEN
        sync: false
"@
$RenderYaml | Out-File -FilePath "render.yaml" -Encoding utf8

# Create README
"Deploy via Render Dashboard" | Out-File -FilePath "README.md" -Encoding utf8

git add .
git commit -m "Initial commit"
git push origin main

Write-Host ""
Write-Host "✅ DEPLOYED TO GITHUB" -ForegroundColor Green
Write-Host ""
Write-Host "Next: Open https://dashboard.render.com/create?type=web"
Write-Host "1. Connect repository: Scarmonit/jules-orchestrator"
Write-Host "2. Add environment variables: JULES_API_KEY and GITHUB_TOKEN"
Write-Host "3. Click Deploy"
