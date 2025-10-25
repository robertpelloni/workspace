@echo off
REM Batch script to create symbolic links for all MCP configuration files
REM Run this script as Administrator

cd /d "C:\Users\hyper\fwber\tools_config_files"

echo Creating symbolic links for MCP configuration files...

REM Claude CLI
if exist "C:\Users\hyper\.claude.json" (
    if exist "claude.json" del "claude.json"
    mklink "claude.json" "C:\Users\hyper\.claude.json"
    echo Created: claude.json
) else (
    echo Target not found: C:\Users\hyper\.claude.json
)

REM Cursor MCP
if exist "C:\Users\hyper\.cursor\mcp.json" (
    if exist "cursor_mcp.json" del "cursor_mcp.json"
    mklink "cursor_mcp.json" "C:\Users\hyper\.cursor\mcp.json"
    echo Created: cursor_mcp.json
) else (
    echo Target not found: C:\Users\hyper\.cursor\mcp.json
)

REM Cline MCP Settings
if exist "C:\Users\hyper\AppData\Roaming\Cursor\User\globalStorage\saoudrizwan.claude-dev\settings\cline_mcp_settings.json" (
    if exist "cline_mcp_settings.json" del "cline_mcp_settings.json"
    mklink "cline_mcp_settings.json" "C:\Users\hyper\AppData\Roaming\Cursor\User\globalStorage\saoudrizwan.claude-dev\settings\cline_mcp_settings.json"
    echo Created: cline_mcp_settings.json
) else (
    echo Target not found: Cline MCP settings
)

REM Codex Config
if exist "C:\Users\hyper\.codex\config.toml" (
    if exist "codex_config.toml" del "codex_config.toml"
    mklink "codex_config.toml" "C:\Users\hyper\.codex\config.toml"
    echo Created: codex_config.toml
) else (
    echo Target not found: C:\Users\hyper\.codex\config.toml
)

REM Gemini Settings
if exist "C:\Users\hyper\.gemini\settings.json" (
    if exist "gemini_settings.json" del "gemini_settings.json"
    mklink "gemini_settings.json" "C:\Users\hyper\.gemini\settings.json"
    echo Created: gemini_settings.json
) else (
    echo Target not found: C:\Users\hyper\.gemini\settings.json
)

REM Copilot MCP Config
if exist "C:\Users\hyper\.copilot\mcp-config.json" (
    if exist "copilot_mcp_config.json" del "copilot_mcp_config.json"
    mklink "copilot_mcp_config.json" "C:\Users\hyper\.copilot\mcp-config.json"
    echo Created: copilot_mcp_config.json
) else (
    echo Target not found: C:\Users\hyper\.copilot\mcp-config.json
)

REM Grok Settings
if exist "C:\Users\hyper\.grok\settings.json" (
    if exist "grok_settings.json" del "grok_settings.json"
    mklink "grok_settings.json" "C:\Users\hyper\.grok\settings.json"
    echo Created: grok_settings.json
) else (
    echo Target not found: C:\Users\hyper\.grok\settings.json
)

REM WebStorm MCP Servers
if exist "C:\Users\hyper\AppData\Roaming\JetBrains\WebStorm2025.3\options\llm.mcpServers.xml" (
    if exist "webstorm_llm_mcpServers.xml" del "webstorm_llm_mcpServers.xml"
    mklink "webstorm_llm_mcpServers.xml" "C:\Users\hyper\AppData\Roaming\JetBrains\WebStorm2025.3\options\llm.mcpServers.xml"
    echo Created: webstorm_llm_mcpServers.xml
) else (
    echo Target not found: WebStorm MCP servers
)

REM Claude Desktop Config
if exist "C:\Users\hyper\AppData\Roaming\Claude\claude_desktop_config.json" (
    if exist "claude_desktop_config.json" del "claude_desktop_config.json"
    mklink "claude_desktop_config.json" "C:\Users\hyper\AppData\Roaming\Claude\claude_desktop_config.json"
    echo Created: claude_desktop_config.json
) else (
    echo Target not found: Claude Desktop config
)

REM GitHub Copilot IntelliJ MCP
if exist "C:\Users\hyper\AppData\Local\github-copilot\intellij\mcp.json" (
    if exist "github_copilot_intellij_mcp.json" del "github_copilot_intellij_mcp.json"
    mklink "github_copilot_intellij_mcp.json" "C:\Users\hyper\AppData\Local\github-copilot\intellij\mcp.json"
    echo Created: github_copilot_intellij_mcp.json
) else (
    echo Target not found: GitHub Copilot IntelliJ MCP
)

REM Grok User Settings
if exist "C:\Users\hyper\.grok\user-settings.json" (
    if exist "grok_user_settings.json" del "grok_user_settings.json"
    mklink "grok_user_settings.json" "C:\Users\hyper\.grok\user-settings.json"
    echo Created: grok_user_settings.json
) else (
    echo Target not found: Grok user settings
)

REM Serena Config
if exist "C:\Users\hyper\.serena\serena_config.yml" (
    if exist "serena_config.yml" del "serena_config.yml"
    mklink "serena_config.yml" "C:\Users\hyper\.serena\serena_config.yml"
    echo Created: serena_config.yml
) else (
    echo Target not found: Serena config
)

REM Code Config
if exist "C:\Users\hyper\.code\config.toml" (
    if exist "code_config.toml" del "code_config.toml"
    mklink "code_config.toml" "C:\Users\hyper\.code\config.toml"
    echo Created: code_config.toml
) else (
    echo Target not found: Code config
)

REM Gemini MCP Config
if exist "C:\Users\hyper\.gemini\mcp-config.json" (
    if exist "gemini_mcp_config.json" del "gemini_mcp_config.json"
    mklink "gemini_mcp_config.json" "C:\Users\hyper\.gemini\mcp-config.json"
    echo Created: gemini_mcp_config.json
) else (
    echo Target not found: Gemini MCP config
)

REM Lingma MCP
if exist "C:\Users\hyper\.lingma\lingma_mcp.json" (
    if exist "lingma_mcp.json" del "lingma_mcp.json"
    mklink "lingma_mcp.json" "C:\Users\hyper\.lingma\lingma_mcp.json"
    echo Created: lingma_mcp.json
) else (
    echo Target not found: Lingma MCP
)

REM LM Studio MCP
if exist "C:\Users\hyper\.lmstudio\mcp.json" (
    if exist "lmstudio_mcp.json" del "lmstudio_mcp.json"
    mklink "lmstudio_mcp.json" "C:\Users\hyper\.lmstudio\mcp.json"
    echo Created: lmstudio_mcp.json
) else (
    echo Target not found: LM Studio MCP
)

REM Qwen Settings
if exist "C:\Users\hyper\.qwen\settings.json" (
    if exist "qwen_settings.json" del "qwen_settings.json"
    mklink "qwen_settings.json" "C:\Users\hyper\.qwen\settings.json"
    echo Created: qwen_settings.json
) else (
    echo Target not found: Qwen settings
)

REM Witsy Settings
if exist "C:\Users\hyper\AppData\Roaming\Witsy\settings.json" (
    if exist "witsy_settings.json" del "witsy_settings.json"
    mklink "witsy_settings.json" "C:\Users\hyper\AppData\Roaming\Witsy\settings.json"
    echo Created: witsy_settings.json
) else (
    echo Target not found: Witsy settings
)

REM Kilo Code MCP Settings
if exist "C:\Users\hyper\AppData\Roaming\Cursor\User\globalStorage\kilocode.kilo-code\settings\mcp_settings.json" (
    if exist "kilo_code_mcp_settings.json" del "kilo_code_mcp_settings.json"
    mklink "kilo_code_mcp_settings.json" "C:\Users\hyper\AppData\Roaming\Cursor\User\globalStorage\kilocode.kilo-code\settings\mcp_settings.json"
    echo Created: kilo_code_mcp_settings.json
) else (
    echo Target not found: Kilo Code MCP settings
)

echo.
echo Symbolic link creation completed!
echo You can now add these files to git tracking.
pause
