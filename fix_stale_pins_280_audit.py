#!/usr/bin/env python3
"""Audit recorded gitlinks vs published remote tips for robertpelloni-owned submodule URLs.
Reports pins whose recorded sha is not advertised by any ref on the submodule remote
(ls-remote). Such pins fail Jules' shallow recursive clone with 'not our ref'.
"""
import subprocess, re, json, sys
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")
CACHE = {}

def run(cmd, cwd=None, timeout=90):
    try:
        p = subprocess.run(cmd, cwd=str(cwd) if cwd else None, capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, (p.stdout or "") + (p.stderr or "")
    except Exception as e:
        return -2, f"ERR {e}"

def ls_remote(url):
    if url in CACHE:
        return CACHE[url]
    rc, out = run(f"git ls-remote {url}", timeout=120)
    tips = {}
    if rc == 0:
        for line in out.splitlines():
            parts = line.split()
            if len(parts) == 2:
                tips[parts[1]] = parts[0]
    CACHE[url] = tips
    return tips

def gitmodules_urls(repo_path):
    gm = repo_path / ".gitmodules"
    urls = {}
    if not gm.exists():
        return urls
    text = gm.read_text(encoding="utf-8", errors="replace")
    cur_path = None
    for block in re.split(r"\[submodule \"[^\"]+\"\]", text):
        pm = re.search(r"^\s*path\s*=\s*(.+?)\s*$", block, re.M)
        um = re.search(r"^\s*url\s*=\s*(.+?)\s*$", block, re.M)
        if pm and um:
            urls[pm.group(1).strip()] = um.group(1).strip()
    return urls

def default_tip(tips):
    if "HEAD" in tips:
        return tips["HEAD"]
    for ref in ("refs/heads/main", "refs/heads/master"):
        if ref in tips:
            return tips[ref]
    return next(iter(tips.values()), None)

def audit_repo(rel, ref="HEAD"):
    repo = ROOT / rel
    urls = gitmodules_urls(repo)
    rc, out = run(f"git ls-tree -r {ref}", repo, 60)
    bad = []
    for line in out.splitlines():
        m = re.match(r"160000 commit ([0-9a-f]{40})\t(.+)$", line)
        if not m:
            continue
        sha, path = m.group(1), m.group(2)
        url = urls.get(path)
        if not url or "robertpelloni" not in url:
            continue
        tips = ls_remote(url)
        if not tips:
            bad.append({"repo": rel, "path": path, "sha": sha, "url": url, "issue": "NO_REMOTE_REFS", "tip": None})
        elif sha not in tips.values():
            bad.append({"repo": rel, "path": path, "sha": sha, "url": url, "issue": "NOT_ADVERTISED", "tip": default_tip(tips)})
    return bad

if __name__ == "__main__":
    targets = sys.argv[1:] or ["bobfilez", "bg"]
    all_bad = []
    for rel in targets:
        ref = "origin/master" if rel == "bg" else "origin/main"
        bad = audit_repo(rel, ref)
        all_bad += bad
        print(f"{rel}@{ref}: {len(bad)} stale robertpelloni pins", flush=True)
        for b in bad:
            print(f"  {b['path']} {b['sha'][:10]} -> tip {(b['tip'] or '')[:10]} ({b['issue']}) {b['url']}", flush=True)
    (ROOT / "fix_stale_pins_280_audit.json").write_text(json.dumps(all_bad, indent=2), encoding="utf-8")
    print(f"TOTAL: {len(all_bad)}")
