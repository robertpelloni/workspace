# Omni-Workspace TODOs

## Urgent Tasks (Short-Term)
* [ ] **Automated Mapping Cleanup:** Create a script to prune dead or broken submodule paths (`fatal: no submodule mapping found`) from `.gitmodules` globally.
* [ ] **Dead Link Cleanup:** Remove or re-link missing repositories (e.g., `rental.home.admin-website`, `CLove`) currently failing `git fetch`.
* [ ] **Upstream Resolution:** Investigate `topaz-ffmpeg` and `claude-mem` to resolve their complex "unrelated histories" without losing local features.

## Backlog Tasks (Medium-Term)
* [x] **Universal Propagation:** Implement a script to inject `docs/UNIVERSAL_LLM_INSTRUCTIONS.md` to all submodules. (Completed in v1.3.1)
* [x] **Submodule Audit:** Perform a holistic health audit and refresh the dashboard. (Completed in v1.3.2)
* [x] **Bidirectional Synchronization:** Implement `sync_and_merge.py` for intelligent multi-repo feature branch integration. (Completed in v1.3.3)
* [x] **Deep Submodule Synchronization & Feature Merge:** Intelligently merged all local feature branches into main. (Completed in v1.3.4)
* [x] **Comprehensive Dashboard:** Generated a complete submodule dashboard listing all versions. (Completed in v1.3.4)
* [x] **Synchronization Hardening:** Integrated global `git fetch --all --tags` into the pipeline. (Completed in v1.3.7)
* [x] **Live Health Monitoring:** Implemented `scripts/health_check.py` and enhanced the mission control dashboard. (Completed in v1.3.8)
* [ ] Add automated build checks (`make`, `npm build`, `cargo build`) to `update_repos_v6.py` using the detected build systems from `workspace_graph.json`.
* [ ] Integrate a workspace-wide search API or indexing service for "needle-in-a-haystack" analysis.
* [ ] Set up a unified `pytest` or `jest` suite at the root to validate integration between the most critical projects.
