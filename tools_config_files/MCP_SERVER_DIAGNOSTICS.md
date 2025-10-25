# MCP Server Diagnostics and Troubleshooting

## Test Date: 2025-01-12

## MCP Server Status Overview

### ❌ **Critical Issues Identified**

#### **1. JetBrains MCP Server**
- **Error:** "Connection refused: getsockopt" / "Connection closed"
- **Port:** 64342 (SSE connection)
- **Status:** ❌ FAILING across all CLI tools
- **Impact:** Blocks JetBrains IDE integration

#### **2. Serena MCP Server**
- **Error:** "request timed out"
- **Command:** `uv run --directory C:\Users\hyper\serena\ serena start-mcp-server`
- **Status:** ❌ FAILING in Codex CLI
- **Impact:** Blocks memory and project coordination features

#### **3. Sequential Thinking MCP Server**
- **Error:** "request timed out"
- **Command:** `npx -y @modelcontextprotocol/server-sequential-thinking`
- **Status:** ❌ FAILING in Codex CLI
- **Impact:** Blocks structured reasoning capabilities

#### **4. Gemini MCP Tool Server**
- **Error:** "request timed out"
- **Command:** `npx -y gemini-mcp-tool`
- **Status:** ❌ FAILING in Codex CLI
- **Impact:** Blocks Gemini model integration via MCP

### ✅ **Working MCP Server**

#### **Codex MCP Server (in Copilot CLI)**
- **Status:** ✅ WORKING
- **Message:** "codex-mcp-server started successfully"
- **Tool:** GitHub Copilot CLI
- **Impact:** Enables Codex integration in Copilot

## Root Cause Analysis

### **1. JetBrains MCP Server Issues**
**Problem:** WebStorm MCP server not running or not accessible
**Possible Causes:**
- WebStorm not running
- MCP server plugin not installed/activated
- Port 64342 blocked or in use
- Java classpath issues

**Investigation Steps:**
1. Check if WebStorm is running
2. Verify MCP server plugin is installed
3. Test port 64342 accessibility
4. Check Java classpath configuration

### **2. Serena MCP Server Issues**
**Problem:** UV/Python environment not accessible
**Possible Causes:**
- UV not installed or not in PATH
- Serena package not installed
- Python environment issues
- Directory permissions

**Investigation Steps:**
1. Verify UV installation: `uv --version`
2. Check Serena package: `uv run serena --version`
3. Test directory access: `C:\Users\hyper\serena\`
4. Check Python environment

### **3. NPM-based MCP Servers Issues**
**Problem:** Sequential Thinking and Gemini MCP tools timing out
**Possible Causes:**
- NPM packages not installed
- Network connectivity issues
- Package compatibility issues
- Node.js version conflicts

**Investigation Steps:**
1. Test NPM access: `npm --version`
2. Check package installation: `npx @modelcontextprotocol/server-sequential-thinking --version`
3. Test network connectivity
4. Verify Node.js version compatibility

## Troubleshooting Commands

### **1. Check JetBrains MCP Server**
```bash
# Check if WebStorm is running
tasklist | findstr "WebStorm"

# Test port accessibility
telnet localhost 64342

# Check Java installation
java -version

# Test MCP server manually
"C:\Program Files\JetBrains\WebStorm 253.25908.30\jbr\bin\java" -classpath "..." com.intellij.mcpserver.stdio.McpStdioRunnerKt
```

### **2. Check Serena MCP Server**
```bash
# Check UV installation
uv --version

# Check Serena package
uv run --directory C:\Users\hyper\serena\ serena --version

# Test Serena MCP server manually
uv run --directory C:\Users\hyper\serena\ serena start-mcp-server --context ide-assistant --project C:\Users\hyper\fwber\
```

### **3. Check NPM-based MCP Servers**
```bash
# Check NPM
npm --version

# Check Node.js
node --version

# Test Sequential Thinking server
npx -y @modelcontextprotocol/server-sequential-thinking

# Test Gemini MCP tool
npx -y gemini-mcp-tool
```

## Configuration Fixes

### **1. Fix JetBrains MCP Server**
**Option A: Use HTTP instead of SSE**
```json
{
  "mcpServers": {
    "jetbrains": {
      "url": "http://localhost:64342/sse"
    }
  }
}
```

**Option B: Ensure WebStorm is running**
- Start WebStorm IDE
- Enable MCP server plugin
- Verify port 64342 is accessible

### **2. Fix Serena MCP Server**
**Check UV Installation:**
```bash
# Install UV if missing
pip install uv

# Install Serena package
uv run --directory C:\Users\hyper\serena\ pip install serena
```

### **3. Fix NPM-based Servers**
**Install Missing Packages:**
```bash
# Install Sequential Thinking server
npm install -g @modelcontextprotocol/server-sequential-thinking

# Install Gemini MCP tool
npm install -g gemini-mcp-tool
```

## Alternative Configurations

### **1. Disable Problematic MCP Servers**
For immediate functionality, disable failing servers:

```json
{
  "mcpServers": {
    "serena": {
      "enabled": false
    },
    "jetbrains": {
      "enabled": false
    },
    "sequential-thinking": {
      "enabled": false
    },
    "gemini-mcp-tool": {
      "enabled": false
    }
  }
}
```

### **2. Use Direct Model Access**
Instead of MCP servers, use direct CLI tool access:
- Codex CLI: `codex exec --model gpt-5-codex`
- Gemini CLI: `gemini -p "prompt"`
- Grok CLI: `grok -p "prompt"`
- Copilot CLI: `copilot -p "prompt"`

## Expected Resolution Timeline

### **Immediate (1-2 hours):**
1. Fix NPM package installations
2. Test Sequential Thinking and Gemini MCP servers
3. Verify UV and Serena installation

### **Short-term (1-2 days):**
1. Resolve JetBrains MCP server connectivity
2. Test all MCP server connections
3. Validate multi-model orchestration

### **Long-term (1 week):**
1. Implement robust error handling
2. Add health checks for MCP servers
3. Create automated troubleshooting scripts

## Success Criteria

- ✅ All MCP servers start without timeout errors
- ✅ CLI tools can connect to their respective MCP servers
- ✅ Multi-model orchestration system fully functional
- ✅ Real AI-to-AI consultation working across all tools

## Next Actions

1. **Run diagnostic commands** to identify specific failure points
2. **Install missing packages** (UV, Serena, NPM packages)
3. **Test individual MCP servers** in isolation
4. **Re-enable MCP servers** once issues are resolved
5. **Validate orchestration system** with working MCP servers
