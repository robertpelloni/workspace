#!/bin/bash
echo "=== plugins status (ai engine / ai-related) ==="
sudo -u www-data wp plugin list --path=/var/www/aimoneymachine 2>/dev/null | grep -iE "ai|engine" | head -10
echo
echo "=== nginx log sizes ==="
ls -laSh /var/log/nginx/*.log 2>/dev/null | head -12
echo
echo "=== other big logs (>20M, excluding journal) ==="
find /var/log -type f -size +20M \( -name "*.log" -o -name "*log*" \) -exec ls -lSh {} \; 2>/dev/null | head -12
echo
echo "=== journal size ==="
journalctl --disk-usage 2>/dev/null
echo
echo "=== disk ==="
df -h / | tail -1
