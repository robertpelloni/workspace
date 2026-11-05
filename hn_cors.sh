#!/bin/bash
echo "=== setCORSHeaders ==="
sed -n '145,175p' /opt/marketing_agent/internal/web/server.go
echo
echo "=== nginx: /api/v1 routing ==="
grep -n -B2 -A3 "api/v1" /etc/nginx/sites-enabled/hypernexus.site | head -30
echo
echo "=== aimoneymachine nginx root/site ==="
grep -n "server_name\|root\|location" /etc/nginx/sites-enabled/aimoneymachine.site 2>/dev/null | head -20
