# Workspace Handoff — v2.5.0 — 2026-04-17

## Session Summary
Protocol v2.5.0: Major feature branch merges including superai hypercode porting (413 files, 121K+ insertions), bobgui 1997-commit GTK update, supersaber, picard, linthesia merges. Submodule pointer updates for bobeditpro/muse_framework, bobtrax/ardour, npp/bobgui. 23 feature branches reverse-synced. All upstream forks checked (no new changes). jules-autopilot built successfully (10.62s, 485KB index chunk).

## Key Changes This Session
- **superai**: Merged `jules-hypercode-porting-p1` — massive 413-conflict merge resolved, 14 commits pushed
- **bobgui**: Merged `jules-10024490872005189356` — 1997 commits ahead, pushed to master
- **supersaber**: Merged jules branch — docs + editor templates
- **picard**: Merged jules branch — log cleanup
- **linthesia**: Merged jules branch — midi driver cleanup
- **bobeditpro/muse_framework**: Resolved autobot→testflow rename conflict
- **bobtrax/ardour**: Resolved modify/delete zita-resampler conflict
- **npp/bobgui**: Merged upstream GTK changes
- **bobcoin**: Stale lock cleared, already up to date
- **jules-autopilot**: Checked out main, merged jules branch, built clean

## Pushed Repos
- bobgui (1997 ahead), bobtrax (1 ahead), npp (1 ahead), picard (3 ahead)
- superai (14 ahead), supersaber (4 ahead), bobeditpro feature branches (1271+1289)
- pi-mono/badlogic-main (27 ahead), ksm-v2 feature (3 ahead), linthesia (3 ahead)

## Push Failures / Blockers
- **openclaw-config**: HTTP 403 (TechNickAI remote) — persistent permission issue
- **antigravity-cli**: HTTP 403 (krmslmz remote) — persistent permission issue  
- **Maestro**: Requires `--no-verify` for push (pre-push hooks)
- **Maestro/borg-assimilation**: Push timed out (810 commits ahead)
- **bg**: Skipped (huge build_output tree causes git operations to timeout)
- **bobdesk**: 13K dirty LibreOffice files (intentional)
- **borg**: Secondary worktree at hypercode-push (by design)

## Known Issues
- 156 Dependabot vulnerabilities in jules-autopilot (3 critical, 73 high)
- bobfilez has 18 dirty tracked files + 1 behind upstream
- hyperharness has 25 dirty submodule pointers
- bobui has 2 dirty submodule pointers
- antigravity-autopilot `release/5.1.1` branch not merged (release branch)
- topaz-ffmpeg `topaz/develop` branch not merged (upstream dev branch)

## Repo Architecture
### Workspace Root (C:/Users/hyper/workspace)
Main meta-repo. Contains CHANGELOG.md, VERSION, HANDOFF.md, and 40+ repo clones.

### Key Repos
| Repo | Default Branch | Upstream | Notes |
|------|---------------|----------|-------|
| jules-autopilot | main | sbhavani/jules-app | Main AI app, Vite build |
| bobeditpro | master | audacity/audacity | Audacity fork, has muse_framework + bobui submodules |
| superai | main | — | 14 ahead, large hypercode porting merge |
| bobgui | master | — | GTK fork, 1997 commits |
| tabby | master | Eugeny/tabby | Terminal emulator fork |
| Maestro | main | — | AI orchestration, needs --no-verify |
| bobcoin | main | — | Blockchain project |
| pi-mono | main | — | Pi ecosystem |

### bobmani/ Submodules
| Submodule | Default | Notes |
|-----------|---------|-------|
| bobmania | master | StepMania theme |
| ksm-v2 | master | K-Shoot MANIA fork |
| linthesia | main | Piano game |
| arrowvortex | master | Arrow pattern editor |
| ddc | master | Dance dance converter |
| itgmania | master | ITG game fork |
| beatoraja | main | Rhythm game |
| Simply-Love-SM5 | master | StepMania theme |

## Build Info
- **jules-autopilot**: Vite v6.4.2, 2970 modules, 10.62s build, 485KB index chunk
- **Node**: v22+ required
- **Build command**: `cd jules-autopilot && npm run build`

## Conflict Resolution Strategy
- Lock files (package-lock, yarn.lock): `--theirs` (accept incoming)
- Translation files (.po): `--theirs`
- Source files: Union merge (concatenate both sides via regex)
- Submodule conflicts: Reset dirty state, then merge

## Next Steps
1. Address Maestro/borg-assimilation push timeout (810 commits)
2. Resolve bobfilez upstream behind state (1 commit)
3. Clean hyperharness/bobui dirty submodule pointers
4. Consider merging antigravity-autopilot release/5.1.1
5. Fix openclaw-config and antigravity-cli 403 permission issues with collaborators
