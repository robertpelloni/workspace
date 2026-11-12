#!/usr/bin/env python3
"""Probe each gitlink in a repo@ref the way Jules' shallow submodule clone does:
temp-init + `git fetch --depth 1 <url> <sha>`. Records fetchable + remote HEAD tip."""
import subprocess, re, json, sys, tempfile
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")

def run(cmd, cwd, timeout=240):
    try:
        p = subprocess.run(cmd, cwd=str(cwd), capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, ((p.stdout or "") + (p.stderr or "")).strip()
    except Exception as e:
        return -2, f"ERR {e}"

def main(repo_rel, ref, prefixes):
    repo = ROOT / repo_rel
    gm_path = repo / ".gitmodules"
    # read .gitmodules at ref, not working tree
    rc, gm = run(f"git show {ref}:.gitmodules", repo, 60)
    urls = {}
    for block in re.split(r"\[submodule \"[^\"]+\"\]", gm):
        pm = re.search(r"^\s*path\s*=\s*(.+?)\s*$", block, re.M)
        um = re.search(r"^\s*url\s*=\s*(.+?)\s*$", block, re.M)
        umode = re.search(r"^\s*update\s*=\s*(.+?)\s*$", block, re.M)
        if pm and um:
            urls[pm.group(1).strip()] = (um.group(1).strip(), (umode.group(1).strip() if umode else ""))
    rc, out = run(f"git ls-tree -r {ref}", repo, 60)
    results = []
    for line in out.splitlines():
        m = re.match(r"160000 commit ([0-9a-f]{40})\t(.+)$", line)
        if not m:
            continue
        sha, path = m.group(1), m.group(2)
        if prefixes and not any(path.startswith(p) for p in prefixes):
            continue
        entry = urls.get(path)
        if not entry:
            continue
        url, upd = entry
        if upd == "none":
            print(f"SKIP(update=none) {path}", flush=True)
            continue
        with tempfile.TemporaryDirectory() as d:
            run("git init -q", Path(d), 60)
            rc4, err = run(f"git fetch -q --depth 1 {url} {sha}", Path(d), 240)
            ok = (rc4 == 0)
        tip = None
        if not ok:
            rc5, lo = run(f"git ls-remote {url} HEAD", ROOT, 120)
            for ln in lo.splitlines():
                parts = ln.split()
                if len(parts) == 2 and parts[1] == "HEAD":
                    tip = parts[0]
        print(f"{'OK ' if ok else 'BAD'} {path} {sha[:10]}" + ("" if ok else f" -> tip {(tip or '')[:10]}"), flush=True)
        results.append({"path": path, "sha": sha, "url": url, "fetchable": ok, "tip": tip})
    out_name = "probe_pins_" + repo_rel.replace("/", "_") + ".json"
    (ROOT / out_name).write_text(json.dumps(results, indent=2), encoding="utf-8")
    bad = [r for r in results if not r["fetchable"]]
    print(f"{repo_rel}@{ref}: total={len(results)} bad={len(bad)} -> {out_name}")

if __name__ == "__main__":
    repo_rel = sys.argv[1]
    ref = sys.argv[2] if len(sys.argv) > 2 else "origin/main"
    prefixes = sys.argv[3].split(",") if len(sys.argv) > 3 else []
    main(repo_rel, ref, prefixes)
