#!/usr/bin/env python3
"""Protocol #286 phase 2: commit genuine dirty files, FF stale defaults, merge deferred features, -X theirs retry for conflicts."""
import subprocess, json
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")
SKIP_REPOS = {"openclaw-config", "HyperNexus2old", "HyperNexus", "unitedbeats_site"}
SKIP_BRANCH_SUBSTR = ["heads/upstream/", "upstream/", "gh-pages", "cloud-dashboard-mcp-sse", "dependabot"]

def run(cmd, cwd, timeout=180):
    try:
        p = subprocess.run(cmd, cwd=str(cwd), capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, (p.stdout or "") + (p.stderr or "")
    except Exception as e:
        return -2, f"TIMEOUT {e}"

def gitlink_paths(path):
    rc, out = run("git ls-files -s", path, 30)
    links = set()
    for line in out.splitlines():
        parts = line.split(None, 3)
        if len(parts) == 4 and parts[0] == "160000":
            links.add(parts[3].strip('"'))
    return links

def dirty_regular_files(path):
    rc, out = run("git status --porcelain -uno --ignore-submodules=dirty", path, 30)
    files = []
    for line in out.splitlines():
        if line.strip():
            files.append(line[3:].strip().strip('"'))
    return files

def is_clean(path):
    return len(dirty_regular_files(path)) == 0

def cur(path):
    rc, out = run("git rev-parse --abbrev-ref HEAD", path, 15)
    return out.strip()

def commit_dirty(path, rel, log):
    files = dirty_regular_files(path)
    if not files:
        return True
    links = gitlink_paths(path)
    regular = [f for f in files if f not in links]
    if not regular:
        return True
    for f in regular:
        run(f'git add -- "{f}"', path, 30)
    rc, out = run('git commit -m "chore: track dirty state (Protocol #286)"', path, 60)
    if rc != 0:
        run("git reset", path, 30)
        log.append({"repo": rel, "phase": "DIRTYCOMMIT", "action": "fail", "files": regular[:5]})
        print(f"DIRTYCOMMIT FAIL {rel} {regular[:3]}", flush=True)
        return False
    log.append({"repo": rel, "phase": "DIRTYCOMMIT", "action": "committed", "files": regular[:8]})
    print(f"DIRTYCOMMIT OK {rel}: {regular[:3]}", flush=True)
    return True

def main():
    triage = json.loads((ROOT / "sync_protocol_286_triage.json").read_text(encoding="utf-8"))
    prev = json.loads((ROOT / "sync_protocol_286_merge_results.json").read_text(encoding="utf-8"))
    log = []
    conflict_retry = [(e["repo"], e["branch"]) for e in prev if e["phase"] == "MERGE" and e["action"] == "conflict-aborted"]

    # FF remaining behind-only defaults (commit regular dirty files first, then FF, then push is unneeded)
    for r in triage:
        rel, default, ff = r["repo"], r.get("default"), r.get("ff") or ""
        if not default or rel in SKIP_REPOS or "0 ahead" not in ff or "behind origin" not in ff:
            continue
        path = ROOT / rel
        if not (path / ".git").exists():
            continue
        rc, out = run(f"git rev-list --left-right --count {default}...origin/{default}", path, 20)
        try:
            ahead, behind = [int(x) for x in out.split()]
        except Exception:
            continue
        if behind <= 0 or ahead > 0:
            continue
        if cur(path) != default:
            if not commit_dirty(path, rel, log):
                continue
            rc, out = run(f"git checkout {default}", path, 60)
            if rc != 0:
                continue
        elif not commit_dirty(path, rel, log):
            continue
        rc, out = run(f"git merge --ff-only origin/{default}", path, 120)
        if rc == 0:
            # re-commit dirty files that were committed on wrong branch is not applicable; push dirty-commit if HEAD ahead
            rc2, out2 = run(f"git rev-list --count origin/{default}..{default}", path, 20)
            if (out2.strip() or "0") not in ("0", ""):
                run(f"git push origin {default}", path, 180)
            log.append({"repo": rel, "phase": "FF2", "action": "ff-ok"})
            print(f"FF2 OK {rel}", flush=True)
        else:
            log.append({"repo": rel, "phase": "FF2", "action": "ff-fail", "detail": out[-200:]})
            print(f"FF2 FAIL {rel}", flush=True)

    # Merge deferred features in now-clean repos
    for r in triage:
        rel, default = r["repo"], r.get("default")
        if not default or rel in SKIP_REPOS:
            continue
        feats = [f for f in r.get("features", [])
                 if not any(s in f["branch"] for s in SKIP_BRANCH_SUBSTR)
                 and not (rel == "bobeditpro" and f["branch"] == "main")]
        if not feats:
            continue
        path = ROOT / rel
        if not (path / ".git").exists():
            continue
        # skip if already merged in phase 1 (check cherry vs local default now)
        for f in sorted(feats, key=lambda x: x["cherry_plus"]):
            br = f["branch"]
            rc, out = run(f"git cherry {default} {br}", path, 30)
            plus = sum(1 for l in out.splitlines() if l.startswith("+"))
            if plus <= 0:
                continue
            if not is_clean(path):
                if not commit_dirty(path, rel, log):
                    continue
            if cur(path) != default:
                rc, out = run(f"git checkout {default}", path, 60)
                if rc != 0:
                    continue
            rc, out = run(f"git merge --no-ff {br} -m \"merge: {br} into {default} (Protocol #286)\"", path, 240)
            if rc == 0:
                rc2, _ = run(f"git push origin {default}", path, 180)
                log.append({"repo": rel, "phase": "MERGE2", "branch": br, "action": "merged+pushed" if rc2 == 0 else "merged-push-fail"})
                print(f"MERGE2 OK {rel} {br}", flush=True)
            else:
                run("git merge --abort", path, 30)
                log.append({"repo": rel, "phase": "MERGE2", "branch": br, "action": "conflict-aborted"})
                print(f"MERGE2 CONFLICT {rel} {br}", flush=True)
                conflict_retry.append((rel, br))

    # Conflict retry with -X theirs (feature implementation wins conflicts; main keeps non-conflicting progress)
    seen = set()
    for rel, br in conflict_retry:
        if (rel, br) in seen or rel in SKIP_REPOS:
            continue
        seen.add((rel, br))
        default = next((r.get("default") for r in triage if r["repo"] == rel), None)
        path = ROOT / rel
        if not default or not (path / ".git").exists() or not is_clean(path):
            continue
        if cur(path) != default:
            rc, out = run(f"git checkout {default}", path, 60)
            if rc != 0:
                continue
        rc, out = run(f"git cherry {default} {br}", path, 30)
        if sum(1 for l in out.splitlines() if l.startswith("+")) <= 0:
            continue
        rc, out = run(f"git merge --no-ff -X theirs {br} -m \"merge: {br} into {default} (Protocol #286, feature-wins conflicts)\"", path, 240)
        if rc == 0:
            rc2, _ = run(f"git push origin {default}", path, 180)
            log.append({"repo": rel, "phase": "MERGE2X", "branch": br, "action": "merged-theirs+pushed" if rc2 == 0 else "merged-theirs-push-fail"})
            print(f"MERGE2X OK {rel} {br}", flush=True)
        else:
            run("git merge --abort", path, 30)
            log.append({"repo": rel, "phase": "MERGE2X", "branch": br, "action": "conflict-aborted-final"})
            print(f"MERGE2X CONFLICT-FINAL {rel} {br} (branch retained)", flush=True)

    (ROOT / "sync_protocol_286_phase2_results.json").write_text(json.dumps(log, indent=2), encoding="utf-8")
    print(f"\nPHASE2 SUMMARY: {len(log)} actions", flush=True)

if __name__ == "__main__":
    main()





