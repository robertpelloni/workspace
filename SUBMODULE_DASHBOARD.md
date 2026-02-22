# Submodule Dashboard & Project Structure
**Last Updated:** 2026-02-22 17:00:00

## Project Directory Structure Explanation
This monorepo serves as a unified workspace and orchestrator for dozens of independent microservices, libraries, desktop applications, and AI agents.

*   **`Root/`**: Contains the global orchestration scripts (`sync_and_merge.py`, `intelligent_sync_all.py`), universal documentation (`LLM_INSTRUCTIONS.md`, `ROADMAP.md`), and the workspace-level configuration files.
*   **`.gemini/`, `.claude/`, etc.**: AI agent configuration and context directories managing instructions and local extensions for LLMs.
*   **AI Agent Projects**: Folders like `borg`, `metamcp`, `jules-autopilot`, `antigravity-autopilot`, `mcp-superassistant` contain specialized multi-modal and autonomous agents leveraging MCP (Model Context Protocol).
*   **Full-Stack Apps**: Folders like `Chamber.Law`, `cointrade`, `bobeditpro`, `bobfilez` contain entire standalone full-stack applications with their own submodules.
*   **Shared Libraries**: Other directories include shared utilities and libraries nested across the ecosystem.

## Top-Level Submodules & Versions

| Path | Version | Branch | Location |
| :--- | :--- | :--- | :--- |
| **Root Workspace** | 1.3.3 | main | `/` |
| `antigravity-autopilot` | v5.2.55 | main | `/antigravity-autopilot` |
| `jules-autopilot` | v0.8.8 | main | `/jules-autopilot` |
| `borg` | v2.7.0 | main | `/borg` |
| `metamcp` | v3.7.0 | main | `/metamcp` |
| `Chamber.Law` | v1.0.1 | main | `/Chamber.Law` |
| `cointrade` | v2.1.2 | master | `/cointrade` |
| `bobcoin` | v1.2.0 | main | `/bobcoin` |
| `bobeditpro` | v2.1.0 | master | `/bobeditpro` |
| `Alti.Code.Studio` | v1.5.0 | main | `/Alti.Code.Studio` |
| `mcp-superassistant` | v0.6.0 | main | `/mcp-superassistant` |
| `redprints` | v0.56.0 | main | `/redprints` |

*(Note: Hundreds of nested submodules are actively maintained by the background `sync_and_merge.py` process.)*
