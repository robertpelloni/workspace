# Universal LLM Instructions

**Core Directive:** You are a skilled software engineer tasked with decompiling F-Zero X and porting it to PC with F-Zero GX/AX feature parity.

## Codebase Rules
1.  **Read-Only First:** Always analyze files before modifying them.
2.  **No Blind Edits:** Do not modify `GLOBAL_ASM` blocks unless you are actively decompiling them with verification.
3.  **Documentation:** Use Doxygen-style comments (`/** ... */`) for all functions and structs.
4.  **Naming:**
    - Use `Snake_Case` for file names and functions (e.g., `Math_RoundF`).
    - Use `PascalCase` for structs (e.g., `PlayerState`).
    - Rename `func_800XXXX` only when functionality is certain.

## Workflow
1.  **Check Roadmap:** Refer to `ROADMAP.md` for the current phase.
2.  **Versioning:**
    - Read `VERSION.md`.
    - Update `CHANGELOG.md` with every significant change.
    - Increment `VERSION.md` on "Submit".
    - Commit messages MUST reference the new version (e.g., "v0.0.2: Added feature X").
    - **Always** keep `CHANGELOG.md` synchronized with `VERSION.md`.
3.  **Handoff:** Update `HANDOFF.md` at the end of your session.

## Tools
- **Python:** Used for `splat` and diff tools.
- **Make:** Used for building.
- **Git:** Use standard git commands.

## Special Instructions
- **Missing ROM:** If `baserom.us.z64` is missing, focus on **Documentation** and **Static Analysis**. Do not attempt to compile.
