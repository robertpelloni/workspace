#!/usr/bin/env python3
"""Add credential patterns to hymnmania .gitignore and commit safe files."""
import subprocess
from pathlib import Path

REPO = Path(r"C:\Users\hyper\workspace\bobmani\hymnmania")

# Update .gitignore
gi = REPO / ".gitignore"
existing = gi.read_text(encoding="utf-8") if gi.exists() else ""
patterns = [
    "# Credentials (never commit)",
    ".social_config/bluesky_accounts.json",
    ".social_config/bluesky_config.json",
    ".social_config/bluesky_robertpelloni.json",
    ".social_config/fb_state.json",
    ".social_config/linkedin_config.json",
    ".social_config/twitter_config.json",
    ".social_config/youtube_token.json",
    ".tiktok_state.json",
]
to_add = [p for p in patterns if p not in existing]
if to_add:
    gi.write_text(existing + "\n".join(to_add) + "\n", encoding="utf-8")
    print(f"Added {len(to_add)} patterns to .gitignore")
else:
    print(".gitignore already up to date")

def run(cmd, timeout=30):
    p = subprocess.run(cmd, cwd=str(REPO), capture_output=True, text=True, timeout=timeout, shell=True)
    return p.returncode, (p.stdout or "") + (p.stderr or "")

run("git add .gitignore")
run("git add .pi/caps-context-state.json")
run("git add .social_config/linkedin_config.template.json")
run("git add .social_config/twitter_config.template.json")

rc, out = run("git commit -m 'chore: track .social_config templates + .pi/caps-context-state.json; gitignore credential files'")
print(out[-200:] if out else "commit done")

rc, out = run("git status --short")
print(out[:500] if out else "clean")
