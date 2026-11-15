# Workspace Monorepo — Brain Memory (`main`)

*Last Updated: 2026-11-14 (v5.309.0 — Protocol #300)*

## Project Purpose

Federated monorepo at `github.com/robertpelloni/workspace` orchestrating **134 root submodules** (`509` recursive submodule repositories across all layers) across AI agent harnesses (`HyperNexus`, `hyperharness`, `pi-mono`, `hermes-agent`, `Maestro`, `jules-autopilot`, `CodeWhale-Extensions`), terminals/IDEs (`tabby`, `warp`, `hyper`, `npp`, `bqt`, `bgtk`), games & rhythm engines (`bg`, `bobmani`, `hymnmania`, `ArrowVortex`, `beatoraja`, `mk64`, `sm64coopdx`, `neverball`, `bobsaver`), and commercial/web platforms (`fwber`, `realestatecrm`, `marketing_agent`, `unitedbeats_site`, `unitedbeats_hypernexus_gtm`).

## Current State (`v5.309.0`)

- **Executive Protocols #1–#300 Complete:** Deep 509-submodule recursive synchronization, hidden-branch harvest (`warp` +6 branches, `hyper` `v1.2.0` +8,469 LOC, `tabby` `v1.0.285`, `bgtk` `v1.8.0` +10,283 LOC 6-pillar framework + dashboard/tray, `CodeWhale-Extensions` +12 branches, `ArrowVortex/odcnn` `v2.4.0` +51, `bobtorrent/element-web` +22, `fcdm` +18, `bobeditpro` `master` +189, `electricsheep`, `neverball`, `sm64coopdx`, `mk64` upstream +6, `bobsaver/geiss` +13), **all 4 formerly retained conflict branches resolved (`0` retained conflicts remaining)**, and published-only root pointer pincheck (`0` unpublished pins).
- **Consolidated Control Center (`:2999`) & System Tray (`v2.0.0`):** Live in `research/workspace-orchestrator/` (`start.bat dashboard` / `start.bat tray` / `start_dashboard_tray.bat`), running at `BelowNormal` CPU priority and managing all **10/10** Go binaries (`build.bat` 4/4 OK, `start.bat build` 10/10 OK).
- **Disk & Build Cache Healthy:** Stale git `.tmp` packs cleaned (`~258 GB` free on `C:`); Go caches routed to `D:\agent-cache\go-build` & `D:\agent-cache\go-tmp`.
- **Org Migrations & GTM:** `fwber` -> `FWBerLLC`; `unitedbeats_site` -> `UnitedBeatsLLC` (`unitedbeats.org` live on WordPress `UnitedBeats Legacy` `v1.4.0` with 79 souls, `Kourlos` spelling fixed, and 10 public B2B/project pages); `unitedbeats_hypernexus_gtm` (`v0.1.0`) seeded for the 30-day HyperNexus B2B rollout.

## Key Standing Decisions

| Decision | Rationale |
|----------|-----------|
| **Always-Deploy Close-Out** | Verify `build.bat` + `start.bat build`, keep all `.exe` binaries, update docs/maps, and push root `0/0` every protocol. |
| **Published-Only Pincheck** | Never stage a submodule gitlink unless `git branch -r --contains HEAD` passes (`pincheck == 0`). |
| **Deep Recursive `HEAD..<ref>` Audit** | Traverse nested submodules and inspect `HEAD..<ref>` across all owned repos (not just `origin/HEAD..<ref>` or non-skipped repos) so feature branches are never stranded. |
| **GitHub Desktop Git + `.env` Auth** | Prepend GitHub Desktop `git.exe` to `PATH`; unset burned OS `GITHUB_TOKEN` or load verified `.env` token per-shell without printing. |
| **`D:\agent-cache` + `BelowNormal`** | Prevents `C:` disk exhaustion and keeps desktop responsiveness smooth during Go/C++ builds. |
| **Sibling Lane Isolation** | Leader sync runs fetch/status only on `HyperNexus`, `HyperNexus2old`, and `unitedbeats_site`. |

## Open Owner-Gated Items (Reserved for Robert)

1. **Retained Conflict Branches:** `0` remaining (`bobfilez`, `freellm`, `veilid_reddit_facebook`, and `hyperporn` all intelligently reconciled and pushed in Protocol #300).
2. **Commercial & Legal Gates:** `unitedbeats_hypernexus_gtm` pricing/pilot outreach, Hank/Excel Legacy Realty proposal & Invoice #001, Mercury invite, Umbrella `v6`/`v7` confirmation with Bobbi (`muse.ai` weekly usage reset window open).
3. **Maintenance Window Gates:** Replacing burned OS-level `GITHUB_TOKEN` in Windows System Environment Variables, Groq/HF key rotation, and 2-minute HyperNexus quiesce window to checkpoint/LFS-handle `HyperNexus/data/tormentnexus.db`.
