#!/bin/bash
echo "=== GET (no body) ==="
curl -s -o /dev/null -w "  GET  -> HTTP %{http_code}\n" \
	https://aimoneymachine.site/api/v1/billing/checkout \
	--resolve aimoneymachine.site:443:127.0.0.1 -k 2>&1
echo "=== POST empty json ==="
curl -s -w "  POST -> HTTP %{http_code}\n" -o /tmp/b500.html \
	-X POST https://aimoneymachine.site/api/v1/billing/checkout \
	--resolve aimoneymachine.site:443:127.0.0.1 -k \
	-H "Content-Type: application/json" -d '{}' 2>&1
echo "--- body head ---"
head -c 300 /tmp/b500.html
echo
echo
echo "=== recent php/nginx errors for aimoneymachine ==="
tail -5 /var/log/nginx/error.log 2>/dev/null
