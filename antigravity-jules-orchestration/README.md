# Antigravity-Jules Orchestration

**Version: 2.6.2** | [CHANGELOG](./CHANGELOG.md)

## Overview
Autonomous AI orchestration architecture combining **Google Antigravity** with the **Jules API** for hands-free development workflows. This system leverages the Model Context Protocol (MCP) for seamless agent coordination.

## Architecture Components

### 1. Google Antigravity Integration
- **Browser Subagent**: Specialized model for browser automation with DOM capture, screenshots, and video recording
- **Agent Modes**: Planning mode for complex tasks with task groups and artifacts; Fast mode for simple operations
- **Workspace Management**: Multi-workspace support with parallel conversation execution
- **Task Lists & Implementation Plans**: Structured approach to complex tasks with approval workflows
- **MCP Store Integration**: Built-in support for connecting to external services and databases

### 2. Jules API Connection
- **Autonomous Coding Sessions**: Create and manage Jules coding sessions directly from AI assistants
- **GitHub Integration**: Connect to repositories through Jules sources
- **Plan Approval Workflow**: Review and approve execution plans before changes
- **Real-time Activity Tracking**: Monitor session progress with detailed activity logs
- **MCP Bridge**: Jules MCP server acts as bridge between AI assistants and Jules API

### 3. MCP Integration Layer
- **Custom MCP Server**: Node.js-based server using Streamable HTTP transport
- **Type-safe Validation**: Joi schemas for runtime validation of all inputs
- **Stateless Architecture**: Optimized for compatibility with multiple MCP clients
- **65 MCP Tools Available** including:
  - Jules Core API (7 tools)
  - Session Management (5 tools)
  - Session Templates (4 tools)
  - Session Cloning & Search (2 tools)
  - PR Integration (3 tools)
  - Session Queue (4 tools)
  - Batch Processing (7 tools)
  - Analytics (1 tool)
  - Monitoring & Cache (4 tools)
  - Ollama Local LLM (4 tools)
  - RAG (4 tools)
  - Semantic Memory (8 tools)
  - Render Integration (12 tools)
  - Suggested Tasks (3 tools)

## v2.6.x Features

### Render Auto-Fix Integration (v2.6.0)
- Automatically detect and fix build failures on Jules PRs
- Webhook receiver for Render deployment events
- Build log analysis with intelligent error pattern recognition
- Secure credential storage with AES-256-GCM encryption

### Suggested Tasks Scanner (v2.6.0)
- Scan codebases for TODO/FIXME/HACK comments
- Priority-based task ranking
- Create Jules sessions to fix suggested tasks

### Semantic Memory Integration (v2.6.1)
- 8 MCP tools for persistent AI memory
- SSRF protection with domain whitelist
- Error message sanitization

### GitHub Issue Integration
- jules_create_from_issue: Creates a Jules session from a GitHub issue
- jules_batch_from_labels: Creates Jules sessions from all issues with a given label

### Batch Processing
- jules_batch_create: Creates a batch of Jules sessions from a list of tasks
- jules_batch_status: Checks the status of a batch of Jules sessions
- jules_batch_approve_all: Approves all sessions in a batch
- jules_batch_retry_failed: Retry all failed sessions in a batch

### Session Templates (v2.5.0)
- Save and reuse session configurations
- Create sessions from templates with overrides

### Priority Queue (v2.5.0)
- Queue sessions with priority-based processing
- Automatic failure handling

### PR Integration (v2.5.0)
- Merge PRs directly from Jules sessions
- Add comments to PRs

### Session Monitoring
- jules_monitor_all: Monitors all active Jules sessions
- jules_session_timeline: Gets a timeline of events for a Jules session

## Workflow Architecture

### MCP Tool Chain Orchestration
**Status:** Production Ready | **Tools:** 65 MCP tools | **Chains:** 5 executable workflows

- **65 MCP Tools Cataloged**: Jules, Ollama, RAG, Semantic Memory, Render integration
- **5 Tool Chains Designed**: Complete workflows from diagnostics to deployment
- **Automated Execution**: PowerShell scripts for repeatable chain testing
- **Production-Ready Artifacts**: Generated Terraform, Docker, K8s, Prometheus configs

**Documentation:**
- [MCP Tool Chain Architecture](docs/reference/MCP_TOOL_CHAINS.md) - Complete guide
- [Orchestration Report](docs/reports/MCP_ORCHESTRATION_REPORT.md) - Execution results
- [Quick Reference](docs/MCP_QUICK_REFERENCE.md) - Commands and patterns

### Autonomous Development Loop
1. **Task Initiation**: User provides high-level task in Antigravity
2. **Planning Phase**: Antigravity agent creates implementation plan with task groups
3. **Jules Session Creation**: MCP server creates Jules coding session with appropriate source
4. **Parallel Execution**: Antigravity manages browser automation; Jules handles code generation
5. **Progress Monitoring**: Real-time activity tracking across both systems
6. **Approval Gates**: Implementation plans reviewed before execution
7. **Completion**: Changes merged, tests executed, documentation updated

## Installation

### Prerequisites
- Node.js v18+
- Google Antigravity installed
- Jules API account with API key
- GitHub account with connected repositories

### Setup Steps

1. Clone Repository: git clone https://github.com/Scarmonit/antigravity-jules-orchestration.git
2. Install Dependencies: npm install
3. Configure Environment: cp .env.example .env (add JULES_API_KEY)
4. Start MCP Server: npm run dev

## Configuration

| Variable | Description | Default |
|----------|-------------|---------|
| PORT | Server port | 3323 |
| JULES_API_KEY | Jules API key (required) | null |
| GITHUB_TOKEN | GitHub token for issue integration | null |
| DATABASE_URL | PostgreSQL connection string | null |
| SLACK_WEBHOOK_URL | Slack notifications | null |
| LOG_LEVEL | Logging level | info |
| ALLOWED_ORIGINS | CORS whitelist | null |
| SEMANTIC_MEMORY_URL | Semantic memory MCP server URL | null |

## Performance Features

- **LRU Cache**: 100 item capacity with 10s default TTL
- **Circuit Breaker**: Trips after 5 consecutive failures, 60s reset
- **Retry Logic**: 3 retries with exponential backoff and jitter

## Deployment

- **Platform**: Render
- **Branch**: main
- **Health Check**: /health
- **Live URL**: https://scarmonit.com

## Development

- Start server: npm run dev
- Run tests: npm test
- MCP diagnostics: npm run mcp:diagnostics

## License
MIT License

## Contact
- Email: Scarmonit@gmail.com
- GitHub: [@Scarmonit](https://github.com/Scarmonit)

## Troubleshooting

### Git Clone Error: "could not read Password for 'http://git@192.168.0.1:8080'"

If you encounter this error during deployment or when using Jules:
`fatal: could not read Password for 'http://git@192.168.0.1:8080': No such device or address`

This is caused by a global git configuration that forces `https://github.com` URLs to use a local proxy (`192.168.0.1:8080`). This configuration is often injected by the CI/CD environment or container image (via a `setup_git_config` script).

**Solution:**
Check your CI/CD environment (e.g., container entrypoint, cloudbuild config) and remove the script or command that sets this git config:
`git config --global --add url.http://git@192.168.0.1:8080/.insteadOf https://github.com/`