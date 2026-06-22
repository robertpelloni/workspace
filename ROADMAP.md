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

## Phase 5d: Executive Protocol #13 — Deep Submodule Repair & Sync v5.25.0 (Completed 2026-06-20)
- [x] Full fetch across all submodules + tags
- [x] Fixed MilkDrop3/bg/bobsgameonlinejava/references/defold — re-added with valid upstream HEAD (a17be93)
- [x] Fixed MilkDrop3/bg/bobsgameonlinejava/references/tiled — updated to upstream master HEAD (ad2c29d)
- [x] Fixed bobsgameonlinejava submodule remote URL (was pointing to defold/defold)
- [x] Updated commit chain: bobsgameonlinejava → bg → MilkDrop3 → workspace
- [x] Reverse merge: main → all active feature branches across 7 repos
- [x] Version bumped to v5.25.0 across VERSION, VERSION.md, build.bat, start.bat

## Phase 5e: Executive Protocol #14 — Repository Sync & Maintenance v5.26.0 (Completed 2026-06-20)
- [x] Full fetch across all submodules + tags
- [x] Updated TormentNexus & tormentnexus to remote HEAD (df03c438)
- [x] Reverse merge: main → enterprise_sales_bot (jules-autodev-phase5-integration)
- [x] Version bumped to v5.26.0 across VERSION, VERSION.md, build.bat, start.bat

## Phase 5f: Executive Protocol #15 — Submodule Sanitization & Duplicate Consolidation v5.27.0 (Completed 2026-06-21)
- [x] Full fetch across all root + 74 submodules (recursive)
- [x] Fixed MilkDrop3 & bg submodule corruption (re-clone + re-init)
- [x] Removed orphaned muse submodule from bobeditpro
- [x] Consolidated duplicate TormentNexus/tormentnexus submodules (removed TormentNexus, kept tormentnexus with branch=main)
- [x] Fixed case-insensitive Windows gitdir collision (TormentNexus/tormentnexus sharing same .git/modules/)
- [x] Updated enterprise_sales_bot submodule pointer (blog frontmatter, borg cleanup)
- [x] Updated tormentnexus submodule pointer to remote HEAD (df03c43)
- [x] Version bumped to v5.27.0 across VERSION, VERSION.md, build.bat, start.bat

## Phase 5g: Executive Protocol #16 — Repository Sync & Feature Branch Assessment v5.28.0 (Completed 2026-06-21)
- [x] Full fetch across all submodules (recursive)
- [x] Updated tormentnexus + enterprise_sales_bot submodule pointers to remote HEAD
- [x] Evaluated all active feature branches across 9 robertpelloni repos
- [x] Version bumped to v5.28.0 across VERSION, VERSION.md, build.bat, start.bat

## Phase 5h: Executive Protocol #17 — Repository Sync & Reverse Merge v5.29.0 (Completed 2026-06-21)
- [x] Full fetch across all submodules
- [x] Reverse merged main into 4 enterprise_sales_bot feature branches
- [x] Reverse merged main into 3 aimoneymachine_site feature branches
- [x] Reverse merged main into Maestro multi-language-harness-expansion
- [x] Version bumped to v5.29.0 across VERSION, VERSION.md, build.bat, start.bat

## Phase 5i: Executive Protocol #18 — Repository Sync & Reverse Merge v5.30.0 (Completed 2026-06-21)
- [x] Full fetch across all submodules
- [x] Reverse merged main into 4 enterprise_sales_bot branches
- [x] Reverse merged main into 3 aimoneymachine_site branches
- [x] Version bumped to v5.30.0 across VERSION, VERSION.md, build.bat, start.bat

## Phase 5j: Executive Protocol #19 — Full Dual-Direction Merge & Submodule Registration v5.31.0 (Completed 2026-06-22)
- [x] Full fetch across all root + submodules (recursive with tags)
- [x] Registered all bobmani nested submodules in .gitmodules (Simply-Love-SM5, arrowvortex, beatoraja, bobmania, ddc, ddc_onset, ffr-difficulty-model, hymnmania, itgmania, ksm-v2, leraine-studio, linthesia, pianogame)
- [x] Fixed bobmani submodule URL (bobmani.git → bobmania)
- [x] Forward merged: enterprise_sales_bot (8 feature branches → main, 281 commits)
- [x] Forward merged: aimoneymachine_site (5 feature branches → main, 51 commits)
- [x] Forward merged: freellm (freellm-linux → main)
- [x] Forward merged: fwber (federation-hardening → main)
- [x] Forward merged: jules-autopilot (jules-485-merge-test → main)
- [x] Reverse merged main back into all active feature branches
- [x] Version bumped to v5.31.0 across all reference files
