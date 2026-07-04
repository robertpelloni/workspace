# Workspace Monorepo — Project Roadmap

## Project Purpose

Massive monorepo at `github.com/robertpelloni/workspace` containing 74+ submodules across games, AI agents, MCP servers, terminal tools, UI frameworks, music apps, and developer utilities. Functions as a unified development platform with global build orchestration (`build.bat`, `start.bat`) across Go, Rust, C++, Java, Python, Node.js, and .NET projects.

## Current State (v5.96.0)

- **Executive sync protocol healthy** — Protocols #12-#74 completed in succession
- **Protocol #74 (v5.96.0):** Maintenance sync — no new feature branches since Protocol #72
- **Forward merges (cumulative):** ArrowVortex (+3), MarbleBlast (+2), agentirc (+23), ai_game_engine (+17), bobtorrent (+27), bobsaver (+1), realestatecrm (+7), bobbybookmarks (+3), bqt audio graph renaming (+1), aimoneymachine_site blog (+7), tormentnexus MCP SSE (+19), fcdm Milestone 8 (+1), f-zerox Netplay/C physics/Fast3D (+29), hyperharness LLM StreamChat/FTS5 (+16), bobtrax WASM (+10), bqt OmniAudioGraph (+6), aimoneymachine_site affiliate links (+1)
- **Submodule fixes:** enterprise_sales_bot/borg, stale locks, MilkDrop3_fix/bobmani/bobmania + Themes/Simply-Love-SM5
- **All submodules initialized** — no uninitialized submodules in .gitmodules (excluding bg references/)
- **Version control** — Global version bumped to v5.95.0, synced across VERSION, VERSION.md, CHANGELOG.md
- **jules-autopilot on latest** — v3.6.24
- **tormentnexus active** — Cloud dashboard MCP SSE, cold archive, skill evolution

## Key Decisions Made

| Decision | Rationale |
|----------|-----------|
| **Submodules over subtrees** | Submodules allow independent versioning of each project |
| **Reverse-merge strategy** | Feature branches with 100+ unique commits kept separate; main synced into them via --allow-unrelated-histories + "theirs" conflict resolution |
| **Version bump per protocol** | Each Executive Protocol increments the global version (v5.12.0 → v5.40.0 across 28 protocols) |
| **De-nest bg from MilkDrop3** | MilkDrop3 had `bg` as a redundant nested submodule. Same repo as workspace `bg/`. No functional dependency — only doc files and archive scripts. Removed to eliminate double checkout and simplify pointer propagation. |
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
- [x] v5.40.0 — Cherry-picked & merged 2 feature branches: bobui (bqt) bqt-renaming-audio-graph (93 files, +1339), bobsgameonlinejava port-cpp-puzzle-logic (+152)
- [x] v5.40.0 — De-nested redundant bg submodule from MilkDrop3
- [x] v5.79.0 — Protocol #63: 12 feature branches forward-merged across 11 submodules
- [x] v5.80.0 — Protocol #64: 9 feature branches forward-merged across 7 submodules (follow-up sweep)
- [x] v5.81.0 — Protocol #65: 7 feature branches forward-merged across 4 submodules + qbittorrent removed from bobtorrent
- [x] v5.91.0 — Protocol #69: MilkDrop3_fix/aios re-initialized, stale lock/metadata cleanup
- [x] v5.92.0 — Protocol #70: Submodule sanitization, stale lock file cleanup, lr2oraja-endlessdream init, feature branch assessment
- [x] v5.93.0 — Protocol #71: Fixed broken bobmania submodule, forward-merged fcdm go-onnx-inference (+1)
- [x] v5.94.0 — Protocol #72: Forward-merged 5 feature branches (f-zerox +29, hyperharness +16, bobtrax +10, bqt +6, aimoneymachine_site +1)
- [x] v5.95.0 — Protocol #73: Maintenance sync, no new feature branches
- [x] v5.96.0 — Protocol #74: Maintenance sync, no new feature branches
- [ ] 165 GitHub vulnerabilities on default branch (1 critical, 72 high)
- [ ] bg nested references/ submodules (~50) remain uninitialized

## Open Problems

1. **GitHub Dependabot vulnerabilities** — 165 total (1 critical). Needs triage.
2. **bg nested submodules** — ~50 references/ submodules (ControlNet, Stable Diffusion, aseprite, etc.) are large third-party repos that can't be easily initialized.
3. **bobsgameonlinejava_fix fix/stale-lib-submodules** — Identified unique work but complex submodule merge deferred from multiple protocols.
4. **Deep directory nesting issue** — `tests/test_cmake_build/subdirectory_function/build_output/pybind11/...` exceeds Windows MAX_PATH, causes `git status` timeouts.
5. **Jules proxy freshness** — The proxy at 192.168.0.1:8080 may serve stale git data.
6. **MilkDrop3-2077/** — Untracked directory with gitdir reference, not a registered submodule or worktree. Possibly orphaned.
7. **bg de-nested from MilkDrop3** (2026-06-23) — Removed from MilkDrop3/.gitmodules. If anything breaks, add it back.
