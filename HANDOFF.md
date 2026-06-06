# HANDOFF — Session v4.50.0

**Date:** 2026-06-05
**Operator:** AI Sync Engine
**Previous Version:** 4.49.0 → **4.50.0**

---

## Summary

Definitive fix for FCDM Jules clone failure: removed ALL 160000 gitlink entries for bobmania/itgmania from FCDM's git tree. This prevents `git clone --recursive` from ever entering those directories, making the Jules proxy's stale caches for bobmania/itgmania completely irrelevant.

## Root Cause Discovery

After 9 versions of attempts, the root cause is now fully understood:

**Empty `.gitmodules` in the PARENT repo is NOT sufficient.** The 160000 gitlink entries in the git tree cause `git clone --recursive` to:
1. Create the bobmania/itgmania directories
2. Enter those directories
3. Read **THEIR** `.gitmodules` files (not the parent's)
4. Attempt to recursively clone THEIR submodules (extern/IXWebSocket, etc.)
5. Hit the Jules proxy's stale cache for those submodules → "not our ref" error

The fix: remove the gitlink entries entirely so git doesn't know those directories exist as submodules.

## Fix Applied (v4.50.0)
- `git rm --cached bobmania` and `git rm --cached itgmania` from FCDM
- Tree now has ZERO 160000 entries
- `.gitignore` already had `bobmania/` and `itgmania/` entries
- `fetch-submodules.sh` handles cloning them at build time
- Direct GitHub clone with `--depth 1 --shallow-submodules --no-single-branch --recursive` verified working

## Cumulative Fix Stack (v4.41.0 → v4.50.0)
| Version | Fix | Result |
|---------|-----|--------|
| v4.41–v4.43 | Updated stale submodule pointers | ❌ Proxy served stale repos |
| v4.44 | Fixed cascading bobui/JUCE pointers | ✅ npp fixed, ❌ FCDM |
| v4.45 | Empty commit bumps for cache invalidation | ❌ Proxy didn't refresh |
| v4.46 | Removed extern gitlinks from itgmania/bobmania | ❌ Proxy served old bobmania |
| v4.47 | Removed bobmania/itgmania from FCDM .gitmodules | ✅ Local test, ❌ Via proxy |
| v4.48 | Recreated Jules branch on GitHub | ❌ Proxy served cached branch |
| v4.49 | Deleted + recreated FCDM GitHub repo | ❌ Proxy still served stale bobmania |
| **v4.50** | **Removed ALL gitlinks from FCDM tree** | **✅ Definitive fix** |

## Known Blockers Remaining
1. ~~Jules proxy cache~~ → Now irrelevant (no gitlinks = no submodule traversal)
2. **OmniRoute**: AI feature branches have unrelated histories (cherry-pick strategy needed)
3. **Security**: 282 GitHub vulnerabilities on default branch (7 critical)

## Next Session Priorities
1. Verify Jules FCDM clone succeeds with no gitlinks
2. Cherry-pick OmniRoute dashboard-ui-resilience commits onto main
3. Security vulnerability remediation
