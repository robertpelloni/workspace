#!/bin/bash
set -e
CONF=/etc/nginx/sites-available/aimoneymachine
STAMP=$(date +%Y%m%d-%H%M%S)

cp "$CONF" "$CONF.bak-$STAMP"
echo "backed up -> $CONF.bak-$STAMP"

if grep -q "api/v1/billing/checkout" "$CONF"; then
	echo "proxy already present — no change"
	exit 0
fi

python3 - <<'PY'
conf = "/etc/nginx/sites-available/aimoneymachine"
src = open(conf).read()

block = """    # --------------------------------------------------------------------
    # Honest Work Desk checkout (added 2026-09-16)
    #
    # Proxies to the marketing_agent billing service so the page can POST
    # same-origin. aimoneymachine.site is deliberately NOT in that service's
    # allowedOrigin() CORS list, so a direct browser call would be blocked;
    # routing through nginx sidesteps CORS entirely and needs no Go rebuild.
    # --------------------------------------------------------------------
    location = /api/v1/billing/checkout {
        proxy_pass http://127.0.0.1:8084/api/v1/billing/checkout;
        proxy_http_version 1.1;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
        proxy_connect_timeout 10s;
        proxy_read_timeout 30s;
    }

    location / {
        try_files $uri $uri/ /index.php?$args;
    }"""

old = """    location / {
        try_files $uri $uri/ /index.php?$args;
    }"""

assert src.count(old) == 1, f"expected exactly 1 'location /' block, found {src.count(old)}"
open(conf, "w").write(src.replace(old, block))
print("proxy block inserted")
PY

nginx -t
systemctl reload nginx
echo "nginx reloaded"
