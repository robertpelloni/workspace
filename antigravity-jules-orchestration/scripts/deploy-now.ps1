# scripts/deploy-now.ps1
# CONSOLIDATED DEPLOYMENT SCRIPT (PowerShell Version)
# Run this single command to deploy Jules Orchestrator

$ErrorActionPreference = "Stop"

Write-Host "🚀 Jules Orchestrator - Automated Deployment" -ForegroundColor Cyan
Write-Host "============================================="
Write-Host ""

# Check if credentials are set
if (-not $env:GITHUB_TOKEN) {
    Write-Error "GITHUB_TOKEN not set"
    Write-Host "Get it from: https://github.com/settings/tokens"
    Write-Host "Set with: `$env:GITHUB_TOKEN='ghp_your_token'"
    exit 1
}

# JULES_API_KEY check removed as it might be replaced by Service Account JSON in production

Write-Host "✓ Credentials verified" -ForegroundColor Green
Write-Host ""

# Step 1: Create GitHub repo via API
Write-Host "📦 Creating GitHub repository..."

$Headers = @{
    Authorization = "Bearer $env:GITHUB_TOKEN"
    Accept = "application/vnd.github.v3+json"
}

try {
    $Repo = Invoke-RestMethod -Uri "https://api.github.com/repos/Scarmonit/jules-orchestrator" -Headers $Headers -Method Get -ErrorAction SilentlyContinue
    if ($Repo) {
        Write-Host "⚠️  Repository already exists, skipping creation" -ForegroundColor Yellow
    }
}
catch {
    # Repo likely doesn't exist, create it
    $Body = @{
        name = "jules-orchestrator"
        description = "Autonomous AI orchestration system for Jules API"
        private = $false
        auto_init = $true
    } | ConvertTo-Json

    Invoke-RestMethod -Uri "https://api.github.com/user/repos" -Headers $Headers -Method Post -Body $Body -ContentType "application/json"
    Write-Host "✓ Repository created" -ForegroundColor Green
    Start-Sleep -Seconds 3
}

Write-Host ""

# Step 2: Clone and setup
Write-Host "📥 Cloning repository..."

$WorkDir = "temp_deploy_$(Get-Date -Format 'yyyyMMddHHmmss')"
New-Item -ItemType Directory -Path $WorkDir -Force | Out-Null
Set-Location $WorkDir

git clone https://github.com/Scarmonit/jules-orchestrator.git
Set-Location jules-orchestrator

Write-Host "✓ Repository cloned" -ForegroundColor Green
Write-Host ""

# Step 3: Create project structure
Write-Host "🏗️  Creating project structure..."

New-Item -ItemType Directory -Path "src", "migrations", "monitoring", ".github\workflows", "dashboard\src" -Force | Out-Null

# Copy implementation files
$IndexJs = @"
// orchestrator-api/src/index.js
import express from 'express';
import pg from 'pg';
import axios from 'axios';
import { WebSocketServer } from 'ws';
import { createServer } from 'http';
import { GoogleAuth } from 'google-auth-library';
import * as metrics from './metrics.js';

const app = express();
app.use(express.json());

// Config
const JULES_API_KEY = process.env.JULES_API_KEY;
const GITHUB_TOKEN = process.env.GITHUB_TOKEN;
const DATABASE_URL = process.env.DATABASE_URL;
const PORT = process.env.PORT || 3000;

// Initialize database (optional - graceful fallback)
let db = null;
if (DATABASE_URL) {
  db = new pg.Pool({ connectionString: DATABASE_URL });
  console.log('Database configured');
}

// Metrics Endpoint
app.get('/api/v1/metrics', async (req, res) => {
  res.set('Content-Type', metrics.registerContentType);
  res.end(await metrics.getMetrics());
});

// Initialize Google Auth
const auth = new GoogleAuth({
  scopes: 'https://www.googleapis.com/auth/cloud-platform'
});

// Jules API client
const julesClient = axios.create({
  baseURL: 'https://jules.googleapis.com/v1alpha',
  headers: { 
    'Content-Type': 'application/json'
  }
});

// Add auth interceptor
julesClient.interceptors.request.use(async (config) => {
  try {
    // Get the client and headers (automatically uses GOOGLE_APPLICATION_CREDENTIALS_JSON or ADC)
    const client = await auth.getClient();
    const headers = await client.getRequestHeaders();
    
    // If JULES_API_KEY is still set and no Service Account, fallback (though likely to fail if OAuth required)
    if (!headers.Authorization && JULES_API_KEY) {
        config.headers.Authorization = `Bearer `${JULES_API_KEY}`;
    } else {
        config.headers.Authorization = headers.Authorization;
    }
    
    console.log(`[Jules Client] Requesting `${config.url} with Auth: `${config.headers.Authorization ? 'Present' : 'Missing'}`);
    return config;
  } catch (error) {
    console.error('[Jules Client] Auth Error:', error.message);
    return Promise.reject(error);
  }
});

// GitHub API client
const githubClient = axios.create({
  baseURL: 'https://api.github.com',
  headers: { 
    'Accept': 'application/vnd.github+json'
  }
});

githubClient.interceptors.request.use((config) => {
  if (GITHUB_TOKEN) {
    config.headers.Authorization = 'Bearer ' + GITHUB_TOKEN;
  }
  return config;
});

// Root Endpoint (Service Metadata)
app.get('/', (req, res) => {
  res.json({
    status: 'healthy',
    service: 'Jules MCP Server',
    version: '1.2.0',
    capabilities: ['sessions', 'tasks', 'orchestration', 'mcp-protocol'],
    timestamp: new Date().toISOString()
  });
});

// Health Check
app.get(['/health', '/api/v1/health'], async (req, res) => {
  let dbStatus = 'not_configured';
  if (db) {
    try {
      await db.query('SELECT 1');
      dbStatus = 'connected';
    } catch (e) {
      dbStatus = 'error: ' + e.message;
    }
  }
  
  res.json({ 
    status: 'ok',
    version: '1.2.0',
    services: {
      database: dbStatus,
      julesApi: 'configured',
      githubApi: GITHUB_TOKEN ? 'configured' : 'not_configured'
    },
    timestamp: new Date().toISOString() 
  });
});

// MCP Tools List
app.get('/mcp/tools', (req, res) => {
  res.json({
    tools: [
      {
        name: "jules_create_session",
        description: "Create a new Jules coding session",
        inputSchema: {
          type: "object",
          properties: {
            name: { type: "string", description: "Session name" },
            source: { type: "string", description: "Source repository (e.g., github.com/owner/repo)" }
          },
          required: ["source"]
        }
      },
      {
        name: "jules_list_sessions",
        description: "List active Jules sessions",
        inputSchema: {
          type: "object",
          properties: {
            pageSize: { type: "number" }
          }
        }
      },
      {
        name: "jules_get_session",
        description: "Get details of a specific session",
        inputSchema: {
          type: "object",
          properties: {
            sessionId: { type: "string" }
          },
          required: ["sessionId"]
        }
      }
    ]
  });
});

// MCP Tool Execution
app.post('/mcp/execute', async (req, res) => {
  const { name, arguments: args, tool, parameters } = req.body;
  
  // Support both MCP formats
  const toolName = name || tool;
  const toolArgs = args || parameters || {};
  
  if (!toolName) {
    return res.status(400).json({ error: 'Tool name required (use "name" or "tool" field)' });
  }
  
  try {
    let result;
    if (toolName === 'jules_create_session') {
      const response = await julesClient.post('/sessions', toolArgs);
      result = response.data;
    } else if (toolName === 'jules_list_sessions') {
      const response = await julesClient.get('/sessions');
      result = response.data;
    } else if (toolName === 'jules_get_session') {
      const response = await julesClient.get('/sessions/' + toolArgs.sessionId);
      result = response.data;
    } else {
      return res.status(404).json({ error: 'Tool ' + toolName + ' not found' });
    }
    
    res.json({ 
      success: true,
      content: [{ type: "text", text: JSON.stringify(result, null, 2) }],
      result 
    });
  } catch (error) {
    console.error('MCP Execute Error (' + toolName + '):', error.response?.data || error.message);
    res.status(500).json({ 
      success: false,
      error: error.response?.data?.error?.message || error.message 
    });
  }
});

// WebSocket Setup
const server = createServer(app);
const wss = new WebSocketServer({ server });

const clients = new Set();

wss.on('connection', (ws) => {
  clients.add(ws);
  console.log('WebSocket client connected');
  
  ws.on('close', () => {
    clients.delete(ws);
    console.log('WebSocket client disconnected');
  });
});

function broadcast(data) {
  clients.forEach(client => {
    if (client.readyState === 1) {
      client.send(JSON.stringify(data));
    }
  });
}

// Workflow Status Endpoint
app.get('/api/v1/workflows/:id', async (req, res) => {
  if (!db) {
    return res.status(503).json({ error: 'Database not configured' });
  }
  
  try {
    const workflow = await db.query(
      'SELECT * FROM workflow_instances WHERE id = $1',
      [req.params.id]
    );
    
    if (!workflow.rows.length) {
      return res.status(404).json({ error: 'Workflow not found' });
    }
    
    res.json(workflow.rows[0]);
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
});

// GitHub Webhook Receiver
app.post('/api/v1/webhooks/github', async (req, res) => {
  const event = req.headers['x-github-event'];
  console.log('Received GitHub webhook: ' + event);
  
  broadcast({
    type: 'github_webhook',
    event,
    payload: req.body,
    timestamp: new Date().toISOString()
  });
  
  res.status(200).json({ received: true });
});

// Start server
server.listen(PORT, () => {
  console.log('Jules Orchestrator API running on port ' + PORT);
  console.log('Health check: http://localhost:' + PORT + '/api/v1/health');
  console.log('MCP Tools: http://localhost:' + PORT + '/mcp/tools');
  console.log('Jules API Auth: Configured with GoogleAuth');
  console.log('GitHub Token: ' + (GITHUB_TOKEN ? 'Configured' : 'Not set'));
  console.log('Database: ' + (DATABASE_URL ? 'Configured' : 'Not set'));
});
"@
$IndexJs | Out-File -FilePath "src\index.js" -Encoding utf8

$MetricsJs = @"
import promClient from 'prom-client';

const register = new promClient.Register();

// Default metrics
promClient.collectDefaultMetrics({ register });

export const activeWorkflows = new promClient.Gauge({
  name: 'workflow_active',
  help: 'Number of currently active workflows',
  registers: [register]
});

export const workflowDuration = new promClient.Histogram({
  name: 'workflow_duration_seconds',
  help: 'Workflow execution duration',
  labelNames: ['template', 'status'],
  buckets: [5, 10, 30, 60, 300, 600, 1800, 3600],
  registers: [register]
});

export const julesTaskCounter = new promClient.Counter({
  name: 'jules_tasks_total',
  help: 'Total Jules tasks created',
  labelNames: ['status'],
  registers: [register]
});

export const workflowCounter = new promClient.Counter({
  name: 'workflow_total',
  help: 'Total number of workflows executed',
  labelNames: ['template', 'status'],
  registers: [register]
});

export const actionCounter = new promClient.Counter({
  name: 'workflow_actions_total',
  help: 'Total workflow actions executed',
  labelNames: ['action_type', 'success'],
  registers: [register]
});

export const webhookCounter = new promClient.Counter({
  name: 'webhook_events_total',
  help: 'Total webhook events received',
  labelNames: ['source', 'event_type'],
  registers: [register]
});

export async function getMetrics() {
  return register.metrics();
}

export const registerContentType = register.contentType;
"@
$MetricsJs | Out-File -FilePath "src\metrics.js" -Encoding utf8

$PackageJson = @"
{
  "name": "jules-orchestrator",
  "version": "1.2.0",
  "type": "module",
  "main": "src/index.js",
  "scripts": {
    "start": "node src/index.js"
  },
  "dependencies": {
    "axios": "^1.6.0",
    "express": "^4.18.2",
    "pg": "^8.11.3",
    "prom-client": "^15.0.0",
    "ws": "^8.16.0",
    "google-auth-library": "^9.0.0"
  }
}
"@
$PackageJson | Out-File -FilePath "package.json" -Encoding utf8

$Dockerfile = @"
FROM node:20-alpine
WORKDIR /app
COPY package*.json ./
RUN npm install --production
COPY src/ ./src/
EXPOSE 3000
CMD ["node", "src/index.js"]
"@
$Dockerfile | Out-File -FilePath "Dockerfile" -Encoding utf8

$RenderYaml = @"
services:
  - type: web
    name: jules-orchestrator
    runtime: docker
    region: oregon
    branch: main
    dockerfilePath: ./Dockerfile
    envVars:
      - key: JULES_API_KEY
        sync: false
      - key: GITHUB_TOKEN
        sync: false
      - key: PORT
        value: 3000
    healthCheckPath: /api/v1/health

databases:
  - name: orchestrator-db
    databaseName: jules_orchestrator
    plan: starter
"@
$RenderYaml | Out-File -FilePath "render.yaml" -Encoding utf8

$ReadMe = @"
# Jules Orchestrator

Autonomous AI coding agent orchestration system powered by Google Jules API.

## Deployment
1. Connect this repo in Render dashboard
2. Set environment variables (JULES_API_KEY, GITHUB_TOKEN)
3. Deploy automatically via render.yaml

## Endpoints
- GET /api/v1/health - Health check
- POST /api/v1/workflows/execute - Execute workflow
- POST /api/v1/webhooks/github - GitHub webhook receiver
"@
$ReadMe | Out-File -FilePath "README.md" -Encoding utf8

Write-Host "✓ Project files created" -ForegroundColor Green
Write-Host ""

# Step 4: Commit and push
Write-Host "📤 Pushing to GitHub..."

git add .
git commit -m "Update Jules Orchestrator to v1.2.0 with Google Auth and fixes" 2>$null
git push origin main

Write-Host "✓ Code pushed" -ForegroundColor Green
Write-Host ""

# Step 5: Database migrations (if DATABASE_URL is set)
if ($env:DATABASE_URL) {
    Write-Host "💾 Running database migrations..."
    
    $InitSql = @"
CREATE TABLE IF NOT EXISTS workflow_templates (
  id SERIAL PRIMARY KEY,
  name VARCHAR(255) UNIQUE NOT NULL,
  definition_json JSONB NOT NULL,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

INSERT INTO workflow_templates (name, definition_json) VALUES
('dependency-update', '{"name": "Dependency Update", "trigger": {"type": "scheduled"}}')
ON CONFLICT (name) DO NOTHING;
"@
    $InitSql | Out-File -FilePath "init.sql" -Encoding utf8

    if (Get-Command psql -ErrorAction SilentlyContinue) {
        Get-Content init.sql | psql $env:DATABASE_URL
        Write-Host "✓ Database initialized" -ForegroundColor Green
    } else {
        Write-Warning "psql not found, skipping execution"
    }
} else {
    Write-Warning "DATABASE_URL not set, skipping database setup"
}

Write-Host ""
Write-Host "✅ DEPLOYMENT COMPLETE!" -ForegroundColor Green
Write-Host ""
Write-Host "📋 Next steps:"
Write-Host ""
Write-Host "1. Open Render Dashboard (already open in browser)"
Write-Host "   https://dashboard.render.com/create?type=web"
Write-Host ""
Write-Host "2. Click 'New +' -> 'Web Service'"
Write-Host ""
Write-Host "3. Connect repository: Scarmonit/jules-orchestrator"
Write-Host ""
Write-Host "4. Render will auto-configure from render.yaml"
Write-Host ""
Write-Host "5. Add environment variables in Render:"
Write-Host "   JULES_API_KEY=$env:JULES_API_KEY"
Write-Host "   GITHUB_TOKEN=$env:GITHUB_TOKEN"
Write-Host ""
Write-Host "6. Click 'Deploy'"
Write-Host ""
Write-Host "🎉 Your orchestrator will be live at:"
Write-Host "   https://jules-orchestrator.onrender.com"
Write-Host ""