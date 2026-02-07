# Universal LLM Instructions

This file contains the core instructions for all AI models working on **BobsGameOnline**. All models (Claude, Copilot, Gemini, GPT, etc.) must adhere to these protocols.

## Project Context
*   **Language**: Java (Modern versions preferred, currently Java 21).
*   **Build System**: Gradle 8.8.
*   **Key Libraries**: LWJGL 3, GeoIP2, LZ4, JInput, TWL.
*   **Architecture**: Client-Server model with Lua scripting support.

## Workflow Protocols

### 1. Version Control & Branching
*   **Commit Messages**: Clear, descriptive, imperative mood (e.g., "Add feature X", "Fix bug Y").
*   **Submodules**: Always check for submodule updates when pulling. Use `git submodule update --init --recursive`.
*   **Branches**: Create feature branches for new work. Merge to `main` via PR or direct merge if authorized.
*   **Syncing**: Regularly sync with the remote repository. Fetch, pull, and merge upstream changes (including forks) before starting new work.

### 2. Versioning & Changelog (CRITICAL)
*   **Source of Truth**: `VERSION.md` contains the current version number (e.g., `0.1.3`).
*   **Updates**:
    *   **Every significant change, build, or feature implementation MUST increment the version number.**
    *   Update `CHANGELOG.md` with a new entry under the new version.
    *   **Commit Protocol**: When the version number is updated, perform a git commit and push immediately. The commit message **MUST** explicitly reference the version bump (e.g., "Bump version to 0.1.4").
    *   **Code Integration**: Internal code MUST reference `VERSION.md` (or a generated resource file derived from it) rather than hardcoding version strings.
    *   **User Interface**: If the program has a UI, the version number must be displayed prominently and synchronized with `VERSION.md`.

### 3. Documentation & Dashboard
*   **Dashboard**: Maintain `docs/dashboard.md` as a live status report. It must list:
    *   All submodules with their versions/commits.
    *   Project directory structure explanation.
    *   Build status.
*   **Roadmap**: Keep `ROADMAP.md` updated. Move completed items to "Completed" and add new findings to "Planned" or "Backlog".
*   **Handoff**: When finishing a session, create a `HANDOFF.md` summarizing the state, changes, and next steps.

### 4. Code Style
*   Follow standard Java naming conventions.
*   Prioritize readability and maintainability.
*   Add Javadoc for public methods and classes.
*   Use meaningful variable names.

## Model-Specific Instructions
*   **Claude**: Refer to `CLAUDE.md` (Appends to this file).
*   **Copilot**: Refer to `.github/copilot-instructions.md` (Appends to this file).
*   **Gemini**: Refer to `GEMINI.md` (Appends to this file).
*   **GPT**: Refer to `GPT.md` (Appends to this file).
*   **Agents**: Refer to `AGENTS.md` (Appends to this file).
