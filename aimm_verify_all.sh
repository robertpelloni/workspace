#!/bin/bash
R=/var/www/aimoneymachine
echo "=== version / plugins / users ==="
echo "  core:    $(sudo -u www-data wp core version --path=$R 2>/dev/null)"
echo "  plugins: $(sudo -u www-data wp plugin list --status=active --field=name --path=$R 2>/dev/null | tr '\n' ' ')"
echo "  users:   $(sudo -u www-data wp user list --field=user_login --path=$R 2>/dev/null | tr '\n' ' ')"
echo "  admins:  $(sudo -u www-data wp user list --role=administrator --field=user_login --path=$R 2>/dev/null | tr '\n' ' ')"
echo "  JWT installed but inactive: $(sudo -u www-data wp plugin get jwt-authentication-for-wp-rest-api --field=status --path=$R 2>/dev/null || echo n/a)"

echo
echo "=== flush cache ==="
sudo -u www-data wp cache flush --path=$R 2>&1 | tail -2
sudo -u www-data wp super-cache flush --path=$R 2>&1 | tail -2 || true

echo
echo "=== live checks ==="
for u in "https://aimoneymachine.site/" \
	"https://aimoneymachine.site/wp-json/batch/v1" \
	"https://aimoneymachine.site/wp-json/jwt-auth/v1/token" \
	"https://aimoneymachine.site/xmlrpc.php" \
	"https://aimoneymachine.site/wp-login.php" \
	"https://aimoneymachine.site/sitemap_index.xml"; do
	printf "  %s  %s\n" "$(curl -s -o /dev/null -w '%{http_code}' -m 20 "$u")" "$u"
done

echo
echo "=== defacement still gone? ==="
curl -s -m 20 "https://aimoneymachine.site/?cb=$RANDOM" | grep -ci "KZFULL\|kzfp\|kamikaze"
echo "  (0 = clean)"
