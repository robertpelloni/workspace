v5.176.0 - Protocol #156: Infrastructure fixes + realestatecrm forward merge (+1)

## Summary

Protocol #156 focused on fixing broken submodule infrastructure that was blocking git status operations, plus one forward merge.

### Merges Completed

- **realestatecrm**: Fast-forward merge from dashboard-newest (1 doc commit shared across 5 identical branches)

### Submodule Infrastructure Fixes

- **bobtrax**: Fixed broken gitdir refs in muse/zrythm `.git` files; corrected worktree paths in git configs; deinited lmms/ardour/zrythm/muse — bobtrax git status now clean
- **bobfilez**: Deinited 60+ libs/* submodules (fstlib, heif, libheif, imageinfo, Windows, etc.) — eliminating git status timeouts
- **MilkDrop3/MilkDrop3_fix bobmani**: Deinited deeply nested submodules (hymnmania, arrowvortex, beatoraja, bobmania, ddc, ksm-v2, itgmania, etc.) from both repos — eliminating recursive timeout chains
- **bg**: Resolved bobsgameweb submodule pointer merge conflict (UU → resolved)

### Workspace root git status now functional with `--ignore-submodules=dirty`

### Next Agent Tasks

1. Stage remaining submodule pointer updates (`git add` all `+` submodules)
2. Run full build: `build.bat`
3. Merge workspace root dependabot branches
4. Address 29 GitHub dependabot vulnerabilities
5. Push individual submodule changes: `git submodule foreach 'git push origin main'`
