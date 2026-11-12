#!/usr/bin/env python3
"""Re-pin stale robertpelloni submodule gitlinks to remote-advertised default tips.
Uses update-index plumbing so working trees / local submodule checkouts stay untouched.
Order matters: innermost repos first, then their parents.
"""
import subprocess, json
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")
RESULTS = []

def run(cmd, cwd=ROOT, timeout=240):
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

def repin(repo_rel, branch, pins, msg):
    repo = ROOT / repo_rel
    entry = {"repo": repo_rel, "branch": branch, "pins": pins}
    # sync base to origin tip first (merge; pointer-only conflicts resolved by our staged pins after)
    rc, out = run(f"git checkout {branch}", repo)
    entry["checkout"] = out[-200:]
    rc, out = run(f"git merge origin/{branch} --no-edit", repo)
    entry["merge"] = out[-300:]
    if "CONFLICT" in out:
        run("git merge --abort", repo)
        entry["result"] = "base-merge-conflict"
        RESULTS.append(entry)
        print(f"{repo_rel}: BASE MERGE CONFLICT, skipped", flush=True)
        return None
    for path, tip in pins.items():
        rc, out = run(f"git update-index --cacheinfo 160000,{tip},{path}", repo)
        if rc != 0:
            entry["result"] = f"update-index fail {path}: {out[-200:]}"
            RESULTS.append(entry)
            print(f"{repo_rel}: UPDATE-INDEX FAIL {path}", flush=True)
            return None
    rc, out = run("git diff --cached --quiet", repo)
    if rc == 0:
        entry["result"] = "no-change"
        RESULTS.append(entry)
        print(f"{repo_rel}: no change", flush=True)
        rc2, head = run("git rev-parse HEAD", repo)
        return head.strip()
    rc, out = run(f'git commit -m "{msg}"', repo)
    if rc != 0:
        entry["result"] = f"commit fail: {out[-200:]}"
        RESULTS.append(entry)
        print(f"{repo_rel}: COMMIT FAIL", flush=True)
        return None
    rc, out = run(f"git push origin {branch}", repo, 300)
    entry["push"] = out[-300:]
    entry["result"] = "pushed" if rc == 0 else "push-fail"
    rc2, head = run("git rev-parse HEAD", repo)
    entry["head"] = head.strip()
    RESULTS.append(entry)
    print(f"{repo_rel}: {entry['result']} {entry.get('head','')[:10]}", flush=True)
    return entry.get("head") if rc == 0 else None

if __name__ == "__main__":
    # 1. bobsgameonlinejava: libs/bobui -> bobui published HEAD tip
    bobui_tip = remote_tip("https://github.com/robertpelloni/bobui.git")
    print(f"bobui tip {bobui_tip}", flush=True)
    bgj_head = repin("bobsgameonlinejava", "main",
                     {"libs/bobui": bobui_tip},
                     "fix: re-pin libs/bobui to published tip (Jules stale-pin)")
    # 2. bg: bobsgameonlinejava -> its new published tip
    if bgj_head:
        repin("bg", "master",
              {"bobsgameonlinejava": bgj_head},
              "fix: re-pin bobsgameonlinejava to published tip (Jules stale-pin)")
    # 3. bobfilez: 5 stale libs -> published HEAD tips
    bobfilez_pins = {}
    for path, url in {
        "libs/ADSFileSystem": "https://github.com/robertpelloni/ADSFileSystem",
        "libs/DataStreamBrowser": "https://github.com/robertpelloni/DataStreamBrowser",
        "libs/bobgui": "https://github.com/robertpelloni/bgtk",
        "libs/bobui": "https://github.com/robertpelloni/bqt.git",
        "libs/btk": "https://github.com/robertpelloni/bcs.git",
    }.items():
        tip = remote_tip(url)
        print(f"bobfilez {path} tip {tip}", flush=True)
        if tip:
            bobfilez_pins[path] = tip
    repin("bobfilez", "main", bobfilez_pins,
          "fix: re-pin stale libs to published tips (Jules stale-pin)")
    # 4. bobsaver: 4 stale pins -> published HEAD tips
    bobsaver_pins = {}
    for path, url in {
        "MilkDrop3": "https://github.com/robertpelloni/MilkDrop3.git",
        "apophysis-j": "https://github.com/robertpelloni/apophysis-j",
        "electricsheep": "https://github.com/robertpelloni/electricsheep",
        "geiss": "https://github.com/robertpelloni/geiss",
    }.items():
        tip = remote_tip(url)
        print(f"bobsaver {path} tip {tip}", flush=True)
        if tip:
            bobsaver_pins[path] = tip
    repin("bobsaver", "main", bobsaver_pins,
          "fix: re-pin stale submodules to published tips (Jules stale-pin)")
    # 5. arrowvortex: lib/ddc -> ddc published HEAD tip; then bobmani arrowvortex -> new tip
    ddc_tip = remote_tip("https://github.com/robertpelloni/ddc.git")
    print(f"ddc tip {ddc_tip}", flush=True)
    av_head = repin("bobmani/arrowvortex", "main",
                    {"lib/ddc": ddc_tip},
                    "fix: re-pin lib/ddc to published tip (Jules stale-pin)")
    if av_head:
        repin("bobmani", "main",
              {"arrowvortex": av_head},
              "fix: re-pin arrowvortex (ddc stale-pin fix)")
    (ROOT / "fix_stale_pins_280_apply.json").write_text(json.dumps(RESULTS, indent=2), encoding="utf-8")
    print("APPLY DONE")
