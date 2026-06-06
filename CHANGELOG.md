## [4.56.0] - 2026-06-06

### Nuclear Fix: Delete Poisoned FCDM Repo
- Deleted `robertpelloni/fitness_center_dance_machine` entirely (proxy at 192.168.0.1:8080 caches stale packfiles)
- Renamed directory + submodule to `fcdm` (path, name, URL all consistent)
- Updated .git/modules/fcdm config: worktree and origin URL
- Removed stale `.borg_startup_marker` and `.tormentnexus` tree from root
- **ACTION REQUIRED**: Update Jules task config to clone `robertpelloni/fcdm` branch `fitness-machine-foundation-15646876857894738390`

### tormentnexus Submodule
- Already registered in .gitmodules with URL `https://github.com/robertpelloni/TormentNexus.git`
- borg→tormentnexus rename was completed in prior session
- Directory `borg/` no longer exists

## [4.55.0] - 2026-06-06

### CRITICAL: Fix Corrupted Tree Filenames
- All 212 tree entries had "tt" appended to filenames (e.g. ".agenttt" instead of ".agent")
- Root cause: printf with 		 in bash while-loop piped to git mktree caused trailing tabs rendered as "tt" on Windows/Git Bash
- Rebuilt entire tree from clean base (commit a6b0bc9b4) using git update-index
- All filenames now correct - verified zero "tt" suffixes

### FCDM Proxy Resolution
- The proxy at 192.168.0.1:8080 serves stale packfiles for robertpelloni/fitness_center_dance_machine
- All GitHub-side fixes are correct (clean .gitmodules, zero gitlinks)
- The ONLY remaining fix: change the Jules clone URL to robertpelloni/fcdm (never cached by proxy)
- Both branches on fcdm (main + fitness-machine-foundation-*) have zero submodules

### Branch Merges
- jules-autopilot: 18 upstream palette/UX branches merged
- FAGLSC: dependabot merged
- enterprise_sales_bot: dependabot merged
- planet_fitness_stepmaniax_agent: 2 feature branches merged
- Root workspace: dependabot npm branch merged

### tormentnexus
- Already registered as submodule with URL https://github.com/robertpelloni/TormentNexus.git
- borg to tormentnexus rename completed in prior session
