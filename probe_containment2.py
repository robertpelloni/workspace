#!/usr/bin/env python3
"""Containment check for probe-BAD pins of an arbitrary repo.
Usage: probe_containment2.py <repo_rel> <probe_json>
For each fetchable=false entry, fetch in repo/<path> local clone and test
branch/tag containment + ancestor-of-tip. Writes probe_containment_<repo>.json
with only the truly unreachable pins."""
import subprocess, json, sys
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")

def run(cmd, cwd, timeout=600):
    try:
        p = subprocess.run(cmd, cwd=str(cwd), capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, ((p.stdout or "") + (p.stderr or "")).strip()
    except Exception as e:
        return -2, f"ERR {e}"

def main(repo_rel, probe_json):
    data = json.loads((ROOT / probe_json).read_text(encoding="utf-8"))
    repo = ROOT / repo_rel
    truly_bad = []
    for r in data:
        if r["fetchable"]:
            continue
        local = repo / r["path"]
        if not (local / ".git").exists():
            print(f"NO_LOCAL {r['path']}", flush=True)
            truly_bad.append({**r, "reason": "no_local_clone"})
            continue
        run("git fetch origin -q --prune", local, 900)
        rc, branches = run(f"git branch -r --contains {r['sha']}", local, 60)
        rc2, tags = run(f"git tag --contains {r['sha']}", local, 60)
        contained = bool(branches.strip() and "error" not in branches) or bool(tags.strip() and "error" not in tags)
        anc = False
        if r.get("tip"):
            rc3, _ = run(f"git merge-base --is-ancestor {r['sha']} {r['tip']}", local, 60)
            anc = (rc3 == 0)
        ok = contained or anc
        print(f"{'OK ' if ok else 'BAD'} {r['path']} contained={contained} ancestor_of_tip={anc}", flush=True)
        if not ok:
            truly_bad.append(r)
    out_name = "probe_containment_" + repo_rel.replace("/", "_") + ".json"
    (ROOT / out_name).write_text(json.dumps(truly_bad, indent=2), encoding="utf-8")
    print(f"{repo_rel}: truly_bad={len(truly_bad)} -> {out_name}")

if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
