#!/bin/bash
echo "=== handleCreateCheckout (full) ==="
sed -n '1352,1400p' /opt/marketing_agent/internal/web/server.go
echo
echo "=== CORS handling ==="
grep -rn "Access-Control-Allow-Origin\|cors\|CORS" /opt/marketing_agent/internal/web/server.go | head -12
echo
echo "=== stripe key mode (prefix only) ==="
grep -o 'STRIPE_API_KEY=sk_[a-z]*' /opt/marketing_agent/.env 2>/dev/null | sed 's/.*=//'
echo
echo "=== how marketing_agent is served (nginx -> ?) ==="
grep -n "location\|proxy_pass\|root" /etc/nginx/sites-enabled/hypernexus.site | head -20
