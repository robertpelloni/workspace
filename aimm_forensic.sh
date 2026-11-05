#!/bin/bash
ROOT=/var/www/aimoneymachine
PW=$(grep "DB_PASSWORD" $ROOT/wp-config.php | cut -d"'" -f4)
DB=aimoneymachine_wp
U=wp_aimoneymachine
M="mysql -u$U -p$PW $DB -N -B"

echo "=== ACTIVE PLUGINS with versions ==="
$M -e "SELECT option_value FROM wp_options WHERE option_name='active_plugins';" 2>/dev/null | tr ';' '\n' | grep -oE '"[^"]+\.php"' | tr -d '"' | while read p; do
	v=$(grep -m1 -iE "^[[:space:]]*\*?[[:space:]]*Version:" "$ROOT/wp-content/plugins/$p" 2>/dev/null | head -1)
	[ -z "$v" ] && v=$(grep -m1 -iE "Version:" "$ROOT/wp-content/plugins/$(dirname $p)/$(basename $p)" 2>/dev/null | head -1)
	printf "  %-58s %s\n" "$p" "$v"
done

echo
echo "=== Wordfence present? log files ==="
ls -la $ROOT/wp-content/wflogs/ 2>/dev/null | head -12
ls -la $ROOT/wp-content/uploads/wflogs 2>/dev/null | head

echo
echo "=== nginx access logs available ==="
ls -la /var/log/nginx/ 2>/dev/null | head -20

echo
echo "=== search access logs for aimoneymachine + user-creating requests ==="
for f in /var/log/nginx/*.log /var/log/nginx/*.gz; do
	[ -e "$f" ] || continue
	case "$f" in
	*.gz) C="zgrep" ;;
	*) C="grep" ;;
	esac
	echo "--- $f ---"
	$C -h "aimoneymachine" "$f" 2>/dev/null | grep -iE "POST (/wp-json|/wp-admin|/xmlrpc)" | tail -25
done 2>/dev/null | head -80
