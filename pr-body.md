## Summary

Adds a generic runtime extension system to CodeWhale, inspired by the Pi Coding Agent's ExtensionAPI pattern. Extensions can hook into the agent lifecycle (session start, tool calls, turn end, etc.) and register MCP servers, slash commands, keyboard shortcuts, and custom tools.

## New crate: `codewhale-extension`

- **Extension trait** with 12 lifecycle hooks: SessionStart, BeforeAgentStart, ToolCall, ToolResult, TurnEnd, Input, UserBash, ModelSelect, SessionBeforeCompact, SessionCompact, SessionShutdown
- **ExtensionManager** — registers extensions, dispatches events, collects MCP servers/commands/shortcuts/tools
- **HookResult** — allows extensions to modify system prompts, transform user input, or suppress default behavior
- **Generic types** — McpServerDef, SlashCommandDef, ShortcutDef, ToolDef
- **Prelude** — easy imports via `use codewhale_extension::prelude::*`

## Additional fix

- **Ctrl+Up/Down** keybinding now scrolls the transcript by 1 line (was unhandled, falling through to vim_move_up/down)

## Example

```rust
use codewhale_extension::prelude::*;

struct MyLogger;
#[async_trait]
impl Extension for MyLogger {
    fn name(&self) -> &str { "logger" }
    async fn on_event(&self, event: &HookEvent) -> HookResult {
        match event {
            HookEvent::ToolCall { tool_name, .. } => {
                eprintln!("Tool called: {tool_name}");
            }
            _ => {}
        }
        HookResult::default()
    }
}
```

## Integration points (documented in code)

The Extension events map to CodeWhale's engine at these locations:
- `engine.rs: handle_send_message` -> BeforeAgentStart
- `engine/tool_execution.rs: execute_tool_with_lock` -> ToolCall/ToolResult
- `engine/turn_loop.rs` -> TurnEnd
- `session_manager.rs` -> SessionStart
- `ui.rs` -> Input transformation

These integration points are documented but NOT yet activated — they require wiring the ExtensionManager into the Engine struct and calling `dispatch()` at each lifecycle point.
