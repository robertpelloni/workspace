# Omni-Workspace Memory

## Recurring Observations
- **Submodule Sensitivity:** The workspace is highly sensitive to detached HEADs and unmerged feature branches. Always use `scripts/sync_all_submodules.py` to reconcile.
- **Build Bottleneck:** `bg/okgame/lib/boost` is the primary build bottleneck. Preservation of compiled binaries via `.build_success` markers is mandatory.
- **Mapping Errors:** Broken gitlinks (160000) often cause `fatal: no submodule mapping found`. Prune them from the index using `git rm --cached` if they lack a `.gitmodules` entry.

## Project Preferences
- **Instruction Precedence:** `docs/UNIVERSAL_LLM_INSTRUCTIONS.md` is the root authority. Proprietary files (`CLAUDE.md`, etc.) are model-specific extensions.
- **Conflict Strategy:** Prefer intelligent merging (combining features) over blind selection. Use `git checkout --ours` as a baseline for stabilization only when markers are missing.
- **Search:** Use `scripts/search_api.py` (FastMCP) for high-speed analysis instead of broad `grep` calls.

## Architectural Decisions
- **Bridge Port:** Port 3001 is the designated bridge between the Borg Core runtime and external control planes (VS Code, Mobile).
- **Research Cluster:** The `research/` directory is the standard location for experimental, untracked projects to keep the root directory clean.
- **Dashboarding:** `SUBMODULE_DASHBOARD.md` must be refreshed after every stabilization pass to reflect live commit hashes.

---
*Last Updated: 2026-03-25*
