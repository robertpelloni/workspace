import shutil
import subprocess
import sys

CONF = "/etc/nginx/sites-available/aimoneymachine"
BLOCK = """
    # --------------------------------------------------------------------
    # Security hardening — added 2026-09-14 after the "Kamikaze" defacement.
    # Initial-access vector was the WP REST API batch endpoint
    # (/wp-json/batch/v1), abused to bypass auth and mint 40 admin users.
    # --------------------------------------------------------------------

    # REST API batch endpoint — the auth-bypass vector (case-insensitive)
    location ~* ^/wp-json/batch(/|$)          { deny all; return 403; }

    # XML-RPC — brute force + pingback amplification
    location ~* ^/xmlrpc\.php$                { deny all; return 403; }

    # Never execute PHP from writable dirs (classic webshell drop points)
    location ~* ^/wp-content/uploads/.*\.php$  { deny all; return 403; }
    location ~* ^/wp-content/cache/.*\.php$    { deny all; return 403; }
    location ~* ^/wp-content/upgrade/.*\.php$  { deny all; return 403; }

    # Hide REST user enumeration
    location = /wp-json/wp/v2/users           { deny all; return 403; }

"""

src = open(CONF, encoding="utf-8").read()

if "/wp-json/batch" in src:
    print("ALREADY HARDENED - no change")
    sys.exit(0)

shutil.copy2(CONF, CONF + ".bak-20260914")
print("backup written:", CONF + ".bak-20260914")

anchor = "    client_max_body_size 64M;"
if anchor not in src:
    print("ANCHOR NOT FOUND - aborting")
    sys.exit(1)

out = src.replace(anchor, anchor + "\n" + BLOCK, 1)
open(CONF, "w", encoding="utf-8").write(out)
print("config updated")

r = subprocess.run(["nginx", "-t"], capture_output=True, text=True)
print("nginx -t:", r.stdout.strip() or r.stderr.strip())
