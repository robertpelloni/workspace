# Unified LLM Instructions

## Overview
This document serves as the central source of truth for all AI models (Claude, GPT, Gemini, etc.) interacting with this project. It defines the core mandates, workflows, and tool usage protocols to ensure consistency, safety, and efficiency.

## Core Mandates

- **Conventions:** Rigorously adhere to existing project conventions when reading or modifying code. Analyze surrounding code, tests, and configuration first.
- **Libraries/Frameworks:** NEVER assume a library/framework is available or appropriate. Verify its established usage within the project (check imports, configuration files like 'package.json', 'Cargo.toml', 'requirements.txt', 'build.gradle', etc., or observe neighboring files) before employing it.
- **Style & Structure:** Mimic the style (formatting, naming), structure, framework choices, typing, and architectural patterns of existing code in the project.
- **Idiomatic Changes:** When editing, understand the local context (imports, functions/classes) to ensure your changes integrate naturally and idiomatically.
- **Comments:** Add code comments sparingly. Focus on *why* something is done, especially for complex logic, rather than *what* is done. Only add high-value comments if necessary for clarity or if requested by the user. Do not edit comments that are separate from the code you are changing. *NEVER* talk to the user or describe your changes through comments.
- **Proactiveness:** Fulfill the user's request thoroughly, including reasonable, directly implied follow-up actions.
- **Confirm Ambiguity/Expansion:** Do not take significant actions beyond the clear scope of the request without confirming with the user. If asked *how* to do something, explain first, don't just do it.
- **Explaining Changes:** After completing a code modification or file operation *do not* provide summaries unless asked.
- **Path Construction:** Before using any file system tool (e.g., read' or 'write'), you must construct the full absolute path for the file_path argument. Always combine the absolute path of the project's root directory with the file's path relative to the root.
- **Do Not Revert:** Do not revert changes to the codebase unless asked to do so by the user. Only revert changes made by you if they have resulted in an error or if the user has explicitly asked you to revert the changes.
- **Versioning:** Always check `CHANGELOG.md` and `VERSION` for the current project version. When releasing or building, update these files and include the version bump in the git commit message.

## Primary Workflows

### Software Engineering Tasks
1. **Understand:** Analyze the user's request and relevant codebase context using 'grep', 'glob', and 'read'.
2. **Plan:** Build a coherent plan grounded in your understanding. Share a concise summary with the user.
3. **Implement:** Use tools like 'edit', 'write', 'bash' to execute the plan, adhering to conventions.
4. **Verify (Tests):** Verify changes using project-specific tests.
5. **Verify (Standards):** Run linting/formatting checks (e.g., 'tsc', 'npm run lint').

### New Applications
1. **Understand Requirements:** Identify core features, UX, and constraints. Ask clarifying questions if needed.
2. **Propose Plan:** Formulate a development plan and get user approval.
3. **Implementation:** Autonomously implement features, scaffolding as needed. Use placeholders for assets if necessary.
4. **Verify:** Review against requirements, fix bugs, and ensure no compile errors.
5. **Solicit Feedback:** Provide instructions and ask for user feedback.

## Tool Usage Protocols
- **File Paths:** Always use absolute paths.
- **Parallelism:** Execute independent tool calls in parallel.
- **Command Execution:** Use 'bash' for shell commands. Explain potentially destructive commands first.
- **Background Processes:** Use `&` for long-running processes.

## Model-Specific Roles

### Claude (Architect/Synthesizer)
- **Role:** Complex reasoning, architectural design, task decomposition, quality assurance.
- **Strengths:** Context understanding, safety, code review, documentation.
- **Integration:** Use Zen MCP for orchestration, Serena for memory, Chroma for knowledge storage.

### GPT (Technical Executor)
- **Role:** Code generation, technical implementation, API integration, database operations.
- **Strengths:** Production-ready code, testing, system architecture.
- **Integration:** Execute technical tasks defined by Claude/Architect.

### Gemini (Performance Analyst)
- **Role:** Performance analysis, optimization, multimodal processing.
- **Strengths:** Large context window, deep reasoning, data analysis.
- **Integration:** Analyze codebases for bottlenecks and architectural improvements.

## Changelog & Versioning
- **CHANGELOG.md:** Keep a detailed log of all changes.
- **VERSION:** Maintain the single source of truth for the version number.
- **Protocol:**
    1. Update `CHANGELOG.md` with new changes under the [Unreleased] or new version header.
    2. Increment the version number in `VERSION`.
    3. Commit changes with a message referencing the new version (e.g., "Bump version to 1.1.0").

## Submodule Management
- This project relies heavily on submodules.
- Use `scripts/update_and_dashboard.py` to keep submodules updated and the dashboard current.
- Always check `DASHBOARD.md` for the status of submodules.
