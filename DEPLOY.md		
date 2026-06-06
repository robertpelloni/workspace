# Omni-Workspace Deployment & Maintenance Strategy

## 1. The Global Update Loop
To deploy or maintain the full suite of 100+ nested repositories, execute the python synchronization script.

```bash
# Clear previous logs
del processed_repos_v3.txt
del failed_repos_v3.log

# Run the recursive synchronization
python update_repos_v3.py
```

### What `update_repos_v3.py` Does:
1.  Recursively maps all submodules and sub-submodules.
2.  Checks out the default branch (`main`, `master`, etc.).
3.  Pulls origin changes.
4.  Fetches and merges `upstream` changes (if it's a fork).
5.  Merges all local feature branches into the default branch (aborting on severe conflicts or unrelated histories to prevent data loss).
6.  Pushes updated `robertpelloni` repositories to their origins.

## 2. Dashboard Generation
After syncing, you MUST regenerate the dashboard to reflect the new state:
```bash
python scripts/generate_dashboard.py
```

## 3. Root Commit
Finally, stage the submodule pointer changes and the dashboard, then commit with the new version number referenced in `VERSION`.
```bash
git add .
git commit -m "chore: bump version and sync all submodules"
git push origin main
```
