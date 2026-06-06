#!/bin/bash
# deploy-jules-orchestrator.sh
# Master deployment script for Jules Orchestrator system

set -e  # Exit on error

echo "🚀 Jules Orchestrator Deployment Script"
echo "========================================"
echo ""

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Check prerequisites
echo "📋 Checking prerequisites..."

command -v git >/dev/null 2>&1 || { echo "${RED}❌ git is required${NC}"; exit 1; }
command -v node >/dev/null 2>&1 || { echo "${RED}❌ node is required${NC}"; exit 1; }
command -v docker >/dev/null 2>&1 || { echo "${RED}❌ docker is required${NC}"; exit 1; }
command -v psql >/dev/null 2>&1 || { echo "${RED}❌ psql is required${NC}"; exit 1; }

echo "${GREEN}✓${NC} All prerequisites met"
echo ""

# Step 1: Create GitHub repository
echo "📦 Step 1: Creating GitHub repository..."

if [ -z "$GITHUB_TOKEN" ]; then
    echo "${YELLOW}⚠️  GITHUB_TOKEN not set. Please set it:${NC}"
    echo "   export GITHUB_TOKEN=your_token_here"
    exit 1
fi

node scripts/create-repo.js

echo "${GREEN}✓${NC} Repository created"
echo ""

# Step 2: Clone and setup repository
echo "📥 Step 2: Cloning and setting up repository..."

if [ -d "jules-orchestrator" ]; then
    rm -rf jules-orchestrator
fi

# Replace with your actual repo URL if different
REPO_URL="https://github.com/scarmonit/jules-orchestrator.git"
git clone $REPO_URL
cd jules-orchestrator

# Copy all implementation files from local project structure
echo "  Copying implementation files..."
cp ../orchestrator-api/src/index.js src/index.js
cp ../orchestrator-api/src/metrics.js src/metrics.js
# schema.sql and seed.sql are in ../orchestrator-api/migrations/
mkdir -p migrations
cp ../orchestrator-api/migrations/001_initial_schema.sql migrations/001_initial_schema.sql
cp ../orchestrator-api/migrations/002_seed_templates.sql migrations/002_seed_templates.sql
cp ../orchestrator-api/Dockerfile Dockerfile
cp ../orchestrator-api/render.yaml render.yaml
cp ../orchestrator-api/package.json package.json

# Create GitHub Actions workflow directory
mkdir -p .github/workflows
cp ../orchestrator-api/.github/workflows/deploy.yml .github/workflows/deploy.yml

# Create monitoring directory
mkdir -p monitoring
cp ../orchestrator-api/monitoring/prometheus.yml monitoring/prometheus.yml
cp ../orchestrator-api/monitoring/alerts.yml monitoring/alerts.yml
cp ../orchestrator-api/monitoring/docker-compose.monitoring.yml docker-compose.monitoring.yml

echo "${GREEN}✓${NC} Files copied"
echo ""

# Step 3: Install dependencies and test locally
echo "🔧 Step 3: Installing dependencies..."

npm install

echo "${GREEN}✓${NC} Dependencies installed"
echo ""

# Step 4: Setup database (if DATABASE_URL is set)
if [ ! -z "$DATABASE_URL" ]; then
    echo "💾 Step 4: Setting up database..."
    
    psql $DATABASE_URL < migrations/001_initial_schema.sql
    psql $DATABASE_URL < migrations/002_seed_templates.sql
    
    echo "${GREEN}✓${NC} Database initialized"
else
    echo "${YELLOW}⚠️  DATABASE_URL not set. Skipping database setup.${NC}"
    echo "   Run manually: psql \$DATABASE_URL < migrations/001_initial_schema.sql"
fi
echo ""

# Step 5: Commit and push
echo "📤 Step 5: Committing and pushing to GitHub..."

git add .
git commit -m "Initial implementation of Jules Orchestrator

- API Gateway with REST endpoints
- Workflow engine with template processing
- Jules API integration
- PostgreSQL state management
- Redis event bus
- WebSocket real-time updates
- GitHub Actions CI/CD
- Prometheus metrics
- Mission Control dashboard
"

git push origin main

echo "${GREEN}✓${NC} Code pushed to GitHub"
echo ""

# Step 6: Build and test locally
echo "🏗️  Step 6: Building Docker image..."

docker build -t scarmonit/jules-orchestrator:local .

echo "${GREEN}✓${NC} Docker image built"
echo ""

# Step 7: Deploy monitoring stack
echo "📊 Step 7: Deploying monitoring stack..."

docker-compose -f docker-compose.monitoring.yml up -d

echo "${GREEN}✓${NC} Monitoring stack deployed"
echo "   Grafana: http://localhost:3001 (admin/admin)"
echo "   Prometheus: http://localhost:9090"
echo ""

# Step 8: Build Mission Control dashboard
echo "🎨 Step 8: Building Mission Control dashboard..."

mkdir -p dashboard
cd dashboard

npm create vite@latest . -- --template react --name jules-dashboard
npm install
npm install ws

# Copy dashboard files
cp ../../dashboard_assets/App.jsx src/App.jsx
cp ../../dashboard_assets/App.css src/App.css

# Update vite config for agent.scarmonit.com
cat > vite.config.js << 'EOF'
import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'

export default defineConfig({
  plugins: [react()],
  server: {
    proxy: {
      '/api': 'http://localhost:3000',
      '/ws': {
        target: 'ws://localhost:3000',
        ws: true
      }
    }
  }
})
EOF

npm run build

echo "${GREEN}✓${NC} Dashboard built"
echo ""

cd .. # back to jules-orchestrator repo root

# Step 9: Summary and next steps
echo "✅ Deployment preparation complete!"
echo ""
echo "📋 Next steps:"
echo ""
echo "1. Configure Render:"
echo "   • Go to https://dashboard.render.com"
echo "   • Connect scarmonit/jules-orchestrator repository"
echo "   • Add environment variables:"
echo "     - JULES_API_KEY (from jules.google.com/settings)"
echo "     - GITHUB_TOKEN"
echo "     - SLACK_WEBHOOK_URL"
echo "     - WEBHOOK_SECRET (generate a random string)"
echo ""
echo "2. Deploy to Render:"
echo "   • Render will auto-deploy from render.yaml"
echo "   • Wait for PostgreSQL and Redis to provision"
echo "   • API will be available at https://agent.scarmonit.com"
echo ""
echo "3. Deploy Mission Control dashboard to Cloudflare Pages:"
echo "   cd dashboard"
echo "   npx wrangler pages deploy dist --project-name=jules-dashboard"
echo ""
echo "4. Configure GitHub webhooks for target repositories:"
echo "   • Go to repo Settings → Webhooks → Add webhook"
echo "   • URL: https://agent.scarmonit.com/api/v1/webhooks/github"
echo "   • Content type: application/json"
echo "   • Secret: [your WEBHOOK_SECRET]"
echo "   • Events: issues, issue_comment, push, pull_request"
echo ""
echo "5. Test the system:"
echo "   • Create an issue in a watched repo"
echo "   • Add label 'bug-auto' to trigger bugfix workflow"
echo "   • Monitor at https://agent.scarmonit.com"
echo ""
echo "🎉 Your autonomous AI orchestration system is ready!"
