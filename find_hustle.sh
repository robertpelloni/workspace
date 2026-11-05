#!/bin/bash
R=/srv/www/robertpelloni.com
echo "=== robertpelloni.com AI Engine plugin ==="
if [ -d "$R" ]; then
	ls "$R/wp-content/plugins" 2>/dev/null | grep -i "ai" | head -10
	echo "--- status ---"
	sudo -u www-data wp plugin list --path=$R 2>/dev/null | grep -iE "ai-engine|ai_engine" | head -5
	echo "--- is it in active list? ---"
	sudo -u www-data wp plugin list --status=active --field=name --path=$R 2>/dev/null | tr '\n' ' ' | head -c 600
	echo
else
	echo "  $R missing"
fi
echo
echo "=== what is 'hustle'? ==="
pm2 list 2>/dev/null | head -20
echo "--- pm2 as root ---"
sudo -u root pm2 list 2>/dev/null | head -20
echo "--- docker containers ---"
docker ps --format '{{.Names}}\t{{.Image}}\t{{.Status}}' 2>/dev/null | head -10
echo
echo "=== recent hustle log lines (who writes them) ==="
grep -m3 "hustle\[" /var/log/syslog 2>/dev/null | cut -c1-200
echo
echo "=== UFW block rate in last 1000 syslog lines ==="
tail -1000 /var/log/syslog | grep -c "UFW BLOCK"
