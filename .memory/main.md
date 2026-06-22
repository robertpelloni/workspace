# Workspace Monorepo — Project Roadmap

## Project Purpose
Massive monorepo at `github.com/robertpelloni/workspace` containing 74+ submodules across games, AI agents, MCP servers, terminal tools, UI frameworks, music apps, and developer utilities. Functions as a unified development platform with global build orchestration (`build.bat`, `start.bat`) across Go, Rust, C++, Java, Python, Node.js, and .NET projects.

## Current State (v5.30.0)
- **Executive sync protocol healthy** — Protocols #12-#18 completed in succession
- **All submodules initialized** — no uninitialized submodules, no `+`/`-` status
- **Feature branches tracked** — enterprise_sales_bot, aimoneymachine_site, Maestro, fcdm all receiving regular reverse merges
- **Jules proxy compatibility** — stale submodule pins fixed across bg, bobsgameonlinejava, geany, bcs chains
- **Jules clone issues** — Root cause identified: local-only commits in submodule pins. Fixed by updating all stale pins to upstream HEAD. Additional issue: Jules proxy at 192.168.0.1:8080 may serve stale `master` branches.
- **TormentNexus/tormentnexus duplicate resolved** — Removed duplicate case-insensitive submodule entry from .gitmodules

## Key Decisions Made

| Decision | Rationale |
|----------|-----------|
| **Submodules over subtrees** | Submodules allow independent versioning of each project |
| **Reverse-merge strategy** | Feature branches with 100+ unique commits kept separate; main synced into them via --allow-unrelated-histories + "theirs" conflict resolution |
| **Version bump per protocol** | Each Executive Protocol increments the global version (v5.12.0 → v5.30.0 across 18 protocols) |
| **Windows case-insensitive gitdir collision** | Two submodule paths differing only by case (TormentNexus/tormentnexus) share the same `.git/modules/` on Windows. Consolidated to one path. |
| **Fix directories as submodules** | MilkDrop3_fix, bg_fix, bobfilez_fix, bobsaver_fix, bobsgameonlinejava_fix registered as proper submodules (same URLs as originals) for historical reference |
| **Deepseek API key** | Set via `DEEPSEEK_API_KEY` in WSL `~/.hermes/.env` (rotated per standard practice) |
| **tabby** | Tracks `master` branch. Merged upstream Eugeny/tabby into our fork. Pinned to v1.0.115-level commit with our custom features (broadcast mode, session logging, Ctrl+C paste). |
| **warp** | Tracks `master` branch. Already at latest origin/master. |

## Milestones

- [x] v5.12.0–v5.30.0 — 18 Executive Protocols completed
- [x] Submodule fix pass: 17+7+8 stale pins fixed across bg, bobsgameonlinejava, bcs, geany chains
- [x] TormentNexus duplicate consolidation (case-insensitive Windows fix)
- [x] enterprise_sales_bot reverse merges: 8 branches kept current with main
- [x] aimoneymachine_site reverse merges: 6 branches kept current
- [x] tabby: merged upstream Eugeny/tabby, set to track master
- [ ] 165 GitHub vulnerabilities on default branch (1 critical, 72 high)
- [ ] bobfilez/recovery/detached-work blocked by pybind11 MAX_PATH
- [ ] bg nested references/ submodules (~50) remain uninitialized

## Open Problems

1. **GitHub Dependabot vulnerabilities** — 165 total (1 critical). Needs triage.
2. **bobfilez pybind11 path** — Deeply nested `tests/test_cmake_build/subdirectory_function/build_output/pybind11/...` exceeds Windows MAX_PATH, preventing branch checkout.
3. **bg nested submodules** — ~50 references/ submodules (ControlNet, Stable Diffusion, aseprite, etc.) are large third-party repos that can't be easily initialized.
4. **Jules proxy freshness** — The proxy at 192.168.0.1:8080 serves stale git data. May need `master` branches synced to `main` or deleted.
5. **Build orchestration** — build.bat builds 4 Go binaries across 4 repos. May need expansion as new Go services are added.
