#!/usr/bin/env python3
"""Apply re-pins: gitlink -> remote-published tip via plumbing (working trees untouched). Push each parent."""
import subprocess, json
from pathlib import Path
from collections import defaultdict

ROOT = Path(r"C:\Users\hyper\workspace")
PARENT_DIR = {
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
PARENT_BRANCH = {
    "f-zerox": "main", "geiss": "main", "hyperharness": "main", "itgmania": "main",
    "bobtorrent": "master", "okgame": "main", "bobsaver": "main", "superdawmcp": "main",
    "linthesia": "main", "bobmani/itgmania": "release",
}

def run(cmd, cwd, timeout=180):
    try:
        p = subprocess.run(cmd, cwd=str(cwd), capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, (p.stdout or "") + (p.stderr or "")
    except Exception as e:
        return -2, f"TIMEOUT {e}"

def remove_gitmodules_section(path, subpath):
    rc, out = run("git config --file .gitmodules --list", path, 30)
    names = {}
    for line in out.splitlines():
        if "=" not in line:
            continue
        k, v = line.split("=", 1)
        kp = k.split(".")
        if len(kp) >= 3 and kp[0] == "submodule":
            names.setdefault(".".join(kp[1:-1]), {})[kp[-1]] = v.strip()
    for name, e in names.items():
        if e.get("path") == subpath:
            run(f"git config --file .gitmodules --remove-section submodule.{name}", path, 30)
            return name
    return None

def main():
    fixes = json.loads((ROOT / "fix_stale_pins_fixes.json").read_text(encoding="utf-8"))
    by_parent = defaultdict(list)
    for fx in fixes:
        if fx["status"] != "NO_URL":
            by_parent[fx["parent"]].append(fx)
    log = []
    new_heads = {}
    for parent, fxs in by_parent.items():
        ppath = PARENT_DIR[parent]
        branch = PARENT_BRANCH[parent]
        rc, cur = run("git rev-parse --abbrev-ref HEAD", ppath, 15)
        if cur.strip() != branch:
            rc, out = run(f"git checkout {branch}", ppath, 60)
            if rc != 0:
                log.append({"parent": parent, "action": "checkout-fail", "detail": out[-200:]})
                print(f"FAIL checkout {parent}: {out[-150:]}", flush=True)
                continue
        applied = []
        for fx in fxs:
            sub, tip, st = fx["sub"], fx.get("tip"), fx["status"]
            if st == "DEAD_OR_FETCH_FAIL":
                run(f"git update-index --force-remove -- {sub}", ppath, 30)
                remove_gitmodules_section(ppath, sub)
                run("git add .gitmodules", ppath, 30)
                applied.append(f"{sub}: REMOVED (upstream 404)")
            else:
                rc, out = run(f"git update-index --cacheinfo 160000,{tip},{sub}", ppath, 30)
                if rc == 0:
                    applied.append(f"{sub}: -> {tip[:12]}")
                else:
                    applied.append(f"{sub}: CACHEINFO_FAIL {out[-100:]}")
        rc, out = run("git status --porcelain --cached -uno --ignore-submodules=all", ppath, 30)
        if not out.strip():
            log.append({"parent": parent, "action": "nothing-staged"})
            print(f"NOTHING STAGED {parent}", flush=True)
            continue
        msg = "fix: re-pin submodules to published commits (Jules recursive clone)"
        rc, out = run(f'git commit --no-verify -m "{msg}"', ppath, 120)
        if rc != 0:
            log.append({"parent": parent, "action": "commit-fail", "detail": out[-250:]})
            print(f"FAIL commit {parent}: {out[-200:]}", flush=True)
            continue
        rc, out = run(f"git push origin {branch}", ppath, 240)
        rc2, head = run("git rev-parse HEAD", ppath, 15)
        new_heads[parent] = head.strip()
        act = "repinned+pushed" if rc == 0 else "repinned-push-fail"
        log.append({"parent": parent, "action": act, "applied": applied, "head": head.strip()[:12], "detail": out[-200:] if rc != 0 else ""})
        print(f"{act.upper()} {parent} ({len(applied)} pins)", flush=True)
        for a in applied:
            print(f"    {a}", flush=True)
    (ROOT / "fix_stale_pins_apply_results.json").write_text(json.dumps(log, indent=2), encoding="utf-8")
    (ROOT / "fix_stale_pins_newheads.json").write_text(json.dumps(new_heads, indent=2), encoding="utf-8")
    print("APPLY_DONE", flush=True)

if __name__ == "__main__":
    main()
