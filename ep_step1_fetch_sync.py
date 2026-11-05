#!/usr/bin/env python3
"""EP Step 1: Fetch all submodules and FF-pull. Paths from .gitmodules."""
import subprocess, re, sys
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")

def run(cmd, cwd, timeout=180):
    try:
        p = subprocess.run(cmd, cwd=str(cwd), capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, (p.stdout or "") + (p.stderr or "")
    except subprocess.TimeoutExpired:
        return -1, "TIMEOUT"
    except Exception as e:
        return -2, str(e)

def load_paths():
    gm = (ROOT / ".gitmodules").read_text(encoding="utf-8", errors="replace")
    return re.findall(r"^\s*path\s*=\s*(.+?)\s*$", gm, re.M)

def process(path_rel):
    path = ROOT / path_rel
    gitdir = path / ".git"
    if not gitdir.exists():
        return path_rel, "NOT-INIT", ""
    rc1, o1 = run("git fetch --all --tags --prune", path, 180)
    rc2, o2 = run("git rev-parse --abbrev-ref HEAD", path, 30)
    branch = o2.strip()
    if branch in ("HEAD", ""):
        rc3, o3 = run("git remote show origin", path, 60)
        default = "main"
        for line in o3.splitlines():
            if "HEAD branch" in line:
                default = line.split(":")[-1].strip()
                break
        run(f'git checkout "{default}"', path, 60)
        branch = default
    rc4, o4 = run("git pull --ff-only", path, 180)
    low = (o4 or "").lower()
    if rc4 == 0:
        status = "OK"
    elif "already up to date" in low:
        status = "OK"
    elif "local changes" in low or "would be overwritten" in low or "unmerged" in low:
        status = "DIRTY"
    elif "no tracking" in low or "no upstream" in low:
        status = "NO-UPSTREAM"
    else:
        status = "FF-FAIL"
    note = (o4 or "")[-100:].replace("\n", " | ")
    return path_rel, status, f"{branch} :: {note}"

def main():
    paths = load_paths()
    print(f"Found {len(paths)} submodule paths from .gitmodules", flush=True)
    results = []
    for i, path in enumerate(paths, 1):
        print(f"[{i}/{len(paths)}] {path} ...", end=" ", flush=True)
        p, st, note = process(path)
        results.append((p, st, note))
        print(f"{st}", flush=True)

    from collections import Counter
    c = Counter(s for _, s, _ in results)
    print(f"\n=== SUMMARY: {dict(c)} of {len(results)} ===", flush=True)
    for p, s, n in results:
        if s not in ("OK",):
            print(f"  [{s}] {p}: {n}", flush=True)

if __name__ == "__main__":
    main()
