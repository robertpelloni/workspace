# Workspace TODO — v3.76.0

## Critical
- [ ] **Security**: Audit all repos for accidentally committed auth tokens/keys
  - hymnmania had SSR auth tokens committed — fixed in v3.76.0
  - Need to check: bobbybookmarks, realestatecrm, OmniRoute, litellm
- [ ] **tabby**: Resolve jules-15161538455472121726 divergence (68 vs 25)

## High Priority
- [ ] **borg**: Bulk-merge or close 170 dependabot PRs
- [ ] **auto_dj_script**: Validate Tempo Ramping with real DJ sets
- [ ] **hymnmania**: Test Udio API integration end-to-end
- [ ] **jules-autopilot**: Validate -280 line refactoring, cost optimizer
- [ ] **slsk**: Test scan_artists.py with real artist lists

## Medium Priority
- [ ] **topaz-ffmpeg**: Resolve upstream divergence (manual rebase needed)
- [ ] **bg**: Resolve submodule merge complexity
- [ ] **bobfilez**: Fix pybind11 directory recursion (causes git timeout)
- [ ] **openclaw-config**: Evaluate 115 commits ahead for upstream push-back
- [ ] **OmniRoute**: Need Linux CI for proper testing (Windows EPERM issues)

## Low Priority
- [ ] **mk64**: Old DRAFT PRs — may be stale
- [ ] **235 GitHub security vulnerabilities** across workspace
- [ ] **.gitignore standardization** across all repos for AI artifacts
- [ ] **Git LFS migration** for large binary assets

## v3.77.0 Updates
- [x] Merged 5 borg dependabot PRs (165 remaining of 170)
- [ ] auto_dj_script: analysis.py needs integration testing with DSP pipeline
- [ ] hymnmania: manual_extract.py and udio_direct_test.py need validation with live API
- [ ] slsk: musicbrainz service changes need testing with real queries

## v3.78.0 Updates
- [x] borg: All 170 dependabot PRs resolved
- [ ] Only 4 PRs remain in entire workspace (2 OmniRoute DRAFT + 2 mk64 old DRAFT)

## v3.79.0 Updates
- [ ] hymnmania: udio_browser_automation.py needs live Udio validation
- [ ] hymnmania: test suite (test_udio_remix, test_udio_automation) should be run
- [ ] auto_dj_script: analysis.py continues expansion — validate with real audio

## v3.80.0 Updates
- [ ] borg: SessionImportService.ts and ImportedSessionStore.ts need integration testing
- [ ] borg: LanceDBStore.ts changes need vector DB validation
- [ ] hymnmania: scratch/inspect_*.py scripts need cleanup or documentation

## v3.81.0 Updates
- [ ] hymnmania: feat/ui-feedback branch can be deleted (redundant 1.27.0 bump commit)
- [ ] auto_dj_script: approaching stability after 10 sessions of continuous refinement

## v3.82.0 Updates
- [ ] auto_dj_script: 11 sessions and counting — evaluate if approaching v1.0

## v3.83.0 Updates
- [ ] hymnmania: cdp_extract.py and extract_fresh.py need documentation and testing
- [ ] auto_dj_script: Monitor if 11-session streak has stabilized — potential release candidate

## v3.84.0 Updates
- [ ] hymnmania: ai_video.py needs validation with real video generation
- [ ] hymnmania: gemini_generator.py needs Gemini API key configuration
- [ ] hymnmania: udio_oauth_remaker.py needs OAuth flow testing
- [ ] hymnmania: requirements.txt has new dependencies — needs pip install
- [ ] auto_dj_script: confirmed stable — evaluate for release tag

## v3.85.0 Updates
- [ ] auto_dj_script: ready for release tag — 3 quiet sessions confirms stability
- [ ] hymnmania: validate v3.84.0 AI integration (gemini, ai_video, udio_oauth)

## v3.86.0 Updates
- [ ] Maestro: git operations timeout — needs investigation
- [ ] auto_dj_script: 4 quiet sessions — overdue for release tag

## v3.87.0 Updates
- [x] bobfilez: ai-file-sorter pointer fixed (d5bbce4a→cd9a024)
- [ ] bobfilez: 130+ nested libs — spot-check more submodule pointers for remote existence
- [ ] bobfilez: pybind11 infinite directory recursion still blocks git operations

## v3.88.0 Updates
- [ ] borg/hypercode: Verify build after massive rename (1249 files)
- [ ] borg/hypercode: Update any external references to "borg" in workspace scripts
- [ ] auto_dj_script: Test convert_to_mp3.py integration
- [ ] planet_fitness_stepmaniax_agent: Review CRM pipeline for production readiness
- [ ] hymnmania: 2 feature branches current — evaluate for forward merge next session

## v3.89.0 Updates
- [ ] borg: memoryRouter.hypercode→borg rename suggests incomplete migration — audit remaining
- [ ] auto_dj_script: 132MB binary removed — verify tests still pass
- [ ] jules-autopilot: Queue service expanded — load testing needed
- [ ] hymnmania: clear_udio_popup.py — integrate into main pipeline

## v3.90.0 Updates
- [ ] borg/hypercode: Borg→hypercode migration still in progress (some files still reference borg)
- [ ] borg/hypercode: LanceDBStore expanding rapidly — needs test coverage
- [ ] auto_dj_script: Core still refactoring — not yet stable
- [ ] jules-autopilot: jules-17764958747146694232 branch ready for forward merge evaluation

## v3.91.0 Updates
- [ ] private_gemini_storage: 1.4GB repo — needs Git LFS or shallow clone strategy
- [ ] stonerock: Empty repo — add when content is pushed
- [ ] New submodules (20): Need upstream remote configuration where applicable
- [ ] JWildfire: Large Java repo — may need .gitignore for build artifacts
- [ ] element-web: Large Matrix client fork — check for upstream remote
- [ ] Verify all 20 new submodules have proper .gitmodules configuration

## v3.92.0 Follow-ups
- [ ] bobdesk: ~112 remaining Copilot feature branches (mostly empty AI-generated, low priority)
- [ ] bobfilez: Add .gitignore for pybind11 directory to prevent infinite recursion
- [ ] bobfilez: Protect submodule pointer updates from being overwritten by `git add -A`
- [ ] superdawmcp: Validate Bitwig MCP extension builds correctly
- [ ] fwber: Verify ActivityPub federation hardening changes
- [ ] tabby: Verify SFTP progress sync changes

## v3.93.0 Follow-ups
- [ ] fwber: Force push pending — need to complete push of rewritten history (secrets removed)
- [ ] fwber: Rotate AWS and OpenAI API keys (already exposed in git history)
- [ ] auto_dj_script: Verify all test tracks are excluded via .gitignore
- [ ] Scan ALL repos for committed secrets (AWS keys, API tokens, etc.)
- [ ] bobfilez: Verify Jules clone works with fixed submodule pointers

## v3.94.0 Follow-ups
- [ ] fwber: Complete force push of secrets-purged history
- [ ] fwber: Rotate AWS and OpenAI API keys (URGENT)
- [ ] Scan all repos for committed secrets proactively
- [ ] Verify Jules can successfully clone bobfilez after stale pointer fixes
- [ ] Consider adding pre-push hook to prevent committing .env files
- [ ] Consider Git LFS migration for large binary assets

## v3.96.0 Follow-ups
- [ ] fwber: Complete force push of secrets-purged history (persistent timeout)
- [ ] fwber: AWS/OpenAI key rotation (URGENT)
- [ ] ddc: Remote still contains old history with large files (filter-repo was local only, force push completed)
- [ ] element-web: Investigate persistent fetch timeout
- [ ] Consider adding pre-commit hooks to prevent large binary commits
- [ ] Scan remaining repos for oversized files (>100MB)

## v3.97.0 Follow-ups
- [ ] borg: 3 dependabot branches with conflicts need manual resolution
- [ ] bobfilez: Investigate pybind11 recursion causing git hang
- [ ] bobsgameweb: Fix nested submodule status hanging
- [ ] element-web: Configure fetch to target develop branch only
- [ ] openclaw-dashboard/computer-use-preview: Consider forking to robertpelloni for push access
- [ ] topaz-ffmpeg: Push master branch changes (currently only topaz/develop pushed)

## v3.98.0 Follow-ups
- [ ] fwber: 51 commits behind upstream — need strategy for orphan sync
- [ ] borg: upstream repo (OhMyOpenCode/aios) deleted — remove upstream remote
- [ ] topaz-ffmpeg: master branch recreated and merged — clean up after push
- [ ] Consider running `git gc` on repos with many deleted branches

## v3.99.0 Follow-ups
- [ ] OmniRoute: release/v3.4.9 and v3.5.0 failed merge — needs manual resolution
- [ ] bobgui: 665-entry-textview branch needs manual conflict resolution
- [ ] borg: Remove stale upstream remote (OhMyOpenCode/aios deleted)
- [ ] fwber: Strategy for orphan repo sync (51 behind upstream)
- [ ] bobfilez: Deep pybind11 recursion fix for git operations

## v4.0.0 Follow-ups
- [ ] CRITICAL: Fix auto-commit recovery protocol — `git reset --hard` after auto-commit destroys work. Need to push auto-commits BEFORE reset, or use `git stash` approach.
- [ ] OmniRoute: 5 release branches need strategic decision (merge or archive)
- [ ] openclaw-dashboard: Create robertpelloni fork for push access
- [ ] bobsgameweb: Fix remote pack corruption (invalid index-pack)
- [ ] borg: Remove stale upstream remote (OhMyOpenCode/aios 404)
- [ ] fwber: Strategy for orphan repo sync (51 behind upstream)
- [ ] bobfilez: Deep pybind11 recursion fix for git operations

## v4.1.0 Follow-ups
- [ ] openclaw-dashboard: Create robertpelloni fork to persist .gitignore fix
- [ ] OmniRoute: Decide fate of 5+ release branches (archive or strategic merge)
- [ ] bobsgameweb: Fix remote pack corruption (invalid index-pack)
- [ ] borg: Remove defunct upstream remote (OhMyOpenCode/aios 404)
- [ ] bobgui/AUTO_DENATTIFYING: 865 files — evaluate for merge or skip
- [ ] fwber: Long-term strategy for orphan repo (51 behind upstream)

## v4.2.0 Follow-ups
- [ ] openclaw-dashboard: Create robertpelloni fork to persist .gitignore fix (3rd cycle recurring)
- [ ] bobgui/adwaita: 151 files — evaluate for strategic merge or skip
- [ ] topaz-ffmpeg/nipun/fi: Investigate merge conflict
- [ ] bobbybookmarks: Investigate gc/repack timeout (corrupt objects?)
- [ ] OmniRoute: 5+ release branches — decide archive vs. merge
- [ ] borg: Remove defunct upstream remote
- [ ] fwber: Strategy for orphan repo (51 behind upstream)

## v4.3.0 Follow-ups
- [ ] bobgui/amolenaar/fix-dnd-macos-26-gtk-4-20: 10 conflicts — needs manual resolution
- [ ] bobgui/amolenaar/macos-26-native-controls-backport: 103 ahead — evaluate
- [ ] openclaw-dashboard: Create robertpelloni fork (4th cycle recurring)
- [ ] bobgui/adwaita: 151 files — evaluate for merge or skip
- [ ] bobbybookmarks: gc/repack timeout persists — investigate corrupt objects
- [ ] OmniRoute: 5+ release branches — decide archive vs. merge
- [ ] borg: Remove defunct upstream remote
- [ ] fwber: Strategy for orphan repo (51 behind upstream)

## v4.3.1 Follow-ups
- [ ] CRITICAL: Verify jules-autopilot is not losing in-progress work between cycles
- [ ] bobfilez: 12 superseded submodule pointer commits in reflog (safe to ignore)
- [ ] Consider adding `git stash` before reset as additional safety net
- [ ] Consider periodic reflog garbage collection prevention for recovery window

## v4.4.0 Follow-ups
- [ ] bobgui/adwaita: 9 ahead, 151 files — evaluate
- [ ] bobgui/AUTO_DENATTIFYING: 4 ahead, 865 files — evaluate
- [ ] bobgui/amolenaar/fix-dnd-macos-26: 97 ahead, 105 files (10 conflicts last cycle)
- [ ] bobgui/amolenaar/macos-26-native-controls-backport: 103 ahead, 109 files
- [ ] OmniRoute: 5+ release branches — decide archive vs. merge
- [ ] borg: Remove defunct upstream remote (OhMyOpenCode/aios 404)
- [ ] fwber: Strategy for orphan repo (51 behind upstream)
- [ ] openclaw-dashboard: Create robertpelloni fork (stash workaround is temporary)

## v4.5.0 Follow-ups
- [ ] openclaw-dashboard: Create robertpelloni fork to persist .gitignore fix (6th cycle recurring)
- [ ] openclaw-dashboard: Stash conflict resolution overwrites .gitignore fix — need special handling
- [ ] bobgui/adwaita: 9 ahead, 151 files — evaluate
- [ ] bobgui/AUTO_DENATTIFYING: 4 ahead, 865 files — evaluate
- [ ] bobgui/amolenaar/fix-dnd-macos-26: 97 ahead, 105 files (10 conflicts)
- [ ] bobgui/amolenaar/macos-26-native-controls-backport: 103 ahead, 109 files
- [ ] OmniRoute: 5+ release branches — decide archive vs. merge
- [ ] borg: Remove defunct upstream remote
- [ ] fwber: Strategy for orphan repo (51 behind)
- [ ] Pre-existing conflict markers in mk64, neverball (third-party, local fix only)

## v4.6.0 Follow-ups
- [ ] hymnmania: push deferred — large repo timeout; retry with gc/repack
- [ ] bobbybookmarks: push fails (32MB DB in commits); add DB to .gitignore
- [ ] openclaw-dashboard: Create robertpelloni fork to persist .gitignore fix (7th cycle recurring)
- [ ] bobgui/adwaita: 9 ahead, 151 files — evaluate
- [ ] bobgui/AUTO_DENATTIFYING: 4 ahead, 865 files — evaluate
- [ ] bobgui/amolenaar/fix-dnd-macos-26: 97 ahead, 105 files (10+ conflicts)
- [ ] bobgui/amolenaar/macos-26-native-controls-backport: 103 ahead, 109 files
- [ ] OmniRoute: 5+ release branches — decide archive vs. merge
- [ ] borg: Remove defunct upstream remote (OhMyOpenCode/aios deleted)
- [ ] fwber: Strategy for orphan repo (51 behind)
- [ ] litellm: Recurring conflict markers (120 files this cycle) — investigate root cause

## v4.7.0 Follow-ups
- [ ] hymnmania: push deferred — large repo timeout; retry with gc/repack
- [ ] bobbybookmarks: push fails (large DB in commits); add DB to .gitignore
- [ ] openclaw-dashboard: Create robertpelloni fork to persist .gitignore fix (8th cycle)
- [ ] bobgui/adwaita: 9 ahead, 151 files — evaluate
- [ ] bobgui/AUTO_DENATTIFYING: 4 ahead, 865 files — evaluate
- [ ] bobgui/amolenaar/fix-dnd-macos-26: 97 ahead, 105 files
- [ ] bobgui/amolenaar/macos-26-native-controls-backport: 103 ahead, 109 files
- [ ] OmniRoute: 5+ release branches — decide archive vs. merge
- [ ] borg: Remove defunct upstream remote (404)
- [ ] fwber: Strategy for orphan repo
- [ ] fully_automated_gay_luxury_space_communism: First Jules branch merged; monitor for more

## v4.8.0 Follow-ups
- [ ] hymnmania: push still fails (pack-objects signal 15) — needs repack/cleanup
- [ ] bobbybookmarks: push fails (large DB) — add DB to .gitignore
- [ ] openclaw-dashboard: Create fork to persist .gitignore fix (9th cycle)
- [ ] bobgui/adwaita: 9 ahead, 151 files
- [ ] bobgui/AUTO_DENATTIFYING: 4 ahead, 865 files
- [ ] bobgui/amolenaar/fix-dnd-macos-26: 97 ahead, 105 files
- [ ] OmniRoute: release branches too diverged
- [ ] bobgui recurring conflict markers (35 files this cycle) — root cause?

## v4.9.0 Follow-ups
- [ ] bobgui/arraystore-perf: 39 ahead, 37 files, 11 modify/delete conflicts — needs manual resolution
- [ ] geany: many version branches remaining (0.18, 0.19, 0.20, 1.23, build-exec)
- [ ] hymnmania: push still fails
- [ ] bobbybookmarks: push still fails
- [ ] openclaw-dashboard: Create fork (10th cycle)
- [ ] bobgui/adwaita: 9 ahead, 151 files
- [ ] bobgui/AUTO_DENATTIFYING: 4 ahead, 865 files
- [ ] bobgui/amolenaar/fix-dnd-macos-26: 97 ahead

## v4.10.0 Follow-ups
- [ ] bobgui/async-dialog-api: 4 ahead, 9 files, 3 conflicts — needs manual resolution
- [ ] geany/sm: 1 ahead, 20 files, 2 conflicts — needs manual resolution
- [ ] bobgui/arraystore-perf: 39 ahead, 37 files, 11 conflicts (deferred since v4.9.0)
- [ ] bobgui/adwaita: 9 ahead, 151 files
- [ ] bobgui/AUTO_DENATTIFYING: 4 ahead, 865 files
- [ ] bobgui/amolenaar/fix-dnd-macos-26: 97 ahead
- [ ] geany: version branches remaining (0.18, 0.19, 0.20, 1.23, build-exec)
- [ ] hymnmania: push still fails
- [ ] bobbybookmarks: push still fails
- [ ] openclaw-dashboard: Create fork (11th cycle)

## v4.11.0 Follow-ups
- [ ] tabby: more all-contributors branches remaining (check for additional)
- [ ] bobgui/arraystore-perf: 39 ahead, 37 files, 11 conflicts (deferred since v4.9.0)
- [ ] bobgui/async-dialog-api: 4 ahead, 9 files, 3 conflicts (deferred since v4.10.0)
- [ ] bobgui/adwaita: 9 ahead, 151 files
- [ ] bobgui/AUTO_DENATTIFYING: 4 ahead, 865 files
- [ ] geany/sm: 1 ahead, 20 files, 2 conflicts
- [ ] geany: version branches remaining (0.18, 0.19, 0.20, 1.23, build-exec)
- [ ] hymnmania: push still fails
- [ ] bobbybookmarks: push still fails
- [ ] openclaw-dashboard: Create fork (12th cycle)
