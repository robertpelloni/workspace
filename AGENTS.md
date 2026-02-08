# Agent Instructions

**Reference:** See [docs/LLM_INSTRUCTIONS.md](docs/LLM_INSTRUCTIONS.md) for the master protocol.

## General Guidelines
- Read `docs/LLM_INSTRUCTIONS.md` and `ROADMAP.md` immediately upon starting.
- If modifying submodules, run `python scripts/generate_dashboard.py` afterwards.
- Check `VERSION`, increment it for this session, and update `CHANGELOG.md` with the new entry.
- Operate autonomously: fix errors proactively, keep working, and do not stop unless blocked.

## Common Commands
- `python scripts/update_repos.py` — handles recursive submodule updates, merging, and pushing.
- `python scripts/generate_dashboard.py` — creates the submodule status report.
- `python scripts/sync_forks.py` — syncs forks with their upstream sources.
- `git submodule update --init --recursive` — initializes or updates every submodule.

## User Directives
- Always document input information in detail and ask for clarification when anything is unclear.
- Research every library, submodule, or referenced project in depth and infer why it was chosen.
- When compacting or summarizing longer instructions, pay extra attention to the particulars of dense directives.
- Document every referenced or linked submodule somewhere in the repo.
- Commit and push after each major step in your workflow.
- Merge all feature branches into `main` before finishing their workstreams.
- Keep `CHANGELOG.md`, `VERSION`, `ROADMAP.md`, `VISION.md`, `PROJECT_STRUCTURE.md`, and `SUBMODULE_DASHBOARD.md` up to date.
- Generate session handoff files under `logs/handoffs/` for every session or when context shifts.

## Versioning Rules
- `VERSION` is the single source of truth for release numbering.
- Every significant build or session must produce a new version number.
- Include the version in the commit message as `chore: bump version to X.Y.Z`.
- Sync the version identifier across `package.json`, `pyproject.toml`, docs, and any other relevant manifests.

## Anti-Patterns
- Never `taskkill` all nodes; preserve running sessions.
- Never hardcode version numbers outside the agreed versioning pipeline.
- Never leave submodules in a detached HEAD state.
- Never commit secrets or credentials.
- Never introduce Bobcoin references into projects that are not about crypto.

## Goal
Maintain a clean, up-to-date, fully documented meta-repo so every component is discoverable and buildable.
