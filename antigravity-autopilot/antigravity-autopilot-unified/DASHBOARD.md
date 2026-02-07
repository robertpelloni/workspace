# Antigravity Autopilot Dashboard

**Version**: 4.0.0
**Build Date**: 2026-02-07

## Directory Structure
The project is organized as a unified extension with modular components.

| Component | Location | Description |
| :--- | :--- | :--- |
| **Root** | `c:\Users\hyper\workspace\antigravity-autopilot` | Parent workspace directory. |
| **Unified Core** | `antigravity-autopilot-unified/` | **The Main Extension**. Contains all active development. |
| **Active Source** | `antigravity-autopilot-unified/src/` | TypeScript source code. |
| **Browser Scripts** | `antigravity-autopilot-unified/main_scripts/` | JS injected into VS Code via CDP. |
| **Docs** | `antigravity-autopilot-unified/docs/` | Universal instructions and references. |
| **Legacy/Reference** | `AUTO-ALL-AntiGravity/` | Original CDP implementation (Reference). |
| **Legacy/Reference** | `antigravity-auto-accept/` | Simple command implementation (Reference). |
| **Legacy/Reference** | `yoke-antigravity/` | Original autonomous logic (Reference). |

## Module Status (Unified Extension)

| Module | Status | Version | Notes |
| :--- | :--- | :--- | :--- |
| **Core Loop** | ✅ Active | 4.0.0 | Full autonomous cycle implemented. |
| **CDP Strategy** | ✅ Active | 4.0.0 | Supports multi-tab & background mode. |
| **Simple Strategy** | ✅ Active | 4.0.0 | Fallback command-based mode. |
| **Project Manager** | ✅ Active | 4.0.0 | Jira/GitHub sync operational. |
| **MCP Client** | ✅ Active | 4.0.0 | Integrated with local MCP servers. |
| **Voice Control** | ✅ Active | 4.0.0 | Push-to-talk/Always-listening modes. |

## Quick Links
*   [Vision & Roadmap](./VISION.md)
*   [Changelog](./CHANGELOG.md)
*   [Universal Instructions](./docs/LLM_INSTRUCTIONS.md)
