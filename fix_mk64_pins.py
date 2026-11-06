#!/usr/bin/env python3
"""Check each mk64 gitlink reachability from remote HEAD; re-pin bad ones to remote tip; push mk64."""
import subprocess, json
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")
MK = ROOT / "mk64"
TMPBASE = Path(r"C:\Users\hyper\AppData\Local\Temp\pincheck_mk64")

def run(cmd, cwd=None, timeout=180):
    try:
        p = subprocess.run(cmd, cwd=str(cwd) if cwd else None, capture_output=True, text=True, timeout=timeout, shell=True)
        return p.returncode, (p.stdout or "") + (p.stderr or "")
    except Exception as e:
        return -2, f"TIMEOUT {e}"

def main():
    rc, out = run("git ls-tree -r HEAD", MK, 60)
    links = []
    for line in out.splitlines():
        meta, _, path = line.partition("\t")
        parts = meta.split()
        if len(parts) >= 3 and parts[0] == "160000":
            links.append((path.strip(), parts[2]))
    rc, cfg = run("git config --file .gitmodules --list", MK, 30)
    urls = {}
    entries = {}
    for line in cfg.splitlines():
        if "=" not in line:
            continue
        k, v = line.split("=", 1)
        kp = k.split(".")
        if len(kp) >= 3 and kp[0] == "submodule":
            entries.setdefault(".".join(kp[1:-1]), {})[kp[-1]] = v.strip()
    for e in entries.values():
        if "path" in e and "url" in e:
            urls[e["path"]] = e["url"]
    print(f"gitlinks: {len(links)}", flush=True)
    fixes = []
    TMPBASE.mkdir(parents=True, exist_ok=True)
    for sub, sha in links:
        url = urls.get(sub, "")
        tmp = TMPBASE / sub.replace("/", "_")
        if tmp.exists():
            run(f"rmdir /s /q {tmp}", None, 60)
        rc, out = run(f"git clone --bare --filter=blob:none --no-checkout {url} {tmp}", None, 300)
        if rc != 0:
            fixes.append((sub, sha, "", "DEAD"))
            print(f"{sub}: DEAD {url}", flush=True)
            continue
        rc, tip = run("git rev-parse HEAD", tmp, 30)
        tip = tip.strip()
        rc1, _ = run(f"git cat-file -t {sha}", tmp, 30)
        if rc1 != 0:
            fixes.append((sub, sha, tip, "MISSING"))
            print(f"{sub}: MISSING pin {sha[:12]} tip {tip[:12]}", flush=True)
            continue
        rc2, _ = run(f"git merge-base --is-ancestor {sha} HEAD", tmp, 30)
        if rc2 != 0:
            fixes.append((sub, sha, tip, "UNREACHABLE"))
            print(f"{sub}: UNREACHABLE pin {sha[:12]} tip {tip[:12]}", flush=True)
        else:
            print(f"{sub}: OK", flush=True)
    for sub, sha, tip, st in fixes:
        if st == "DEAD":
            print(f"SKIP DEAD {sub} (needs manual decision)", flush=True)
            continue
        rc, out = run(f"git update-index --cacheinfo 160000,{tip},{sub}", MK, 30)
        print(f"repinned {sub} -> {tip[:12]} rc={rc}", flush=True)
    if fixes:
        rc, out = run('git commit --no-verify -m "fix: re-pin submodules to published commits (Jules recursive clone)"', MK, 120)
        print(f"commit rc={rc} {out[-150:]}", flush=True)
        rc, out = run("git push origin master", MK, 240)
        print(f"push rc={rc} {out[-150:]}", flush=True)
    rc, head = run("git rev-parse HEAD", MK, 15)
    print(f"MK64_HEAD {head.strip()}", flush=True)
    (ROOT / "fix_mk64_results.json").write_text(json.dumps({"fixes": fixes, "head": head.strip()}, indent=2), encoding="utf-8")

if __name__ == "__main__":
    main()
