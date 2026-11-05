#!/bin/bash
R=/var/www/aimoneymachine
echo "=== registered menus ==="
sudo -u www-data wp menu list --fields=term_id,name,slug,count --path=$R 2>&1
echo
echo "=== menu locations ==="
sudo -u www-data wp menu location list --path=$R 2>&1
echo
echo "=== items in primary-ish menus ==="
for m in $(sudo -u www-data wp menu list --field=slug --path=$R 2>/dev/null); do
	echo "--- menu: $m ---"
	sudo -u www-data wp menu item list "$m" --fields=title,type,object,url --path=$R 2>&1 | head -12
done
