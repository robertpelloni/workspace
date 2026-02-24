# Omni-Workspace Roadmap

## Current State: Phase 1 — "Federated Synchronization" (Complete)
*   **Recursive Submodule Updator (`update_repos_v3.py`):** Achieved robust synchronization across all 100+ nested repositories.
*   **Upstream Syncing:** Implemented reliable, automated `fetch` and `merge` logic for forks tracking `upstream`.
*   **Feature Branch Merging:** Developed intelligent detection and bidirectional merging (`sync_and_merge.py`) for local/remote feature branches into `main`, and `main` back into feature branches, resolving basic conflicts.
*   **Documentation Architecture:** Created `docs/UNIVERSAL_LLM_INSTRUCTIONS.md` as the single source of truth for all LLMs in the root folder, completely overhauling `GEMINI.md`, `CLAUDE.md`, etc.
*   **Dashboarding:** `SUBMODULE_DASHBOARD.md` redesigned to include directory structure explanations alongside version tracking.

## Next Phase: Phase 2 — "Intelligent Propagation"
*   **Universal Instructions Propagation Script:** A script to automatically push or synchronize `docs/UNIVERSAL_LLM_INSTRUCTIONS.md` to all submodule `docs/` directories (where applicable) to ensure unified agent behavior throughout the entire tree. (Completed)
*   **Global CI/CD Dashboard:** Expand `SUBMODULE_DASHBOARD.md` to track the build/test status of each major project (e.g., pulling GitHub Actions status). Detailed dashboard now covers all submodules, their versions, dates, and locations.
*   **Conflict Resolution Sub-Agent:** A specialized routine within `update_repos.py` to invoke an LLM API to attempt to resolve "unrelated histories" or complex merge conflicts autonomously, rather than just aborting. Added `intelligent_sync_all.py` for auto-resolving local and remote feature branches, prioritizing progress retention.

## Future Phase: Phase 3 — "Omniscient Orchestration"
*   **Workspace Search API:** Implement a local vector or full-text search API that indexes all 100+ repos, allowing an LLM in the root to rapidly locate specific code patterns across isolated projects without relying purely on `grep`.
*   **Cross-Submodule Dependency Graph:** Map which projects depend on others within this workspace to orchestrate multi-repo builds in the correct topological order.
