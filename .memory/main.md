# Workspace Monorepo — Brain Memory (`main`)

*Last Updated: 2026-11-15 (v5.312.0 — Protocol #303)*

## Project Purpose

Federated monorepo at `github.com/robertpelloni/workspace` orchestrating **134 root submodules** (`509` recursive submodule repositories across all layers) across AI agent harnesses (`HyperNexus`, `hyperharness`, `pi-mono`, `hermes-agent`, `freellm`, `Maestro`, `jules-autopilot`, `CodeWhale-Extensions`), terminals/IDEs (`tabby`, `warp`, `hyper`, `npp`, `bqt`, `bgtk`), games & rhythm engines (`bg`, `bobmani`, `hymnmania`, `ArrowVortex`, `beatoraja`, `mk64`, `sm64coopdx`, `neverball`, `bobsaver`), and commercial/web platforms (`fwber`, `realestatecrm`, `marketing_agent`, `unitedbeats_site`, `unitedbeats_hypernexus_gtm`).

## Current State (`v5.312.0`)

- **Executive Protocols #1–#303 Complete:** Deep 509-submodule recursive synchronization, hidden-branch & `<slug>-<digits>` Jules harvest (`bgtk` `v1.8.0`, `hyper` `v1.2.0`, `warp` +6 branches, `tabby` `v1.0.285`, `CodeWhale-Extensions` all 37 branches incl. 25 Jules test/perf branches reconciled with 53/53 Rust tests green & `0` unmerged Jules branches remaining, `vst_monster` `v0.8.3` +76 commits, `freellm` `RouterEvent` + tray Go build restored, `bobtorrent/bobcoin` +62 synced -> `bobtorrent` `8ea1472`, `ArrowVortex/odcnn` `v2.4.0`, standalone `ADSFileSystem`/`DataStreamBrowser`/`geiss`/`odcnn`/`element-web` + dual-branch `agentirc`/`ArrowVortex`/`bobmani`/`ksm-v2` synced), **all 4 formerly retained conflict branches resolved (`0` retained conflicts remaining)**, and published-only root pointer pincheck (`0` unpublished pins).
- **Consolidated Control Center (`:2999`) & System Tray (`v2.2.0`):** Live in `research/workspace-orchestrator/` (`start.bat dashboard` / `start.bat tray` / `start_dashboard_tray.bat`), running at `BelowNormal` CPU priority with **async 6-worker `ahead/behind` origin divergence & actionable branch scanning across 133/134 submodules**, **embedded HyperNexus `:7778` Session Bus live feed & broadcast**, root-pin drift telemetry, Windows Startup shortcut toggle, and full lifecycle management over all **12/12** Go binaries (`build.bat` 4/4 OK, `start.bat build` 12/12 OK).
- **Disk & Build Cache Healthy:** Stale git `.tmp` packs cleaned (`~258 GB` free on `C:`); Go caches routed to `D:\agent-cache\go-build` & `D:\agent-cache\go-tmp`.
- **Org Migrations & GTM:** `fwber` -> `FWBerLLC`; `unitedbeats_site` -> `UnitedBeatsLLC` (`unitedbeats.org` live on WordPress `UnitedBeats Legacy` `v1.7.0` with 80 souls, Lumbros Dark Rainbow Oil-Sheen HUD, **The $10,000 Haircut & Life-Changing Chair Commission by Lum** 5-question qualification dossier & $10,000.00 USD Private Commission Invoice (`/lum-10000-haircut/`), dedicated `php8.4-fpm-unitedbeats.sock` pool + `UNITEDBEATS` FastCGI microcache, and 11 public pages); `unitedbeats_hypernexus_gtm` (`v0.1.0`) seeded for the 30-day HyperNexus B2B rollout.

## Key Standing Decisions

| Decision | Rationale |
|----------|-----------|
| **Always-Deploy Close-Out** | Verify `build.bat` + `start.bat build` (`12/12` OK), keep all `.exe` binaries, update docs/maps, and push root `0/0` every protocol. |
| **Published-Only Pincheck** | Never stage a submodule gitlink unless `git branch -r --contains HEAD` passes (`pincheck == 0`). |
| **Deep Recursive `HEAD..<ref>` Audit** | Traverse nested submodules and inspect `HEAD..<ref>` across all owned repos (including `<slug>-<digits>` Jules branches) so feature branches are never stranded. |
| **GitHub Desktop Git + `.env` Auth** | Prepend GitHub Desktop `git.exe` to `PATH`; unset burned OS `GITHUB_TOKEN` or load verified `.env` token per-shell without printing. |
| **`D:\agent-cache` + `BelowNormal`** | Prevents `C:` disk exhaustion and keeps desktop responsiveness smooth during Go/C++ builds. |
| **Sibling Lane Isolation** | Leader sync runs fetch/status only on `HyperNexus`, `HyperNexus2old`, and `unitedbeats_site` (plus active sibling-edited files). |

## Open Owner-Gated Items (Reserved for Robert)

1. **Retained Conflict Branches:** `0` remaining (all 4 reconciled & pushed cleanly).
2. **Commercial & Legal Gates:** `unitedbeats_hypernexus_gtm` pricing/pilot outreach, Hank/Excel Legacy Realty proposal & Invoice #001, Mercury invite, Umbrella `v6`/`v7` confirmation with Bobbi (`muse.ai` weekly usage reset window open).
3. **Maintenance Window Gates:** Replacing burned OS-level `GITHUB_TOKEN` in Windows System Environment Variables, Groq/HF key rotation, and 2-minute HyperNexus quiesce window to checkpoint/LFS-handle `HyperNexus/data/tormentnexus.db`.
