# Universal Agent Instructions

This document serves as the central source of truth for all AI agents working on the Neverball project.

## Core Directives

1.  **Code Style:**
    *   Use C99 standard.
    *   Follow K&R brace style.
    *   4-space indentation (no tabs).
    *   Prefix global functions with module name (e.g., `game_server_init`).
    *   Memory management: `malloc`/`free` or `realloc`. Ensure cleanup in `_free` functions.

2.  **Architecture:**
    *   **Client-Server:** The engine uses a local client-server model. `game_server.c` runs the simulation; `game_client.c` handles interpolation; `share/cmd.c` handles communication via a ring buffer.
    *   **State Machine:** The game is a stack of states (`struct state`). Transition via `goto_state` or `push_state`.
    *   **Physics:** `share/solid_sim_sol.c` is the physics core. Do not modify unless necessary for global physics changes.

3.  **Versioning:**
    *   Read version from `VERSION` file.
    *   Update `CHANGELOG.md` for every user-facing change.
    *   Bump version number in `VERSION` on every significant feature merge.

4.  **Documentation:**
    *   Maintain `ROADMAP.md` to reflect current progress.
    *   Update `docs/DASHBOARD.md` when adding new dependencies or modules.

5.  **Workflow:**
    *   **Plan:** Analyze requirements, check `ROADMAP.md`.
    *   **Implement:** Write code, add tests (if applicable) or verification steps.
    *   **Verify:** Compile (`make`), check for warnings, run manual verification logic.
    *   **Commit:** Use descriptive messages.
