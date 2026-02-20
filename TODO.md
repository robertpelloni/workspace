# Omni-Workspace TODOs

## Urgent Tasks (Short-Term)
* [ ] **Submodule Cleanup:** Investigate and fix the missing submodule mapping for `AUTO-ALL-AntiGravity` in `antigravity-autopilot`.
* [ ] **Dead Link Cleanup:** Remove or re-link missing repositories (e.g., `rental.home.admin-website`, `CLove`) currently failing `git fetch`.
* [ ] **Upstream Resolution:** Investigate `topaz-ffmpeg` and `claude-mem` to resolve their complex "unrelated histories" without losing local features.

## Backlog Tasks (Medium-Term)
* [x] **Universal Propagation:** Implement a script to inject `docs/UNIVERSAL_LLM_INSTRUCTIONS.md` to all submodules. (Completed in v1.3.1)
* [ ] Add automated build checks (`make`, `npm build`, `cargo build`) to `update_repos_v3.py` to immediately notify the user if a merged feature branch breaks compilation.
* [ ] Integrate a global `git fetch --all --tags` command into the synchronization pipeline to capture release tags across all 100+ projects.
* [ ] Set up a unified `pytest` or `jest` suite at the root (or in a dedicated `/tests` submodule) to validate the integration between the most critical projects.
