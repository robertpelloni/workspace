# Workspace Handoff — v3.76.0

**Date**: 2026-05-21
**Version**: 3.76.0
**Commit**: 2d3ec0c28

## Session Summary

### STEP 1: Upstream Tracking & Submodule Sanitization
- **67 repos fetched** (all tags included)
- **1 upstream merge**: ksm-v2 (34)
- **4 submodules committed**: auto_dj_script, hymnmania, ksm-v2, slsk
- All working directories clean across 71 submodules

### STEP 2: Dual-Direction Intelligent Merge Engine
- **0 forward merges** — no feature branches ahead of main with unique content
- **0 reverse merges** — all feature branches already caught up
- **1 dependabot PR merged**: bobui #13 (postcss bump)
- **Remaining open PRs**: OmniRoute (2 DRAFT), borg (170 dependabot), mk64 (2 old DRAFT)

### STEP 3: Workspace Cleanup, Documentation & Build Finalization

#### 🔒 Security Incident
- **hymnmania committed SSR auth tokens** — detected and removed:
  - `__hssrc.bin`, `sb-ssr-production-auth-token.0.bin`, `sb-ssr-production-auth-token.1.bin`
  - `ssr_bucket.bin`, `decrypt_files.py`
  - Added to `.gitignore`: `*.bin`, `sb-ssr-*`, `ssr_bucket.*`
  - **⚠️ ACTION REQUIRED**: Rotate any exposed SSR production auth tokens
  - These were committed during Jules AI development sessions

#### Batch Script Validation
- `build_all.bat`, `RESET_WORKSPACE.bat`, shell scripts — all paths verified correct

#### Version Governance
- VERSION: 3.75.0 → 3.76.0
- CHANGELOG.md updated with security fix documentation

#### Documentation Sync
- **NEW**: `SUBMODULE_MAP.md` — structural map of all 71 submodules with tree layout
- **Updated**: `ROADMAP.md` — comprehensive feature tracking (v3.68→v3.76)
- **Updated**: `TODO.md` — prioritized action items (critical→low)

#### Key Changes This Session
- auto_dj_script: core.py (+5/-5) — 5th consecutive session with active changes
- hymnmania: extract_token.py (+59/-3), security cleanup
- slsk: .borg_startup_marker removed from tracking
- borg: next-env.d.ts committed (+1/-1) — rare borg activity

## Known Issues
1. **🔒 Security**: hymnmania SSR auth tokens were committed — need token rotation
2. **bobfilez**: pybind11 directory recursion — skipped
3. **bg**: Submodule merge complexity — skipped
4. **tabby/jules**: Diverged 68 vs 25 — still unresolved
5. **topaz-ffmpeg**: Diverged from upstream
6. **openclaw-config**: 115 commits ahead of upstream
7. **borg**: 170 open dependabot PRs
8. **235 GitHub security vulnerabilities** across workspace

## Recommendations
1. **URGENT**: Audit all repos for accidentally committed credentials (not just hymnmania)
2. **URGENT**: Rotate any SSR production auth tokens that were in hymnmania
3. Consider adding a pre-commit hook to detect .bin/.key/.pem files
4. Standardize .gitignore across all repos for AI artifacts
5. Workspace is otherwise very stable — focus on security and testing
