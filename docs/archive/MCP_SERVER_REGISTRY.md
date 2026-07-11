# MCP Server Registry

**Last Updated**: November 4, 2025  
**Last Test**: November 4, 2025 - All servers tested and working! 🎉

**Purpose**: Track useful MCP servers found from Edge tabs and other sources

---

## 🎯 Quick Summary (November 4, 2025 Test)

**Total Servers Tested**: 7  
**Working**: 7/7 (100%) ✅  
**Failed**: 0 ❌

**Top 4 for Web Development** (⭐⭐⭐⭐⭐):
1. **Chrome DevTools MCP** - Browser testing, automation, debugging
2. **Tavily Search** - Real-time documentation & best practices
3. **Zen MCP** - 70+ AI models (GPT-5, Gemini 2.5 Pro, Grok-4, etc.)
4. **Serena** - Intelligent code navigation & editing

**Detailed Test Results**: See `MCP_SERVER_TEST_RESULTS.md`  
**Screenshot**: `fwber/fwber-frontend/MCP_TEST_RESULTS.png`

---

## Quick Add Template

```markdown
### Server Name
- **Type**: [AI Model/Development Tool/Database/etc.]
- **Source**: [Edge tab URL or source]
- **Status**: [Found/Testing/Working/Failed]
- **Notes**: [Quick notes on usefulness]
- **Config Location**: [Where to add it]
```

---

## Found Servers

*Add entries as you discover them in your tabs*

---

## Currently Working (Verified November 4, 2025)

### chroma-knowledge
- **Type**: Knowledge Base / Vector Database
- **Status**: ✅ Working
- **Command**: `C:\Users\hyper\workspace\chroma\.venv\Scripts\chroma-mcp.exe`
- **Tools**: 14 tools (add_documents, query_documents, etc.)
- **Web Dev Rating**: ⭐⭐⭐ (3/5) - Good for project knowledge storage

### serena
- **Type**: Code Intelligence / Memory
- **Status**: ✅ Working
- **Command**: `C:\Users\hyper\workspace\serena\.venv\Scripts\serena-mcp-server.exe`
- **Tools**: 22 tools (find_symbol, code analysis, memory management)
- **Web Dev Rating**: ⭐⭐⭐⭐⭐ (5/5) - Essential for large codebases

### zen-mcp-server
- **Type**: AI Orchestration / Multi-Model
- **Status**: ✅ Working ✅ TESTED
- **Command**: `C:\Users\hyper\workspace\zen-mcp-server\.venv\Scripts\zen-mcp-server.exe`
- **Tools**: 17 tools (chat, consensus, debug, codereview, etc.)
- **Models**: 70+ models (GPT-5 Pro, Gemini 2.5 Pro, Grok-4, Claude Opus, etc.)
- **Web Dev Rating**: ⭐⭐⭐⭐⭐ (5/5) - Multi-AI expertise for any problem
- **Test Results**: Successfully provided Sentry optimization advice via Gemini Flash

### tavily-mcp (Tavily Search & Extract)
- **Type**: Web Search / Content Extraction
- **Status**: ✅ Working ✅ TESTED
- **Tools**: search, extract, crawl, map
- **Web Dev Rating**: ⭐⭐⭐⭐⭐ (5/5) - Essential for current documentation
- **Test Results**: Successfully searched "Next.js 14 Sentry best practices 2025"
- **Quality**: Returned high-quality results from Sentry docs, Medium, Stack Overflow

### chrome-devtools-mcp
- **Type**: Browser Automation / Testing
- **Status**: ✅ Working ✅ TESTED
- **Tools**: navigate, snapshot, click, screenshot, console logs, network requests
- **Web Dev Rating**: ⭐⭐⭐⭐⭐ (5/5) - Game-changer for testing
- **Test Results**: 
  - ✅ Navigated to localhost:3002/sentry-test
  - ✅ Captured accessibility snapshot
  - ✅ Clicked test button programmatically
  - ✅ Read console errors
  - ✅ Took screenshot
- **Screenshot**: See MCP_TEST_RESULTS.png

### filesystem-mcp
- **Type**: File Operations
- **Status**: ✅ Working ✅ TESTED
- **Tools**: read_file, read_multiple_files, list_directory, etc.
- **Web Dev Rating**: ⭐⭐⭐⭐ (4/5) - Quick file access
- **Test Results**: Successfully read package.json

### memory (Knowledge Graph)
- **Type**: Knowledge Storage / Entity Relations
- **Status**: ✅ Working ✅ TESTED (empty graph)
- **Tools**: search_nodes, open_nodes, create_entities, create_relations
- **Web Dev Rating**: ⭐⭐⭐ (3/5) - Needs population, good potential
- **Test Results**: Search worked but returned empty (no data stored yet)

---

## ⚠️ Issues to Fix

### tavily-remote-mcp
- **Status**: ⚠️ Disabled (not needed - local tavily-mcp works perfectly)

### Other potential servers
- Check Edge tabs for additional MCP servers to test

---

## Categorized by Type

### 🌐 Web Search & Content (Tier 1 - Essential)
- **tavily-mcp** ✅ ⭐⭐⭐⭐⭐ (search, extract, crawl, map)

### 🔍 Browser Automation & Testing (Tier 1 - Essential)
- **chrome-devtools-mcp** ✅ ⭐⭐⭐⭐⭐ (navigate, click, snapshot, screenshot, console, network)

### 🧠 AI Models & Orchestration (Tier 1 - Essential)
- **zen-mcp-server** ✅ ⭐⭐⭐⭐⭐ (70+ models, chat, consensus, codereview, debug)

### 💻 Code Intelligence (Tier 1 - Essential)
- **serena** ✅ ⭐⭐⭐⭐⭐ (symbolic navigation, find_symbol, smart editing)

### 📁 File Operations (Tier 2 - Very Useful)
- **filesystem-mcp** ✅ ⭐⭐⭐⭐ (read, write, move, list, search)

### 🧩 Knowledge Bases (Tier 3 - Specialized)
- **chroma-knowledge** ✅ ⭐⭐⭐ (vector DB, documents, embeddings)
- **memory** ✅ ⭐⭐⭐ (knowledge graph, entities, relations)

### 🔮 To Test
- Playwright MCP (if available)
- Database MCPs
- Git/GitHub MCPs
- Testing MCPs (Jest, Vitest)

---

## Configuration File Locations

### Codex
- **Config**: `C:\Users\hyper\.codex\config.toml`
- **MCP Settings**: In config.toml under `[mcp_servers]`

### Cursor
- **MCP Config**: `C:\Users\hyper\.cursor\mcp.json`
- **Alternative**: `.kilocode/mcp.json` (may be empty - sync with templates)
- **Templates**: `tools_config_files/cursor_mcp.json`, `enhanced_mcp_settings.json`

### Claude
- **CLI Config**: `C:\Users\hyper\.claude.json`
- **Desktop Config**: `C:\Users\hyper\AppData\Roaming\Claude\claude_desktop_config.json`
- **Claude Dev**: `C:\Users\hyper\AppData\Roaming\Cursor\User\globalStorage\saoudrizwan.claude-dev\settings\cline_mcp_settings.json`

### Notepad++
*Add location when found*

---

## Notes Section

*Use this space for quick thoughts, patterns noticed, or decisions about which servers to prioritize*

### VSCode Insiders + Copilot/GPT-5 Analysis
- Analyzing C drive for MCP servers and tools
- Cross-reference findings with Edge tab discoveries

