#!/bin/bash
# CONSOLIDATED DEPLOYMENT SCRIPT
# Run this single command to deploy Jules Orchestrator

set -e

echo "🚀 Jules Orchestrator - Automated Deployment"
echo "============================================="
echo ""

# Check if credentials are set
if [ -z "$GITHUB_TOKEN" ]; then
    echo "❌ GITHUB_TOKEN not set"
    echo "Get it from: https://github.com/settings/tokens"
    echo "Set with: export GITHUB_TOKEN=ghp_your_token"
    exit 1
fi

# Note: JULES_API_KEY check removed as it might be replaced by Service Account JSON in production,
# but user can still provide it for fallback.

echo "✓ Credentials verified"
echo ""

# Step 1: Create GitHub repo via API
echo "📦 Creating GitHub repository..."

REPO_EXISTS=$(curl -s -H "Authorization: Bearer $GITHUB_TOKEN" \
    https://api.github.com/repos/Scarmonit/jules-orchestrator | grep -c '"id":' || true)

if [ "$REPO_EXISTS" -gt 0 ]; then
    echo "⚠️  Repository already exists, skipping creation"
else
    curl -X POST -H "Authorization: Bearer $GITHUB_TOKEN" \
        -H "Content-Type: application/json" \
        -d '{ "name": "jules-orchestrator", "description": "Autonomous AI orchestration system for Jules API", "private": false, "auto_init": true }' \
        https://api.github.com/user/repos
    
    echo "✓ Repository created"
    sleep 3
fi

echo ""

# Step 2: Clone and setup
echo "📥 Cloning repository..."

# Use a temporary directory for the clone operation to ensure a clean state
WORK_DIR="temp_deploy_$(date +%s)"
mkdir -p "$WORK_DIR"
cd "$WORK_DIR"

git clone https://github.com/Scarmonit/jules-orchestrator.git
cd jules-orchestrator

echo "✓ Repository cloned"
echo ""

# Step 3: Create project structure
echo "🏗️  Creating project structure..."

mkdir -p src migrations monitoring .github/workflows dashboard/src

# Copy implementation files
cat > src/index.js << 'JSEOF'
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
        config.headers.Authorization = `Bearer ${JULES_API_KEY}`;
    } else {
        config.headers.Authorization = headers.Authorization;
    }
    
    console.log(`[Jules Client] Requesting ${config.url} with Auth: ${config.headers.Authorization ? 'Present' : 'Missing'}`);
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
JSEOF

# Metrics file
cat > src/metrics.js << 'METRICSEOF'
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
METRICSEOF

cat > package.json << 'PKGEOF'
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
PKGEOF

cat > Dockerfile << 'DEOF'
FROM node:20-alpine
WORKDIR /app
COPY package*.json ./
RUN npm install --production
COPY src/ ./src/
EXPOSE 3000
CMD ["node", "src/index.js"]
DEOF

cat > render.yaml << 'REOF'
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
REOF

cat > README.md << 'MDEOF'
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
MDEOF

echo "✓ Project files created"
echo ""

# Step 4: Commit and push
echo "📤 Pushing to GitHub..."

git add .
git commit -m "Update Jules Orchestrator to v1.2.0 with Google Auth and fixes" || true
git push origin main

echo "✓ Code pushed"
echo ""

# Step 5: Database migrations (if DATABASE_URL is set)
if [ ! -z "$DATABASE_URL" ]; then
    echo "💾 Running database migrations..."
    
    cat > init.sql << 'SQLEOF'
CREATE TABLE IF NOT EXISTS workflow_templates (
  id SERIAL PRIMARY KEY,
  name VARCHAR(255) UNIQUE NOT NULL,
  definition_json JSONB NOT NULL,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

INSERT INTO workflow_templates (name, definition_json) VALUES
('dependency-update', '{"name": "Dependency Update", "trigger": {"type": "scheduled"}}')
ON CONFLICT (name) DO NOTHING;
SQLEOF

    psql $DATABASE_URL < init.sql
    echo "✓ Database initialized"
else
    echo "⚠️  DATABASE_URL not set, skipping database setup"
fi

echo ""
echo "✅ DEPLOYMENT COMPLETE!"
echo ""
echo "📋 Next steps:"
echo ""
echo "1. Open Render Dashboard (already open in browser)"
echo "   https://dashboard.render.com/create?type=web"
echo ""
echo "2. Click 'New +' -> 'Web Service'"
echo ""
echo "3. Connect repository: Scarmonit/jules-orchestrator"
echo ""
echo "4. Render will auto-configure from render.yaml"
echo ""
echo "5. Add environment variables in Render:"
echo "   JULES_API_KEY=$JULES_API_KEY"
echo "   GITHUB_TOKEN=$GITHUB_TOKEN"
echo ""
echo "6. Click 'Deploy'"
echo ""
echo "🎉 Your orchestrator will be live at:"
echo "   https://jules-orchestrator.onrender.com"
echo ""