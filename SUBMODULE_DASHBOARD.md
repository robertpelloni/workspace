# Submodule Dashboard & Project Structure
**Last Updated:** 2026-02-24 15:30:00

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
| **Root Workspace** | 1.3.4 | main | `/` |
| `antigravity-autopilot` | v5.2.56 | main | `/antigravity-autopilot` |
| `jules-autopilot` | v0.8.9 | main | `/jules-autopilot` |
| `borg` | v2.7.1 | main | `/borg` |
| `metamcp` | v3.7.1 | main | `/metamcp` |
| `Chamber.Law` | v1.0.2 | main | `/Chamber.Law` |
| `cointrade` | v2.1.3 | master | `/cointrade` |
| `bobcoin` | v1.2.1 | main | `/bobcoin` |
| `bobeditpro` | v2.1.1 | master | `/bobeditpro` |
| `Alti.Code.Studio` | v1.5.1 | main | `/Alti.Code.Studio` |
| `mcp-superassistant` | v0.6.1 | main | `/mcp-superassistant` |
| `redprints` | v0.56.1 | main | `/redprints` |

*(Note: Hundreds of nested submodules are actively maintained by the background `update_repos_v5.py` process. As of v1.3.4, all local feature branches and upstream forks have been completely synchronized, intelligently merged, and resolved against main/master branches without losing progress.)*
