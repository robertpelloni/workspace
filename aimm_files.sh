#!/bin/bash
ROOT=/var/www/aimoneymachine
Q=/root/aimm-incident-20260914/quarantine
mkdir -p $Q

echo "=== verify defacement gone ==="
PW=$(grep "DB_PASSWORD" $ROOT/wp-config.php | cut -d"'" -f4)
DB=aimoneymachine_wp
U=wp_aimoneymachine
mysql -u$U -p$PW $DB -N -B -e "SELECT COUNT(*) AS kz_posts FROM wp_posts WHERE post_content LIKE '%KZFULL%';" 2>/dev/null

echo
echo "=== quarantining publicly-reachable / dangerous helper scripts ==="
for f in test-auth.php test-wp-auth.php test-rest-filter.php update_post.php regenerate-posts.php; do
	if [ -e "$ROOT/$f" ]; then
		mv "$ROOT/$f" "$Q/$f" && echo "  quarantined: $f"
	fi
done
ls -la $Q/

echo
echo "=== remaining web-root php/txt ==="
ls -la $ROOT/*.php $ROOT/*.txt 2>/dev/null | awk '{print "  "$1" "$3":"$4" "$9}'

echo
echo "=== nginx config for this site ==="
grep -rln "aimoneymachine" /etc/nginx/sites-enabled/ /etc/nginx/conf.d/ 2>/dev/null
