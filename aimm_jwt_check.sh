#!/bin/bash
ROOT=/var/www/aimoneymachine
echo "=== WP-CLI available? ==="
command -v wp || echo "  wp not on PATH"
ls $ROOT/wp-cli.phar 2>/dev/null || echo "  no wp-cli.phar"

echo
echo "=== who references JWT in site code? ==="
grep -rl "jwt" $ROOT/wp-content/mu-plugins/ $ROOT/*.php 2>/dev/null | head
echo "  ---"

echo "=== does any site code call the JWT endpoint? ==="
grep -rn "jwt-auth/v1/token\|JWT_AUTH" $ROOT/wp-content/mu-plugins/ 2>/dev/null | head

echo
echo "=== recent JWT token requests (are clients using it?) ==="
for f in /var/log/nginx/access.log /var/log/nginx/access.log.1; do
	[ -e "$f" ] || continue
	echo "--- $f ---"
	grep -c "jwt-auth/v1/token" "$f" 2>/dev/null
	grep "jwt-auth/v1/token" "$f" 2>/dev/null | tail -5
done
for f in /var/log/nginx/access.log.*.gz; do
	[ -e "$f" ] || continue
	n=$(zgrep -c "jwt-auth/v1/token" "$f" 2>/dev/null)
	[ "$n" != "0" ] && echo "  $f: $n hits"
done

echo
echo "=== application passwords in use (would survive JWT removal) ==="
PW=$(grep "DB_PASSWORD" $ROOT/wp-config.php | cut -d"'" -f4)
DB=aimoneymachine_wp
U=wp_aimoneymachine
mysql -u$U -p$PW $DB -N -B -e "SELECT user_id, meta_key FROM wp_usermeta WHERE meta_key LIKE '%application_password%';" 2>/dev/null
echo "  (empty = none)"
