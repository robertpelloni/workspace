#!/bin/bash
# setup-env.sh - Interactive environment setup

echo "🔧 Jules Orchestrator Environment Setup"
echo "======================================="
echo ""

# Function to prompt for input with default
prompt_input() {
    local var_name=$1
    local prompt_text=$2
    local default_value=$3
    local current_value=$(eval echo \$$var_name)
    
    if [ -z "$current_value" ]; then
        read -p "$prompt_text [$default_value]: " input_value
        export $var_name="${input_value:-$default_value}"
    else
        echo "$prompt_text: [Already set]"
    fi
}

# GitHub token
if [ -z "$GITHUB_TOKEN" ]; then
    echo "📝 GitHub Personal Access Token"
    echo "   Generate at: https://github.com/settings/tokens"
    echo "   Required scopes: repo, workflow, admin:org_hook"
    read -sp "   Token: " GITHUB_TOKEN
    export GITHUB_TOKEN
    echo ""
else
    echo "✓ GITHUB_TOKEN already set"
fi

# Jules API key
if [ -z "$JULES_API_KEY" ]; then
    echo ""
    echo "🤖 Jules API Key"
    echo "   Get from: https://jules.google.com/settings"
    echo "   (Max 3 keys per account)"
    read -sp "   API Key: " JULES_API_KEY
    export JULES_API_KEY
    echo ""
else
    echo "✓ JULES_API_KEY already set"
fi

# Database URL
prompt_input DATABASE_URL "Database URL" "postgresql://localhost:5432/jules_orchestrator"

# Redis URL
prompt_input REDIS_URL "Redis URL" "redis://localhost:6379"

# Slack webhook
if [ -z "$SLACK_WEBHOOK_URL" ]; then
    echo ""
    echo "💬 Slack Webhook (optional)"
    echo "   Create at: https://api.slack.com/messaging/webhooks"
    read -p "   Webhook URL (or press Enter to skip): " SLACK_WEBHOOK_URL
    export SLACK_WEBHOOK_URL
fi

# Webhook secret
prompt_input WEBHOOK_SECRET "GitHub Webhook Secret" $(openssl rand -hex 20)

# Port
prompt_input PORT "API Port" "3000"

# Node environment
prompt_input NODE_ENV "Node Environment" "production"

# Save to .env file
echo ""
echo "💾 Saving to .env file..."

cat > .env << EOF
# Jules Orchestrator Environment Variables
# Generated: $(date)

# GitHub
GITHUB_TOKEN=$GITHUB_TOKEN

# Jules API
JULES_API_KEY=$JULES_API_KEY

# Database
DATABASE_URL=$DATABASE_URL

# Redis
REDIS_URL=$REDIS_URL

# Notifications
SLACK_WEBHOOK_URL=$SLACK_WEBHOOK_URL

# Security
WEBHOOK_SECRET=$WEBHOOK_SECRET

# Server
PORT=$PORT
NODE_ENV=$NODE_ENV
EOF

echo "✅ Environment configured!"
echo ""
echo "📄 Variables saved to .env"
echo "   Source with: source .env"
echo ""
echo "🔒 Security reminder:"
echo "   • Add .env to .gitignore"
echo "   • Never commit secrets to git"
echo "   • Use Render environment variables for production"
