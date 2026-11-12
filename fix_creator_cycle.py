#!/usr/bin/env python3
"""Break hymnmania<->creator submodule cycle: add update=none to hymnmania_src
in ableton_psytrance_hymn_creator via plumbing, push main. Then re-pin creator
in hymnmania (main, plumbing) and hymnmania in bobmani (main, plumbing)."""
import subprocess, os, sys, tempfile
from pathlib import Path

ROOT = Path(r"C:\Users\hyper\workspace")

def run(cmd, cwd, env=None, timeout=300, check=True):
    e = dict(os.environ)
    if env:
        e.update(env)
    p = subprocess.run(cmd, cwd=str(cwd), capture_output=True, text=True, timeout=timeout, shell=True, env=e)
    out = (p.stdout or "").strip() or ((p.stdout or "") + (p.stderr or "")).strip()
    if check and p.returncode != 0:
        print(f"FAIL: {cmd}\n{out}")
        sys.exit(1)
    return out

def plumbing_commit(repo, branch, mutate, message):
    run("git fetch origin -q", repo)
    base = run(f"git rev-parse origin/{branch}", repo)
    with tempfile.TemporaryDirectory() as d:
        env = {"GIT_INDEX_FILE": str(Path(d) / "index")}
        run(f"git read-tree origin/{branch}", repo, env)
        mutate(repo, env)
        tree = run("git write-tree", repo, env)
        commit = run(f'git commit-tree {tree} -p {base} -m "{message}"', repo, env)
    run(f"git push origin {commit}:{branch}", repo)
    print(f"{repo.name}: {branch} {base[:10]} -> {commit[:10]}")
    return commit

def main():
    creator = ROOT / "bobmani" / "hymnmania" / "submodules" / "ableton_psytrance_hymn_creator"
    hymn = ROOT / "bobmani" / "hymnmania"
    bobmani = ROOT / "bobmani"

    # 1. creator: .gitmodules hymnmania_src update=none
    def mut_creator(repo, env):
        gm = run("git show origin/main:.gitmodules", repo)
        if "update = none" not in gm and "update=none" not in gm:
            lines = gm.splitlines()
            out_lines, in_section = [], False
            for ln in lines:
                out_lines.append(ln)
                if ln.strip().startswith('[submodule "hymnmania_src"]'):
                    in_section = True
                elif ln.strip().startswith("[submodule"):
                    in_section = False
            # append update=none right after the hymnmania_src section header block:
            # simpler: insert after the url line of that section
            final, inserted, sect = [], False, False
            for ln in out_lines:
                final.append(ln)
                if ln.strip().startswith('[submodule "hymnmania_src"]'):
                    sect = True
                elif ln.strip().startswith("[submodule"):
                    sect = False
                if sect and not inserted and ln.strip().startswith("url"):
                    final.append("\tupdate = none")
                    inserted = True
            if not inserted:
                print("could not insert update=none")
                sys.exit(1)
            gm = "\n".join(final) + "\n"
        with tempfile.NamedTemporaryFile("w", suffix=".txt", delete=False, encoding="utf-8", newline="\n") as f:
            f.write(gm)
            tmp = f.name
        blob = run(f"git hash-object -w {tmp}", repo)
        run(f"git update-index --cacheinfo 100644,{blob},.gitmodules", repo, env)

    creator_commit = plumbing_commit(creator, "main", mut_creator,
        "fix: skip hymnmania_src in recursive clones (break hymnmania cycle, Jules clone)")

    # 2. hymnmania: re-pin submodules/ableton_psytrance_hymn_creator to new creator commit.
    # hymnmania published branch is main (bobmani pins hymnmania@main tip).
    def mut_hymn(repo, env):
        run(f"git update-index --cacheinfo 160000,{creator_commit},submodules/ableton_psytrance_hymn_creator", repo, env)
    hymn_commit = plumbing_commit(hymn, "main", mut_hymn,
        "fix: re-pin ableton_psytrance_hymn_creator (cycle break)")

    # 3. bobmani: re-pin hymnmania to new hymnmania commit
    def mut_bobmani(repo, env):
        run(f"git update-index --cacheinfo 160000,{hymn_commit},hymnmania", repo, env)
    bobmani_commit = plumbing_commit(bobmani, "main", mut_bobmani,
        "fix: re-pin hymnmania (creator cycle break)")

    print(f"CREATOR={creator_commit}")
    print(f"HYMNMANIA={hymn_commit}")
    print(f"BOBMANI={bobmani_commit}")

if __name__ == "__main__":
    main()
