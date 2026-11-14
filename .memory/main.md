# Workspace Monorepo — Brain Memory (`main`)

*Last Updated: 2026-11-14 (v5.308.0 — Protocol #299)*

## Project Purpose

Federated monorepo at `github.com/robertpelloni/workspace` orchestrating **134 submodules** (`133` initialized) across AI agent harnesses (`HyperNexus`, `hyperharness`, `pi-mono`, `hermes-agent`, `Maestro`, `jules-autopilot`), terminals/IDEs (`tabby`, `warp`, `hyper`, `npp`, `bqt`, `bgtk`), games & rhythm engines (`bg`, `bobmani`, `hymnmania`, `ArrowVortex`, `beatoraja`), and commercial/web platforms (`fwber`, `realestatecrm`, `marketing_agent`, `unitedbeats_site`, `unitedbeats_hypernexus_gtm`).

## Current State (`v5.308.0`)

- **Executive Protocols #1–#299 Complete:** Continuous zero-loss synchronization, dirty-state tracking, forward/reverse branch reconciliation, and published-only root pointer pincheck (`0` unpublished pins).
- **Consolidated Control Center (`:2999`) & System Tray (`v2.0.0`):** Live in `research/workspace-orchestrator/` (`start.bat dashboard` / `start.bat tray` / `start_dashboard_tray.bat`), running at `BelowNormal` CPU priority and managing all **10/10** Go binaries (`hyper-go` fixed from `./cmd/hyper` -> `.`).
- **Disk & Build Cache Healthy:** Stale git `.tmp` packs cleaned (`~285 GB` free on `C:`); Go caches routed to `D:\agent-cache\go-build` & `D:\agent-cache\go-tmp`.
- **Org Migrations & GTM:** `fwber` -> `FWBerLLC`; `unitedbeats_site` -> `UnitedBeatsLLC` (`unitedbeats.org` live on WordPress `UnitedBeats Legacy` `v1.4.0` with 79 souls, `Kourlos` spelling fixed, and 10 public B2B/project pages); `unitedbeats_hypernexus_gtm` (`v0.1.0`) seeded for the 30-day HyperNexus B2B rollout.
- **Handover Note (2026-11-14):** Muse leader (`muse-wonder-leader`, session `01a1aa95-ba13-7573-81c8-8d1c0a06a63a`) hit subscription quota `429` at `09:57 EST` (resets `2026-11-16 00:00 UTC`); Antigravity (`antigravity-gemini`) seamlessly took over and completed Protocol #299 (`v5.308.0`).

## Key Standing Decisions

| Decision | Rationale |
|----------|-----------|
| **Always-Deploy Close-Out** | Verify `build.bat`, keep all `.exe` binaries, update docs/maps, and push root `0/0` every protocol. |
| **Published-Only Pincheck** | Never stage a submodule gitlink unless `git branch -r --contains HEAD` passes (`pincheck == 0`). |
| **GitHub Desktop Git + `.env` Auth** | Prepend GitHub Desktop `git.exe` to `PATH`; unset burned OS `GITHUB_TOKEN` or load verified `.env` token per-shell without printing. |
| **`D:\agent-cache` + `BelowNormal`** | Prevents `C:` disk exhaustion and keeps desktop responsiveness smooth during Go/C++ builds. |
| **Sibling Lane Isolation** | Leader sync runs fetch/status only on `HyperNexus`, `HyperNexus2old`, and `unitedbeats_site`. |

## Open Owner-Gated Items (Reserved for Robert)

1. **4 Retained Dual-Conflict Branches:** `bobfilez` (`origin/backup/wip-leader-sync-20261107` `+1`), `freellm` (`temp-main` `+2`), `veilid_reddit_facebook` (`jules-scaffold-0.1.0-18345075036601368068` `+17`), `hyperporn` (`origin/backup/wip-leader-sync-20261107` `+2`).
2. **Commercial & Legal Gates:** `unitedbeats_hypernexus_gtm` pricing/pilot outreach, Hank/Excel Legacy Realty proposal & Invoice #001, Mercury invite, Umbrella `v6`/`v7` confirmation with Bobbi (`muse.ai` weekly usage resets Nov 14 `18:38 EST`).
3. **Maintenance Window Gates:** Replacing burned OS-level `GITHUB_TOKEN` in Windows System Environment Variables, Groq/HF key rotation, and 2-minute HyperNexus quiesce window to checkpoint/LFS-handle `HyperNexus/data/tormentnexus.db`.
