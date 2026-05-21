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
