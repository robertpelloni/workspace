# HANDOFF — Session v4.46.0

**Date:** 2026-06-05
**Operator:** AI Sync Engine
**Previous Version:** 4.45.0 → **4.46.0**

---

## Summary

Applied **permanent architectural fix** for recurring FCDM Jules clone errors by removing all 11 extern/* git submodule entries from itgmania and bobmania. Third-party build dependencies are now fetched by `fetch-extern-deps.sh` instead of being tracked as git submodules.

## Jules Clone Error Fix (PERMANENT) — extern submodule removal

### Root Cause (Final Analysis)
- Jules uses `--shallow-submodules --depth 1 --recursive` clone
- Internal proxy at `192.168.0.1:8080` caches GitHub repo state and serves stale data
- Third-party repos (IXWebSocket, ffmpeg, etc.) force-push/rebase their history
- When proxy serves stale branch tip, embedded tree references submodule commits that no longer exist at the third-party remote
- Previous fixes (updating submodule pointers, empty commit bumps for cache invalidation) all failed because the proxy persisted stale state

### Permanent Fix
- Removed all 11 extern gitlink (160000) entries from itgmania's index
- Removed corresponding .gitmodules sections from itgmania
- Removed all 11 itgmania/extern gitlink entries from bobmania's index
- Removed corresponding .gitmodules sections from bobmania
- Added `fetch-extern-deps.sh` to itgmania for build-time dependency fetching
- Added extern dirs to `.gitignore` in itgmania
- CMake build files **unchanged** — they still expect source in `extern/` directories

### Removed Dependencies (now fetched by script)
| Dependency | URL | Pinned Commit |
|-----------|-----|---------------|
| IXWebSocket | machinezone/IXWebSocket | 998cf95 |
| ffmpeg | FFmpeg/FFmpeg | b355200 |
| mbedtls | Mbed-TLS/mbedtls | 545d1b7 |
| zlib | madler/zlib | e3dc0a8 |
| ogg | xiph/ogg | 06a5e02 |
| vorbis | xiph/vorbis | 1c5f57a |
| libtomcrypt | libtom/libtomcrypt | a68fa19 |
| libtommath | libtom/libtommath | ae40a87 |
| libpng | pnggroup/libpng | 92c853c |
| libjpeg-turbo | libjpeg-turbo/libjpeg-turbo | 94d5ff4 |
| hidapi | libusb/hidapi | c3509c1 |
| libusb | libusb/libusb-cmake | c8477c1 |

### Updated Repos
| Repo | Commit | Change |
|------|--------|--------|
| itgmania | `93bcd8de` | Removed 11 extern gitlinks, added fetch-extern-deps.sh |
| bobmania | `a44c21be` | Removed 11 itgmania/extern gitlinks, updated embedded tree |
| FCDM | `4bad359` | Updated bobmania + itgmania pointers |

## Known Blockers Remaining

1. **OmniRoute**: AI feature branches have unrelated histories (cherry-pick strategy needed)
2. **Security**: 282 GitHub vulnerabilities on default branch (7 critical)

## Next Session Priorities

1. Monitor if FCDM Jules clone now succeeds (should — no more extern gitlinks to fail on)
2. Cherry-pick OmniRoute dashboard-ui-resilience commits onto main
3. Security vulnerability remediation
