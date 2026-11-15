# Omni-Workspace Memory

*Last Updated: 2026-11-15 (v5.313.0 — Protocol #304)*

## Operational Facts & Standing Guardrails

- **Always-Deploy Rule (2026-11-13+):** Every Executive Protocol close-out verifies `build.bat` (`4 OK, 0 failed`), preserves all compiled `.exe` binaries (never clean/purge), updates `VERSION`, `VERSION.current`, `VERSION.md`, `build.bat`, `start.bat`, `CHANGELOG.md`, `HANDOFF.md`, `TODO.md`, `ROADMAP.md`, regenerates `STRUCTURAL_MAP.md` & `SUBMODULE_DASHBOARD.md`, and pushes root `0/0` vs `origin/main`.
- **Published-Only Pincheck Guard:** Never stage a submodule pointer in root unless `git branch -r --contains <HEAD>` succeeds inside that submodule (`pincheck == 0` unpublished mandatory).
- **Working Git Binary on Windows (`PINK`/`BOBPC`):** System `C:\Program Files\Git\mingw64\bin\git.exe` lacks `git-remote-https`. Prepend GitHub Desktop's git (`C:\Users\hyper\AppData\Local\GitHubDesktop\app-3.6.11\resources\app\git\cmd`) to `PATH`.
- **GitHub Auth Hygiene:** The OS-level `GITHUB_TOKEN` env var is a burned token that breaks HTTPS pushes on `Maestro`, `bobmani/ksm-v2`, `electricsheep`, and `neverball`. Unset `GITHUB_TOKEN` (to fall back to Windows Git Credential Manager) or load the valid `robertpelloni` token per-shell from gitignored root `.env` without ever printing or committing it.
- **Disk & Build Cache Hygiene:** Keep Go build caches on `D:\agent-cache` (`GOCACHE=D:\agent-cache\go-build`, `GOTMPDIR=D:\agent-cache\go-tmp`) and run background builds/daemons at `BelowNormal` CPU priority so interactive desktop work is never starved.
- **Sibling Submodule Lanes:** Respect active sibling agent lanes (`HyperNexus`, `HyperNexus2old`, `unitedbeats_site`, `fwber`, `realestatecrm`, `marketing_agent`, etc.). Leader sync fetches/monitors `HyperNexus` without modifying its shared working tree.

## Infrastructure & Control Plane Ports

- **`:2999` — Consolidated Workspace Control Center** (`research/workspace-orchestrator`, `start.bat dashboard` / `start.bat tray` / `start_dashboard_tray.bat`): Single-page monitoring & process orchestrator + native `.NET NotifyIcon` Windows system tray controller (`tray_controller.ps1`).
- **`:7778` / `:7779` — HyperNexus Engine & Web UI**: Go control plane API, supervisor, and cross-session memory/scratchpad bus (`node HyperNexus/addons/shared/session-bus.mjs`).
- **`:8082` / `:3006` — Jules Autopilot API & UI**: Fleet session dispatcher and PR monitor.
- **`:9222` — MS Edge CDP Bridge**: Browser session coordination (`node HyperNexus/addons/shared/cdp-bridge.mjs`) linking Bobbi (`muse.ai`), Gemini, and ChatGPT web threads.

## Organization & Production Deployments

- **GitHub Org Migrations:** `fwber` -> `FWBerLLC/fwber`; `unitedbeats_site` -> `UnitedBeatsLLC/unitedbeats_site`; new B2B GTM repo `robertpelloni/unitedbeats_hypernexus_gtm` (`v0.1.0`).
- **United Beats Production (`unitedbeats.org` on Hetzner `/var/www/unitedbeats`):** WordPress (`PHP 8.4-FPM` + MySQL `unitedbeats_wp`) running custom `UnitedBeats Legacy` theme (`v1.4.0`), preserving the verbatim 100vh legacy memorial & star/nebula canvas (`79 souls`, `Kourlos` spelling fixed) above 10 live B2B/project pages (adult properties kept off public menu to protect Google AdSense & enterprise B2B conversion).
