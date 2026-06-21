# Submodule Dashboard & Project Structure
**Last Updated:** 2026-06-21 08:45:57

## Project Directory Structure Explanation
This monorepo serves as a unified workspace and orchestrator for dozens of independent microservices, libraries, desktop applications, and AI agents.
*   **`Root/`**: Contains the global orchestration scripts (`sync_and_merge.py`, `intelligent_sync_all.py`), universal documentation (`LLM_INSTRUCTIONS.md`, `ROADMAP.md`), and the workspace-level `package.json` / configuration files.
*   **`.gemini/`, `.claude/`, etc.**: AI agent configuration and context directories managing instructions and local extensions for LLMs.
*   **AI Agent Projects**: Folders like `borg`, `metamcp`, `jules-autopilot`, `antigravity-autopilot`, `mcp-superassistant` contain specialized multi-modal and autonomous agents leveraging MCP (Model Context Protocol).
*   **Full-Stack Apps**: Folders like `Chamber.Law`, `cointrade`, `bobeditpro`, `bobfilez` contain entire standalone full-stack applications with their own submodules.
*   **Shared Libraries**: Other directories include shared utilities and libraries nested across the ecosystem.

## Submodule Status & Versions

| Path | Version | Branch | Commit | Date | Message |
| :--- | :--- | :--- | :--- | :--- | :--- |
| ArrowVortex | v1.3.3 | HEAD | 'ae6a17d' | '2026-06-19' | 'feat: merge DDC AI integration (BatchDDC improvem... |
| CLIProxyAPIPlus | N/A | HEAD | 'd8e38f93' | '2026-06-01' | 'chore: save progress before update' |
| Cli-Proxy-API-Management-Center | N/A | main | '4a6a277' | '2026-06-19' | 'sec: npm audit fix â€” drastically reduce vulnera... |
| GWEN | N/A | HEAD | '5a4fab4' | '2026-03-21' | 'chore: save progress before update' |
| Maestro | v0.15.9 | main | 'f4b1aeb5' | '2026-06-20' | 'sec: upgrade axios@^1.12.0, esbuild@latest' |
| MarbleBlast | N/A | master | '79e877e' | '2026-06-19' | 'feat: merge Ogg/Vorbis native support and asset i... |
| OmniRoute | N/A | main | '2081f96e' | '2026-06-14' | 'chore: resolve merge conflicts & apply security o... |
| OpenMBU | N/A | master | '3b139ae9' | '2026-05-02' | 'sync: update project state' |
| WebAI-to-API | N/A | master | '1b0017e' | '2026-06-14' | 'chore: stop tracking pi-lens/pi tool cache, add t... |
| ableton_psytrance_hymn_creator | N/A | main | '4dd9f78' | '2026-06-19' | 'sec: npm audit fix â€” reduce vulnerabilities' |
| ai_game_engine | N/A | main | '8bc3b30' | '2026-06-14' | 'sync: update godot-cpp submodule' |
| aimoneymachine_site | N/A | main | '2a10520' | '2026-06-19' | 'Merge feat/v1.0.0-alpha.66-intelligent-luxury-int... |
| antigravity-cli | N/A | main | 'dac8d96' | '2026-06-14' | 'sync: commit antigravity-cli changes' |
| antigravity-jules-orchestration | N/A |  |  |  |  |
| apophysis-j | N/A | master | '8e84307' | '2026-05-19' | 'chore: bump version to 2.10.0 and close _SaveFlam... |
| auto_dj_script | N/A | main | '8d1ef2c5' | '2026-06-14' | 'chore: remove pi-lens cache from tracking' |
| bcs | 0.2.0 | master | '6294b1ae8' | '2026-06-19' | 'fix: remove stale bobui-reference submodule entry... |
| bgtk | 1.0.2 | HEAD | '5cd36564eb' | '2026-06-19' | 'fix: update ultimatepp submodule to valid HEAD (5... |
| bobbybookmarks | N/A | main | '640ab94' | '2026-06-19' | 'chore: merge bobbybookmarks cleanup with gitignor... |
| bobcoin | N/A | main | 'd406bb7d' | '2026-06-04' | 'refactor: merge .borg/.hypercode into .tormentnex... |
| bobeditpro | N/A | master | '59953b988' | '2026-05-30' | 'fix: resolve 43 conflict markers in bobeditpro (C... |
| bobfilez | N/A | main | 'ed7df6af8' | '2026-06-20' | 'fix: update btk submodule pin to commit with fixe... |
| bobsaver | N/A | main | '13f5423d' | '2026-06-20' | 'fix: update projectm submodule pin to HEAD â€” re... |
| bobsgameweb | N/A | master | '5e84d930' | '2026-06-19' | 'fix: remove 31 stale submodule entries from submo... |
| bobtorrent | 11.60.30 | master | '658a087' | '2026-06-19' | 'sec: npm audit fix â€” reduce vulnerabilities' |
| bobtrader | N/A | main | 'e2af0a7' | '2026-06-16' | 'chore: forward-merge assimilate-top-crypto-bots f... |
| bobzzite | N/A | main | '058c18b' | '2026-05-02' | 'sync: update project state' |
| bqt | N/A | main | 'c7e1fc7059a' | '2026-06-19' | 'fix: update submodule pointers to valid HEAD â€” ... |
| computer-use-preview | N/A | main | '56c5f74' | '2026-06-04' | 'Merge pull request #112 from MuhammedSenn/add-dot... |
| crowdsourced_dance_club | N/A | main | 'f1c3ce0' | '2026-06-05' | 'fix: update 1 stale submodule pointer to HEAD â€”... |
| dao | N/A | main | '96f45e7' | '2026-06-19' | 'sec: npm audit fix â€” reduce vulnerabilities' |
| dupeguru | N/A | master | '03f4d214' | '2026-05-21' | 'Version 4.3.7: Refactored NamedObject and updated... |
| electricsheep | N/A | master | 'd07f18e' | '2026-05-22' | 'Fix build errors, modernize dependencies, and gen... |
| enterprise_sales_bot | <<<<<<< HEAD
0.5.0
=======
0.6.0
>>>>>>> origin/jules-phase6-production-hardening-042-863b86a9-12417263503841031080 | main | '3cd9355' | '2026-06-21' | 'Fix LinkedInSource config - reads credentials fro... |
| f-zerox | N/A | main | '407e20e' | '2026-06-05' | 'fix: update 4 stale submodule pointers to HEAD â€... |
| fcdm | N/A | main | 'ae852b5' | '2026-06-06' | 'v4.53.0: remove gitlinks - NO submodule reference... |
| frontend-sdl-cpp | N/A | master | '1ee402b' | '2026-05-02' | 'sync: update project state' |
| fwber | 2.1.9 | main | 'f8d58bd02' | '2026-06-19' | 'docs: add workspace preservation notice to .gitig... |
| geany | N/A | master | 'bd221de07' | '2026-06-20' | 'fix: update btk submodule pin â€” btk now has fix... |
| geiss | N/A | main | '816b527' | '2026-03-05' | 'Merge branch 'main' of https://www.github.com/gei... |
| hyper | N/A | canary | '7c75cfa7' | '2026-06-14' | 'chore: apply security overrides via pnpm audit --... |
| hyperharness | 0.5.0-alpha.5 | main | 'f6321e5d' | '2026-06-19' | 'fix: remove stale external/OmniRoute submodule en... |
| litellm | N/A | HEAD | 'a58b45bddd' | '2026-05-30' | 'merge: audit-and-metrics-implementation (3 commit... |
| mcp-superassistant | 0.7.2 | main | '986c53a' | '2026-06-05' | 'fix: update 1 stale submodule pointer to HEAD â€”... |
| mk64 | 8.107.5 | master | '41638788d' | '2026-06-19' | 'fix: remove stale bobcoin submodule entry from in... |
| native-fy | N/A | main | '5a6268e' | '2026-05-26' | 'feat: implement deep telemetry dashboard and E2E ... |
| neverball | 1.6.13-dev | master | '55403258' | '2026-06-03' | 'Merge remote-tracking branch 'origin/master-15755... |
| npp | 1.0.19 | master | '96fdacba1' | '2026-06-19' | 'fix: update stale submodule pointers for bcs/bgtk... |
| onetool-mcp | N/A | main | '0f5fd03' | '2026-05-21' | 'Merge branch 'pr-1'' |
| openclaw-config | 0.27.1 | HEAD | 'd9571ef' | '2026-05-27' | 'fix: resolve pre-existing conflict markers in rep... |
| openclaw-dashboard | N/A | HEAD | 'd6198d0' | '2026-03-17' | 'Merge pull request #29 from tardigrde/add-dockerf... |
| opencode-autopilot | N/A | HEAD | '97bc316' | '2026-06-19' | 'sec: npm audit fix â€” reduce vulnerabilities' |
| pi-mono | N/A | main | '81d7f739' | '2026-06-20' | 'Merge branch 'rev/jules-5192995686709987445-f4e7a... |
| picard | N/A | master | '0f71386a4' | '2026-05-17' | 'chore: sync uncommitted changes' |
| planet_fitness_stepmaniax_agent | N/A | main | '67b31f8' | '2026-06-06' | 'Merge remote-tracking branch 'origin/feat/enterpr... |
| projectm | N/A | master | '23757a21e' | '2026-06-05' | 'fix: update 1 stale submodule pointer to HEAD â€”... |
| psytrance_night_outreach_agent | N/A | main | '1008e66' | '2026-06-14' | 'v1.1.63: Finalize documentation, stakeholder revi... |
| raindropioapp | 1.0.4 | master | '67830358' | '2026-05-25' | 'chore: auto-commit pending changes before workspa... |
| realestatecrm | N/A | HEAD | 'c5a9610' | '2026-06-11' | 'chore: save local progress before sync' |
| skillzhub | v0.1.19 | main | 'bd9e062' | '2026-05-20' | 'style: polish Company Dashboard analytics UI\n\n-... |
| slsk_discography_downloader_script | N/A | HEAD | '55936b9' | '2026-06-03' | 'chore: sync working tree' |
| sm64coopdx | N/A | main | '59b416eb4' | '2026-06-06' | 'Merge remote-tracking branch 'upstream/dev'' |
| superpowers | N/A | main | '8e2e6b6' | '2026-05-02' | 'sync: update project state' |
| supersaber | N/A | master | '6d7243c' | '2026-05-20' | '[v1.4.0] Docs: Add 10-point audit analysis to Han... |
| tabby | N/A | master | '046ee2b4' | '2026-06-19' | 'fix: remove stale warp submodule entry from index... |
| tormentnexus | 1.0.0-alpha.134 | HEAD | 'f152af482' | '2026-06-21' | 'fix: Dockerfile â€” remove stale mcp-registry and... |
| veilid_reddit_facebook | N/A | main | '94a2a8b' | '2026-06-19' | 'sec: npm audit fix â€” reduce vulnerabilities' |
| vst_monster | N/A | main | 'a3e1b79' | '2026-06-03' | 'init: VST Monster v0.1.0 - Documentation, Crawler... |
| xrnet | N/A | main | '4e953df' | '2026-06-14' | 'XRNet v0.1.43: Multi-Hop Distance-Vector Routing ... |
| ArrowVortex\odcnn | N/A | HEAD | '454f4c7' | '2020-02-26' | 'small change' |
| CLIProxyAPIPlus\ui | N/A | HEAD | 'c20f705' | '2026-04-09' | 'fix(ai-providers): include base-url when deleting... |
| ableton_psytrance_hymn_creator\hymnmania_src | 1.28.0 | HEAD | 'a87c1b4' | '2026-05-23' | 'fix: dependency compatibility and final syntax cl... |
| antigravity-autopilot\AUTO-ALL-AntiGravity | N/A | master | '82b20b3' | '2026-04-08' | 'Auto-sync' |
| antigravity-autopilot\AntiBridge-Antigravity-remote | N/A | main | 'c79ab65' | '2026-04-08' | 'Auto-sync' |
| antigravity-autopilot\AntigravityMobile | N/A | main | '149f1f5' | '2026-04-11' | 'Auto-sync' |
| antigravity-autopilot\Claude-Autopilot | N/A | main | '8443801' | '2026-04-15' | 'chore: auto-save' |
| antigravity-autopilot\antigravity-auto-accept | N/A | master | 'da6df56' | '2026-04-08' | 'Auto-sync' |
| antigravity-autopilot\antigravity-multi-purpose-agent | N/A | main | 'cfe8354' | '2026-04-08' | 'Auto-sync' |
| antigravity-autopilot\auto-accept-agent | N/A | master | 'a6d0be5' | '2026-04-08' | 'Auto-sync' |
| antigravity-autopilot\copilot-auto-continue | N/A | main | '267a418' | '2026-04-08' | 'Auto-sync' |
| antigravity-autopilot\free-auto-accept-antigravity | N/A | main | '0fcf71d' | '2026-04-11' | 'Global Sync: Merged features, updated submodules,... |
| antigravity-autopilot\yoke-antigravity | N/A | master | '8c3d312' | '2026-04-08' | 'Auto-sync' |
| bg\bobsgameonlinejava | N/A |  |  |  |  |
| bg\okgame | N/A |  |  |  |  |
| bobeditpro\muse_framework | N/A | main | '42673313' | '2026-05-25' | 'Merge branch 'main' of https://github.com/musesco... |
| bobfilez\VERT | N/A | HEAD | '49821e5' | '2026-06-02' | 'fix: sponsor' |
| bobfilez\ai-file-sorter | N/A | HEAD | 'cd9a024' | '2026-05-13' | 'feat(packaging): add RPM packaging and backend-aw... |
| bobmani\Simply-Love-SM5 | N/A | itgmania-release | '06a56f5f' | '2026-06-06' | 'Merge remote-tracking branch 'upstream/itgmania-b... |
| bobmani\arrowvortex | 0.2.32 | release | 'abee60c' | '2026-06-12' | 'Merge jules DDC integration - update lib/ddc subm... |
| bobmani\beatoraja | 0.9.2 | HEAD | '8a22693c' | '2026-06-19' | 'Merge: bring in bobcoin fix from master' |
| bobmani\bobmania | 5.7.0-Unified-Alpha | master | 'bc65b9fa2d' | '2026-06-19' | 'fix: remove stale submodule entries from itgmania... |
| bobmani\ddc | 0.2.32 | master | '84bd10e' | '2026-05-25' | 'chore: auto-commit pending changes before workspa... |
| bobmani\ddc_onset | N/A | main | '5d7572a' | '2026-05-02' | 'sync: update project state' |
| bobmani\ffr-difficulty-model | N/A | master | 'b13fe4f' | '2026-05-02' | 'sync: update project state' |
| bobmani\hymnmania | 1.37.0 | main | '77e376b' | '2026-06-12' | 'Merge remote-tracking branch 'origin/main'' |
| bobmani\itgmania | N/A | release | 'f0e9e75ae4' | '2026-06-19' | 'fix: remove stale IXWebSocket submodule entry fro... |
| bobmani\ksm-v2 | 2.0.0-alpha29 | master | 'd72474f' | '2026-06-05' | 'fix: update 4 stale submodule pointers to HEAD â€... |
| bobmani\leraine-studio | N/A | master | 'd1b5e24' | '2026-05-02' | 'sync: update project state' |
| bobmani\linthesia | 0.10.10 | main | 'e88f1fd' | '2026-05-25' | 'chore: auto-commit pending changes before workspa... |
| bobmani\pianogame | N/A | master | '1ece599' | '2026-05-21' | 'chore: complete project audit and memory leak cle... |
| bobsaver\JWildfire | N/A | HEAD | '6d851b50' | '2026-05-22' | 'chore: sync uncommitted changes' |
| bobsaver\MilkDrop3 | N/A | main | '3376cde' | '2026-06-19' | 'fix: remove dead submodules metamcp and raindropi... |
| bobsaver\apophysis-j | N/A | master | '8e84307' | '2026-05-19' | 'chore: bump version to 2.10.0 and close _SaveFlam... |
| bobsaver\electricsheep | N/A | master | 'd07f18e' | '2026-05-22' | 'Fix build errors, modernize dependencies, and gen... |
| bobsaver\geiss | N/A | main | '816b527' | '2026-03-05' | 'Merge branch 'main' of https://www.github.com/gei... |
| bobsaver\projectm | N/A | master | '23757a21e' | '2026-06-05' | 'fix: update 1 stale submodule pointer to HEAD â€”... |
| bobsgameonlinejava\bobcoin | N/A | main | '5e0b5d48' | '2026-05-30' | 'fix: resolve conflict markers in bobcoin HANDOFF.... |
| bobtorrent\bobcoin | N/A | main | '5e0b5d48' | '2026-05-30' | 'fix: resolve conflict markers in bobcoin HANDOFF.... |
| bobtorrent\element-web | N/A | develop | '2f4e2d235e' | '2026-06-01' | 'Merge remote-tracking branch 'origin/travis/msc43... |
| bobtorrent\qbittorrent | N/A | master | '30242fa54' | '2026-05-25' | 'sync: session 19 add all files and merge branches... |
| bobtrax\ardour | N/A | HEAD | '8015119773' | '2026-06-16' | 'silence a gcc fallthrough warning with c++17 port... |
| bobtrax\bobui | N/A | main | '5e8ea5784a' | '2026-06-01' | 'Merge branch 'main' of https://github.com/robertp... |
| bobtrax\lmms | N/A | HEAD | 'e215cd0c3' | '2026-06-19' | 'Remove `Model` constraints on `VolumeKnob` (#8438... |
| bobtrax\muse | N/A | master | 'fe5e92ed' | '2026-04-14' | 'chore: save local progress before sync' |
| bobtrax\zrythm | N/A | HEAD | '4967fd053' | '2026-06-18' | 'Merge branch 'feature/chord-functionality' into '... |
| enterprise_sales_bot\borg | 1.0.0-alpha.101 | HEAD | 'e3e33771' | '2026-06-04' | 'feat: total assimilation and pre-flight validatio... |
| f-zerox\bobcoin | N/A | main | '755a3fb' | '2026-04-23' | 'feat: Add explicit enactment delays to governance... |
| hyperharness\adrenaline | N/A | HEAD | '7520e9c' | '2024-02-23' | 'Delete hello.md' |
| hyperharness\aider | N/A | main | '3ec8ec5a' | '2026-04-25' | 'fix: update FAQ token percentages and switch hist... |
| hyperharness\amazon-q-developer-cli | N/A | HEAD | '15cc8f3c' | '2026-04-23' | 'Update README to include issue reporting link (#3... |
| hyperharness\auggie | N/A | HEAD | 'e327605' | '2026-04-10' | 'ci: pin Bun to 1.3.11 to fix codesign regression ... |
| hyperharness\azure-ai-cli | N/A | HEAD | '8d3b8e4' | '2025-03-28' | 'Brianem/place holder key (#345)' |
| hyperharness\bito-cli | N/A | main | 'cb3a779' | '2025-04-23' | 'README.md' |
| hyperharness\byterover-cli | N/A | HEAD | 'e080f240' | '2026-04-14' | 'fix: [ENG-2085] strip ANSI codes in query-rendere... |
| hyperharness\claude-code | N/A | main | 'a371abb' | '2026-04-05' | 'fix(README): formatting in README.md for QueryEng... |
| hyperharness\claude-code-templates | N/A | HEAD | '5d807455' | '2026-04-14' | 'Merge pull request #521 from kiliancm94/narrow-si... |
| hyperharness\code-cli | N/A | HEAD | '5b0c8300e' | '2026-04-05' | 'docs(changelog): update for v0.6.92 [skip ci]' |
| hyperharness\copilot-cli | N/A | HEAD | '89ee433' | '2026-04-13' | 'Update changelog.md for version 1.0.25' |
| hyperharness\crush | N/A | HEAD | 'a210bfbb' | '2026-04-14' | 'chore(legal): @KimBioInfoStudio has signed the CL... |
| hyperharness\dolt | N/A | HEAD | 'cb62860beb' | '2026-04-14' | 'Merge pull request #10846 from dolthub/aaron/flak... |
| hyperharness\factory-cli | N/A | HEAD | '4090349' | '2026-04-14' | 'docs: add droid-control feature page (#933)' |
| hyperharness\gemini-cli | N/A | HEAD | '212edf31e' | '2026-04-14' | 'chore(mcp): check MCP error code over brittle str... |
| hyperharness\goose | N/A | HEAD | '8e04d7c8b' | '2026-04-14' | 'chore(release): bump version to 1.31.0 (minor) (#... |
| hyperharness\grok-cli | N/A | HEAD | '3fe9be7' | '2026-04-13' | 'fix: pipe MCP stdio server stderr to prevent logs... |
| hyperharness\jules-extension | N/A | HEAD | '9f2fc14' | '2025-10-30' | 'Merge pull request #4 from Smetalo/Smetalo-patch-... |
| hyperharness\kilocode | N/A | HEAD | 'edb7dbbf5c' | '2026-04-14' | 'chore: update nix node_modules hashes' |
| hyperharness\kimi-cli | N/A | HEAD | '7869e8cc' | '2026-04-14' | 'chore: bump kimi-cli 1.34.0 (#1875)' |
| hyperharness\litellm | N/A | HEAD | 'b8f7d61400' | '2026-04-14' | 'Merge pull request #25589 from BerriAI/litellm_os... |
| hyperharness\llamafile | N/A | main | '18db09f' | '2026-05-14' | 'Clarify Linux GPU offload diagnostics (#967)' |
| hyperharness\llm-cli | N/A | HEAD | '1bfb96d' | '2026-04-07' | 'Ignore *.db (temporary test databases)' |
| hyperharness\mistral-vibe | N/A | main | 'a83c81e' | '2026-04-21' | 'v2.8.1 (#618)' |
| hyperharness\ollama | N/A | HEAD | '120424d8' | '2026-04-13' | 'Revert "launch/opencode: use inline config (#1546... |
| hyperharness\open-interpreter | N/A | HEAD | '06c796a2' | '2026-04-14' | 'Merge pull request #1721 from iam-saiteja/main' |
| hyperharness\opencode | N/A | HEAD | 'a53fae151' | '2026-04-14' | 'Fix diff line number contrast for built-in themes... |
| hyperharness\pi-cli | N/A | HEAD | '6722144b' | '2026-04-14' | 'chore: approve contributor jay-aye-see-kay' |
| hyperharness\qwen-code-cli | N/A | HEAD | 'dbf2772' | '2025-07-05' | 'chore: ignore local test script' |
| hyperharness\rowboat | N/A | HEAD | '2133d722' | '2026-04-13' | 'Merge pull request #490 from rowboatlabs/dev' |
| hyperharness\smithery-cli | N/A | HEAD | 'a42487e' | '2026-04-13' | 'release: 4.8.0 (#719)' |
| mk64\doxygen-awesome-css | N/A | HEAD | 'd52eafe' | '2026-03-20' | 'feat: prepare npm release' |
| musicbrainz-soulseek-downloader\picard | N/A |  |  |  |  |
| npp\bcs | N/A | master | '6294b1ae8' | '2026-06-19' | 'fix: remove stale bobui-reference submodule entry... |
| npp\bgtk | 1.0.2 | HEAD | '5cd36564eb' | '2026-06-19' | 'fix: update ultimatepp submodule to valid HEAD (5... |
| npp\bqt | N/A | HEAD | 'c7e1fc7059' | '2026-06-19' | 'fix: update submodule pointers to valid HEAD â€” ... |
| npp\textfx | N/A | main | '71ec1ea' | '2026-02-24' | 'Updated version' |
| tormentnexus\borg | 1.0.0-alpha.114 |  |  |  |  |
| tormentnexus\enterprise_sales_bot | 0.5.0 | main | 'c4c5ab4' | '2026-06-15' | 'Add static site files (tormentnexus & hypernexus)... |
| ArrowVortex\lib\ddc | 0.2.32 | HEAD | '84bd10e' | '2026-05-25' | 'chore: auto-commit pending changes before workspa... |
| ai_game_engine\third_party\godot-cpp | N/A | master | '5a7bd2f' | '2026-06-02' | 'Merge pull request #1996 from FishermanWWK/master... |
| antigravity-autopilot\submodules\antigravity-sdk | N/A | main | 'e6f8efb' | '2026-04-08' | 'Auto-sync' |
| bcs\external\bqt-reference | N/A | HEAD | '1c589f87cb' | '2026-06-05' | 'fix: update 2 stale submodule pointers to HEAD â€... |
| bcs\external\juce | N/A | HEAD | '3ba67d4585' | '2026-05-21' | 'CI: Add juce9 branch' |
| bcs\external\ultimatepp | N/A | HEAD | '5276c666b' | '2026-06-18' | 'Merge branch 'master' of https://github.com/ultim... |
| bg\bobsgameonlinejava\bobcoin | N/A |  |  |  |  |
| bgtk\submodules\juce | N/A | master | '3ba67d4585' | '2026-05-21' | 'CI: Add juce9 branch' |
| bgtk\submodules\ultimatepp | N/A | master | '70e1422bf' | '2026-05-24' | 'Core/SSL: Hardened AES-GCM-256 encryption/decrypt... |
| bobfilez\libs\7zip | N/A | main | 'fea94d3' | '2025-10-01' | 'Update latest_version.json' |
| bobfilez\libs\ADSFileSystem | N/A | master | '5ab73c6' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\ADSIdentifier | N/A | master | '7074e07' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\ADSman | N/A | main | '40b0766' | '2026-04-11' | 'chore: save progress before update' |
| bobfilez\libs\AlternateDataStreams | N/A | master | '9eb3f30' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\BLAKE3 | N/A | master | '3702a2e' | '2026-05-25' | 'Merge branch 'master' of https://github.com/BLAKE... |
| bobfilez\libs\Bringing-Old-Photos-Back-to-Life | N/A | master | '2093171' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\C | N/A | master | '75cfc361' | '2026-04-14' | 'Merge feature origin/leetcode_writer_fix into mas... |
| bobfilez\libs\DataStreamBrowser | N/A | master | '70235cc' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\Dependencies | N/A | main | '4c1c96a' | '2026-06-01' | 'Merge branch 'main' of https://github.com/ImageMa... |
| bobfilez\libs\FFmpeg | 0.7.8 | master | 'd6682e1df3' | '2026-05-25' | 'Merge branch 'master' of https://github.com/FFmpe... |
| bobfilez\libs\ImageMagick | N/A | main | '98dbe3e76' | '2026-06-01' | 'Merge branch 'main' of https://github.com/ImageMa... |
| bobfilez\libs\Imath | N/A | main | 'f707a64' | '2026-05-25' | 'Merge branch 'main' of https://github.com/Academy... |
| bobfilez\libs\JUCE | N/A | master | 'fa781307cb' | '2026-05-25' | 'sync: session 19 add all files and merge branches... |
| bobfilez\libs\LibRaw | N/A |  |  | '2026-05-16' | 'fixed stack memory/previous image metadata exposu... |
| bobfilez\libs\Magick.NET | N/A | main | '0ab3f2405' | '2026-06-01' | 'Corrected typo.' |
| bobfilez\libs\MediaInfo | N/A | HEAD | 'fabd16d40' | '2026-05-20' | 'Merge pull request #1283 from g-maxime/appimage' |
| bobfilez\libs\MediaInfoLib | N/A | master | '4172255b3' | '2026-05-25' | 'Merge branch 'master' of https://github.com/Media... |
| bobfilez\libs\OpenColorIO | N/A | main | '066c5e29' | '2026-05-25' | 'sync: session 19 add all files and merge branches... |
| bobfilez\libs\OpenCue | N/A | master | '979e4e31' | '2026-06-01' | 'Merge branch 'master' of https://github.com/Acade... |
| bobfilez\libs\OpenImageIO | N/A | main | 'f7f483ba9' | '2026-06-01' | 'Merge branch 'main' of https://github.com/Academy... |
| bobfilez\libs\OpenRV | N/A | main | '682e4712' | '2026-06-01' | 'Merge branch 'main' of https://github.com/Academy... |
| bobfilez\libs\OpenTimelineIO | N/A | main | 'dc802c8' | '2026-06-01' | 'chore: save progress before update' |
| bobfilez\libs\Powershell-ADS | N/A | master | '13a7507' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\RenStrm | N/A | master | 'f195bb9' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\SharpADS | N/A | main | '8802fc6' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\ShazamAPI | N/A | main | '6cd2c9f' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\ShazamIO | N/A | master | '9163c1b' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\SysmonForLinux | N/A | main | '5d4afca' | '2026-06-01' | 'chore: save progress before update' |
| bobfilez\libs\TinyEXIF | N/A | master | 'feb86cd' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\Windows | N/A | main | 'e1a9307' | '2026-05-25' | 'Merge branch 'main' of https://github.com/ImageMa... |
| bobfilez\libs\WizardsToolkit | N/A | main | 'abe6322' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\ads | N/A | master | '812a05d' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\argon2 | N/A | master | '1ce5c81' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\audio-recognizer | N/A | master | '3dcaaee' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\audiocraft | N/A | main | '28223fe' | '2026-04-14' | 'Merge feature origin/jasco_release_Jan12 into mai... |
| bobfilez\libs\bobgui | 1.0.2 | HEAD | '79878af782' | '2026-05-25' | 'chore: auto-commit pending changes before workspa... |
| bobfilez\libs\bobui | N/A | main | '852143497e' | '2026-06-01' | 'Merge branch 'main' of https://github.com/robertp... |
| bobfilez\libs\brotli | N/A | master | 'b9a3377b' | '2026-06-01' | 'Merge pull request #1406 from mannewalis:fix/emsc... |
| bobfilez\libs\btk | 0.2.0 | master | '0ccafdbdf' | '2026-06-20' | 'fix: update bobui-reference submodule pin to vali... |
| bobfilez\libs\c-ares | N/A | master | '6298122' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\cURL | N/A | master | '5104c165f' | '2026-05-25' | 'sync: session 19 add all files and merge branches... |
| bobfilez\libs\calibre | N/A | master | 'e43178cd4c' | '2026-06-01' | 'Cover grid: When using an image larger than the v... |
| bobfilez\libs\ckmame | N/A | main | 'e2585f6b' | '2026-05-25' | 'Merge branch 'main' of https://github.com/nih-at/... |
| bobfilez\libs\cmark | N/A | master | 'b6232e9' | '2026-05-29' | 'Refactor: Use snprintf return value instead of re... |
| bobfilez\libs\cyrus-sasl | N/A | master | '1144b53' | '2026-05-25' | 'sync: session 19 add all files and merge branches... |
| bobfilez\libs\dirent | N/A | master | '1d454a8' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\dokany | N/A | master | 'c192535' | '2026-06-01' | 'chore: save progress before update' |
| bobfilez\libs\dragonffi | N/A | master | '6790c07' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\dtl-diff | N/A | master | '32567bb' | '2024-07-11' | 'v1.21' |
| bobfilez\libs\dunst | N/A | master | '4600ec9' | '2026-06-01' | 'Merge branch 'master' of https://github.com/dunst... |
| bobfilez\libs\enchant | N/A | master | '1e7b104' | '2026-05-25' | 'Merge branch 'master' of https://github.com/winli... |
| bobfilez\libs\fast-lzma2 | N/A | master | '5ea485a' | '2026-04-13' | 'Merge feature origin/dev into master' |
| bobfilez\libs\freetype | N/A | master | 'fa9b229' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\fribidi | N/A | master | '09fa0da' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\fstlib | N/A | develop | 'bb046ea' | '2026-04-14' | 'Merge feature origin/release into master' |
| bobfilez\libs\fuse_xattrs | N/A | master | 'acf60d4' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\gdk-pixbuf | N/A | main | '3648c0a' | '2026-04-11' | 'chore: save progress before update' |
| bobfilez\libs\getopt-win | N/A | getopt_glibc_2.42_port | 'ac1b9ea' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\getopt-win32 | N/A | original | 'f45e27d' | '2026-04-13' | 'Merge feature origin/ont_msvc14 into main' |
| bobfilez\libs\gettext | N/A | master | 'd513aad' | '2026-05-25' | 'Merge branch 'master' of https://github.com/winli... |
| bobfilez\libs\ghostpdl | N/A | master | '2379059fb' | '2026-05-28' | 'PDF interpreter - initialise Private values in FD... |
| bobfilez\libs\glad | N/A | glad2 | 'cef3f89' | '2026-04-09' | 'c: Try loading OpenGL through EGL if GLX isn't av... |
| bobfilez\libs\glib | N/A | master | '08e2002' | '2026-05-25' | 'sync: session 19 add all files and merge branches... |
| bobfilez\libs\hash-library | N/A | master | '1f94d39' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\hashcat | N/A | master | '28d049e04' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\hashingImage | N/A | master | '309a7c0' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\heif | N/A | master | 'ae87cf7' | '2026-05-25' | 'sync: session 19 add all files and merge branches... |
| bobfilez\libs\highlightjs | N/A | main | '5697ae51' | '2025-07-06' | '(enh) Add 3rd party Abc Notation grammar to Suppo... |
| bobfilez\libs\httpd | N/A | trunk | '8b4f5a4dac' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\icu4c | N/A | master | '8a1dbca2' | '2026-04-13' | 'Merge feature origin/icu4c-78.2-1 into master' |
| bobfilez\libs\image-hash | N/A | master | '9c770dae3' | '2026-06-01' | 'Merge remote-tracking branch 'origin/dependabot/n... |
| bobfilez\libs\image_info | N/A | master | 'f0ab154' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\imagehash | N/A | master | '5063b18' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\imageinfo | N/A | master | 'a257837' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\imap | N/A | master | '8b21912' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\imghash-viewer | N/A | main | '1154eb2' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\jhead | N/A | master | 'f2945d5' | '2026-05-25' | 'Merge branch 'master' of https://github.com/Matth... |
| bobfilez\libs\json-c | N/A | master | '9300a67' | '2026-05-25' | 'Merge branch 'master' of https://github.com/json-... |
| bobfilez\libs\libarchive | N/A | master | '17b4395a' | '2026-06-01' | 'Merge pull request #3082 from stoeckmann/bzip2_de... |
| bobfilez\libs\libavif | N/A | master | 'fe09b88' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\libbzip2 | N/A | master | 'c380811' | '2026-04-13' | 'Merge feature origin/bzip2-1.0.6 into master' |
| bobfilez\libs\libde265 | N/A | master | '9183675' | '2026-06-01' | 'Add SSE4.1 accelerated add_residual' |
| bobfilez\libs\libevent | N/A | master | '0ccdb859' | '2026-06-01' | 'Merge branch 'master' of https://github.com/libev... |
| bobfilez\libs\libexif | N/A | master | '6155976' | '2026-05-25' | 'Merge branch 'master' of https://github.com/libex... |
| bobfilez\libs\libffi | N/A | master | 'f791f02' | '2026-05-25' | 'Merge branch 'master' of https://github.com/libff... |
| bobfilez\libs\libgit2 | N/A | HEAD | 'e490b18b7' | '2026-05-25' | 'Merge pull request #7157 from OlekRaymond/main' |
| bobfilez\libs\libheif | N/A | master | '1df1d148' | '2026-06-01' | 'Merge branch 'master' of https://github.com/struk... |
| bobfilez\libs\libiconv | N/A | master | '42b5931' |  |  |
| bobfilez\libs\libimghash | N/A |  |  |  |  |
| bobfilez\libs\libjpeg | N/A |  |  |  |  |
| bobfilez\libs\libjpeg-turbo | N/A |  |  |  |  |
| bobfilez\libs\libmcrypt | N/A |  |  |  |  |
| bobfilez\libs\libpng | N/A |  |  |  |  |
| bobfilez\libs\librsync | N/A | master | '271744d' | '2025-08-29' | 'Merge pull request #264 from trel/trel-rdiff.md' |
| bobfilez\libs\libsodium | N/A | master | '911f62c' | '2026-05-25' | 'Merge branch 'master' of https://github.com/winli... |
| bobfilez\libs\libssh2 | N/A | master | '9329c02' | '2026-05-25' | 'Merge branch 'master' of https://github.com/winli... |
| bobfilez\libs\libtidy | N/A | master | '1665706' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\libunistd | 1.3 | master | 'bd579ab' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\libvbucket | N/A | master | 'f18a4dd' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\libvips | N/A | master | 'de292f1ac' | '2026-06-01' | 'Merge branch 'master' of https://github.com/libvi... |
| bobfilez\libs\libvpx | N/A | master | 'c35e9cb' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\libwebp | N/A | master | 'ec08809' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\libxml2 | 2.16.0 | master | '55366e5d' | '2026-06-01' | 'Merge branch 'master' of https://github.com/GNOME... |
| bobfilez\libs\libxmlplusplus | N/A | master | '3a6cda0' | '2026-05-25' | 'sync: session 19 add all files and merge branches... |
| bobfilez\libs\libxpm | N/A | master | '6eab947' | '2026-05-25' | 'Merge branch 'master' of https://github.com/winli... |
| bobfilez\libs\libxslt | N/A | master | '242f6e8' | '2026-05-25' | 'Merge branch 'master' of https://github.com/winli... |
| bobfilez\libs\libzip | N/A | main | '1e728030' | '2026-05-25' | 'Merge branch 'main' of https://github.com/nih-at/... |
| bobfilez\libs\lmdb | N/A | master | '7a041dc' | '2026-05-25' | 'Merge branch 'master' of https://github.com/winli... |
| bobfilez\libs\lsads | N/A | master | 'b349877' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\lvgl | N/A | master | '98d7c2999' | '2026-05-25' | 'sync: session 19 add all files and merge branches... |
| bobfilez\libs\lz4 | N/A | dev | 'a79e8435' | '2026-06-01' | 'Merge pull request #1755 from lz4/bye_cirrus' |
| bobfilez\libs\md4c | N/A | master | '6ed63d1' | '2026-05-31' | 'Fix broken testcase related to #352.' |
| bobfilez\libs\metastore | N/A | master | '9b78b5d' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\mm_file | N/A | master | 'e57b1b0' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\mpir | N/A | master | 'ee0bc0e' | '2026-05-25' | 'Merge branch 'master' of https://github.com/winli... |
| bobfilez\libs\mpv | N/A | master | 'a863e08a21' | '2026-06-01' | 'Merge branch 'master' of https://github.com/mpv-p... |
| bobfilez\libs\net-snmp | N/A | master | 'c5119d1' | '2026-05-25' | 'Merge branch 'master' of https://github.com/winli... |
| bobfilez\libs\nghttp2 | N/A | master | '2924fed' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\nihtest | N/A | main | '971f34b' | '2026-05-25' | 'Merge branch 'main' of https://github.com/nih-at/... |
| bobfilez\libs\nihtest-cpp | N/A | main | '6f417fd' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\oniguruma | N/A | master | '9f47fdf' | '2026-05-25' | 'Merge branch 'master' of https://github.com/winli... |
| bobfilez\libs\openapv | N/A | main | '4c5180c' | '2026-05-25' | 'Merge branch 'main' of https://github.com/Academy... |
| bobfilez\libs\opencv | N/A | 4.x | 'd1581abe27' | '2026-06-01' | 'Merge branch '4.x' of https://github.com/opencv/o... |
| bobfilez\libs\openexr | N/A | main | 'ad5022c6' | '2026-06-01' | 'Merge branch 'main' of https://github.com/Academy... |
| bobfilez\libs\openfx | N/A | main | '2f286ac' | '2026-06-01' | 'Merge branch 'main' of https://github.com/Academy... |
| bobfilez\libs\openh264 | N/A | master | '672eeb36' | '2026-05-25' | 'Merge branch 'master' of https://github.com/cisco... |
| bobfilez\libs\openjpeg | N/A | master | '5a7241d4' | '2026-05-25' | 'Merge branch 'master' of https://github.com/uclou... |
| bobfilez\libs\openldap | N/A | master | '4932387' | '2026-05-25' | 'sync: session 19 add all files and merge branches... |
| bobfilez\libs\openssl | N/A | 4.0 | '8729d6d5' | '2026-05-05' | 'Update to 4.0.0' |
| bobfilez\libs\p7zip | N/A | master | '6819e2d' | '2025-05-20' | 'move license file to the root director (#252)' |
| bobfilez\libs\pHash | N/A | main | '2f69861' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\pHash.c | N/A | main | 'a03872e' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\pandoc | N/A | main | '903843948' | '2026-06-01' | 'Fix typo in stack.yaml.' |
| bobfilez\libs\pcre2 | N/A | main | '3f6e8efd' | '2026-05-25' | 'Merge branch 'main' of https://github.com/PCRE2Pr... |
| bobfilez\libs\perceptual-dct-hash | N/A | master | 'c533281' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\pngquant | N/A | main | '1808c8f' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\poppler | N/A | master | 'a2cf35eb' | '2026-06-01' | 'Update (C)' |
| bobfilez\libs\postgresql | N/A | master | '8b0120b2' | '2026-05-25' | 'sync: session 19 add all files and merge branches... |
| bobfilez\libs\pslib | N/A | main | '881d8e5' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\pthreads | N/A | main | '3015396' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\pxz | N/A | master | '6469dd6' | '2026-04-11' | 'chore: save progress before update' |
| bobfilez\libs\qdbm | N/A | master | '1a556e3' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\radare2 | N/A | master | 'ae883b6c79' | '2026-06-01' | 'Merge branch 'master' of https://github.com/radar... |
| bobfilez\libs\rapidjson | N/A | master | '382c9a9' | '2026-06-01' | 'chore: save progress before update' |
| bobfilez\libs\raylib | N/A | master | '278d00705' | '2026-06-01' | 'Merge branch 'master' of https://github.com/raysa... |
| bobfilez\libs\re2 | N/A | main | '972a15c' | '2026-01-22' | 're2: remove unnecessary & in MutexLock usage' |
| bobfilez\libs\rename-utils | N/A | main | 'b54c01ec' | '2026-05-18' | 'Add more docstrings.' |
| bobfilez\libs\ripgrep | N/A | master | '4857d6f' | '2026-05-26' | 'docs: s/our projects/this project in AI policy' |
| bobfilez\libs\securecopy | N/A | master | 'd4cb8e4' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\seek-tune | N/A | main | '5374d39' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\sigil | N/A | master | '16d3dbf36' | '2026-05-31' | 'more updates to the ChangeLog.txt [skip ci]' |
| bobfilez\libs\sqlite | 3.54.0 | master | '13c9399550' | '2026-05-25' | 'sync: session 19 add all files and merge branches... |
| bobfilez\libs\sqlite3 | N/A | master | '817931b' | '2026-04-11' | 'chore: save progress before update' |
| bobfilez\libs\ssdeep | N/A | master | 'd0e31a5' | '2026-04-11' | 'chore: save progress before update' |
| bobfilez\libs\sumatrapdf | N/A | master | 'd980442ff' | '2026-05-25' | 'sync: session 19 add all files and merge branches... |
| bobfilez\libs\the_silver_searcher | N/A | master | 'a61f178' | '2020-12-16' | 'Merge pull request #1424 from sanjaymsh/ppc64le' |
| bobfilez\libs\tinyphash | N/A | master | 'ccab513' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\tinyxml2 | N/A | master | '8224e42' | '2026-05-23' | 'Merge branch 'master' of github.com:leethomason/t... |
| bobfilez\libs\ultimatepp | N/A | master | '20c352c7c' | '2026-06-01' | 'CtrlCore: Fixed to compile in Linux' |
| bobfilez\libs\util-linux | N/A | master | '8d3fd92f8' | '2026-05-25' | 'Merge branch 'master' of https://github.com/util-... |
| bobfilez\libs\vlc | N/A | master | '9b943a3e49' | '2026-05-25' | 'Merge branch 'master' of https://github.com/video... |
| bobfilez\libs\wineditline | N/A | master | '20dd166' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\wkhtmltopdf | 0.12.7-dev | master | 'd398c8a' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\xattrlib | N/A | master | '85522f2' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\xattrs | N/A | master | 'b60f534' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\xxHash | N/A | dev | 'c65bb60' | '2026-06-01' | 'Merge branch 'dev' of https://github.com/Cyan4973... |
| bobfilez\libs\ziptools | N/A | main | 'b9864d1' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\zlib | N/A | master | 'bc33e6c' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\zstd | N/A | dev | '5233c58e' | '2026-05-14' | '[doc] Clarify requirements around Block_Maximum_S... |
| bobmani\arrowvortex\odcnn | N/A | master | '454f4c7' | '2020-02-26' | 'small change' |
| bobmani\beatoraja\bobcoin | N/A | main | '9a1dcff' | '2026-04-14' | 'Merge branch 'main' of https://github.com/robertp... |
| bobmani\beatoraja\lr2oraja-endlessdream | N/A | main | '47d3b7f5' | '2026-04-14' | 'Merge feature origin/bugfix-key-c-binding into ma... |
| bobmani\bobmania\bobcoin | N/A | main | '77089464' | '2026-06-04' | 'chore: sync working tree' |
| bobmani\ddc\ddc_onset | N/A | main | '5d7572a' | '2026-05-02' | 'sync: update project state' |
| bobmani\ddc\ffr-difficulty-model | N/A | master | 'b13fe4f' | '2026-05-02' | 'sync: update project state' |
| bobmani\itgmania\bobcoin | N/A | HEAD | '64575ee3' | '2026-06-02' | 'chore: sync working tree' |
| bobmani\ksm-v2\ksmaxis | N/A | master | 'dc522d0' | '2026-04-14' | 'chore: save local progress before sync' |
| bobmani\ksm-v2\kson | N/A | master | 'cadcff4' | '2026-03-08' | 'Reset curve a,b after curve expansion' |
| bobmani\linthesia\pianogame | N/A | master | '1ece599' | '2026-05-21' | 'chore: complete project audit and memory leak cle... |
| bobsgameonlinejava\libs\aseprite-file | N/A | master | '06b6189' | '2018-12-01' | 'Update README.md' |
| bobsgameonlinejava\libs\bobui | N/A | main | '32ee250ec5' | '2026-06-01' | 'chore: save progress before update' |
| bobsgameonlinejava\libs\commons-lang | N/A | master | '62ea4b620' | '2026-05-29' | 'Update POM SCM tag' |
| bobsgameonlinejava\libs\jinput | N/A | master | 'f79007c' | '2026-04-03' | 'Merge pull request #409 from jinput/dependabot/ma... |
| bobsgameonlinejava\libs\lwjgl3 | N/A | HEAD | '01b1fa7be' | '2026-06-14' | 'build(core) fix FFI_DEFAULT_ABI on ppc64le' |
| bobsgameonlinejava\libs\lz4-java | N/A | master | 'ed8e580' | '2026-06-01' | 'chore: save progress before update' |
| bobsgameonlinejava\libs\micromod | N/A | master | '83b5d9a' | '2026-04-14' | 'More consistent resampling behaviour.' |
| bobsgameonlinejava\libs\mysql-connector-j | N/A | release/9.x | '0aade1f1' | '2026-03-18' | 'Fix for Bug#119863 (Bug#38951042), Inaccurate dec... |
| bobsgameonlinejava\libs\twl-lwjgl3 | N/A | master | '647ec34' | '2016-10-02' | 'Update README.md' |
| bobsgameonlinejava\libs\xpp3 | N/A | master | '68498e7' | '2025-04-13' | 'Remove oss-parent and add GPG and central publish... |
| bobsgameonlinejava\libs\xz-java | N/A | master | '492b6ea' | '2026-03-01' | 'Fix copy-paste errors in NEWS.md' |
| bobsgameonlinejava\references\Cytopia | N/A | master | 'b67e255d' | '2025-03-28' | 'Migrate config renovate.json' |
| bobsgameonlinejava\references\DTile | N/A | master | '22a977f' | '2018-04-04' | 'Add keyboard shortcuts to rename dialog and make ... |
| bobsgameonlinejava\references\GrowTools | N/A | master | 'fe146b8' | '2025-11-21' | 'Update rtconverter.html' |
| bobsgameonlinejava\references\LibreSprite | N/A | master | 'ea601594b' | '2026-06-01' | 'chore: save progress before update' |
| bobsgameonlinejava\references\OgmoEditor3-CE | N/A | master | 'b2a5215' | '2022-01-19' | 'Merge pull request #209 from hubol/support-tabbin... |
| bobsgameonlinejava\references\Pixelorama | N/A | master | 'd023704c' | '2026-06-01' | 'Allow exporting tilesets from the layer propertie... |
| bobsgameonlinejava\references\PixiEditor | N/A | master | '47961f1c5' | '2026-06-01' | 'chore: save progress before update' |
| bobsgameonlinejava\references\PyxleOS | N/A | master | '624359c' | '2017-03-26' | 'haha typo' |
| bobsgameonlinejava\references\Raylib-Examples | N/A | master | 'abe00d9' | '2023-02-20' | 'Update README.md' |
| bobsgameonlinejava\references\Simple-Sprite-Tile-2D | N/A | master | 'c5ba692' | '2017-04-10' | 'Fix Scale.Z vector' |
| bobsgameonlinejava\references\SpeedEd | N/A | main | '0be20dc' | '2022-01-01' | 'Update year in Copyright notice' |
| bobsgameonlinejava\references\Tile-Studio | N/A | master | 'd0f5d2e' | '2021-07-17' | 'Palette manager: save as GIMP Palette' |
| bobsgameonlinejava\references\aseprite | N/A | main | '82d99d492' | '2026-06-01' | 'chore: save progress before update' |
| bobsgameonlinejava\references\aseprite-guide | N/A | main | '471c8ec' | '2025-10-03' | 'Update AsepriteV1.3.4.md' |
| bobsgameonlinejava\references\blockbench | N/A | master | '8fe8d9d9' | '2026-04-25' | 'v5.1.4 [ci-build]' |
| bobsgameonlinejava\references\bottled-up-tilemap | N/A | daelon-refactor | '7a93386' | '2023-04-07' | 'Update README.md' |
| bobsgameonlinejava\references\csprite | N/A | master | '11eca90' | '2025-08-05' | 'Update function names' |
| bobsgameonlinejava\references\defold | 1.13.1 | dev | '2f81a4eb1b' | '2026-06-01' | 'Fix POSIX crash signal chaining (#12480)' |
| bobsgameonlinejava\references\goxel | N/A | master | 'c84ad6dc' | '2026-04-30' | 'Ignore some imgui warnings on Mac' |
| bobsgameonlinejava\references\grafx2 | N/A | HEAD | '94b1babf' | '2020-12-11' | 'Remove obsolete tag from Doxyfile' |
| bobsgameonlinejava\references\grafx2-dos | N/A | master | '4258bdd' | '2022-04-03' | 'Remove leading directory names from paths.' |
| bobsgameonlinejava\references\love2d | N/A | main | 'c95b8cf79' | '2026-05-31' | 'graphics: add rgb10a2ui pixel format.' |
| bobsgameonlinejava\references\phaser | N/A | master | '4acd940eb' | '2026-05-27' | 'Fix `DrawingContext#beginDraw` calling unnecessar... |
| bobsgameonlinejava\references\piskel | N/A | master | 'a6b9c02d' | '2026-04-09' | 'Merge pull request #1260 from juliandescottes/tes... |
| bobsgameonlinejava\references\raster-master | N/A | main | '9679baf' | '2026-03-20' | 'Update 6.0 R127' |
| bobsgameonlinejava\references\retro-game-editor | N/A | master | 'e3b910c' | '2026-06-01' | 'chore: save progress before update' |
| bobsgameonlinejava\references\rx | N/A | master | '1bcbe90' | '2023-07-02' | 'Fix SVG rendering' |
| bobsgameonlinejava\references\sprite-studio-64 | N/A | main | 'ecd1b73' | '2026-04-17' | 'Update README with note on Master of Sprites' |
| bobsgameonlinejava\references\stipple-effect | N/A | master | 'a47e8fa' | '2025-01-30' | 'Merge pull request #179 from stipple-effect/dev-b... |
| bobsgameonlinejava\references\tactile | N/A | main | 'eb98a4c7c' | '2022-09-07' | 'Update vcpkg.json' |
| bobsgameonlinejava\references\tiled | N/A | master | 'e2aa23008' | '2026-06-01' | 'Add command variables %exportfile and %exportpath... |
| bobsgameonlinejava\references\tilemap-editor | N/A | main | '758cdbb' | '2022-12-07' | 'tilemap editor api improvements' |
| bobsgameonlinejava\references\tilemap-studio | N/A | master | '244378b' | '2026-05-02' | 'Update FLTK to 1.4.5 (#94)' |
| bobsgameonlinejava\references\voidsprite | N/A | HEAD | 'e18443a' | '2026-05-15' | 'loop animation option in gif export' |
| bobsgameweb\submodules\bobui | N/A | main | '9158674f9e' | '2026-06-01' | 'Merge branch 'main' of https://github.com/robertp... |
| bqt\submodules\juce | N/A | master | '0729f131f8' | '2026-04-22' | 'chore: sync v2.7.0' |
| bqt\submodules\ultimatepp | N/A | HEAD | 'fb2a4bc30' | '2026-06-14' | 'CtrlLib: Fixed problem with DisplayPopup getting ... |
| f-zerox\tools\asm-differ | N/A | HEAD | 'dd7f9f0' | '2026-04-01' | 'Fix --compress-matching with three-way diffing' |
| f-zerox\tools\asm-processor | N/A | HEAD | '7864598' | '2026-03-17' | 'Fix Rust version not removing .asmproc.d when no ... |
| f-zerox\tools\ido5.3_cc | N/A | master | 'faa773c' | '2019-12-24' | 'ido 5.3' |
| f-zerox\tools\splat | N/A | HEAD | 'd503762' | '2026-03-30' | 'Explicit UTF-8 for everything (#530)' |
| freellm\third_party\LLMLingua | N/A | main | 'e0e9d99' | '2025-10-28' | 'Merge pull request #230 from liyucheng09/slingua' |
| freellm\third_party\headroom | N/A | main | 'b0cd0329' | '2026-06-17' | 'fix(proxy): stamp X-Client: codex on Responses en... |
| freellm\third_party\rtk | N/A | develop | 'abe7d42' | '2026-06-16' | 'fix(grep): use portable --null in system grep fal... |
| freellm\third_party\tokdiet | N/A | main | '7de2c8b' | '2026-06-17' | 'feat: enhance for dynamic upstream via headers' |
| geany\subprojects\bobgui | N/A | main | '7f77d6f310' | '2026-04-21' | 'merge: 4854-copy-to-with-manual-location-entry-us... |
| geany\subprojects\bobui | N/A | HEAD | 'c7e1fc7059a' | '2026-06-19' | 'fix: update submodule pointers to valid HEAD â€” ... |
| geany\subprojects\btk | 0.2.0 | HEAD | '0ccafdbdfb8' | '2026-06-20' | 'fix: update bobui-reference submodule pin to vali... |
| hyperharness\llamafile\llama.cpp | N/A | master | '3142f1dbb' | '2026-04-29' | 'ggml-cuda: refactor fusion code (#22468)' |
| hyperharness\llamafile\stable-diffusion.cpp | N/A | master | '73ce4b8' | '2026-04-14' | 'chore: save local progress before sync' |
| hyperharness\llamafile\whisper.cpp | N/A | master | '93727cda' | '2026-04-14' | 'chore: save local progress before sync' |
| mcp-superassistant\packages\byterover-cipher | N/A | HEAD | 'e080f240' | '2026-04-14' | 'fix: [ENG-2085] strip ANSI codes in query-rendere... |
| mk64\tools\asm-differ | N/A | HEAD | 'dd7f9f0' | '2026-04-01' | 'Fix --compress-matching with three-way diffing' |
| mk64\tools\decomp-permuter | N/A | HEAD | 'efc5c5e' | '2026-04-03' | 'Strip all dependency generation flags (#200)' |
| mk64\tools\torch | N/A | HEAD | '86a69ba' | '2026-04-09' | 'Merge pull request #220 from inspectredc/fzx-base... |
| projectm\vendor\projectm-eval | N/A | HEAD | 'da885dc' | '2026-02-01' | 'Bump version to 1.0.6' |
| ArrowVortex\lib\ddc\ddc_onset | N/A | HEAD | '5d7572a' | '2026-05-02' | 'sync: update project state' |
| ArrowVortex\lib\ddc\ffr-difficulty-model | N/A | HEAD | 'b13fe4f' | '2026-05-02' | 'sync: update project state' |
| bg\bobsgameonlinejava\libs\aseprite-file | N/A |  |  |  |  |
| bg\bobsgameonlinejava\libs\bobui | N/A |  |  |  |  |
| bg\bobsgameonlinejava\libs\commons-lang | N/A |  |  |  |  |
| bg\bobsgameonlinejava\libs\jinput | N/A |  |  |  |  |
| bg\bobsgameonlinejava\libs\lwjgl3 | N/A |  |  |  |  |
| bg\bobsgameonlinejava\libs\lz4-java | N/A |  |  |  |  |
| bg\bobsgameonlinejava\libs\micromod | N/A |  |  |  |  |
| bg\bobsgameonlinejava\libs\mysql-connector-j | N/A |  |  |  |  |
| bg\bobsgameonlinejava\libs\twl-lwjgl3 | N/A |  |  |  |  |
| bg\bobsgameonlinejava\libs\xpp3 | N/A |  |  |  |  |
| bg\bobsgameonlinejava\libs\xz-java | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\Cytopia | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\DTile | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\GrowTools | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\LibreSprite | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\OgmoEditor3-CE | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\Pixelorama | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\PixiEditor | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\PyxleOS | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\Raylib-Examples | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\Simple-Sprite-Tile-2D | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\SpeedEd | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\Tile-Studio | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite-guide | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\blockbench | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\bottled-up-tilemap | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\csprite | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\defold | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\goxel | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\grafx2 | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\grafx2-dos | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\love2d | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\phaser | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\piskel | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\raster-master | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\retro-game-editor | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\rx | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\sprite-studio-64 | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\stipple-effect | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\tactile | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\tiled | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\tilemap-editor | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\tilemap-studio | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\voidsprite | N/A |  |  |  |  |
| bg\okgame\lib\CTPL | N/A |  |  |  |  |
| bg\okgame\lib\Craft | N/A |  |  |  |  |
| bg\okgame\lib\FBNeo | N/A |  |  |  |  |
| bg\okgame\lib\GWEN | N/A |  |  |  |  |
| bg\okgame\lib\Genesis-Plus-GX | N/A |  |  |  |  |
| bg\okgame\lib\MODPlay | N/A |  |  |  |  |
| bg\okgame\lib\Maelstrom | N/A |  |  |  |  |
| bg\okgame\lib\MicroPather | N/A |  |  |  |  |
| bg\okgame\lib\MilkDrop3 | N/A |  |  |  |  |
| bg\okgame\lib\Nuklear | N/A |  |  |  |  |
| bg\okgame\lib\RetroArch | N/A |  |  |  |  |
| bg\okgame\lib\SDL | N/A |  |  |  |  |
| bg\okgame\lib\SDL2_gfx | N/A |  |  |  |  |
| bg\okgame\lib\SDL_gesture | N/A |  |  |  |  |
| bg\okgame\lib\SDL_image | N/A |  |  |  |  |
| bg\okgame\lib\SDL_mixer | N/A |  |  |  |  |
| bg\okgame\lib\SDL_native_midi | N/A |  |  |  |  |
| bg\okgame\lib\SDL_net | N/A |  |  |  |  |
| bg\okgame\lib\SDL_rtf | N/A |  |  |  |  |
| bg\okgame\lib\SDL_ttf | N/A |  |  |  |  |
| bg\okgame\lib\Snippets | N/A |  |  |  |  |
| bg\okgame\lib\UACME | N/A |  |  |  |  |
| bg\okgame\lib\WavPack | N/A |  |  |  |  |
| bg\okgame\lib\aom | N/A |  |  |  |  |
| bg\okgame\lib\boost | N/A |  |  |  |  |
| bg\okgame\lib\cppcodec | N/A |  |  |  |  |
| bg\okgame\lib\dav1d | N/A |  |  |  |  |
| bg\okgame\lib\defold-astar | N/A |  |  |  |  |
| bg\okgame\lib\flac | N/A |  |  |  |  |
| bg\okgame\lib\freetype | N/A |  |  |  |  |
| bg\okgame\lib\gambatte-libretro | N/A |  |  |  |  |
| bg\okgame\lib\game-music-emu | N/A |  |  |  |  |
| bg\okgame\lib\glad | N/A |  |  |  |  |
| bg\okgame\lib\glew | N/A |  |  |  |  |
| bg\okgame\lib\glfw | N/A |  |  |  |  |
| bg\okgame\lib\gpsp | N/A |  |  |  |  |
| bg\okgame\lib\harfbuzz | N/A |  |  |  |  |
| bg\okgame\lib\highway | N/A |  |  |  |  |
| bg\okgame\lib\imgui | N/A |  |  |  |  |
| bg\okgame\lib\jpeg | N/A |  |  |  |  |
| bg\okgame\lib\libavif | N/A |  |  |  |  |
| bg\okgame\lib\libjxl | N/A |  |  |  |  |
| bg\okgame\lib\libmidi | N/A |  |  |  |  |
| bg\okgame\lib\libmodplug | N/A |  |  |  |  |
| bg\okgame\lib\libpng | N/A |  |  |  |  |
| bg\okgame\lib\libretro-common | N/A |  |  |  |  |
| bg\okgame\lib\libretro-fceumm | N/A |  |  |  |  |
| bg\okgame\lib\libretro-lutro | N/A |  |  |  |  |
| bg\okgame\lib\libretro-samples | N/A |  |  |  |  |
| bg\okgame\lib\libretro-super | N/A |  |  |  |  |
| bg\okgame\lib\libtiff | 4.7.1 |  |  |  |  |
| bg\okgame\lib\libtimidity | N/A |  |  |  |  |
| bg\okgame\lib\libusb | N/A |  |  |  |  |
| bg\okgame\lib\libwebp | N/A |  |  |  |  |
| bg\okgame\lib\libxmp | N/A |  |  |  |  |
| bg\okgame\lib\lz4-java | N/A |  |  |  |  |
| bg\okgame\lib\md5-c | N/A |  |  |  |  |
| bg\okgame\lib\melonDS | N/A |  |  |  |  |
| bg\okgame\lib\mgba | N/A |  |  |  |  |
| bg\okgame\lib\miniz | N/A |  |  |  |  |
| bg\okgame\lib\mpg123 | N/A |  |  |  |  |
| bg\okgame\lib\mpv | N/A |  |  |  |  |
| bg\okgame\lib\nanogui | N/A |  |  |  |  |
| bg\okgame\lib\nanogui-sdl | N/A |  |  |  |  |
| bg\okgame\lib\nestopia | N/A |  |  |  |  |
| bg\okgame\lib\nngui | N/A |  |  |  |  |
| bg\okgame\lib\ogg | N/A |  |  |  |  |
| bg\okgame\lib\opus | N/A |  |  |  |  |
| bg\okgame\lib\opusfile | N/A |  |  |  |  |
| bg\okgame\lib\paulxstretch | N/A |  |  |  |  |
| bg\okgame\lib\picodrive | N/A |  |  |  |  |
| bg\okgame\lib\plutosvg | N/A |  |  |  |  |
| bg\okgame\lib\plutovg | N/A |  |  |  |  |
| bg\okgame\lib\poco | 1.15.1 |  |  |  |  |
| bg\okgame\lib\projectm | N/A |  |  |  |  |
| bg\okgame\lib\raylib | N/A |  |  |  |  |
| bg\okgame\lib\retroarch-assets | N/A |  |  |  |  |
| bg\okgame\lib\retroarch-joypad-autoconfig | N/A |  |  |  |  |
| bg\okgame\lib\sdl2-compat | N/A |  |  |  |  |
| bg\okgame\lib\sigar | N/A |  |  |  |  |
| bg\okgame\lib\snes9x | N/A |  |  |  |  |
| bg\okgame\lib\snes9x2010 | N/A |  |  |  |  |
| bg\okgame\lib\soundtouch | N/A |  |  |  |  |
| bg\okgame\lib\stb | N/A |  |  |  |  |
| bg\okgame\lib\timidity | N/A |  |  |  |  |
| bg\okgame\lib\tremor | N/A |  |  |  |  |
| bg\okgame\lib\vba-next | N/A |  |  |  |  |
| bg\okgame\lib\vbam-libretro | N/A |  |  |  |  |
| bg\okgame\lib\vorbis | N/A |  |  |  |  |
| bg\okgame\lib\zlib | N/A |  |  |  |  |
| bobfilez\ai-file-sorter\external\Catch2 | N/A | devel | '2318c101' | '2026-04-13' | 'chore: save local progress before sync' |
| bobfilez\libs\SysmonForLinux\sysmonCommon | N/A | main | 'b52df2c' | '2026-05-25' | 'Merge branch 'main' of https://github.com/Microso... |
| bobfilez\libs\pngquant\lib | N/A | main | '198571b' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\wkhtmltopdf\qt | N/A | wk_4.8.7 | 'cc6d5e1d37' | '2026-04-14' | 'chore: save local progress before sync' |
| bobmani\bobmania\Themes\Simply-Love-SM5 | N/A | itgmania-release | 'e9ac235b' | '2026-03-26' | 'Remove (beta)' |
| bobmani\itgmania\Themes\Simply Love | N/A | HEAD | 'e9ac235b' | '2026-03-26' | 'Remove (beta)' |
| bobmani\itgmania\Themes\Simply-Love-SM5 | N/A | HEAD | 'e9ac235b' | '2026-03-26' | 'Remove (beta)' |
| bobsaver\projectm\vendor\projectm-eval | N/A | HEAD | 'da885dc' | '2026-02-01' | 'Bump version to 1.0.6' |
| bobsgameonlinejava\references\aseprite\laf | N/A | main | '1cddb56' | '2026-05-29' | 'Add "no AI" declaration' |
| bobtrader\submodules\page-02\Bohr1005__xcrypto | N/A | main | '3d9fb4d' | '2025-01-18' | 'Update README.md' |
| bobtrader\submodules\page-02\JulyIghor__QtBitcoinTrader | N/A | master | '7941537' | '2025-06-25' | 'cleanup' |
| bobtrader\submodules\page-02\Roibal__Cryptocurrency-Trading-Bots-Python-Beginner-Advance | N/A | master | '6cd9f63' | '2019-01-18' | 'Print Exception Raised' |
| bobtrader\submodules\page-02\TraderAlice__OpenAlice | N/A | master | 'a387c96' | '2026-06-01' | 'Merge pull request #248 from TraderAlice/harness-... |
| bobtrader\submodules\page-02\ctubio__Krypto-trading-bot | N/A | master | 'f592cc3c' | '2024-12-15' | 'Updated highcharts UI dependency.' |
| bobtrader\submodules\page-02\jammy928__CoinExchange_CryptoExchange_Java | N/A | master | '8adf508' | '2021-11-05' | 'Update README.md' |
| bobtrader\submodules\page-02\pirate__crypto-trader | N/A | master | 'ec5d709' | '2019-04-03' | 'Update README.md' |
| bobtrader\submodules\page-02\scrtlabs__catalyst | N/A | master | '2e802978' | '2021-09-22' | 'Merge pull request #585 from enigmampc/project-de... |
| bobtrader\submodules\page-02\taniman__profit-trailer | N/A | master | '04d8f20' | '2020-05-14' | 'Update README.md' |
| bobtrader\submodules\page-02\warp-id__solana-trading-bot | N/A | master | '4c9304a' | '2024-05-22' | 'Merge pull request #109 from ajakka/master' |
| bobtrader\submodules\page-03\AdeelMufti__CryptoBot | N/A | master | '6cbdfea' | '2017-01-17' | 'Initial commit' |
| bobtrader\submodules\page-03\Ekliptor__WolfBot | N/A | master | '0f45aae' | '2023-02-17' | 'updated dependencies' |
| bobtrader\submodules\page-03\GuillermoEguilaz__Polymarket-Crypto-Trading-Bot | N/A | main | 'aa9759f' | '2026-04-29' | 'Merge pull request #3 from GuillermoEguilaz/dev' |
| bobtrader\submodules\page-03\Krypto-Hashers-Community__polymarket-crypto-sports-arbitrage-trading-bot | N/A | main | '4f53f77' | '2026-03-29' | 'Update README.md' |
| bobtrader\submodules\page-03\RobertMarcellos__polymarket-copy-trading-bot | N/A | main | '6a98bf3' | '2026-04-05' | 'version 2.0' |
| bobtrader\submodules\page-03\ericjang__cryptocurrency_arbitrage | N/A | master | '88d5429' | '2026-04-10' | 'chore: remove orphan submodule entry fxbtc' |
| bobtrader\submodules\page-03\kelvinau__crypto-arbitrage | N/A | master | '44a3469' | '2024-02-17' | 'add link to introduction of professional trader c... |
| bobtrader\submodules\page-03\markusaksli__TradeBot | N/A | master | '2296fe6' | '2024-11-05' | 'Bump commons-io:commons-io from 2.8.0 to 2.14.0 (... |
| bobtrader\submodules\page-03\saniales__golang-crypto-trading-bot | N/A | main | '02695e5' | '2025-09-30' | 'fix(examples): Removed Slack example due to libra... |
| bobtrader\submodules\page-03\steeply__gbot-trader | N/A | master | 'c8240aa' | '2024-05-14' | 'fix candles bitfinex' |
| bobtrader\submodules\page-04\ArsenAbazian__CryptoTradingFramework | N/A | master | '1962078' | '2024-09-08' | 'Remove Warnings' |
| bobtrader\submodules\page-04\PolyStrategy__Polymarket-Crypto-Market-Bot | N/A | main | 'a66249b' | '2026-04-01' | 'Merge branch 'chore/q1-2026-sync'' |
| bobtrader\submodules\page-04\bitisanop__CryptoExchange_TradingPlatform_CoinExchange | N/A | main | '9ad7651' | '2025-02-19' | 'Update README.md' |
| bobtrader\submodules\page-04\blockplusim__crypto_trading_service_for_tradingview | N/A | main | '2265e6e' | '2022-08-27' | 'Update README.md' |
| bobtrader\submodules\page-04\c9s__bbgo | N/A | main | '816670ada' | '2026-04-14' | 'add v1.64.2 release note' |
| bobtrader\submodules\page-04\ccxt__ccxt | N/A | master | '98076b3' | '2026-04-14' | '[Automated changes] GO files' |
| bobtrader\submodules\page-04\hackingthemarkets__binance-tutorials | N/A | master | '791930d' | '2020-08-16' | 'Update README.md' |
| bobtrader\submodules\page-04\hello2all__gamma-ray | N/A | main | '444dce0' | '2022-02-07' | 'Merge pull request #10 from prgtrdr/main' |
| bobtrader\submodules\page-04\paulcpk__freqtrade-strategies-that-work | N/A | main | '1e154a2' | '2021-06-14' | '#1 fix classname spelling in EMAPriceCrossoverWit... |
| bobtrader\submodules\page-05\6551Team__opennews-mcp | N/A | main | 'e4f40e1' | '2026-04-10' | 'feat: add prediction engine category (12 AI predi... |
| bobtrader\submodules\page-05\AI4Finance-Foundation__FinRL_Crypto | N/A | master | '495a428' | '2025-12-15' | 'Merge pull request #12 from xsa-dev/master' |
| bobtrader\submodules\page-05\CyberPunkMetalHead__gateio-crypto-trading-bot-binance-announcements-new-coins | N/A | master | '180763f' | '2022-01-17' | 'Update README.md' |
| bobtrader\submodules\page-05\JPStrydom__Crypto-Trading-Bot | N/A | master | '94b5aab' | '2021-02-10' | 'Updated readme formatting' |
| bobtrader\submodules\page-05\Mathieu2301__TradingView-API | N/A | main | '574a994' | '2026-04-11' | 'WAF Bypass && getUser max redirect (#310)' |
| bobtrader\submodules\page-05\asavinov__intelligent-trading-bot | N/A | master | '5289048' | '2026-04-14' | 'update documentation' |
| bobtrader\submodules\page-05\fluidex__dingir-exchange | N/A | master | 'f120efe' | '2026-04-13' | 'chore: save local progress before sync' |
| bobtrader\submodules\page-05\ned0flanders__Cryptocoinopoly | N/A | master | 'ec6969f' | '2017-12-31' | 'Add files via upload' |
| bobtrader\submodules\page-05\nicolasbonnici__cryptobot | N/A | develop | '78bdf1e' | '2021-08-10' | 'docs: fix typos (#19)' |
| bobtrader\submodules\page-06\MohammedRashad__Crypto-Copy-Trader | N/A | master | '26016c5' | '2023-04-08' | 'Update README.md' |
| bobtrader\submodules\page-06\Nafidinara__bot-pancakeswap | N/A | master | '40cf4c8' | '2022-02-05' | 'add setting' |
| bobtrader\submodules\page-06\SFCQuantX__polymarket-trading-agent | N/A | main | '20a247e' | '2026-03-30' | 'full update' |
| bobtrader\submodules\page-06\andresilvasantos__bitprophet | N/A | master | '693765a' | '2022-01-14' | 'Fix README' |
| bobtrader\submodules\page-06\fabston__TradingView-Webhook-Bot | N/A | master | '7eff8f9' | '2024-05-01' | 'Update main.py' |
| bobtrader\submodules\page-06\johndpope__CryptoCurrencyTrader | N/A | master | 'd0dd817' | '2021-06-04' | 'Merge pull request #3 from johndpope/dependabot/p... |
| bobtrader\submodules\page-06\nicknochnack__LLMAgentCrypto | N/A | main | 'cddada6' | '2025-04-28' | 'init commit' |
| bobtrader\submodules\page-06\unterstein__binance-trader | N/A | master | '8c3d471' | '2018-01-16' | 'added maven to prerequisites (#16)' |
| bobtrader\submodules\page-06\wangzhe3224__awesome-systematic-trading | N/A | master | 'fa002bf' | '2026-04-14' | 'Add PolyMind to Relevant Projects section (#82)' |
| bobtrader\submodules\page-06\whittlem__pycryptobot | N/A | main | '1fa9aae' | '2024-03-04' | 'Merge pull request #841 from whittlem/beta' |
| bobtrax\bobui\submodules\juce | N/A | HEAD | '3ba67d4585' | '2026-05-21' | 'CI: Add juce9 branch' |
| bobtrax\bobui\submodules\ultimatepp | N/A | HEAD | 'fb2a4bc30' | '2026-06-14' | 'CtrlLib: Fixed problem with DisplayPopup getting ... |
| bobtrax\lmms\doc\wiki | N/A | HEAD | '538199f' | '2026-05-25' | 'Updated Dependencies OpenBSD (markdown)' |
| hyperharness\llamafile\stable-diffusion.cpp\ggml | N/A | master | '1ffa6b11' | '2026-04-14' | 'Merge branch 'master' of https://github.com/ggml-... |
| hyperharness\llamafile\third_party\zipalign | N/A | main | '2ee1385' | '2025-11-28' | 'Test it works with BSD make' |
| mk64\tools\blender\fast64 | N/A | HEAD | 'd517bc4' | '2026-04-10' | '[SM64] Assume "has sm64 settings" -> should load ... |
| OmniRoute\.next\standalone\workspace\OmniRoute | N/A |  |  |  |  |
| bcs\external\bqt-reference\submodules\juce | N/A | HEAD | '3ba67d4585' | '2026-05-21' | 'CI: Add juce9 branch' |
| bcs\external\bqt-reference\submodules\ultimatepp | N/A | HEAD | '26632191f' | '2026-06-05' | 'Merge branch 'master' of https://github.com/ultim... |
| bg\bobsgameonlinejava\references\aseprite\laf | N/A |  |  |  |  |
| bg\okgame\lib\boost\more | N/A |  |  |  |  |
| bg\okgame\lib\libjxl\testdata | N/A |  |  |  |  |
| bg\okgame\lib\plutosvg\plutovg | N/A |  |  |  |  |
| bg\okgame\lib\vbam-libretro\dependencies | N/A |  |  |  |  |
| bobfilez\libs\OpenRV\src\pub | N/A | main | '44a8d2b' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\bobgui\submodules\juce | N/A | master | '3ba67d4585' | '2026-05-21' | 'CI: Add juce9 branch' |
| bobfilez\libs\bobgui\submodules\ultimatepp | N/A | master | '70e1422bf' | '2026-05-24' | 'Core/SSL: Hardened AES-GCM-256 encryption/decrypt... |
| bobfilez\libs\bobui\submodules\juce | N/A | master | 'dc190df0e7' | '2026-05-25' | 'sync: session 19 add all files and merge branches... |
| bobfilez\libs\bobui\submodules\ultimatepp | N/A | master | 'cdc3b8f59' | '2026-06-01' | 'Merge branch 'master' of https://github.com/ultim... |
| bobfilez\libs\btk\external\bobui-reference | N/A | HEAD | 'c7e1fc7059' | '2026-06-19' | 'fix: update submodule pointers to valid HEAD â€” ... |
| bobfilez\libs\btk\external\juce | N/A | master | '67f7646367' | '2026-05-25' | 'sync: session 19 add all files and merge branches... |
| bobfilez\libs\btk\external\ultimatepp | N/A | master | '274b262ef' | '2026-06-01' | 'Merge branch 'master' of https://github.com/ultim... |
| bobfilez\libs\pcre2\deps\sljit | N/A | master | 'd9902b1' | '2026-02-15' | 'config: prevent aarch64_be from being autodetecte... |
| bobfilez\libs\rapidjson\thirdparty\gtest | N/A | main | 'bc2e1882' | '2026-06-01' | 'Merge branch 'main' of https://github.com/google/... |
| bobmani\ksm-v2\kshootmania\ThirdParty\CoTaskLib | N/A | master | 'cdaa8cf' | '2026-04-14' | 'chore: save local progress before sync' |
| bobmani\ksm-v2\kshootmania\ThirdParty\NocoUI | N/A | master | '14454dd' | '2026-05-25' | 'Merge branch 'master' of https://github.com/m4sak... |
| bobmani\ksm-v2\kshootmania\ThirdParty\SQLiteCpp | N/A | master | 'b89a263' | '2026-06-01' | 'chore: save progress before update' |
| bobsgameonlinejava\libs\bobui\submodules\juce | N/A | master | '3ba67d4585' | '2026-05-21' | 'CI: Add juce9 branch' |
| bobsgameonlinejava\libs\bobui\submodules\ultimatepp | N/A | master | '20c352c7c' | '2026-06-01' | 'CtrlCore: Fixed to compile in Linux' |
| bobsgameonlinejava\references\LibreSprite\src\flic | N/A | main | 'a37fe2d' | '2025-05-28' | 'Update year' |
| bobsgameonlinejava\references\LibreSprite\third_party\duktape | N/A | master | '6f71555' | '2021-09-09' | 'Update duktape to 2.6.0' |
| bobsgameonlinejava\references\LibreSprite\third_party\simpleini | N/A | aseprite | '9fa7622' | '2023-12-06' | 'Add support to run tests building with cmake + ct... |
| bobsgameonlinejava\references\PixiEditor\src\ColorPicker | N/A | master | 'd8bffd9' | '2026-03-30' | 'Updated version' |
| bobsgameonlinejava\references\PixiEditor\src\Drawie | N/A | main | '8a1eb8c' | '2026-05-23' | 'Safety checks for create shader' |
| bobsgameonlinejava\references\PixiEditor\src\PixiDocks | N/A | main | 'ee4d6de' | '2026-01-08' | 'Do not raise events if null host changed' |
| bobsgameonlinejava\references\PixiEditor\src\PixiParser | N/A | master | '092d1f6' | '2026-02-22' | 'Merge pull request #37 from PixiEditor/blackboard... |
| bobsgameonlinejava\references\aseprite\laf\clip | N/A | main | '964847c' | '2026-05-03' | 'Fixed integer sign comparison warning in clip_osx... |
| bobsgameonlinejava\references\aseprite\src\flic | N/A | main | 'a37fe2d' | '2025-05-28' | 'Update year' |
| bobsgameonlinejava\references\aseprite\src\observable | N/A | main | 'efe767e' | '2026-03-10' | 'Add support to disconnect/connect slots when iter... |
| bobsgameonlinejava\references\aseprite\src\psd | N/A | main | '87af728' | '2025-04-17' | 'Update cmake minimum version' |
| bobsgameonlinejava\references\aseprite\src\tga | N/A | main | 'cd3420c' | '2023-09-20' | 'Fix unused variable warning in release mode' |
| bobsgameonlinejava\references\aseprite\src\undo | N/A | main | '2209ac5' | '2025-04-17' | 'Update cmake minimum version' |
| bobsgameonlinejava\references\aseprite\third_party\IXWebSocket | N/A | aseprite | '89c9209' | '2023-08-29' | 'Fix finding zlib library so we can use zlibstatic... |
| bobsgameonlinejava\references\aseprite\third_party\TinyEXIF | N/A | aseprite | '21d6cf7' | '2025-04-02' | 'Update cmake_minimum_required()' |
| bobsgameonlinejava\references\aseprite\third_party\benchmark | N/A | main | 'b2b0aab' | '2024-12-03' | 'Fix malformed clang invocation in build_ext.run (... |
| bobsgameonlinejava\references\aseprite\third_party\cityhash | N/A | aseprite | 'e2a9a15' | '2025-01-10' | 'Fix compile with MinGW' |
| bobsgameonlinejava\references\aseprite\third_party\cmark | N/A | master | '3ec91f2' | '2024-04-26' | 'build: Tell cmake to set 'rpath' so the installed... |
| bobsgameonlinejava\references\aseprite\third_party\curl | N/A | master | '0773d2a95' | '2023-05-15' | 'mlc_config.json: remove this linkcheck CI job con... |
| bobsgameonlinejava\references\aseprite\third_party\fmt | N/A | master | 'f781d2b9' | '2025-10-25' | 'Update ChangeLog.md' |
| bobsgameonlinejava\references\aseprite\third_party\freetype2 | N/A | master | 'fae1e3160' | '2026-05-09' | '[raster] Dynamic pool allocation.' |
| bobsgameonlinejava\references\aseprite\third_party\giflib | N/A | master | '8bed392' | '2024-02-27' | 'Emphasize lossnessless.' |
| bobsgameonlinejava\references\aseprite\third_party\harfbuzz | N/A | aseprite | '8607be393' | '2025-04-02' | 'Update cmake_minimum_required()' |
| bobsgameonlinejava\references\aseprite\third_party\json11 | N/A | aseprite | 'a4e1714' | '2025-05-07' | 'Include <cstdint> to use uint8_t type' |
| bobsgameonlinejava\references\aseprite\third_party\libarchive | N/A | aseprite | '7bde8b82' | '2025-04-02' | 'Remove CMAKE_BUILD_TYPE check' |
| bobsgameonlinejava\references\aseprite\third_party\libpng | N/A | aseprite | '224abc8b0' | '2026-02-09' | 'Fix pngprefix.h generation' |
| bobsgameonlinejava\references\aseprite\third_party\libwebp | N/A | main | 'ee8e8c62' | '2025-04-10' | 'Fix member naming for VP8LHistogram' |
| bobsgameonlinejava\references\aseprite\third_party\lua | N/A | aseprite | '2a00e6b0' | '2024-06-03' | 'Add conditional usage of system() function throug... |
| bobsgameonlinejava\references\aseprite\third_party\pixman | N/A | master | '285b9a9' | '2022-02-19' | 'configure: replace bugzilla URL with gitlab issue... |
| bobsgameonlinejava\references\aseprite\third_party\qoi | N/A | master | 'd4fc9d1' | '2024-03-24' | 'Merge pull request #299 from Kakadus/master' |
| bobsgameonlinejava\references\aseprite\third_party\simpleini | N/A | aseprite | '9fa7622' | '2023-12-06' | 'Add support to run tests building with cmake + ct... |
| bobsgameonlinejava\references\aseprite\third_party\tinyexpr | N/A | aseprite | '24b9db0' | '2024-11-07' | 'Fix MSVC warnings' |
| bobsgameonlinejava\references\aseprite\third_party\tinyxml2 | N/A | master | '312a809' | '2024-04-20' | 'Merge pull request #976 from leethomason/AlbertHu... |
| bobsgameonlinejava\references\aseprite\third_party\zlib | N/A | master | '51b7f2a' | '2024-01-22' | 'zlib 1.3.1' |
| bobsgameonlinejava\references\voidsprite\external\SDL | N/A | HEAD | '550394eec' | '2026-02-23' | 'x11: Don't send duplicate key down events when re... |
| bobsgameonlinejava\references\voidsprite\external\SDL_image | N/A | HEAD | '8bd9f3d7' | '2026-02-18' | 'bump vendored aom, dav1d, jpeg, libpng and libweb... |
| bobsgameonlinejava\references\voidsprite\external\SDL_net | N/A | HEAD | '92022dc' | '2026-01-21' | 'release: synchronize build-scripts/build-release.... |
| bobsgameonlinejava\references\voidsprite\external\SDL_ttf | N/A | HEAD | '053bbc8' | '2026-02-13' | 'fixed: sdf characters were misaligned (char rects... |
| bobsgameonlinejava\references\voidsprite\external\fmt | N/A | HEAD | '8d3f7317' | '2026-02-23' | 'Mark static arrays as constexpr for binary opt (#... |
| bobsgameonlinejava\references\voidsprite\external\libavif | N/A | HEAD | '0a3f94e3' | '2026-02-23' | 'Set a callback function for dav1d_log()' |
| bobsgameonlinejava\references\voidsprite\external\liblcf | N/A | HEAD | '4b91a58' | '2026-02-21' | 'Merge pull request #507 from Ghabry/event-chunks' |
| bobsgameonlinejava\references\voidsprite\external\zlib | N/A | HEAD | 'da607da' | '2026-02-17' | 'zlib 1.3.2' |
| bobsgameweb\submodules\bobui\submodules\juce | N/A | master | '3ba67d4585' | '2026-05-21' | 'CI: Add juce9 branch' |
| bobsgameweb\submodules\bobui\submodules\ultimatepp | N/A | master | '20c352c7c' | '2026-06-01' | 'CtrlCore: Fixed to compile in Linux' |
| bobtrader\submodules\page-05\fluidex__dingir-exchange\orchestra | N/A | master | 'd4077bf' | '2026-04-13' | 'chore: save local progress before sync' |
| bobtrax\lmms\plugins\CarlaBase\carla | N/A | HEAD | '66afe24a0' | '2024-03-07' | 'CI: Fix macos cmake artifact name' |
| bobtrax\lmms\plugins\FreeBoy\game-music-emu | N/A | HEAD | '21a064e' | '2017-08-13' | 'Silence unused var warning.' |
| bobtrax\lmms\plugins\MidiImport\portsmf | N/A | HEAD | '081261b' | '2025-03-27' | 'Use fixed-width integer types where appropriate (... |
| bobtrax\lmms\plugins\OpulenZ\adplug | N/A | HEAD | '3ed6617' | '2017-11-06' | 'Fix `-Waggressive-loop-optimizations`' |
| bobtrax\lmms\plugins\Xpressive\exprtk | N/A | HEAD | 'a4b17d5' | '2024-01-01' | 'C++ Mathematical Expression Library (ExprTk)  htt... |
| bobtrax\lmms\plugins\ZynAddSubFx\zynaddsubfx | N/A | HEAD | '66a42efc' | '2025-06-11' | 'Fix toWString() (#28)' |
| bobtrax\lmms\src\3rdparty\jack2 | N/A | HEAD | 'ac334fab' | '2024-03-16' | 'Fix startup and shutdown when server is not runni... |
| bobtrax\lmms\src\3rdparty\qt5-x11embed | N/A | HEAD | '499d737' | '2025-04-26' | 'Bump ECM to v6.13.0-rc1, match cmake min ver' |
| bobtrax\lmms\src\3rdparty\ringbuffer | N/A | HEAD | '1c46ef3' | '2022-02-24' | 'Github Action for `make test` (#6)' |
| bobtrax\zrythm\doc\dev\doxygen-awesome-css | N/A | main | '268db8a' | '2026-06-01' | 'Merge branch 'main' of https://github.com/jothepr... |
| geany\variants\geany-bobgui\subprojects\bobgui | 5.0.0-ultrasonic |  |  |  |  |
| geany\variants\geany-bobgui\subprojects\libffi | N/A | master | '35a3dd28' | '2026-06-19' | 'ci: use correct Debian cross triple for mips64el ... |
| hyperharness\llamafile\stable-diffusion.cpp\thirdparty\libwebm | N/A | main | 'c0996bb' | '2026-04-13' | 'chore: save local progress before sync' |
| hyperharness\llamafile\stable-diffusion.cpp\thirdparty\libwebp | N/A | main | '3a7f2dcf' | '2026-04-14' | 'Merge branch 'main' of https://github.com/webmpro... |
| bg\bobsgameonlinejava\libs\lz4-java\src\lz4 | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\LibreSprite\src\flic | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\LibreSprite\third_party\duktape | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\LibreSprite\third_party\simpleini | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\PixiEditor\src\ColorPicker | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\PixiEditor\src\Drawie | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\PixiEditor\src\PixiDocks | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\PixiEditor\src\PixiParser | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\laf\clip | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\src\flic | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\src\observable | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\src\psd | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\src\tga | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\src\undo | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\third_party\IXWebSocket | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\third_party\TinyEXIF | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\third_party\benchmark | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\third_party\cityhash | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\third_party\cmark | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\third_party\curl | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\third_party\fmt | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\third_party\freetype2 | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\third_party\giflib | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\third_party\harfbuzz | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\third_party\json11 | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\third_party\libarchive | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\third_party\libpng | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\third_party\libwebp | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\third_party\lua | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\third_party\pixman | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\third_party\qoi | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\third_party\simpleini | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\third_party\tinyexpr | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\third_party\tinyxml2 | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\aseprite\third_party\zlib | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\grafx2\tests\pic-samples | N/A |  |  |  |  |
| bg\okgame\lib\Maelstrom\external\SDL | N/A |  |  |  |  |
| bg\okgame\lib\Maelstrom\external\SDL_net | N/A |  |  |  |  |
| bg\okgame\lib\Maelstrom\external\SteamworksSDK | N/A |  |  |  |  |
| bg\okgame\lib\Maelstrom\external\physfs | N/A |  |  |  |  |
| bg\okgame\lib\SDL_image\external\aom | N/A |  |  |  |  |
| bg\okgame\lib\SDL_image\external\dav1d | N/A |  |  |  |  |
| bg\okgame\lib\SDL_image\external\jpeg | N/A |  |  |  |  |
| bg\okgame\lib\SDL_image\external\libavif | N/A |  |  |  |  |
| bg\okgame\lib\SDL_image\external\libjxl | N/A |  |  |  |  |
| bg\okgame\lib\SDL_image\external\libpng | N/A |  |  |  |  |
| bg\okgame\lib\SDL_image\external\libtiff | 4.7.1 |  |  |  |  |
| bg\okgame\lib\SDL_image\external\libwebp | N/A |  |  |  |  |
| bg\okgame\lib\SDL_image\external\zlib | N/A |  |  |  |  |
| bg\okgame\lib\SDL_mixer\external\flac | N/A |  |  |  |  |
| bg\okgame\lib\SDL_mixer\external\libgme | N/A |  |  |  |  |
| bg\okgame\lib\SDL_mixer\external\libxmp | N/A |  |  |  |  |
| bg\okgame\lib\SDL_mixer\external\mpg123 | N/A |  |  |  |  |
| bg\okgame\lib\SDL_mixer\external\ogg | N/A |  |  |  |  |
| bg\okgame\lib\SDL_mixer\external\opus | N/A |  |  |  |  |
| bg\okgame\lib\SDL_mixer\external\opusfile | N/A |  |  |  |  |
| bg\okgame\lib\SDL_mixer\external\tremor | N/A |  |  |  |  |
| bg\okgame\lib\SDL_mixer\external\vorbis | N/A |  |  |  |  |
| bg\okgame\lib\SDL_mixer\external\wavpack | N/A |  |  |  |  |
| bg\okgame\lib\SDL_ttf\external\freetype | N/A |  |  |  |  |
| bg\okgame\lib\SDL_ttf\external\harfbuzz | N/A |  |  |  |  |
| bg\okgame\lib\SDL_ttf\external\plutosvg | N/A |  |  |  |  |
| bg\okgame\lib\SDL_ttf\external\plutovg | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\accumulators | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\algorithm | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\align | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\any | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\array | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\asio | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\assert | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\assign | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\atomic | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\beast | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\bimap | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\bind | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\bloom | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\callable_traits | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\charconv | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\chrono | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\circular_buffer | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\cobalt | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\compat | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\compute | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\concept_check | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\config | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\container | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\container_hash | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\context | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\contract | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\conversion | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\convert | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\core | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\coroutine | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\coroutine2 | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\crc | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\date_time | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\decimal | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\describe | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\detail | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\dll | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\dynamic_bitset | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\endian | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\exception | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\fiber | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\filesystem | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\flyweight | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\foreach | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\format | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\function | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\function_types | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\functional | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\fusion | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\geometry | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\gil | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\graph | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\graph_parallel | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\hana | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\hash2 | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\headers | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\heap | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\histogram | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\hof | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\icl | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\integer | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\interprocess | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\intrusive | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\io | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\iostreams | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\iterator | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\json | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\lambda | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\lambda2 | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\leaf | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\lexical_cast | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\local_function | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\locale | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\lockfree | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\log | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\logic | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\math | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\metaparse | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\move | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\mp11 | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\mpi | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\mpl | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\mqtt5 | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\msm | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\multi_array | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\multi_index | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\multiprecision | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\mysql | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\nowide | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\openmethod | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\optional | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\outcome | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\parameter | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\parameter_python | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\parser | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\pfr | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\phoenix | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\poly_collection | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\polygon | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\pool | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\predef | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\preprocessor | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\process | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\program_options | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\property_map | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\property_map_parallel | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\property_tree | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\proto | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\ptr_container | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\python | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\qvm | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\random | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\range | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\ratio | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\rational | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\redis | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\regex | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\safe_numerics | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\scope | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\scope_exit | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\serialization | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\signals2 | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\smart_ptr | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\sort | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\spirit | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\stacktrace | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\statechart | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\static_assert | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\static_string | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\stl_interfaces | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\system | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\test | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\thread | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\throw_exception | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\timer | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\tokenizer | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\tti | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\tuple | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\type_erasure | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\type_index | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\type_traits | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\typeof | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\units | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\unordered | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\url | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\utility | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\uuid | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\variant | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\variant2 | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\vmd | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\wave | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\winapi | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\xpressive | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\yap | N/A |  |  |  |  |
| bg\okgame\lib\boost\tools\auto_index | N/A |  |  |  |  |
| bg\okgame\lib\boost\tools\bcp | N/A |  |  |  |  |
| bg\okgame\lib\boost\tools\boost_install | N/A |  |  |  |  |
| bg\okgame\lib\boost\tools\boostbook | N/A |  |  |  |  |
| bg\okgame\lib\boost\tools\boostdep | N/A |  |  |  |  |
| bg\okgame\lib\boost\tools\boostlook | N/A |  |  |  |  |
| bg\okgame\lib\boost\tools\cmake | N/A |  |  |  |  |
| bg\okgame\lib\boost\tools\docca | N/A |  |  |  |  |
| bg\okgame\lib\boost\tools\inspect | N/A |  |  |  |  |
| bg\okgame\lib\boost\tools\litre | N/A |  |  |  |  |
| bg\okgame\lib\boost\tools\quickbook | N/A |  |  |  |  |
| bg\okgame\lib\cppcodec\test\catch | N/A |  |  |  |  |
| bg\okgame\lib\freetype\subprojects\dlg | N/A |  |  |  |  |
| bg\okgame\lib\libjxl\third_party\brotli | N/A |  |  |  |  |
| bg\okgame\lib\libjxl\third_party\googletest | N/A |  |  |  |  |
| bg\okgame\lib\libjxl\third_party\highway | N/A |  |  |  |  |
| bg\okgame\lib\libjxl\third_party\lcms | N/A |  |  |  |  |
| bg\okgame\lib\libjxl\third_party\libjpeg-turbo | N/A |  |  |  |  |
| bg\okgame\lib\libjxl\third_party\libpng | N/A |  |  |  |  |
| bg\okgame\lib\libjxl\third_party\sjpeg | N/A |  |  |  |  |
| bg\okgame\lib\libjxl\third_party\skcms | N/A |  |  |  |  |
| bg\okgame\lib\libjxl\third_party\zlib | N/A |  |  |  |  |
| bg\okgame\lib\lz4-java\src\lz4 | N/A |  |  |  |  |
| bg\okgame\lib\nanogui-sdl\ext\eigen | N/A |  |  |  |  |
| bg\okgame\lib\nanogui\ext\eigen | N/A |  |  |  |  |
| bg\okgame\lib\nanogui\ext\glfw | N/A |  |  |  |  |
| bg\okgame\lib\nanogui\ext\nanovg | N/A |  |  |  |  |
| bg\okgame\lib\nanogui\ext\pybind11 | N/A |  |  |  |  |
| bg\okgame\lib\picodrive\cpu\cyclone | N/A |  |  |  |  |
| bg\okgame\lib\picodrive\platform\libpicofe | N/A |  |  |  |  |
| bg\okgame\lib\projectm\vendor\projectm-eval | N/A |  |  |  |  |
| bg\okgame\lib\snes9x\external\SPIRV-Cross | N/A |  |  |  |  |
| bg\okgame\lib\snes9x\external\cubeb | N/A |  |  |  |  |
| bg\okgame\lib\snes9x\external\glslang | N/A |  |  |  |  |
| bg\okgame\lib\snes9x\external\vulkan-headers | N/A |  |  |  |  |
| bobfilez\ai-file-sorter\app\include\external\llama.cpp | N/A | master | 'a848e9015' | '2026-05-25' | 'sync: session 19 add all files and merge branches... |
| bobfilez\libs\OpenTimelineIO\src\deps\Imath | N/A | main | '307d352' | '2026-05-25' | 'sync: session 19 add all files and merge branches... |
| bobfilez\libs\OpenTimelineIO\src\deps\pybind11 | N/A | master | '241e67f7' | '2026-06-01' | 'Merge branch 'master' of https://github.com/pybin... |
| bobfilez\libs\OpenTimelineIO\src\deps\rapidjson | N/A | master | 'a1743352' | '2026-06-01' | 'chore: save progress before update' |
| bobfilez\libs\dokany\samples\dokan_memfs\spdlog | N/A | v1.x | 'daccc034' | '2026-06-01' | 'Merge branch 'v1.x' of https://github.com/gabime/... |
| bobfilez\libs\heif\srcs\extlibs\VVCSoftware_VTM | N/A | HEAD | '274e8fc77' | '2021-05-26' | 'update version to 13.0 and PDF of software manual... |
| bobmani\beatoraja\lr2oraja-endlessdream\core\dependencies\jbms-parser | N/A | master | 'cd980a4' | '2025-11-18' | 'Refactor to use primitive arrays' |
| bobmani\beatoraja\lr2oraja-endlessdream\core\dependencies\jbmstable-parser | N/A | master | '205a286' | '2023-12-02' | 'Improve performance of table decoding' |
| bobmani\ksm-v2\kshootmania\ThirdParty\SQLiteCpp\googletest | N/A | main | 'a721f1b2' | '2026-05-30' | 'Automated Code Change' |
| bobsgameonlinejava\references\aseprite\laf\third_party\googletest | N/A | main | '155b337c' | '2025-04-17' | 'Bump RE2 dependency to 2024-07-02.bcr.1' |
| bobtrax\lmms\plugins\LadspaEffect\calf\veal | N/A | HEAD | '789d0faf' | '2025-03-14' | 'Merge 'calf/master' into 'veal/ladspa'' |
| bobtrax\lmms\plugins\LadspaEffect\cmt\cmt | N/A | HEAD | '24599fb' | '2024-05-10' | 'Remove MSVC dllexport attribute' |
| bobtrax\lmms\plugins\LadspaEffect\swh\ladspa | N/A | HEAD | '0f54d24' | '2024-05-24' | 'Applied patch from Oskar Wallgren via github.' |
| bobtrax\lmms\plugins\LadspaEffect\tap\tap-plugins | N/A | HEAD | '8564022' | '2023-07-14' | 'Refactoring and cleanup' |
| bobtrax\lmms\plugins\Sid\resid\resid | N/A | HEAD | 'ef72462' | '2023-06-01' | 'filter tweaks, patch by leandro nini' |
| bobtrax\lmms\plugins\ZynAddSubFx\zynaddsubfx\instruments | N/A | HEAD | 'c5c9121' | '2021-12-08' | 'Set the LFO intensity of Organ 13 to zero.' |
| bobtrax\lmms\src\3rdparty\hiir\hiir | N/A | HEAD | '4a9a1e6' | '2023-01-24' | 'Update README.md' |
| bobtrax\lmms\src\3rdparty\weakjack\weakjack | N/A | HEAD | 'fd11655' | '2020-06-29' | 'Add wrapper for `jack_set_sync_timeout` -- closes... |
| hyperharness\llamafile\stable-diffusion.cpp\examples\server\frontend | N/A | master | '740475a' | '2026-04-11' | 'first commit' |
| bg\bobsgameonlinejava\references\aseprite\laf\third_party\googletest | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\grafx2\tools\8x8fonts\font8x8 | N/A |  |  |  |  |
| bg\okgame\lib\SDL_image\external\libjxl\testdata | N/A |  |  |  |  |
| bg\okgame\lib\SDL_ttf\external\plutosvg\plutovg | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\numeric\conversion | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\numeric\interval | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\numeric\odeint | N/A |  |  |  |  |
| bg\okgame\lib\boost\libs\numeric\ublas | N/A |  |  |  |  |
| bg\okgame\lib\boost\tools\docca\xslt-visualizer | N/A |  |  |  |  |
| bg\okgame\lib\picodrive\pico\cd\libchdr | N/A |  |  |  |  |
| bg\okgame\lib\picodrive\pico\sound\emu2413 | N/A |  |  |  |  |
| bg\okgame\lib\picodrive\platform\common\dr_libs | N/A |  |  |  |  |
| bg\okgame\lib\snes9x\external\cubeb\googletest | N/A |  |  |  |  |
| bg\okgame\lib\snes9x\win32\libpng\src | N/A |  |  |  |  |
| bg\okgame\lib\snes9x\win32\zlib\src | N/A |  |  |  |  |
| bobfilez\libs\OpenRV\src\lib\files\WFObj | N/A | main | 'ef17b92' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\btk\external\bobui-reference\submodules\juce | N/A | master | 'fe2ffcf7e7' | '2026-04-14' | 'Merge feature origin/develop into master' |
| bobfilez\libs\btk\external\bobui-reference\submodules\ultimatepp | N/A | master | '44e31c73e' | '2026-04-14' | 'chore: save local progress before sync' |
| bobsgameonlinejava\references\aseprite\third_party\freetype2\subprojects\dlg | N/A | main | '395ccad' | '2025-07-20' | 'Fix meson warnings' |
| bobsgameonlinejava\references\retro-game-editor\app\internal-apps\js-sms\jsSMS | N/A | master | '5a85c08' | '2018-02-26' | 'Remove license from top of files.' |
| bobsgameonlinejava\references\voidsprite\external\SDL_image\external\aom | N/A | HEAD | 'f77580e01' | '2026-02-18' | 'cmake: avoid deprecation warnings' |
| bobsgameonlinejava\references\voidsprite\external\SDL_image\external\dav1d | N/A | HEAD | '0a406d35' | '2026-02-18' | 'cmake: require C99 or newer.' |
| bobsgameonlinejava\references\voidsprite\external\SDL_image\external\jpeg | N/A | HEAD | '191c46e' | '2026-02-18' | 'cmake/jconfig.h.in: tweak HAVE_STDDEF_H and HAVE_... |
| bobsgameonlinejava\references\voidsprite\external\SDL_image\external\libavif | N/A | HEAD | '5bcd7d03' | '2024-04-18' | 'simplify handling of Windows dll names.' |
| bobsgameonlinejava\references\voidsprite\external\SDL_image\external\libjxl | N/A | HEAD | 'fddbaf45' | '2026-02-16' | 'cmake: change brotlienc-static to brotlienc, too,... |
| bobsgameonlinejava\references\voidsprite\external\SDL_image\external\libpng | N/A | HEAD | '1541b942a' | '2026-02-18' | 'cmake: remove BUILD_INTERFACE from target_link_li... |
| bobsgameonlinejava\references\voidsprite\external\SDL_image\external\libtiff | 4.7.1 | HEAD | '442c4cf6' | '2026-01-09' | 'cmake: Replace CMath::CMath with direct link to a... |
| bobsgameonlinejava\references\voidsprite\external\SDL_image\external\libwebp | N/A | HEAD | '42611dee' | '2026-02-18' | 'cmake: avoid deprecation warnings, and SET CMP007... |
| bobsgameonlinejava\references\voidsprite\external\SDL_image\external\zlib | N/A | HEAD | '0e68590' | '2026-01-06' | 'cmake: make sure shared and static library genera... |
| bobsgameonlinejava\references\voidsprite\external\SDL_ttf\external\freetype | N/A | HEAD | 'd3a395b5f' | '2025-05-28' | 'cmake: do not export freetype symbols in static b... |
| bobsgameonlinejava\references\voidsprite\external\SDL_ttf\external\harfbuzz | N/A | HEAD | '950d232cd' | '2025-10-25' | 'Guard hb_cairo_glyphs_from_buffer() against bad U... |
| bobsgameonlinejava\references\voidsprite\external\SDL_ttf\external\plutosvg | N/A | HEAD | 'f2996da' | '2025-12-31' | 'Handle UTF-8 BOM' |
| bobsgameonlinejava\references\voidsprite\external\SDL_ttf\external\plutovg | N/A | HEAD | 'c42264b' | '2025-05-20' | 'do not export symbols in static unix builds' |
| bobtrax\lmms\src\3rdparty\qt5-x11embed\3rdparty\ECM | N/A | HEAD | '1f820dc9' | '2025-04-03' | 'Add missing include mocs' |
| bg\bobsgameonlinejava\references\aseprite\third_party\freetype2\subprojects\dlg | N/A |  |  |  |  |
| bg\bobsgameonlinejava\references\retro-game-editor\app\internal-apps\js-sms\jsSMS | N/A |  |  |  |  |
| bg\okgame\lib\SDL_image\external\libjxl\third_party\brotli | N/A |  |  |  |  |
| bg\okgame\lib\SDL_image\external\libjxl\third_party\googletest | N/A |  |  |  |  |
| bg\okgame\lib\SDL_image\external\libjxl\third_party\highway | N/A |  |  |  |  |
| bg\okgame\lib\SDL_image\external\libjxl\third_party\lcms | N/A |  |  |  |  |
| bg\okgame\lib\SDL_image\external\libjxl\third_party\libjpeg-turbo | N/A |  |  |  |  |
| bg\okgame\lib\SDL_image\external\libjxl\third_party\libpng | N/A |  |  |  |  |
| bg\okgame\lib\SDL_image\external\libjxl\third_party\sjpeg | N/A |  |  |  |  |
| bg\okgame\lib\SDL_image\external\libjxl\third_party\skcms | N/A |  |  |  |  |
| bg\okgame\lib\SDL_image\external\libjxl\third_party\zlib | N/A |  |  |  |  |
| bg\okgame\lib\SDL_ttf\external\freetype\subprojects\dlg | N/A |  |  |  |  |
| bg\okgame\lib\nanogui\ext\pybind11\tools\clang | N/A |  |  |  |  |
| bg\okgame\lib\snes9x\external\cubeb\cmake\sanitizers-cmake | N/A |  |  |  |  |
| bg\okgame\lib\snes9x\external\cubeb\src\cubeb-coreaudio-rs | N/A |  |  |  |  |
| bg\okgame\lib\snes9x\external\cubeb\src\cubeb-pulse-rs | N/A |  |  |  |  |
| bobfilez\libs\OpenTimelineIO\src\deps\rapidjson\thirdparty\gtest | N/A | main | '37063c3f' | '2026-06-01' | 'Merge branch 'main' of https://github.com/google/... |
| bobsgameonlinejava\references\voidsprite\external\SDL_image\external\libjxl\testdata | N/A | HEAD | 'd81acac' | '2022-07-11' | 'Merge pull request #6 from szabadka/main' |
| bobsgameonlinejava\references\voidsprite\external\SDL_ttf\external\plutosvg\plutovg | N/A | HEAD | '1a8412d' | '2025-05-15' | 'Release v1.1.0' |
| bobtrax\lmms\plugins\CarlaBase\carla\source\native-plugins\external | N/A | HEAD | '3c0026d' | '2023-10-03' | 'Fix build with custom updated pugl' |
| bobsgameonlinejava\references\voidsprite\external\SDL_image\external\libjxl\third_party\brotli | N/A | HEAD | '74f08a5' | '2025-04-15' | 'fix build for Microsoft-designed ARM64 ABI' |
| bobsgameonlinejava\references\voidsprite\external\SDL_image\external\libjxl\third_party\googletest | N/A | HEAD | '58d77fa8' | '2022-06-27' | 'Updates the version number in CMakeLists.txt to 1... |
| bobsgameonlinejava\references\voidsprite\external\SDL_image\external\libjxl\third_party\highway | N/A | HEAD | '86a01250' | '2025-12-24' | 'Fix for GCC 15 compiler error on PPC8/PPC9/PPC10' |
| bobsgameonlinejava\references\voidsprite\external\SDL_image\external\libjxl\third_party\lcms | N/A | HEAD | '65c63bf' | '2019-04-18' | 'Merge branch 'master' of https://github.com/mm2/L... |
| bobsgameonlinejava\references\voidsprite\external\SDL_image\external\libjxl\third_party\libpng | N/A | HEAD | 'a40189cf8' | '2019-04-14' | 'Release libpng version 1.6.37' |
| bobsgameonlinejava\references\voidsprite\external\SDL_image\external\libjxl\third_party\sjpeg | N/A | HEAD | '94e0df6' | '2025-04-02' | 'CMakeLists.txt: bump minimum cmake version to 3.5... |
| bobsgameonlinejava\references\voidsprite\external\SDL_image\external\libjxl\third_party\skcms | N/A | HEAD | '6437475' | '2019-12-11' | 'Add skcms_AdaptToXYZD50 to the API' |
| bobsgameonlinejava\references\voidsprite\external\SDL_image\external\libjxl\third_party\zlib | N/A | HEAD | '09155ea' | '2023-08-18' | 'zlib 1.3' |
| bobsgameonlinejava\references\voidsprite\external\SDL_ttf\external\freetype\subprojects\dlg | N/A | HEAD | '72dfcc8' | '2023-04-16' | 'Add changelog' |
| geany\variants\geany-bobgui\subprojects\bobgui\subprojects\glib\subprojects\gvdb | N/A |  |  |  |  |
| bg\okgame\lib\picodrive\platform\common\dr_libs\tests\external\miniaudio | N/A |  |  |  |  |
