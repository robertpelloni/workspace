# Omni-Workspace Deployment & Maintenance Strategy

*Last Updated: 2026-11-15 (v5.311.0 — Protocol #302)*

## 1. Standing Close-Out Policy (Always-Deploy)
Per owner directive (2026-11-13), every Executive Protocol synchronization pass closes out with full verification and root deployment (`0/0` vs `origin/main`):
- **CPU Priority:** Run builds and background daemons at `BelowNormal` priority.
- **Go Build Cache:** Automatically routed to `D:\agent-cache\go-build` and `D:\agent-cache\go-tmp` in `build.bat`, `start.bat`, and Control Center `:2999`.
- **Binary Preservation:** Never clean, purge, or delete compiled `.exe` artifacts.

## 2. Protocol Synchronization Pipeline
1. **Environment Prep:** Prepend `C:\Users\hyper\AppData\Local\GitHubDesktop\app-3.6.11\resources\app\git\cmd` to `PATH` and unset any burned OS `GITHUB_TOKEN` (or load verified token from root `.env` in-memory only).
2. **Fetch & Triage:** Fetch all 134 `.gitmodules` entries (`133/134` initialized; `hypercode` uninitialized) and compare local/remote branches against `origin/<default>`.
3. **Zero-Loss Merge Engine:**
   - Fast-forward clean behind-only defaults.
   - Commit genuine tracked dirty state (`-uno`, skipping gitlinks and active sibling-excluded lanes `HyperNexus`, `HyperNexus2old`, `unitedbeats_site`, `openclaw-config`, `openclaw-dashboard`).
   - Forward-merge feature branches cleanly (retrying conflicts only where safe; retaining dual-direction conflicts untouched for owner review).
   - Push updated submodule defaults to `origin`.
4. **Published-Only Root Pointer Staging:**
   - Stage updated submodule pointers ONLY when `git branch -r --contains <HEAD>` confirms the commit is published on the submodule's remote (`pincheck == 0` unpublished).
5. **Maps & Dashboards:**
   - Regenerate `STRUCTURAL_MAP.md` and `SUBMODULE_DASHBOARD.md`.

## 3. Build & Runtime Verification
```bat
:: Global verification build (hyperharness, pi-mono, tabby-backend, tabby-native)
cmd /c build.bat

:: Full 12-binary Go service suite (tabby x3, hermes-agent, hyperharness, pi-go, npp x2, warp-go, hyper-go, freellm, bobtk)
cmd /c start.bat build

:: Consolidated Control Center (:2999) + Windows System Tray Controller
cmd /c start.bat tray
```

## 4. Explicit Root Commit & Push
Never run blind `git add .` in root (keeps scratch ledgers, logs, and archives unstaged). Stage explicit governance files, scripts, and pincheck-verified submodule gitlinks, then commit and push `main` -> `origin/main`.
