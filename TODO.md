# Omni-Workspace TODOs

## Urgent Tasks (Short-Term)
* [ ] **Automated Mapping Cleanup:** Create a script to prune dead or broken submodule paths (`fatal: no submodule mapping found`) from `.gitmodules` globally.
* [ ] **Dead Link Cleanup:** Remove or re-link missing repositories (e.g., `rental.home.admin-website`, `CLove`) currently failing `git fetch`.
* [ ] **Upstream Resolution:** Investigate `topaz-ffmpeg` and `claude-mem` to resolve their complex "unrelated histories" without losing local features.

## Backlog Tasks (Medium-Term)
* [x] **Universal Propagation:** Implement a script to inject `docs/UNIVERSAL_LLM_INSTRUCTIONS.md` to all submodules. (Completed in v1.3.1)
* [x] **Submodule Audit:** Perform a holistic health audit and refresh the dashboard. (Completed in v1.3.2)
* [x] **Bidirectional Synchronization:** Implement `sync_and_merge.py` for intelligent multi-repo feature branch integration. (Completed in v1.3.3)
* [x] **Deep Submodule Synchronization & Feature Merge:** Intelligently merged all local feature branches (including those by AI tools) into main, updated upstream forks, and ensured clean repo states globally without losing features. (Completed in v1.3.4)
* [x] **Comprehensive Dashboard:** Generated a complete submodule dashboard listing all versions and directory structures. (Completed in v1.3.4)
* [ ] Add automated build checks (`make`, `npm build`, `cargo build`) to `update_repos_v3.py` to immediately notify the user if a merged feature branch breaks compilation.
* [ ] Integrate a global `git fetch --all --tags` command into the synchronization pipeline to capture release tags across all 100+ projects.
* [ ] Set up a unified `pytest` or `jest` suite at the root (or in a dedicated `/tests` submodule) to validate the integration between the most critical projects.
