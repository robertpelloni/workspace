#!/bin/bash
echo "=== billing package files ==="
ls /opt/marketing_agent/internal/billing/ 2>/dev/null
echo
echo "=== CreateCheckoutSessionWithPrice implementation ==="
grep -rn -A 60 "func .*CreateCheckoutSessionWithPrice" /opt/marketing_agent/internal/billing/ 2>/dev/null | head -75
