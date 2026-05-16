# Workspace Handoff — v3.44.0

**Date**: 2026-05-15
**Version**: 3.44.0
**Commit**: f3b731c98

## Session Summary

### What Was Done
1. **Full workspace synchronization** across 61 submodules
2. **100+ feature branches merged** into main (primarily bobdesk/LibreOffice fork)
3. **12+ feature branches merged** from Jules/AI dev tools across multiple repos
4. **2 upstream merges**: bobeditpro (93 commits), ksm-v2 (22 commits)
5. **28 submodule pointers updated** to latest remote HEADs
6. **15+ submodules** with uncommitted changes synced and pushed
7. **4 new submodules** added in v3.43.0: auto_dj_script, slsk_discography_downloader_script, native-fy, planet_fitness_stepmaniax_agent
8. **skillzhub** submodule re-added and feature branch merged in v3.39.0

### Key Architecture Notes
- **bobdesk** is a LibreOffice fork with 100+ feature branches — all have been merged into master
- **bobeditpro** is an Audacity fork — upstream changes are continuously merged
- **topaz-ffmpeg** is a custom FFmpeg build — unpushed commits may accumulate
- **bobfilez** has pybind11 recursion issues causing git operations to hang
- **bg/okgame** has build artifacts bloating the repository
- **borg** is a massive monorepo with its own submodules
- **pi-mono** is actively developed with Jules — feature branches appear regularly

### Known Issues
1. **bobfilez**: Directory recursion with pybind11 causes `git status` to hang
2. **bg/okgame**: Build artifacts not properly gitignored
3. **Large binary assets**: Soundfont files pushing GitHub size limits (need Git LFS)
4. **bobdesk**: 100+ feature branches merged — some may have conflicting changes resolved with `-X ours`
5. **Dependabot branches**: Left unmerged (not feature branches, just dependency updates)

### Submodule Count: 61

### Protocol for Future Syncs
1. Fetch all remotes for each robertpelloni submodule
2. Merge any Jules/feature branches into main with `-X ours`
3. Reverse-sync: merge main into feature branches that are behind
4. Check upstream remotes and merge new changes
5. Add/commit/push any uncommitted changes in submodules
6. Update all workspace submodule pointers to remote HEADs
7. Bump VERSION, update CHANGELOG, commit and push workspace

### Reverse-Sync Status
- All feature branches that are behind main have been offered a merge
- Some branches (pi-mono/jules-*) have merge conflicts that abort — these need manual resolution
- Dependabot branches are intentionally left unmerged
