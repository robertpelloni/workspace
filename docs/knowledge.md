# Workspace Knowledge

## Overview
This workspace contains multiple AI-related projects, tools, and integrations including:
- MCP (Model Context Protocol) servers and implementations
- AI orchestration tools (Zen, Serena, etc.)
- Development tools and frameworks
- Game development projects (BobsGameOnline, hellven, etc.)
- Various AI model integrations (Claude, Gemini, GPT, Grok, Qwen)

## Project Structure
The workspace is organized as a monorepo with multiple independent projects:
- **MCP Servers**: zen-mcp-server, serena, chroma, and others
- **AI Tools**: orchestration, proxy servers, CLI tools
- **Development Projects**: Various application codebases
- **Configuration Files**: Centralized in tools_config_files/

## Development Guidelines
- Follow existing code style and conventions in each project
- MCP servers use TypeScript/JavaScript or Python
- Configuration files use JSON format
- Most projects have their own README.md and documentation

## Common Commands
- Package management varies by project (npm, pnpm, bun, pip, uv)
- Always check project-specific package manager before installing dependencies
- Windows-specific: Use PowerShell commands where applicable

## Multi-AI Orchestration
This workspace supports multiple AI models working together:
- Claude: Architecture and complex reasoning
- GPT: Code implementation
- Gemini: Performance optimization
- Grok: Creative problem-solving

See CLAUDE.md for detailed AI orchestration patterns and best practices.
