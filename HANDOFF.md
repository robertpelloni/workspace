v5.175.0 - Protocol #155: Forward merge — hyper (+124 commits across 3 branches), hyperharness (+2), tormentnexus (+5 files), veilid (+15 files)

## Summary

Protocol #155 executed a full repository synchronization sweep across 75 submodules:

### Merges Completed

- **hyper**: 3 feature branches merged into main — multi-language-agent-foundation (27 commits: C#/Java/Rust/TS agentic tools), tormentnexus-v0.0.1 (34 commits: TormentNexus v1.1.0 LLM harness), hyper-2 (63 commits: upstream terminal fixes). Conflicts resolved by keeping main's versions where diverged.
- **hyperharness**: jules-543599 branch (2 doc commits) merged cleanly.
- **tormentnexus**: cherry-picked 5 files (demo.html, dashboard scripts, catalog.db, tormentnexus.db) from jules-3383 branch to avoid full merge conflicts.
- **veilid_reddit_facebook**: cherry-picked 15 new files from jules-scaffold Gold Master v1.1.0 (Bobcoin integration, crypto auth, wallet UI). Full merge impossible due to unrelated histories.

### Fixed

- Stale index.lock files cleaned: MilkDrop3, bobmani, bobsgameonlinejava
- bobsgameonlinejava: aborted stale rebase, reset to origin/main
- bobui/ultimatepp: aborted stale rebase, reset to origin/main

### Deferred / Known Issues

- **bg_fix nested submodules**: Deep clone of defold/lwjgl3 references times out — ~50 reference submodules skip
- **bobtrax lmms/ardour/zrythm**: Broken nested submodule paths cause git status timeouts in workspace root
- **Workspace root dependabot branches**: 3 branches with security bumps (1 commit each) deferred due to git status timeouts from bobtrax
- **openclaw-config ~40 branches**: All assessed — 0 commits ahead of main

### Next Agent Tasks

1. Fix bobtrax nested submodule structure (lmms/ardour/zrythm) to enable full git status
2. Merge workspace root dependabot branches (npm_and_yarn-56208d8af6, npm_and_yarn-daf66d8d54, uv-0a2ee22f57)
3. Push all changes: `git push origin main` + `git submodule foreach 'git push origin main'`
4. Build and verify: run `build.bat` if available
