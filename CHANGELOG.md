# Changelog

## [v5.99.1] — 2026-07-04 — Protocol #78

### Changed

- **tormentnexus**: Pi extension v3 deployed — 9 custom tools (tn_memory_store/search/vector, tn_tool_search, tn_session_search, tn_skill_manage, tn_code_search, tn_context_harvest, tn_scratchpad) + 6 automatic event hooks (session priming, context injection, per-turn harvesting, compaction enrichment, auto-logging, session cleanup)
- **tormentnexus**: AGENTS.md, README.md ports corrected from legacy (3000/3001/4100/4300) to current (7778/7779)
- **tormentnexus**: install_services.bat now installs pi extension during setup
- **tormentnexus**: .gitignore updated to track .pi/extensions/
- **Root**: Memory state sync and log compaction
