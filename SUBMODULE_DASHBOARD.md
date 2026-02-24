# Submodule Dashboard & Project Structure
**Last Updated:** 2026-02-24 15:50:48

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
| .agent | N/A | main | 'c2caafe' | '2026-02-22' | 'Merge branch 'main' of https://github.com/sickn33... |
| Alti.Assistant | N/A | main | 'cbf85e39' | '2026-02-21' | 'Merge branch 'split_frontend'' |
| Alti.Code.Studio | 7.0.0 | main | 'f1acac0' | '2026-02-23' | 'chore: Sync submodules and resolve .gitmodules co... |
| Azure.Cybersecurity | N/A | main | 'e5693ca' | '2026-02-21' | 'chore: save progress before update' |
| Calling-AI-Agent-Backend | N/A | main | '4dbba40' | '2026-02-20' | 'chore: initial import of backend code from zip' |
| Chamber.Law | N/A | main | 'c4254a8' | '2026-02-24' | 'fix(deploy): restore Azure GitHub Actions workflo... |
| Merk.Mobile | N/A | main | '2aeb554' | '2026-02-21' | 'chore: save progress before update' |
| Root | 1.3.3 | main | 'b8e22cf91' | '2026-02-22' | 'feat(workspace): v1.3.3 - Bidirectional feature b... |
| Snaype | N/A | main | 'd269282' | '2026-02-20' | 'docs: add comprehensive platform documentation su... |
| Stone.Ledger | N/A | master | 'fb24b00' | '2026-02-21' | 'chore: save progress before update' |
| Tickerstone | N/A | master | 'f2f61aa' | '2026-02-21' | 'chore: save progress before update' |
| antigravity-autopilot | N/A | master | '9bbe840' | '2026-02-24' | 'antigravity: auto-save loop #10' |
| antigravity-jules-orchestration | N/A | main | '486de02' | '2026-02-21' | 'chore: save progress before update' |
| audit.layer | N/A | master | 'afc4d41' | '2026-02-24' | 'chore: save progress before update' |
| audit.layer_temp | N/A | main | 'bd50b47' | '2026-02-24' | 'Initial commit' |
| bg | N/A | master | '4876de47' | '2026-02-21' | 'chore: save progress before update' |
| bobcoin | N/A | main | '85bb9d7' | '2026-02-21' | 'Merge origin/feature/comprehensive-ui-spec-176711... |
| bobeditpro | N/A | master | 'd1c211df6' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez | N/A | main | 'a7dc6cad' | '2026-02-21' | 'chore: save progress before update' |
| bobium | N/A | main | '1301317' | '2026-02-21' | 'chore: save progress before update' |
| bobsaver | N/A | main | '4a2d15a' | '2026-02-21' | 'chore: save progress before update' |
| bobtorrent | 11.2.3 | master | '9306047' | '2026-02-24' | 'Merge origin/renovate_undici-7.x into master' |
| bobtrader | N/A | main | 'e85536b' | '2026-02-24' | 'Merge origin/comprehensive-ui-documentation-v2-10... |
| bobtrax | N/A | master | '01b101a' | '2026-02-21' | 'chore: save progress before update' |
| bobui | N/A | main | '2d0763bbeff' | '2026-02-24' | 'Merge origin/feature/omni-ui-framework-1800128421... |
| bobzilla | N/A | main | 'bd20dab' | '2026-02-21' | 'chore: save progress before update' |
| borg | 2.7.14 | main | '94a6f2b4' | '2026-02-24' | 'antigravity: auto-save loop #140' |
| claude-mem | N/A | main | '498c9fef' | '2026-02-24' | 'Merge origin/viewer-ui into main' |
| clear.ledger | 1.0.0 | main | '4848943' | '2026-02-21' | 'chore: save progress before update' |
| coin.project | N/A | master | '59715ce' | '2026-02-24' | 'chore: save progress before update' |
| cointrade | N/A | master | 'b2feb7d' | '2026-02-24' | 'chore: save progress before update' |
| fwber | 0.3.35 | main | 'b7c03c8dc' | '2026-02-24' | 'Merge origin/frontend-features-achievements-chatr... |
| jules-autopilot | N/A | main | '4fc3d88' | '2026-02-24' | 'chore: save progress before update' |
| mcp-superassistant | 0.7.1 | main | '3a99ced' | '2026-02-24' | 'Merge origin/feature/comprehensive-docs-and-ui-en... |
| mcpenetes | N/A | main | 'ffe9204' | '2026-02-21' | 'Merge remote-tracking branch 'origin/dependabot/g... |
| metamcp | 3.7.0 | main | '6e96542' | '2026-02-24' | 'Merge origin/feature/agent-memory-registry-891298... |
| mk64 | N/A | master | 'f87bf8837' | '2026-02-24' | 'chore: save progress before update' |
| opencode-autopilot | N/A | main | '71d79a3' | '2026-02-21' | 'chore: save progress before update' |
| qwen.project | N/A | main | '26f5c16' | '2026-02-21' | 'chore: save progress before update' |
| qwen.project.backend | N/A | main | '6842fbf' | '2026-02-21' | 'chore: save progress before update' |
| qwen.project.frontend | N/A | main | 'cdd6aab' | '2026-02-21' | 'chore: save progress before update' |
| raindropioapp | 1.0.4 | master | '3b9408ec' | '2026-02-24' | 'Merge remote-tracking branch 'upstream/master'' |
| redprints | 0.68.0 | main | 'f05b809' | '2026-02-24' | 'chore: save progress before update' |
| rental.home | N/A | master | '4de2013' | '2026-02-21' | 'chore: save progress before update' |
| sm64coopdx | N/A | main | 'e24c89bd7' | '2026-02-21' | 'Merge remote-tracking branch 'origin/mmorpg-ui-ov... |
| topaz-ffmpeg | N/A | topaz/develop | '295c219d2a' | '2026-02-21' | 'chore: save progress before update' |
| vault.bfsi | N/A | master | '823c454' | '2026-02-24' | 'chore: save progress before update' |
| Alti.Assistant\Alti.Assistant.Backend | N/A | main | '1e0f9a0' | '2026-02-21' | 'chore: save progress before update' |
| Alti.Assistant\Alti.Assistant.Frontend | N/A | main | '7bae366' | '2026-02-21' | 'chore: save progress before update' |
| Alti.Code.Studio\alti.code.studio.backend | N/A | HEAD | '2d45a2a' | '2026-02-23' | 'Merge branch 'main' of https://github.com/mnmball... |
| Alti.Code.Studio\alti.code.studio.frontend | N/A | HEAD | 'ed720d5' | '2026-02-23' | 'Merge branch 'main' of https://github.com/mnmball... |
| Alti.Code.Studio\background-agents | N/A | HEAD | '35a615d' | '2026-02-22' | 'fix: structurally isolate untrusted GitHub commen... |
| Chamber.Law\Chamber.Law.Backend | N/A | main | '472079d' | '2026-02-24' | 'fix(db): ensure isDeleted property exists on Mong... |
| Chamber.Law\Chamber.Law.Desktop | N/A | main | 'b2a1aa0' | '2026-02-23' | 'feat(desktop): Expose Electron IPC boundaries for... |
| Chamber.Law\Chamber.Law.Frontend | N/A | main | 'a30ecdb' | '2026-02-24' | 'feat(conflict): Phase 6.1.0 Conflict of Interest ... |
| Chamber.Law\Tabular_Review | N/A | main | 'a156898' | '2026-02-21' | 'chore: save progress before update' |
| Merk.Mobile\Merk.Mobile.Backend | N/A | main | 'e243d82' | '2026-02-21' | 'chore: save progress before update' |
| Merk.Mobile\Merk.Mobile.Frontend | N/A | main | 'd82189d' | '2026-02-21' | 'chore: save progress before update' |
| Merk.Mobile\merk.mobile.flutter | N/A | main | '6a53d9f' | '2026-02-21' | 'chore: save progress before update' |
| Merk.Mobile\merk.mobile.website | N/A | master | 'b9b3690' | '2026-02-21' | 'chore: save progress before update' |
| Tickerstone\Tickerstone.Backend | N/A | main | 'df90e8c' | '2026-02-21' | 'chore: save progress before update' |
| Tickerstone\Tickerstone.Frontend | N/A | main | '400032a' | '2026-02-21' | 'chore: save progress before update' |
| antigravity-autopilot\AUTO-ALL-AntiGravity | N/A | master | 'ba60d59' | '2026-02-18' | 'chore: cleanup unused legacy files, update docs t... |
| antigravity-autopilot\AntiBridge-Antigravity-remote | N/A | main | '67d7cec' | '2026-01-22' | 'Update README.md' |
| antigravity-autopilot\AntigravityMobile | N/A | master | '3ac39e3' | '2026-01-21' | 'new update' |
| antigravity-autopilot\Claude-Autopilot | N/A | main | 'eaeea24' | '2025-08-21' | 'chore: bump version to 0.1.6' |
| antigravity-autopilot\antigravity-auto-accept | N/A | master | 'd4f03bb' | '2025-12-19' | 'Update all repo URLs to point to public pesoszpes... |
| antigravity-autopilot\antigravity-multi-purpose-agent | N/A | main | '294268e' | '2026-02-02' | 'Updating README.md' |
| antigravity-autopilot\auto-accept-agent | N/A | master | 'e6bca34' | '2026-02-14' | 'correct pws script order' |
| antigravity-autopilot\copilot-auto-continue | N/A | main | 'e87a76b' | '2025-09-17' | 'Ignore "Continue" button during git rebase' |
| antigravity-autopilot\free-auto-accept-antigravity | N/A | main | '581dd93' | '2026-02-12' | 'fix(core): optimize poll interval, fix auto-ON st... |
| antigravity-autopilot\yoke-antigravity | N/A | master | '50e9869' | '2025-12-30' | 'fix: Resolve all 21 TypeScript errors - add missi... |
| audit.layer\audit.layer.backend | N/A | master | 'af0ec23' | '2026-02-24' | 'chore: update README â€” last updated 2026-02-24' |
| audit.layer_temp\audit.layer.frontend | N/A |  |  |  |  |
| bg\bobsgameonlinejava | N/A | main | 'c8f75ec' | '2026-02-21' | 'Merge origin/modernize-codebase-final-final into ... |
| bg\okgame | N/A | main | 'd09dbe6a4' | '2026-02-21' | 'Merge origin/refactor-memory-management-part3 int... |
| bobeditpro\bobcoin | N/A | main | 'aedfdd9' | '2026-02-12' | 'chore: save progress' |
| bobeditpro\muse_framework | N/A | main | '8385bd6e' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\VERT | N/A | main | 'a47f8d9' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\ai-file-sorter | N/A | main | '43ea9ea' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\vcpkg | N/A | master | 'fb87e2bb3f' | '2026-02-04' | '[expat] update to 2.7.4 (#49747)' |
| bobmani\Simply-Love-SM5 | N/A | itgmania-release | '324fe6f7' | '2026-02-21' | 'Merge origin/wip-profile-quick-switch into itgman... |
| bobmani\arrowvortex | v1.3.2 | release | '18126af' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\beatoraja | 0.9.2 | master | 'b430c23d' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\bobmania | 5.7.0-Unified-Alpha | master | '1e486c7f7c' | '2026-02-21' | 'Merge origin/x11_fullscreen into master' |
| bobmani\ddc | 0.2.1 | master | '0e52a59' | '2026-02-21' | 'Merge origin/web into master' |
| bobmani\ddc_onset | N/A | main | 'e9c5ee8' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\ffr-difficulty-model | N/A | master | '13227a6' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\hymnmania | N/A | master | '1c68c78' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\itgmania | N/A | release | 'b4decc982f' | '2026-02-21' | 'Merge origin/sync into release' |
| bobmani\ksm-v2 | 2.0.0-alpha7 | master | '2d133bf' | '2026-02-21' | 'Merge origin/cereal into master' |
| bobmani\leraine-studio | N/A | master | '7ffaf84' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\linthesia | 0.9.0 | main | '2a2646f' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\pianogame | N/A | master | 'bbaf5ac' | '2026-02-21' | 'Merge branch 'master' of https://github.com/rober... |
| bobsaver\BeatDrop | N/A | master | '0d79223' | '2026-02-21' | 'chore: save progress before update' |
| bobsaver\JWildfire | N/A | master | 'cd21197f' | '2026-02-21' | 'chore: save progress before update' |
| bobsaver\MilkDrop3 | N/A | main | 'c709409' | '2026-02-21' | 'chore: save progress before update' |
| bobsaver\apophysis-j | N/A | master | '31c0304' | '2026-02-21' | 'chore: save progress before update' |
| bobsaver\electricsheep | N/A | master | '2c7d84b' | '2026-02-21' | 'chore: save progress before update' |
| bobsaver\geiss | N/A | main | 'aad91e6' | '2026-02-21' | 'chore: save progress before update' |
| bobsaver\projectm | N/A | master | '1802c190e' | '2026-02-21' | 'chore: save progress before update' |
| bobtorrent\qbittorrent | N/A | master | '302c05095' | '2026-02-24' | 'Merge origin/v5_1_x into master' |
| borg\opencode-core | N/A |  |  |  |  |
| borg\openevolve | N/A | main | '41ff634' | '2026-02-02' | 'chore: update submodules and merge features' |
| borg\vibeship-spawner-skills | N/A | main | '70b2e10' | '2026-01-02' | 'Turbocharge error-handling skill to 2,905 lines' |
| clear.ledger\clear.ledger.backend | N/A | main | 'ca28e175' | '2026-02-21' | 'chore: save progress before update' |
| clear.ledger\clear.ledger.frontend | N/A | main | '117afee' | '2026-02-21' | 'chore: save progress before update' |
| coin.project\bitcoin | N/A | master | 'fdc804479d' | '2026-02-24' | 'Merge branch 'master' of https://github.com/bitco... |
| coin.project\bobcoin | N/A | main | '9e9d0321' | '2026-02-22' | 'Merge branch 'main' of https://github.com/robertp... |
| cointrade\cointrade.backend | N/A | main | '1ca0010' | '2026-02-21' | 'chore: save progress before update' |
| cointrade\cointrade.frontend | N/A | master | '358ee3d' | '2026-02-21' | 'chore: save progress before update' |
| jules-autopilot\jules-sdk-reference | N/A | main | '275f583' | '2026-02-21' | 'chore: save progress before update' |
| mk64\bobcoin | N/A | main | '68ac932' | '2026-02-21' | 'Merge branch 'main' of https://github.com/robertp... |
| mk64\doxygen-awesome-css | N/A | main | 'f65ce65' | '2026-02-21' | 'chore: save progress before update' |
| musicbrainz-soulseek-downloader\picard | N/A |  |  |  |  |
| redprints\redprints.backend | N/A | main | '9ebd9e3' | '2026-02-24' | 'feat(v0.85.0): phases 45-47 ar-vr drones blockcha... |
| redprints\redprints.frontend | N/A | main | 'ae4497a' | '2026-02-24' | 'chore: save progress before update' |
| rental.home\rental.home.admin-website | N/A | main | '8d92842' | '2026-02-21' | 'chore: save progress before update' |
| rental.home\rental.home.backend | N/A | main | '664092c' | '2026-02-21' | 'chore: save progress before update' |
| rental.home\rental.home.flutter | N/A | main | 'b064b4f' | '2026-02-21' | 'chore: save progress before update' |
| rental.home\rental.home.frontend | N/A | main | 'b99b6b3' | '2026-02-21' | 'chore: save progress before update' |
| sm64coopdx\bobcoin | N/A | main | '68ac932' | '2026-02-21' | 'Merge branch 'main' of https://github.com/robertp... |
| superbobbyball\MarbleBlast | N/A |  |  |  |  |
| superbobbyball\OpenMBU | N/A |  |  |  |  |
| superbobbyball\f-zerox | N/A |  |  |  |  |
| superbobbyball\neverball | 1.6.1-dev |  |  |  |  |
| vault.bfsi\vault.bfsi.backend | N/A | master | 'a2502fa' | '2026-02-24' | 'chore: save progress before update' |
| vault.bfsi\vault.bfsi.frontend | N/A | master | '84aa2f3' | '2026-02-24' | 'chore: save progress before update' |
| Alti.Assistant\external\CopilotKit | N/A | main | '945d2556f' | '2026-02-21' | 'Merge branch 'main' of https://github.com/Copilot... |
| Alti.Assistant\external\a2a | N/A | main | '0661bda' | '2026-02-21' | 'chore: save progress before update' |
| Alti.Assistant\external\agui | N/A | main | '654f0a7e' | '2026-02-21' | 'Merge branch 'main' of https://github.com/ag-ui-p... |
| Alti.Assistant\external\google-adk | N/A | main | '8a49c33' | '2026-02-21' | 'chore: save progress before update' |
| Alti.Code.Studio\submodules\12-factor-agents | N/A | HEAD | 'd20c728' | '2025-09-21' | 'Merge pull request #72 from kyu08/delete-closing-... |
| Alti.Code.Studio\submodules\fossflow | N/A | HEAD | '8f307cd' | '2026-02-20' | 'chore: Delete icon-list-generation-guide.md' |
| Alti.Code.Studio\submodules\langflow | N/A | main | 'f44e2b31a4' | '2026-02-23' | 'docs: azure default temperature (#11829)' |
| Alti.Code.Studio\submodules\next-devtools-mcp | N/A | main | '8840ce3' | '2026-02-11' | 'docs: add add-mcp install option (#122)' |
| Alti.Code.Studio\submodules\pentagi | N/A | master | '763cb17' | '2026-02-22' | 'fix: issue with user password handling and catchi... |
| bg\bobsgameonlinejava\bobcoin | N/A | main | '452a3e1' | '2026-02-21' | 'Merge remote feature branch' |
| bobcoin\research\forest | N/A | main | '84fabde' | '2026-02-02' | 'chore(deps): bump the patch-versions group with 3... |
| bobcoin\research\solana | N/A | master | 'e24c173' | '2026-01-13' | 'chore: auto-save uncommitted changes during massi... |
| bobfilez\libs\ADSFileSystem | N/A | master | '1902440' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\ADSIdentifier | N/A | master | 'e1783dd' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\ADSman | N/A | main | 'c9982e5' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\AlternateDataStreams | N/A | master | '185c5dc' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\BLAKE3 | N/A | master | 'e72bd7b' | '2026-02-21' | 'Merge branch 'master' of https://github.com/BLAKE... |
| bobfilez\libs\Bringing-Old-Photos-Back-to-Life | N/A | master | '1d72f63' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\C | N/A | master | 'a98902a5' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\DataStreamBrowser | N/A | master | 'da5f30c' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\Dependencies | N/A | main | '447a2ed' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\FFmpeg | N/A | master | '1a4f750473' | '2026-02-21' | 'Merge branch 'master' of https://github.com/FFmpe... |
| bobfilez\libs\ImageMagick | N/A | main | 'bff78a0ac' | '2026-02-21' | 'Merge branch 'main' of https://github.com/ImageMa... |
| bobfilez\libs\Imath | N/A | main | '42e4f06' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\MediaInfo | N/A | master | '0c80255d2' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\MediaInfoLib | N/A | master | 'abe4e76d3' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\OpenColorIO | N/A | main | '45970b8a' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\OpenCue | N/A | master | '5d5591dd' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\OpenImageIO | N/A | main | 'f1597473d' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\OpenRV | N/A | main | '53bab88' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\OpenTimelineIO | N/A | main | '59f9fcf' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\Powershell-ADS | N/A | master | '9b5f67e' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\RenStrm | N/A | master | 'deaa756' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\SharpADS | N/A | main | 'edb8264' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\ShazamAPI | N/A | main | 'c9fb8da' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\ShazamIO | N/A | master | '68ba520' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\SysmonForLinux | N/A | main | 'b68db9f' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\TinyEXIF | N/A | master | 'a38acba' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\Windows | N/A | main | 'cb56197' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\WizardsToolkit | N/A | main | 'd70190d' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\ads | N/A | master | 'e723675' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\argon2 | N/A | master | 'f24bd4c' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\audio-recognizer | N/A | master | 'cb6e093' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\audiocraft | N/A | main | 'bbf43c9' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\c-ares | N/A | master | '62f6024' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\cURL | N/A | master | '91eb21ee' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\ckmame | N/A | main | '8f01f31e' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\cyrus-sasl | N/A | master | 'd933c03' | '2022-06-11' | 'Disable deprecation warnings (C4996)' |
| bobfilez\libs\dirent | N/A | master | 'ccafcca' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\dokany | N/A | master | 'effe740' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\dragonffi | N/A | master | '9697040' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\dunst | N/A | master | '9bb1c50' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\enchant | N/A | master | '70afaf5' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\fast-lzma2 | N/A | master | '2237f44' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\freetype | N/A | master | '718a728' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\fribidi | N/A | master | '91f80cd' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\fstlib | N/A | develop | '652795f' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\fuse_xattrs | N/A | master | 'a8f2b44' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\gdk-pixbuf | N/A | main | '6c42955' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\getopt-win | N/A | getopt_glibc_2.42_port | '30137f3' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\getopt-win32 | N/A | original | '1faf10c' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\gettext | N/A | master | '45d8a34' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\glib | N/A | master | 'b080d29' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\hash-library | N/A | master | '5727748' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\hashcat | N/A | master | 'cc7e46c2d' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\hashingImage | N/A | master | '46fd04a' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\heif | N/A | master | '7f52c9f' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\httpd | N/A | trunk | 'ea615354fe' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\icu4c | N/A | master | 'bf58b7f6' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\image-hash | N/A | master | '9add412' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\image_info | N/A | master | '9d4072e' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\imagehash | N/A | master | '86c40e9' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\imageinfo | N/A | master | 'dcf3204' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\imap | N/A | master | 'b16eaeb' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\imghash-viewer | N/A | main | '1865dd4' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\jhead | N/A | master | '6c66fa8' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\json-c | N/A | master | '00c92f1' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libavif | N/A | master | '067d68c' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libbzip2 | N/A | master | '829e46a' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libevent | N/A | master | '464fbf52' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libexif | N/A | master | 'f85df15' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libffi | N/A | master | '3c3edce' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libgit2 | N/A | main | 'cbc1a4a0f' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libheif | N/A | master | 'da36d41a' | '2026-02-21' | 'Merge branch 'master' of https://github.com/struk... |
| bobfilez\libs\libiconv | N/A | master | '5c67dc6' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libimghash | N/A | master | '980fdca' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libjpeg | N/A | master | '8696ea6' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libjpeg-turbo | N/A | main | '95cbe0f5' | '2026-02-21' | 'Merge branch 'main' of https://github.com/libjpeg... |
| bobfilez\libs\libmcrypt | N/A | master | 'c34305c' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libpng | N/A | master | '35c67a4' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libsodium | N/A | master | '1ca92ee' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libssh2 | N/A | master | 'c39bec7' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libtidy | N/A | master | 'cd7e815' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libunistd | 1.3 | master | 'da8be76' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libvbucket | N/A | master | 'f1255f1' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libvips | N/A | master | '2c40ad6a2' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libvpx | N/A | master | '5e76714' | '2013-04-09' | 'vpx_version.h is also needed' |
| bobfilez\libs\libwebp | N/A | master | '8497e71' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libxml2 | 2.16.0 | master | 'ded22b3a' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libxmlplusplus | N/A | master | 'a3c3414' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libxpm | N/A | master | '8d857a4' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libxslt | N/A | master | 'c4597c3' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\libzip | N/A | main | 'e4102009' | '2026-02-21' | 'Merge branch 'main' of https://github.com/nih-at/... |
| bobfilez\libs\lmdb | N/A | master | 'd69b930' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\lsads | N/A | master | '0a453ca' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\lvgl | N/A | master | 'f6242798d' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\metastore | N/A | master | '7d258ae' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\mm_file | N/A | master | '9f20985' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\mpir | N/A | master | '82ad843' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\mpv | N/A | master | '33474110de' | '2026-02-21' | 'Merge branch 'master' of https://github.com/mpv-p... |
| bobfilez\libs\net-snmp | N/A | master | '630230c' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\nghttp2 | N/A | master | 'bbd1952' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\nihtest | N/A | main | '32a420e' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\nihtest-cpp | N/A | main | '9189ae9' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\oniguruma | N/A | master | 'c794d9b' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\openapv | N/A | main | '51958bb' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\opencv | N/A | 4.x | 'd324e13313' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\openexr | N/A | main | '6410dc02' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\openfx | N/A | main | 'eb83182' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\openh264 | N/A | master | '991ac631' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\openjpeg | N/A | master | '5fab5757' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\openldap | N/A | master | '1d73691' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\openssl | N/A | master | '8f20a107' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\pHash | N/A | main | '9a7dcda' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\pHash.c | N/A | main | 'bca0b96' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\perceptual-dct-hash | N/A | master | 'e220392' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\pngquant | N/A | main | '899db55' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\postgresql | N/A | master | '5e904d1e' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\pslib | N/A | main | '35bc45a' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\pthreads | N/A | main | '0d559b7' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\pxz | N/A | master | '36b9485' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\qdbm | N/A | master | 'dffa91c' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\radare2 | N/A | master | '6a66bb690f' | '2026-02-21' | 'Merge branch 'master' of https://github.com/radar... |
| bobfilez\libs\raylib | N/A | master | 'c088fd83' | '2026-02-21' | 'Merge branch 'master' of https://github.com/raysa... |
| bobfilez\libs\securecopy | N/A | master | '518e218' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\seek-tune | N/A | main | '4c35641' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\sqlite | 3.52.0 | master | '711f180ccf' | '2026-02-21' | 'Merge branch 'master' of https://github.com/sqlit... |
| bobfilez\libs\sqlite3 | N/A | master | '3aa2518' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\ssdeep | N/A | master | '083b2a1' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\sumatrapdf | N/A | master | '94a78490d' | '2026-02-21' | 'Merge branch 'master' of https://github.com/sumat... |
| bobfilez\libs\tinyphash | N/A | master | '72c2f5e' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\tinyxml2 | N/A | master | 'ee182c5' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\util-linux | N/A | master | '619825323' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\vlc | N/A | master | 'd9a2fd36f9' | '2026-02-21' | 'Merge branch 'master' of https://github.com/video... |
| bobfilez\libs\wineditline | N/A | master | '7d9b6f2' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\xattrlib | N/A | master | '67f9b5b' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\xattrs | N/A | master | 'e482350' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\xxHash | N/A | dev | 'f21c37a' | '2026-02-21' | 'Merge branch 'dev' of https://github.com/Cyan4973... |
| bobfilez\libs\ziptools | N/A | main | '0b64504' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\zlib | N/A | master | 'd6d8b5d' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\beatoraja\bobcoin | N/A | main | '772d501' | '2026-02-21' | 'Merge branch 'main' of https://github.com/robertp... |
| bobmani\itgmania\bobcoin | N/A | main | '4b716db' | '2026-02-21' | 'Merge branch 'main' of https://github.com/robertp... |
| bobmani\ksm-v2\ksmaxis | N/A | master | '243552a' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\ksm-v2\kson | N/A | master | '249c2fc' | '2026-02-16' | 'Fix Unicode file path issues in Windows environme... |
| bobmani\linthesia\pianogame | N/A | master | '1879e41' | '2026-02-21' | 'chore: save progress before update' |
| borg\agents\agent-sessions | N/A |  |  |  |  |
| borg\agents\humanlayer | N/A |  |  |  |  |
| borg\agents\maestro | N/A |  |  |  |  |
| borg\agents\open-agents | 0.5.1 |  |  |  |  |
| borg\agents\openchamber | N/A |  |  |  |  |
| borg\agents\opencode-agents | N/A |  |  |  |  |
| borg\agents\opencode-parallel-agents | N/A |  |  |  |  |
| borg\agents\rse-agents | N/A |  |  |  |  |
| borg\agents\software-agent-sdk | N/A |  |  |  |  |
| borg\agents\workty | N/A | main | '5900554' | '2026-01-06' | 'chore: update lockfile' |
| borg\auth\anthropic | N/A |  |  |  |  |
| borg\auth\copilot | N/A |  |  |  |  |
| borg\auth\gemini | N/A |  |  |  |  |
| borg\auth\openai-codex | N/A |  |  |  |  |
| borg\auth\opencode-antigravity-auth | N/A |  |  |  |  |
| borg\auth\opencode-google-antigravity-auth | N/A |  |  |  |  |
| borg\browser-use\algonius-browser | N/A |  |  |  |  |
| borg\browser-use\chrome-devtools-mcp | N/A |  |  |  |  |
| borg\browser-use\kapture | N/A |  |  |  |  |
| borg\browser-use\playwright | N/A |  |  |  |  |
| borg\browser-use\stagehand | N/A |  |  |  |  |
| borg\browsers\browser-tools-mcp | N/A | main | '0befce3' | '2025-03-26' | 'Update README.md' |
| borg\browsers\mcpo-2 | N/A | main | '91e8f94' | '2025-10-14' | 'Merge pull request #263 from open-webui/dev' |
| borg\cli-harnesses\CodeNomad | N/A | dev | '3deb72e' | '2026-02-02' | 'Merge branch 'main' into dev' |
| borg\cli-harnesses\GoogleGeminiRouter | N/A | master | 'bbd9b59' | '2025-08-11' | 'updated readme file' |
| borg\cli-harnesses\Lynkr | N/A | main | '616cc7d' | '2026-02-02' | 'Update README.md' |
| borg\cli-harnesses\aichat | N/A | main | '0493134' | '2026-01-29' | 'chore: update models.yaml' |
| borg\cli-harnesses\amp-examples-and-guides | N/A | main | '435ffc0' | '2025-10-17' | 'added jira to pr sdk agent' |
| borg\cli-harnesses\amped | N/A | main | 'e415572' | '2025-11-01' | 'ci: make release notes have working download link... |
| borg\cli-harnesses\awesome-amp-code | N/A | main | 'cf06730' | '2026-01-26' | 'docs: add founder attribution to README (#67)' |
| borg\cli-harnesses\awesome-copilot | N/A | main | '8da3194' | '2026-02-02' | 'Merge pull request #637 from github/experiment/gi... |
| borg\cli-harnesses\awesome-opencode | N/A | main | '4fadff1' | '2026-01-26' | 'docs: auto-regenerate README and registry data' |
| borg\cli-harnesses\cc-switch | N/A | main | 'f0e8ba1' | '2026-02-02' | 'feat: session manger (#867)' |
| borg\cli-harnesses\cc-switch-cli | N/A | main | '1716975' | '2026-02-02' | 'chore(release): v4.5.0' |
| borg\cli-harnesses\cc-switch-farion1231 | N/A | main | 'e349012' | '2026-02-09' | 'docs: add Right Code as sponsor across all README... |
| borg\cli-harnesses\ccproxy | N/A | main | '4d977b3' | '2026-02-01' | 'Update README.md' |
| borg\cli-harnesses\ccs | N/A | main | 'be63056' | '2026-02-01' | 'chore(release): 7.34.0 [skip ci]' |
| borg\cli-harnesses\ccs-kaitranntt | N/A | main | 'be63056' | '2026-02-01' | 'chore(release): 7.34.0 [skip ci]' |
| borg\cli-harnesses\claude-code-madapp | N/A | main | '550d836' | '2026-02-01' | 'fix(claudeup): v3.3.0 - use Bun in CI instead of ... |
| borg\cli-harnesses\claude-code-madappgang | N/A | main | 'bea99ea' | '2026-02-04' | 'docs: update CLAUDE.md for dev plugin v1.29.0' |
| borg\cli-harnesses\claude-code-mcp | N/A | main | '24dfd38' | '2025-05-17' | 'Clean up duplicate test-install directory structu... |
| borg\cli-harnesses\claude-code-openrouter | N/A | main | 'c1a9710' | '2025-11-30' | 'Merge pull request #3 from derek-larson14/fix-git... |
| borg\cli-harnesses\claude-code-router | N/A | main | 'c73fe0d' | '2026-01-10' | 'add posts' |
| borg\cli-harnesses\claude-hooks | N/A | main | '335a123' | '2026-01-18' | 'Merge pull request #1 from brumar/patch-1' |
| borg\cli-harnesses\claude-tools-mcp | N/A | main | '5615a91' | '2025-10-31' | 'Fix flaky list_shells tests' |
| borg\cli-harnesses\code | N/A | main | '51680828f' | '2026-02-02' | 'docs(changelog): update for v0.6.57 [skip ci]' |
| borg\cli-harnesses\code-assistant-manager | N/A | main | '51b49e9' | '2026-01-27' | 'Merge pull request #47 from zhujian0805/main' |
| borg\cli-harnesses\code-assistant-manager-Chat2AnyLLM | N/A | main | '51b49e9' | '2026-01-27' | 'Merge pull request #47 from zhujian0805/main' |
| borg\cli-harnesses\codebuff | N/A | main | 'a6da1f46f' | '2026-02-02' | 'Dedicated privacy page' |
| borg\cli-harnesses\codebuff-CodebuffAI | N/A | main | '8033e0b49' | '2026-02-10' | 'Bump version to 1.0.617' |
| borg\cli-harnesses\codemachine-cli | N/A | main | 'e55f110' | '2026-02-02' | 'docs: update README and move images to images fol... |
| borg\cli-harnesses\codex | N/A | main | '0b460eda3' | '2026-02-02' | 'chore: ignore synthetic messages (#10394)' |
| borg\cli-harnesses\crush | N/A | main | '019a9a18' | '2026-02-02' | 'v0.38.1' |
| borg\cli-harnesses\devin.cursorrules | N/A | master | '284b743' | '2025-05-26' | 'Emphasise Devin's consumption pricing (#137)' |
| borg\cli-harnesses\emdash | N/A | heads/main | '04480751' | '2026-01-16' | 'Merge pull request #617 from generalaction/emdash... |
| borg\cli-harnesses\emdash-generalaction | N/A | heads/main | '04480751' | '2026-01-16' | 'Merge pull request #617 from generalaction/emdash... |
| borg\cli-harnesses\factory | N/A | main | '5013789' | '2026-01-29' | 'docs: add Analytics API reference documentation (... |
| borg\cli-harnesses\gemini-cli-router | N/A | main | '5cbeed4' | '2025-07-21' | 'feat: add status display showing current port, mo... |
| borg\cli-harnesses\gemini-cli-router-zhifac | N/A | main | 'e7883de' | '2025-07-20' | 'Initial commit' |
| borg\cli-harnesses\gemini-openai-proxy | N/A | main | '1e54746' | '2025-10-07' | 'Update gemini library to supported sdk (#61)' |
| borg\cli-harnesses\gemini-openai-proxy-zuisong | N/A | main | '0e0e9ba' | '2025-12-30' | 'ðŸš¨ Commit Build Artifact from GitHub Actions' |
| borg\cli-harnesses\gemini-router | N/A | main | '1c38c5e' | '2025-09-20' | 'chore: gitignore' |
| borg\cli-harnesses\gemini-superclaude-mcp-server | N/A | main | '05f2d99' | '2025-09-07' | 'Update README.md' |
| borg\cli-harnesses\goose | N/A | main | '493ae789c' | '2026-02-02' | 'fix: make apps work in built copies of goose (#69... |
| borg\cli-harnesses\goose-block | N/A | main | '493ae789c' | '2026-02-02' | 'fix: make apps work in built copies of goose (#69... |
| borg\cli-harnesses\grok-cli | N/A | main | 'ad177ec' | '2025-11-27' | 'Support global custom instructions from ~/.grok/G... |
| borg\cli-harnesses\happy | N/A | main | '3ed8b121' | '2026-01-28' | 'ref: more docs' |
| borg\cli-harnesses\kimi-cli | N/A | main | '9e87547' | '2026-02-03' | 'chore: bump version to 1.6 (#862)' |
| borg\cli-harnesses\kimi-cli-MoonshotAI | N/A | main | 'ba75724' | '2026-02-10' | 'chore: bump version to 1.11.0 (#1083)' |
| borg\cli-harnesses\litellm | N/A |  |  |  |  |
| borg\cli-harnesses\llxprt-code | N/A | main | '88301db43' | '2026-02-02' | 'fix(ci): add quota-aware key selection to PR revi... |
| borg\cli-harnesses\multi-agent-orchestration | N/A | main | 'a21ea34' | '2025-08-12' | 'updated README.md' |
| borg\cli-harnesses\openai-gemini | N/A | main | '61a83bd' | '2025-12-22' | 'Update Vercel regions' |
| borg\cli-harnesses\opencode-gui | N/A | main | '0346d1c' | '2025-10-01' | 'Add: env.d.ts' |
| borg\cli-harnesses\opencode-web | N/A | main | '0ab3c85' | '2025-07-15' | 'delete old docs' |
| borg\cli-harnesses\qwen-code | N/A | main | 'bd900d36' | '2026-01-30' | 'Merge pull request #1663 from QwenLM/hotfix/v0.8.... |
| borg\cli-harnesses\schaltwerk | N/A | main | 'ab15b116' | '2026-02-02' | 'chore: bump version to 0.12.11' |
| borg\cli-harnesses\splitrail | N/A | main | '7a07e94' | '2026-01-30' | 'v3.3.1 (#109)' |
| borg\cli-harnesses\vercel-ai-proxy | N/A | main | '976cab0' | '2024-11-21' | 'feat: support xai' |
| borg\config\opencode-config-joelhooks | N/A |  |  |  |  |
| borg\config\opencode-manager | N/A |  |  |  |  |
| borg\config\opencode-template | N/A |  |  |  |  |
| borg\external\MetaMCP | 3.7.0 | main | '8215dbf' | '2026-02-22' | 'fix(backend): skip DB import migration in JSON-on... |
| borg\external\TheNoeTrevino-dotfiles | N/A | main | '8296b78' | '2026-02-02' | 'chore: update submodules and merge features' |
| borg\external\awesome-ai-apps | N/A | main | '35a1f54' | '2026-01-24' | 'Merge pull request #124 from axsaucedo/add-kaos-s... |
| borg\external\awesome-mcp-servers | N/A | main | 'c73c513' | '2026-02-01' | 'Merge pull request #1790 from jackparnell/main' |
| borg\external\awesome-mcp-servers-appcypher | N/A | main | '187929a' | '2025-09-04' | 'Added Vulert into README.md (#165)' |
| borg\external\awesome-mcp-servers-wong2 | N/A | main | 'a4316c7' | '2025-12-17' | 'Update readme' |
| borg\external\jules-autopilot | 0.8.6 | main | 'eaafda4' | '2026-02-19' | 'chore(jules): bump version to 0.8.6 and fix maint... |
| borg\external\mcp-servers-official | N/A | main | 'e6b0b0f' | '2026-01-27' | 'Merge pull request #3256 from modelcontextprotoco... |
| borg\external\opencode-autopilot | N/A | main | 'a9ea7a5' | '2026-01-23' | 'wip' |
| borg\external\toolsdk-mcp-registry | N/A | main | '760a4401' | '2026-01-27' | 'npm @toolsdk.ai/registry released - 1.0.154' |
| borg\frameworks\Kode-cli-2 | N/A | main | '214c12f' | '2026-01-24' | 'Merge pull request #167 from shareAI-lab/docs/add... |
| borg\mcp-dev-tools\agent-console | N/A | main | '0bbdaa7' | '2025-12-30' | 'Add duration display to sub-agent panel' |
| borg\mcp-dev-tools\inspector | N/A | main | 'a7cfa685' | '2026-02-02' | 'fix(client): tools pagination and reset (#1333)' |
| borg\mcp-dev-tools\mcp-gearbox | N/A | main | '36a7ce7' | '2026-01-27' | 'readme' |
| borg\mcp-dev-tools\mcp-gearbox-cli | N/A | main | '3f2c52b' | '2025-11-20' | 'Merge pull request #35 from rohitsoni007/dev' |
| borg\mcp-dev-tools\mcp-gearbox-js | N/A | main | 'f2d4798' | '2025-11-11' | 'chore: release v0.0.12 [skip ci]' |
| borg\mcp-dev-tools\mcp-router | N/A | main | 'a213cd3' | '2026-01-24' | 'feat(skills): add agent path management & improve... |
| borg\mcp-dev-tools\resterm | N/A | main | 'd44799d' | '2026-02-02' | 'docs: add resterm init' |
| borg\mcp-frameworks\Polymcp | N/A | main | '98694db' | '2026-01-27' | 'Bump version from 1.3.4 to 1.3.5' |
| borg\mcp-frameworks\Super-MCP | N/A | main | 'a417e5c' | '2026-01-28' | 'feat(resources): add MCP resources capability for... |
| borg\mcp-frameworks\lazy-mcp | N/A | main | 'a9928c8' | '2025-10-15' | 'Merge workflow fix for selective package publishi... |
| borg\mcp-frameworks\mcp-use | N/A | main | '59030e97' | '2026-02-02' | 'chore(release): update changelog for v0.18.2 and ... |
| borg\mcp-hubs\awesome-ai-apps | N/A | main | '35a1f54' | '2026-01-24' | 'Merge pull request #124 from axsaucedo/add-kaos-s... |
| borg\mcp-hubs\awesome-ai-apps-Arindam200 | N/A | main | '955655e' | '2026-02-07' | 'Merge pull request #122 from kantorcodes/add-agen... |
| borg\mcp-hubs\awesome-mcp-servers | N/A | main | '187929a' | '2025-09-04' | 'Added Vulert into README.md (#165)' |
| borg\mcp-hubs\awesome-mcp-servers-appcypher | N/A | main | '187929a' | '2025-09-04' | 'Added Vulert into README.md (#165)' |
| borg\mcp-hubs\awesome-mcp-servers-punkpeye | N/A | main | 'c73c513' | '2026-02-01' | 'Merge pull request #1790 from jackparnell/main' |
| borg\mcp-hubs\awesome-mcp-servers-wong2 | N/A | main | 'a4316c7' | '2025-12-17' | 'Update readme' |
| borg\mcp-hubs\mcphub | N/A | main | 'd3e7e7c' | '2026-01-31' | 'feat: add TDD Bug Resolution Agent for structured... |
| borg\mcp-hubs\metamcp | 3.1.0 | main | '80344bb' | '2025-12-27' | 'Add mcp-shark as submodule in two locations' |
| borg\mcp-hubs\pluggedin-mcp | N/A | main | '1e23c62' | '2026-01-07' | '1.12.5' |
| borg\mcp-hubs\toolsdk-mcp-registry | N/A | main | '760a4401' | '2026-01-27' | 'npm @toolsdk.ai/registry released - 1.0.154' |
| borg\mcp-hubs\toolsdk-mcp-registry-toolsdk-ai | N/A | main | '760a4401' | '2026-01-27' | 'npm @toolsdk.ai/registry released - 1.0.154' |
| borg\mcp-routers\agent-mcp-gateway | N/A | main | 'a1d664a' | '2025-12-02' | 'Fix graceful shutdown of downstream MCP servers' |
| borg\mcp-routers\mcp-proxy | N/A | master | 'd7b7c14' | '2026-01-26' | 'docs: update README to use lowercase module paths... |
| borg\mcp-routers\mcpproxy | N/A | main | 'd43b27f' | '2025-07-22' | 'Fix Tool Indexing, Persistence, and Retrieval Iss... |
| borg\mcp-routers\mcpproxy-go | N/A | main | 'fa9ecf1' | '2026-02-02' | 'docs: update demo video link in README' |
| borg\mcp-routers\meta-mcp-proxy | N/A | main | '6c10f1b' | '2025-05-13' | 'Update package' |
| borg\mcp-routers\microsoft-mcp-gateway | N/A | main | '5dbe5d6' | '2026-01-15' | 'Bump fastmcp from 2.13.0 to 2.14.0 in /sample-ser... |
| borg\mcp-routers\microsoft-mcp-gateway-2 | N/A | main | '5dbe5d6' | '2026-01-15' | 'Bump fastmcp from 2.13.0 to 2.14.0 in /sample-ser... |
| borg\mcp-routers\ncp | N/A | main | '290845e' | '2026-01-17' | 'Merge pull request #14 from portel-dev/claude/val... |
| borg\mcp-tool-rag\lootbox | N/A | main | '0e8fc1b' | '2025-12-06' | 'Revise promo link and project description' |
| borg\mcp-tool-rag\mcp-funnel | N/A | develop | '12d44ef' | '2025-11-24' | 'release: v0.0.8' |
| borg\memory\Claude-Matrix | N/A | main | '5da800c' | '2026-01-29' | 'chore: sync versions to 2.2.1' |
| borg\memory\mcp-obsidian-notes | N/A | master | 'f189a2a' | '2026-01-31' | 'cli' |
| borg\memory\mcp-obsidian-notes-2 | N/A | master | 'f189a2a' | '2026-01-31' | 'cli' |
| borg\memory\memora | N/A | main | 'eae45c0' | '2026-01-31' | 'Fix cloud graph broadcast blocked by Cloudflare b... |
| borg\misc\Andrew6rant | N/A | main | 'e059bd7' | '2025-03-03' | 'Updated README' |
| borg\misc\MZaFaRM | N/A | main | '4e0c045' | '2026-02-02' | '[BOT] auto update README - 2026-02-02' |
| borg\misc\awesome-opencode | N/A |  |  |  |  |
| borg\misc\bilgecan | N/A | main | '31ccb1d' | '2025-12-23' | 'hide ai task list during edit mode' |
| borg\misc\claude-limitline | N/A | main | 'af0855d' | '2026-01-01' | 'Merge pull request #11 from tylergraydev/fix/maco... |
| borg\misc\inframind | N/A | main | '64854d0' | '2025-12-15' | 'added the modal test script' |
| borg\misc\ocmonitor-share | N/A |  |  |  |  |
| borg\misc\oh-my-opencode | N/A |  |  |  |  |
| borg\misc\openapi-ts | N/A |  |  |  |  |
| borg\misc\opencode-pty | N/A |  |  |  |  |
| borg\misc\opencode-vibe | N/A |  |  |  |  |
| borg\misc\opencode-wrapped | N/A |  |  |  |  |
| borg\misc\tether-chat | N/A | main | '4553b09' | '2026-01-28' | 'Made the checkbox 'extended context enabled' pers... |
| borg\misc\tokscale | N/A |  |  |  |  |
| borg\multi-agent\1d3eeb46ddfda5257c08744972e0fc4c | N/A | main | 'e5bc09b' | '2025-12-16' | '' |
| borg\multi-agent\A2A | N/A | main | '6292104' | '2026-01-29' | 'fix(spec): Added clarification on timestamps in H... |
| borg\multi-agent\A2A-a2aproject | N/A | main | '6292104' | '2026-01-29' | 'fix(spec): Added clarification on timestamps in H... |
| borg\multi-agent\CopilotKit | N/A | main | 'fd9935047' | '2026-02-02' | 'Update asset link in README.md' |
| borg\multi-agent\OpenHands | N/A | main | 'd6c11fe51' | '2026-02-02' | 'fix selected repo disappearing in pen repository ... |
| borg\multi-agent\Self-Learning-Agents | N/A | main | 'ca6c83a' | '2025-06-28' | 'Merge pull request #2 from omdivyatej/c' |
| borg\multi-agent\TaskSync | N/A | main | 'b6bacf8' | '2026-01-06' | 'update CHANGELOG' |
| borg\multi-agent\TaskSync-4regab | N/A | main | 'b6bacf8' | '2026-01-06' | 'update CHANGELOG' |
| borg\multi-agent\a2a-main | N/A | main | '6292104' | '2026-01-29' | 'fix(spec): Added clarification on timestamps in H... |
| borg\multi-agent\a2a-ui | N/A | main | '04de7f1' | '2025-12-04' | 'Updated default URL in `AddAgentModal` to point t... |
| borg\multi-agent\ag-ui | N/A | main | '6bd15ad8' | '2026-02-02' | 'chore: release mastra sdk v1 (#1042)' |
| borg\multi-agent\agentdepot-agents | N/A | main | '063606c' | '2025-12-17' | 'chore: removed unused verified property and valid... |
| borg\multi-agent\agentdepot-agents-2 | N/A | main | '063606c' | '2025-12-17' | 'chore: removed unused verified property and valid... |
| borg\multi-agent\agentic-playground | N/A | main | 'a99a84f' | '2025-07-26' | 'Update README.md' |
| borg\multi-agent\agentic-ray | N/A | main | '67fbcde' | '2026-01-30' | 'fix: update URLs to superserve.ai and use light l... |
| borg\multi-agent\agentic-ray-rayai-labs | N/A | main | '7b14304' | '2026-02-05' | 'Documentation edits made through Mintlify web edi... |
| borg\multi-agent\codev | N/A | main | '959480a' | '2026-02-02' | '[Spec 0087] review: porch-timeout-termination-ret... |
| borg\multi-agent\langgraph | N/A | main | '82f9c09b' | '2026-01-31' | 'chore(deps-dev): bump ruff from 0.14.7 to 0.14.11... |
| borg\multi-agent\metamcp-robertpelloni | 3.2.18 | main | 'c7ed2d8' | '2026-02-02' | 'chore: update submodules and merge features' |
| borg\multi-agent\opus-agents | N/A | main | '5652e61' | '2026-01-18' | 'local release steps' |
| borg\multi-agent\priyan-coder-multi-agent | N/A | main | 'a21ea34' | '2025-08-12' | 'updated README.md' |
| borg\multi-agent\pydantic-deepagents-2 | N/A | main | '749b0d9' | '2026-01-23' | 'Merge pull request #23 from vstorm-co/0.2.14' |
| borg\multi-agent\tasksync-mcp | N/A | main | '7a5d1c9' | '2026-01-25' | 'Update readme' |
| borg\plugins\opencode-dynamic-context-pruning | N/A |  |  |  |  |
| borg\plugins\opencode-notifier | N/A |  |  |  |  |
| borg\plugins\opencode-shell-strategy | N/A |  |  |  |  |
| borg\plugins\opencode-wakatime | N/A |  |  |  |  |
| borg\references\awesome-mcp-servers | N/A | main | 'c73c513' | '2026-02-01' | 'Merge pull request #1790 from jackparnell/main' |
| borg\research\MCP-Zero | N/A | master | 'fd666c4' | '2025-07-02' | '[fix] update filename' |
| borg\research\OpenCoder-llm | N/A | main | '6131c47' | '2024-12-09' | 'update README.md: add opc_data_filtering into the... |
| borg\skills\anthropics-skills | N/A | main | '69c0b1a' | '2025-12-20' | 'Add link to Agent Skills specification website (#... |
| borg\skills\bkircher-skills | N/A | main | '9fe323a' | '2026-01-28' | 'unit-testing skill: refine a bit' |
| borg\skills\claude-code-tips | N/A | main | '7d3b087' | '2026-02-01' | 'Add note about picking your own version' |
| borg\skills\gemini-claude-skills | N/A | main | '0a31cfe' | '2026-01-14' | 'Add image input support to Nano Banana Pro skill' |
| borg\skills\skills-openai | N/A | main | 'db358da' | '2026-02-02' | 'Update openai.yaml (#86)' |
| borg\skills\ykdojo-claude-code-tips | N/A | main | '7d3b087' | '2026-02-01' | 'Add note about picking your own version' |
| borg\submodules\Agent-MCP | N/A | main | '13d98b2c' | '2025-10-09' | 'fix: Resolve SSE connection TypeError in Python A... |
| borg\submodules\Auditor | N/A | main | 'b4948ab8' | '2026-01-23' | 'Sherlocked twice... lol... Watch this pivot.' |
| borg\submodules\CLIProxyAPI | N/A | main | '250f212' | '2026-02-03' | 'fix(executor): handle "global" location in AI pla... |
| borg\submodules\PowerTrader_AI | N/A | main | '7220b40' | '2026-01-18' | 'Update README with structured logging system' |
| borg\submodules\Puzld.ai | N/A | main | 'ccbf0ea' | '2026-01-01' | 'refactor: simplify MCP serve command' |
| borg\submodules\Unified-MCP-Tool-Graph | N/A | main | 'c8a51dd' | '2025-11-21' | 'Merge pull request #50 from pratikjadhav2726/dev' |
| borg\submodules\Windows-MCP | N/A | main | 'c4cf8f9' | '2026-02-02' | 'Merge pull request #74 from yakub268/fix/stdout-c... |
| borg\submodules\agent-client-protocol | N/A | main | '2f15228' | '2026-02-02' | 'chore(deps): bump the minor group with 24 updates... |
| borg\submodules\agentmux | N/A | main | 'cd4de797' | '2026-02-01' | 'Merge feat: role-skill-chat enhancements with cod... |
| borg\submodules\ai-that-works | N/A | main | '7c92232' | '2026-02-02' | 'no vibes allowed' |
| borg\submodules\aichat | N/A | main | '0493134' | '2026-01-29' | 'chore: update models.yaml' |
| borg\submodules\browser-use | N/A | main | '6abac049' | '2026-02-01' | 'added extraction schema (#4005)' |
| borg\submodules\claude-code | N/A | main | 'f298d94' | '2026-01-31' | 'chore: Update CHANGELOG.md' |
| borg\submodules\claude-squad | N/A | main | '9d7ca2d' | '2025-12-24' | 'chore: bump version' |
| borg\submodules\claudex | N/A | main | '317d81b' | '2026-02-02' | 'Merge pull request #157 from Mng-dev-ai/codex/fix... |
| borg\submodules\code-conductor | 0.1.3 | main | '4a7aa0c' | '2026-02-02' | 'Merge branch 'main' of https://github.com/ryanmac... |
| borg\submodules\copilot-cli | N/A | main | '1bc2c29' | '2026-01-30' | 'Update changelog.md for version 0.0.400' |
| borg\submodules\emdash | N/A | heads/main | '8ce8228c' | '2025-12-10' | 'Merge pull request #448 from generalaction/fix-st... |
| borg\submodules\gemini-bridge | N/A | main | 'e139cf5' | '2025-08-17' | 'fix(debug): replace bc with awk for portable time... |
| borg\submodules\jules-agent-sdk-python | N/A | main | '51685d6' | '2025-10-04' | 'chore: update version to 0.1.1 and remove setup.p... |
| borg\submodules\jules-app | 0.7.0 | main | '5799a35' | '2026-02-02' | 'chore: save local progress before sync' |
| borg\submodules\mcp-manager | N/A | main | '66b4d03' | '2025-03-28' | 'docs: Better download link' |
| borg\submodules\mcp-reticle | N/A | main | '37b1517' | '2026-01-06' | 'Update README with new design, logo, and wiki lin... |
| borg\submodules\mcp-shark | N/A | main | '5c212d4' | '2026-01-25' | 'chore: update package version' |
| borg\submodules\mcpc | N/A | main | 'd2d28bd' | '2026-01-27' | 'Updated package.json URLs' |
| borg\submodules\mcpenetes | N/A | main | 'f0fd60e' | '2025-12-28' | 'chore: update dependencies' |
| borg\submodules\opencode-autopilot | N/A | main | 'a9ea7a5' | '2026-01-23' | 'wip' |
| borg\submodules\pctx | N/A | main | '4b413be' | '2026-01-29' | 'remove allowed hosts tests (fetch no longer avail... |
| borg\submodules\plandex | N/A | main | 'e2d77207' | '2025-10-03' | 'link to cloud wind down post' |
| borg\submodules\quotio | N/A | master | 'fcfdecd' | '2026-01-30' | 'chore: bump version to 0.7.10 [skip ci]' |
| borg\submodules\reag | N/A | main | 'de230c7' | '2025-02-12' | 'bump version' |
| borg\submodules\software-agent-sdk | N/A | main | 'bc7ea211' | '2026-02-02' | 'fix: several issues related to scalability (#1619... |
| borg\submodules\vibe-kanban | N/A | main | '5929647a' | '2026-02-02' | 'Cargo lock bump (#2493)' |
| borg\temp\MetaMCP | 3.6.3 | main | '076abce' | '2026-02-16' | 'chore: save progress' |
| borg\testing\agentic-qe | N/A | main | 'e7145be2' | '2026-02-02' | 'feat(v3.4.3): add --upgrade flag and fix skills R... |
| borg\tmp\jules-autopilot | 0.7.1 | main | '280accd' | '2026-02-02' | 'chore: save local progress before sync' |
| borg\tools\OpenCodeRunner | N/A |  |  |  |  |
| borg\tools\opencode_tools | N/A |  |  |  |  |
| cointrade\references\a2a-protocol | N/A | main | 'e8875db' | '2026-02-24' | 'Merge branch 'main' of https://github.com/a2aproj... |
| cointrade\references\a2ui | N/A | main | 'd0c191d' | '2026-02-24' | 'Merge branch 'main' of https://github.com/google/... |
| cointrade\references\adk-samples | N/A | main | '3b76da4' | '2026-02-21' | 'chore: save progress before update' |
| cointrade\references\agent-ui | N/A | main | '17ae19c' | '2026-02-21' | 'chore: save progress before update' |
| cointrade\references\copilotkit | N/A | main | '5bfed6856' | '2026-02-24' | 'Merge branch 'main' of https://github.com/Copilot... |
| jules-autopilot\external\antigravity-jules-orchestration | N/A | main | 'b24dddb' | '2026-02-21' | 'chore: save progress before update' |
| jules-autopilot\external\gemini-cli-jules | N/A | main | 'c6481d8' | '2026-02-21' | 'chore: save progress before update' |
| jules-autopilot\external\google-jules-mcp | N/A | main | '902f23a' | '2026-02-21' | 'chore: save progress before update' |
| jules-autopilot\external\jules-action | N/A | main | '918b756' | '2026-02-21' | 'chore: save progress before update' |
| jules-autopilot\external\jules-awesome-list | N/A | main | '074c7f8' | '2026-02-21' | 'chore: save progress before update' |
| jules-autopilot\external\jules-mcp-server | N/A | main | '5d29c1a' | '2026-02-21' | 'chore: save progress before update' |
| jules-autopilot\external\jules-system-prompt | N/A | add-details-md | 'c5ea3e9' | '2026-02-21' | 'chore: save progress before update' |
| jules-autopilot\external\jules-task-queue | N/A | main | 'aa34fb3' | '2026-02-21' | 'chore: save progress before update' |
| jules-autopilot\external\jules_mcp | N/A | main | '21ddac5' | '2026-02-21' | 'chore: save progress before update' |
| metamcp\submodules\cointrade | N/A | master | '71fa6b3' | '2026-02-18' | 'chore: merge submodules' |
| metamcp\submodules\mcp-directories | N/A |  |  |  |  |
| mk64\tools\asm-differ | N/A | main | '408c0c8' | '2026-02-24' | 'Merge branch 'main' of https://github.com/simonli... |
| mk64\tools\decomp-permuter | N/A | main | 'a858348' | '2026-02-21' | 'Merge branch 'main' of https://github.com/simonli... |
| mk64\tools\torch | N/A | main | '977dbb4' | '2026-02-24' | 'Merge branch 'main' of https://github.com/Harbour... |
| superbobbyball\f-zerox\bobcoin | N/A |  |  |  |  |
| Alti.Code.Studio\submodules\openclaw\.github | N/A | main | 'd1e99e5' | '2026-01-28' | 'Create SECURITY.md for security policy and report... |
| Alti.Code.Studio\submodules\openclaw\barnacle | N/A | main | 'c16f620' | '2026-02-18' | 'chore: update carbon' |
| Alti.Code.Studio\submodules\openclaw\butter.bot | N/A | main | 'd96c348' | '2026-01-02' | 'feat: add nano-banana hero image ðŸ§ˆðŸ¦žðŸŽ¨' |
| Alti.Code.Studio\submodules\openclaw\casa | N/A | main | '66d84d9' | '2026-02-07' | 'Fix scene selection state' |
| Alti.Code.Studio\submodules\openclaw\clawdinators | N/A | main | '4a40ae2' | '2026-02-23' | 'ðŸ¤– config: restrict main clawdinator discord sc... |
| Alti.Code.Studio\submodules\openclaw\clawgo | N/A | main | '36d4909' | '2026-01-05' | 'Align clawgo with clawdbot metadata' |
| Alti.Code.Studio\submodules\openclaw\clawhub | N/A | main | 'f4f8e72' | '2026-02-18' | 'docs: clarify skill delete/undelete permissions' |
| Alti.Code.Studio\submodules\openclaw\flawd-bot | N/A | main | '9d9655a' | '2026-01-24' | 'Initial commit' |
| Alti.Code.Studio\submodules\openclaw\homebrew-tap | N/A | main | 'b498a62' | '2026-01-04' | 'chore: initialize tap repo' |
| Alti.Code.Studio\submodules\openclaw\lobster | N/A | main | '61218be' | '2026-02-17' | 'Use gogcli GitHub URL in gog command help text (#... |
| Alti.Code.Studio\submodules\openclaw\maintainers | N/A | main | '01bc408' | '2026-02-19' | 'Remove redundant line from README' |
| Alti.Code.Studio\submodules\openclaw\nix-openclaw | N/A | main | 'fbef208' | '2026-02-21' | 'ðŸ¤– codex: bump openclaw pins' |
| Alti.Code.Studio\submodules\openclaw\nix-steipete-tools | N/A | main | '95ebfa7' | '2026-02-21' | 'sync skills from clawdbot' |
| Alti.Code.Studio\submodules\openclaw\openclaw | N/A | main | 'f8524ec77' | '2026-02-24' | 'fix(security): harden exported session html rende... |
| Alti.Code.Studio\submodules\openclaw\openclaw-ansible | N/A | main | '862ab49' | '2026-02-21' | 'Merge PR #25: Fix critical directory bootstrap bu... |
| Alti.Code.Studio\submodules\openclaw\openclaw.ai | N/A | main | 'ee7180f' | '2026-02-23' | 'fix(installer): silence gum skip notice in non-in... |
| Alti.Code.Studio\submodules\openclaw\skills | N/A | main | '88b9a58c39' | '2026-02-24' | 'meta: seedance-2-video-gen v1.4.1' |
| Alti.Code.Studio\submodules\openclaw\trust | N/A | main | 'eee55ba' | '2026-02-09' | 'fix: correct rendered URL in README' |
| Tickerstone\Tickerstone.Backend\third_party\fmt | N/A | master | 'b14a68db' | '2026-02-22' | 'Merge branch 'master' of https://github.com/fmtli... |
| Tickerstone\Tickerstone.Backend\third_party\magic_enum | N/A | master | 'ae4cff7' | '2026-02-21' | 'chore: save progress before update' |
| Tickerstone\Tickerstone.Backend\third_party\nameof | N/A | master | '0485ad7' | '2026-02-21' | 'chore: save progress before update' |
| Tickerstone\Tickerstone.Backend\third_party\roq-api | N/A | master | '339c0251' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\libs\aseprite-file | N/A | master | 'f108930' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\libs\commons-lang | N/A | master | '3d53079ad' | '2026-02-21' | 'Merge branch 'master' of https://github.com/apach... |
| bg\bobsgameonlinejava\libs\jinput | N/A | master | 'd461409' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\libs\lwjgl3 | N/A | master | '0fa7b6aae' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\libs\lz4-java | N/A | master | '5e90884' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\libs\micromod | N/A | master | '2aaa281' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\libs\mysql-connector-j | N/A | release/9.x | 'fdef61f4' | '2025-12-17' | 'Update copyright year.' |
| bg\bobsgameonlinejava\libs\twl-lwjgl3 | N/A | master | '5cdf50b' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\libs\xpp3 | N/A | master | 'af6ece2' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\libs\xz-java | N/A | master | '5b4763d' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\Cytopia | N/A | master | '91e1703b' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\DTile | N/A | master | 'a27f7b3' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\GrowTools | N/A | master | '309d17e' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\LibreSprite | N/A | master | '4d18dc589' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\OgmoEditor3-CE | N/A | master | '3526adb' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\Pixelorama | N/A | master | 'f34f1097' | '2026-02-21' | 'Merge branch 'master' of https://github.com/Orama... |
| bg\bobsgameonlinejava\references\PixiEditor | N/A | master | '09adceb7c' | '2026-02-21' | 'Merge branch 'master' of https://github.com/PixiE... |
| bg\bobsgameonlinejava\references\PyxleOS | N/A | master | '82e5d15' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\Raylib-Examples | N/A | master | '0a98962' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\Simple-Sprite-Tile-2D | N/A | master | '8d7daa0' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\SpeedEd | N/A | main | 'e6c6cd9' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\Tile-Studio | N/A | master | '95910e6' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite | N/A | main | '44589d3f8' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite-guide | N/A | main | '9388fa3' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\blockbench | N/A | master | 'c183c8e7' | '2026-01-25' | 'Update issue template' |
| bg\bobsgameonlinejava\references\bottled-up-tilemap | N/A | daelon-refactor | '43c0c19' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\csprite | N/A | master | '8e4f192' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\goxel | N/A | master | '162aec83' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\grafx2 | N/A | master | 'deec00e6' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\grafx2-dos | N/A | master | '84944cc' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\piskel | N/A | master | '11e6eac' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\raster-master | N/A | main | '067be50' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\retro-game-editor | N/A | master | '16812f7' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\rx | N/A | master | 'c8cb2c6' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\sprite-studio-64 | N/A | main | 'dab2033' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\stipple-effect | N/A | master | '272a63a' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\tactile | N/A | main | 'a8aace4c5' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\tiled | N/A | master | '8f60325dc' | '2026-02-21' | 'Merge branch 'master' of https://github.com/maped... |
| bg\bobsgameonlinejava\references\tilemap-editor | N/A | main | '0a05e87' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\tilemap-studio | N/A | master | '66adef2' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\voidsprite | N/A | HEAD |  |  |  |
| bg\okgame\lib\CLove | N/A | master | '2f5cb14' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\CTPL | N/A | master | '232fcce' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\Craft | N/A | master | 'eff0be7' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\FBNeo | N/A | master | '8b6d78495' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\GWEN | N/A | main | '352a7b1' | '2026-02-21' | 'Merge origin/continued-improvements into main' |
| bg\okgame\lib\Genesis-Plus-GX | N/A | master | 'd95f143' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\MODPlay | N/A | master | 'a02ac9b' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\Maelstrom | N/A | main | '0eeb9a0' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\MicroPather | N/A | master | '5622e44' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\MilkDrop-MusicVisualizer | N/A | master | 'a804245' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\MilkDrop3 | N/A | main | '6afcc0c' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\Nuklear | N/A | master | 'dec9897' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\RetroArch | N/A | master | '6c19b4a512' | '2026-02-21' | 'Merge branch 'master' of https://github.com/libre... |
| bg\okgame\lib\SDL | N/A | main | 'd8f1337e1' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\SDL2_gfx | N/A | master | 'a43e1cd' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\SDL_gesture | N/A | main | '5bd3259' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\SDL_image | N/A | main | 'b6be52fc' | '2026-02-18' | 'chore: save progress before update' |
| bg\okgame\lib\SDL_mixer | N/A | main | '582750d6' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\SDL_native_midi | N/A | main | 'c01a9bb' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\SDL_net | N/A | main | 'a360494' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\SDL_rtf | N/A | main | '99638ea' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\SDL_ttf | N/A | HEAD |  |  |  |
| bg\okgame\lib\Snippets | N/A | master | '3d3faa0' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\UACME | N/A | master | 'd4ef1ae' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\WavPack | N/A | master | '36b9c91' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\aom | N/A | main | '65b66a0d1' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\boost | N/A | master | '8d451ee5b3' | '2026-02-18' | 'chore: save progress before update' |
| bg\okgame\lib\brotli | N/A | HEAD |  |  |  |
| bg\okgame\lib\butterchurn | N/A | master | 'ea89299' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\cppcodec | N/A | master | '8984a6f' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\dav1d | N/A | master | '3fe7afb3' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\defold-astar | N/A | master | 'e2edcc9' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\desmume | N/A | HEAD |  |  |  |
| bobfilez\ai-file-sorter\external\Catch2 | N/A | devel | '376567b3' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\SysmonForLinux\sysmonCommon | N/A | main | '949f742' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\pngquant\lib | N/A | main | '2c87ad5' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\bobmania\itgmania\bobcoin | N/A | main | '77ed11f' | '2026-02-21' | 'Merge origin/feature/comprehensive-ui-spec-176711... |
| bobmani\itgmania\Themes\Simply Love | N/A | itgmania-release | 'ed98aad' | '2025-06-22' | 'Version bump to 5.7.0' |
| bobmani\itgmania\Themes\Simply-Love-SM5 | N/A | itgmania-release | 'a8ca8b2' | '2026-02-21' | 'Merge origin/srpg into itgmania-release' |
| bobmani\itgmania\extern\IXWebSocket | N/A | master | '200a1e5' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\itgmania\extern\ffmpeg | N/A | master | '8a9fd0a6fe' | '2026-02-21' | 'Merge branch 'master' of https://github.com/FFmpe... |
| bobmani\itgmania\extern\hidapi | 0.16.0 | master | '336114a' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\itgmania\extern\libjpeg-turbo | N/A | main | '3689356' | '2026-02-21' | 'Merge branch 'main' of https://github.com/libjpeg... |
| bobmani\itgmania\extern\libpng | N/A | libpng18 | '1b9aaf45d' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\itgmania\extern\libtomcrypt | N/A | develop | 'ebfe41f' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\itgmania\extern\libtommath | N/A | develop | '321d7c7' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\itgmania\extern\libusb | N/A | main | '35db58a' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\itgmania\extern\mbedtls | N/A | development | '4bf80a1' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\itgmania\extern\ogg | N/A | main | 'b121d4c' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\itgmania\extern\vorbis | N/A | main | 'f87e885' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\itgmania\extern\zlib | N/A | develop | 'e4a806e' | '2026-02-21' | 'chore: save progress before update' |
| bobsaver\projectm\vendor\projectm-eval | N/A | master | '0fa8b9f' | '2026-02-21' | 'chore: save progress before update' |
| borg\.borg\worktrees\grand-test-1770171775199 | 2.6.0 | task/grand-test-1770171775199 | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\.borg\worktrees\grand-test-1770171893786 | 2.6.0 | task/grand-test-1770171893786 | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\.borg\worktrees\grand-test-1770171936691 | 2.6.0 | task/grand-test-1770171936691 | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\.borg\worktrees\grand-test-1770172047640 | 2.6.0 | task/grand-test-1770172047640 | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\.borg\worktrees\grand-test-1770172150142 | 2.6.0 | task/grand-test-1770172150142 | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\.borg\worktrees\grand-test-1770172224262 | 2.6.0 | task/grand-test-1770172224262 | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\.borg\worktrees\grand-test-1770172488444 | 2.6.0 | task/grand-test-1770172488444 | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\.borg\worktrees\grand-test-1770174461411 | 2.6.0 | task/grand-test-1770174461411 | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\.borg\worktrees\grand-test-1770174604154 | 2.6.0 | task/grand-test-1770174604154 | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\.borg\worktrees\grand-test-1770174726807 | 2.6.0 | task/grand-test-1770174726807 | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\.borg\worktrees\swarm-test-1770491592269 | 2.6.0 | swarm-test-1770491592269 | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\.borg\worktrees\swarm-test-1770491990072 | 2.6.0 | swarm-test-1770491990072 | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\.borg\worktrees\swarm-test-1770494350445 | 2.6.0 | swarm-test-1770494350445 | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\.borg\worktrees\swarm-test-1770494813866 | 2.6.0 | swarm-test-1770494813866 | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\.borg\worktrees\swarm-test-1770500034818 | 2.6.0 | swarm-test-1770500034818 | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\.borg\worktrees\swarm-test-1770500343272 | 2.6.0 | swarm-test-1770500343272 | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\agents\refs\pydantic-ai | N/A | main | 'f4c52ad0' | '2026-02-02' | 'Fix compatibility with Vercel AI SDK v5 by adding... |
| borg\agents\refs\smolagents | N/A | main | 'd977b06' | '2026-01-20' | 'Update _function_type_hints_utils.py: CohereForAI... |
| borg\code-indexing\ast\ast-grep | N/A | main | '817ba62' | '2026-01-28' | 'chore(deps): update rust crate clap to v4.5.55 (#... |
| borg\code-indexing\ast\tree-sitter | N/A | master | 'eab567a' | '2026-02-02' | 'fix(rust): place `std::env::set_var` inside `unsa... |
| borg\code-indexing\tools\bloop | N/A | oss | '431e9e8' | '2024-12-04' | 'Add "Open with Codeanywhere" badge to README.md (... |
| borg\code-sandbox\runtimes\dagger | N/A | main | '3e92868' | '2026-01-29' | 'Update Helm chart testing link in Kubernetes docs... |
| borg\code-sandbox\tools\cohere-terrarium | N/A | main | '179d9cb' | '2024-04-24' | 'Merge pull request #1 from cohere-ai/ads/create-i... |
| borg\code-sandbox\tools\e2b-code-interpreter | N/A | main | '618716e' | '2026-02-09' | 'Merge branch 'main' of https://github.com/e2b-dev... |
| borg\code-sandbox\tools\open-interpreter | N/A | main | '681f5ce5' | '2026-02-09' | 'Merge pull request #1686 from thecaptain789/fix-t... |
| borg\code-sandbox\tools\safeexec | N/A | main | '93b6729' | '2025-12-30' | 'Refine README for clarity and formatting' |
| borg\computer-use\desktop\cua | N/A | main | '1b932bbb' | '2026-02-02' | 'Add Docs MCP Server with vector and SQL query cap... |
| borg\computer-use\desktop\magentic-ui | N/A | main | 'edaed9a' | '2025-12-17' | 'Enable Fara agent to save screenshots (#480)' |
| borg\computer-use\examples\claude-quickstarts | N/A | main | '4b2549e' | '2026-02-05' | 'Update computer-use-demo to use text_editor_20250... |
| borg\database\mcp-servers\dbhub | N/A | main | 'f303799' | '2026-01-30' | 'docs: add GitHub Copilot CLI installation instruc... |
| borg\database\mcp-servers\mysql | N/A | main | 'e24859a' | '2026-01-30' | 'chore(main): release 0.1.4 (#70)' |
| borg\database\mcp-servers\postgres | N/A | main | '6f1a9b7' | '2026-01-30' | 'chore(deps): update github actions (major) (#66)' |
| borg\external\TheNoeTrevino-dotfiles\nvim | N/A | main | 'c3ac5e5' | '2026-02-06' | 'rm: explorer preview' |
| borg\external\TheNoeTrevino-dotfiles\tmux | N/A | main | '3f61527' | '2026-01-08' | 'fix: increase right hand side of status bar' |
| borg\external\awesome\Awesome-LLMOps | N/A | main | 'e628643' | '2025-12-30' | 'Add semantic-coverage to Observability (#220)' |
| borg\external\awesome\awesome-llm-apps | N/A | main | '9529d00' | '2026-02-08' | 'Merge pull request #481 from Shubhamsaboo/ai-nego... |
| borg\external\chat\lobehub | N/A | main | '4efe60e9f' | '2026-02-02' | 'ðŸ”¨ chore: Remove unexpected file (#12045)' |
| borg\external\clis\CodeMachine-CLI | N/A | main | 'e55f110' | '2026-02-02' | 'docs: update README and move images to images fol... |
| borg\external\clis\CodeNomad | N/A | dev | '2556805' | '2026-02-02' | 'Merge branch 'main' into dev' |
| borg\external\clis\GoogleGeminiRouter | N/A | master | 'bbd9b59' | '2025-08-11' | 'updated readme file' |
| borg\external\clis\Kode-cli | N/A | main | '214c12f' | '2026-01-24' | 'Merge pull request #167 from shareAI-lab/docs/add... |
| borg\external\clis\Lynkr | N/A | main | '616cc7d' | '2026-02-02' | 'Update README.md' |
| borg\external\clis\SuperClaude_Framework | 4.2.0 | master | 'ad6b2e9' | '2026-01-18' | 'docs: update version references and fix CHANGELOG... |
| borg\external\clis\aichat | N/A | main | '0493134' | '2026-01-29' | 'chore: update models.yaml' |
| borg\external\clis\amp-examples-and-guides | N/A | main | '435ffc0' | '2025-10-17' | 'added jira to pr sdk agent' |
| borg\external\clis\amped | N/A | main | 'e415572' | '2025-11-01' | 'ci: make release notes have working download link... |
| borg\external\clis\awesome-amp-code | N/A | main | 'cf06730' | '2026-01-26' | 'docs: add founder attribution to README (#67)' |
| borg\external\clis\awesome-copilot | N/A | main | '8da3194' | '2026-02-02' | 'Merge pull request #637 from github/experiment/gi... |
| borg\external\clis\awesome-opencode | N/A | main | '4fadff1' | '2026-01-26' | 'docs: auto-regenerate README and registry data' |
| borg\external\clis\cc-switch | N/A | main | 'f0e8ba1' | '2026-02-02' | 'feat: session manger (#867)' |
| borg\external\clis\cc-switch-cli | N/A | main | '1716975' | '2026-02-02' | 'chore(release): v4.5.0' |
| borg\external\clis\ccproxy | N/A | main | '4d977b3' | '2026-02-01' | 'Update README.md' |
| borg\external\clis\ccs | N/A | main | 'be63056' | '2026-02-01' | 'chore(release): 7.34.0 [skip ci]' |
| borg\external\clis\claude-code | N/A | main | '550d836' | '2026-02-01' | 'fix(claudeup): v3.3.0 - use Bun in CI instead of ... |
| borg\external\clis\claude-code-mcp | N/A | main | '24dfd38' | '2025-05-17' | 'Clean up duplicate test-install directory structu... |
| borg\external\clis\claude-code-openrouter | N/A | main | 'c1a9710' | '2025-11-30' | 'Merge pull request #3 from derek-larson14/fix-git... |
| borg\external\clis\claude-code-router | N/A | main | 'c73fe0d' | '2026-01-10' | 'add posts' |
| borg\external\clis\claude-code-scheduler | N/A | main | 'f44464e' | '2026-01-19' | 'Merge pull request #1 from ojowwalker77/main' |
| borg\external\clis\claude-hooks | N/A | main | '335a123' | '2026-01-18' | 'Merge pull request #1 from brumar/patch-1' |
| borg\external\clis\claude-tools-mcp | N/A | main | '5615a91' | '2025-10-31' | 'Fix flaky list_shells tests' |
| borg\external\clis\code | N/A | main | '51680828f' | '2026-02-02' | 'docs(changelog): update for v0.6.57 [skip ci]' |
| borg\external\clis\code-assistant-manager | N/A | main | '51b49e9' | '2026-01-27' | 'Merge pull request #47 from zhujian0805/main' |
| borg\external\clis\codebuff | N/A | main | 'a6da1f46f' | '2026-02-02' | 'Dedicated privacy page' |
| borg\external\clis\codex | N/A | main | '9d976962e' | '2026-02-02' | 'Add credits tooltip (#10274)' |
| borg\external\clis\copilot-cli | N/A | main | '1bc2c29' | '2026-01-30' | 'Update changelog.md for version 0.0.400' |
| borg\external\clis\crush | N/A | main | '019a9a18' | '2026-02-02' | 'v0.38.1' |
| borg\external\clis\emdash | N/A | heads/main | 'c5371f3b' | '2026-01-14' | 'Merge pull request #615 from generalaction/ui-fil... |
| borg\external\clis\factory | N/A | main | '5013789' | '2026-01-29' | 'docs: add Analytics API reference documentation (... |
| borg\external\clis\gemini-cli-router | N/A | main | '5cbeed4' | '2025-07-21' | 'feat: add status display showing current port, mo... |
| borg\external\clis\gemini-openai-proxy | N/A | main | '1e54746' | '2025-10-07' | 'Update gemini library to supported sdk (#61)' |
| borg\external\clis\gemini-router | N/A | main | '1c38c5e' | '2025-09-20' | 'chore: gitignore' |
| borg\external\clis\gemini-superclaude-mcp-server | N/A | main | '05f2d99' | '2025-09-07' | 'Update README.md' |
| borg\external\clis\goose | N/A | main | '603f25258' | '2026-02-02' | 'Clean up build canonical warnings (#6880)' |
| borg\external\clis\grok-cli | N/A | main | 'ad177ec' | '2025-11-27' | 'Support global custom instructions from ~/.grok/G... |
| borg\external\clis\happy | N/A | main | '3ed8b121' | '2026-01-28' | 'ref: more docs' |
| borg\external\clis\kimi-cli | N/A | main | '9e87547' | '2026-02-03' | 'chore: bump version to 1.6 (#862)' |
| borg\external\clis\litellm | N/A | main | 'ade35a3f9a' | '2026-02-02' | 'Merge pull request #20266 from BerriAI/litellm_os... |
| borg\external\clis\llxprt-code | N/A | main | '88301db43' | '2026-02-02' | 'fix(ci): add quota-aware key selection to PR revi... |
| borg\external\clis\multi-agent-orchestration | N/A | main | 'a21ea34' | '2025-08-12' | 'updated README.md' |
| borg\external\clis\oh-my-opencode | N/A | dev | '0f81d4c' | '2026-02-02' | '@dan-myles has signed the CLA in code-yeongyu/oh-... |
| borg\external\clis\openai-gemini | N/A | main | '61a83bd' | '2025-12-22' | 'Update Vercel regions' |
| borg\external\clis\opencode | N/A | dev | 'b9aad20be' | '2026-02-02' | 'fix(app): open project search (#11783)' |
| borg\external\clis\opencode-gui | N/A | main | '0346d1c' | '2025-10-01' | 'Add: env.d.ts' |
| borg\external\clis\opencode-web | N/A | main | '0ab3c85' | '2025-07-15' | 'delete old docs' |
| borg\external\clis\plandex | N/A | main | 'e2d77207' | '2025-10-03' | 'link to cloud wind down post' |
| borg\external\clis\qwen-code | N/A | main | 'bd900d36' | '2026-01-30' | 'Merge pull request #1663 from QwenLM/hotfix/v0.8.... |
| borg\external\clis\schaltwerk | N/A | main | 'ab15b116' | '2026-02-02' | 'chore: bump version to 0.12.11' |
| borg\external\clis\smart-ralph | N/A | main | 'f2667f2' | '2026-02-01' | 'docs: simplify installation guide in README' |
| borg\external\clis\splitrail | N/A | main | '7a07e94' | '2026-01-30' | 'v3.3.1 (#109)' |
| borg\external\clis\vercel-ai-proxy | N/A | main | '976cab0' | '2024-11-21' | 'feat: support xai' |
| borg\external\code-indexing\CodeWeaver | N/A | main | '54225b3' | '2025-12-04' | 'Merge pull request #10 from glebkudr/patch-1' |
| borg\external\code-indexing\code-to-tree | N/A | master | '700a234' | '2025-05-17' | 'misc: add license' |
| borg\external\code-indexing\deepcontext-mcp | N/A | main | '8180517' | '2025-09-22' | 'attempt publishing to official MCP registry' |
| borg\external\code-indexing\octocode | N/A | master | '72c7030' | '2026-02-01' | 'fix(indexer): guarantee forward progress in text ... |
| borg\external\code-indexing\probe | N/A | main | 'b6055b2' | '2026-02-02' | 'feat: Forward MCP tools to delegate sessions (#37... |
| borg\external\code-indexing\serena | N/A | main | '764f26f' | '2026-02-01' | 'Merge pull request #982 from oraios/ls-completion... |
| borg\external\computer-use\algonius-browser | N/A | master | 'ae03e6a' | '2025-06-25' | 'feat: update logo' |
| borg\external\computer-use\chrome-devtools-mcp | N/A | main | '482a288' | '2026-02-10' | 'chore: evaluate select_page scenario (#925)' |
| borg\external\computer-use\claude-quickstarts | N/A | main | '4b2549e' | '2026-02-05' | 'Update computer-use-demo to use text_editor_20250... |
| borg\external\computer-use\clickclickclick | N/A | main | '6f18cd8' | '2025-10-05' | 'Update README.md' |
| borg\external\computer-use\cua | N/A | main | '1b932bbb' | '2026-02-02' | 'Add Docs MCP Server with vector and SQL query cap... |
| borg\external\computer-use\fara | N/A | main | 'ee0d215' | '2026-02-02' | 'chore: update submodules and merge features' |
| borg\external\computer-use\generalagents-python | N/A | main | 'd36f6a8' | '2025-04-11' | 'Bump version 0.1.1 (#8)' |
| borg\external\computer-use\kapture | N/A | master | 'a9ea1d9' | '2025-07-14' | 'chore: bump version to 2.1.1' |
| borg\external\computer-use\magentic-ui | N/A | main | 'edaed9a' | '2025-12-17' | 'Enable Fara agent to save screenshots (#480)' |
| borg\external\computer-use\puppeteer | N/A | main | 'f71d8cbc029' | '2026-02-02' | 'test: refactor keyboard modifier tests for clarit... |
| borg\external\computer-use\spark-mcp | N/A | claude/bytebot-mcp-server-01EeujB7JsCc5NqfrnbWM2oQ | '6b1eb66' | '2025-11-22' | 'Add production-grade ByteBot MCP Server' |
| borg\external\computer-use\uPhone | N/A | main | 'b4dd0db' | '2025-12-10' | 'fix: remove accidential proxy configuration' |
| borg\external\computer-use\webctl | N/A | main | '90bcf94' | '2026-01-26' | 'chore: Update version to 0.3.1 and finalize chang... |
| borg\external\database\dbhub | N/A | main | 'f303799' | '2026-01-30' | 'docs: add GitHub Copilot CLI installation instruc... |
| borg\external\database\mysql | N/A | main | 'e24859a' | '2026-01-30' | 'chore(main): release 0.1.4 (#70)' |
| borg\external\database\postgres | N/A | main | '6f1a9b7' | '2026-01-30' | 'chore(deps): update github actions (major) (#66)' |
| borg\external\database\supabase | N/A | master | '786f931f6e' | '2026-02-02' | 'Merge branch 'master' of https://github.com/supab... |
| borg\external\financial\BinanceMCPServer | N/A | main | 'bcceced' | '2026-01-22' | 'Fix formatting in license disclaimer section' |
| borg\external\financial\TAM-MCP-Server | N/A | main | '25030aa' | '2025-06-22' | '1.0.1' |
| borg\external\financial\Upsonic | N/A | master | '78eada8' | '2026-02-02' | 'feat: add comprehensive benchmark system for perf... |
| borg\external\financial\ai-hedge-fund | N/A | main | '9adb980' | '2025-12-01' | 'Bump version' |
| borg\external\financial\alpha_vantage_mcp | N/A | main | '59e3c41' | '2026-01-23' | 'Update README.md' |
| borg\external\financial\armor-crypto-mcp | N/A | main | 'c026c00' | '2025-05-27' | 'Merge pull request #22 from armorwallet/fix/archi... |
| borg\external\financial\awesome-crypto-mcp-servers | N/A | main | '6f3db72' | '2025-03-27' | 'Merge pull request #2 from donbagger/dexpaprika-m... |
| borg\external\financial\binance-mcp-server | N/A | main | '2b6f2b7' | '2026-01-31' | 'update readme' |
| borg\external\financial\bybit-mcp-server | N/A | master | '1884c5c' | '2025-07-13' | 'add npm download counter' |
| borg\external\financial\coin_api_mcp | N/A | main | '33eb213' | '2025-02-14' | 'Merge pull request #2 from smithery-ai/smithery/c... |
| borg\external\financial\coingecko-typescript | N/A | main | '29d1d98' | '2025-12-18' | 'release: 2.5.0' |
| borg\external\financial\coinmarketcap-mcp | N/A | main | '0214e75' | '2025-11-25' | 'Update badge links in README.md (#80)' |
| borg\external\financial\coinstats-mcp | N/A | main | '98dd666' | '2025-08-15' | 'Update README.md' |
| borg\external\financial\crypto-feargreed-mcp | N/A | main | 'b1f2294' | '2025-05-10' | 'Merge pull request #3 from smithery-ai/smithery/c... |
| borg\external\financial\crypto-indicators-mcp | N/A | main | '2855e66' | '2025-12-06' | 'update README' |
| borg\external\financial\crypto-sentiment-mcp | N/A | main | 'a002ece' | '2025-03-28' | 'update pyproject.toml' |
| borg\external\financial\cryptopanic-mcp-server | N/A | main | '922f2e0' | '2025-12-09' | 'Update README' |
| borg\external\financial\dappier-mcp | N/A | staging | '38bbde1' | '2025-06-27' | 'add a video demo link' |
| borg\external\financial\freqtrade-mcp | N/A | main | '6762093' | '2025-12-06' | 'Update README' |
| borg\external\financial\hive-crypto-mcp | N/A | main | '3e86d03' | '2025-09-08' | 'Update README.md' |
| borg\external\financial\korea-stock-analyzer-mcp | N/A | main | 'e3145c1' | '2025-09-20' | 'perf: cache fundamentals for multi-year metrics' |
| borg\external\financial\mcp | N/A | main | 'a74555c' | '2025-07-31' | 'chore(remove-vector-db) remove vector db from git... |
| borg\external\financial\mcp-audiense-insights | N/A | main | 'f18ffa6' | '2025-06-16' | 'chore: Add deprecation note' |
| borg\external\financial\mcp-server | N/A | main | '08e7a3d' | '2025-06-05' | 'Update gitignore' |
| borg\external\financial\octagon-13f-holdings-mcp | N/A | main | 'd884613' | '2025-06-03' | 'udpate package json' |
| borg\external\financial\octagon-financials-mcp | N/A | main | '19e79d4' | '2025-06-04' | 'update package name' |
| borg\external\financial\octagon-funding-data-mcp | N/A | main | 'f472310' | '2025-06-03' | 'first commit' |
| borg\external\financial\octagon-investors-mcp | N/A | main | 'dd73c91' | '2025-06-03' | 'first commit' |
| borg\external\financial\octagon-mcp-server | N/A | main | 'd8f2466' | '2026-02-09' | 'Merge pull request #9 from OctagonAI/progress' |
| borg\external\financial\octagon-private-companies-mcp | N/A | main | '40f3386' | '2025-06-03' | 'first commit' |
| borg\external\financial\octagon-sec-filings-mcp | N/A | main | 'ce1280a' | '2025-06-03' | 'first commit' |
| borg\external\financial\octagon-stock-market-data-mcp | N/A | main | '277d166' | '2025-06-03' | 'Update README.md' |
| borg\external\financial\octagon-transcripts-mcp | N/A | main | 'b3e5ee8' | '2025-06-04' | 'update package name' |
| borg\external\financial\octagon-vc-agents | N/A | main | '8af68fe' | '2025-05-12' | 'Removing Metrics Agent' |
| borg\external\financial\okx-mcp-playground | N/A | main | '23c6a84' | '2025-07-16' | 'fix: typo' |
| borg\external\financial\polymarket-mcp | N/A | master | '9660556' | '2026-01-11' | 'Merge pull request #10 from ozgureyilmaz/fix/cli-... |
| borg\external\financial\trade-agent-mcp | N/A | main | 'b25f32d' | '2026-02-08' | 'Enhance README with brokerage and crypto support ... |
| borg\external\financial\uniswap-poolspy-mcp | N/A | main | 'a4dfb09' | '2025-03-28' | 'update project name' |
| borg\external\financial\uniswap-trader-mcp | N/A | main | 'b743a9d' | '2025-05-08' | 'Merge pull request #2 from smithery-ai/smithery/c... |
| borg\external\financial\upbit-mcp-server | N/A | main | '60f2698' | '2025-04-25' | 'ci: add gitguard' |
| borg\external\frameworks\agent-lightning | N/A | main | '9864b8fb' | '2026-02-10' | 'New example: AGL Simulation (#367)' |
| borg\external\frameworks\awesome-llm-apps | N/A | main | '9529d00' | '2026-02-08' | 'Merge pull request #481 from Shubhamsaboo/ai-nego... |
| borg\external\frameworks\fastmcp | N/A | main | '49707813' | '2026-02-02' | 'Mock network calls in CLI tests and use MemorySto... |
| borg\external\frameworks\maestro | N/A | main | '2fcd03eb' | '2026-02-03' | 'Remove duplicate Contributors section' |
| borg\external\frameworks\mcp-reasoner | N/A | main | 'ee93c70' | '2025-01-07' | 'fixed readme for formatting' |
| borg\external\frameworks\opencode-interpreter | N/A | main | '9674d8a' | '2024-05-07' | 'update evalplus' |
| borg\external\frameworks\pi-mono | N/A | main | '81b8f9c0' | '2026-02-03' | 'chore: approve contributor PriNova' |
| borg\external\frameworks\polymcp | N/A | main | '964a650' | '2026-02-03' | 'Update paths in publish.yml to ignore specific fi... |
| borg\external\frameworks\ui-tars | N/A | main | '3f254968' | '2026-01-05' | 'Fix typo, launch* instead of luanch (#1774)' |
| borg\external\mcp-directories\awesome-ai-apps | N/A | main | '955655e' | '2026-02-07' | 'Merge pull request #122 from kantorcodes/add-agen... |
| borg\external\mcp-directories\awesome-mcp-servers | N/A | main | 'c73c513' | '2026-02-01' | 'Merge pull request #1790 from jackparnell/main' |
| borg\external\mcp-directories\metamcp | 3.2.18 | main | '324102e' | '2026-01-11' | 'docs: expand ROADMAP.md with AIOS integration and... |
| borg\external\mcp-directories\toolsdk-mcp-registry | N/A | main | '760a4401' | '2026-01-27' | 'npm @toolsdk.ai/registry released - 1.0.154' |
| borg\external\mcp-servers\Andrew6rant | N/A | main | 'e059bd7' | '2025-03-03' | 'Updated README' |
| borg\external\mcp-servers\Claude-Matrix | N/A | main | '844b984' | '2026-02-07' | 'Nuke skill, dead code tools, hooks cleanup (#97)' |
| borg\external\mcp-servers\Jacck-mcp-reasoner | N/A | main | 'ee93c70' | '2025-01-07' | 'fixed readme for formatting' |
| borg\external\mcp-servers\LoCoDiff-bench | N/A | main | 'f6fb4be4d' | '2025-10-15' | 'Merge pull request #340 from AbanteAI/mentat-264' |
| borg\external\mcp-servers\MZaFaRM | N/A | main | '4e0c045' | '2026-02-02' | '[BOT] auto update README - 2026-02-02' |
| borg\external\mcp-servers\Maestro | N/A | main | '9cf1b056' | '2026-02-01' | 'docs: sync release notes for v0.15.0-rc' |
| borg\external\mcp-servers\Tether-Chat | N/A | main | '4553b09' | '2026-01-28' | 'Made the checkbox 'extended context enabled' pers... |
| borg\external\mcp-servers\adk-js | N/A | main | '6aebd70' | '2026-01-30' | 'Release: v0.3.0 (#107)' |
| borg\external\mcp-servers\agent-console | N/A | main | '0bbdaa7' | '2025-12-30' | 'Add duration display to sub-agent panel' |
| borg\external\mcp-servers\awesome-llm-services | N/A | main | 'b845aca' | '2026-02-09' | 'feat: postiz, nanobot' |
| borg\external\mcp-servers\bilgecan | N/A | main | '31ccb1d' | '2025-12-23' | 'hide ai task list during edit mode' |
| borg\external\mcp-servers\browser-tools-mcp | N/A | main | '0befce3' | '2025-03-26' | 'Update README.md' |
| borg\external\mcp-servers\chgpt-mcp-bridge | N/A | main | 'd99e46d' | '2025-12-04' | 'fix: fastmcp 2.13 not working, requiring 2.12 for... |
| borg\external\mcp-servers\claude-limitline | N/A | main | 'af0855d' | '2026-01-01' | 'Merge pull request #11 from tylergraydev/fix/maco... |
| borg\external\mcp-servers\cloud-run-mcp | N/A | main | '469d9ba' | '2026-02-09' | 'Merge branch 'main' of https://github.com/GoogleC... |
| borg\external\mcp-servers\combined-autonomous-coding | N/A | master | '0dc2e1d' | '2026-02-10' | 'feat: Add yaml-lab command (#1013)' |
| borg\external\mcp-servers\conductor | N/A | main | 'd4749d3' | '2026-01-29' | 'Merge pull request #85 from gemini-cli-extensions... |
| borg\external\mcp-servers\datacommons | N/A | main | '29c6de8' | '2025-11-20' | 'Publish v1.1.5 (#19)' |
| borg\external\mcp-servers\experiments | N/A | main | '2cea0c151' | '2024-06-23' | 'Update week 6/23 submission results' |
| borg\external\mcp-servers\firebase | N/A | main | '997151b' | '2025-10-13' | 'Add IS_GEMINI_CLI_EXTENSION env variable (#6)' |
| borg\external\mcp-servers\gcloud | N/A | main | 'ec545cd' | '2025-09-23' | 'doc: readme wording' |
| borg\external\mcp-servers\gnapsis | N/A | main | '01da658' | '2026-02-02' | 'Improve 3D graph visualizer UX (#30)' |
| borg\external\mcp-servers\gpt-generals | N/A | main | '2c7ba3a' | '2025-03-14' | 'Merge pull request #120 from AbanteAI/mentat-119-... |
| borg\external\mcp-servers\inframind | N/A | main | '64854d0' | '2025-12-15' | 'added the modal test script' |
| borg\external\mcp-servers\jules | N/A | main | '9f2fc14' | '2025-10-30' | 'Merge pull request #4 from Smetalo/Smetalo-patch-... |
| borg\external\mcp-servers\mcp | N/A | main | '7492e83' | '2025-05-23' | 'Bump version' |
| borg\external\mcp-servers\mcp-chrome | N/A | master | 'f48e717' | '2026-01-06' | 'Merge pull request #272 from hangwin/feat/element... |
| borg\external\mcp-servers\mcp-toolbox | N/A | main | 'e39267d' | '2026-01-28' | 'chore(main): release 0.5.0 (#70)' |
| borg\external\mcp-servers\mcp_obsidian_notes | N/A | master | 'f189a2a' | '2026-01-31' | 'cli' |
| borg\external\mcp-servers\mcpo | N/A | main | '91e8f94' | '2025-10-14' | 'Merge pull request #263 from open-webui/dev' |
| borg\external\mcp-servers\memora | N/A | main | 'eae45c0' | '2026-01-31' | 'Fix cloud graph broadcast blocked by Cloudflare b... |
| borg\external\mcp-servers\memory-opensource | N/A | main | '4dfc7c0' | '2026-02-02' | 'chore: update submodules and merge features' |
| borg\external\mcp-servers\mentat-template-js | N/A | main | '299953c' | '2025-08-01' | 'change order of preview windows' |
| borg\external\mcp-servers\nanobanana | N/A | heads/main | '74b36b6' | '2025-11-20' |  |
| borg\external\mcp-servers\party | N/A | main | '1b0a381' | '2025-10-08' | 'update readme' |
| borg\external\mcp-servers\qa-party | N/A | main | 'd2aa345' | '2025-09-25' | 'update party README' |
| borg\external\mcp-servers\repo-visualizer | N/A | main | '460b9ca' | '2025-07-29' | 'Merge pull request #75 from AbanteAI/mentat-64' |
| borg\external\mcp-servers\resterm | N/A | main | 'd44799d' | '2026-02-02' | 'docs: add resterm init' |
| borg\external\mcp-servers\spice | N/A | main | '395a594' | '2024-09-27' | 'Merge pull request #115 from AbanteAI/version-0.4... |
| borg\external\mcp-servers\tiktoken | N/A | main | '08f9f69' | '2025-03-21' | 'Merge pull request #2 from AbanteAI/mentat-script... |
| borg\external\mcp-servers\vertex | N/A | main | '22600f8' | '2025-12-11' | 'Merge pull request #4 from gemini-cli-extensions/... |
| borg\external\mcp-servers\vertex-ai-creative-studio | N/A | main | '61a746a5' | '2026-02-02' | 'chore(deps): bump python-multipart (#1011)' |
| borg\external\mcp-servers\vscode | N/A | main | '8bb98407949' | '2025-06-16' | 'Merge pull request #251658 from microsoft/tyriar/... |
| borg\external\mcp-servers\websocket-demo | N/A | main | '4ec4e9c' | '2025-06-17' | 'initial commit - working demo of websocket forwar... |
| borg\external\mcp-servers\workspace | N/A | main | '07c9434' | '2026-02-08' | 'chore: auto-commit local changes' |
| borg\external\mcp-servers\wot-mcp | N/A | main | '0a325ac' | '2025-12-17' | 'First release' |
| borg\external\mcp-servers\wot-mcp-cli | N/A | main | 'dbce3b3' | '2025-12-17' | 'First release' |
| borg\external\mcp-servers\wot-mcp-examples | N/A | main | 'cdf26dc' | '2026-02-04' | 'Fixed the access to the notification' |
| borg\external\mcp-tooling\Polymcp | N/A | main | '98694db' | '2026-01-27' | 'Bump version from 1.3.4 to 1.3.5' |
| borg\external\mcp-tooling\Switchboard | N/A | main | 'e33359c' | '2025-10-01' | 'README' |
| borg\external\mcp-tooling\ToolRAG | N/A | main | 'd503b58' | '2025-03-29' | '#0' |
| borg\external\mcp-tooling\agent-mcp-gateway | N/A | main | 'a1d664a' | '2025-12-02' | 'Fix graceful shutdown of downstream MCP servers' |
| borg\external\mcp-tooling\agents | N/A | main | '1a11bc6' | '2026-02-02' | 'Downgrade agents changelog from minor to patch' |
| borg\external\mcp-tooling\claude-lazy-loading | N/A | master | '77cd89b' | '2025-09-09' | 'Update README with correct repository URL' |
| borg\external\mcp-tooling\code-executor-MCP | N/A | main | '9421b82' | '2025-11-23' | 'chore(release): prepare v1.0.5' |
| borg\external\mcp-tooling\code-mode | N/A | main | '181f053' | '2026-02-02' | 'Merge branch 'main' of https://github.com/univers... |
| borg\external\mcp-tooling\code-mode-toon | N/A | main | '6caaa2c' | '2026-01-22' | 'Merge pull request #12 from ziad-hsn/ziad-hsn-pat... |
| borg\external\mcp-tooling\codemode-unified | N/A | main | '6e4daa3' | '2025-10-01' | 'Merge feature/mcp-typescript-codegen: comprehensi... |
| borg\external\mcp-tooling\hypertool-mcp | N/A | main | '5a5175c' | '2025-09-30' | 'chore: release version 0.0.46 [skip-ci]' |
| borg\external\mcp-tooling\lazy-mcp | N/A | main | '44abd4d' | '2026-01-09' | 'Merge pull request #10 from agentic-ai-forge/feat... |
| borg\external\mcp-tooling\lootbox | N/A | main | '0e8fc1b' | '2025-12-06' | 'Revise promo link and project description' |
| borg\external\mcp-tooling\mcp-funnel | N/A | develop | '7ff977e' | '2025-11-24' | 'Merge branch 'develop'' |
| borg\external\mcp-tooling\mcp-gateway | N/A | main | '5dbe5d6' | '2026-01-15' | 'Bump fastmcp from 2.13.0 to 2.14.0 in /sample-ser... |
| borg\external\mcp-tooling\mcp-json-yaml-toml | N/A | main | 'ba600ec' | '2026-02-01' | 'Merge pull request #22 from bitflight-devops/clau... |
| borg\external\mcp-tooling\mcp-linker | N/A | main | '89cea47' | '2026-01-20' | 'docs: add note for relaunching app after first lo... |
| borg\external\mcp-tooling\mcp-server-code-execution-mode | N/A | main | '27d23b8' | '2025-12-05' | 'Refactor code structure for improved readability ... |
| borg\external\mcp-tooling\mcp-tool-chainer | N/A | main | '3331750' | '2026-01-23' | 'wip' |
| borg\external\mcp-tooling\mcpm.sh | N/A | main | '44601b9' | '2026-01-15' | 'chore(release): 2.13.0 [skip ci]' |
| borg\external\mcp-tooling\mcpproxy | N/A | main | 'd43b27f' | '2025-07-22' | 'Fix Tool Indexing, Persistence, and Retrieval Iss... |
| borg\external\mcp-tooling\meta-mcp-proxy | N/A | main | '6c10f1b' | '2025-05-13' | 'Update package' |
| borg\external\mcp-tooling\ncp | N/A | main | '290845e' | '2026-01-17' | 'Merge pull request #14 from portel-dev/claude/val... |
| borg\external\mcp-tooling\opus_agents | N/A | main | '5652e61' | '2026-01-18' | 'local release steps' |
| borg\external\mcp-tooling\pctx | N/A | main | '4b413be' | '2026-01-29' | 'remove allowed hosts tests (fetch no longer avail... |
| borg\external\mcp-tooling\pluggedin-mcp | N/A | main | '1e23c62' | '2026-01-07' | '1.12.5' |
| borg\external\mcp-tooling\programmatic-tool-calling-ai-sdk | N/A | main | '8297ec8' | '2025-12-03' | 'Add package directory and update documentation wi... |
| borg\external\mcp-tooling\smolagents | N/A | main | 'd977b06' | '2026-01-20' | 'Update _function_type_hints_utils.py: CohereForAI... |
| borg\external\mcp-tooling\toolscript | N/A | main | '0268bf8' | '2025-12-12' | 'chore(release): 1.2.1 [skip ci]' |
| borg\external\mcp-tooling\utcp-mcp | N/A | main | '5ed1f04' | '2025-11-27' | 'Merge pull request #14 from universal-tool-callin... |
| borg\external\mcp-tooling\zypher-agent | N/A | main | '1b319c6' | '2026-02-08' | 'chore(agent): update McpServerManager for new mcp... |
| borg\external\memory\Context-Engine | N/A | main | '2b22d04' | '2025-12-11' | 'feat: Refactor MCP setup logic, add compatibility... |
| borg\external\memory\Long-Term-Memory-API | N/A | main | '00a7119' | '2025-12-17' | 'fix: Update Stripe API version to 2025-12-15.clov... |
| borg\external\memory\MemMachine | N/A | main | 'ca2dbf7' | '2026-01-30' | 'fix messages is not filtered by conversation inde... |
| borg\external\memory\Memori | N/A | main | '7e45217' | '2026-02-02' | 'feat: introduce UnsupportedLLMProviderError for b... |
| borg\external\memory\MemoryOS | N/A | main | 'd7a5462' | '2025-09-20' | 'Update README.md' |
| borg\external\memory\Mimir | N/A | main | '01c0203' | '2025-12-25' | 'update chat file' |
| borg\external\memory\OpenMemory | N/A | main | '30daf78' | '2026-01-27' | 'feat: implement core database, vector store, temp... |
| borg\external\memory\automem | N/A | main | 'ad9500f' | '2026-01-21' | 'docs: Update API documentation and configuration ... |
| borg\external\memory\awesome-pieces | N/A | main | '4be5b5c' | '2024-08-29' | 'Merge pull request #4 from Sophyia7/main' |
| borg\external\memory\beads | N/A | main | 'c2f3d46e' | '2026-02-02' | 'fix: resolve errcheck violations in cmd/bd/gitlab... |
| borg\external\memory\beads_viewer | N/A | main | 'e05901b' | '2026-02-01' | 'fix: correct data_source path and exit code in ro... |
| borg\external\memory\chroma | N/A | main | 'edb189187' | '2026-02-02' | '[DOC] fix fork function param (#6306)' |
| borg\external\memory\cipher | N/A | main | '8155225' | '2025-12-16' | 'Merge pull request #290 from MahlerTom/bug/sqlite... |
| borg\external\memory\cli-agent | N/A | main | '78a752d' | '2026-01-18' | 'Merge pull request #437 from SiddharthaSree/feat/... |
| borg\external\memory\cognee | N/A | main | '2cef47e0' | '2026-01-31' | 'Added module-level docstrings for memify, graph, ... |
| borg\external\memory\context-portal | N/A | main | '18bde46' | '2026-01-19' | 'Merge pull request #74 from GreatScottyMac/depend... |
| borg\external\memory\core | N/A | main | 'd8cd4a3' | '2026-02-03' | 'fix: document is not update directly when edited ... |
| borg\external\memory\hindsight | N/A | main | '3825506' | '2026-02-02' | 'fix: custom pg schema is not reliable (#278)' |
| borg\external\memory\jean-memory | N/A | main | 'aac8e748' | '2026-01-06' | 'refactor: Improve deprecation banner and add foot... |
| borg\external\memory\langmem | N/A | main | '6c1a46c' | '2025-10-27' | 'Update lockfile' |
| borg\external\memory\letta | N/A | main | '65dbd7fd8' | '2026-01-29' | 'chore: bump v0.16.4 (#3168)' |
| borg\external\memory\letta-code | N/A | main | 'b9eaaa1' | '2026-02-02' | 'refactor(cli): unify TUI and headless stream proc... |
| borg\external\memory\lifecontext | N/A | main | 'fefe70b' | '2025-12-02' | 'Merge branch 'main' into dev' |
| borg\external\memory\mcp-automem | N/A | main | 'c8b05f7' | '2026-01-26' | 'Feat/claude desktop plugin (#34)' |
| borg\external\memory\mcp-memory-service | N/A | main | '14f9ffb' | '2026-02-10' | 'fix(ci): install pytest-benchmark in uvx test (#3... |
| borg\external\memory\mcp-server-qdrant | N/A | master | '860ab93' | '2025-12-10' | 'bump version to 0.8.1 (#99)' |
| borg\external\memory\mem0 | N/A | main | '70baa46c' | '2026-02-02' | 'fix: add OpenClaw to docs navigation (#3965)' |
| borg\external\memory\memU | N/A | main | 'ee27d8a' | '2026-02-02' | 'docs: file system in readme (#301)' |
| borg\external\memory\memai | N/A | main | '480552f' | '2026-01-29' | 'Merge pull request #2 from KraftyUX/feature/bulk-... |
| borg\external\memory\memvault-sync | N/A | main | '81a4a42' | '2025-12-17' | 'fix: update correct readme for marketplace' |
| borg\external\memory\opencode-plugin-simple-memory | N/A | main | '5ac3fb0' | '2025-12-15' | '1.0.2' |
| borg\external\memory\qdrant | N/A | main | '235c64010' | '2024-10-16' | 'Initial commit' |
| borg\external\memory\roampal-core | N/A | main | 'd8984e1' | '2026-01-27' | 'v0.3.1: Reserved working memory slot for context ... |
| borg\external\memory\sem-mem | N/A | main | '5178c14' | '2026-01-09' | 'license updates' |
| borg\external\memory\servers | N/A | main | 'e6b0b0f' | '2026-01-27' | 'Merge pull request #3256 from modelcontextprotoco... |
| borg\external\memory\supermemory | N/A | main | 'b7e6eb65' | '2026-01-31' | 'langchain integration (#718)' |
| borg\external\memory\supermemory-mcp | N/A | master | '84f5dc9' | '2025-12-30' | 'Update README.md' |
| borg\external\memory\txtai | N/A | master | '92461fe' | '2026-01-30' | 'Add support for Agent memory, closes #1016' |
| borg\external\memory\zep | N/A | main | '4f170ca' | '2026-02-01' | 'Add ElevenLabs Zep example with React frontend an... |
| borg\external\misc\MaorBril-clauder | N/A | main | '523b272' | '2026-01-26' | 'chore: bump version to 0.8.2' |
| borg\external\misc\mikekelly-claude-sneakpeek | N/A | main | 'c1c57b1' | '2026-01-28' | '1.6.10' |
| borg\external\misc\nuwainfo-ffl-mcp | N/A | master | 'e1c1650' | '2026-01-23' | 'Demo intro' |
| borg\external\misc\openclaw | N/A | main | '7113dc21a' | '2026-02-02' | 'Revert "Core: update shared gateway models"' |
| borg\external\misc\sivanhavkin-Entelgia | N/A | main | 'bd5ec56' | '2026-02-10' | 'Document community proposals for transparency' |
| borg\external\misc\sugaiketadao-sicore | N/A | main | '75d3c8d' | '2026-02-08' | 'Refactoring, and documentation updates.' |
| borg\external\misc\tchebb-openwv | N/A | main | '4306a3c' | '2025-11-05' | 'build.rs: Use new output form' |
| borg\external\orchestration\A2A | N/A | main | '6292104' | '2026-01-29' | 'fix(spec): Added clarification on timestamps in H... |
| borg\external\orchestration\CopilotKit | N/A | main | '6b9c60e44' | '2026-02-09' | 'fix: add dependencies to fix stale state of regen... |
| borg\external\orchestration\OpenHands | N/A | main | 'b088d4857' | '2026-02-02' | 'Improve batch_get_app_conversations UUID handling... |
| borg\external\orchestration\PocketFlow-Tutorial-Cursor | N/A | main | '0e69c81' | '2025-03-17' | 'Update README.md' |
| borg\external\orchestration\Self-Learning-Agents | N/A | main | 'ca6c83a' | '2025-06-28' | 'Merge pull request #2 from omdivyatej/c' |
| borg\external\orchestration\TaskSync | N/A | main | 'b6bacf8' | '2026-01-06' | 'update CHANGELOG' |
| borg\external\orchestration\a2a-main | N/A | main | '6292104' | '2026-01-29' | 'fix(spec): Added clarification on timestamps in H... |
| borg\external\orchestration\a2a-ui | N/A | main | '04de7f1' | '2025-12-04' | 'Updated default URL in `AddAgentModal` to point t... |
| borg\external\orchestration\ag-ui | N/A | main | '6bd15ad8' | '2026-02-02' | 'chore: release mastra sdk v1 (#1042)' |
| borg\external\orchestration\ag-ui-protocol | N/A | main | 'd0f8fbf' | '2026-02-10' | 'Feat/tsdown (#1071)' |
| borg\external\orchestration\agentdepot-agents | N/A | main | '063606c' | '2025-12-17' | 'chore: removed unused verified property and valid... |
| borg\external\orchestration\agentic-playground | N/A | main | 'a99a84f' | '2025-07-26' | 'Update README.md' |
| borg\external\orchestration\agentic-ray | N/A | main | '7b14304' | '2026-02-05' | 'Documentation edits made through Mintlify web edi... |
| borg\external\orchestration\codev | N/A | main | '959480a' | '2026-02-02' | '[Spec 0087] review: porch-timeout-termination-ret... |
| borg\external\orchestration\promptflow | N/A | main | 'a7ff428' | '2025-12-22' | 'Updated the runtime-change-log.md file (#4074)' |
| borg\external\orchestration\pydantic-deepagents | N/A | main | 'f450c4f' | '2026-02-07' | 'Merge pull request #27 from vstorm-co/0.2.15' |
| borg\external\orchestration\tasksync-mcp | N/A | main | '7a5d1c9' | '2026-01-25' | 'Update readme' |
| borg\external\rag\PageIndex | N/A | main | '884209e' | '2026-01-25' | 'Update README.md' |
| borg\external\rag\WeKnora | 0.2.10 | main | '9c57e11' | '2026-02-02' | 'feat: add bing search provider' |
| borg\external\rag\llama_index | N/A | main | 'cf8835bc8' | '2026-02-02' | 'fix(agent): handle empty LLM responses with retry... |
| borg\external\rag\mindsdb | N/A | main | 'c32f8619a' | '2026-01-28' | 'add images for readme files update (#12151)' |
| borg\external\rag\vectorize-ui | N/A | main | '29183da' | '2025-11-11' | 'add license' |
| borg\external\research\kea-research | v0.2.0 | main | '8a019f8' | '2026-01-25' | 'Update README.md' |
| borg\external\sandboxing\code-interpreter | N/A | main | 'dad052e' | '2026-02-09' | 'Merge branch 'main' of https://github.com/e2b-dev... |
| borg\external\sandboxing\code-sandbox-mcp | N/A | main | '0f0b8d6' | '2025-03-23' | 'feat: add copy_file_from_sandbox tool for file tr... |
| borg\external\sandboxing\cohere-terrarium | N/A | main | '179d9cb' | '2024-04-24' | 'Merge pull request #1 from cohere-ai/ads/create-i... |
| borg\external\sandboxing\microsandbox | N/A | main | '790ecd7' | '2026-01-11' | 'fix: improve error reporting in installer script ... |
| borg\external\sandboxing\open-interpreter | N/A | main | '681f5ce5' | '2026-02-09' | 'Merge pull request #1686 from thecaptain789/fix-t... |
| borg\external\sandboxing\piston | N/A | master | '1d55a41' | '2025-02-08' | 'Explicitly provide env vars instead of inheriting... |
| borg\external\sandboxing\piston-mcp | N/A | main | 'b15d00c' | '2025-07-06' | 'update README' |
| borg\external\search\DesktopCommanderMCP | N/A | main | 'feb2a38' | '2026-02-09' | 'Update README.md' |
| borg\external\search\mcp-everything-search | N/A | main | '0d46c1b' | '2025-10-21' | 'Add CLAUDE.md for Claude Code guidance' |
| borg\external\search\web-search-mcp | N/A | main | 'eeb03f8' | '2025-08-08' | 'Update to tidy README' |
| borg\external\skills\claude-code-tips | N/A | main | '7d3b087' | '2026-02-01' | 'Add note about picking your own version' |
| borg\external\skills\dotfiles | N/A | main | '6cdf472' | '2026-02-02' | 'chore: update submodules and merge features' |
| borg\external\skills\gemini-claude-skills | N/A | main | '0a31cfe' | '2026-01-14' | 'Add image input support to Nano Banana Pro skill' |
| borg\external\skills\jkfran-killport | N/A | main | '99e09ba' | '2025-11-04' | 'Update ci.yml' |
| borg\external\skills\joel-jeremy-emissary | N/A | main | 'e68c385' | '2026-02-02' | 'Bump gradle-wrapper from 9.3.0 to 9.3.1 (#269)' |
| borg\external\skills\microsoft-dcp | N/A | main | '0da67d7' | '2026-02-02' | 'Update documentation for release process (#67)' |
| borg\external\skills\puemos-lareview | N/A | main | '5ba51b8' | '2026-01-23' | 'chore(release): v0.0.28' |
| borg\external\skills\skills | N/A | main | '69c0b1a' | '2025-12-20' | 'Add link to Agent Skills specification website (#... |
| borg\external\skills\ykdojo-claude-code-tips | N/A | main | '5184a36' | '2026-02-09' | 'Add system prompt patches for Claude Code 2.1.38' |
| borg\external\skills_repos\TheNoeTrevino-dotfiles | N/A | main | '0e6288b' | '2026-01-22' | 'Add commit navigation shortcuts to config' |
| borg\external\skills_repos\anthropic-skills | N/A | main | '1ed29a0' | '2026-02-06' | 'Update skill-creator and make scripts executable ... |
| borg\external\skills_repos\bkircher-skills | N/A | main | '9fe323a' | '2026-01-28' | 'unit-testing skill: refine a bit' |
| borg\external\skills_repos\gemini-claude-skills | N/A | main | '0a31cfe' | '2026-01-14' | 'Add image input support to Nano Banana Pro skill' |
| borg\external\skills_repos\humanizer | N/A | main | 'c78047b' | '2026-01-22' | 'Improve full before/after example to hit all 24 A... |
| borg\external\skills_repos\openai-skills | N/A | main | '4ab6e0f' | '2026-02-09' | 'Remove stale references in skill-creator (#110)' |
| borg\external\tools\claude-mem | N/A | main | '1341e93f' | '2026-01-28' | 'chore: update plugin context' |
| borg\external\tools\incidentfox | N/A | main | '01993a9' | '2026-02-02' | 'Merge pull request #237 from incidentfox/chiehmin... |
| borg\external\tools\theme-context | N/A | main | '1fff8a3' | '2026-01-25' | 'Use collapsible sections for IDE setup instructio... |
| borg\external\tools\tokentap | N/A | main | '80e6e2a' | '2026-02-02' | 'Merge pull request #12 from gclayburg/fix/argpass... |
| borg\external\ui\openwork | N/A | dev | '29b70f8' | '2026-02-03' | 'ignore: update download stats 2026-02-03' |
| borg\external\unsorted\Auditor | N/A | main | 'b4948ab8' | '2026-01-23' | 'Sherlocked twice... lol... Watch this pivot.' |
| borg\external\unsorted\CLIProxyAPIPlus | N/A | main | '91841a55' | '2026-02-10' | 'Merge branch 'router-for-me:main' into main' |
| borg\external\unsorted\Charm | N/A | main | '748ad0a' | '2026-02-01' | 'doc: ui-protocol' |
| borg\external\unsorted\Chatterbox-TTS-Server | N/A | main | '86567ea' | '2025-12-20' | 'Update Dockerfile for PyTorch and dependencies' |
| borg\external\unsorted\CodeMachine-CLI | N/A | main | '7443670' | '2025-12-29' | 'feat(bmad): add critical rule for document handli... |
| borg\external\unsorted\ComfyUI-LTXVideo | N/A | master | '49add6d' | '2026-01-29' | 'Merge pull request #398 from Lightricks/pr-2026-0... |
| borg\external\unsorted\Crystalline-Protocol | N/A | main | 'e4ac987' | '2026-01-14' | 'Enhance README with project badges and links' |
| borg\external\unsorted\Droid-CLI-Orchestrator | N/A | main | '26828bc' | '2025-10-19' | '- orchestrator now is a command. - orchestrator j... |
| borg\external\unsorted\LLM-Providers | N/A | main | '550cbfb' | '2026-02-02' | 'optimize' |
| borg\external\unsorted\LLMRouter | N/A | main | 'e467838' | '2026-01-17' | 'Merge pull request #149 from ulab-uiuc/fix-KNNMul... |
| borg\external\unsorted\Lean | N/A | master | '31e247689' | '2026-01-30' | 'Allow specifying PositionSize wolverine order pro... |
| borg\external\unsorted\LlamaFactory | N/A | main | 'b53d7037' | '2026-02-02' | '[model] support youtu-vl model (#10152)' |
| borg\external\unsorted\Lynkr | N/A | main | '616cc7d' | '2026-02-02' | 'Update README.md' |
| borg\external\unsorted\MCP-Checklists | N/A | main | '0323ce0' | '2025-10-23' | 'Update reported-vulnerability-index.md' |
| borg\external\unsorted\MCP-Zero | N/A | master | 'fd666c4' | '2025-07-02' | '[fix] update filename' |
| borg\external\unsorted\MES-replacement | N/A | main | 'd7eaaac' | '2026-01-30' | 'Step 2: Added mkdir, cp, chmod and rm #3' |
| borg\external\unsorted\Mole | N/A | main | 'c6e58c4' | '2026-02-02' | 'fix: replace clear with clear_screen for better c... |
| borg\external\unsorted\Mr.-Ranedeer-AI-Tutor | N/A | main | 'ea29bcf' | '2025-09-30' | 'Update README.md' |
| borg\external\unsorted\Mysti | N/A | main | 'ff1b8d4' | '2025-12-28' | 'Merge pull request #7 from a-programmers-programm... |
| borg\external\unsorted\NoteDiscovery | 0.15.4 | main | '8282643' | '2026-02-02' | 'Updated version to 0.15.4' |
| borg\external\unsorted\OmniParser | N/A | master | 'b0d5c9f' | '2025-09-09' | 'Merge pull request #337 from microsoft/ataymano/s... |
| borg\external\unsorted\OpenAgents | 0.7.1 | main | 'b41641c' | '2026-02-02' | 'fix: correct YAML errors and restore missing perm... |
| borg\external\unsorted\OpenBB | N/A | main | '5c8fb349db3' | '2026-01-03' | 'Merge pull request #7297 from OpenBB-finance/rele... |
| borg\external\unsorted\OpenHands | N/A | main | 'b088d4857' | '2026-02-02' | 'Improve batch_get_app_conversations UUID handling... |
| borg\external\unsorted\OpenHands-CLI | N/A | main | '811604f' | '2026-02-02' | 'fix(tui): reset token metrics when creating new c... |
| borg\external\unsorted\Personal_AI_Infrastructure | N/A | main | 'b16d708' | '2026-02-02' | 'chore: update submodules and merge features' |
| borg\external\unsorted\Puzld.ai | N/A | main | 'ccbf0ea' | '2026-01-01' | 'refactor: simplify MCP serve command' |
| borg\external\unsorted\Qwen3 | N/A | main | '7a2f61f' | '2026-01-09' | 'Add LM Studio md file and add link into navigatio... |
| borg\external\unsorted\SpotiFLAC | N/A | main | 'b74dec7' | '2026-01-29' | '.channel and community' |
| borg\external\unsorted\Star_Seeker_mcp | N/A | main | '82cfd8e' | '2026-01-25' | 'Update README with Cursor AI usage instructions' |
| borg\external\unsorted\Super-MCP | N/A | main | 'a417e5c' | '2026-01-28' | 'feat(resources): add MCP resources capability for... |
| borg\external\unsorted\Tess | N/A | dev | 'f7dfc20' | '2026-01-21' | ':bookmark: Bump version to 0.7.0-alpha.15 (#71)' |
| borg\external\unsorted\TidGi-Desktop | N/A | master | 'b82379c5' | '2026-02-02' | 'chore: update submodules and merge features' |
| borg\external\unsorted\Timeseal | N/A | master | '6697afd' | '2025-12-30' | 'docs(README): add table of contents and services ... |
| borg\external\unsorted\TradingAgents | N/A | main | '13b826a' | '2025-10-09' | 'Merge pull request #245 from TauricResearch/feat/... |
| borg\external\unsorted\VideoRAG | N/A | main | 'd186992' | '2026-01-12' | 'Merge pull request #34 from YousefAliUK/main' |
| borg\external\unsorted\Xmas.JS | N/A | master | '08710cc' | '2026-01-19' | 'package loader use vfs' |
| borg\external\unsorted\ableton-mcp | N/A | main | 'e008328' | '2026-01-28' | 'Merge pull request #57 from closestfriend/fix/fas... |
| borg\external\unsorted\ableton-xml-analysis | N/A | dev | '0c02ceb' | '2021-01-24' | 'Added method to save XML files as specifically st... |
| borg\external\unsorted\advanced-tools | N/A | main | '0f0d88c' | '2025-12-23' | 'Update README.md' |
| borg\external\unsorted\agent-of-empires | N/A | main | '0fa377c' | '2026-02-09' | 'Bump version to 0.11.2' |
| borg\external\unsorted\agent-pr-replay | N/A | main | '92c9553' | '2026-01-01' | 'Update warning: clarify API costs (~$4 per --top-... |
| borg\external\unsorted\agentapi | N/A | main | '2ab7a0b' | '2026-01-27' | 'chore: integrate coder/quartz (#175)' |
| borg\external\unsorted\agentexport | N/A | main | 'db91b6e' | '2026-02-01' | 'Release agentexport version 0.3.1' |
| borg\external\unsorted\agentic | N/A | master | '3a39153' | '2025-09-02' | 'docs: update readme with up to date instructions ... |
| borg\external\unsorted\agentic-starter-cli | N/A | main | 'a194c83' | '2026-01-02' | 'vitest and house keeping' |
| borg\external\unsorted\ai-gateway-kit | N/A | main | '8257d99' | '2026-01-02' | '3.0.0' |
| borg\external\unsorted\ai-maestro | N/A | main | 'a770f6a' | '2026-01-30' | 'Merge pull request #143 from 23blocks-OS/feature/... |
| borg\external\unsorted\ai-sdk-provider-opencode-sdk | N/A | main | 'ad6e2bb' | '2026-01-01' | 'Migrate provider to AI SDK v6 (#3)' |
| borg\external\unsorted\alpasim | N/A | main | 'a54a1b5' | '2026-01-07' | 'Follow variable name convention and update transf... |
| borg\external\unsorted\awesome-ai-tools-for-game-dev | N/A | main | 'e9419d8' | '2024-11-19' | 'Merge pull request #11 from mliudev/add-rosebud-a... |
| borg\external\unsorted\awesome-claude-skills | N/A | master | 'e762a98' | '2026-02-05' | 'Merge pull request #127 from sohamganatra/add-com... |
| borg\external\unsorted\awesome-llm-apps | N/A | main | '9529d00' | '2026-02-08' | 'Merge pull request #481 from Shubhamsaboo/ai-nego... |
| borg\external\unsorted\awesome-mcp-servers | N/A | main | 'c73c513' | '2026-02-01' | 'Merge pull request #1790 from jackparnell/main' |
| borg\external\unsorted\awesome-obsidian | N/A | master | 'f5e4b78' | '2023-11-17' | 'merge: pull request #66 from ben-8409/patch-1' |
| borg\external\unsorted\basic-memory | N/A | main | '8072449' | '2026-02-01' | 'chore: Add fast feedback loop tooling (#538)' |
| borg\external\unsorted\bitwig-mcp-server | N/A | main | '120f7a0' | '2025-04-10' | 'chore: update browser indexer and add OSC query t... |
| borg\external\unsorted\bonsai | N/A | master | '1aadf3dd' | '2026-02-02' | 'chore: update submodules and merge features' |
| borg\external\unsorted\boxlite | N/A | main | '92eab3f' | '2026-02-02' | 'chore: save local progress before sync' |
| borg\external\unsorted\brainkernel | N/A | main | 'b528c47' | '2026-01-04' | 'Revise README with new roadmap details' |
| borg\external\unsorted\browser-use | N/A | main | '6abac049' | '2026-02-01' | 'added extraction schema (#4005)' |
| borg\external\unsorted\call-me | N/A | main | 'e46afeb' | '2026-01-09' | 'Merge pull request #17 from ZeframLou/dev' |
| borg\external\unsorted\captive-wifi-tool | N/A | main | '98af9e5' | '2025-12-29' | 'updated flowchart in docs to show new no-route so... |
| borg\external\unsorted\ccrider | N/A | main | '74b9114' | '2026-02-01' | 'Merge feature/fast-import: 3.9x faster imports wi... |
| borg\external\unsorted\claude-bootstrap | N/A | main | 'f0ce3a0' | '2026-02-07' | 'Update README with prominent Agent Teams document... |
| borg\external\unsorted\claude-code-gh-dash | N/A | master | 'a3b5d47' | '2026-01-16' | 'Merge pull request #1 from jakozloski/fix/hook-tr... |
| borg\external\unsorted\claude-code-tools | N/A | main | '72ba02b' | '2026-02-06' | 'fix: voice plugin stale update bug + bump version... |
| borg\external\unsorted\claude-squad | N/A | main | '9d7ca2d' | '2025-12-24' | 'chore: bump version' |
| borg\external\unsorted\claudex | N/A | main | 'f1786b6' | '2026-02-01' | 'Merge pull request #155 from Mng-dev-ai/update-ru... |
| borg\external\unsorted\clifm | N/A | master | '3a9299df' | '2026-02-01' | 'Update the mime.types file' |
| borg\external\unsorted\cocoindex | N/A | main | 'e040f21b' | '2026-02-01' | 'workflow: add release for freethreaded (#1612)' |
| borg\external\unsorted\code-chunk | N/A | main | '9712616' | '2026-01-06' | 'Merge pull request #26 from adam2am/fix/bun-expor... |
| borg\external\unsorted\codex-as-mcp | N/A | main | '51fd20a' | '2025-09-26' | 'Merge pull request #2 from Intelligent-Internet/f... |
| borg\external\unsorted\codex-container | N/A | main | '7a45b9b' | '2025-12-31' | 'cleanup' |
| borg\external\unsorted\codex-kaioken | N/A | main | '22a2c14e' | '2026-01-24' | 'feat: sync plan mode and steering from upstream' |
| borg\external\unsorted\codex-skills | N/A | master | 'cd9f49a' | '2026-01-03' | 'Add Screenshots' |
| borg\external\unsorted\comet-mcp | N/A | main | '6f10c86' | '2026-01-13' | 'feat: Add Windows and WSL support' |
| borg\external\unsorted\computer-use-preview | N/A | main | 'd6b242a' | '2026-01-29' | 'Clarify available models. (#107)' |
| borg\external\unsorted\consult-llm-mcp | N/A | main | '63aa32a' | '2026-01-29' | '1.7.0' |
| borg\external\unsorted\continue | N/A | main | 'ca4497322' | '2026-02-02' | 'Merge pull request #10115 from continuedev/nate/f... |
| borg\external\unsorted\continuous-claude | N/A | main | 'd998bf5' | '2026-01-27' | ':bookmark: Release version v0.21.0' |
| borg\external\unsorted\cosmic-files | N/A | master | '3c46135' | '2026-01-30' | 'Merge pull request #1574 from weblate/weblate-pop... |
| borg\external\unsorted\dev-browser | N/A | main | '66682fb' | '2026-01-05' | 'Add contributing guide' |
| borg\external\unsorted\dify | N/A | main | '491fa9923b' | '2026-02-02' | 'refactor: port api/controllers/console/datasets/d... |
| borg\external\unsorted\documentation | N/A | main | 'd168639' | '2026-01-26' | 'Update README.md' |
| borg\external\unsorted\droid-factory | N/A | main | '834c551' | '2025-10-11' | 'ci: add GitHub Actions workflow to publish to npm... |
| borg\external\unsorted\fcvvdp | N/A | main | '4a6475a' | '2025-12-29' | 'chore: bump version' |
| borg\external\unsorted\gastown | N/A | main | 'e2116bbd' | '2026-02-01' | 'fix(beads): redirect to mayor/rig/.beads when rig... |
| borg\external\unsorted\gemini-cli | N/A | main | '1721ccc' | '2025-07-17' | 'Merge branch 'chux0519:main' into main' |
| borg\external\unsorted\gemini-cli-mcp-openai-bridge | N/A | main | '76c28cc' | '2026-02-10' | 'chore: auto-save uncommitted changes during massi... |
| borg\external\unsorted\gomuxai | N/A | main | '21616de' | '2026-01-23' | '- Update instructions, local dev and agent' |
| borg\external\unsorted\google-jules-mcp | N/A | main | '39b4251' | '2025-12-04' | 'fix: use --ignore-scripts in npm ci to fix TypeSc... |
| borg\external\unsorted\gopher-mcp | N/A | main | 'fa08eb25' | '2026-01-24' | 'make format CPP code to apply clang-format (#163)... |
| borg\external\unsorted\goto | N/A | main | '9a729c8' | '2026-01-19' | 'fix: remove dead find case causing query corrupti... |
| borg\external\unsorted\hello-agents | N/A | main | '6ccd640' | '2026-02-02' | 'adjust the location of kkkano's project' |
| borg\external\unsorted\human-in-the-loop-nlp | N/A | main | '0eee83e' | '2026-01-11' | 'Define post-hoc erasure as a canonical governance... |
| borg\external\unsorted\ii-agent | N/A | main | '682d077' | '2025-08-16' | 'add video installation instruction' |
| borg\external\unsorted\incus-sandbox-sdk | N/A | main | '25054a8' | '2026-01-13' | 'feat: add isb CLI using Stricli' |
| borg\external\unsorted\infinite-chat | N/A | main | 'f7588e3' | '2025-09-09' | 'stuff' |
| borg\external\unsorted\install-mcp | N/A | main | '4221ba8' | '2026-01-20' | 'fix: use jsonc-parser for all JSON config files t... |
| borg\external\unsorted\interface | N/A | main | '809f101' | '2026-02-02' | 'fix circular dependency in SDK build by lazy-load... |
| borg\external\unsorted\interpreter | N/A | main | '325478c' | '2026-01-31' | 'Bump version to 2.17.2 (#223)' |
| borg\external\unsorted\investbuddy-mcp-server | N/A | main | 'f8fea8f' | '2025-12-21' | 'Revise accuracy and features in README.md' |
| borg\external\unsorted\jules-agent-sdk-python | N/A | main | '51685d6' | '2025-10-04' | 'chore: update version to 0.1.1 and remove setup.p... |
| borg\external\unsorted\jules-mcp-server | N/A | main | '5779789' | '2025-10-15' | 'Bump version to 0.1.6 and update Docker workflow ... |
| borg\external\unsorted\julie | N/A | main | '7925bdd' | '2026-01-26' | 'chore: remove julieweb from oss repo' |
| borg\external\unsorted\khoj | N/A | master | '9cbf620e' | '2026-01-06' | 'Retry (with fallback) on Gemini fails with intern... |
| borg\external\unsorted\kreuzberg | N/A | main | 'e68e72f5' | '2026-01-14' | 'chore: bump version to 4.0.6' |
| borg\external\unsorted\langchain | N/A | master | 'ae5b50f37f' | '2026-02-02' | 'test(core): increase `delta_time` for flaky test ... |
| borg\external\unsorted\lar | N/A | main | 'd1f1772' | '2026-02-02' | 'docs: update README and system prompt for v1.3.1 ... |
| borg\external\unsorted\lazy-mcp | N/A | main | 'a9928c8' | '2025-10-15' | 'Merge workflow fix for selective package publishi... |
| borg\external\unsorted\lcpfs | 2026.1.100 | main | '359df2a' | '2026-01-18' | 'Merge pull request #3 from artst3in/remove-pqc' |
| borg\external\unsorted\learn-claude-code | N/A | main | '0e0cb3d' | '2026-02-01' | 'Merge pull request #21 from synix/main' |
| borg\external\unsorted\liballocs | N/A | master | '91e2330' | '2026-02-02' | 'chore: save local progress before sync' |
| borg\external\unsorted\license-generator | N/A | main | '44bd264' | '2026-01-14' | 'Bump inquirer from 13.1.0 to 13.2.0 (#9)' |
| borg\external\unsorted\linggen | N/A | main | '3d89668' | '2026-01-29' | 'linggen init --global' |
| borg\external\unsorted\live | N/A | main | '01b7b07' | '2024-03-25' | 'change error msg' |
| borg\external\unsorted\llm-bridge | N/A | main | 'd648075' | '2025-10-31' | 'Merge pull request #6 from supermemoryai/10-30-up... |
| borg\external\unsorted\llm-council | N/A | master | '92e1fcc' | '2025-11-22' | 'readme tweaks' |
| borg\external\unsorted\logicstamp-context | N/A | main | 'e95a7ed' | '2026-02-09' | 'fix: test flakiness and documentation consistency... |
| borg\external\unsorted\magg | N/A | main | 'c237d4c' | '2025-08-06' | 'Release v0.10.1' |
| borg\external\unsorted\mcp-chat-studio | N/A | main | '53abbfc' | '2026-01-07' | 'style: Fix README formatting' |
| borg\external\unsorted\mcp-cli | N/A | main | 'd2d28bd' | '2026-01-27' | 'Updated package.json URLs' |
| borg\external\unsorted\mcp-reticle | N/A | main | '37b1517' | '2026-01-06' | 'Update README with new design, logo, and wiki lin... |
| borg\external\unsorted\mcp-tui-driver | N/A | main | '6d3eb4c' | '2026-01-12' | 'Update installation command in README' |
| borg\external\unsorted\mcp-tui-server | N/A | main | '6d3eb4c' | '2026-01-12' | 'Update installation command in README' |
| borg\external\unsorted\mcpdir | N/A | main | '4452d1a' | '2026-01-11' | 'feat: disable AI parsing by default in sync workf... |
| borg\external\unsorted\mcphub | N/A | main | 'd3e7e7c' | '2026-01-31' | 'feat: add TDD Bug Resolution Agent for structured... |
| borg\external\unsorted\mcpproxy-go | N/A | main | 'fa9ecf1' | '2026-02-02' | 'docs: update demo video link in README' |
| borg\external\unsorted\mcpr | N/A | main | '1298d44' | '2026-01-12' | 'Add support for Antigravity' |
| borg\external\unsorted\memU | N/A | main | 'ee27d8a' | '2026-02-02' | 'docs: file system in readme (#301)' |
| borg\external\unsorted\memex | N/A | main | 'f56357b' | '2026-02-01' | 'Release memex version 0.2.7' |
| borg\external\unsorted\memos | N/A | main | 'cf0a285e' | '2026-02-02' | 'fix(auth): make PKCE optional for OAuth sign-in (... |
| borg\external\unsorted\memvid | N/A | main | 'df8723a' | '2026-01-29' | 'Merge pull request #188 from 0x-pankaj/feat/vecto... |
| borg\external\unsorted\metube | N/A | master | 'c28ceda' | '2026-02-01' | 'upgrade yt-dlp from 2026.1.29 to 2026.1.31' |
| borg\external\unsorted\misc-text | N/A | main | '685cf70' | '2026-01-06' | 'Create Impact of LLM code generation on programmi... |
| borg\external\unsorted\mux | N/A | main | 'fa2608ad' | '2026-02-02' | 'ðŸ¤– feat: add tray icon + close-to-tray behavior... |
| borg\external\unsorted\mystats | N/A | main | '2ab3dc2' | '2026-02-03' | 'chore: show cloud sync state on sync failure' |
| borg\external\unsorted\nanovg | N/A | master | 'f93799c' | '2023-08-26' | 'Merge pull request #642 from mulle-nat/typofix' |
| borg\external\unsorted\newsnow | N/A | main | '951241b' | '2025-12-27' | 'feat: Add new flag for hot news in Weibo source' |
| borg\external\unsorted\notebooklm-kit | N/A | main | '3ced31e' | '2026-01-14' | 'chore: bump version to 2.2.0' |
| borg\external\unsorted\nuclear | N/A | master | 'd55bd753' | '2025-11-06' | 'Merge pull request #1834 from dim5x/master' |
| borg\external\unsorted\nucleus | N/A | main | '81ed9cf' | '2026-01-29' | 'add ouroboros' |
| borg\external\unsorted\obsidian-releases | N/A | master | '59784c12' | '2026-02-10' | 'Update beta to v1.12.0.' |
| borg\external\unsorted\open-skills | N/A | main | '6480335' | '2026-01-24' | 'Option 2: Opencode with Open-Skills' |
| borg\external\unsorted\open-webui | N/A | main | '2b2635500' | '2026-01-11' | 'Merge pull request #20560 from open-webui/dev' |
| borg\external\unsorted\openchamber | N/A | main | '0ff67e4' | '2026-02-02' | 'release v1.6.3' |
| borg\external\unsorted\opencode-antigravity-auth | N/A | main | '28f46c2' | '2026-02-06' | 'Merge pull request #375 from NoeFabris/opus-4.6' |
| borg\external\unsorted\opencode-dynamic-context-pruning | N/A | master | 'c01cbf2' | '2026-02-10' | 'Merge pull request #376 from Opencode-DCP/dev' |
| borg\external\unsorted\opencode-gemini-auth | N/A | main | '21d87aa' | '2026-01-31' | 'chore: update readme' |
| borg\external\unsorted\opencode-google-antigravity-auth | N/A | main | 'd20188e' | '2026-01-30' | 'chore: release 0.2.15' |
| borg\external\unsorted\opencode-md-table-formatter | N/A | main | '24b7ce2' | '2025-12-09' | 'Revise README by removing examples and updating r... |
| borg\external\unsorted\opencode-morph-fast-apply | N/A | trunk | '4ba0d8f' | '2026-02-04' | 'Revert "docs: add Why section, account signup lin... |
| borg\external\unsorted\opencode-notificator | N/A | main | '07b3a7b' | '2026-02-02' | 'No longer emit notification for subtasks' |
| borg\external\unsorted\opencode-notifier | N/A | main | 'f8ef7b4' | '2026-02-10' | 'feat: add icon support for notifications' |
| borg\external\unsorted\opencode-openai-codex-auth | N/A | main | 'bec2ad6' | '2026-01-09' | 'Release 4.4.0' |
| borg\external\unsorted\opencode-plugin-template | N/A | main | '56cd4ef' | '2026-01-23' | 'wip' |
| borg\external\unsorted\opencode-plugins | N/A | main | 'f65469a' | '2025-09-09' | 'feat(copilot): simplify prompt' |
| borg\external\unsorted\opencode-pty | N/A | main | '6c417c4' | '2026-01-30' | 'chore: release 0.1.5' |
| borg\external\unsorted\opencode-shell-strategy | N/A | trunk | '1f83c6e' | '2026-01-19' | 'Remove version number from Claude reference' |
| borg\external\unsorted\opencode-skillful | N/A | main | '5f5e676' | '2026-02-09' | 'Merge branch 'main' of https://github.com/zenobi-... |
| borg\external\unsorted\opencode-skills | N/A | main | '5579eff' | '2025-12-23' | 'chore(main): release 1.0.0' |
| borg\external\unsorted\opencode-supermemory | N/A | main | 'e315fd3' | '2026-01-29' | 'v2.0.1' |
| borg\external\unsorted\opencode-type-inject | N/A | main | '007b880' | '2026-01-25' | 'chore: version packages (#5)' |
| borg\external\unsorted\opencode-wakatime | N/A | master | 'ff4d9b4' | '2026-02-09' | 'chore(release): 1.2.0 [skip ci]' |
| borg\external\unsorted\opencode-websearch-cited | N/A | main | '65e3267' | '2026-01-10' | 'chore: bump version to v1.2.0' |
| borg\external\unsorted\openevolve | N/A | main | 'ad9c9c1' | '2026-01-28' | 'Make max snapshot artifacts limit configurable (#... |
| borg\external\unsorted\pal-mcp-server | N/A | main | '7afc7c1' | '2025-12-15' | 'chore: sync version to config.py [skip ci]' |
| borg\external\unsorted\pktai | N/A | main | '49704ae' | '2025-08-12' | 'updates to uv.lock' |
| borg\external\unsorted\playwriter | N/A | main | 'ec7ed4e' | '2026-01-31' | 'better getHtml function. keep test ids' |
| borg\external\unsorted\pluggedin-app | N/A | main | '5bc62777' | '2026-01-18' | 'Merge pull request #129 from VeriTeknik/fix/test-... |
| borg\external\unsorted\portal | N/A | main | '5b8bc9a' | '2026-01-22' | 'Merge pull request #25 from skiks/fix/hide-model-... |
| borg\external\unsorted\postiz-app | N/A | main | '6d19fe45' | '2026-02-02' | 'Merge branch 'main' of https://github.com/gitroom... |
| borg\external\unsorted\promptflow | N/A | main | 'a7ff42803' | '2025-12-22' | 'Updated the runtime-change-log.md file (#4074)' |
| borg\external\unsorted\proofloop | N/A | main | '81d460d' | '2026-01-12' | 'test: update finalize summary expectation' |
| borg\external\unsorted\quartz | N/A | v4 | 'ec00a40' | '2026-01-27' | 'chore(deps): bump the production-dependencies gro... |
| borg\external\unsorted\quickadd | N/A | master | 'bccc331' | '2026-02-01' | 'fix: improve choice rename UX' |
| borg\external\unsorted\quivr | N/A | main | '947a78541' | '2025-06-19' | 'fix: add Claude 4 support (#3645)' |
| borg\external\unsorted\ragflow | N/A | main | '2e5a18602' | '2026-02-02' | 'refactor: optimize agent list payload and improve... |
| borg\external\unsorted\reag | N/A | main | 'de230c7' | '2025-02-12' | 'bump version' |
| borg\external\unsorted\refact | N/A | main | '3e63faca1' | '2025-12-23' | 'Merge pull request #849 from smallcloudai/dev' |
| borg\external\unsorted\runtm-coding-agent-runtime-control-plane | N/A | main | '2c607c8' | '2026-01-23' | 'fixed formatting errors' |
| borg\external\unsorted\ryos | N/A | main | '00af4fea' | '2026-02-01' | 'Merge pull request #712 from ryokun6/cursor/admin... |
| borg\external\unsorted\ryot | N/A | main | 'f4250895' | '2026-02-02' | 'chore(browser-extension): rename file' |
| borg\external\unsorted\selfhosted | N/A | master | 'b8fee7f' | '2026-01-15' | 'feat: use terraform for deployment' |
| borg\external\unsorted\showcode | N/A | main | 'a5fdfeb' | '2026-01-25' | 'updated my content.json' |
| borg\external\unsorted\siara | N/A | main | 'd7744bf' | '2026-01-02' | 'Add MIT License to the project' |
| borg\external\unsorted\siyuan | N/A | master | 'd5d10dd41' | '2026-01-26' | ':art: https://github.com/siyuan-note/siyuan/pull/... |
| borg\external\unsorted\skills-supply | N/A | main | '38b54f3' | '2026-01-17' | 'chore(discovery): remove Reddit commands from CLI... |
| borg\external\unsorted\software-agent-sdk | N/A | main | 'eb74fa32' | '2026-02-10' | 'Fix Laminar trace continuation for PR review eval... |
| borg\external\unsorted\sopro | N/A | main | '482c207' | '2026-01-07' | 'Bump version' |
| borg\external\unsorted\stabilize | N/A | main | '0ebcaf4' | '2026-02-02' | 'updating prompt, ready for MCP server' |
| borg\external\unsorted\subtask2 | N/A | main | '92ad854' | '2026-01-30' | '0.3.5' |
| borg\external\unsorted\thesis | N/A | main | 'ff743e0' | '2026-01-14' | 'Redirect to unpack (consolidation)' |
| borg\external\unsorted\ticket | N/A | master | '51fe359' | '2026-01-28' | 'release: v0.3.1' |
| borg\external\unsorted\tintcd | N/A | main | '364c999' | '2025-12-31' | 'Unquote tagline' |
| borg\external\unsorted\trello-mcp-server | N/A | main | '8c0f867' | '2025-04-23' | 'readme' |
| borg\external\unsorted\triton-windowing | N/A | main | '2ba7e95' | '2026-01-02' | 'first commit' |
| borg\external\unsorted\tui4j | N/A | dev | 'e5f6156' | '2026-01-30' | 'Merge pull request #13 from WilliamAGH/dev' |
| borg\external\unsorted\turingmind-code-review | N/A | main | 'e939ab6' | '2026-01-08' | 'Merge pull request #1 from turingmindai/feature/h... |
| borg\external\unsorted\universal-session-viewer | N/A | main | '1b06434' | '2026-01-19' | 'chore: bump version to 2.0.11' |
| borg\external\unsorted\vibe-kanban | N/A | main | 'bd4b78e8' | '2026-02-02' | 'chore: update remote Cargo.lock (#2490)' |
| borg\external\unsorted\vibekit-nextjs-supabase | N/A | main | 'a9c9178' | '2025-07-04' | 'Initial commit from Create Next App' |
| borg\external\unsorted\vibeproxy | N/A | main | '1515dbc' | '2026-02-02' | 'Update appcast.xml for v1.8.73' |
| borg\external\unsorted\vibesbench | N/A | main | 'd46ff16' | '2026-02-01' | 'codegen slot machine' |
| borg\external\unsorted\vibesdk | N/A | main | 'ebe25a6' | '2026-01-12' | 'Merge pull request #298 from cloudflare/nightly' |
| borg\external\unsorted\vibeship-spawner-skills | N/A | main | '70b2e10' | '2026-01-02' | 'Turbocharge error-handling skill to 2,905 lines' |
| borg\external\unsorted\vibora | N/A | main | '13d0371' | '2026-02-02' | 'feat: add master memory file (MEMORY.md) replacin... |
| borg\external\unsorted\video_explainer | N/A | main | '7d28c86' | '2026-02-02' | 'Add --merge-chunks option to automatically concat... |
| borg\external\unsorted\voicemode | N/A | master | 'd272058' | '2026-02-03' | 'docs: Remove incorrect link' |
| borg\external\unsorted\void | N/A | main | '17e7a5b1' | '2026-01-12' | 'Update README.md' |
| borg\external\unsorted\web-check | N/A | master | 'aac6121' | '2026-01-31' | 'Merge pull request #271 from Alearner12/fix/carbo... |
| borg\external\unsorted\webcli | N/A | main | '411e35b' | '2026-01-09' | 'fix' |
| borg\external\unsorted\whatthefile | N/A | main | '7ad7911' | '2024-11-10' | 'update' |
| borg\external\unsorted\wip | N/A | master | '2702b20' | '2026-01-09' | 'chore: bump version to 0.1.12' |
| borg\external\unsorted\witr | N/A | main | 'ce90dd2' | '2026-01-22' | 'Merge pull request #161 from pranshuparmar/depend... |
| borg\external\unsorted\workty | N/A | main | '61cd061' | '2026-02-02' | 'Release v0.3.3' |
| borg\external\unsorted\xpipe | 20.4-1 | master | '0769d219c' | '2026-01-18' | 'Fix NPE for main window post init' |
| borg\external\unsorted\yolobox | N/A | master | '002ed89' | '2026-01-31' | 'fix: strip installMethod from .claude.json when c... |
| borg\external\unsorted\zapret-discord-youtube | N/A | main | '05bd8cf' | '2026-02-07' | 'Upgrade GitHub Actions for Node 24 compatibility ... |
| borg\external\unsorted\zeroshot | N/A | main | 'd8fd7e8' | '2026-01-27' | 'Release (#171)' |
| borg\financial\crypto\awesome-crypto-mcp | N/A | main | '6f3db72' | '2025-03-27' | 'Merge pull request #2 from donbagger/dexpaprika-m... |
| borg\financial\crypto\coingecko-mcp | N/A | main | '29d1d98' | '2025-12-18' | 'release: 2.5.0' |
| borg\financial\crypto\coinstats-mcp | N/A | main | '98dd666' | '2025-08-15' | 'Update README.md' |
| borg\financial\mcp-servers\alpha_vantage_mcp | N/A | main | '59e3c41' | '2026-01-23' | 'Update README.md' |
| borg\financial\mcp-servers\financial-datasets-mcp | N/A | main | '08e7a3d' | '2025-06-05' | 'Update gitignore' |
| borg\financial\mcp-servers\octagon-mcp-server | N/A | main | 'd8f2466' | '2026-02-09' | 'Merge pull request #9 from OctagonAI/progress' |
| borg\financial\trading\ai-hedge-fund | N/A | main | '9adb980' | '2025-12-01' | 'Bump version' |
| borg\financial\trading\trade-agent-mcp | N/A | main | '473fc2c' | '2025-12-15' | 'Update README with new MCP registry link' |
| borg\mcp-servers\ai\consult-llm-mcp | N/A | main | '63aa32a' | '2026-01-29' | '1.7.0' |
| borg\mcp-servers\ai\gemini-mcp-tool | N/A | main | 'ef11fab' | '2025-07-23' | 'Update README.md' |
| borg\mcp-servers\ai\mcp-server-deep-research | N/A | main | '640129a' | '2025-03-25' | 'Update README.md' |
| borg\mcp-servers\ai\mcp-server-gemini | N/A | main | 'd90346a' | '2025-07-14' | 'fix: Remove exposed API key and improve security' |
| borg\mcp-servers\ai\mcp-zen | N/A | main | '60e03b0' | '2025-06-14' | 'Simplify installation - API keys in Claude config... |
| borg\mcp-servers\ai\notebooklm-mcp | N/A | main | '5ba9714' | '2025-12-13' | 'feat: v1.3.7 - Add Tool Profiles, Enhanced Answer... |
| borg\mcp-servers\browser\algonius-browser | N/A | master | 'ae03e6a' | '2025-06-25' | 'feat: update logo' |
| borg\mcp-servers\browser\algonius-browser-2 | N/A | master | 'ae03e6a' | '2025-06-25' | 'feat: update logo' |
| borg\mcp-servers\browser\algonius-browser-3 | N/A | master | 'ae03e6a' | '2025-06-25' | 'feat: update logo' |
| borg\mcp-servers\browser\algonius-browser-4 | N/A | master | 'ae03e6a' | '2025-06-25' | 'feat: update logo' |
| borg\mcp-servers\browser\chrome-devtools-mcp | N/A | main | '482a288' | '2026-02-10' | 'chore: evaluate select_page scenario (#925)' |
| borg\mcp-servers\browser\clickclickclick | N/A | main | '6f18cd8' | '2025-10-05' | 'Update README.md' |
| borg\mcp-servers\browser\computer-control-mcp | N/A | main | '91b8266' | '2026-01-12' | 'fix: handle image read and scaling validation in ... |
| borg\mcp-servers\browser\cua | N/A | main | '1b932bb' | '2026-02-02' | 'Add Docs MCP Server with vector and SQL query cap... |
| borg\mcp-servers\browser\fara | N/A | main | 'f42a7ce' | '2026-02-02' | 'chore: update submodules and merge features' |
| borg\mcp-servers\browser\generalagents-python | N/A | main | 'd36f6a8' | '2025-04-11' | 'Bump version 0.1.1 (#8)' |
| borg\mcp-servers\browser\playwright-mcp | N/A | main | '167abba' | '2026-02-09' | 'chore(extension): remove unused permission (#1383... |
| borg\mcp-servers\browser\spark-mcp | N/A | claude/bytebot-mcp-server-01EeujB7JsCc5NqfrnbWM2oQ | '6b1eb66' | '2025-11-22' | 'Add production-grade ByteBot MCP Server' |
| borg\mcp-servers\financial\Upsonic | N/A | master | '78eada8' | '2026-02-02' | 'feat: add comprehensive benchmark system for perf... |
| borg\mcp-servers\financial\ai-hedge-fund | N/A | main | '06602cb' | '2026-02-02' | 'Add frontier models' |
| borg\mcp-servers\financial\alpha_vantage_mcp | N/A | main | '59e3c41' | '2026-01-23' | 'Update README.md' |
| borg\mcp-servers\financial\binance-mcp-server | N/A | main | '2b6f2b7' | '2026-01-31' | 'update readme' |
| borg\mcp-servers\financial\coingecko-typescript | N/A | main | '29d1d98' | '2025-12-18' | 'release: 2.5.0' |
| borg\mcp-servers\financial\financial-datasets-mcp | N/A | main | '08e7a3d' | '2025-06-05' | 'Update gitignore' |
| borg\mcp-servers\financial\octagon-mcp-server | N/A | main | 'd8f2466' | '2026-02-09' | 'Merge pull request #9 from OctagonAI/progress' |
| borg\mcp-servers\financial\trade-agent-mcp | N/A | main | 'b25f32d' | '2026-02-08' | 'Enhance README with brokerage and crypto support ... |
| borg\mcp-servers\media\youtube-video-summarizer-mcp | N/A | main | '08d1bd2' | '2026-02-01' | 'updated version' |
| borg\mcp-servers\memory\chroma-mcp | N/A | main | '98ff675' | '2025-09-17' | 'chore(GitHub Action): adding container workflow (... |
| borg\mcp-servers\memory\mcp-context-forge | N/A | main | '39b80a19' | '2026-02-10' | 'fix: display error message on UI when removing ad... |
| borg\mcp-servers\memory\mcp-mem0 | N/A | main | '22fb7af' | '2025-04-12' | 'Centering top text in README' |
| borg\mcp-servers\memory\mem0-mcp | N/A | main | 'b53a1f3' | '2025-12-07' | 'Merge pull request #25 from mem0ai/readme_fixes' |
| borg\mcp-servers\memory\vibememo | N/A | main | 'a0a3aea' | '2025-12-05' | 'removed unused files' |
| borg\mcp-servers\misc\chgpt-mcp-bridge | N/A | main | 'd99e46d' | '2025-12-04' | 'fix: fastmcp 2.13 not working, requiring 2.12 for... |
| borg\mcp-servers\misc\wot-mcp | N/A | main | '0a325ac' | '2025-12-17' | 'First release' |
| borg\mcp-servers\misc\wot-mcp-cli | N/A | main | 'dbce3b3' | '2025-12-17' | 'First release' |
| borg\mcp-servers\misc\wot-mcp-examples | N/A | main | '4f7b451' | '2025-12-17' | 'First release' |
| borg\mcp-servers\orchestration\mcp-tool-chainer | N/A | main | '3e385b1' | '2026-01-23' | 'wip' |
| borg\mcp-servers\oversight\vibe-check-mcp-server | N/A | main | '3b94a24' | '2025-11-06' | 'Merge pull request #80 from PV-Bhat/codex/trouble... |
| borg\mcp-servers\search\DesktopCommanderMCP | N/A | main | 'feb2a38' | '2026-02-09' | 'Update README.md' |
| borg\mcp-servers\search\mcp-everything-search | N/A | main | '0d46c1b' | '2025-10-21' | 'Add CLAUDE.md for Claude Code guidance' |
| borg\mcp-servers\search\mindsdb | N/A | main | 'c32f8619a' | '2026-01-28' | 'add images for readme files update (#12151)' |
| borg\mcp-servers\search\sourcerer-mcp | N/A | main | '5839e64' | '2025-11-10' | 'fix: extract class methods for js,py, & ts (#10)' |
| borg\mcp-servers\search\web-search-mcp | N/A | main | 'eeb03f8' | '2025-08-08' | 'Update to tidy README' |
| borg\memory\adapters\adk-js | N/A | main | '6aebd70' | '2026-01-30' | 'Release: v0.3.0 (#107)' |
| borg\memory\mcp-servers\deepcontext-mcp | N/A | main | '8180517' | '2025-09-22' | 'attempt publishing to official MCP registry' |
| borg\memory\mcp-servers\mcp-automem | N/A | main | 'c8b05f7' | '2026-01-26' | 'Feat/claude desktop plugin (#34)' |
| borg\memory\mcp-servers\mcp-memory-service | N/A | main | '14f9ffb' | '2026-02-10' | 'fix(ci): install pytest-benchmark in uvx test (#3... |
| borg\memory\mcp-servers\mcp-servers-official | N/A | main | '70c549b' | '2026-02-09' | 'Merge pull request #3306 from shuklaham/time_doc_... |
| borg\memory\mcp-servers\qdrant-mcp | N/A | master | '860ab93' | '2025-12-10' | 'bump version to 0.8.1 (#99)' |
| borg\memory\mcp-servers\supermemory-mcp | N/A | master | '84f5dc9' | '2025-12-30' | 'Update README.md' |
| borg\memory\plugins\opencode-plugin-simple-memory | N/A | main | '5ac3fb0' | '2025-12-15' | '1.0.2' |
| borg\memory\systems-refs\cognee | N/A | main | '2cef47e0' | '2026-01-31' | 'Added module-level docstrings for memify, graph, ... |
| borg\memory\systems-refs\letta | N/A | main | '65dbd7fd8' | '2026-01-29' | 'chore: bump v0.16.4 (#3168)' |
| borg\memory\systems-refs\txtai | N/A | master | '92461fe' | '2026-01-30' | 'Add support for Agent memory, closes #1016' |
| borg\memory\systems\Claude-Matrix | N/A | main | '5da800c' | '2026-01-29' | 'chore: sync versions to 2.2.1' |
| borg\memory\systems\CodeWeaver | N/A | main | '54225b3' | '2025-12-04' | 'Merge pull request #10 from glebkudr/patch-1' |
| borg\memory\systems\Context-Engine | N/A | main | '2b22d04' | '2025-12-11' | 'feat: Refactor MCP setup logic, add compatibility... |
| borg\memory\systems\Long-Term-Memory-API | N/A | main | '00a7119' | '2025-12-17' | 'fix: Update Stripe API version to 2025-12-15.clov... |
| borg\memory\systems\MemMachine | N/A | main | 'ca2dbf7' | '2026-01-30' | 'fix messages is not filtered by conversation inde... |
| borg\memory\systems\Memori | N/A | main | '87b39b6' | '2026-02-02' | 'Hosted metrics (#299)' |
| borg\memory\systems\MemoryOS | N/A | main | 'd7a5462' | '2025-09-20' | 'Update README.md' |
| borg\memory\systems\Mimir | N/A | main | '01c0203' | '2025-12-25' | 'update chat file' |
| borg\memory\systems\OpenMemory | N/A | main | '30daf78' | '2026-01-27' | 'feat: implement core database, vector store, temp... |
| borg\memory\systems\automem | N/A | main | 'ad9500f' | '2026-01-21' | 'docs: Update API documentation and configuration ... |
| borg\memory\systems\beads | N/A | main | 'c2f3d46e' | '2026-02-02' | 'fix: resolve errcheck violations in cmd/bd/gitlab... |
| borg\memory\systems\beads_viewer | N/A | main | 'e05901b' | '2026-02-01' | 'fix: correct data_source path and exit code in ro... |
| borg\memory\systems\cipher | N/A | main | '8155225' | '2025-12-16' | 'Merge pull request #290 from MahlerTom/bug/sqlite... |
| borg\memory\systems\code-to-tree | N/A | master | '700a234' | '2025-05-17' | 'misc: add license' |
| borg\memory\systems\codebase-context | N/A | master | '10c9c71' | '2026-01-31' | 'Merge pull request #19 from PatrickSys/chore/clea... |
| borg\memory\systems\cognee | N/A | main | '2cef47e' | '2026-01-31' | 'Added module-level docstrings for memify, graph, ... |
| borg\memory\systems\context-portal | N/A | main | '18bde46' | '2026-01-19' | 'Merge pull request #74 from GreatScottyMac/depend... |
| borg\memory\systems\hindsight | N/A | main | '3825506' | '2026-02-02' | 'fix: custom pg schema is not reliable (#278)' |
| borg\memory\systems\jean-memory | N/A | main | 'aac8e74' | '2026-01-06' | 'refactor: Improve deprecation banner and add foot... |
| borg\memory\systems\langmem | N/A | main | '6c1a46c' | '2025-10-27' | 'Update lockfile' |
| borg\memory\systems\letta | N/A | main | '65dbd7f' | '2026-01-29' | 'chore: bump v0.16.4 (#3168)' |
| borg\memory\systems\letta-code | N/A | main | 'b9eaaa1' | '2026-02-02' | 'refactor(cli): unify TUI and headless stream proc... |
| borg\memory\systems\lifecontext | N/A | main | 'fefe70b' | '2025-12-02' | 'Merge branch 'main' into dev' |
| borg\memory\systems\mem0 | N/A | main | '70baa46' | '2026-02-02' | 'fix: add OpenClaw to docs navigation (#3965)' |
| borg\memory\systems\memai | N/A | main | '480552f' | '2026-01-29' | 'Merge pull request #2 from KraftyUX/feature/bulk-... |
| borg\memory\systems\memory-opensource | N/A | main | '558575e' | '2026-02-02' | 'Merge commit 'f6290590562bd475d1dc48c64dee2a6e054... |
| borg\memory\systems\memvault-sync | N/A | main | '81a4a42' | '2025-12-17' | 'fix: update correct readme for marketplace' |
| borg\memory\systems\octocode | N/A | master | '72c7030' | '2026-02-01' | 'fix(indexer): guarantee forward progress in text ... |
| borg\memory\systems\pieces-cli-agent | N/A | main | '78a752d' | '2026-01-18' | 'Merge pull request #437 from SiddharthaSree/feat/... |
| borg\memory\systems\probe | N/A | main | 'b6055b2' | '2026-02-02' | 'feat: Forward MCP tools to delegate sessions (#37... |
| borg\memory\systems\redplanethq-core | N/A | main | 'c52be4e' | '2026-02-03' | 'bump: new version 0.3.1' |
| borg\memory\systems\roampal-core | N/A | main | 'd8984e1' | '2026-01-27' | 'v0.3.1: Reserved working memory slot for context ... |
| borg\memory\systems\sem-mem | N/A | main | '5178c14' | '2026-01-09' | 'license updates' |
| borg\memory\systems\serena | N/A | main | '764f26f' | '2026-02-01' | 'Merge pull request #982 from oraios/ls-completion... |
| borg\memory\systems\supermemory | N/A | main | 'b7e6eb6' | '2026-01-31' | 'langchain integration (#718)' |
| borg\memory\systems\txtai | N/A | master | '92461fe' | '2026-01-30' | 'Add support for Agent memory, closes #1016' |
| borg\memory\systems\zep | N/A | main | '4f170ca' | '2026-02-01' | 'Add ElevenLabs Zep example with React frontend an... |
| borg\memory\vector-stores\pgvector | N/A | master | '35ab919' | '2026-01-21' | 'Switched to statically-allocated IndexAmRoutine f... |
| borg\misc\abanteai\gpt-generals | N/A | main | '2c7ba3a' | '2025-03-14' | 'Merge pull request #120 from AbanteAI/mentat-119-... |
| borg\misc\abanteai\mentat-template-js | N/A | main | '299953c' | '2025-08-01' | 'change order of preview windows' |
| borg\misc\abanteai\party | N/A | main | '1b0a381' | '2025-10-08' | 'update readme' |
| borg\misc\abanteai\repo-visualizer | N/A | main | '460b9ca' | '2025-07-29' | 'Merge pull request #75 from AbanteAI/mentat-64' |
| borg\misc\abanteai\spice | N/A | main | '395a594' | '2024-09-27' | 'Merge pull request #115 from AbanteAI/version-0.4... |
| borg\misc\abanteai\tiktoken | N/A | main | '08f9f69' | '2025-03-21' | 'Merge pull request #2 from AbanteAI/mentat-script... |
| borg\misc\abanteai\vscode | N/A | main | '8bb9840' | '2025-06-16' | 'Merge pull request #251658 from microsoft/tyriar/... |
| borg\misc\abanteai\websocket-demo | N/A | main | '4ec4e9c' | '2025-06-17' | 'initial commit - working demo of websocket forwar... |
| borg\misc\gemini-extensions\cloud-run-mcp | N/A | main | '623ef98' | '2026-02-09' | 'Merge branch 'main' of https://github.com/GoogleC... |
| borg\misc\gemini-extensions\firebase | N/A | main | '997151b' | '2025-10-13' | 'Add IS_GEMINI_CLI_EXTENSION env variable (#6)' |
| borg\misc\gemini-extensions\workspace | N/A | main | '4f12520' | '2026-01-29' | 'chore: add prettier to CI and project configurati... |
| borg\packages\skills\claude-code-tips | N/A | main | '4203f53' | '2026-02-19' | 'Document native installer corruption when other v... |
| borg\packages\skills\gemini-claude-skills | N/A | main | '0a31cfe' | '2026-01-14' | 'Add image input support to Nano Banana Pro skill' |
| borg\packages\skills\skills | N/A | main | '0e6288b' | '2026-01-22' | 'Add commit navigation shortcuts to config' |
| borg\reference\agent-ui\copilotkit | N/A | main | 'fd9935047' | '2026-02-02' | 'Update asset link in README.md' |
| borg\reference\browser\puppeteer | N/A | main | 'f4c9feef997' | '2026-02-02' | 'feat: pluggable browser providers (#14552)' |
| borg\reference\cli\aider | N/A | main | '4bf56b77' | '2026-01-19' | 'Merge pull request #4772 from markmcd/sdk-depro' |
| borg\reference\cli\codebuff | N/A | main | 'd512e726e' | '2026-02-02' | 'Delete best practicese page that had no new info' |
| borg\reference\cli\codex | N/A | main | 'cbfd2a37c' | '2026-02-02' | 'Trim compaction input (#10374)' |
| borg\reference\cli\crush | N/A | main | 'b7e814a3' | '2026-02-02' | 'chore(legal): @acmacalister has signed the CLA' |
| borg\reference\cli\goose | N/A | main | 'ca7a99a11' | '2026-02-03' | 'docs: update MCP Apps blog post terminology and a... |
| borg\reference\cli\opencode | N/A | dev | '34384659f' | '2026-02-02' | 'ci: add license to npm (#11883)' |
| borg\reference\cli\plandex | N/A | main | 'e2d77207' | '2025-10-03' | 'link to cloud wind down post' |
| borg\reference\context\beads | N/A | main | 'ed71a9ab' | '2026-02-02' | 'fix: remove unused source return value from getGi... |
| borg\reference\indexing\serena | N/A | main | '4dab291' | '2026-02-02' | 'Merge pull request #985 from oraios/lazy-open-fil... |
| borg\reference\mcp\mcp-tool-chainer | N/A | main | '84ab853' | '2025-08-04' | 'Update README.md' |
| borg\reference\mcp\metamcp | 3.2.18 | main | 'c7ed2d8' | '2026-02-02' | 'chore: update submodules and merge features' |
| borg\reference\memory\letta | N/A | main | '65dbd7fd8' | '2026-01-29' | 'chore: bump v0.16.4 (#3168)' |
| borg\reference\memory\mem0 | N/A | main | '70baa46c' | '2026-02-02' | 'fix: add OpenClaw to docs navigation (#3965)' |
| borg\reference\memory\supermemory | N/A | main | '16da766f' | '2026-02-03' | 'langgraph integration (#719)' |
| borg\reference\memory\zep | N/A | main | '4f170ca' | '2026-02-01' | 'Add ElevenLabs Zep example with React frontend an... |
| borg\reference\orchestration\crewai | N/A | main | '7590d4c6' | '2026-02-02' | 'fix: enforce additionalProperties=false in schema... |
| borg\reference\orchestration\langgraph | N/A | main | '82f9c09b' | '2026-01-31' | 'chore(deps-dev): bump ruff from 0.14.7 to 0.14.11... |
| borg\reference\protocols\a2a | N/A | main | '6292104' | '2026-01-29' | 'fix(spec): Added clarification on timestamps in H... |
| borg\reference\sandbox\e2b | N/A | main | '99b7d8c' | '2026-01-07' | 'Bump the pip group across 2 directories with 2 up... |
| borg\search\mcp-servers\web-search-mcp | N/A | main | 'eeb03f8' | '2025-08-08' | 'Update to tidy README' |
| borg\skills\external\ensue-skill | N/A | main | '876ba4f' | '2026-01-28' | 'Merge remote-tracking branch 'refs/remotes/origin... |
| borg\skills\prompts\anthropic-quickstarts | N/A | main | '4b2549e' | '2026-02-05' | 'Update computer-use-demo to use text_editor_20250... |
| borg\skills\refs\skills-bkircher | N/A | main | '9fe323a' | '2026-01-28' | 'unit-testing skill: refine a bit' |
| borg\submodules\jules-app\jules-sdk-reference | N/A | main | '51685d6' | '2025-10-04' | 'chore: update version to 0.1.1 and remove setup.p... |
| borg\superai-cli\agents\crewai | N/A | main | '96bde45' | '2026-02-02' | 'feat: auto update tools.specs (#4341)' |
| borg\superai-cli\agents\langgraph | N/A | main | '82f9c09' | '2026-01-31' | 'chore(deps-dev): bump ruff from 0.14.7 to 0.14.11... |
| borg\superai-cli\agents\openhands | N/A | main | 'b088d48' | '2026-02-02' | 'Improve batch_get_app_conversations UUID handling... |
| borg\superai-cli\clis-refs\fabric | N/A | main | '9ab45a25' | '2026-01-31' | 'chore(release): Update version to v1.4.397' |
| borg\superai-cli\clis-refs\gemini-cli | N/A | main | 'c5d0fc2c3' | '2026-02-02' | 'Docs: Revise docs/index.md (#17879)' |
| borg\superai-cli\clis-refs\goose | N/A | main | 'a9f4b2d637' | '2026-02-02' | 'Remove dependency on goose-mcp from goose crate (... |
| borg\superai-cli\clis-refs\grok-cli | N/A | main | 'ad177ec' | '2025-11-27' | 'Support global custom instructions from ~/.grok/G... |
| borg\superai-cli\clis-refs\kilocode | N/A | main | '7f8db21fcc' | '2026-02-02' | 'Merge branch 'main' of https://github.com/Kilo-Or... |
| borg\superai-cli\clis\CodeNomad | N/A | dev | 'ba0898b' | '2026-02-02' | 'Merge branch 'main' into dev' |
| borg\superai-cli\clis\claude-code-madapp | N/A | main | 'bea99ea' | '2026-02-04' | 'docs: update CLAUDE.md for dev plugin v1.29.0' |
| borg\superai-cli\clis\codebuff | N/A | main | 'a6da1f4' | '2026-02-02' | 'Dedicated privacy page' |
| borg\superai-cli\clis\codex-kaioken | N/A | main | '22a2c14e' | '2026-01-24' | 'feat: sync plan mode and steering from upstream' |
| borg\superai-cli\clis\kimi-cli | N/A | main | '9e87547' | '2026-02-03' | 'chore: bump version to 1.6 (#862)' |
| borg\superai-cli\extensions\gemini-superclaude-mcp-server | N/A | main | '05f2d99' | '2025-09-07' | 'Update README.md' |
| borg\superai-cli\harnesses\SuperClaude_Framework | 4.2.0 | master | 'ad6b2e9' | '2026-01-18' | 'docs: update version references and fix CHANGELOG... |
| borg\superai-cli\mcp-advanced\anthropic-tools | N/A | main | '795f706' | '2024-11-04' | 'Merge pull request #30 from anthropics/deprecatio... |
| borg\superai-cli\mcp-advanced\awesome-mcp-servers | N/A | main | 'c73c513' | '2026-02-01' | 'Merge pull request #1790 from jackparnell/main' |
| borg\superai-cli\mcp-advanced\mcp-servers | N/A | main | '70c549b' | '2026-02-09' | 'Merge pull request #3306 from shuklaham/time_doc_... |
| borg\superai-cli\proxies\ccproxy | N/A | main | '4d977b3' | '2026-02-01' | 'Update README.md' |
| borg\superai-cli\proxies\gemini-openai-proxy-2 | N/A | main | '0e0e9ba' | '2025-12-30' | 'ðŸš¨ Commit Build Artifact from GitHub Actions' |
| borg\superai-cli\proxies\gemini-openai-proxy-zhu | N/A | main | '1e54746' | '2025-10-07' | 'Update gemini library to supported sdk (#61)' |
| borg\superai-cli\proxies\gemini-openai-proxy-zuisong | N/A | main | '0e0e9ba' | '2025-12-30' | 'ðŸš¨ Commit Build Artifact from GitHub Actions' |
| borg\superai-cli\proxies\openai-gemini | N/A | main | '61a83bd' | '2025-12-22' | 'Update Vercel regions' |
| borg\superai-cli\proxies\openai-gemini-2 | N/A | main | '61a83bd' | '2025-12-22' | 'Update Vercel regions' |
| borg\superai-cli\proxies\vercel-ai-proxy | N/A | main | '976cab0' | '2024-11-21' | 'feat: support xai' |
| borg\superai-cli\routers\GoogleGeminiRouter | N/A | master | 'bbd9b59' | '2025-08-11' | 'updated readme file' |
| borg\superai-cli\routers\gemini-cli-router | N/A | main | '5cbeed4' | '2025-07-21' | 'feat: add status display showing current port, mo... |
| borg\superai-cli\routers\gemini-router | N/A | main | '1c38c5e' | '2025-09-20' | 'chore: gitignore' |
| borg\superai-cli\tools\Lynkr | N/A | main | '616cc7d' | '2026-02-02' | 'Update README.md' |
| borg\superai-cli\tools\cc-switch | N/A | main | 'f0e8ba1' | '2026-02-02' | 'feat: session manger (#867)' |
| borg\superai-cli\tools\cc-switch-cli | N/A | main | '1716975' | '2026-02-02' | 'chore(release): v4.5.0' |
| borg\superai-cli\tools\ccs | N/A | main | 'be63056' | '2026-02-01' | 'chore(release): 7.34.0 [skip ci]' |
| borg\superai-cli\tools\code-assistant-manager | N/A | main | '51b49e9' | '2026-01-27' | 'Merge pull request #47 from zhujian0805/main' |
| borg\superai-cli\tools\convx | N/A | main | '4acf3a0' | '2025-08-21' | 'Add export functionality and OpenTUI dialog impro... |
| borg\superai-cli\tools\cupcake | N/A | main | '9ea25f2' | '2026-01-16' | 'chore: bump version to 0.5.2' |
| borg\superai-cli\tools\gomuxai | N/A | main | '21616de' | '2026-01-23' | '- Update instructions, local dev and agent' |
| borg\superai-cli\tools\lunaroute | N/A | main | '4e3eafe' | '2025-11-25' | 'Merge pull request #23 from erans/feature/provide... |
| borg\superai-cli\tools\occtx | N/A | main | '8546933' | '2025-09-19' | 'feat(workflows): add trigger for Homebrew tap upd... |
| borg\superai-cli\tools\poe-code | N/A | main | 'a643660' | '2026-02-08' | 'chore: auto-commit local changes' |
| borg\superai-cli\tools\splitrail | N/A | main | '7a07e94' | '2026-01-30' | 'v3.3.1 (#109)' |
| borg\tools\github\claude-code-gh-dash | N/A | master | 'a3b5d47' | '2026-01-16' | 'Merge pull request #1 from jakozloski/fix/hook-tr... |
| borg\tools\misc\vibeship-idearater | N/A | main | '4341772' | '2026-01-01' | 'Add Vibeship logo as favicon' |
| borg\tools\refs\pluggedin-app | N/A | main | '5bc62777' | '2026-01-18' | 'Merge pull request #129 from VeriTeknik/fix/test-... |
| borg\tools\security\claude-code-safety-net | N/A | main | '82f676b' | '2026-02-02' | 'docs: remove gemini hooks configuration as it is ... |
| borg\tools\security\vibeship-scanner | N/A | main | '3f8f073' | '2026-01-17' | 'Simplify MCP install to clean command bar' |
| mk64\tools\blender\fast64 | N/A | main | 'fc9a191' | '2026-02-24' | 'Merge branch 'main' of https://github.com/Fast-64... |
| superbobbyball\f-zerox\tools\asm-differ | N/A |  |  |  |  |
| superbobbyball\f-zerox\tools\asm-processor | N/A |  |  |  |  |
| superbobbyball\f-zerox\tools\ido5.3_cc | N/A |  |  |  |  |
| superbobbyball\f-zerox\tools\splat | N/A |  |  |  |  |
| Tickerstone\Tickerstone.Backend\third_party\roq-api\cmake | N/A | master | 'b376037' | '2026-02-21' | 'chore: save progress before update' |
| Tickerstone\Tickerstone.Backend\third_party\roq-api\scripts | N/A | master | 'f6cd9e0' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\laf | N/A | main | '71822c3' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\OpenRV\src\pub | N/A | main | 'b851325' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\bobmania\itgmania\Themes\Simply-Love-SM5 | N/A | itgmania-release | '1650b880' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\bobmania\itgmania\extern\IXWebSocket | N/A | master | 'f6f9dd4' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\bobmania\itgmania\extern\ffmpeg | N/A | master | '4bf8039ca8' | '2026-02-21' | 'Merge branch 'master' of https://github.com/FFmpe... |
| bobmani\bobmania\itgmania\extern\hidapi | N/A | master | '444b506' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\bobmania\itgmania\extern\libjpeg-turbo | N/A | main | '8552ddf5' | '2026-02-21' | 'Merge branch 'main' of https://github.com/libjpeg... |
| bobmani\bobmania\itgmania\extern\libpng | N/A | libpng18 | '41e831e1a' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\bobmania\itgmania\extern\libtomcrypt | N/A | develop | 'e7f32b7' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\bobmania\itgmania\extern\libtommath | N/A | develop | 'e533b14' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\bobmania\itgmania\extern\libusb | N/A | main | '753d0e9' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\bobmania\itgmania\extern\mbedtls | N/A | development | '5c5266c' | '2026-02-17' | 'chore: save progress' |
| bobmani\bobmania\itgmania\extern\ogg | N/A | main | 'a682b88' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\bobmania\itgmania\extern\vorbis | N/A | main | '656e3b4' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\ksm-v2\kshootmania\ThirdParty\CoTaskLib | N/A | master | 'e180a16' | '2026-02-21' | 'chore: save progress before update' |
| bobmani\ksm-v2\kshootmania\ThirdParty\NocoUI | N/A | master | 'f4248bc' | '2026-02-21' | 'chore: save progress before update' |
| borg\.borg\worktrees\chore\index-inbox-links | 2.6.0 | chore/index-inbox-links | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\external\computer-use\fara\autogen | N/A | main | '13e144e54' | '2025-10-04' | 'fix: order by clause (#7051)' |
| borg\external\forks\bkircher\skills | N/A | main | '9fe323a' | '2026-01-28' | 'unit-testing skill: refine a bit' |
| borg\external\forks\finmap-org\mcp-server | N/A | main | '18e11d7' | '2026-02-09' | 'Release v2.0.0' |
| borg\external\forks\paperinvest\mcp-server | N/A | main | 'd4ac588' | '2025-09-18' | 'Merge pull request #2 from paperinvest/docs/mcp-r... |
| borg\external\forks\zhifac\gemini-cli-router | N/A | main | 'e7883de' | '2025-07-20' | 'Initial commit' |
| borg\external\plugins\vibeship\vibeship-plugin | N/A | main | '4fd0772' | '2025-12-30' | 'Add /vibeship-init command, enhance error UX, add... |
| borg\external\skills\dotfiles\nvim | N/A | main | '9dabbb1' | '2026-02-01' | 'update' |
| borg\external\skills\dotfiles\tmux | N/A | main | '3f61527' | '2026-01-08' | 'fix: increase right hand side of status bar' |
| borg\external\skills_repos\vibeship\vibeship-spawner-skills | N/A | main | '70b2e10' | '2026-01-02' | 'Turbocharge error-handling skill to 2,905 lines' |
| borg\external\unsorted\gemini-cli-mcp-openai-bridge\gemini-cli | N/A | main | 'f9fc9335f' | '2026-02-10' | 'Code review cleanup for thinking display (#18720)... |
| borg\mcp-servers\browser\fara\autogen | N/A | main | '13e144e54' | '2025-10-04' | 'fix: order by clause (#7051)' |
| borg\multi-agent\metamcp-robertpelloni\submodules\mcpdir | N/A | main | '4452d1a' | '2026-01-11' | 'feat: disable AI parsing by default in sync workf... |
| borg\packages\mcp-directory\general\awesome-ai-apps | N/A | main | '955655e' | '2026-02-07' | 'Merge pull request #122 from kantorcodes/add-agen... |
| borg\packages\mcp-directory\general\awesome-mcp-servers | N/A | main | '187929a' | '2025-09-04' | 'Added Vulert into README.md (#165)' |
| borg\packages\mcp-directory\general\toolsdk-mcp-registry | N/A | main | '760a4401' | '2026-01-27' | 'npm @toolsdk.ai/registry released - 1.0.154' |
| borg\packages\mcp-directory\orchestration\blog.md | N/A | main | '0e69c81' | '2025-03-17' | 'Update README.md' |
| borg\packages\mcp-directory\orchestration\metamcp | 3.7.0 | main | 'cf46a38' | '2026-02-19' | 'chore: update submodules and merge fix/detached-h... |
| borg\submodules\jules-app\external\antigravity-jules-orchestration | N/A | main | 'e12e5a1' | '2026-01-08' | 'test: fix memory integration test isolation issue... |
| borg\submodules\jules-app\external\gemini-cli-jules | N/A | main | '9f2fc14' | '2025-10-30' | 'Merge pull request #4 from Smetalo/Smetalo-patch-... |
| borg\submodules\jules-app\external\google-jules-mcp | N/A | main | '39b4251' | '2025-12-04' | 'fix: use --ignore-scripts in npm ci to fix TypeSc... |
| borg\submodules\jules-app\external\jules-action | N/A | main | 'bff7875' | '2025-12-13' | 'Merge pull request #2 from google-labs-code/s/upd... |
| borg\submodules\jules-app\external\jules-awesome-list | N/A | main | '0118486' | '2025-05-20' | 'Merge pull request #2 from sntgchns/main' |
| borg\submodules\jules-app\external\jules-mcp-server | N/A | main | '5779789' | '2025-10-15' | 'Bump version to 0.1.6 and update Docker workflow ... |
| borg\submodules\jules-app\external\jules-system-prompt | N/A | add-details-md | 'de4a2bf' | '2025-12-08' | 'Merge pull request #4 from DiaAviLinden/feature/r... |
| borg\submodules\jules-app\external\jules-task-queue | N/A | main | 'f11d2ad' | '2025-12-14' | 'Merge pull request #163 from iHildy/iHildy-patch-... |
| borg\submodules\jules-app\external\jules_mcp | N/A | main | 'db11576' | '2025-10-04' | 'Add .npmignore, update package.json with metadata... |
| bg\bobsgameonlinejava\libs\lz4-java\src\lz4 | N/A | dev | '1aae9402' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\LibreSprite\src\flic | N/A | main | 'bd83c80' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\LibreSprite\third_party\duktape | N/A | master | 'e7c72a1' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\LibreSprite\third_party\simpleini | N/A | aseprite | '35a140e' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\PixiEditor\src\ColorPicker | N/A | master | 'ec83a46' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\PixiEditor\src\Drawie | N/A | main | 'fe4dc76' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\PixiEditor\src\PixiDocks | N/A | main | '60bd4cd' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\PixiEditor\src\PixiParser | N/A | master | '0bd8106' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\laf\clip | N/A | main | '2126d24' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\src\flic | N/A | main | '1cf97b7' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\src\observable | N/A | main | 'f654c89' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\src\psd | N/A | main | '379d9cb' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\src\tga | N/A | main | '58cbb5f' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\src\undo | N/A | main | 'df28321' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\IXWebSocket | N/A | aseprite | '89c9209' | '2023-08-29' | 'Fix finding zlib library so we can use zlibstatic... |
| bg\bobsgameonlinejava\references\aseprite\third_party\TinyEXIF | N/A | aseprite | 'd515f0d' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\benchmark | N/A | main | 'b1b0798' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\cityhash | N/A | aseprite | '2d44742' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\cmark | N/A | master | 'dcbea94' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\curl | N/A | master | '1bf7b6368' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\fmt | N/A | master | '76d6c751' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\freetype2 | N/A | master | '0fc990593' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\giflib | N/A | master | '3cecfec' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\harfbuzz | N/A | aseprite | '0c190aa08' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\json11 | N/A | aseprite | '69ae915' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\libarchive | N/A | aseprite | '65836611' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\libpng | N/A | aseprite | '72145e983' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\libwebp | N/A | main | 'd5734225' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\lua | N/A | aseprite | 'b2cc1ad6' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\pixman | N/A | master | 'e221a85' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\qoi | N/A | master | '0c82f2d' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\simpleini | N/A | aseprite | '630f8d9' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\tinyexpr | N/A | aseprite | '6ada1f0' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\tinyxml2 | N/A | master | 'e7687e9' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\aseprite\third_party\zlib | N/A | master | '1f2f3f6' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\grafx2\tests\pic-samples | N/A | pic-samples | 'd8924d3' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\ai-file-sorter\app\include\external\llama.cpp | N/A | master | '40e669993' | '2026-02-21' | 'Merge branch 'master' of https://github.com/ggerg... |
| bobfilez\libs\OpenTimelineIO\src\deps\Imath | N/A | main | '97977e6' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\OpenTimelineIO\src\deps\pybind11 | N/A | master | '1eb92be3' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\OpenTimelineIO\src\deps\rapidjson | N/A | master | 'd2b77291' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\dokany\samples\dokan_memfs\spdlog | N/A | v1.x | '8e007923' | '2026-02-21' | 'Merge branch 'v1.x' of https://github.com/gabime/... |
| borg\external\unsorted\TidGi-Desktop\template\wiki | N/A | master | '80ecfba' | '2026-02-01' | 'Automated Update all Library in libraries.json' |
| borg\external\unsorted\bonsai\external\bonsai_debug | N/A | master | '6ce5fb8' | '2025-11-28' | 'Silence warning' |
| borg\external\unsorted\bonsai\external\bonsai_stdlib | N/A | master | 'bf76eeb' | '2025-12-30' | 'Add Eps in Normalize' |
| borg\external\unsorted\liballocs\contrib\cil | N/A | develop | 'dc23d260' | '2026-02-02' | 'Merge branch 'master' into develop' |
| borg\external\unsorted\liballocs\contrib\donald | N/A | master | '7129b44' | '2020-09-21' | 'Fix a subtle load bug, and make us a bit more gen... |
| borg\external\unsorted\liballocs\contrib\elftin | N/A | master | '9d4467d' | '2026-02-02' | 'chore: update submodules and merge features' |
| borg\external\unsorted\liballocs\contrib\liballocstool | N/A | master | '61a64bd' | '2026-01-14' | 'Tidy up frame_element cases, and tentatively hand... |
| borg\external\unsorted\liballocs\contrib\libdlbind | N/A | master | 'c6fb65f' | '2026-02-02' | 'chore: update submodules and merge features' |
| borg\external\unsorted\liballocs\contrib\libmallochooks | N/A | master | 'b34e29b' | '2025-11-15' | 'More sanity about symbol prefixing, and treat mal... |
| borg\external\unsorted\liballocs\contrib\libsystrap | N/A | master | '9937ecb' | '2026-02-02' | 'chore: update submodules and merge features' |
| borg\external\unsorted\liballocs\contrib\toolsub | N/A | master | '4f5c5e8' | '2025-09-29' | 'wrapper: some more manual additions for clang and... |
| borg\multi-agent\metamcp-robertpelloni\submodules\mcp-directories\awesome-ai-apps | N/A | main | '955655e' | '2026-02-07' | 'Merge pull request #122 from kantorcodes/add-agen... |
| borg\multi-agent\metamcp-robertpelloni\submodules\mcp-directories\awesome-mcp-servers-appcypher | N/A | main | '187929a' | '2025-09-04' | 'Added Vulert into README.md (#165)' |
| borg\multi-agent\metamcp-robertpelloni\submodules\mcp-directories\awesome-mcp-servers-punkpeye | N/A | main | 'c73c513' | '2026-02-01' | 'Merge pull request #1790 from jackparnell/main' |
| borg\multi-agent\metamcp-robertpelloni\submodules\mcp-directories\awesome-mcp-servers-wong2 | N/A | main | 'a4316c7' | '2025-12-17' | 'Update readme' |
| borg\multi-agent\metamcp-robertpelloni\submodules\mcp-directories\mcp-official-servers | N/A | main | '70c549b' | '2026-02-09' | 'Merge pull request #3306 from shuklaham/time_doc_... |
| borg\multi-agent\metamcp-robertpelloni\submodules\mcp-directories\toolsdk-mcp-registry | N/A | main | '760a4401' | '2026-01-27' | 'npm @toolsdk.ai/registry released - 1.0.154' |
| borg\packages\cli\.borg\worktrees\integration-prep | 2.6.0 | integration-prep | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\security-feature-integration | 2.6.0 | security-feature-integration | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\security-features | 2.6.0 | security-features | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\security-review-feature | 2.6.0 | security-review-feature | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\task-1770681933847-APPROVEDv | 2.6.0 | task/task-1770681933847-APPROVEDv | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\submodules\opencode-autopilot\memory\projects\claude-mem | N/A | main | 'a59ff73f' | '2026-02-08' | 'chore: merge feat/mcp-phase-2 (resolved conflicts... |
| borg\submodules\opencode-autopilot\superai-cli\cli-tools\cc-switch | N/A | main | 'e349012' | '2026-02-09' | 'docs: add Right Code as sponsor across all README... |
| borg\submodules\opencode-autopilot\superai-cli\cli-tools\ccs | N/A | main | '7ceb019' | '2026-02-07' | 'chore(release): 7.40.0 [skip ci]' |
| borg\submodules\opencode-autopilot\superai-cli\cli-tools\claude-code | N/A | main | '19bb071' | '2026-02-10' | 'chore: Update CHANGELOG.md' |
| borg\submodules\opencode-autopilot\superai-cli\cli-tools\claude-squad | N/A | main | 'fc1b967' | '2025-11-21' | 'fix: Sanitize final branch name to handle invalid... |
| borg\submodules\opencode-autopilot\superai-cli\cli-tools\code-assistant-manager | N/A | main | '51b49e9' | '2026-01-27' | 'Merge pull request #47 from zhujian0805/main' |
| borg\submodules\opencode-autopilot\superai-cli\cli-tools\code-nomad | N/A | dev | '0e755b7' | '2026-02-09' | 'fix(ui): exclude routes from service worker cache... |
| borg\submodules\opencode-autopilot\superai-cli\cli-tools\emdash | N/A | heads/main | '8ce8228' | '2025-12-10' | 'Merge pull request #448 from generalaction/fix-st... |
| borg\submodules\opencode-autopilot\superai-cli\cli-tools\lynkr | N/A | main | 'edaeed5' | '2026-02-11' | 'Fixed semantic caching in codex' |
| borg\submodules\opencode-autopilot\superai-cli\cli-tools\madappgang-claude-code | N/A | main | 'bea99ea' | '2026-02-04' | 'docs: update CLAUDE.md for dev plugin v1.29.0' |
| borg\submodules\opencode-autopilot\superai-cli\proxies\gemini-openai-proxy-zhu | N/A | main | '1e54746' | '2025-10-07' | 'Update gemini library to supported sdk (#61)' |
| borg\submodules\opencode-autopilot\superai-cli\proxies\openai-gemini | N/A | main | '61a83bd' | '2025-12-22' | 'Update Vercel regions' |
| borg\submodules\opencode-autopilot\superai-cli\routers\claude-code-router | N/A | main | 'c73fe0d' | '2026-01-10' | 'add posts' |
| borg\superai-cli\clis-refs\kilocode\deps\vscode | N/A | main | '2050e3c2c3c' | '2026-02-10' | 'Terminal: update auto replies configuration (#294... |
| bg\bobsgameonlinejava\references\aseprite\laf\third_party\googletest | N/A | main | 'a8ec48e5' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\grafx2\tools\8x8fonts\font8x8 | N/A | master | 'a23596d' | '2026-02-21' | 'chore: save progress before update' |
| bg\okgame\lib\CLove\src\3rdparty\microui | N/A | master | '9fddfab' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\OpenRV\src\lib\files\WFObj | N/A | main | '51ad9e3' | '2026-02-21' | 'chore: save progress before update' |
| borg\packages\cli\.borg\worktrees\feat\top-features | 1.5.1 | feat/top-features | '2dfcf638' | '2026-02-09' | 'chore: auto-save uncommitted changes during massi... |
| borg\packages\cli\.borg\worktrees\feat\top_features | 2.6.0 | feat/top_features | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\analyze-enhancements | 2.6.0 | feature/analyze-enhancements | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\analyze-features | 2.6.0 | feature/analyze-features | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\approval | 2.6.0 | feature/approval | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\architecture | 2.6.0 | feature/architecture | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\architecture-review | 2.6.0 | feature/architecture-review | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\audit | 2.6.0 | feature/audit | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\audit-protocol | 2.6.0 | feature/audit-protocol | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\audit-update | 2.6.0 | feature/audit-update | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\audit_protocol | 2.6.0 | feature/audit_protocol | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\backlog_review | 2.6.0 | feature/backlog_review | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\compliance | 2.6.0 | feature/compliance | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\engagement-analysis | 2.6.0 | feature/engagement-analysis | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\feature-enhancements | 2.6.0 | feature/feature-enhancements | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\login | 2.6.0 | feature/login | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\performance-analysis | 2.6.0 | feature/performance-analysis | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\refactor | 2.6.0 | feature/refactor | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\roadmap-alignment | 2.6.0 | feature/roadmap-alignment | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\roadmap-review | 2.6.0 | feature/roadmap-review | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\scalability | 2.6.0 | feature/scalability | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\security | 2.6.0 | feature/security | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\security-audit | 2.6.0 | feature/security-audit | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\security-review | 2.6.0 | feature/security-review | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\top-features | 2.6.0 | feature/top-features | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\ui-activation | 2.6.0 | feature/ui-activation | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\ui-features | 2.6.0 | feature/ui-features | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\user-impact | 2.6.0 | feature/user-impact | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\user-interface | 2.6.0 | feature/user-interface | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\user_engagement_analysis | 2.6.0 | feature/user_engagement_analysis | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\validate-backlog | 2.6.0 | feature/validate-backlog | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\validate-features | 2.6.0 | feature/validate-features | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\validate-pain-points | 2.6.0 | feature/validate-pain-points | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| borg\packages\cli\.borg\worktrees\feature\validate-painpoints | 2.6.0 | feature/validate-painpoints | 'f5e57ac2' | '2026-02-09' | 'fix(core): break circular dependencies by using i... |
| bg\bobsgameonlinejava\references\aseprite\third_party\freetype2\subprojects\dlg | N/A | master | 'bf99cab' | '2026-02-21' | 'chore: save progress before update' |
| bg\bobsgameonlinejava\references\retro-game-editor\app\internal-apps\js-sms\jsSMS | N/A | master | '82088c8' | '2026-02-21' | 'chore: save progress before update' |
| bobfilez\libs\OpenTimelineIO\src\deps\rapidjson\thirdparty\gtest | N/A | main | '1baeda35' | '2026-02-21' | 'chore: save progress before update' |
| borg\external\unsorted\liballocs\contrib\elftin\contrib\librunt | N/A | master | 'fe167de' | '2025-09-25' | 'Add fake_dladdr_with_cache(), which does not mall... |
| borg\external\unsorted\liballocs\contrib\elftin\contrib\libsrk31c++ | N/A | master | '3a5e029' | '2025-11-18' | 'Merge pull request #3 from difcsi/fix-oob' |
| borg\external\unsorted\liballocs\contrib\liballocstool\contrib\dwarfidl | N/A | master | 'a04b422' | '2026-01-14' | 'Update libdwarfpp submodule' |
| borg\external\unsorted\liballocs\contrib\libdlbind\example\libsystrap | N/A | master | 'fec1172' | '2026-02-02' | 'chore: update submodules and merge features' |
| borg\external\unsorted\liballocs\contrib\libsystrap\contrib\donald | N/A | master | '7129b44' | '2020-09-21' | 'Fix a subtle load bug, and make us a bit more gen... |
| borg\external\unsorted\liballocs\contrib\libsystrap\contrib\librunt | N/A | master | 'fe167de' | '2025-09-25' | 'Add fake_dladdr_with_cache(), which does not mall... |
| borg\external\unsorted\liballocs\contrib\libsystrap\contrib\libx86emulate | N/A | decode-only-extended | 'c029b2e' | '2025-01-30' | 'x86_defs.h: make saw_operand() arg types for from... |
| borg\external\unsorted\liballocs\contrib\libsystrap\contrib\musl | 1.2.5 | master | '1b76ff07' | '2025-10-12' | 's390x: shuffle register usage in __tls_get_offset... |
| borg\external\unsorted\liballocs\contrib\libsystrap\contrib\xed | v2025.12.14 | main | '95ca7183' | '2025-12-15' | 'External Release v2025.12.14' |
| borg\external\unsorted\boxlite\boxlite\deps\e2fsprogs-sys\vendor\e2fsprogs | N/A | master | '0b2752ce' | '2025-11-11' | 'mke2fs: fix memory leak which causes ASAN to comp... |
| borg\external\unsorted\boxlite\boxlite\deps\libkrun-sys\vendor\libkrun | N/A | main | 'fbb860a' | '2025-12-19' | 'nitro: improve console support' |
| borg\external\unsorted\boxlite\boxlite\deps\libkrun-sys\vendor\libkrunfw | N/A | main | '20484a2' | '2025-12-16' | 'ci: split up release publish jobs' |
| borg\external\unsorted\liballocs\contrib\liballocstool\contrib\dwarfidl\contrib\libantlr3c++ | N/A | master | 'a3914cc' | '2024-09-11' | 'parser.hpp: use rvalue refs to treat temporary os... |
| borg\external\unsorted\liballocs\contrib\liballocstool\contrib\dwarfidl\contrib\libcxxgen | N/A | master | 'bfdabd9' | '2023-06-29' | 'cxx_compiler.cpp: track multiple equivalent base ... |
| borg\external\unsorted\liballocs\contrib\liballocstool\contrib\dwarfidl\contrib\libdwarfpp | N/A | master | '3e60380' | '2026-01-14' | 'Merge' |
| borg\external\unsorted\liballocs\contrib\liballocstool\contrib\dwarfidl\contrib\m4ntlr | N/A | master | '0b9c1bd' | '2020-12-15' | 'test_parser.c.m4: report error in exit status' |
| borg\external\unsorted\liballocs\contrib\libdlbind\example\libsystrap\contrib\donald | N/A | master | '7129b44' | '2020-09-21' | 'Fix a subtle load bug, and make us a bit more gen... |
| borg\external\unsorted\liballocs\contrib\libdlbind\example\libsystrap\contrib\librunt | N/A | master | 'fe167de' | '2025-09-25' | 'Add fake_dladdr_with_cache(), which does not mall... |
| borg\external\unsorted\liballocs\contrib\libdlbind\example\libsystrap\contrib\libx86emulate | N/A | decode-only-extended | 'c029b2e' | '2025-01-30' | 'x86_defs.h: make saw_operand() arg types for from... |
| borg\external\unsorted\liballocs\contrib\libdlbind\example\libsystrap\contrib\musl | 1.2.5 | master | '1b76ff07' | '2025-10-12' | 's390x: shuffle register usage in __tls_get_offset... |
| borg\external\unsorted\liballocs\contrib\libdlbind\example\libsystrap\contrib\xed | v2025.12.14 | main | '95ca7183' | '2025-12-15' | 'External Release v2025.12.14' |
| borg\external\unsorted\liballocs\contrib\liballocstool\contrib\dwarfidl\contrib\libdwarfpp\contrib\libc++fileno | N/A | master | 'ca4b2a0' | '2019-08-06' | 'Merge branch 'master' of git://github.com/stephen... |
| borg\external\unsorted\liballocs\contrib\liballocstool\contrib\dwarfidl\contrib\libdwarfpp\contrib\libdwarf | N/A | master | '5c15be2' | '2017-12-22' | 'dwarf_init_finish.c: make zlib sanity checks even... |
| borg\external\unsorted\liballocs\contrib\liballocstool\contrib\dwarfidl\contrib\libdwarfpp\contrib\libsrk31c++ | N/A | master | '3a5e029' | '2025-11-18' | 'Merge pull request #3 from difcsi/fix-oob' |
