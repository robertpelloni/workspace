#!/bin/bash
# Security audit for aimoneymachine.site WordPress
ROOT=/var/www/aimoneymachine
PW=$(grep "DB_PASSWORD" $ROOT/wp-config.php | cut -d"'" -f4)
DB=$(grep "DB_NAME" $ROOT/wp-config.php | cut -d"'" -f4)
USER=$(grep "DB_USER" $ROOT/wp-config.php | cut -d"'" -f4)
M="mysql -u$USER -p$PW $DB -N -B"

echo "=== USERS ==="
$M -e "SELECT ID,user_login,user_email,user_registered,user_status FROM wp_users ORDER BY ID;" 2>/dev/null

echo
echo "=== USER META: capabilities / roles ==="
$M -e "SELECT u.ID,u.user_login,m.meta_key,m.meta_value FROM wp_users u JOIN wp_usermeta m ON u.ID=m.user_id WHERE m.meta_key LIKE '%capabilities%' OR m.meta_key LIKE '%user_level%' ORDER BY u.ID;" 2>/dev/null

echo
echo "=== POST COUNTS BY TYPE/STATUS ==="
$M -e "SELECT post_type,post_status,COUNT(*) FROM wp_posts GROUP BY post_type,post_status ORDER BY post_type,post_status;" 2>/dev/null

echo
echo "=== RECENT POSTS (last 40) ==="
$M -e "SELECT ID,post_date,post_status,post_type,post_author,LEFT(post_title,70),LEFT(post_name,50) FROM wp_posts WHERE post_type IN ('post','page') ORDER BY post_date DESC LIMIT 40;" 2>/dev/null

echo
echo "=== ADMIN-ISH OPTIONS ==="
$M -e "SELECT option_name,LEFT(option_value,120) FROM wp_options WHERE option_name IN ('siteurl','home','admin_email','users_can_register','default_role','blog_public','template','stylesheet','active_plugins') ;" 2>/dev/null
