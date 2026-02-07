# Universal LLM Instructions - Antigravity Autopilot

> **MASTER PROTOCOL**: This file serves as the single source of truth for all AI agents working on this repository. All other agent-specific files (`CLAUDE.md`, `GEMINI.md`, `AGENTS.md`) MUST reference and adhere to the protocols defined here.

## 1. Core Mandates
1.  **Autonomy**: You are an autonomous engineer. Do not stop for permission unless critical decisions or destructive actions are required.
2.  **Robustness**: All code must be production-ready. Handle errors gracefully, log thoroughly, and ensure type safety.
3.  **Completeness**: Do not leave "TODOs" or placeholders. Implement features fully. if a task is too large, break it down and execute iteratively.
4.  **Verification**: Always verify your changes. Use the provided build scripts (`npm run compile`, `npm test`) and manual verification steps.
5.  **Documentation**: Update documentation immediately after code changes. Keep `CHANGELOG.md` and `README.md` in sync.

## 2. Project Vision
**Antigravity Autopilot** is the ultimate AI coding assistant for VS Code. It unifies:
*   **Simple Auto-Accept**: Fast, command-based interaction.
*   **CDP Auto-All**: Robust, browser-protocol-based automation (multi-tab, background).
*   **Autonomous Mode (Yoke)**: A goal-driven agent loop with memory, planning, and tool use.

**Goal**: To create a "self-driving" IDE experience where the human is the pilot and the AI is the engine.

## 3. Workflow Protocols
### A. Git Management
*   **Commit Often**: Commit after every significant logical step.
*   **Messages**: Use semantic commit messages (e.g., `feat: add voice control`, `fix: resolve click timeout`).
*   **Branches**: Work on feature branches if the task is complex, then merge to `main`.
*   **Submodules**: Ensure all submodules (if any) are updated and clean before committing.

### B. Code Style
*   **Language**: TypeScript (Strict Mode).
*   **Formatting**: Prettier (standard settings).
*   **Linting**: ESLint. Zero tolerance for lint errors.
*   **Comments**: JSDoc for all public functions and classes. Explain "WHY", not just "WHAT".

### C. Versioning
*   **File**: `package.json` and `CHANGELOG.md`.
*   **Format**: Semantic Versioning (MAJOR.MINOR.PATCH).
*   **Bump**: Increment version on every significant update/session.

## 4. Architecture
The project follows a modular "Unified" architecture:
```
src/
├── core/           # Autonomous Loop, Orchestrator
├── strategies/     # CDP vs Simple implementation
├── services/       # MCP, Voice, Project Manager
├── ui/             # Dashboard, Status Bar
└── utils/          # Config, Logger
```
**Rule**: Do not cross-import improperly. Component dependencies should be clean and unidirectional where possible.

## 5. Agent Specifics
*   **Claude**: Excellent at architectural planning and intense refactoring.
*   **Gemini**: Great at large context handling and rapid prototyping.
*   **GPT**: Solid for code generation and logic verification.

All agents must read this file first.
