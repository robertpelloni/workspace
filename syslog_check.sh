#!/bin/bash
R=/var/www/robertpelloni
echo "=== AI Engine plugin status on robertpelloni.com ==="
if [ -d "$R" ]; then
	sudo -u www-data wp plugin list --path=$R 2>/dev/null | grep -iE "ai-engine|ai_engine|aiengine" | head -5
	echo "--- all active plugins (robertpelloni) ---"
	sudo -u www-data wp plugin list --status=active --field=name --path=$R 2>/dev/null | head -25
else
	echo "  $R not found; searching for robertpelloni web root"
	ls -d /var/www/*obert* 2>/dev/null
fi
echo
echo "=== what is filling syslog? top repeating patterns ==="
tail -20000 /var/log/syslog 2>/dev/null | sed -E 's/^[A-Za-z]+ +[0-9]+ [0-9:]+ [^ ]+ //' | sed -E 's/[0-9]{2,}/N/g' | sort | uniq -c | sort -rn | head -12
echo
echo "=== AI Engine mentions in current syslog ==="
grep -c "AI Engine" /var/log/syslog 2>/dev/null
echo "=== AI Engine mentions in syslog.1 ==="
grep -c "AI Engine" /var/log/syslog.1 2>/dev/null
echo
echo "=== newest AI Engine line in syslog (is it still happening?) ==="
grep "AI Engine" /var/log/syslog 2>/dev/null | tail -2 | cut -c1-160
