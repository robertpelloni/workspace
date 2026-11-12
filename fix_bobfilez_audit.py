#!/usr/bin/env python3
"""Audit all gitlinks in bobfilez@origin/main.
For each: if recorded sha is contained in remote branches/tags (via local clone
after fetch) -> OK. Else target = merge-base(recorded, remote HEAD tip) when the
recorded object exists locally, else the remote HEAD tip.
Writes fix_bobfilez_audit.json with re-pin targets. No pushes."""
import subprocess, re, json, sys, tempfile
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")
REPO = ROOT / "bobfilez"

def run(cmd, cwd, timeout=900):
    try:
        p = subprocess.run(cmd, cwd=str(cwd), capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, (p.stdout or "").strip(), ((p.stdout or "") + (p.stderr or "")).strip()
    except Exception as e:
        return -2, "", f"ERR {e}"

def remote_tip(url):
    rc, out, _ = run(f"git ls-remote {url} HEAD", ROOT, 180)
    for line in out.splitlines():
        parts = line.split()
        if len(parts) == 2 and parts[1] == "HEAD":
            return parts[0]
    return None

def main():
    rc, gm, _ = run("git show origin/main:.gitmodules", REPO, 60)
    urls = {}
    for block in re.split(r"\[submodule \"[^\"]+\"\]", gm):
        pm = re.search(r"^\s*path\s*=\s*(.+?)\s*$", block, re.M)
        um = re.search(r"^\s*url\s*=\s*(.+?)\s*$", block, re.M)
        upd = re.search(r"^\s*update\s*=\s*(.+?)\s*$", block, re.M)
        if pm and um:
            urls[pm.group(1).strip()] = (um.group(1).strip(), upd.group(1).strip() if upd else "")
    rc, out, _ = run("git ls-tree -r origin/main", REPO, 60)
    results, repins = [], []
    for line in out.splitlines():
        m = re.match(r"160000 commit ([0-9a-f]{40})\t(.+)$", line)
        if not m:
            continue
        sha, path = m.group(1), m.group(2)
        entry = urls.get(path)
        if not entry:
            continue
        url, upd = entry
        if upd == "none":
            print(f"SKIP {path}", flush=True)
            continue
        tip = remote_tip(url)
        local = REPO / path
        status, target = None, None
        if (local / ".git").exists():
            run("git fetch origin -q --prune", local, 1200)
            rc1, branches, _ = run(f"git branch -r --contains {sha}", local, 60)
            rc2, tags, _ = run(f"git tag --contains {sha}", local, 60)
            contained = (branches and "error" not in branches) or (tags and "error" not in tags)
            if contained:
                status = "ok"
            else:
                rc3, mb, _ = run(f"git merge-base {sha} {tip}", local, 60)
                if rc3 == 0 and re.fullmatch(r"[0-9a-f]{40}", mb or ""):
                    target, status = mb, "repin-mergebase"
                else:
                    target, status = tip, "repin-tip"
        else:
            # no local clone: probe fetch-by-sha; if fails, re-pin to tip
            with tempfile.TemporaryDirectory() as d:
                run("git init -q", Path(d), 60)
                rc4, _, _ = run(f"git fetch -q --depth 1 {url} {sha}", Path(d), 600)
                if rc4 == 0:
                    status = "ok"
                else:
                    target, status = tip, "repin-tip-nolocal"
        print(f"{status.upper()} {path} {sha[:10]}" + (f" -> {target[:10]}" if target else ""), flush=True)
        results.append({"path": path, "sha": sha, "url": url, "tip": tip, "status": status, "target": target})
        if target and target != sha:
            repins.append({"path": path, "from": sha, "to": target})
    (ROOT / "fix_bobfilez_audit.json").write_text(json.dumps({"results": results, "repins": repins}, indent=2), encoding="utf-8")
    print(f"total={len(results)} repins={len(repins)} -> fix_bobfilez_audit.json")

if __name__ == "__main__":
    main()
