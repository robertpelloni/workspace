#!/bin/bash
R=/var/www/aimoneymachine
echo "=== existing pages ==="
sudo -u www-data wp post list --post_type=page --fields=ID,post_title,post_name,post_status --path=$R 2>&1 | head -20
echo
echo "=== total posts/pages ==="
sudo -u www-data wp post list --post_type=post --format=count --path=$R 2>&1
echo
echo "=== mu-plugins ==="
ls -la $R/wp-content/mu-plugins/ 2>&1
echo
echo "=== payment-related plugins ==="
sudo -u www-data wp plugin list --path=$R 2>&1 | grep -iE "woo|stripe|paypal|payment|member|subscri|form" | head -10
echo "(end plugins)"
echo
echo "=== active theme ==="
sudo -u www-data wp theme list --status=active --field=name --path=$R 2>&1
echo
echo "=== permalink structure ==="
sudo -u www-data wp option get permalink_structure --path=$R 2>&1
