# Session 36 Handoff Document
# Date: 2026-05-10
# Workspace: https://github.com/robertpelloni/workspace.git
# Version: 3.30.0

## Session Summary
Merged 1 upstream (topaz-ffmpeg +1 from FFmpeg), committed 4 dirty repos, merged tabby jules branch, reverse-synced 9 feature branches across 5 repos. All submodule pointers updated.

## Upstream Merges (1 new)
| Submodule | Upstream | Changes |
|-----------|----------|---------|
| topaz-ffmpeg | FFmpeg/FFmpeg | +1: swscale/filters hard-code radius for trivial kernels. +20/-2 |

## Commits & Pushes (4 repos)
- **bobmani/hymnmania**: Added .gitignore for suno test artifacts. Cleaned up repo.
- **bobbybookmarks**: incoming resources + pi agent config (supervisor.md, taskplane.json)
- **pi-mono**: New extensions (acp_adapter, babysitter, plannotator, react_fallback, worktrees), version bump, models update
- **tabby**: Jules branch merged into master (fast-forward — handoff.md case fix commits)

## Reverse Syncs (9 branches across 5 repos)
- topaz-ffmpeg: master synced (+98 from develop)
- bobmani/hymnmania: 2 branches (+1 each)
- bobbybookmarks: 3 branches (+1 each)
- tabby: feat/real-pty-serial (+2)
- pi-mono: 2 branches (+1 each, 1 force-pushed for diverged ref)

## Workspace Submodule Pointer Updates (5)
- topaz-ffmpeg: b26cd16bc → 6c906999
- bobmani/hymnmania: f118ec2b → ad9517f4
- bobbybookmarks: 2c585749 → ba94cf3d
- tabby: 160358a5 → d7ce936a
- pi-mono: 9cbe802c → 9d03790e

## Verification
- Zero unpushed commits ✅
- No feature branches ahead of default ✅
- All upstreams checked (only topaz-ffmpeg had new commits) ✅

## Known Issues (Unchanged)
1. **bg/okgame**: Boost build artifacts bloat repo — NEEDS .gitignore
2. **bobfilez/wkhtmltopdf**: pybind11 infinite recursion makes git add/diff timeout
3. **bobeditpro copilot branches**: 3 permanently unmergeable
4. **bg/bobsgameweb**: Unresolved merge from prior session
5. **raindropioapp upstream**: Fetch fails (HTTP error)
6. **Maestro/pi-mono**: Some feature branches non-fast-forward on remote
7. **tabby upstream**: Tag conflict (v1.0.231/233)
8. **hymnmania**: 65MB SF2 exceeds GitHub's 50MB recommendation
9. **.agent**: Third-party repo, local mods can't be pushed
10. **tabby HANDOFF.md**: Recurring case-sensitivity conflict on Windows

## Recommendations for Next Session
1. **CRITICAL: Add .gitignore for bg/okgame** — Boost artifacts make entire bg repo unusable
2. **hymnmania SF2**: Consider Git LFS for 65MB soundfont
3. **Force-push Maestro/pi-mono feature branches** that diverged
4. **bg/bobsgameweb**: Complete the unresolved merge
5. **Jules clone test**: Verify `git clone --recurse-submodules https://github.com/robertpelloni/bobfilez` works after session 34 fixes
