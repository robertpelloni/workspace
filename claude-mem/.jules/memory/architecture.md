# Hypercode Extension (formerly Claude-Mem) Architecture Summary

## 1. Core Architecture and Concept
Hypercode Extension is a persistent memory compression system built for AI coding assistants (originally Claude Code, but expanding to Copilot and others via `openclaw` and MCP).

**System Layers:**
1. **Host Integration Layer:** Hooks (e.g., in Claude Code via `.claude-plugin` hooks or VS Code extension) intercept events like session start, user prompts, tool executions, and session termination.
2. **CLI / Bridge Layer:** Scripts (like `hook-command.ts`) execute quickly to send data to the backend.
3. **Worker Daemon:** A central server (`src/services/worker-service.ts`) running on port `37777`. It handles memory processing asynchronously without blocking the user's workflow. It uses Express to expose HTTP and SSE (Server-Sent Events) routes.
4. **Storage Layer:**
   - **SQLite (`claude-mem.db`)**: Stores relational structured data (sessions, observations, user prompts, session summaries, and a pending message queue). It uses `bun:sqlite` or `better-sqlite3`.
   - **ChromaDB (`chroma.sqlite3`)**: An external vector database used for semantic search embeddings. Handled by `ChromaSync` and `ChromaMcpManager`.
   - **FTS5**: SQLite's Full-Text Search is heavily utilized.
5. **AI Processing Layer:** A background SDK Agent (Anthropic Claude Agent SDK, OpenRouterAgent, GeminiAgent) acts as a summarizer and semantic processor. It takes raw tool output and "compresses" it into smaller observations.

## 2. Key Patterns

### The CLAIM-CONFIRM Queue (PendingMessageStore)
To ensure observations are not lost when the host shuts down, the CLI writes messages to a SQLite queue (`pending_messages`) with a status of `pending`. The Worker claims them (updating to `processing`), processes them through the SDK agent, and deletes them upon success. Failed messages are marked `failed` and retried.

### Dual Session ID Architecture
- **`contentSessionId`:** The immutable ID given by the Host (e.g. Claude Code conversation ID).
- **`memorySessionId`:** A dynamically generated ID by the background SDK agent (or a synthesized fallback ID).
This split prevents cross-contamination. Foreign Keys in the database (like for observations) tie back to `memorySessionId`.

### Circuit Breaker & Graceful Degradation
- If the AI generator crashes repeatedly, a circuit breaker trips to prevent infinite retry loops.
- The CLI hooks are designed to fail silently (`exit 0` for transport errors) so the user's active AI chat session is never blocked by a backend memory failure.

### Deduplication
Observations are deduplicated by generating a 16-character hex hash from the session ID, title, and narrative. 

### Server-Sent Events (SSE)
The `SSEBroadcaster` sends live logs and status updates to connected UI viewers (like the React dashboard).

## 3. Database Schema (SQLite)
* `sdk_sessions`: Tracks lifecycle (`content_session_id`, `memory_session_id`, `status`).
* `observations`: Tool usage results (`memory_session_id`, `type`, `title`, `narrative`, `content_hash`).
* `session_summaries`: Final output (`request`, `learned`, `completed`).
* `user_prompts`: History of prompts typed by the user.
* `pending_messages`: The async job queue.
* `observation_feedback`: Explicit signals from the user.

## 4. Current State & Implementation Details
- The codebase is overwhelmingly written in TypeScript (`src/`, `tests/`, `plugin/`, `vscode-extension/`).
- The transition to Bun from PM2 for process management is complete (version 7.1.0+).
- Current repository tag is roughly `v12.1.0` (on the `main` branch).
- Submodules/Plugins exist: `opencode-plugin` (OpenCode integration), `openclaw`, `vscode-extension` (Copilot extension), and the main UI dashboard.

## 5. Path to Go Port
To port this effectively to Go, the architecture implies:
1. **Storage/SQLite:** Porting the schema, migrations, `SessionStore`, and `PendingMessageStore` to use `mattn/go-sqlite3` or `ncruces/go-sqlite3`.
2. **Worker Daemon:** Creating a Go HTTP server with equivalent Express endpoints (`DataRoutes`, `SessionRoutes`, `SearchRoutes`) and the `SSEBroadcaster`.
3. **Queue Processing:** Implementing a goroutine worker pool mimicking the CLAIM-CONFIRM queue loop.
4. **Agent Integration:** A Go-based wrapper to call Anthropic/OpenRouter/Gemini to replace the JS SDK logic.