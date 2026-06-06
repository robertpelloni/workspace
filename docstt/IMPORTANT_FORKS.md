# Important Forked Projects Reference

**Created:** 2026-01-09  
**Purpose:** Document projects that were forked because of their exceptional functionality for future research and reimplementation.

---

## Overview

These projects were forked to Robert Pelloni's GitHub because their functionality seemed particularly important. The forks have now been switched to upstream URLs, but their features and patterns should be carefully researched and potentially reimplemented in the core workspace projects.

---

## MCP (Model Context Protocol) Servers

### High Priority - Core Infrastructure

| Project | Upstream | Why It's Important |
|---------|----------|-------------------|
| **Super-MCP** | nspr-io/Super-MCP | Meta-MCP server that orchestrates other MCPs - core to aios architecture |
| **mcphub** | samanhappy/mcphub | Hub for discovering and managing MCP servers |
| **mcpproxy-go** | smart-mcp-proxy/mcpproxy-go | Go-based proxy for MCP connections - critical for routing |
| **mcp-cli** | apify/mcp-cli | Command-line interface for MCP operations |
| **mcpm.sh** | pathintegral-institute/mcpm.sh | Package manager for MCP servers - installation automation |
| **mcp-tool-chainer** | thirdstrandstudio/mcp-tool-chainer | Chain MCP tools together - pipeline execution |
| **lazy-mcp** | machjesusmoto/lazy-mcp | Lazy loading for MCP tools - reduces memory footprint |
| **MCP-Zero** | xfey/MCP-Zero | Minimal MCP implementation - reference for custom servers |
| **Polymcp** | poly-mcp/Polymcp | Multi-language MCP SDK |

### Medium Priority - Specialized Features

| Project | Upstream | Why It's Important |
|---------|----------|-------------------|
| **pluggedin-mcp** | VeriTeknik/pluggedin-mcp | Plugin system for MCP - extensibility |
| **pluggedin-app** | VeriTeknik/pluggedin-app | Web UI for MCP management |
| **notebooklm-mcp** | roomi-fields/notebooklm-mcp | NotebookLM integration - research automation |
| **voicemode** | mbailey/voicemode | Voice interaction for AI agents |
| **pctx** | portofcontext/pctx | Context injection for AI tools |
| **pal-mcp-server** | BeehiveInnovations/pal-mcp-server | Personal assistant MCP server |
| **mcp-server-code-execution-mode** | elusznik/mcp-server-code-execution-mode | Safe code execution sandbox |

---

## AI Agents & Orchestration

| Project | Upstream | Why It's Important |
|---------|----------|-------------------|
| **claude-squad** | smtg-ai/claude-squad | Multi-agent orchestration using tmux - key for agent swarms |
| **smolagents** | huggingface/smolagents | HuggingFace's agent framework - reference implementation |
| **reag** | superagent-ai/reag | React-based agent UI framework |
| **claudex** | Mng-dev-ai/claudex | Claude CLI extensions |
| **Auditor** | TheAuditorTool/Auditor | Code auditing agent - security analysis |
| **jules-agent-sdk-python** | AsyncFuncAI/jules-agent-sdk-python | Python SDK for Jules-style agents |
| **magg** | sitbon/magg | Agent graph framework |

---

## Developer Tools

| Project | Upstream | Why It's Important |
|---------|----------|-------------------|
| **emdash** | generalaction/emdash | CLI dashboard framework - could enhance aios CLI |
| **mux** | coder/mux | Terminal multiplexer for dev environments |
| **superpowers** | obra/superpowers | IDE enhancements for AI-assisted coding |
| **Puzld.ai** | MedChaouch/Puzld.ai | Puzzle-based AI interface |

---

## Rhythm Games

| Project | Upstream | Why It's Important |
|---------|----------|-------------------|
| **lr2oraja** | wcko87/lr2oraja | LR2 BMS player enhancement - beatoraja compatibility |
| **lr2oraja-endlessdream** | seraxis/lr2oraja-endlessdream | Extended LR2 features - replay system |
| **BeatDrop** | mvsoft74/BeatDrop | BeatSaber level manager - could adapt for StepMania |

---

## Graphics & Visualization

| Project | Upstream | Why It's Important |
|---------|----------|-------------------|
| **nanovg** | memononen/nanovg | Lightweight vector graphics - UI rendering |
| **bonsai** | scallyw4g/bonsai | Fractal tree generation - visual effects |
| **Depixelization_poc** | spipm/Depixelization_poc | AI upscaling for pixel art - retro game enhancement |

---

## Other Notable Forks

| Project | Upstream | Why It's Important |
|---------|----------|-------------------|
| **codebuff** | CodebuffAI/codebuff | AI code generation patterns |
| **CodeMachine-CLI** | moazbuilds/CodeMachine-CLI | CLI code generation |
| **mcpr** | jrandolf/mcpr | MCP registry client |
| **vibekit-nextjs-supabase** | superagent-ai/vibekit-nextjs-supabase | Full-stack AI app template |
| **checkedc** | checkedc/checkedc | Type-safe C extensions - security |

---

## Research Priority

### Immediate Research (for aios Phase 8)
1. **Super-MCP** - Core orchestration patterns
2. **claude-squad** - Multi-agent tmux architecture
3. **mcp-tool-chainer** - Tool pipeline implementation
4. **lazy-mcp** - Lazy loading strategies

### Secondary Research (for Phase 9+)
1. **smolagents** - HuggingFace agent patterns
2. **mcphub** - Server discovery mechanisms
3. **voicemode** - Voice interface integration
4. **nanovg** - UI rendering optimization

### Long-term Reference
1. **Depixelization_poc** - ML upscaling for okgame/BobsGameOnline
2. **BeatDrop** - Level management patterns for rhythm games
3. **checkedc** - Security patterns for C++ projects

---

## Notes

- All upstream URLs have been updated in `.gitmodules` files
- Original forks may be deleted from robertpelloni GitHub once upstream sync is confirmed
- Features from these projects should be abstracted and integrated, not copied directly
- Maintain attribution when implementing derived features
