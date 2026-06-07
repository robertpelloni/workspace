# Jules Orchestrator API Architecture (agent.scarmonit.com)

## Stack
- Runtime: Node.js/Bun or Go (fast, async-first)
- Database: PostgreSQL for task state + workflow definitions
- Queue: Redis for event processing and delayed jobs
- API: REST + WebSocket for real-time updates
- Hosting: Render (existing infrastructure)

## Core Services

### 1. API Gateway (/api/v1)
Routes:
- POST /workflows/execute - Create workflow instance from template
- GET /workflows/:id - Get workflow status
- POST /tasks - Create Jules task (proxies to Jules API)
- GET /tasks/:id - Get Jules task status
- POST /webhooks/github - GitHub webhook receiver
- POST /webhooks/security - External security scanner webhook
- GET /health - Health check

### 2. Workflow Engine
- Loads templates from DB or JSON config
- Substitutes template variables ({{repo_name}}, {{issue_title}}, etc)
- Executes pre_actions before Jules task creation
- Creates Jules API task with authentication
- Polls Jules task status or listens to Jules webhooks
- Executes post_actions after task completion
- Handles failures, retries, and rollback

### 3. State Manager (PostgreSQL)
Tables:
- workflow_templates (id, name, definition_json)
- workflow_instances (id, template_id, status, context_json, created_at, updated_at)
- jules_tasks (id, workflow_instance_id, jules_task_id, status, plan_summary, pr_url)
- action_log (id, workflow_instance_id, action_type, result, timestamp)

States: pending → running → awaiting_approval → executing → completed/failed

### 4. Action Executor
Handles pre/post actions:
- notify: Slack webhook, email, PagerDuty
- github_comment: Post comment via GitHub API
- github_review_request: Request PR review
- deploy_preview: Trigger Render preview deploy
- deploy: Production deployment (canary/blue-green)
- github_auto_merge: Merge PR if conditions met

### 5. Event Bus (Redis Pub/Sub)
Channels:
- workflow:created
- workflow:updated
- jules:task:plan_ready
- jules:task:completed
- github:webhook:received

## Authentication & Security
- Jules API: X-Goog-Api-Key header (from jules.google settings)
- GitHub: Personal Access Token or GitHub App (stored in env/secrets)
- Internal API: API key or JWT for webhook authentication
- Secrets: Store in Render environment variables or HashiCorp Vault

## Deployment
- Docker container on Render
- Health checks every 30s
- Auto-restart on failure
- Horizontal scaling for high throughput
