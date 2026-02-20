# Workspace Memories

*   **Submodule Resilience:** The biggest bottleneck is detached HEADs and dirty worktrees in nested submodules (e.g., `.borg` artifacts in `Alti.Code.Studio`). Future scripts must be aggressive about cleaning untracked files before submodule updates.
*   **Git LFS Limits:** Large binary files (e.g., `antigravity-autopilot.7z`) can block pushes for the entire workspace. Always check file sizes or exclude archives before committing root changes.
*   **API Security:** Repositories like `metamcp` often have hardcoded secrets in their history from previous automated commits. Interactive rebasing or squash-merging is essential to purge these before pushing to GitHub.
*   **Unrelated Histories:** Many automated feature branches have completely divergent commit graphs from their upstream parents. Blind merging is dangerous; the current strategy of aborting these merges is correct.
