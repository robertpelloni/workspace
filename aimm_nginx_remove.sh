#!/bin/bash
set -e
CONF=/etc/nginx/sites-available/aimoneymachine
STAMP=$(date +%Y%m%d-%H%M%S)

if ! grep -q "api/v1/billing/checkout" "$CONF"; then
	echo "proxy not present — nothing to do"
	exit 0
fi

cp "$CONF" "$CONF.bak-removed-$STAMP"

python3 - <<'PY'
conf = "/etc/nginx/sites-available/aimoneymachine"
src = open(conf).read()
start = src.find("    # --------------------------------------------------------------------\n    # Honest Work Desk checkout")
end = src.find("    location / {\n        try_files", start)
if start == -1 or end == -1:
    raise SystemExit("could not locate the proxy block")
src = src[:start] + src[end:]
open(conf, "w").write(src)
print("proxy block removed")
PY

nginx -t 2>&1 | tail -2
systemctl reload nginx
echo "nginx reloaded"
echo
echo "=== confirm the checkout path is no longer proxied ==="
curl -s -o /dev/null -w "  aimoneymachine.site/api/v1/billing/checkout -> HTTP %{http_code}\n" \
	-X POST https://aimoneymachine.site/api/v1/billing/checkout \
	--resolve aimoneymachine.site:443:127.0.0.1 -k \
	-H "Content-Type: application/json" -d '{}' 2>&1
