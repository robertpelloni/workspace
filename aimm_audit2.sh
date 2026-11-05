#!/bin/bash
ROOT=/var/www/aimoneymachine
PW=$(grep "DB_PASSWORD" $ROOT/wp-config.php | cut -d"'" -f4)
DB=$(grep "DB_NAME" $ROOT/wp-config.php | cut -d"'" -f4)
U=$(grep "DB_USER" $ROOT/wp-config.php | cut -d"'" -f4)
M="mysql -u$U -p$PW $DB -N -B"

echo "=== JWT AUTH CONFIG in wp-config ==="
grep -iE "jwt|secret" $ROOT/wp-config.php | sed 's/\(SECRET[_A-Z]*.,[[:space:]]*.\)[^'"'"']*/\1***REDACTED***/I'

echo
echo "=== KAMIKAZE POST (id 6064) ==="
$M -e "SELECT ID,post_author,post_date,post_status,post_title,post_name,LENGTH(post_content) FROM wp_posts WHERE ID=6064;" 2>/dev/null
echo "--- content (first 1200 chars) ---"
$M -e "SELECT LEFT(post_content,1200) FROM wp_posts WHERE ID=6064;" 2>/dev/null

echo
echo "=== POSTS BY ROGUE AUTHORS ==="
$M -e "SELECT p.ID,p.post_date,p.post_status,LEFT(p.post_title,60),p.post_author,u.user_login FROM wp_posts p JOIN wp_users u ON p.post_author=u.ID WHERE p.post_author>1 AND p.post_type IN ('post','page') ORDER BY p.ID DESC LIMIT 30;" 2>/dev/null

echo
echo "=== ROGUE USERS: login/IP metadata ==="
$M -e "SELECT user_id,meta_key,LEFT(meta_value,90) FROM wp_usermeta WHERE user_id>1 AND meta_key NOT LIKE '%capabilities%' AND meta_key NOT LIKE '%user_level%' LIMIT 40;" 2>/dev/null

echo
echo "=== WP_CRON HOOKS (possible injected) ==="
$M -e "SELECT LEFT(option_value,2000) FROM wp_options WHERE option_name='cron';" 2>/dev/null | head -c 1800

echo
echo
echo "=== RECENTLY MODIFIED PHP FILES (last 30 days) ==="
find $ROOT -name "*.php" -mtime -30 -printf "%TY-%Tm-%Td %TH:%TM  %10s  %p\n" 2>/dev/null | sort -r | head -30

echo
echo "=== .htaccess ==="
cat $ROOT/.htaccess 2>/dev/null

echo
echo "=== suspicious top-level files ==="
ls -la $ROOT/*.php $ROOT/*.txt 2>/dev/null
