#!/bin/bash
ROOT=/var/www/aimoneymachine
PW=$(grep "DB_PASSWORD" $ROOT/wp-config.php | cut -d"'" -f4); DB=aimoneymachine_wp; U=wp_aimoneymachine
M="mysql -u$U -p$PW $DB"

echo "=== BEFORE: users=$(mysql -u$U -p$PW $DB -N -B -e 'SELECT COUNT(*) FROM wp_users;' 2>/dev/null) posts_by_rogue=$(mysql -u$U -p$PW $DB -N -B -e 'SELECT COUNT(*) FROM wp_posts WHERE post_author>1;' 2>/dev/null) ==="

echo "=== deleting the Kamikaze defacement (post 6064) + its meta ==="
$M -e "DELETE FROM wp_postmeta WHERE post_id=6064; DELETE FROM wp_posts WHERE ID=6064;" 2>/dev/null && echo "  done"

echo "=== deleting rogue administrators (all users with ID > 1) ==="
$M -e "DELETE FROM wp_usermeta WHERE user_id > 1; DELETE FROM wp_users WHERE ID > 1;" 2>/dev/null && echo "  done"

echo "=== clearing any transient/cache leftovers ==="
$M -e "DELETE FROM wp_options WHERE option_name LIKE '%_transient_%' OR option_name LIKE '%_site_transient_%';" 2>/dev/null && echo "  done"

echo
echo "=== AFTER ==="
echo "users:"
mysql -u$U -p$PW $DB -N -B -e "SELECT ID,user_login,user_email FROM wp_users;" 2>/dev/null
echo "remaining posts by non-admin authors: $(mysql -u$U -p$PW $DB -N -B -e 'SELECT COUNT(*) FROM wp_posts WHERE post_author>1;' 2>/dev/null)"
echo "Kamikaze still present: $(mysql -u$U -p$PW $DB -N -B -e \"SELECT COUNT(*) FROM wp_posts WHERE ID=6064 OR post_content LIKE '%KZFULL%';\" 2>/dev/null)"
