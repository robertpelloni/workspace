#!/bin/bash
# SINGLE COMMAND DEPLOYMENT
# Run this script to deploy Jules Orchestrator immediately

set -e

# Prompt for credentials if not set
if [ -z "$GITHUB_TOKEN" ]; then
    echo "Enter GitHub Token (from github.com/settings/tokens):"
    read -s GITHUB_TOKEN
    export GITHUB_TOKEN
fi

if [ -z "$JULES_API_KEY" ]; then
    echo "Enter Jules API Key (from jules.google.com/settings):"
    read -s JULES_API_KEY
    export JULES_API_KEY
fi

echo "Creating repository..."
curl -s -X POST -H "Authorization: Bearer $GITHUB_TOKEN" \
    -H "Content-Type: application/json" \
    -d '{"name":"jules-orchestrator","auto_init":true}' \
    https://api.github.com/user/repos > repo.json

# Use a temp dir in the current directory to avoid path issues
WORK_DIR="temp_quick_deploy_$(date +%s)"
mkdir -p "$WORK_DIR"
cd "$WORK_DIR"

git clone https://github.com/Scarmonit/jules-orchestrator.git
cd jules-orchestrator

# Create package.json
echo '{"name":"jules-orchestrator","version":"1.0.0","type":"module","main":"src/index.js","scripts":{"start":"node src/index.js"},"dependencies":{"express":"^4.18.2","ws":"^8.16.0"}}' > package.json

# Create src directory and index.js
mkdir -p src
cat > src/index.js << 'EOF'
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
EOF

# Create Dockerfile
cat > Dockerfile << 'EOF'
FROM node:20-alpine
WORKDIR /app
COPY package*.json ./
RUN npm ci --only=production
COPY src/ ./src/
EXPOSE 3000
CMD ["node", "src/index.js"]
EOF

# Create render.yaml
cat > render.yaml << 'EOF'
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
EOF

# Create README
cat > README.md << 'EOF'
# Jules Orchestrator
Deploy via Render Dashboard
EOF

git add .
git commit -m "Initial commit" || true
git push origin main

echo ""
echo "✅ DEPLOYED TO GITHUB"
echo ""
echo "Next: Open https://dashboard.render.com/create?type=web"
echo "1. Connect repository: Scarmonit/jules-orchestrator"
echo "2. Add environment variables:"
echo "   JULES_API_KEY=${JULES_API_KEY:0:10}..."
echo "   GITHUB_TOKEN=${GITHUB_TOKEN:0:10}..."
echo "3. Click Deploy"
