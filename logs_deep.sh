#!/bin/bash
echo "=== robertpelloni.com vhost root ==="
grep -A4 "server_name robertpelloni" /etc/nginx/sites-enabled/* 2>/dev/null | grep -E "server_name|root" | head -8
echo
echo "=== find its web root ==="
for d in /var/www/*/; do
	[ -f "$d/wp-config.php" ] && echo "  wp root: $d"
done
echo
echo "=== AI Engine plugin anywhere ==="
for d in /var/www/*/; do
	if [ -d "$d/wp-content/plugins" ]; then
		found=$(ls "$d/wp-content/plugins" 2>/dev/null | grep -i "ai-engine\|ai_engine")
		[ -n "$found" ] && echo "  $d -> $found"
	fi
done
echo
echo "=== hustle service (log spammer) ==="
systemctl status hustle --no-pager 2>&1 | head -8
echo
echo "=== full log inventory >1M ==="
find /var/log -type f -size +1M -exec ls -lSh {} \; 2>/dev/null | awk '{print $5, $9}' | head -20
echo
echo "=== logrotate configs present ==="
ls /etc/logrotate.d/ 2>/dev/null | head -20
