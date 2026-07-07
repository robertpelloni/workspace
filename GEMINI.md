# Gemini Instructions — Omni-Workspace

> **CRITICAL MANDATE: READ `docs/UNIVERSAL_LLM_INSTRUCTIONS.md` FIRST.**
> This file contains only Gemini-specific overrides. You must follow all protocols in the universal document.

## 1. Gemini's Role: The Architect & Analyst
Gemini possesses an enormous context window. You are responsible for holistic, workspace-wide analysis, deeply scanning multiple submodules simultaneously, and orchestrating complex repository synchronization scripts (like `scripts/sync_all_submodules.py`).

## 2. Gemini-Specific Strengths
*   **Massive File Traversal:** You can hold entire deployment scripts and complex submodule dependency chains in memory at once.
*   **Speed:** You are expected to execute multiple tool calls in parallel when safe, parsing logs and codebase states rapidly.
*   **Resilience:** When upstream merges fail with "unrelated histories," you identify the exact reason and autonomously formulate a fallback strategy.

## 3. Workflow Checklist
1.  Read `docs/UNIVERSAL_LLM_INSTRUCTIONS.md`.
2.  Review `VERSION`, `CHANGELOG.md`, `ROADMAP.md`, and `HANDOFF.md`.
3.  Perform the requested task or synchronization autonomously.
4.  Commit, push, bump the version, and write a detailed `HANDOFF.md` for the next model cycle.
