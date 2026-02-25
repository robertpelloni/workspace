# Submodule Dashboard & Project Structure

## Project Directory Structure Explanation
This monorepo serves as a unified workspace and orchestrator for dozens of independent microservices, libraries, desktop applications, and AI agents.
*   **Root/**: Contains the global orchestration scripts (sync_and_merge.py, intelligent_sync_all.py), universal documentation (LLM_INSTRUCTIONS.md, ROADMAP.md), and the workspace-level package.json / configuration files.
*   **.gemini/, .claude/, etc.**: AI agent configuration and context directories managing instructions and local extensions for LLMs.
*   **AI Agent Projects**: Folders like org, metamcp, jules-autopilot, ntigravity-autopilot, mcp-superassistant contain specialized multi-modal and autonomous agents leveraging MCP (Model Context Protocol).
*   **Full-Stack Apps**: Folders like Chamber.Law, cointrade, obeditpro, obfilez contain entire standalone full-stack applications with their own submodules.
*   **Shared Libraries**: Other directories include shared utilities and libraries nested across the ecosystem.

## Submodule Status & Versions

| Path | Commit Hash | Branch/Status |
| :--- | :--- | :--- |
| .agent | c2caafe280dd71b5b806a7e6f8c92701f47b468f | (v5.7.0-39-gc2caafe) |
| Alti.Assistant | cbf85e392458798312c5fcfb40d713f74ffcfd72 | (heads/backend-branch) |
| Alti.Assistant/Alti.Assistant.Backend | 1e0f9a0cdd024c200fc76c05ca1a78c6452698f1 | (heads/main) |
| Alti.Assistant/Alti.Assistant.Frontend | 7bae366547551729e012d46dba51f83cb28ce497 | (heads/main) |
| Alti.Assistant/external/CopilotKit | 945d2556f990731f48aa24fd534d86a50ee84c52 | (v1.51.4-41-g945d2556f) |
| Alti.Assistant/external/a2a | 0661bdadeb9bd7c59ecf7d1087eba2f64960c20f | (heads/main) |
| Alti.Assistant/external/agui | 654f0a7e8dac2d742283c67eb055f6388d62115f | (heads/main) |
| Alti.Assistant/external/google-adk | 8a49c335198bcb2b17fc267315264d36fd48021d | (heads/main) |
| Alti.Code.Studio | f1acac03849c1808353867b564d09763bfa6eabd | (heads/main) |
| Alti.Code.Studio/alti.code.studio.backend | 2d45a2aa297e9baed6f4e977afd28719469f3e7b | (heads/main-5-g2d45a2a) |
| Alti.Code.Studio/alti.code.studio.frontend | ed720d542d110c356357e60d32fefafe8a5d5df4 | (heads/main-3-ged720d5) |
| Alti.Code.Studio/background-agents | 35a615dcb339d2328fce92e8acf4d56e464de94e | (35a615d) |
| Alti.Code.Studio/submodules/12-factor-agents | d20c728368bf9c189d6d7aab704744decb6ec0cc | (heads/main) |
| Alti.Code.Studio/submodules/fossflow | 8f307cdf96cdb71d50c81a3311d0c9076c81c9dd | (v1.10.7-3-g8f307cd) |
| Alti.Code.Studio/submodules/langflow | f44e2b31a4eae2b43cf612cec1fdae745af6997f | (1.8.0.rc2-16-gf44e2b31a4) |
| Alti.Code.Studio/submodules/next-devtools-mcp | 8840ce34d4d586e93a8d788da0dbedd0d74c3c82 | (v0.3.10-2-g8840ce3) |
| Alti.Code.Studio/submodules/openclaw/.github | d1e99e594a985958aa2daf25d2cfc3cdc9db94a9 | (heads/main) |
| Alti.Code.Studio/submodules/openclaw/barnacle | c16f6203f6bfac0ddebc22693dc31b39d9cb86c8 | (heads/main) |
| Alti.Code.Studio/submodules/openclaw/butter.bot | d96c348fbf2b46f86ee4cdfba17a36fba7beb9a0 | (heads/main) |
| Alti.Code.Studio/submodules/openclaw/casa | 66d84d91c272debe7dcb006bdb43a97af1acc9e9 | (heads/main) |
| Alti.Code.Studio/submodules/openclaw/clawdinators | 4a40ae24e26a2626573d68ad598dd3d35eac5e18 | (heads/main) |
| Alti.Code.Studio/submodules/openclaw/clawgo | 36d4909cbd34d3e786ce9da200d30fb2b3b9bea9 | (heads/main) |
| Alti.Code.Studio/submodules/openclaw/clawhub | f4f8e7276fc462cf5fe90d17ded47d8f3dffd872 | (v0.6.1-127-gf4f8e72) |
| Alti.Code.Studio/submodules/openclaw/flawd-bot | 9d9655a68122ff5536e2b41a765b1235e4249bb3 | (heads/main) |
| Alti.Code.Studio/submodules/openclaw/homebrew-tap | b498a624380bde076fa1b222c596a40a11313d34 | (heads/main) |
| Alti.Code.Studio/submodules/openclaw/lobster | 61218be5679709ea47471f213c0dcefe8079ddd5 | (heads/main) |
| Alti.Code.Studio/submodules/openclaw/maintainers | 01bc4087977e1a1682de0f177298dec231b1c98d | (heads/main) |
| Alti.Code.Studio/submodules/openclaw/nix-openclaw | fbef2087190ccfca375b351cdaad49bcbaea721a | (v2.0.0-beta5-809-gfbef208) |
| Alti.Code.Studio/submodules/openclaw/nix-steipete-tools | 95ebfa73f4421144173f7060433c510a7d2d014a | (heads/main) |
| Alti.Code.Studio/submodules/openclaw/openclaw | f8524ec77a3999d573e6c6b8a5055bf35c49a2e6 | (v2026.2.12-4842-gf8524ec77) |
| Alti.Code.Studio/submodules/openclaw/openclaw-ansible | 862ab49e7f7127ab21748ca27e5b10bca5a207c7 | (v2.0.0-32-g862ab49) |
| Alti.Code.Studio/submodules/openclaw/openclaw.ai | ee7180fcc0ac48ef9ca9dff1c4cd447bd10a2414 | (heads/main) |
| Alti.Code.Studio/submodules/openclaw/skills | 88b9a58c396b77e235309e19ef83d6532235ec7e | (heads/main) |
| Alti.Code.Studio/submodules/openclaw/trust | eee55ba2f4ab8263d52d8eef46605cf24363bfd6 | (heads/main) |
| Alti.Code.Studio/submodules/pentagi | 763cb170f0b14cfd5971f26bd64c88413e2d147f | (v1.1.0-32-g763cb17) |
| Azure.Cybersecurity | e5693ca4139e91c438eda72507ad87a4f033acb4 | (heads/main) |
| Calling-AI-Agent-Backend | 4dbba404e312c61b7e8a0751301dd4bd6eb248b4 | (heads/main) |
| Chamber.Law | fe450c0520964262d56a27d545f2f38d4d2ec3bd | (remotes/origin/main) |
| Chamber.Law/Chamber.Law.Backend | 472079d2174e4d429faf6e9e567a5a558a16b820 | (remotes/chamberlaw/HEAD-17-g472079d) |
| Chamber.Law/Chamber.Law.Desktop | b2a1aa0e613018a35edefdef4d07f6a0ca9e65a9 | (heads/main) |
| Chamber.Law/Chamber.Law.Frontend | +1f6ef6ac14ae150802da62301fec3c15eb896620 | (heads/main) |
| Chamber.Law/Tabular_Review | a15689825f5d3679ea19769311023b2ed872da4a | (heads/main) |
| Merk.Mobile | 2aeb554f76ebdf916fa078c15a7889eac14f97db | (heads/main) |
| Merk.Mobile/Merk.Mobile.Backend | e243d825fd6e679a1fb4a24458a6c9fc35479627 | (heads/main) |
| Merk.Mobile/Merk.Mobile.Frontend | d82189dd4aad6ff67b6fbf7e33e6d9f9fafd7b17 | (heads/main) |
| Merk.Mobile/merk.mobile.flutter | 6a53d9f0dd56e1535d3ce431f74fa65d2a3fe4d8 | (heads/main) |
| Merk.Mobile/merk.mobile.website | b9b369003d05d5b1db581f4acba613a0aa32ee30 | (heads/master) |
| Snaype | d26928261ec455e66c71316bf632fcebcc84999d | (heads/main) |
| Snaype/Snaype.Backend | -36df5597ea38f04fe629402a6e7d187262fa45b5 |  |
| Snaype/Snaype.Frontend | -1d92e436c9ce2577f54abac8691ac5657c8a32d0 |  |
| Stone.Ledger | fb24b00a52492f5cdbfa6feaf36fea3aab3f0354 | (heads/master) |
| Tickerstone | f2f61aa7abf07d07d896465d8041e284b31c5899 | (heads/master) |
| Tickerstone/Tickerstone.Backend | df90e8c67119da79fa92be801f236bf477712ca3 | (heads/main) |
| Tickerstone/Tickerstone.Backend/third_party/fmt | +b14a68db12774fa23eb2c3fe76de4d1ff6f6f323 | (12.1.0-109-gb14a68db) |
| Tickerstone/Tickerstone.Backend/third_party/magic_enum | ae4cff77d5aa19a57e018bf24cb54c621b326e29 | (v0.9.7-41-gae4cff7) |
| Tickerstone/Tickerstone.Backend/third_party/nameof | 0485ad728e386c2b9d8414fe19ee185373147c43 | (v0.10.4-4-g0485ad7) |
| Tickerstone/Tickerstone.Backend/third_party/roq-api | 339c02518a16f8b5cbd933e5a17e355f1ecfd07b | (1.1.2-4-g339c0251) |
| Tickerstone/Tickerstone.Backend/third_party/roq-api/cmake | b37603797fd47307242c1be7af91b6d7a7292f6a | (1.1.2-1-gb376037) |
| Tickerstone/Tickerstone.Backend/third_party/roq-api/scripts | f6cd9e0e1db38d7305d8020eb7f74b5e8208d7d9 | (1.1.2-1-gf6cd9e0) |
| Tickerstone/Tickerstone.Frontend | 400032aac8919f3e45652920c0041c14b07ea64b | (heads/main) |
| antigravity-autopilot | +4c19c01475fd11691be2221463be14ea6c22960f | (v5.2.9-259-g4c19c01) |