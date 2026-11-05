#!/bin/bash
echo "=== CreateCheckoutSession (tier -> price id mapping) ==="
grep -n -A 45 "func .*CreateCheckoutSession(ctx" /opt/marketing_agent/internal/billing/billing.go | head -55
echo
echo "=== priceIDForTier / tier mapping ==="
grep -n -B3 -A 25 "func .*priceIDForTier\|priceForTier\|PriceID" /opt/marketing_agent/internal/billing/billing.go | head -50
