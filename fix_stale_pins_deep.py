#!/usr/bin/env python3
"""Deep audit: every gitlink in the 9 Jules-failing parents; check pin reachable from remote default tip."""
import subprocess, json, tempfile, shutil
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor, as_completed

ROOT = Path(r"C:\Users\hyper\workspace")
PARENTS = {
    "f-zerox": ROOT / "f-zerox",
    "geiss": ROOT / "geiss",
    "hyperharness": ROOT / "hyperharness",
    "itgmania": ROOT / "itgmania_fix_clone",
    "bobtorrent": ROOT / "bobtorrent",
    "okgame": ROOT / "okgame",
    "bobsaver": ROOT / "bobsaver",
    "superdawmcp": ROOT / "superdawmcp",
    "linthesia": ROOT / "linthesia_fix_clone",
    "bobmani/itgmania": ROOT / "bobmani" / "itgmania",
}

def run(cmd, cwd=None, timeout=120):
    try:
        p = subprocess.run(cmd, cwd=str(cwd) if cwd else None, capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, (p.stdout or "") + (p.stderr or "")
    except Exception as e:
        return -2, f"TIMEOUT {e}"

def gitlinks(parent_path):
    rc, out = run("git ls-tree -r HEAD", parent_path, 60)
    links = []
    for line in out.splitlines():
        meta, _, path = line.partition("\t")
        parts = meta.split()
        if len(parts) >= 3 and parts[0] == "160000":
            links.append((path.strip(), parts[2]))
    return links

def url_for(parent_path, subpath):
    rc, out = run("git config --file .gitmodules --list", parent_path, 30)
    # map path -> url via submodule sections
    entries = {}
    cur = None
    for line in out.splitlines():
        if "=" not in line:
            continue
        k, v = line.split("=", 1)
        kp = k.split(".")
        if len(kp) >= 3 and kp[0] == "submodule":
            name = ".".join(kp[1:-1])
            entries.setdefault(name, {})[kp[-1]] = v.strip()
    for name, e in entries.items():
        if e.get("path") == subpath:
            return e.get("url", "")
    return ""

def check_url(url, shas):
    """Clone blob:none bare once; return {sha: status} + remote tip."""
    tmp = Path(tempfile.mkdtemp(prefix="pincheck_"))
    try:
        rc, out = run(f"git clone --bare --filter=blob:none --no-checkout {url} repo", tmp, 300)
        if rc != 0:
            return {s: "DEAD_OR_FETCH_FAIL" for s in shas}, "", out[-200:]
        repo = tmp / "repo"
        rc, tip = run("git rev-parse HEAD", repo, 30)
        tip = tip.strip()
        res = {}
        for s in shas:
            rc1, _ = run(f"git cat-file -t {s}", repo, 30)
            if rc1 != 0:
                res[s] = "MISSING"
                continue
            rc2, _ = run(f"git merge-base --is-ancestor {s} HEAD", repo, 30)
            res[s] = "OK" if rc2 == 0 else "UNREACHABLE"
        return res, tip, ""
    finally:
        shutil.rmtree(tmp, ignore_errors=True)

def main():
    # collect (parent, subpath, sha, url)
    items = []
    url_shas = {}
    for pname, ppath in PARENTS.items():
        if not (ppath / ".git").exists():
            print(f"SKIP {pname} (no .git)", flush=True)
            continue
        for subpath, sha in gitlinks(ppath):
            url = url_for(ppath, subpath)
            if url.startswith("../"):
                rc_o, origin_url = run("git remote get-url origin", ppath, 15)
                origin_url = origin_url.strip()
                if "github.com/" in origin_url:
                    base = origin_url.rsplit("/", 1)[0]
                    url = base + "/" + url[3:]
            items.append((pname, subpath, sha, url))
            if url:
                url_shas.setdefault(url, set()).add(sha)
    print(f"gitlinks: {len(items)}, unique urls: {len(url_shas)}", flush=True)
    results = {}
    with ThreadPoolExecutor(max_workers=8) as ex:
        futs = {ex.submit(check_url, u, sorted(s)): u for u, s in url_shas.items()}
        for f in as_completed(futs):
            u = futs[f]
            res, tip, err = f.result()
            results[u] = (res, tip)
            bad = {s: v for s, v in res.items() if v != "OK"}
            if bad:
                print(f"BAD {u} tip={tip[:12]} {bad} {err[:100]}", flush=True)
    fixes = []
    for pname, subpath, sha, url in items:
        if not url:
            fixes.append({"parent": pname, "sub": subpath, "sha": sha, "status": "NO_URL", "tip": ""})
            continue
        res, tip = results.get(url, ({}, ""))
        st = res.get(sha, "UNKNOWN")
        if st != "OK":
            fixes.append({"parent": pname, "sub": subpath, "sha": sha, "status": st, "tip": tip, "url": url})
    print(f"\nFIXES NEEDED: {len(fixes)}", flush=True)
    for fx in fixes:
        print(f"  {fx['parent']} :: {fx['sub']} pin {fx['sha'][:12]} -> {fx['status']} (tip {str(fx.get('tip'))[:12]}) {fx.get('url','')}", flush=True)
    (ROOT / "fix_stale_pins_fixes.json").write_text(json.dumps(fixes, indent=2), encoding="utf-8")

if __name__ == "__main__":
    main()
