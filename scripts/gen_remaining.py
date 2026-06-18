import os
import subprocess

def run_cmd(cmd, cwd=None):
    res = subprocess.run(cmd, cwd=cwd, shell=True, capture_output=True, text=True, encoding="utf-8", errors="replace")
    return res.stdout.strip()

root_dir = os.getcwd()
out = run_cmd("git submodule --quiet foreach --recursive \"echo $displaypath\"", cwd=root_dir)
all_repos = [root_dir]
if out:
    for path in out.splitlines():
        full_path = os.path.join(root_dir, path.strip())
        if os.path.exists(full_path):
            all_repos.append(full_path)

all_repos.sort(key=lambda x: x.count(os.sep))

found = False
remaining = []
last_processed = "bg/bobsgameonlinejava/references/raster-master"

for repo in all_repos:
    rel_path = os.path.relpath(repo, root_dir).replace("\\", "/")
    if rel_path == ".": rel_path = ""
    
    if found:
        remaining.append(repo)
    
    if rel_path == last_processed:
        found = True

with open("remaining_repos.txt", "w", encoding="utf-8") as f:
    for r in remaining:
        f.write(r + "\n")
