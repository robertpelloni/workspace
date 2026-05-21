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
