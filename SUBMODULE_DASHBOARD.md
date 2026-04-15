# Submodule Dashboard & Project Structure
**Last Updated:** 2026-04-15 00:15:16

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
| CLIProxyAPIPlus | N/A | main | '8d6017ab' | '2026-04-14' | 'Merge feature origin/jules-6176689634486707782-88... |
| Maestro | 0.15.9 | main | '3a007bc1' | '2026-04-03' | 'fix: align visual orchestrator theme imports and ... |
| MarbleBlast | N/A | master | '1659db7' | '2026-04-14' | 'Merge feature origin/jules-15180076805006571318-0... |
| OmniRoute | N/A | main | '8778ccbb' | '2026-03-23' | 'Merge branch 'main' of https://github.com/diegoso... |
| OpenMBU | N/A | main | '50c92253' | '2026-04-08' | 'Auto-sync' |
| antigravity-cli | N/A | main | '43fc7b6' | '2026-04-08' | 'Auto-sync' |
| antigravity-jules-orchestration | N/A |  |  |  |  |
| bobbybookmarks | N/A | main | 'e3a1061' | '2026-04-14' | 'FIX: Resolved ReferenceError for NeonCard and fin... |
| bobcoin | N/A | main | 'ed098861' | '2026-04-13' | 'Merge feature origin/dependabot/npm_and_yarn/fron... |
| bobeditpro | N/A | master | '85073cd1b' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez | N/A | main | '3de1fe977' | '2026-04-14' | 'chore: save local progress before sync' |
| bobgui | 5.0.0-ultrasonic | main | 'ce7fcfeb92' | '2026-04-14' | 'Merge branch 'main' of https://github.com/robertp... |
| bobsaver | N/A | main | 'b815d0bb' | '2026-04-14' | 'Merge feature origin/jules-7169901332660125491-9d... |
| bobtorrent | 11.60.0 | master | '82ec276' | '2026-04-14' | 'Merge feature origin/feature/go-supernode-webui-1... |
| bobtrader | N/A | main | 'd0c188e' | '2026-04-14' | 'Merge branch 'main' of https://github.com/robertp... |
| bobui | N/A | main | '84e615e8c6a' | '2026-04-14' | 'chore: save local progress before sync' |
| bobzzite | N/A | main | 'fa1236f' | '2026-01-12' | 'Initialize bobzzite gaming Linux distro structure... |
| borg | 1.0.0-alpha.32 | HEAD | 'c33d456cb' | '2026-04-11' | 'Resolve submodule conflict and restore prism-mcp ... |
| btk | 0.2.0 | master | '92a051932' | '2026-04-14' | 'chore: save local progress before sync' |
| computer-use-preview | N/A | main | 'f8be28e' | '2026-04-14' | 'Merge feature origin/mquirosbloch-patch-1 into ma... |
| dupeguru | N/A | master | 'c0df9eb1' | '2026-03-11' | 'Merge remote-tracking branch 'origin/rust'' |
| f-zerox | N/A | main | '1ac5f8c' | '2026-04-14' | 'chore: save local progress before sync' |
| frontend-sdl-cpp | N/A | master | 'bc3c0ae' | '2026-03-11' | 'Merge remote-tracking branch 'origin/ci'' |
| fwber | N/A | main | '2490855c2' | '2026-04-14' | 'fix: update nginx ws.fwber.me.conf to point to po... |
| geany | N/A | master | '22824b4c2' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode | 1.0.0-alpha.25 | main | '855c4d802' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode-push | 1.0.0-alpha.1 | main | '855c4d802' | '2026-04-14' | 'chore: save local progress before sync' |
| hyperharness | 0.3.0 | main | '5752c73' | '2026-04-14' | 'Merge branch 'main' of https://github.com/robertp... |
| mcp-superassistant | <<<<<<< HEAD
0.7.2
| mk64 | N/A | master | 'f60d29954' | '2026-04-14' | 'Merge upstream changes' |
| neverball | <<<<<<< HEAD
1.6.2-dev
| npp | 1.1.0 | master | '3260d84d5' | '2026-04-14' | 'chore: save local progress before sync' |
| onetool-mcp | N/A | main | 'eac44ae' | '2026-04-03' | 'Release 2.2.2' |
| opencode-autopilot | N/A | main | '30b8cf7' | '2026-04-14' | 'Merge feature origin/jules-4657769983160951050-bc... |
| pi-mono | N/A | main | 'df8d92ad' | '2026-04-14' | 'Merge feature origin/jules-14458798274183669513-1... |
| picard | N/A | master | '7a2df93e9' | '2026-04-14' | 'Merge feature origin/jules-12364719424079951847-3... |
| raindropioapp | <<<<<<< HEAD
1.0.4
| sm64coopdx | N/A | main | '1a4e1e12c' | '2026-03-23' | 'chore: save progress before update' |
| superai | N/A | main | '643a6a73' | '2026-04-10' | 'Auto-sync: update files and submodules' |
| superpowers | N/A | main | '8123184' | '2026-03-21' | 'Merge remote-tracking branch 'origin/wip-gemini-c... |
| supersaber | N/A | master | '818e2c1' | '2026-04-14' | 'Merge feature origin/jules-13860999388841438430-7... |
| tabby | N/A | master | 'b4c7775f' | '2026-04-14' | 'Merge upstream changes' |
| antigravity-autopilot\AUTO-ALL-AntiGravity | N/A | master | '82b20b3' | '2026-04-08' | 'Auto-sync' |
| antigravity-autopilot\AntiBridge-Antigravity-remote | N/A | main | 'c79ab65' | '2026-04-08' | 'Auto-sync' |
| antigravity-autopilot\AntigravityMobile | N/A | main | '149f1f5' | '2026-04-11' | 'Auto-sync' |
| antigravity-autopilot\Claude-Autopilot | N/A | main | '8341bc6' | '2026-04-14' | 'chore: save local progress before sync' |
| antigravity-autopilot\antigravity-auto-accept | N/A | master | 'da6df56' | '2026-04-08' | 'Auto-sync' |
| antigravity-autopilot\antigravity-multi-purpose-agent | N/A | main | 'cfe8354' | '2026-04-08' | 'Auto-sync' |
| antigravity-autopilot\auto-accept-agent | N/A | master | 'a6d0be5' | '2026-04-08' | 'Auto-sync' |
| antigravity-autopilot\copilot-auto-continue | N/A | main | '267a418' | '2026-04-08' | 'Auto-sync' |
| antigravity-autopilot\free-auto-accept-antigravity | N/A | main | '0fcf71d' | '2026-04-11' | 'Global Sync: Merged features, updated submodules,... |
| antigravity-autopilot\yoke-antigravity | N/A | master | '8c3d312' | '2026-04-08' | 'Auto-sync' |
| bg\bobsgameonlinejava | N/A | main | 'b4aba26' | '2026-04-14' | 'Fix commons-lang submodule: repoint to stable ori... |
| bg\okgame | N/A | main | '643b14465' | '2026-04-13' | 'Update projectm submodule' |
| bobeditpro\muse_framework | N/A | main | '43fd57d3' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\VERT | N/A | main | 'b741a34' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\ai-file-sorter | N/A | main | '3fb48ad' | '2026-04-14' | 'Merge feature origin/dev into main' |
| bobmani\Simply-Love-SM5 | N/A | itgmania-release | '75bbe99e' | '2026-04-10' | 'Auto-resolve: merge upstream' |
| bobmani\arrowvortex | v1.3.2 | main | '26bea86' | '2026-04-14' | 'chore: save local progress before sync' |
| bobmani\beatoraja | 0.9.2 | master | '7cb31e07' | '2026-04-14' | 'chore: save local progress before sync' |
| bobmani\bobmania | <<<<<<< HEAD
5.7.0-Unified-Alpha
| bobmani\ddc | 0.2.32 | master | '61714ecf' | '2026-04-11' | 'Global Sync: Consolidated feature branches and up... |
| bobmani\ddc_onset | N/A | main | '53044b5' | '2026-04-11' | 'Global Sync: Merged features, updated submodules,... |
| bobmani\ffr-difficulty-model | N/A | master | '8d21998' | '2026-04-11' | 'Auto-sync: update files and submodules' |
| bobmani\hymnmania | 1.7.0 | master | 'ead4be3' | '2026-04-14' | 'Merge feature origin/feat/comprehensive-docs-and-... |
| bobmani\itgmania | N/A | release | '0822ac9323' | '2026-04-14' | 'Fix libtommath submodule: repoint to stable origi... |
| bobmani\ksm-v2 | 2.0.0-alpha23 | master | 'b4d4a1d' | '2026-04-01' | 'Merge remote-tracking branch 'origin/jules/featur... |
| bobmani\leraine-studio | N/A | master | '36ad74f' | '2026-04-14' | 'chore: save local progress before sync' |
| bobmani\linthesia | 0.9.1 | main | 'f1375fe' | '2026-04-13' | 'docs: wait mode log, roadmap updates' |
| bobmani\pianogame | N/A | master | '5860035' | '2026-02-27' | 'Merge branch 'master' of https://github.com/rober... |
| bobsaver\JWildfire | N/A | master | 'b18de072' | '2026-04-02' | 'docs: Acknowledge local VoC installation in analy... |
| bobsaver\MilkDrop3 | N/A | main | '218af58' | '2026-04-01' | 'Merge branch 'main' of https://github.com/robertp... |
| bobsaver\apophysis-j | N/A | master | '584376a' | '2026-03-11' | 'Merge branch 'master' of https://www.github.com/m... |
| bobsaver\electricsheep | N/A | master | 'f7ec891' | '2026-03-01' | 'chore: save progress before update' |
| bobsaver\geiss | N/A | main | '816b527' | '2026-03-05' | 'Merge branch 'main' of https://www.github.com/gei... |
| bobsaver\projectm | N/A | master | '4f125a5b1' | '2026-04-14' | 'chore: save local progress before sync' |
| bobsgameonlinejava\bobcoin | N/A | HEAD | '4f730d6' | '2026-04-14' | 'chore: save local progress before sync' |
| bobtorrent\bobcoin | N/A | main | '18225a1' | '2026-04-14' | 'Merge branch 'main' of https://github.com/robertp... |
| bobtorrent\qbittorrent | N/A | master | 'f4ab75943' | '2026-04-14' | 'chore: save local progress before sync' |
| bobtrax\ardour | N/A | master | '4f96ee188c' | '2026-04-14' | 'chore: save local progress before sync' |
| bobtrax\bobui | N/A | master | '9e94d07095' | '2026-04-14' | 'chore: save local progress before sync' |
| bobtrax\lmms | N/A | master | '22722fdd9' | '2026-04-13' | 'chore: save local progress before sync' |
| bobtrax\muse | N/A | master | 'fe5e92ed' | '2026-04-14' | 'chore: save local progress before sync' |
| bobtrax\zrythm | N/A | master | 'c650b551e' | '2026-04-14' | 'Merge branch 'master' of https://github.com/zryth... |
| borg\jules-autopilot | N/A | main | 'c6038eb' | '2026-04-14' | 'chore: save local progress before sync' |
| f-zerox\bobcoin | N/A | main | '8d996a9' | '2026-04-14' | 'Merge branch 'main' of https://github.com/robertp... |
| hyperharness\adrenaline | N/A | master | '5fc1025' | '2026-04-14' | 'Merge feature origin/feature/every-code-change-is... |
| hyperharness\aider | N/A | main | '68f78fad' | '2026-04-14' | 'chore: save local progress before sync' |
| hyperharness\amazon-q-developer-cli | N/A | main | 'c181fba2' | '2026-04-14' | 'Merge feature origin/agent_crate_tests into main' |
| hyperharness\auggie | N/A | main | '4348d11' | '2026-04-14' | 'Merge feature origin/augment-agent-add-common-fla... |
| hyperharness\azure-ai-cli | N/A | main | 'f729d5c' | '2026-04-14' | 'Merge feature origin/brandom/js-docs-template int... |
| hyperharness\bito-cli | N/A | main | 'cb3a779' | '2025-04-23' | 'README.md' |
| hyperharness\byterover-cli | N/A | main | '773dcf3a' | '2026-04-14' | 'chore: save local progress before sync' |
| hyperharness\claude-code | N/A | main | 'a371abb' | '2026-04-05' | 'fix(README): formatting in README.md for QueryEng... |
| hyperharness\claude-code-templates | N/A | main | '02ea4a05' | '2026-04-14' | 'chore: save local progress before sync' |
| hyperharness\code-cli | N/A | main | '89ee67aeb' | '2026-04-14' | 'chore: save local progress before sync' |
| hyperharness\copilot-cli | N/A | main | '52470a3' | '2026-04-14' | 'Merge feature origin/copilot/install-repo-powersh... |
| hyperharness\crush | N/A | main | 'af98249f' | '2026-04-14' | 'Merge branch 'main' of https://github.com/charmbr... |
| hyperharness\dolt | N/A | main | '70b736f900' | '2026-04-14' | 'Merge feature origin/aaron/faster-nbs-tests into ... |
| hyperharness\factory-cli | N/A | main | 'e56291c' | '2026-04-14' | 'Merge branch 'main' of https://github.com/Factory... |
| hyperharness\gemini-cli | N/A | main | '548b10acb' | '2026-04-14' | 'Merge branch 'main' of https://github.com/google-... |
| hyperharness\goose | N/A | main | '18664f047' | '2026-04-14' | 'Merge feature origin/Roshansingh9/main into main' |
| hyperharness\grok-cli | N/A | main | 'f172499' | '2026-04-14' | 'chore: save local progress before sync' |
| hyperharness\jules-extension | N/A | main | '2e471f8' | '2026-04-14' | 'Merge feature origin/dependabot/npm_and_yarn/mcp-... |
| hyperharness\kilocode | N/A | main | '2fcd793aa' | '2026-04-14' | 'Merge branch 'main' of https://github.com/Kilo-Or... |
| hyperharness\kimi-cli | N/A | main | 'f6066556' | '2026-04-14' | 'Merge feature origin/bigeagle/toolset-step into m... |
| hyperharness\litellm | N/A | main | 'ead76127fa' | '2026-04-14' | 'chore: save local progress before sync' |
| hyperharness\llamafile | N/A | main | 'f3eba97' | '2026-04-14' | 'chore: save local progress before sync' |
| hyperharness\llm-cli | N/A | main | 'bad3510' | '2026-04-14' | 'chore: save local progress before sync' |
| hyperharness\mistral-vibe | N/A | main | 'e1a25ca' | '2026-04-14' | 'v2.7.5 (#589)' |
| hyperharness\ollama | N/A | main | '562a1b36' | '2026-04-14' | 'Merge branch 'main' of https://github.com/ollama/... |
| hyperharness\open-interpreter | N/A | main | '9e1331d1' | '2026-04-14' | 'Merge branch 'main' of https://github.com/OpenInt... |
| hyperharness\opencode | N/A | HEAD | '0e66bdd43' | '2026-04-14' | 'chore: save local progress before sync' |
| hyperharness\pi-cli | N/A | main | 'e49567b0' | '2026-04-14' | 'chore: save local progress before sync' |
| hyperharness\qwen-code-cli | N/A | clean-main | '93e49ff' | '2026-04-14' | 'Merge feature origin/rjmz8d-codex/implement-cance... |
| hyperharness\rowboat | N/A | main | '67482e9f' | '2026-04-14' | 'chore: save local progress before sync' |
| hyperharness\smithery-cli | N/A | main | '151c9a1' | '2026-04-14' | 'chore: save local progress before sync' |
| mk64\bobcoin | N/A | main | 'd390f6e' | '2026-04-14' | 'Merge branch 'main' of https://github.com/robertp... |
| mk64\doxygen-awesome-css | N/A | main | '56b7222' | '2026-04-13' | 'Merge feature origin/fix/list_in_tabs into main' |
| musicbrainz-soulseek-downloader\picard | N/A |  |  |  |  |
| npp\bobgui | 5.0.0-ultrasonic | main | '3f16bb9c10' | '2026-04-14' | 'Merge branch 'main' of https://github.com/robertp... |
| npp\bobui | N/A | main | '8f73db19fb' | '2026-04-14' | 'chore: save local progress before sync' |
| npp\btk | 0.2.0 | master | '937774500' | '2026-04-14' | 'chore: save local progress before sync' |
| npp\textfx | N/A | main | '71ec1ea' | '2026-02-24' | 'Updated version' |
| superai\adrenaline | N/A | master | 'c42ecf4' | '2026-04-14' | 'Merge feature origin/feature/every-code-change-is... |
| superai\aider | N/A | HEAD | 'bdb4d9ff' | '2026-03-16' | 'copy' |
| superai\auggie | N/A | main | '43b07df' | '2026-04-14' | 'Merge feature origin/augment-agent-add-common-fla... |
| superai\azure-ai-cli | N/A | main | 'f0a1d41' | '2026-04-14' | 'Merge feature origin/brandom/js-docs-template int... |
| superai\bito-cli | N/A | main | 'cb3a779' | '2025-04-23' | 'README.md' |
| superai\byterover-cli | N/A | main | 'f2c559da' | '2026-04-14' | 'chore: save local progress before sync' |
| superai\claude-code | N/A | HEAD | 'd46bd99' | '2026-04-02' | 'docs(README): updated docs' |
| superai\claude-code-templates | N/A | main | '3adda963' | '2026-04-14' | 'chore: save local progress before sync' |
| superai\code-cli | N/A | main | '3133cc380' | '2026-04-14' | 'chore: save local progress before sync' |
| superai\copilot-cli | N/A | main | 'a07ed82' | '2026-04-14' | 'Merge feature origin/copilot/install-repo-powersh... |
| superai\crush | N/A | main | '8581ba22' | '2026-04-14' | 'Merge branch 'main' of https://github.com/charmbr... |
| superai\dolt | N/A | main | '70dec094fe' | '2026-04-14' | 'Merge feature origin/aaron/bats-cleanup-leaked-ba... |
| superai\factory-cli | N/A | main | '6e77b90' | '2026-04-14' | 'Merge branch 'main' of https://github.com/Factory... |
| superai\gemini-cli | N/A | main | '1f6086aae' | '2026-04-14' | 'Merge branch 'main' of https://github.com/google-... |
| superai\goose | N/A | main | 'd54279042' | '2026-04-14' | 'Merge feature origin/Roshansingh9/main into main' |
| superai\grok-cli | N/A | main | 'e1f1a87' | '2026-04-14' | 'chore: save local progress before sync' |
| superai\jules-extension | N/A | main | '95bdb88' | '2026-04-14' | 'Merge feature origin/dependabot/npm_and_yarn/mcp-... |
| superai\kilocode | N/A | main | 'c8af4b052' | '2026-04-14' | 'Merge branch 'main' of https://github.com/Kilo-Or... |
| superai\kimi-cli | N/A | main | 'bb3d7527' | '2026-04-14' | 'Merge feature origin/bigeagle/toolset-step into m... |
| superai\litellm | N/A | main | 'a283c205da' | '2026-04-14' | 'chore: save local progress before sync' |
| superai\llamafile | N/A | main | 'd2e80d1' | '2026-04-14' | 'chore: save local progress before sync' |
| superai\llm-cli | N/A | main | '89e6f06' | '2026-04-14' | 'chore: save local progress before sync' |
| superai\mistral-vibe | N/A | HEAD | '90763da' | '2026-04-03' | 'v2.7.3 (#564)' |
| superai\ollama | N/A | main | 'b0eb32d2' | '2026-04-14' | 'Merge branch 'main' of https://github.com/ollama/... |
| superai\open-interpreter | N/A | main | 'b5ba3fc7' | '2026-04-14' | 'Merge branch 'main' of https://github.com/OpenInt... |
| superai\opencode | N/A | dev | '2d7546cc0' | '2026-04-14' | 'chore: save local progress before sync' |
| superai\pi-cli | N/A | main | 'cebd4360' | '2026-04-14' | 'chore: save local progress before sync' |
| superai\qwen-code-cli | N/A | clean-main | '48d0e9f' | '2026-04-14' | 'chore: save local progress before sync' |
| superai\rowboat | N/A | main | '1ca3f70e' | '2026-04-14' | 'chore: save local progress before sync' |
| superai\smithery-cli | N/A | main | '179736d' | '2026-04-14' | 'chore: save local progress before sync' |
| antigravity-autopilot\submodules\antigravity-sdk | N/A | main | 'e6f8efb' | '2026-04-08' | 'Auto-sync' |
| bg\bobsgameonlinejava\bobcoin | N/A | main | '4f730d6' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\7zip | N/A | main | 'fea94d3' | '2025-10-01' | 'Update latest_version.json' |
| bobfilez\libs\ADSFileSystem | N/A | master | '5ab73c6' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\ADSIdentifier | N/A | master | '7074e07' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\ADSman | N/A | main | '40b0766' | '2026-04-11' | 'chore: save progress before update' |
| bobfilez\libs\AlternateDataStreams | N/A | master | '9eb3f30' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\BLAKE3 | N/A | master | '3736360' | '2026-04-14' | 'Merge branch 'master' of https://github.com/BLAKE... |
| bobfilez\libs\Bringing-Old-Photos-Back-to-Life | N/A | master | '2093171' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\C | N/A | master | '75cfc361' | '2026-04-14' | 'Merge feature origin/leetcode_writer_fix into mas... |
| bobfilez\libs\DataStreamBrowser | N/A | master | '70235cc' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\Dependencies | N/A | main | '340b46b' | '2026-04-11' | 'chore: save progress before update' |
| bobfilez\libs\FFmpeg | <<<<<<< HEAD
0.7.8
| bobfilez\libs\ImageMagick | N/A | main | 'e1eaef1ed' | '2026-04-13' | 'Merge branch 'main' of https://github.com/ImageMa... |
| bobfilez\libs\Imath | N/A | main | 'ec0b4e8' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\JUCE | N/A | master | 'e302722055' | '2026-04-14' | 'Merge feature origin/develop into master' |
| bobfilez\libs\LibRaw | N/A | master | 'f74ddd99' | '2026-04-07' | 'Merge pull request #799 from JuanPabloZambrano/Ha... |
| bobfilez\libs\Magick.NET | N/A | main | '8e15a1c' | '2026-04-13' | 'Corrected version.' |
| bobfilez\libs\MediaInfo | N/A | master | 'c30984be0' | '2026-04-14' | 'Merge branch 'master' of https://github.com/Media... |
| bobfilez\libs\MediaInfoLib | N/A | master | 'f362f57b9' | '2026-04-14' | 'Merge branch 'master' of https://github.com/Media... |
| bobfilez\libs\OpenColorIO | N/A | main | 'f3299506' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\OpenCue | N/A | master | 'fe3636ae' | '2026-04-14' | 'Merge feature origin/Update-Steering-Committee in... |
| bobfilez\libs\OpenImageIO | N/A | main | '5804620e9' | '2026-04-14' | 'Merge branch 'main' of https://github.com/Academy... |
| bobfilez\libs\OpenRV | N/A | main | '413a47a7' | '2026-04-14' | 'Merge feature origin/ci-test into main' |
| bobfilez\libs\OpenTimelineIO | N/A | main | '75f8220' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\Powershell-ADS | N/A | master | '13a7507' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\RenStrm | N/A | master | 'f195bb9' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\SharpADS | N/A | main | '8802fc6' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\ShazamAPI | N/A | main | '6cd2c9f' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\ShazamIO | N/A | master | '9163c1b' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\SysmonForLinux | N/A | main | '21c6e4c' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\TinyEXIF | N/A | master | 'feb86cd' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\Windows | N/A | main | '5e6884e' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\WizardsToolkit | N/A | main | 'abe6322' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\ads | N/A | master | '812a05d' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\argon2 | N/A | master | '1ce5c81' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\audio-recognizer | N/A | master | '3dcaaee' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\audiocraft | N/A | main | '28223fe' | '2026-04-14' | 'Merge feature origin/jasco_release_Jan12 into mai... |
| bobfilez\libs\bobgui | 5.0.0-ultrasonic | main | '95e89fc4de' | '2026-04-14' | 'Merge feature origin/1422-gtkentry-s-minimum-widt... |
| bobfilez\libs\bobui | N/A | main | 'f73a2e83e6' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\brotli | N/A | master | 'b3dc9cc' | '2026-04-14' | 'Merge pull request #1457 from google:dependabot/g... |
| bobfilez\libs\btk | 0.2.0 | master | 'd21bfdfb8' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\c-ares | N/A | master | '6298122' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\cURL | N/A | master | '634d04573' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\calibre | N/A | master | 'a923534' | '2026-04-14' | 'Merge branch 'copilot/add-tests-safe-replace-func... |
| bobfilez\libs\ckmame | N/A | main | '61b40199' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\cmark | N/A | master | '64efa3b' | '2026-03-01' | 'Fix running tests on Python 3.14' |
| bobfilez\libs\cyrus-sasl | N/A | master | '69b6288' | '2026-04-13' | 'Merge feature origin/cmb/2.1.28 into master' |
| bobfilez\libs\dirent | N/A | master | '1d454a8' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\dokany | N/A | master | 'feb4b7b' | '2026-04-14' | 'Merge feature origin/oplock-cancel-force into mas... |
| bobfilez\libs\dragonffi | N/A | master | '6790c07' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\dtl-diff | N/A | master | '32567bb' | '2024-07-11' | 'v1.21' |
| bobfilez\libs\dunst | N/A | master | 'e3fbe22' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\enchant | N/A | master | 'b0458c2' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\fast-lzma2 | N/A | master | '5ea485a' | '2026-04-13' | 'Merge feature origin/dev into master' |
| bobfilez\libs\freetype | N/A | master | 'fa9b229' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\fribidi | N/A | master | '09fa0da' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\fstlib | N/A | master | 'bb046ea' | '2026-04-14' | 'Merge feature origin/release into master' |
| bobfilez\libs\fuse_xattrs | N/A | master | 'acf60d4' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\gdk-pixbuf | N/A | main | '3648c0a' | '2026-04-11' | 'chore: save progress before update' |
| bobfilez\libs\getopt-win | N/A | getopt_glibc_2.42_port | 'ac1b9ea' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\getopt-win32 | N/A | original | 'f45e27d' | '2026-04-13' | 'Merge feature origin/ont_msvc14 into main' |
| bobfilez\libs\gettext | N/A | master | '68e963a' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\ghostpdl | N/A | master | '872e7b0' | '2026-04-13' | 'Type 2 CharString parser - treat missing endchar ... |
| bobfilez\libs\glad | N/A | glad2 | 'cef3f89' | '2026-04-09' | 'c: Try loading OpenGL through EGL if GLX isn't av... |
| bobfilez\libs\glib | N/A | master | 'de41341' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\hash-library | N/A | master | '1f94d39' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\hashcat | N/A | master | '28d049e04' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\hashingImage | N/A | master | '309a7c0' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\heif | N/A | master | '9b91888' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\highlightjs | N/A | main | '5697ae5' | '2025-07-06' | '(enh) Add 3rd party Abc Notation grammar to Suppo... |
| bobfilez\libs\httpd | N/A | trunk | '8b4f5a4dac' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\icu4c | N/A | master | '8a1dbca2' | '2026-04-13' | 'Merge feature origin/icu4c-78.2-1 into master' |
| bobfilez\libs\image-hash | N/A | master | '6c00e1979' | '2026-04-14' | 'Merge feature origin/dependabot/npm_and_yarn/form... |
| bobfilez\libs\image_info | N/A | master | 'f0ab154' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\imagehash | N/A | master | '5063b18' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\imageinfo | N/A | master | 'a257837' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\imap | N/A | master | '8b21912' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\imghash-viewer | N/A | main | '1154eb2' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\jhead | N/A | master | '54c91ad' | '2026-04-11' | 'chore: save progress before update' |
| bobfilez\libs\json-c | N/A | master | '1300fa1' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\libarchive | N/A | master | '6d9dddba' | '2026-04-13' | 'Merge pull request #2957 from kientzle/kientzle-l... |
| bobfilez\libs\libavif | N/A | master | 'fe09b88' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\libbzip2 | N/A | master | 'c380811' | '2026-04-13' | 'Merge feature origin/bzip2-1.0.6 into master' |
| bobfilez\libs\libde265 | N/A | master | '2032bd8' | '2026-04-12' | 'refpix.cc: fix integer overflow' |
| bobfilez\libs\libevent | N/A | master | 'd9df20f9' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\libexif | N/A | master | '8e33051' | '2026-04-14' | 'Merge feature origin/dfandrich/ci into master' |
| bobfilez\libs\libffi | N/A | master | '0c6c2c0' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\libgit2 | N/A | main | '3d2374c8b' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\libheif | N/A | master | '2d8845c7' | '2026-04-14' | 'Merge feature origin/ci-gcc-versions into master' |
| bobfilez\libs\libiconv | N/A | master | '09e4bfc' | '2026-04-13' | 'Merge feature origin/cmb/test into master' |
| bobfilez\libs\libimghash | N/A | master | '30b7d6d' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\libjpeg | N/A | master | '25f4abc' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\libjpeg-turbo | N/A | main | '8e23e046' | '2026-04-14' | 'Merge branch 'main' of https://github.com/libjpeg... |
| bobfilez\libs\libmcrypt | N/A | master | 'c14d309' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\libpng | N/A | master | 'e2f97fd' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\librsync | N/A | master | '271744d' | '2025-08-29' | 'Merge pull request #264 from trel/trel-rdiff.md' |
| bobfilez\libs\libsodium | N/A | master | '9c8e752' | '2026-04-11' | 'chore: save progress before update' |
| bobfilez\libs\libssh2 | N/A | master | '2ba19de' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\libtidy | N/A | master | '1665706' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\libunistd | 1.3 | master | 'bd579ab' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\libvbucket | N/A | master | 'f18a4dd' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\libvips | N/A | master | 'ca6489498' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\libvpx | N/A | master | 'c35e9cb' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\libwebp | N/A | master | 'ec08809' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\libxml2 | 2.16.0 | master | '44bcd030' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\libxmlplusplus | N/A | master | 'd9a3799' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\libxpm | N/A | master | '30f214d' | '2026-04-11' | 'chore: save progress before update' |
| bobfilez\libs\libxslt | N/A | master | '8cde8bf' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\libzip | N/A | main | '00f81978' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\lmdb | N/A | master | '6354a6a' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\lsads | N/A | master | 'b349877' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\lvgl | N/A | master | '29e9873c5' | '2026-04-14' | 'Merge feature origin/fix/wide-gifs into master' |
| bobfilez\libs\lz4 | N/A | dev | '9da37b2' | '2026-04-01' | 'Merge pull request #1730 from lz4/dependabot/gith... |
| bobfilez\libs\md4c | N/A | master | '481fbfb' | '2024-02-25' | 'Check for hard breaks more carefully to avoid fal... |
| bobfilez\libs\metastore | N/A | master | '9b78b5d' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\mm_file | N/A | master | 'e57b1b0' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\mpir | N/A | master | 'df470da' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\mpv | N/A | master | '5481a7d160' | '2026-04-14' | 'Merge feature origin/absurd_test3 into master' |
| bobfilez\libs\net-snmp | N/A | master | '3461e8d' | '2026-04-13' | 'Merge feature origin/cmb/memleak into master' |
| bobfilez\libs\nghttp2 | N/A | master | '2924fed' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\nihtest | N/A | main | '4a9329f' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\nihtest-cpp | N/A | main | '6f417fd' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\oniguruma | N/A | master | '433a24f' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\openapv | N/A | main | '3ba0276' | '2026-04-14' | 'Merge feature origin/add_444_12_and_4444_12 into ... |
| bobfilez\libs\opencv | N/A | master | '6965cf3501' | '2026-04-14' | 'Merge branch 'master' of https://github.com/openc... |
| bobfilez\libs\openexr | N/A | main | 'db6b41c0' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\openfx | N/A | main | '191f604' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\openh264 | N/A | master | '5d61ae0c' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\openjpeg | N/A | master | 'a42b4778' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\openldap | N/A | master | 'e8e17d8' | '2026-04-13' | 'Merge feature origin/cmb/2.5.18 into master' |
| bobfilez\libs\openssl | N/A | master | '8228c4c6' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\p7zip | N/A | master | '6819e2d' | '2025-05-20' | 'move license file to the root director (#252)' |
| bobfilez\libs\pHash | N/A | main | '2f69861' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\pHash.c | N/A | main | 'a03872e' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\pandoc | N/A | main | '5caad90' | '2026-04-13' | 'Docx reader with `citations` extension: prefer `c... |
| bobfilez\libs\pcre2 | N/A | main | '4247c78' | '2026-04-11' | 'Global Sync: Merged features, updated submodules,... |
| bobfilez\libs\perceptual-dct-hash | N/A | master | 'c533281' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\pngquant | N/A | main | '1808c8f' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\poppler | N/A | master | 'e092d11' | '2026-04-11' | 'Use existing tokenizer function and less GooStrin... |
| bobfilez\libs\postgresql | N/A | master | 'ae7d5552' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\pslib | N/A | main | '881d8e5' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\pthreads | N/A | main | '3015396' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\pxz | N/A | master | '6469dd6' | '2026-04-11' | 'chore: save progress before update' |
| bobfilez\libs\qdbm | N/A | master | '1a556e3' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\radare2 | N/A | master | '721421f892' | '2026-04-14' | 'Merge feature origin/abidir into master' |
| bobfilez\libs\rapidjson | N/A | master | 'a497b0a' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\raylib | N/A | master | 'e4e055413' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\re2 | N/A | main | '972a15c' | '2026-01-22' | 're2: remove unnecessary & in MutexLock usage' |
| bobfilez\libs\rename-utils | N/A | main | '4cffb0c' | '2026-02-20' | 'Fix build with libxml 2.15' |
| bobfilez\libs\ripgrep | N/A | master | '4519153' | '2026-02-27' | 'doc: clarify half-boundary syntax for the `-w/--w... |
| bobfilez\libs\securecopy | N/A | master | 'd4cb8e4' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\seek-tune | N/A | main | '5374d39' | '2026-03-01' | 'chore: save progress before update' |
| bobfilez\libs\sigil | N/A | master | 'd75d308' | '2026-04-12' | 'make sure MIT license header is used on the CSSDe... |
| bobfilez\libs\sqlite | 3.54.0 | master | '8f67561824' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\sqlite3 | N/A | master | '817931b' | '2026-04-11' | 'chore: save progress before update' |
| bobfilez\libs\ssdeep | N/A | master | 'd0e31a5' | '2026-04-11' | 'chore: save progress before update' |
| bobfilez\libs\sumatrapdf | N/A | master | 'de542bc13' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\the_silver_searcher | N/A | master | 'a61f178' | '2020-12-16' | 'Merge pull request #1424 from sanjaymsh/ppc64le' |
| bobfilez\libs\tinyphash | N/A | master | 'ccab513' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\tinyxml2 | N/A | master | '22a9c87' | '2026-04-14' | 'Merge feature origin/leethomason/docs into master... |
| bobfilez\libs\util-linux | N/A | master | '1bb25e774' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\vlc | N/A | master | '9efa0f3720' | '2026-04-14' | 'Merge branch 'master' of https://github.com/video... |
| bobfilez\libs\wineditline | N/A | master | '20dd166' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\wkhtmltopdf | 0.12.7-dev | master | 'd398c8a' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\xattrlib | N/A | master | '85522f2' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\xattrs | N/A | master | 'b60f534' | '2026-02-26' | 'chore: save progress before update' |
| bobfilez\libs\xxHash | N/A | dev | '28ac630' | '2026-04-14' | 'Merge feature origin/dependabot/github_actions/os... |
| bobfilez\libs\ziptools | N/A | main | 'b9864d1' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\zlib | N/A | master | 'bc33e6c' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\zstd | N/A | dev | '48c0ed7' | '2026-04-01' | 'Merge pull request #4635 from facebook/dependabot... |
| bobmani\arrowvortex\odcnn | N/A | master | '454f4c7' | '2020-02-26' | 'small change' |
| bobmani\beatoraja\bobcoin | N/A | main | '9a1dcff' | '2026-04-14' | 'Merge branch 'main' of https://github.com/robertp... |
| bobmani\beatoraja\lr2oraja-endlessdream | N/A | main | '47d3b7f5' | '2026-04-14' | 'Merge feature origin/bugfix-key-c-binding into ma... |
| bobmani\ddc\ddc_onset | N/A | main | '53044b5' | '2026-04-11' | 'Global Sync: Merged features, updated submodules,... |
| bobmani\ddc\ffr-difficulty-model | N/A | master | '8d21998' | '2026-04-11' | 'Auto-sync: update files and submodules' |
| bobmani\itgmania\bobcoin | N/A | main | '9a1dcff' | '2026-04-14' | 'Merge branch 'main' of https://github.com/robertp... |
| bobmani\ksm-v2\ksmaxis | N/A | master | 'dc522d0' | '2026-04-14' | 'chore: save local progress before sync' |
| bobmani\ksm-v2\kson | N/A | master | 'cef4485' | '2026-04-14' | 'chore: save local progress before sync' |
| bobmani\linthesia\pianogame | N/A | master | '5860035' | '2026-02-27' | 'Merge branch 'master' of https://github.com/rober... |
| bobsgameonlinejava\libs\aseprite-file | N/A | master | '06b6189' | '2018-12-01' | 'Update README.md' |
| bobsgameonlinejava\libs\commons-lang | N/A | master | '7138b8c00' | '2026-04-14' | 'Bump actions/upload-artifact from 7.0.0 to 7.0.1' |
| bobsgameonlinejava\libs\jinput | N/A | master | 'f79007c' | '2026-04-03' | 'Merge pull request #409 from jinput/dependabot/ma... |
| bobsgameonlinejava\libs\lwjgl3 | N/A | master | 'f7909c672' | '2026-04-06' | 'feat(harfbuzz) update to 14.1.0' |
| bobsgameonlinejava\libs\lz4-java | N/A | master | 'be9ce57' | '2025-11-28' | 'Merge pull request #232 from yawkat/patch-1' |
| bobsgameonlinejava\libs\micromod | N/A | master | '287d8fa' | '2026-03-12' | 'Improve resampler and add gain control to wavefor... |
| bobsgameonlinejava\libs\mysql-connector-j | N/A | release/9.x | 'fdef61f4' | '2025-12-17' | 'Update copyright year.' |
| bobsgameonlinejava\libs\twl-lwjgl3 | N/A | master | '647ec34' | '2016-10-02' | 'Update README.md' |
| bobsgameonlinejava\libs\xpp3 | N/A | master | '68498e7' | '2025-04-13' | 'Remove oss-parent and add GPG and central publish... |
| bobsgameonlinejava\libs\xz-java | N/A | master | '492b6ea' | '2026-03-01' | 'Fix copy-paste errors in NEWS.md' |
| bobsgameonlinejava\references\Cytopia | N/A | master | 'b67e255d' | '2025-03-28' | 'Migrate config renovate.json' |
| bobsgameonlinejava\references\DTile | N/A | master | '22a977f' | '2018-04-04' | 'Add keyboard shortcuts to rename dialog and make ... |
| bobsgameonlinejava\references\GrowTools | N/A | master | 'fe146b8' | '2025-11-21' | 'Update rtconverter.html' |
| bobsgameonlinejava\references\LibreSprite | N/A | master | '4b30f8fb3' | '2026-04-08' | 'Update GitHub workflow with manual app codesignin... |
| bobsgameonlinejava\references\OgmoEditor3-CE | N/A | master | 'b2a5215' | '2022-01-19' | 'Merge pull request #209 from hubol/support-tabbin... |
| bobsgameonlinejava\references\Pixelorama | N/A | master | '02a879c6' | '2026-04-13' | 'Workaround for https://github.com/godotengine/god... |
| bobsgameonlinejava\references\PixiEditor | N/A | master | 'b8c9626a9' | '2026-04-14' | 'Changed category of Character Position Node' |
| bobsgameonlinejava\references\PyxleOS | N/A | master | '624359c' | '2017-03-26' | 'haha typo' |
| bobsgameonlinejava\references\Raylib-Examples | N/A | master | 'abe00d9' | '2023-02-20' | 'Update README.md' |
| bobsgameonlinejava\references\Simple-Sprite-Tile-2D | N/A | master | 'c5ba692' | '2017-04-10' | 'Fix Scale.Z vector' |
| bobsgameonlinejava\references\SpeedEd | N/A | main | '0be20dc' | '2022-01-01' | 'Update year in Copyright notice' |
| bobsgameonlinejava\references\Tile-Studio | N/A | master | 'd0f5d2e' | '2021-07-17' | 'Palette manager: save as GIMP Palette' |
| bobsgameonlinejava\references\aseprite | N/A | main | '4f7df5fc5' | '2026-04-08' | 'Fix regression crash when removing cel in tool lo... |
| bobsgameonlinejava\references\aseprite-guide | N/A | main | '471c8ec' | '2025-10-03' | 'Update AsepriteV1.3.4.md' |
| bobsgameonlinejava\references\blockbench | N/A | master | '39ad4b4c' | '2026-04-14' | 'Update contributing guide' |
| bobsgameonlinejava\references\bottled-up-tilemap | N/A | daelon-refactor | '7a93386' | '2023-04-07' | 'Update README.md' |
| bobsgameonlinejava\references\csprite | N/A | master | '11eca90' | '2025-08-05' | 'Update function names' |
| bobsgameonlinejava\references\goxel | N/A | master | '1f763149' | '2026-01-20' | 'gltf: add option to export only visible layers' |
| bobsgameonlinejava\references\grafx2 | N/A | master | '94b1babf' | '2020-12-11' | 'Remove obsolete tag from Doxyfile' |
| bobsgameonlinejava\references\grafx2-dos | N/A | master | '4258bdd' | '2022-04-03' | 'Remove leading directory names from paths.' |
| bobsgameonlinejava\references\piskel | N/A | master | 'a6b9c02d' | '2026-04-09' | 'Merge pull request #1260 from juliandescottes/tes... |
| bobsgameonlinejava\references\raster-master | N/A | main | '9679baf' | '2026-03-20' | 'Update 6.0 R127' |
| bobsgameonlinejava\references\retro-game-editor | N/A | master | '2a93781' | '2017-07-13' | 'Trying to solve 'localforage-backbone' conflicts' |
| bobsgameonlinejava\references\rx | N/A | master | '1bcbe90' | '2023-07-02' | 'Fix SVG rendering' |
| bobsgameonlinejava\references\sprite-studio-64 | N/A | main | '5661c39' | '2024-04-06' | 'Update README.md' |
| bobsgameonlinejava\references\stipple-effect | N/A | master | 'a47e8fa' | '2025-01-30' | 'Merge pull request #179 from stipple-effect/dev-b... |
| bobsgameonlinejava\references\tactile | N/A | main | 'eb98a4c7c' | '2022-09-07' | 'Update vcpkg.json' |
| bobsgameonlinejava\references\tiled | N/A | master | 'fa6254757' | '2026-04-13' | 'Bump softprops/action-gh-release from 2 to 3 (#45... |
| bobsgameonlinejava\references\tilemap-editor | N/A | main | '758cdbb' | '2022-12-07' | 'tilemap editor api improvements' |
| bobsgameonlinejava\references\tilemap-studio | N/A | master | 'ffcce44' | '2025-09-12' | 'Update FLTK to 1.4.4 (#87)' |
| bobui\submodules\juce | N/A | master | '501c07674e' | '2026-01-16' | 'Docs: Add a course link to the Doxygen layout' |
| bobui\submodules\ultimatepp | N/A | master | '70657d292' | '2026-04-09' | 'Draw: In Win32, DrawImage with Color now using Ca... |
| borg\apps\cloud-orchestrator | <<<<<<< HEAD
3.6.0
| borg\apps\maestro | 0.15.7 | main | '13d4f4b8' | '2026-04-14' | 'Merge feature origin/jules-2575151016458646249-2d... |
| borg\archive\OmniRoute | N/A | main | 'eaec3279' | '2026-04-13' | 'Merge pull request #1192 from diegosouzapw/releas... |
| borg\archive\claude-mem | N/A | main | '0d507feb' | '2026-04-14' | 'chore: save local progress before sync' |
| borg\data\bobbybookmarks | N/A | main | '398a7488' | '2026-04-14' | 'chore: save local progress before sync' |
| borg\packages\claude-mem | N/A | main | 'dc0e6a46' | '2026-04-14' | 'Merge branch 'main' of https://github.com/robertp... |
| borg\submodules\borg | N/A | main | '37830d7' | '2026-04-05' | 'feat(tui): add compact pane summary command' |
| borg\submodules\prism-mcp | N/A | main | 'c9e3b47' | '2026-04-14' | 'chore(deps): bump follow-redirects' |
| borg\tmp\cloud-orchestrator-sync | 1.0.0-alpha.25 | cloud-orchestrator-sync | '6b7551b63' | '2026-04-14' | 'chore: save local progress before sync' |
| btk\external\bobui-reference | N/A | main | '3377820441' | '2026-04-14' | 'chore: save local progress before sync' |
| btk\external\juce | N/A | master | '419d0643a6' | '2026-04-14' | 'Merge feature origin/develop into master' |
| btk\external\ultimatepp | N/A | master | 'f23ca1058' | '2026-04-14' | 'Merge feature origin/QHD into master' |
| f-zerox\tools\asm-differ | N/A | main | '4c70d6a' | '2026-04-13' | 'Merge feature origin/add-powerpc-xenon-arch into ... |
| f-zerox\tools\asm-processor | N/A | main | 'b062e6e' | '2026-04-14' | 'chore: save local progress before sync' |
| f-zerox\tools\ido5.3_cc | N/A | master | 'faa773c' | '2019-12-24' | 'ido 5.3' |
| f-zerox\tools\splat | N/A | main | '9709206' | '2026-04-14' | 'chore: save local progress before sync' |
| geany\subprojects\bobgui | 5.0.0-ultrasonic | main | '2507913a01' | '2026-04-14' | 'Merge branch 'main' of https://github.com/robertp... |
| geany\subprojects\bobui | N/A | main | '6dc5794d382' | '2026-04-14' | 'chore: save local progress before sync' |
| geany\subprojects\btk | 0.2.0 | master | '19be40254' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode-push\apps\cloud-orchestrator | <<<<<<< HEAD
3.6.0
| hypercode-push\apps\maestro | 0.15.7 | main | '3718339f' | '2026-04-14' | 'Merge feature origin/jules-2575151016458646249-2d... |
| hypercode-push\archive\OmniRoute | N/A | main | '04dfcf13' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode-push\archive\claude-mem | N/A | main | '1f0ed064' | '2026-04-14' | 'Merge branch 'main' of https://github.com/robertp... |
| hypercode-push\packages\claude-mem | N/A | main | 'f719a3f1' | '2026-04-14' | 'Merge branch 'main' of https://github.com/robertp... |
| hypercode-push\submodules\hyperharness | 0.3.0 | main | '3982f660' | '2026-04-13' | 'chore: save local progress before sync' |
| hypercode-push\submodules\prism-mcp | N/A | main | 'c9e3b47' | '2026-04-14' | 'chore(deps): bump follow-redirects' |
| hypercode\archive\OmniRoute | N/A | main | '12aadf46' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode\archive\claude-mem | N/A | main | 'f5d0b949' | '2026-04-14' | 'Merge branch 'main' of https://github.com/robertp... |
| hypercode\submodules\hyperharness | N/A | main | '3982f660' | '2026-04-13' | 'chore: save local progress before sync' |
| hypercode\submodules\prism-mcp | N/A | main | 'c9e3b47' | '2026-04-14' | 'chore(deps): bump follow-redirects' |
| hyperharness\llamafile\llama.cpp | N/A | master | '8763823e4' | '2026-04-14' | 'chore: save local progress before sync' |
| hyperharness\llamafile\stable-diffusion.cpp | N/A | master | '73ce4b8' | '2026-04-14' | 'chore: save local progress before sync' |
| hyperharness\llamafile\whisper.cpp | N/A | master | '93727cda' | '2026-04-14' | 'chore: save local progress before sync' |
| mcp-superassistant\packages\byterover-cipher | N/A | HEAD | '81552257' | '2025-12-16' | 'Merge pull request #290 from MahlerTom/bug/sqlite... |
| mk64\tools\asm-differ | N/A | main | '7f5c026' | '2026-04-13' | 'Merge feature origin/add-powerpc-xenon-arch into ... |
| mk64\tools\decomp-permuter | N/A | main | 'cb7132a' | '2026-04-14' | 'chore: save local progress before sync' |
| mk64\tools\torch | N/A | main | '84174c8' | '2026-04-14' | 'chore: save local progress before sync' |
| pi-mono\submodules\aider | N/A | HEAD | 'f09d7065' | '2026-04-08' | 'feat: Enable overeager mode for Claude Sonnet 4.5... |
| pi-mono\submodules\opencode-cli | N/A | HEAD | '5b0c8300e' | '2026-04-05' | 'docs(changelog): update for v0.6.92 [skip ci]' |
| superai\llamafile\llama.cpp | N/A | master | '274a54600' | '2026-04-14' | 'chore: save local progress before sync' |
| superai\llamafile\stable-diffusion.cpp | N/A | master | 'be1a17a' | '2026-04-14' | 'chore: save local progress before sync' |
| superai\llamafile\whisper.cpp | N/A | master | '101e38ac' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\libs\aseprite-file | N/A | master | 'dfa79dd' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\libs\commons-lang | N/A | HEAD | '7138b8c00' | '2026-04-14' | 'Bump actions/upload-artifact from 7.0.0 to 7.0.1' |
| bg\bobsgameonlinejava\libs\jinput | N/A | master | '40fae2e' | '2026-04-11' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\libs\lwjgl3 | N/A | master | '35c70e1c5' | '2026-04-11' | 'Global Sync: Consolidated feature branches and up... |
| bg\bobsgameonlinejava\libs\lz4-java | N/A | master | '646fb46' | '2026-04-14' | 'Merge feature origin/Java7Build into master' |
| bg\bobsgameonlinejava\libs\micromod | N/A | master | '953029e' | '2026-03-25' | 'chore: intelligently resolve merge conflicts' |
| bg\bobsgameonlinejava\libs\mysql-connector-j | N/A | release/9.x | '425d46c3' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\libs\twl-lwjgl3 | N/A | master | 'de05f4e' | '2026-03-11' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\libs\xpp3 | N/A | master | '61cb446' | '2026-03-11' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\libs\xz-java | N/A | master | '06b51b8' | '2026-04-11' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\Cytopia | N/A | master | '15261fed' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\DTile | N/A | master | '7e062f5' | '2026-02-27' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\GrowTools | N/A | master | '464d619' | '2026-02-27' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\LibreSprite | N/A | master | '5efc49bb5' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\OgmoEditor3-CE | N/A | master | 'dfbb1ef' | '2026-04-14' | 'Merge feature origin/feature/typed-export-data in... |
| bg\bobsgameonlinejava\references\Pixelorama | N/A | master | '2e6772fa' | '2026-04-13' | 'Merge branch 'master' of https://github.com/Orama... |
| bg\bobsgameonlinejava\references\PixiEditor | N/A | master | '659b5ea99' | '2026-04-14' | 'Merge branch 'master' of https://github.com/PixiE... |
| bg\bobsgameonlinejava\references\PyxleOS | N/A | master | '68dc41e' | '2026-02-27' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\Raylib-Examples | N/A | master | '387800c' | '2026-02-27' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\Simple-Sprite-Tile-2D | N/A | master | 'd77e3db' | '2026-02-27' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\SpeedEd | N/A | main | 'aece583' | '2026-02-27' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\Tile-Studio | N/A | master | 'e5f97d5' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite | N/A | main | 'ee168cce9' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite-guide | N/A | main | '8b44c38' | '2026-02-27' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\blockbench | N/A | master | '6067c85a' | '2026-04-14' | 'Merge feature origin/gh-pages into master' |
| bg\bobsgameonlinejava\references\bottled-up-tilemap | N/A | main | 'cb9e753' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\csprite | N/A | master | '0578f00' | '2026-02-27' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\goxel | N/A | master | 'f4e2fb25' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\grafx2 | N/A | master | 'e414bd65' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\grafx2-dos | N/A | master | 'f031af7' | '2026-02-27' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\piskel | N/A | master | 'b669492f' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\raster-master | N/A | main | 'b63d476' | '2026-04-11' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\retro-game-editor | N/A | master | '3812e2a' | '2026-04-11' | 'Global Sync: Consolidated feature branches and up... |
| bg\bobsgameonlinejava\references\rx | N/A | master | '8c57a90' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\sprite-studio-64 | N/A | main | 'adecf6e' | '2026-02-27' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\stipple-effect | N/A | master | 'cd03543' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\tactile | N/A | main | '2eacbf1e3' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\tiled | N/A | master | '9d8130f90' | '2026-04-14' | 'Merge feature origin/dependabot/github_actions/ac... |
| bg\bobsgameonlinejava\references\tilemap-editor | N/A | main | '4e2b0fb' | '2026-02-27' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\tilemap-studio | N/A | master | 'd3dd414' | '2026-02-27' | 'chore: save progress before update' |
| bg\okgame\lib\CTPL | N/A | master | '437e135' | '2015-06-12' | 'fixed a bug - crash' |
| bg\okgame\lib\Craft | N/A | master | '1d9159b' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\FBNeo | N/A | HEAD | '659fefe34' | '2026-04-11' | 'Global Sync: Consolidated feature branches and up... |
| bg\okgame\lib\GWEN | N/A | main | '5a4fab4' | '2026-03-21' | 'chore: save progress before update' |
| bg\okgame\lib\Genesis-Plus-GX | N/A | HEAD | 'c7ecd07' | '2026-03-24' | 'Updated builds and changelog' |
| bg\okgame\lib\MODPlay | N/A | master | '1121103' | '2026-02-17' | 'Update README to reflect move to Codeberg' |
| bg\okgame\lib\Maelstrom | N/A | HEAD | '7911378' | '2026-04-11' | 'Global Sync: Consolidated feature branches and up... |
| bg\okgame\lib\MicroPather | N/A | master | '33a3b84' | '2016-10-17' | 'Merge pull request #16 from sagamusix/master' |
| bg\okgame\lib\MilkDrop3 | N/A | main | '218af58' | '2026-04-01' | 'Merge branch 'main' of https://github.com/robertp... |
| bg\okgame\lib\Nuklear | N/A | master | '9217391' | '2026-04-14' | 'Merge feature origin/fix-nk_size-for-nk_memcpy in... |
| bg\okgame\lib\RetroArch | N/A | master | 'bfaa74d6a7' | '2026-04-14' | 'Merge branch 'master' of https://github.com/libre... |
| bg\okgame\lib\SDL | N/A | main | '8c6ae6d20' | '2026-04-14' | 'Merge branch 'main' of https://github.com/libsdl-... |
| bg\okgame\lib\SDL2_gfx | N/A | master | 'd985671' | '2022-12-15' | 'Removed USE_MMX from Debug/x64, updated names' |
| bg\okgame\lib\SDL_gesture | N/A | main | 'dfd3001' | '2025-11-06' | 'Use libsdl-org/setup-sdl + private setup-ninja ac... |
| bg\okgame\lib\SDL_image | N/A | main | '4f98764b' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_mixer | N/A | main | '677f8a4a' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_native_midi | N/A | main | '6423664' | '2025-11-17' | 'fixed several -Wzero-as-null-pointer-constant war... |
| bg\okgame\lib\SDL_net | N/A | main | 'b1774e4' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_rtf | N/A | HEAD | 'c2c8165' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_ttf | N/A | HEAD | 'aab1afc' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\Snippets | N/A | master | '09d739b' | '2026-04-12' | 'Merge feature origin/filehandling into master' |
| bg\okgame\lib\UACME | N/A | master | '6daa8d4' | '2026-02-17' | 'Update Yuubari and fix some bugs' |
| bg\okgame\lib\WavPack | N/A | master | 'ad71427' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\aom | N/A | main | '481a01604' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost | N/A | master | '73db166c7e' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\cppcodec | N/A | HEAD | '6e71248' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\dav1d | N/A | HEAD | '27fd0906' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\defold-astar | N/A | HEAD | '3d8d117' | '2026-03-09' | 'readme + agent + copilot instructions' |
| bg\okgame\lib\flac | N/A | master | 'b6138f45' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\freetype | N/A | master | 'aa6c60b6c' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\gambatte-libretro | N/A | master | 'fda41ca' | '2026-04-12' | 'Merge feature origin/revert-269-master into maste... |
| bg\okgame\lib\game-music-emu | N/A | HEAD | 'f02fbca' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\glad | N/A | HEAD | '02a74fe' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\glew | N/A | master | 'fc1bfeb' | '2026-04-14' | 'Merge feature origin/blacklist-MESA_sampler_objec... |
| bg\okgame\lib\glfw | N/A | master | '859b7da6' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\gpsp | N/A | master | '3ca9809' | '2026-04-13' | 'Merge feature origin/new-targets into master' |
| bg\okgame\lib\harfbuzz | N/A | main | '4004e06d4' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\highway | N/A | master | 'a42f7681' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\imgui | N/A | master | '23027227d' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\jpeg | N/A | HEAD | 'b8e1152' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\libavif | N/A | main | 'a141a564' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\libjxl | N/A | main | 'b75cd676' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\libmidi | N/A | main | '1b5c6e1' | '2024-10-29' | 'update cmake file' |
| bg\okgame\lib\libmodplug | N/A | master | 'd1b97ed' | '2022-01-31' | 'Merge pull request #83 from AliceLR/fix-pat-strin... |
| bg\okgame\lib\libpng | N/A | master | '7774b6e60' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\libretro-common | N/A | HEAD | 'd45d9f6' | '2026-04-13' | 'Resync' |
| bg\okgame\lib\libretro-fceumm | N/A | master | '7583f5b' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\libretro-lutro | N/A | master | '7c687ff' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\libretro-samples | N/A | master | 'bce193b' | '2022-11-10' | 'Merge pull request #27 from libretro/CI-PS4' |
| bg\okgame\lib\libretro-super | N/A | master | 'de9b276a' | '2026-04-07' | 'Merge pull request #1973 from cscd98/mupen-gles' |
| bg\okgame\lib\libtiff | <<<<<<< HEAD
4.7.1
| bg\okgame\lib\libtimidity | N/A | master | 'be69669' | '2026-04-12' | 'Merge feature origin/soundfont into master' |
| bg\okgame\lib\libusb | N/A | HEAD | 'ccc1c53a' | '2026-04-10' | 'Misc: Update README file to add current developer... |
| bg\okgame\lib\libwebp | N/A | main | '20dd8706' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\libxmp | N/A | HEAD | '68f9efd0' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\lz4-java | N/A | master | '0f1b991' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\md5-c | N/A | main | '5327bf6' | '2026-04-11' | 'Auto-sync: Protocol Update 2026-04-11' |
| bg\okgame\lib\melonDS | N/A | HEAD | '2ce513d3' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\mgba | N/A | master | '4f25d9d0a' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\miniz | N/A | master | '7b4106e' | '2026-04-11' | 'Auto-sync: Protocol Update 2026-04-11' |
| bg\okgame\lib\mpg123 | N/A | main | '28757b0' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\mpv | N/A | master | '84adeaf0cb' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\nanogui | N/A | master | '19d0c68' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\nanogui-sdl | N/A | master | '92ced8b' | '2026-04-11' | 'Global Sync: Merged features, updated submodules,... |
| bg\okgame\lib\nestopia | N/A | master | 'b0fd87d' | '2026-04-02' | 'libretro: add webOS to CI (#110)' |
| bg\okgame\lib\nngui | N/A | master | 'c2b6c2b' | '2016-09-06' | 'added basic context menu widget' |
| bg\okgame\lib\ogg | N/A | main | '6721ef8' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\opus | N/A | main | '3cd79d30' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\opusfile | N/A | HEAD | '28a1701' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\paulxstretch | N/A | main | 'c4967df' | '2026-04-12' | 'Merge feature origin/develop into main' |
| bg\okgame\lib\picodrive | N/A | master | '4749fa51' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\plutosvg | N/A | HEAD | 'bb27ab0' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\plutovg | N/A | main | '3f46f9d' | '2026-04-12' | 'Merge feature origin/v1.1.0-SDL into main' |
| bg\okgame\lib\poco | <<<<<<< HEAD
1.15.1
| bg\okgame\lib\projectm | N/A | HEAD | 'fc45c2af5' | '2026-04-13' | 'Fix projectm-eval submodule sync' |
| bg\okgame\lib\raylib | N/A | master | '019cc889' | '2026-04-13' | 'Updated Notepad++ scripts and autocomplete' |
| bg\okgame\lib\retroarch-assets | N/A | master | 'cd17f64c' | '2026-04-11' | 'Merge pull request #493 from comfysage/feat/asset... |
| bg\okgame\lib\retroarch-joypad-autoconfig | N/A | master | '6ae0376' | '2026-04-12' | 'Merge feature origin/xbox-one-wireless-bt into ma... |
| bg\okgame\lib\sdl2-compat | N/A | main | '91d36b8' | '2026-04-04' | 'Expose SDL3 version string in SDL3_VERSION hint' |
| bg\okgame\lib\sigar | N/A | master | 'c745bdd0' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\snes9x | N/A | HEAD | '3f55d00a' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\snes9x2010 | N/A | master | '30633e8' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\soundtouch | N/A | HEAD | '56890ed' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\stb | N/A | master | '3c76ac7' | '2026-04-12' | 'Merge feature origin/stb_vorbis-sezero into maste... |
| bg\okgame\lib\timidity | N/A | cvs | 'f726f8f' | '2026-04-01' | 'Merge remote-tracking branch 'origin/cvs-R2_12_0_... |
| bg\okgame\lib\tremor | N/A | main | '7ab30ad' | '2026-04-13' | 'Merge feature origin/v1.2.1-SDL into master' |
| bg\okgame\lib\vba-next | N/A | master | 'd0ec7f3' | '2024-10-21' | 'Merge pull request #153 from warmenhoven/warmenho... |
| bg\okgame\lib\vbam-libretro | N/A | master | '02342c67' | '2026-04-11' | 'Global Sync: Merged features, updated submodules,... |
| bg\okgame\lib\vorbis | N/A | main | '274f59c' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\zlib | N/A | master | '7289c50' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\ai-file-sorter\external\Catch2 | N/A | HEAD | '9cfa51c2' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\SysmonForLinux\sysmonCommon | N/A | main | '6c01e63' | '2026-04-12' | 'Merge feature origin/nicolejms-patch-1 into main' |
| bobfilez\libs\pngquant\lib | N/A | main | '198571b' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\wkhtmltopdf\qt | N/A | wk_4.8.7 | 'cc6d5e1d37' | '2026-04-14' | 'chore: save local progress before sync' |
| bobmani\bobmania\Themes\Simply-Love-SM5 | N/A | HEAD | 'ed98aad9' | '2025-06-22' | 'Version bump to 5.7.0' |
| bobmani\itgmania\Themes\Simply Love | N/A | HEAD | 'e9ac235b' | '2026-03-26' | 'Remove (beta)' |
| bobmani\itgmania\Themes\Simply-Love-SM5 | N/A | HEAD | '5c23b0ba' | '2026-02-26' | 'Merge branch 'itgmania-release' of https://github... |
| bobmani\itgmania\extern\IXWebSocket | N/A | HEAD | '150e3d8' | '2025-08-05' | 'Fix spelling error: 'perpertually' â†’ 'perpetual... |
| bobmani\itgmania\extern\ffmpeg | N/A | HEAD | '10928524068' | '2026-04-13' | 'swscale/ops: remove type from continuation functi... |
| bobmani\itgmania\extern\hidapi | 0.16.0 | HEAD | '657b9fa' | '2026-03-20' | 'netbsd: check if iconv(3) requires pointer-to-con... |
| bobmani\itgmania\extern\libjpeg-turbo | N/A | HEAD | '31448a81' | '2026-03-21' | 'j*lossls.c: Throw error if cinfo.Ss < 1 or > 7' |
| bobmani\itgmania\extern\libpng | N/A | HEAD | 'd5515b5b8b' | '2026-03-25' | 'Release libpng version 1.6.56' |
| bobmani\itgmania\extern\libtomcrypt | N/A | HEAD | '66925c259c' | '2026-04-13' | 'Fix `helper.pl`. [skip ci]' |
| bobmani\itgmania\extern\libtommath | N/A | HEAD | '652d70a' | '2026-04-07' | 'Merge pull request #594 from libtom/deploy-for-ar... |
| bobmani\itgmania\extern\libusb | N/A | main | 'bb56796' | '2026-04-11' | 'chore: save progress before update' |
| bobmani\itgmania\extern\mbedtls | N/A | development | 'b500453002' | '2026-04-11' | 'Global Sync: Consolidated feature branches and up... |
| bobmani\itgmania\extern\ogg | N/A | main | 'e261e29' | '2026-04-11' | 'chore: save progress before update' |
| bobmani\itgmania\extern\vorbis | N/A | main | '4d06c39' | '2026-04-11' | 'chore: save progress before update' |
| bobmani\itgmania\extern\zlib | N/A | develop | 'f42980c' | '2026-04-11' | 'chore: save progress before update' |
| bobsaver\projectm\vendor\projectm-eval | N/A | master | '99a6aef' | '2026-04-13' | 'Merge feature origin/fix-pkgconfig-destdir into m... |
| bobtrader\submodules\page-02\Bohr1005__xcrypto | N/A | main | '3d9fb4d' | '2025-01-18' | 'Update README.md' |
| bobtrader\submodules\page-02\JulyIghor__QtBitcoinTrader | N/A | master | '7941537' | '2025-06-25' | 'cleanup' |
| bobtrader\submodules\page-02\Roibal__Cryptocurrency-Trading-Bots-Python-Beginner-Advance | N/A | master | '6cd9f63' | '2019-01-18' | 'Print Exception Raised' |
| bobtrader\submodules\page-02\TraderAlice__OpenAlice | N/A | master | '3d3a29b' | '2026-04-14' | 'Merge pull request #123 from TraderAlice/dev' |
| bobtrader\submodules\page-02\ctubio__Krypto-trading-bot | N/A | master | 'f592cc3' | '2024-12-15' | 'Updated highcharts UI dependency.' |
| bobtrader\submodules\page-02\jammy928__CoinExchange_CryptoExchange_Java | N/A | master | '8adf508' | '2021-11-05' | 'Update README.md' |
| bobtrader\submodules\page-02\pirate__crypto-trader | N/A | master | 'ec5d709' | '2019-04-03' | 'Update README.md' |
| bobtrader\submodules\page-02\scrtlabs__catalyst | N/A | master | '2e80297' | '2021-09-22' | 'Merge pull request #585 from enigmampc/project-de... |
| bobtrader\submodules\page-02\taniman__profit-trailer | N/A | master | '04d8f20' | '2020-05-14' | 'Update README.md' |
| bobtrader\submodules\page-02\warp-id__solana-trading-bot | N/A | master | '4c9304a' | '2024-05-22' | 'Merge pull request #109 from ajakka/master' |
| bobtrader\submodules\page-03\AdeelMufti__CryptoBot | N/A | master | '6cbdfea' | '2017-01-17' | 'Initial commit' |
| bobtrader\submodules\page-03\Ekliptor__WolfBot | N/A | master | '0f45aae' | '2023-02-17' | 'updated dependencies' |
| bobtrader\submodules\page-03\GuillermoEguilaz__Polymarket-Crypto-Trading-Bot | N/A | main | '60b068a' | '2026-03-14' | 'Initial commit' |
| bobtrader\submodules\page-03\Krypto-Hashers-Community__polymarket-crypto-sports-arbitrage-trading-bot | N/A | main | '4f53f77' | '2026-03-29' | 'Update README.md' |
| bobtrader\submodules\page-03\RobertMarcellos__polymarket-copy-trading-bot | N/A | main | '6a98bf3' | '2026-04-05' | 'version 2.0' |
| bobtrader\submodules\page-03\ericjang__cryptocurrency_arbitrage | N/A | master | '88d5429' | '2026-04-10' | 'chore: remove orphan submodule entry fxbtc' |
| bobtrader\submodules\page-03\kelvinau__crypto-arbitrage | N/A | master | '44a3469' | '2024-02-17' | 'add link to introduction of professional trader c... |
| bobtrader\submodules\page-03\markusaksli__TradeBot | N/A | master | '2296fe6' | '2024-11-05' | 'Bump commons-io:commons-io from 2.8.0 to 2.14.0 (... |
| bobtrader\submodules\page-03\saniales__golang-crypto-trading-bot | N/A | main | '02695e5' | '2025-09-30' | 'fix(examples): Removed Slack example due to libra... |
| bobtrader\submodules\page-03\steeply__gbot-trader | N/A | master | 'c8240aa' | '2024-05-14' | 'fix candles bitfinex' |
| bobtrader\submodules\page-04\0xAxon7__polymarket-almanac-arbitrage-trading-bot-sports-crypto | N/A | main | 'f88366a' | '2026-03-31' | 'feat: switch copy-trading flow to global wallet a... |
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
| bobtrader\submodules\page-05\Brunofancy__polymarket-trading-agent | N/A | main | 'dbcf83c' | '2026-03-27' | 'docs: add workflow diagram images (step1 and full... |
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
| bobtrax\bobui\submodules\juce | N/A | HEAD | '501c07674e' | '2026-01-16' | 'Docs: Add a course link to the Doxygen layout' |
| bobtrax\bobui\submodules\ultimatepp | N/A | HEAD | '70657d292' | '2026-04-09' | 'Draw: In Win32, DrawImage with Color now using Ca... |
| bobtrax\lmms\doc\wiki | N/A | master | '3e9a38b' | '2026-04-02' | 'Updated Making a music on LMMS (markdown)' |
| borg\archive\submodules\mcpproxy | N/A | main | 'd43b27f' | '2025-07-22' | 'Fix Tool Indexing, Persistence, and Retrieval Iss... |
| borg\submodules\prism-mcp\Brave-Gemini-Research-MCP-Server | N/A | main | '0418355' | '2025-04-13' | 'Update README.md' |
| hypercode-push\archive\submodules\litellm | N/A | main | 'cd3272a00f' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode-push\archive\submodules\mcpproxy | N/A | main | 'd43b27f' | '2025-07-22' | 'Fix Tool Indexing, Persistence, and Retrieval Iss... |
| hypercode-push\submodules\hyperharness\adrenaline | N/A | master | '2948ed9' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode-push\submodules\hyperharness\aider | N/A | main | 'f4906ca2' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode-push\submodules\hyperharness\amazon-q-developer-cli | N/A | main | '160f11a1' | '2026-04-14' | 'Merge feature origin/arjun37602-patch-1 into main... |
| hypercode-push\submodules\hyperharness\auggie | N/A | main | 'ad1f83f' | '2026-04-14' | 'Merge feature origin/test/readme-pr-workflow-2026... |
| hypercode-push\submodules\hyperharness\azure-ai-cli | N/A | main | '9be15bf' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode-push\submodules\hyperharness\bito-cli | N/A | main | 'cb3a779' | '2025-04-23' | 'README.md' |
| hypercode-push\submodules\hyperharness\byterover-cli | N/A | main | '6a921ed4' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode-push\submodules\hyperharness\claude-code | N/A | main | 'a371abb' | '2026-04-05' | 'fix(README): formatting in README.md for QueryEng... |
| hypercode-push\submodules\hyperharness\claude-code-templates | N/A | main | 'f1ceb095' | '2026-04-14' | 'Merge feature origin/claude-daniel/condescending-... |
| hypercode-push\submodules\hyperharness\code-cli | N/A | main | 'e530f12bd' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode-push\submodules\hyperharness\copilot-cli | N/A | main | '6315a6c' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode-push\submodules\hyperharness\crush | N/A | main | 'dacb4d62' | '2026-04-14' | 'Merge branch 'main' of https://github.com/charmbr... |
| hypercode-push\submodules\hyperharness\dolt | N/A | main | '45bcaaba2f' | '2026-04-14' | 'Merge branch 'main' of https://github.com/dolthub... |
| hypercode-push\submodules\hyperharness\factory-cli | N/A | main | '1b49af4' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode-push\submodules\hyperharness\gemini-cli | N/A | main | 'b345eaaae' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode-push\submodules\hyperharness\goose | N/A | main | 'fce9f8215' | '2026-04-14' | 'Merge feature origin/Roshansingh9/main into main' |
| hypercode-push\submodules\hyperharness\grok-cli | N/A | main | 'c49c187' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode-push\submodules\hyperharness\jules-extension | N/A | main | 'b55d68b' | '2026-04-14' | 'Merge feature origin/dependabot/npm_and_yarn/mcp-... |
| hypercode-push\submodules\hyperharness\kilocode | N/A | main | '2b1a91dd8' | '2026-04-14' | 'Merge branch 'main' of https://github.com/Kilo-Or... |
| hypercode-push\submodules\hyperharness\kimi-cli | N/A | main | 'ed383c9d' | '2026-04-14' | 'Merge feature origin/bigeagle/toolset-step into m... |
| hypercode-push\submodules\hyperharness\litellm | N/A | main | '37838abff2' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode-push\submodules\hyperharness\llamafile | N/A | main | '7cfcbb7' | '2026-04-13' | 'chore: save local progress before sync' |
| hypercode-push\submodules\hyperharness\llm-cli | N/A | main | 'b61c720' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode-push\submodules\hyperharness\mistral-vibe | N/A | main | 'e1a25ca' | '2026-04-14' | 'v2.7.5 (#589)' |
| hypercode-push\submodules\hyperharness\ollama | N/A | main | '4f2eb409' | '2026-04-14' | 'Merge branch 'main' of https://github.com/ollama/... |
| hypercode-push\submodules\hyperharness\open-interpreter | N/A | main | 'c243c213' | '2026-04-14' | 'Merge branch 'main' of https://github.com/OpenInt... |
| hypercode-push\submodules\hyperharness\opencode | N/A | dev | 'fceb09a5c' | '2026-04-14' | 'Merge feature origin/2.0 into main' |
| hypercode-push\submodules\hyperharness\pi-cli | N/A | main | '6b6f8667' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode-push\submodules\hyperharness\qwen-code-cli | N/A | clean-main | '4ba8d08' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode-push\submodules\hyperharness\rowboat | N/A | main | 'e32049f2' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode-push\submodules\hyperharness\smithery-cli | N/A | main | '7f7ddc2' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode\archive\submodules\litellm | N/A | main | '872ca89f0f' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode\archive\submodules\mcpproxy | N/A | main | 'cd33f66' | '2026-04-03' | 'chore: rename borg to hypercode' |
| hypercode\submodules\hyperharness\adrenaline | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\aider | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\amazon-q-developer-cli | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\auggie | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\azure-ai-cli | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\bito-cli | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\byterover-cli | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\claude-code | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\claude-code-templates | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\code-cli | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\copilot-cli | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\crush | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\dolt | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\factory-cli | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\gemini-cli | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\goose | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\grok-cli | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\jules-extension | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\kilocode | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\kimi-cli | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\litellm | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\llamafile | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\llm-cli | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\mistral-vibe | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\ollama | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\open-interpreter | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\opencode | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\pi-cli | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\qwen-code-cli | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\rowboat | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\smithery-cli | N/A |  |  |  |  |
| hypercode\submodules\prism-mcp\Brave-Gemini-Research-MCP-Server | N/A | main | '0418355' | '2025-04-13' | 'Update README.md' |
| hyperharness\llamafile\stable-diffusion.cpp\ggml | N/A | master | '1ffa6b11' | '2026-04-14' | 'Merge branch 'master' of https://github.com/ggml-... |
| hyperharness\llamafile\third_party\zipalign | N/A | main | '2ee1385' | '2025-11-28' | 'Test it works with BSD make' |
| mk64\tools\blender\fast64 | N/A | main | 'ce614e0' | '2026-04-11' | 'chore: save progress before update' |
| npp\bobui\submodules\juce | N/A | master | '3adf3d4f2b' | '2026-04-14' | 'Merge feature origin/develop into master' |
| npp\bobui\submodules\ultimatepp | N/A | master | '70657d292' | '2026-04-09' | 'Draw: In Win32, DrawImage with Color now using Ca... |
| npp\btk\external\bobui-reference | N/A | main | '51a2407a57' | '2026-04-14' | 'chore: save local progress before sync' |
| npp\btk\external\juce | N/A | master | 'ee0d1aa270' | '2026-04-14' | 'Merge feature origin/develop into master' |
| npp\btk\external\ultimatepp | N/A | master | '323be6810' | '2026-04-14' | 'Merge feature origin/QHD into master' |
| superai\llamafile\stable-diffusion.cpp\ggml | N/A | master | '906baf4c' | '2026-04-14' | 'Merge branch 'master' of https://github.com/ggml-... |
| superai\llamafile\third_party\zipalign | N/A | main | '2ee1385' | '2025-11-28' | 'Test it works with BSD make' |
| bg\bobsgameonlinejava\references\aseprite\laf | N/A | main | 'a33f1c5' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\more | N/A | master | '3da8ceb' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\libjxl\testdata | N/A | main | '73695d3' | '2025-05-13' | 'Update splines test to cover more than 1 group.' |
| bg\okgame\lib\plutosvg\plutovg | N/A | main | 'dabf47c' | '2026-01-14' | 'Refactor tiled texture blending to apply bilinear... |
| bg\okgame\lib\vbam-libretro\dependencies | N/A | master | 'cb28fa7' | '2025-11-05' | 'Make __declspec(uuid) MSVC-only for XAudio' |
| bobfilez\libs\OpenRV\src\pub | N/A | main | '44a8d2b' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\bobui\submodules\juce | N/A | master | '687504fa8a' | '2026-04-14' | 'Merge feature origin/develop into master' |
| bobfilez\libs\bobui\submodules\ultimatepp | N/A | master | 'd03c1cbea' | '2026-04-14' | 'Merge feature origin/X11S into master' |
| bobfilez\libs\btk\external\bobui-reference | N/A | main | '84e615e8c6' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\btk\external\juce | N/A | master | 'ca1c08a8f9' | '2026-04-14' | 'Merge feature origin/develop into master' |
| bobfilez\libs\btk\external\ultimatepp | N/A | master | 'f4a07fa16' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\pcre2\deps\sljit | N/A | master | 'd9902b1' | '2026-02-15' | 'config: prevent aarch64_be from being autodetecte... |
| bobfilez\libs\rapidjson\thirdparty\gtest | N/A | main | '4c400e2a' | '2026-04-14' | 'chore: save local progress before sync' |
| bobmani\itgmania\extern\mbedtls\framework | N/A | main | 'e7a59aeea' | '2026-04-14' | 'Merge feature origin/dev/gilles-peskine-arm/outco... |
| bobmani\itgmania\extern\mbedtls\tf-psa-crypto | N/A | HEAD | '7ab631c29' | '2026-04-13' | 'chore: save local progress before sync' |
| bobmani\ksm-v2\kshootmania\ThirdParty\CoTaskLib | N/A | master | 'cdaa8cf' | '2026-04-14' | 'chore: save local progress before sync' |
| bobmani\ksm-v2\kshootmania\ThirdParty\NocoUI | N/A | master | '23de5ff' | '2026-04-12' | 'Merge branch 'master' of https://github.com/m4sak... |
| bobtrader\submodules\page-05\fluidex__dingir-exchange\orchestra | N/A | master | 'd4077bf' | '2026-04-13' | 'chore: save local progress before sync' |
| bobtrax\lmms\plugins\CarlaBase\carla | N/A | main | 'c4a3972c7' | '2026-04-14' | 'chore: save local progress before sync' |
| bobtrax\lmms\plugins\FreeBoy\game-music-emu | N/A | HEAD | '785e554' | '2026-04-13' | 'chore: save local progress before sync' |
| bobtrax\lmms\plugins\MidiImport\portsmf | N/A | main | '2cd26cb' | '2026-02-08' | 'clang-tidy: bugprone-branch-clone (#13)' |
| bobtrax\lmms\plugins\OpulenZ\adplug | N/A | master | 'fd97989' | '2026-04-14' | 'chore: save local progress before sync' |
| bobtrax\lmms\plugins\Xpressive\exprtk | N/A | master | 'a94c950' | '2026-04-13' | 'chore: save local progress before sync' |
| bobtrax\lmms\plugins\ZynAddSubFx\zynaddsubfx | N/A | HEAD | '3088dbd8' | '2026-04-13' | 'chore: save local progress before sync' |
| bobtrax\lmms\src\3rdparty\jack2 | N/A | HEAD | '15fcdcab' | '2026-04-13' | 'Merge feature origin/extended-port-flags into mai... |
| bobtrax\lmms\src\3rdparty\qt5-x11embed | N/A | HEAD | 'bdd90b0' | '2026-04-13' | 'chore: save local progress before sync' |
| bobtrax\lmms\src\3rdparty\ringbuffer | N/A | master | '01cb53c' | '2026-04-12' | 'Merge feature origin/testbranch into master' |
| bobtrax\zrythm\doc\dev\doxygen-awesome-css | N/A | main | '232fb97' | '2026-04-12' | 'Merge feature origin/fix/list_in_tabs into main' |
| borg\data\bobbybookmarks\submodules\4regab-TaskSync | N/A |  |  |  |  |
| borg\data\bobbybookmarks\submodules\a2aproject-A2A | N/A |  |  |  |  |
| borg\data\bobbybookmarks\submodules\anthropics-skills | N/A |  |  |  |  |
| borg\data\bobbybookmarks\submodules\awesome-ai-apps | N/A |  |  |  |  |
| borg\data\bobbybookmarks\submodules\awesome-mcp-servers-appcypher | N/A |  |  |  |  |
| borg\data\bobbybookmarks\submodules\awesome-mcp-servers-punkpeye | N/A |  |  |  |  |
| borg\data\bobbybookmarks\submodules\awesome-mcp-servers-wong2 | N/A |  |  |  |  |
| borg\data\bobbybookmarks\submodules\bkircher-skills | N/A |  |  |  |  |
| borg\data\bobbybookmarks\submodules\dotfiles | N/A |  |  |  |  |
| borg\data\bobbybookmarks\submodules\openai-skills | N/A |  |  |  |  |
| borg\data\bobbybookmarks\submodules\robertpelloni-metamcp | 3.8.0 |  |  |  |  |
| borg\data\bobbybookmarks\submodules\stared-gemini-claude-skills | N/A |  |  |  |  |
| borg\data\bobbybookmarks\submodules\toolsdk-mcp-registry | N/A |  |  |  |  |
| borg\data\bobbybookmarks\submodules\ykdojo-claude-code-tips | N/A |  |  |  |  |
| borg\tmp\cloud-orchestrator-sync\apps\cloud-orchestrator | N/A | main | 'd154c3b' | '2026-04-14' | 'chore: save local progress before sync' |
| btk\external\bobui-reference\submodules\juce | N/A | master | '25887d9b93' | '2026-04-14' | 'Merge feature origin/develop into master' |
| btk\external\bobui-reference\submodules\ultimatepp | N/A | master | 'e6bd8a31f' | '2026-04-14' | 'Merge feature origin/X11S into master' |
| geany\subprojects\bobui\submodules\juce | N/A | master | 'cd07af40fc' | '2026-04-14' | 'Merge feature origin/develop into master' |
| geany\subprojects\bobui\submodules\ultimatepp | N/A | master | 'ad982a38f' | '2026-04-14' | 'Merge feature origin/X11S into master' |
| geany\subprojects\btk\external\bobui-reference | N/A | main | '3e938babe7' | '2026-04-14' | 'chore: save local progress before sync' |
| geany\subprojects\btk\external\juce | N/A | master | '84d40e57a5' | '2026-04-14' | 'Merge feature origin/develop into master' |
| geany\subprojects\btk\external\ultimatepp | N/A | master | '621556bcf' | '2026-04-14' | 'chore: save local progress before sync' |
| geany\variants\geany-bobgui\subprojects\bobgui | 5.0.0-ultrasonic |  |  |  |  |
| hypercode-push\submodules\hyperharness\llamafile\llama.cpp | N/A | master | '6a89a2372' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode-push\submodules\hyperharness\llamafile\stable-diffusion.cpp | N/A | HEAD | '02a15df' | '2026-04-13' | 'chore: save local progress before sync' |
| hypercode-push\submodules\hyperharness\llamafile\whisper.cpp | N/A | master | 'd26771ce' | '2026-04-14' | 'Merge feature origin/chess into master' |
| hypercode\archive\ts-legacy\apps\cloud-orchestrator | 3.6.0 |  |  |  |  |
| hypercode\archive\ts-legacy\apps\maestro | 0.15.7 |  |  |  |  |
| hypercode\archive\ts-legacy\packages\claude-mem | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\llamafile\llama.cpp | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\llamafile\stable-diffusion.cpp | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\llamafile\whisper.cpp | N/A |  |  |  |  |
| hyperharness\llamafile\stable-diffusion.cpp\thirdparty\libwebm | N/A | main | 'c0996bb' | '2026-04-13' | 'chore: save local progress before sync' |
| hyperharness\llamafile\stable-diffusion.cpp\thirdparty\libwebp | N/A | main | '3a7f2dcf' | '2026-04-14' | 'Merge branch 'main' of https://github.com/webmpro... |
| superai\llamafile\stable-diffusion.cpp\thirdparty\libwebm | N/A | main | 'a0a27ac' | '2026-04-13' | 'chore: save local progress before sync' |
| superai\llamafile\stable-diffusion.cpp\thirdparty\libwebp | N/A | main | '0d4861f5' | '2026-04-14' | 'Merge branch 'main' of https://github.com/webmpro... |
| bg\bobsgameonlinejava\libs\lz4-java\src\lz4 | N/A | dev | '06b46098' | '2026-04-14' | 'Merge feature origin/threadpool_pthread into main... |
| bg\bobsgameonlinejava\references\LibreSprite\src\flic | N/A | main | 'a25b736' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\LibreSprite\third_party\duktape | N/A | master | '42a4c01' | '2026-02-27' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\LibreSprite\third_party\simpleini | N/A | master | 'ec45fd7' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\PixiEditor\src\ColorPicker | N/A | master | 'a1449e8' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\PixiEditor\src\Drawie | N/A | main | '048ce05' | '2026-04-14' | 'Merge feature origin/rem-srgb-paintables into mai... |
| bg\bobsgameonlinejava\references\PixiEditor\src\PixiDocks | N/A | main | '83fc0a5' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\PixiEditor\src\PixiParser | N/A | master | 'e804e8a' | '2026-04-13' | 'Merge feature origin/replace-qoi-library into mas... |
| bg\bobsgameonlinejava\references\aseprite\laf\clip | N/A | main | '3b109e5' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\src\flic | N/A | main | '117114c' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\src\observable | N/A | main | '547af02' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\src\psd | N/A | main | '3f8688d' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\src\tga | N/A | main | 'd91dd76' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\src\undo | N/A | main | 'd2fddbb' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\third_party\IXWebSocket | N/A | master | 'a0a846c' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\third_party\TinyEXIF | N/A | master | '2284c13' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\third_party\benchmark | N/A | main | 'eec030d' | '2026-02-27' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\cityhash | N/A | master | 'e59a90b' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\third_party\cmark | N/A | master | '56db4b6' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\third_party\curl | N/A | master | 'eec196dab' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\third_party\fmt | N/A | master | '4e4ef292' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\third_party\freetype2 | N/A | master | '6b31d0f4a' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\third_party\giflib | N/A | master | '76d54b1' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\third_party\harfbuzz | N/A | main | '477cdd0da' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\third_party\json11 | N/A | master | 'b7fdc48' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\third_party\libarchive | N/A | master | '53f4ebcc' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\third_party\libpng | N/A | master | '8f059c911' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\third_party\libwebp | N/A | main | '16943e41' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\third_party\lua | N/A | master | '4de4d958' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\third_party\pixman | N/A | master | '9c69eb9' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\third_party\qoi | N/A | master | '2c30ad3' | '2026-02-27' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\simpleini | N/A | master | 'f393d63' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\third_party\tinyexpr | N/A | master | '792d86d' | '2026-04-12' | 'Merge feature origin/aseprite-ca50544 into master... |
| bg\bobsgameonlinejava\references\aseprite\third_party\tinyxml2 | N/A | master | 'd529294' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\aseprite\third_party\zlib | N/A | master | '8304143' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\grafx2\tests\pic-samples | N/A | pic-samples | 'ac35d4d' | '2026-02-27' | 'chore: save progress before update' |
| bg\okgame\lib\Maelstrom\external\SDL | N/A | main | '8f8aa9f80' | '2026-04-14' | 'Merge branch 'main' of https://github.com/libsdl-... |
| bg\okgame\lib\Maelstrom\external\SDL_net | N/A | main | '81eb296' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\Maelstrom\external\SteamworksSDK | N/A | main | '7094e89' | '2026-04-11' | 'Auto-sync: Protocol Update 2026-04-11' |
| bg\okgame\lib\Maelstrom\external\physfs | N/A | main | '99dc312' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_image\external\aom | N/A | main | '9047365a0' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_image\external\dav1d | N/A | master | 'fa39dd5d' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_image\external\jpeg | N/A | main | '6d5efb7' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_image\external\libavif | N/A | main | 'eebbc975' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_image\external\libjxl | N/A | main | '80de95a0' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_image\external\libpng | N/A | master | '2ed42dd86' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_image\external\libtiff | <<<<<<< HEAD
4.7.1
| bg\okgame\lib\SDL_image\external\libwebp | N/A | main | '4b3fe04c' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_image\external\zlib | N/A | master | 'fe3fab1' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_mixer\external\flac | N/A | master | 'eb40e8b4' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_mixer\external\libgme | N/A | master | '7f3c5ac' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_mixer\external\libxmp | N/A | master | 'a115adfa' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_mixer\external\mpg123 | N/A | main | '292472e' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_mixer\external\ogg | N/A | main | '9bcc8d7' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_mixer\external\opus | N/A | main | '9b448d9b' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_mixer\external\opusfile | N/A | main | 'afb965c' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_mixer\external\tremor | N/A | main | '55fab1e' | '2026-04-13' | 'Merge feature origin/v1.2.1-SDL into master' |
| bg\okgame\lib\SDL_mixer\external\vorbis | N/A | main | '2a7dcff' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_mixer\external\wavpack | N/A | master | '7ba247e' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_ttf\external\freetype | N/A | master | '6c0f809fc' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_ttf\external\harfbuzz | N/A | main | 'ef65edb41' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_ttf\external\plutosvg | N/A | HEAD | '5ed99f9' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_ttf\external\plutovg | N/A | HEAD | '048a6b8' | '2026-04-12' | 'Merge feature origin/v1.1.0-SDL into main' |
| bg\okgame\lib\boost\libs\accumulators | N/A | master | '1aae67f' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\algorithm | N/A | master | '996bd6e' | '2026-04-14' | 'Merge feature origin/svn-branches/cpp0x into mast... |
| bg\okgame\lib\boost\libs\align | N/A | master | '85f26d7' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\any | N/A | master | '1452793' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\array | N/A | master | '02056ba' | '2026-04-14' | 'Merge feature origin/svn-branches/proto/v3 into m... |
| bg\okgame\lib\boost\libs\asio | N/A | master | 'b3f0d4a3' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\assert | N/A | master | '0bbcea9' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\assign | N/A | master | '8f77141' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\atomic | N/A | master | '4e08347' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\beast | N/A | master | '15c13b3d' | '2026-04-14' | 'Merge branch 'master' of https://github.com/boost... |
| bg\okgame\lib\boost\libs\bimap | N/A | master | 'ebf849d' | '2026-04-13' | 'Merge feature origin/svn-branches/xpressive/neste... |
| bg\okgame\lib\boost\libs\bind | N/A | master | '7cdb2a2' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\bloom | N/A | master | 'd5cba47' | '2026-04-13' | 'Merge feature origin/feature/bulk-ops-optimizatio... |
| bg\okgame\lib\boost\libs\callable_traits | N/A | master | 'd4a8b1a' | '2026-04-14' | 'Merge feature origin/pr/cmakelists into master' |
| bg\okgame\lib\boost\libs\charconv | N/A | master | '58f4457' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\chrono | N/A | master | '809ea16' | '2026-04-14' | 'Merge feature origin/svn-branches/quickbook-filen... |
| bg\okgame\lib\boost\libs\circular_buffer | N/A | master | '8b234c4' | '2026-04-12' | 'Merge feature origin/svn-branches/maintenance/1_5... |
| bg\okgame\lib\boost\libs\cobalt | N/A | master | '65ee103' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\compat | N/A | master | 'f71e176' | '2026-03-23' | 'chore: save progress before update' |
| bg\okgame\lib\boost\libs\compute | N/A | master | '377027f1' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\concept_check | N/A | master | '0d3c94c' | '2026-03-23' | 'chore: save progress before update' |
| bg\okgame\lib\boost\libs\config | N/A | master | 'e7981f6e' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\container | N/A | master | '403a703' | '2026-04-11' | 'chore: save progress before update' |
| bg\okgame\lib\boost\libs\container_hash | N/A | master | '73beb59' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\context | N/A | master | 'bbebc14' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\contract | N/A | master | 'eee6244' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\conversion | N/A | master | '0d9fc61' | '2026-03-23' | 'chore: save progress before update' |
| bg\okgame\lib\boost\libs\convert | N/A | master | '349b2a9' | '2026-03-23' | 'chore: save progress before update' |
| bg\okgame\lib\boost\libs\core | N/A | master | '797a6b3' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\coroutine | N/A | master | 'ff93a76' | '2026-04-13' | 'Merge feature origin/svn-branches/modular-build i... |
| bg\okgame\lib\boost\libs\coroutine2 | N/A | master | '9c80cdd' | '2026-04-11' | 'Auto-update feature with latest main changes' |
| bg\okgame\lib\boost\libs\crc | N/A | master | '3a85cfe' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\date_time | N/A | master | '8f28a17' | '2026-04-13' | 'Merge feature origin/issue-67 into master' |
| bg\okgame\lib\boost\libs\decimal | N/A | master | 'e55a40aa' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\describe | N/A | master | '6d3adfc' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\detail | N/A | master | '27a86bd' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\dll | N/A | master | 'cf437fe' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\dynamic_bitset | N/A | master | '93adfd6' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\endian | N/A | master | '9b48ca3' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\exception | N/A | master | '84b2f89' | '2026-04-14' | 'Merge feature origin/gha into master' |
| bg\okgame\lib\boost\libs\fiber | N/A | master | 'd9ad835' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\filesystem | N/A | master | '40052b8' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\flyweight | N/A | master | '916d06f' | '2026-04-12' | 'Merge feature origin/svn-branches/units/autoprefi... |
| bg\okgame\lib\boost\libs\foreach | N/A | master | '746d53a' | '2026-04-14' | 'Merge feature origin/svn-branches/phoenix_v3 into... |
| bg\okgame\lib\boost\libs\format | N/A | master | '3e142a6' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\function | N/A | master | 'a207986' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\function_types | N/A | master | 'e40f672' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\functional | N/A | master | '355c581' | '2026-04-11' | 'Auto-update feature with latest main changes' |
| bg\okgame\lib\boost\libs\fusion | N/A | master | '6e1796ba' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\geometry | N/A | master | '6147257f9' | '2026-04-12' | 'Merge feature origin/joss_paper into master' |
| bg\okgame\lib\boost\libs\gil | N/A | master | '9052121ac' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\graph | N/A | master | '71010b6f' | '2026-04-14' | 'Merge feature origin/sandbox-branches/bhy/py3k in... |
| bg\okgame\lib\boost\libs\graph_parallel | N/A | master | 'e97e695' | '2026-04-13' | 'Merge feature origin/svn-tags/RC_1_34_0_freeze in... |
| bg\okgame\lib\boost\libs\hana | N/A | master | '9ee64e1eb' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\hash2 | N/A | master | '0bac6243' | '2026-04-11' | 'Global Sync: Merged features, updated submodules,... |
| bg\okgame\lib\boost\libs\headers | N/A | master | 'd12e70f' | '2026-04-11' | 'Auto-sync: Protocol Update 2026-04-11' |
| bg\okgame\lib\boost\libs\heap | N/A | master | '1b7a26a' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\histogram | N/A | master | '41c18ee0' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\hof | N/A | master | 'e5b0a7d' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\icl | N/A | master | 'da0dd54' | '2026-04-14' | 'Merge feature origin/svn-branches/quickbook-filen... |
| bg\okgame\lib\boost\libs\integer | N/A | master | '0f783ba' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\interprocess | N/A | master | '6a7dba7' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\intrusive | N/A | master | 'cef1704' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\io | N/A | master | 'daa5c90' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\iostreams | N/A | master | 'afc4ec7' | '2026-04-14' | 'Merge feature origin/sandbox-branches/straszheim/... |
| bg\okgame\lib\boost\libs\iterator | N/A | master | 'bf90351' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\json | N/A | master | '7f0b962' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\lambda | N/A | master | 'da23cdc' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\lambda2 | N/A | master | '4768bca' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\leaf | N/A | master | '2e12ca4' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\lexical_cast | N/A | master | 'd81a7f6' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\local_function | N/A | master | '0904507' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\locale | N/A | master | 'ee6e587' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\lockfree | N/A | master | 'efc7d99' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\log | N/A | master | '825176a' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\logic | N/A | master | '343e5e9' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\math | N/A | master | '4b7bd4459' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\metaparse | N/A | master | '915929b' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\move | N/A | master | '53007c8' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\mp11 | N/A | master | 'e54724a' | '2026-04-11' | 'Global Sync: Merged features, updated submodules,... |
| bg\okgame\lib\boost\libs\mpi | N/A | master | '429f6d5' | '2026-04-14' | 'Merge feature origin/feature/101-ibcast into mast... |
| bg\okgame\lib\boost\libs\mpl | N/A | master | '318663d' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\mqtt5 | N/A | master | 'ca39ba3' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\msm | N/A | master | '1e26146' | '2026-04-14' | 'Merge branch 'master' of https://github.com/boost... |
| bg\okgame\lib\boost\libs\multi_array | N/A | master | 'a30b781' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\multi_index | N/A | master | '0ce4708' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\multiprecision | N/A | master | '4041ea78' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\mysql | N/A | master | '6adc5129' | '2026-04-14' | 'Merge feature origin/feature/decimal-review into ... |
| bg\okgame\lib\boost\libs\nowide | N/A | master | 'd52e97e' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\openmethod | N/A | master | 'e9d8b52' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\optional | N/A | master | '5affb12' | '2026-04-14' | 'Merge feature origin/sandbox-branches/intrusive_f... |
| bg\okgame\lib\boost\libs\outcome | N/A | master | '5beae6c5' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\parameter | N/A | master | '13fcc1a' | '2026-04-14' | 'Merge feature origin/svn-branches/b2 into master' |
| bg\okgame\lib\boost\libs\parameter_python | N/A | master | '16d2081' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\parser | N/A | master | '47bd1df9' | '2026-04-11' | 'Global Sync: Merged features, updated submodules,... |
| bg\okgame\lib\boost\libs\pfr | N/A | master | 'b1b0608' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\phoenix | N/A | master | '3d09650' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\poly_collection | N/A | master | '96bb0fe' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\polygon | N/A | master | '7e0c6f8' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\pool | N/A | master | '5b66c3e' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\predef | N/A | master | '5bc2ad5' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\preprocessor | N/A | master | '61496a7' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\process | N/A | master | 'a1d42dc' | '2026-04-14' | 'Merge feature origin/freebsd into master' |
| bg\okgame\lib\boost\libs\program_options | N/A | master | '3794f7d' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\property_map | N/A | master | '95aa19f' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\property_map_parallel | N/A | master | '08d7d82' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\property_tree | N/A | master | 'e18792b' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\proto | N/A | master | 'bbfc2b2' | '2026-04-14' | 'Merge feature origin/svn-branches/units/autoprefi... |
| bg\okgame\lib\boost\libs\ptr_container | N/A | master | '456defb' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\python | N/A | master | 'fa234136' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\qvm | N/A | master | '44c3c9f' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\random | N/A | master | 'be67a08' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\range | N/A | master | 'b9d40f2' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\ratio | N/A | master | '068bcc4' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\rational | N/A | master | '13cad06' | '2026-04-14' | 'Merge feature origin/svn-branches/b2 into master' |
| bg\okgame\lib\boost\libs\redis | N/A | master | '1fb63e5' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\regex | N/A | master | '1ad1e35c' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\safe_numerics | N/A | master | 'a8773f0' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\scope | N/A | master | '019097e' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\scope_exit | N/A | master | 'f72e6bb' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\serialization | N/A | master | 'd8f318bc' | '2026-04-14' | 'Merge feature origin/svn-branches/filesystem3 int... |
| bg\okgame\lib\boost\libs\signals2 | N/A | master | 'e0c6da9' | '2026-04-14' | 'Merge feature origin/svn-branches/units/autoprefi... |
| bg\okgame\lib\boost\libs\smart_ptr | N/A | master | '26b3198' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\sort | N/A | master | '0013e7f' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\spirit | N/A | master | 'a9766fe60' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\stacktrace | N/A | master | '2001aac' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\statechart | N/A | master | '5b06bb1' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\static_assert | N/A | master | '7f53a39' | '2026-04-14' | 'Merge feature origin/svn-branches/serialization_n... |
| bg\okgame\lib\boost\libs\static_string | N/A | master | '3e7defc' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\stl_interfaces | N/A | master | '1cc4c24' | '2026-04-11' | 'Global Sync: Merged features, updated submodules,... |
| bg\okgame\lib\boost\libs\system | N/A | master | '534d534' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\test | N/A | master | 'cbfb9c0e' | '2026-04-14' | 'Merge feature origin/topic/GH-131-better-boost-te... |
| bg\okgame\lib\boost\libs\thread | N/A | master | '9fa9bbe6' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\throw_exception | N/A | master | '780cdb3' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\timer | N/A | master | '62350da' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\tokenizer | N/A | master | 'b1c27ae' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\tti | N/A | master | '66c731d' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\tuple | N/A | master | 'e205966' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\type_erasure | N/A | master | '2c6fe3d' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\type_index | N/A | master | 'a602890' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\type_traits | N/A | master | 'c5a76bf' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\typeof | N/A | master | 'c4d92ce' | '2026-04-14' | 'Merge feature origin/svn-branches/fix-links into ... |
| bg\okgame\lib\boost\libs\units | N/A | master | '841d8bf' | '2026-04-14' | 'Merge feature origin/svn-branches/maintenance/1_5... |
| bg\okgame\lib\boost\libs\unordered | N/A | master | '94115e1d' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\url | N/A | master | '41ec333' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\utility | N/A | master | 'cfc4688' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\uuid | N/A | master | '1f39dd4' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\variant | N/A | master | '148d8fd' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\variant2 | N/A | master | '913dd31' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\vmd | N/A | master | '0d5b636' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\wave | N/A | master | 'f907325' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\winapi | N/A | master | 'da2f7a6' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\xpressive | N/A | master | '3c9574f' | '2026-04-14' | 'Merge feature origin/svn-branches/b2 into master' |
| bg\okgame\lib\boost\libs\yap | N/A | master | '49a974b' | '2026-04-11' | 'Global Sync: Merged features, updated submodules,... |
| bg\okgame\lib\boost\tools\auto_index | N/A | master | '9a394a6' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\tools\bcp | N/A | master | '0f68958' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\tools\boost_install | N/A | master | 'f3fb613' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\tools\boostbook | N/A | master | 'e7ea7ed' | '2026-04-14' | 'Merge feature origin/svn-branches/bcbboost into m... |
| bg\okgame\lib\boost\tools\boostdep | N/A | master | 'f861e45' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\tools\boostlook | N/A | master | '5653983' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\tools\cmake | N/A | master | 'bfb5395' | '2026-04-11' | 'Global Sync: Merged features, updated submodules,... |
| bg\okgame\lib\boost\tools\docca | N/A | master | 'e0e03d6' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\tools\inspect | N/A | master | 'c54a611' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\tools\litre | N/A | master | 'f0bbba3' | '2026-04-12' | 'Merge feature origin/svn-branches/xpressive/neste... |
| bg\okgame\lib\boost\tools\quickbook | N/A | master | '0b81f54' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\cppcodec\test\catch | N/A | HEAD | '022f9394' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\freetype\subprojects\dlg | N/A | master | 'bd5b76c' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\libjxl\third_party\brotli | N/A | master | 'c2b24d0' | '2026-04-14' | 'Merge feature origin/test_889816903 into master' |
| bg\okgame\lib\libjxl\third_party\googletest | N/A | main | '5ce1596f' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\libjxl\third_party\highway | N/A | master | '41a30e1a' | '2026-04-14' | 'Merge branch 'master' of https://github.com/googl... |
| bg\okgame\lib\libjxl\third_party\lcms | N/A | master | 'fb48851' | '2026-04-09' | 'Merge pull request #552 from mm2/dependabot/githu... |
| bg\okgame\lib\libjxl\third_party\libjpeg-turbo | N/A | main | 'c8f5ea22' | '2026-04-14' | 'Merge branch 'main' of https://github.com/libjpeg... |
| bg\okgame\lib\libjxl\third_party\libpng | N/A | master | '1d1bf8169' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\libjxl\third_party\sjpeg | N/A | main | 'e274159' | '2026-04-13' | 'Merge feature origin/revert-136-sync-3 into main' |
| bg\okgame\lib\libjxl\third_party\skcms | N/A | main | 'd4be963' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\libjxl\third_party\zlib | N/A | master | 'f9dd600' | '2026-03-26' | 'Clean up comment formatting in minizip's zip.c an... |
| bg\okgame\lib\lz4-java\src\lz4 | N/A | dev | '7745d5ee' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\nanogui-sdl\ext\eigen | N/A | master | '1f05f51' | '2017-03-21' | 'Update to version 3.3.3' |
| bg\okgame\lib\nanogui\ext\eigen | N/A | master | '36b959627' | '2019-12-04' | 'Update README.md' |
| bg\okgame\lib\nanogui\ext\glfw | N/A | master | '0944d18b' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\nanogui\ext\nanovg | N/A | master | '0319c43' | '2025-09-07' | 'API to set the device pixel ratio' |
| bg\okgame\lib\nanogui\ext\pybind11 | N/A | master | '6fadcd4e' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\picodrive\cpu\cyclone | N/A | master | '3ac7cf1' | '2024-03-09' | 'optimization for MUL* cycle count' |
| bg\okgame\lib\picodrive\platform\libpicofe | N/A | master | 'dd11f2d' | '2025-09-04' | 'menu: unhardcode 2x mode' |
| bg\okgame\lib\projectm\vendor\projectm-eval | N/A | HEAD | 'da885dc' | '2026-02-01' | 'Bump version to 1.0.6' |
| bg\okgame\lib\snes9x\external\SPIRV-Cross | N/A | HEAD | '60c3e53b' | '2026-04-13' | 'Merge feature origin/pr-2159 into main' |
| bg\okgame\lib\snes9x\external\cubeb | N/A | master | 'd0a05fb' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\snes9x\external\glslang | N/A | main | '717cd5f0' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\snes9x\external\vulkan-headers | N/A | main | 'f4c0fb8' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\ai-file-sorter\app\include\external\llama.cpp | N/A | master | '09e636bb9' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\OpenTimelineIO\src\deps\Imath | N/A | main | 'bbe0887' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\OpenTimelineIO\src\deps\pybind11 | N/A | master | '0ca5ba54' | '2026-04-14' | 'Merge feature origin/henryiii-patch-1 into master... |
| bobfilez\libs\OpenTimelineIO\src\deps\rapidjson | N/A | master | 'b9cae67b' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\dokany\samples\dokan_memfs\spdlog | N/A | master | '36186f47' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\heif\srcs\extlibs\VVCSoftware_VTM | N/A | HEAD | '274e8fc77' | '2021-05-26' | 'update version to 13.0 and PDF of software manual... |
| bobmani\beatoraja\lr2oraja-endlessdream\core\dependencies\jbms-parser | N/A | master | 'cd980a4' | '2025-11-18' | 'Refactor to use primitive arrays' |
| bobmani\beatoraja\lr2oraja-endlessdream\core\dependencies\jbmstable-parser | N/A | master | '205a286' | '2023-12-02' | 'Improve performance of table decoding' |
| bobmani\itgmania\extern\mbedtls\tf-psa-crypto\framework | N/A | main | '672a7c284' | '2026-04-14' | 'Merge feature origin/dev/gilles-peskine-arm/outco... |
| bobtrax\lmms\plugins\LadspaEffect\calf\veal | N/A | ladspa | 'b319458d' | '2026-04-13' | 'chore: save local progress before sync' |
| bobtrax\lmms\plugins\LadspaEffect\cmt\cmt | N/A | main | 'b97bcff' | '2026-04-12' | 'Merge feature lmms into main' |
| bobtrax\lmms\plugins\LadspaEffect\swh\ladspa | N/A | master | '0f54d24' | '2024-05-24' | 'Applied patch from Oskar Wallgren via github.' |
| bobtrax\lmms\plugins\LadspaEffect\tap\tap-plugins | N/A | master | '8564022' | '2023-07-14' | 'Refactoring and cleanup' |
| bobtrax\lmms\plugins\Sid\resid\resid | N/A | master | '3bf8eff' | '2025-08-11' | 'fix for accidently introduced DC offset in 6581 f... |
| bobtrax\lmms\plugins\ZynAddSubFx\zynaddsubfx\instruments | N/A | master | 'e9f64a9' | '2025-12-10' | 'Add files via upload' |
| bobtrax\lmms\src\3rdparty\hiir\hiir | N/A | main | '4a9a1e6' | '2023-01-24' | 'Update README.md' |
| bobtrax\lmms\src\3rdparty\weakjack\weakjack | N/A | master | '6138960' | '2022-06-30' | 'Provide jack2 compatible implementation for jack1... |
| hypercode-push\submodules\hyperharness\llamafile\stable-diffusion.cpp\ggml | N/A | master | '51909cec' | '2026-04-14' | 'Merge branch 'master' of https://github.com/ggml-... |
| hypercode-push\submodules\hyperharness\llamafile\third_party\zipalign | N/A | main | '2ee1385' | '2025-11-28' | 'Test it works with BSD make' |
| hypercode\submodules\hyperharness\llamafile\stable-diffusion.cpp\ggml | N/A |  |  |  |  |
| hypercode\submodules\hyperharness\llamafile\third_party\zipalign | N/A |  |  |  |  |
| hyperharness\llamafile\stable-diffusion.cpp\examples\server\frontend | N/A | master | '740475a' | '2026-04-11' | 'first commit' |
| npp\btk\external\bobui-reference\submodules\juce | N/A | master | '8c635b9f8b' | '2026-04-14' | 'Merge feature origin/develop into master' |
| npp\btk\external\bobui-reference\submodules\ultimatepp | N/A | master | '370250f1b' | '2026-04-14' | 'Merge feature origin/X11S into master' |
| superai\llamafile\stable-diffusion.cpp\examples\server\frontend | N/A | master | '740475a' | '2026-04-11' | 'first commit' |
| bg\bobsgameonlinejava\references\aseprite\laf\third_party\googletest | N/A | main | 'b75798a0' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\grafx2\tools\8x8fonts\font8x8 | N/A | master | '15c22a3' | '2026-02-27' | 'chore: save progress before update' |
| bg\okgame\lib\SDL_image\external\libjxl\testdata | N/A | main | '73695d3' | '2025-05-13' | 'Update splines test to cover more than 1 group.' |
| bg\okgame\lib\SDL_ttf\external\plutosvg\plutovg | N/A | HEAD | '1cb2f36' | '2026-04-11' | 'Global Sync: Merged features, updated submodules,... |
| bg\okgame\lib\boost\libs\numeric\conversion | N/A | master | 'aa11707' | '2026-04-14' | 'Merge feature origin/svn-branches/filesystem3 int... |
| bg\okgame\lib\boost\libs\numeric\interval | N/A | master | 'd594dd1' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\numeric\odeint | N/A | master | '3847c4cf' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\libs\numeric\ublas | N/A | master | 'e6e6f1e3' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\boost\tools\docca\xslt-visualizer | N/A | master | 'e28b494' | '2021-11-09' | 'Handle relative input file paths with parents' |
| bg\okgame\lib\picodrive\pico\cd\libchdr | N/A | master | 'e08956b' | '2026-04-12' | 'chore: save local progress before sync' |
| bg\okgame\lib\picodrive\pico\sound\emu2413 | N/A | main | '813cff6' | '2024-10-07' | 'Merge pull request #13 from carmiker/main' |
| bg\okgame\lib\picodrive\platform\common\dr_libs | N/A | master | '08f2845' | '2026-04-13' | 'Merge branch 'master' of https://github.com/mackr... |
| bg\okgame\lib\snes9x\external\cubeb\googletest | N/A | main | '5a82cc1d' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\snes9x\win32\libpng\src | N/A | HEAD | 'b4301558b' | '2026-04-13' | 'chore: save local progress before sync' |
| bg\okgame\lib\snes9x\win32\zlib\src | N/A | master | 'f9dd600' | '2026-03-26' | 'Clean up comment formatting in minizip's zip.c an... |
| bobfilez\libs\OpenRV\src\lib\files\WFObj | N/A | main | 'ef17b92' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\btk\external\bobui-reference\submodules\juce | N/A | master | 'fe2ffcf7e7' | '2026-04-14' | 'Merge feature origin/develop into master' |
| bobfilez\libs\btk\external\bobui-reference\submodules\ultimatepp | N/A | master | '44e31c73e' | '2026-04-14' | 'chore: save local progress before sync' |
| bobtrax\lmms\src\3rdparty\qt5-x11embed\3rdparty\ECM | N/A | master | 'def261e0' | '2026-04-14' | 'chore: save local progress before sync' |
| geany\subprojects\bobgui\subprojects\glib\subprojects\gvdb | N/A |  |  |  |  |
| geany\subprojects\btk\external\bobui-reference\submodules\juce | N/A | master | 'ef9cd57483' | '2026-04-14' | 'Merge feature origin/develop into master' |
| geany\subprojects\btk\external\bobui-reference\submodules\ultimatepp | N/A | master | '0d7bb188e' | '2026-04-14' | 'chore: save local progress before sync' |
| hypercode-push\submodules\hyperharness\llamafile\stable-diffusion.cpp\thirdparty\libwebm | N/A | main | 'b4b14ec' | '2026-04-13' | 'chore: save local progress before sync' |
| hypercode-push\submodules\hyperharness\llamafile\stable-diffusion.cpp\thirdparty\libwebp | N/A | main | '613c9169' | '2026-04-14' | 'Merge branch 'main' of https://github.com/webmpro... |
| bg\bobsgameonlinejava\references\aseprite\third_party\freetype2\subprojects\dlg | N/A | master | '0994fbd' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\bobsgameonlinejava\references\retro-game-editor\app\internal-apps\js-sms\jsSMS | N/A | master | '58dc60b' | '2026-02-27' | 'chore: save progress before update' |
| bg\okgame\lib\SDL_image\external\libjxl\third_party\brotli | N/A | master | 'fea1ad8' | '2026-04-14' | 'Merge feature origin/dependabot/github_actions/ac... |
| bg\okgame\lib\SDL_image\external\libjxl\third_party\googletest | N/A | main | 'ec4355c6' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_image\external\libjxl\third_party\highway | N/A | master | '9be7a937' | '2026-04-14' | 'Merge feature origin/test_516796152 into master' |
| bg\okgame\lib\SDL_image\external\libjxl\third_party\lcms | N/A | master | '5f3cb0f' | '2026-04-11' | 'Global Sync: Merged features, updated submodules,... |
| bg\okgame\lib\SDL_image\external\libjxl\third_party\libjpeg-turbo | N/A | main | 'd2b663c4' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_image\external\libjxl\third_party\libpng | N/A | master | '76c5516ee' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_image\external\libjxl\third_party\sjpeg | N/A | main | '55ca698' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_image\external\libjxl\third_party\skcms | N/A | main | 'c92da2a' | '2026-04-12' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_image\external\libjxl\third_party\zlib | N/A | master | 'b4ddd15' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\SDL_ttf\external\freetype\subprojects\dlg | N/A | master | 'd3aca76' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\nanogui\ext\pybind11\tools\clang | N/A | master | '826db4f' | '2026-04-12' | 'chore: save local progress before sync' |
| bg\okgame\lib\snes9x\external\cubeb\cmake\sanitizers-cmake | N/A | master | 'bcb1fc6' | '2025-11-03' | 'Merge pull request #39 from purple-lazy/update-cm... |
| bg\okgame\lib\snes9x\external\cubeb\src\cubeb-coreaudio-rs | N/A | HEAD | '3bed4ae' | '2026-04-14' | 'chore: save local progress before sync' |
| bg\okgame\lib\snes9x\external\cubeb\src\cubeb-pulse-rs | N/A | HEAD | 'a173b36' | '2026-04-14' | 'chore: save local progress before sync' |
| bobfilez\libs\OpenTimelineIO\src\deps\rapidjson\thirdparty\gtest | N/A | main | 'e9e1614c' | '2026-04-14' | 'chore: save local progress before sync' |
| bobmani\itgmania\extern\mbedtls\tf-psa-crypto\drivers\pqcp\mldsa-native | N/A | main | '5772b4f' | '2026-01-19' | 'Merge pull request #2 from gilles-peskine-arm/mer... |
| bobtrax\lmms\plugins\CarlaBase\carla\source\native-plugins\external | N/A | master | '0ad6f5a' | '2026-04-12' | 'Merge feature origin/develop into master' |
| hypercode-push\submodules\hyperharness\llamafile\stable-diffusion.cpp\examples\server\frontend | N/A | master | '740475a' | '2026-04-11' | 'first commit' |
| geany\variants\geany-bobgui\subprojects\bobgui\subprojects\glib\subprojects\gvdb | N/A |  |  |  |  |
| bg\okgame\lib\picodrive\platform\common\dr_libs\tests\external\miniaudio | N/A | master | 'a513b522' | '2026-04-06' | 'Dreamcast: Increase lower bound period size from ... |
