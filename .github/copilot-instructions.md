# Github Copilot Instructions

> **IMPORTANT:** The **MASTER PROTOCOL** is located in `docs/LLM_INSTRUCTIONS.md`. You MUST read that file first. It contains the unified vision, core mandates, and workflow protocols for this monorepo.

## Workflow Instruction

You are a coding agent focused on one codebase. Use the brv CLI to manage working context.

### Core Rules
- Start from memory: retrieve context via ByteRover before touching files, then read only what remains necessary.
- Keep a local playbook (`playbook.json`) and update it with actionable knowledge as you work.

### user-centric
Before running any `brv` command, ask the user to choose one of the following options:

1. **Accept** - Review the command, then run it if approved.
2. **Auto-run** - Execute immediately and remember this preference for the remainder of the session.
3. **No** - Cancel the command and continue without running it.
4. **Custom** - Skip the command and provide a different instruction.

Once the user chooses **Auto-run**, apply that preference to every subsequent `brv` command in the conversation without asking again.

### Daily Flow
1. Always attempt to retrieve relevant context from ByteRover first by running `brv retrieve`.
2. Do the work with minimal code reads.
3. Record new or refined knowledge in the playbook:
   - Add only specific, actionable, contextual items; avoid secrets and redact when in doubt.
4. Follow the sync policy (manual by default):
   - Do not auto-push.
   - Prompt the user to run `brv push` when the playbook holds meaningful updates.
   - If the user explicitly allows auto-push, run `brv push -y` without further prompts.

### Playbook Guideline
- Be specific (“Use React Query for data fetching in web modules”).
- Be actionable (clear instruction future agents/developers can apply).
- Be contextual (mention module/service, constraints, links to source when available).
- Include a source (file path + line number or commit) whenever possible.

### CLI Usage Notes
- Run `--help` on any command to discover flags and provide exact arguments for the scenario.

---
## ByteRover CLI Command Reference

### `brv add`
**Description:** Add or update a bullet in the playbook (bypasses the ACE workflow for direct agent usage).

**Flags:**
- `-s, --section <string>`: Section name for the bullet (required).
- `-c, --content <string>`: Content of the bullet (required).
- `-b, --bullet-id <string>`: Bullet ID to update (optional; creates a new bullet if omitted).

**Examples:**
- `brv add --section "Common Errors" --content "Authentication fails when token expires"`
- `brv add --section "Knowledge" --bullet-id "ops-002" --content "Documented how to run brv status on Windows"`
- `brv add -s "Best Practices" -c "Always validate user input before processing"`
**Suggested Sections:** Common Errors, Best Practices, Strategies, Lessons Learned, Project Structure and Dependencies, Testing, Code Style and Quality, Styling and Design.

**Behavior:**
- Warns if using non-standard section names.
- Creates a new bullet with an auto-generated ID when `--bullet-id` is omitted.
- Updates an existing bullet when `--bullet-id` matches an entry.
- Displays bullet ID, section, content, and tags after the operation.

**Requirements:** Playbook must exist (`brv init` first).

---
### `brv retrieve`
**Description:** Retrieve memories from the ByteRover Memora service and save them to the local ACE playbook.

**Flags:**
- `-q, --query <string>`: Search query string (required).
- `-n, --node-keys <string>`: Comma-separated list of node keys (file paths) to filter results.

**Examples:**
- `brv retrieve --query "authentication best practices"`
- `brv retrieve -q "error handling" -n "src/auth/login.ts,src/auth/oauth.ts"`
- `brv retrieve -q "database connection issues"`
**Behavior:**
- **Clears the existing playbook first** (destructive operation).
- Retrieves memories and related memories from Memora.
- Combines both result sets into the playbook.
- Maps memory fields (`bulletId` → `id`, `tags` → `metadata.tags`, `nodeKeys` → `metadata.relatedFiles`).
- Displays each result with score, a 200-character preview, and related file paths.
- Warns on save errors but still displays results as a fail-safe.

**Output:** Shows memory and related memory counts plus detailed previews.

**Requirements:** Must be authenticated and have the project initialized.

---
### `brv push`
**Description:** Push the playbook to ByteRover memory storage and clean up local ACE files.

**Flags:**
- `-b, --branch <string>`: ByteRover branch name (default `main`, **not** a git branch).
- `-y, --yes`: Skip the confirmation prompt.

**Examples:**
- `brv push`
- `brv push --branch develop`
**Behavior:**
- Uploads the local playbook to the specified ByteRover branch.
- Cleans up temporary ACE context files after a successful push.

---
### `brv complete`
**Description:** Complete the ACE workflow by saving executor output, generating a reflection, and updating the playbook in one command.

**Arguments:**
- `hint`: Short hint for naming output files (e.g., “user-auth”, “bug-fix”).
- `reasoning`: Detailed reasoning and approach for completing the task.
- `finalAnswer`: The final answer or solution.

**Flags:**
- `-t, --tool-usage <string>`: Comma-separated list of tool calls with arguments (format `ToolName:argument`; required).
- `-f, --feedback <string>`: Environment feedback (e.g., “Tests passed”, “Build failed”; required).
- `-b, --bullet-ids <string>`: Comma-separated bullet IDs referenced (optional).
- `-u, --update-bullet <string>`: Bullet ID to update with new knowledge (adds a new bullet if omitted).

**Examples:**
- `brv complete "user-auth" "Implemented OAuth2 flow" "Auth works" --tool-usage "Read:src/auth.ts,Edit:src/auth.ts,Bash:npm test" --feedback "All tests passed"`
- `brv complete "validation-fix" "Analyzed validator" "Fixed bug" --tool-usage "Grep:pattern:\"validate\",Read:src/validator.ts" --bullet-ids "bullet-123" --feedback "Tests passed"`
- `brv complete "auth-update" "Improved error handling" "Better errors" --tool-usage "Edit:src/auth.ts" --feedback "Tests passed" --update-bullet "bullet-5"`
**Behavior:**
- **Phase 1 (Executor):** Saves the output with hint, reasoning, answer, tool usage, and bullet IDs.
- **Phase 2 (Reflector):** Auto-generates a reflection based on feedback and tags the playbook.
- **Phase 3 (Curator):** Creates a delta operation (ADD or UPDATE) and applies it to the playbook.
- Adds a new bullet to “Lessons Learned” with tag `['auto-generated']` when `--update-bullet` is absent.
- Updates an existing bullet when `--update-bullet` is provided.
- Extracts file paths from tool usage and stores them as `relatedFiles` in metadata.

**Output:** Shows a summary with file paths, tag counts, and delta operations.

---
### `brv status`
**Description:** Show CLI status and project information, including the local ACE playbook context.

**Arguments:**
- `DIRECTORY`: Project directory (defaults to the current directory).

**Flags:**
- `-f, --format=<option>`: Output format (`table` default; options `table`, `json`).

**Examples:**
- `brv status`
- `brv status --format json`
---
## Best Practices

### Efficient Workflow
1. **Retrieve wisely:** Use `brv retrieve` with narrow queries and `--node-keys` filters.
2. **Read what is needed:** Use `brv status` to inspect playbook size before diving into files.
3. **Update precisely:** Prefer `brv add` for targeted edits and `brv complete` for full ACE updates.
4. **Push when appropriate:** Prompt the user to run `brv push` after significant updates to preserve context.

### Memory Management
- Use `brv add` for targeted bullet edits and `brv retrieve` only when fresh context is required.
- `brv retrieve` clears the existing playbook; double-check before running it.
- Retrieved memories keep Memora tags, not auto-generated ones.
- Both memories and related memories are stored in the playbook for reference.

---
## Workspace Protocols
- `VERSION` is the single source of truth for release numbering; synchronize all references with it.
- Commit and push after each major step, especially following version bumps or documentation updates.
- Update `CHANGELOG.md` whenever the version increases.
- Never commit secrets, credentials, or sensitive data.
- Operate autonomously: fix issues, document findings, and continue to the next work item without waiting for confirmation unless the action is destructive.

---
Generated by ByteRover CLI for Github Copilot
