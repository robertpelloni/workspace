# Workspace Monorepo — Project Roadmap

## Project Purpose

Massive monorepo at `github.com/robertpelloni/workspace` containing 74+ submodules across games, AI agents, MCP servers, terminal tools, UI frameworks, music apps, and developer utilities. Functions as a unified development platform with global build orchestration (`build.bat`, `start.bat`) across Go, Rust, C++, Java, Python, Node.js, and .NET projects.

## Current State (v5.40.0)

- **Executive sync protocol healthy** — Protocols #12-#28 completed in succession
- **All submodules initialized** — no uninitialized submodules in .gitmodules
- **Version control** — Global version bumped to v5.40.0, synced across VERSION, VERSION.md, start.bat, build.bat, CHANGELOG.md, ROADMAP.md
- **jules-autopilot on latest** — Forward-merged jules-485 feature branch, now at v3.6.8 release
- **enterprise_sales_bot clean** — HyperNexus site redesign merged, third NotebookLM video added
- **hymnmania active** — YouTube OAuth upload working, video generator, MilkDrop render pipeline, public privacy setting, title format fixed
- **OAuth secrets scrubbed** — Google Client ID/Secret removed from hymnmania memory log, force-pushed clean
- **Build pipeline verified** — 5 Go binaries built and preserved (tormentnexus, hyperharness, pi-mono, tabby-backend, tabby-native)
- **External tool compatibility** — Jules AI pushes new submodule commits between protocol runs; workspace tracks via pointer updates

## Key Decisions Made

| Decision | Rationale |
|----------|-----------|
| **Submodules over subtrees** | Submodules allow independent versioning of each project |
| **Reverse-merge strategy** | Feature branches with 100+ unique commits kept separate; main synced into them via --allow-unrelated-histories + "theirs" conflict resolution |
| **Version bump per protocol** | Each Executive Protocol increments the global version (v5.12.0 → v5.40.0 across 28 protocols) |
| **Windows case-insensitive gitdir collision** | Two submodule paths differing only by case (TormentNexus/tormentnexus) share the same `.git/modules/` on Windows. Consolidated to one path. |
| **Secret scrubbing in agent logs** | OAuth secrets in `.memory/branches/main/log.md` must be scrubbed before push. GitHub push protection blocks commits containing Client IDs/Secrets. Use `sed` replacement + `git commit --amend` + `force-with-lease` to resolve. |
| **Stash conflict resolution** | When `git stash pop` causes merge conflicts in site redesign files, accept `--theirs` (stash version) as the newer rewrite and verify completion. |
| **Deepseek API key** | Set via `DEEPSEEK_API_KEY` in WSL `~/.hermes/.env` (rotated per standard practice) |
| **tabby** | Tracks `master` branch. Merged upstream Eugeny/tabby into our fork. Pinned to v1.0.115-level commit with our custom features (broadcast mode, session logging, Ctrl+C paste). |

## Milestones

- [x] v5.12.0–v5.30.0 — 18 Executive Protocols completed
- [x] v5.31.0 — Full dual-direction merge & submodule registration (enterprise_sales_bot: 8 branches, aimoneymachine_site: 5 branches, freellm, fwber, jules-autopilot)
- [x] v5.32.0 — Submodule pointer reconciliation & finalization
- [x] v5.33.0 — Forward merge fcdm (74+10 commits), fwber (21+6 commits)
- [x] v5.34.0 — Forward merge Maestro multi-language-harness-expansion (15 commits)
- [x] v5.35.0 — Synced 3 upstream commits, initialized 14 new submodules
- [x] v5.36.0 — Forward merge enterprise_sales_bot CRM mapping, hymnmania studio reversal
- [x] v5.37.0 — Forward merge Maestro .env config loaders, jules-autopilot LM Studio fix
- [x] v5.38.0 — Maestro gitlink fixes, reverse merges, bobsgameonlinejava_fix deferred
- [x] v5.39.0 — enterprise_sales_bot stash resolved, hymnmania WIP committed, OAuth secrets scrubbed, jules-autopilot forward-merged, 5 Go binaries built
- [x] v5.40.0 — External tool submodule pointer sync (enterprise_sales_bot +1, hymnmania +1, jules-autopilot +1), feature branch assessment
- [ ] 165 GitHub vulnerabilities on default branch (1 critical, 72 high)
- [ ] bg nested references/ submodules (~50) remain uninitialized

## Open Problems

1. **GitHub Dependabot vulnerabilities** — 165 total (1 critical). Needs triage.
2. **bg nested submodules** — ~50 references/ submodules (ControlNet, Stable Diffusion, aseprite, etc.) are large third-party repos that can't be easily initialized.
3. **bobsgameonlinejava_fix fix/stale-lib-submodules** — Identified unique work but complex submodule merge deferred from multiple protocols.
4. **Deep directory nesting issue** — `tests/test_cmake_build/subdirectory_function/build_output/pybind11/...` exceeds Windows MAX_PATH, causes `git status` timeouts.
5. **Jules proxy freshness** — The proxy at 192.168.0.1:8080 may serve stale git data.
6. **MilkDrop3-2077/** — Untracked directory with gitdir reference, not a registered submodule or worktree. Possibly orphaned.
