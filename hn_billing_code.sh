#!/bin/bash
echo "=== stripe-related env in marketing_agent (keys masked) ==="
sed -n 's/\(STRIPE[^=]*\)=.*/\1=<set>/p' /opt/marketing_agent/.env 2>/dev/null
echo
echo "=== billing handler in server.go ==="
grep -n "billing\|Checkout\|PriceData\|price_data\|PriceID\|price_\|LineItem" /opt/marketing_agent/internal/web/server.go | head -40
