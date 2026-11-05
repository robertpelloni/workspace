#!/bin/bash
echo "=== web roots ==="
ls -d /var/www/*/ 2>/dev/null
echo
echo "=== nginx server_name -> root for hypernexus.site ==="
grep -rn "hypernexus" /etc/nginx/sites-enabled/ 2>/dev/null | head -20
echo
echo "=== systemd units mentioning billing/hypernexus ==="
systemctl list-units --type=service --all 2>/dev/null | grep -iE "hypernexus|billing|api" | head -10
echo
echo "=== find billing handler files ==="
find /var/www /opt /srv -maxdepth 4 -type f \( -name "*.go" -o -name "*.py" -o -name "*.js" -o -name "*.ts" \) 2>/dev/null | xargs grep -ln "billing/checkout\|billing/plans" 2>/dev/null | head -10
echo
echo "=== stripe env keys present? ==="
find /var/www /opt /srv -maxdepth 3 -name ".env*" 2>/dev/null | head -10
