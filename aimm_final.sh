#!/bin/bash
ROOT=/var/www/aimoneymachine
PW=$(grep "DB_PASSWORD" $ROOT/wp-config.php | cut -d"'" -f4)
DB=aimoneymachine_wp
U=wp_aimoneymachine
M="mysql -u$U -p$PW $DB -N -B"

echo "=== FINAL STATE: aimoneymachine.site ==="
echo "users:        $($M -e 'SELECT COUNT(*) FROM wp_users;' 2>/dev/null)"
echo "admins:       $($M -e "SELECT COUNT(*) FROM wp_usermeta WHERE meta_key='wp_capabilities' AND meta_value LIKE '%administrator%';" 2>/dev/null)"
echo "reg open:     $($M -e "SELECT option_value FROM wp_options WHERE option_name='users_can_register';" 2>/dev/null)"
echo "posts(pub):   $($M -e "SELECT COUNT(*) FROM wp_posts WHERE post_type='post' AND post_status='publish';" 2>/dev/null)"
echo "defacement:   $($M -e "SELECT COUNT(*) FROM wp_posts WHERE post_content LIKE '%KZFULL%' OR post_content LIKE '%kzfp%';" 2>/dev/null)"
echo "suspicious author emails:"
$M -e "SELECT user_login,user_email FROM wp_users WHERE user_email NOT LIKE '%aimoneymachine%';" 2>/dev/null || echo "  none"

echo
echo "=== active plugins ==="
$M -e "SELECT option_value FROM wp_options WHERE option_name='active_plugins';" 2>/dev/null

echo
echo "=== mu-plugins referencing network calls (sanity) ==="
grep -lE "curl_exec|file_get_contents\(['\"]http|base64_decode|eval\(|shell_exec|system\(" $ROOT/wp-content/mu-plugins/*.php 2>/dev/null | head
echo "  (empty = nothing alarming)"

echo
echo "=== robertpelloni.com: JWT plugin present? ==="
ls -d /srv/www/robertpelloni.com/wp-content/plugins/jwt-authentication-for-wp-rest-api 2>/dev/null || echo "  not installed (missing JWT constant is harmless)"

echo
echo "=== recent batch/v1 attempts since the block ==="
grep -c "wp-json/batch" /var/log/nginx/access.log 2>/dev/null
echo "  (nginx now returns 403 for these)"

echo
echo "=== site status ==="
for u in "https://aimoneymachine.site/" "https://aimoneymachine.site/wp-json/batch/v1" "https://robertpelloni.com/"; do
	printf "  %s  %s\n" "$(curl -s -o /dev/null -w '%{http_code}' -m 15 "$u")" "$u"
done
