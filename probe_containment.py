#!/usr/bin/env python3
"""For suspect pins: fetch in the existing local submodule clone and test whether
the recorded sha is contained in any remote branch/tag (or is an ancestor of the
remote HEAD tip). This is the reliable reachability check."""
import subprocess, json, sys
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")

def run(cmd, cwd, timeout=300):
    try:
        p = subprocess.run(cmd, cwd=str(cwd), capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, ((p.stdout or "") + (p.stderr or "")).strip()
    except Exception as e:
        return -2, f"ERR {e}"

def main(probe_json):
    data = json.loads((ROOT / probe_json).read_text(encoding="utf-8"))
    repo = ROOT / "bg" / "bobsgameonlinejava"
    for r in data:
        if r["fetchable"]:
            continue
        local = repo / r["path"]
        print(f"== {r['path']} recorded={r['sha'][:10]} tip={(r['tip'] or '')[:10]} local_exists={local.exists()}", flush=True)
        if not (local / ".git").exists():
            print("   NO_LOCAL_CLONE", flush=True)
            continue
        run("git fetch origin -q --prune", local, 600)
        rc, branches = run(f"git branch -r --contains {r['sha']}", local, 60)
        rc2, tags = run(f"git tag --contains {r['sha']}", local, 60)
        rc3, anc = run(f"git merge-base --is-ancestor {r['sha']} {r['tip']}", local, 60)
        print(f"   contained_branches={branches.splitlines()[:3]} tags={tags.splitlines()[:3]} ancestor_of_tip={rc3 == 0}", flush=True)

if __name__ == "__main__":
    main(sys.argv[1] if len(sys.argv) > 1 else "probe_pins_bg_bobsgameonlinejava.json")
