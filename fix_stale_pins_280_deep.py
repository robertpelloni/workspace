#!/usr/bin/env python3
"""Deep audit: for one repo, check every gitlink at a ref for reachability from the
submodule remote's advertised refs, using the local submodule clone when present.
Writes unreachable pins (with remote HEAD tip) to JSON.
"""
import subprocess, re, json, sys
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")

def run(cmd, cwd=ROOT, timeout=180):
    try:
        p = subprocess.run(cmd, cwd=str(cwd), capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, ((p.stdout or "") + (p.stderr or "")).strip()
    except Exception as e:
        return -2, f"ERR {e}"

def remote_tip(url):
    rc, out = run(f"git ls-remote {url} HEAD", timeout=120)
    for line in out.splitlines():
        parts = line.split()
        if len(parts) == 2 and parts[1] == "HEAD":
            return parts[0]
    return None

def main(repo_rel, ref, prefixes):
    repo = ROOT / repo_rel
    gm = (repo / ".gitmodules").read_text(encoding="utf-8", errors="replace")
    urls = {}
    for block in re.split(r"\[submodule \"[^\"]+\"\]", gm):
        pm = re.search(r"^\s*path\s*=\s*(.+?)\s*$", block, re.M)
        um = re.search(r"^\s*url\s*=\s*(.+?)\s*$", block, re.M)
        if pm and um:
            urls[pm.group(1).strip()] = um.group(1).strip()
    rc, out = run(f"git ls-tree -r {ref}", repo, 60)
    bad, ok, unknown = [], 0, []
    for line in out.splitlines():
        m = re.match(r"160000 commit ([0-9a-f]{40})\t(.+)$", line)
        if not m:
            continue
        sha, path = m.group(1), m.group(2)
        if prefixes and not any(path.startswith(p) for p in prefixes):
            continue
        url = urls.get(path)
        if not url:
            continue
        local = repo / path
        reachable = None
        if (local / ".git").exists() or (local / ".git").is_file():
            run("git fetch origin -q", local, 180)
            rc2, branches = run(f"git branch -r --contains {sha}", local, 60)
            rc3, tags = run(f"git tag --contains {sha}", local, 60)
            reachable = bool(branches.strip() or tags.strip())
        if reachable is None:
            # no local clone: probe fetch-by-sha in temp dir
            import tempfile
            with tempfile.TemporaryDirectory() as d:
                run("git init -q", Path(d), 60)
                rc4, _ = run(f"git fetch -q --depth 1 {url} {sha}", Path(d), 180)
                reachable = (rc4 == 0)
        if reachable:
            ok += 1
        else:
            tip = remote_tip(url)
            bad.append({"path": path, "sha": sha, "url": url, "tip": tip})
            print(f"UNREACHABLE {path} {sha[:10]} -> tip {(tip or '')[:10]}", flush=True)
    print(f"{repo_rel}@{ref}: ok={ok} unreachable={len(bad)}")
    (ROOT / "fix_stale_pins_280_deep.json").write_text(json.dumps(bad, indent=2), encoding="utf-8")

if __name__ == "__main__":
    repo_rel = sys.argv[1] if len(sys.argv) > 1 else "bobsgameonlinejava"
    ref = sys.argv[2] if len(sys.argv) > 2 else "origin/main"
    prefixes = sys.argv[3].split(",") if len(sys.argv) > 3 else ["libs/", "bobcoin"]
    main(repo_rel, ref, prefixes)
