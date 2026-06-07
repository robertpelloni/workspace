#!/bin/bash
# quickstart.sh - Execute deployment in one command

export GITHUB_TOKEN="${GITHUB_TOKEN:-your_github_token_here}"
export DATABASE_URL="${DATABASE_URL:-postgresql://localhost:5432/jules_orchestrator}"

# Make deployment script executable
chmod +x scripts/deploy.sh

# Run deployment
scripts/deploy.sh
