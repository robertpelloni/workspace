# Omni-Workspace TODOs

## Urgent Tasks (Short-Term)
* [ ] **Script Refinement:** Update `scripts/generate_dashboard.py` to also read the specific branch checked out for each submodule.
* [ ] **Dead Link Cleanup:** Remove or re-link missing repositories (e.g., `rental.home.admin-website`, `CLove`) currently failing `git fetch`.
* [ ] **Upstream Resolution:** Investigate `topaz-ffmpeg` and `claude-mem` to resolve their complex "unrelated histories" without losing local features.
* [ ] **Universal Propagation:** Create a script (`scripts/propagate_instructions.py`) to inject or symlink the new `docs/UNIVERSAL_LLM_INSTRUCTIONS.md` to the `docs/` folder of all active submodules.

## Backlog Tasks (Medium-Term)
* [ ] Add automated build checks (`make`, `npm build`, `cargo build`) to `update_repos_v3.py` to immediately notify the user if a merged feature branch breaks compilation.
* [ ] Integrate a global `git fetch --all --tags` command into the synchronization pipeline to capture release tags across all 100+ projects.
* [ ] Set up a unified `pytest` or `jest` suite at the root (or in a dedicated `/tests` submodule) to validate the integration between the most critical projects.
