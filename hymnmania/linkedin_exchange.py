#!/usr/bin/env python3
"""LinkedIn OAuth code exchange — run IMMEDIATELY after pasting a fresh code.
Usage: python linkedin_exchange.py <authorization_code>

Reads app credentials from .social_config/linkedin_config.json (gitignored, never committed).
Writes access + refresh tokens back to the same file. Never prints secrets.
"""
import json
import sys
import urllib.request
import urllib.parse
from pathlib import Path

CONFIG = Path(__file__).parent / ".social_config" / "linkedin_config.json"
TOKEN_URL = "https://www.linkedin.com/oauth/v2/accessToken"


def main():
    if len(sys.argv) != 2 or not sys.argv[1].strip():
        print("Usage: python linkedin_exchange.py <authorization_code>")
        print("(paste a FRESH code — they expire in minutes)")
        sys.exit(1)
    code = sys.argv[1].strip()

    if not CONFIG.exists():
        print(f"Missing {CONFIG}")
        print("Create it from the template with real client_id/client_secret.")
        sys.exit(1)

    cfg = json.loads(CONFIG.read_text(encoding="utf-8"))
    for key in ("client_id", "client_secret", "redirect_uri"):
        if not cfg.get(key) or str(cfg[key]).startswith("YOUR_"):
            print(f"Config key '{key}' is still a placeholder. Fill in real values first.")
            sys.exit(1)

    data = urllib.parse.urlencode({
        "grant_type": "authorization_code",
        "code": code,
        "redirect_uri": cfg["redirect_uri"],
        "client_id": cfg["client_id"],
        "client_secret": cfg["client_secret"],
    }).encode()

    req = urllib.request.Request(TOKEN_URL, data=data,
                                 headers={"Content-Type": "application/x-www-form-urlencoded"})
    try:
        with urllib.request.urlopen(req, timeout=30) as resp:
            tokens = json.loads(resp.read())
    except urllib.error.HTTPError as e:
        print(f"Exchange failed: HTTP {e.code} — {e.read().decode()[:200]}")
        print("(Code probably expired — generate a fresh one and retry immediately.)")
        sys.exit(1)

    cfg["access_token"] = tokens.get("access_token")
    cfg["refresh_token"] = tokens.get("refresh_token", cfg.get("refresh_token"))
    cfg["expires_in"] = tokens.get("expires_in")
    CONFIG.write_text(json.dumps(cfg, indent=2), encoding="utf-8")
    print("OK: tokens stored in local config (gitignored, not committed).")
    print(f"access_token present: {bool(cfg['access_token'])}")
    print(f"expires_in: {cfg.get('expires_in')}")


if __name__ == "__main__":
    main()
