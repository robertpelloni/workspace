# ROADMAP

## Phase 1: Consolidation (Completed)
- [x] Unify all project submodules under a single monorepo layout.
- [x] Fix broken `.gitmodule` pointers in heavily nested repositories.
- [x] Establish global `.gitignore` and version control structure.

## Phase 2: Feature Branch Resolution (Completed)
- [x] Complete "Intelligent Merge Engine" execution over heavily conflicted projects (`borg`, `jules-autopilot`, `fwber`, `hymnmania`, `realestatecrm`).
- [x] Rebase and integrate active feature branches.
- [x] v5.18.0: Merged ArrowVortex jules DDC features, jules-autopilot feat-shadow-pilot, main→feature reverse merges

## Phase 3: Global Build Orchestration (In Progress)
- [x] Connect `build.bat` to all submodule build pipelines.
- [x] Connect `start.bat` to orchestrate multiple sub-services concurrently.
- [ ] Monitor performance of newly merged federation and psy-mono pipelines.
- [x] Migrate all origin remotes to SSH to resolve global auth drift (v1.1.0).

## Phase 4: Production Hardening
- [ ] Implement global health check and monitoring across all sub-services.
- [ ] Optimize containerization for `borg` and `realestatecrm`.
- [ ] Finalize "TormentNexus" cross-module communication protocol.
- [x] Dual-Direction Sync v4.64.0 Completed (2026-06-07)

- Executive Protocol #7 executed - Workspace fully synchronized to v5.14.0 (2026-06-18)
- 270 submodules scanned: 161 clean, 62 tracking updates, 44 private/unreachable
- ArrowVortex/lib/ddc and MilkDrop3/bg/bobsgameonlinejava broken gitlinks repaired

## Phase 5: Intelligent Merge Engine v5.20.0 (Completed 2026-06-19)
- [x] Forward merge: Maestro jules-add-new-agents → main
- [x] Forward merge: pi-mono rev/jules-5192, rev/total-assimilation-cleanup → main
- [x] Forward merge: aimoneymachine_site feat/v1.0.0-alpha.66 → main (v1.0.0-alpha.89)
- [x] Forward merge: fcdm fitness-machine-foundation → main
- [x] Forward merge: jules-autopilot feat-shadow-pilot-git-diff-ui → main
- [x] Forward merge: bobfilez recovery/detached-work → main
- [x] Submodule sanitization: fetched tags + updated all submodules recursively
- [x] Version bumped to v5.20.0 across all reference files

## Phase 5a: Submodule Fix Pass v5.20.2 (Completed 2026-06-19)
- [x] bobtrax: fixed lmms + zrythm submodule pointers (commits dropped from upstream)
- [x] bobsaver: removed dead metamcp/raindropioapp submodules; fixed projectm-eval pointer
- [x] bobfilez: fixed VERT submodule pointer (local-only commit)
- [x] geany: fixed bobui + btk submodule pointers (local-only commits)
- [x] bobsgameonlinejava: fixed grafx2 submodule pointer (local-only commit)
- [x] bobmani: created scaffold-docs branch from main for Jules AI tool compatibility

## Phase 5b: pi-mono Phase 19/20 Assimilation v5.21.0 (Completed 2026-06-20)
- [x] Forward merge: pi-mono rev/jules-5192995686709987445-f4e7a729 → main (37 commits, 33 files changed)
- [x] Phase 19/20 Ultimate LLM Harness: clean room handlers, security tests, E2E tests, smoke/load tests
- [x] Cross-platform security fix: validatePath rejects Unix-absolute paths on Windows
- [x] Version bumped to v5.21.0 across all reference files

## Phase 5c: Executive Protocol #12 — Repository Sync & Submodule Maintenance v5.24.0 (Completed 2026-06-20)
- [x] Full fetch + tags across root and all 78 submodules (+ nested)
- [x] Removed 27 stale index.lock files blocking recursive submodule update
- [x] Reverse merge: main → jules-autopilot (feat-shadow-pilot, jules-485-merge-test)
- [x] Reverse merge: main → fwber (rev/feat/federation-hardening-auth-integration)
- [x] Reverse merge: main → fcdm (fitness-machine-foundation)
- [x] Fixed MilkDrop3/bg/bobsgameonlinejava references/defold — stale hash, deinitialized
- [x] Version bumped to v5.24.0 across VERSION, VERSION.md, build.bat, start.bat
