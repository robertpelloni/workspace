#!/bin/bash
R=/srv/www/robertpelloni.com
PW=$(grep "DB_PASSWORD" $R/wp-config.php | cut -d"'" -f4)
DB=rp_wp
U=robertpelloni
M="mysql -u$U -p$PW $DB -N -B"

echo "=== the example posts ==="
$M -e "SELECT ID,post_status,post_type,LEFT(post_title,50),post_date,CHAR_LENGTH(post_content) FROM wp_posts WHERE ID IN (34958,41799,41869,37843,34947,37741);" 2>/dev/null

echo
echo "=== per-post feed: /41799-2/feed/ ==="
curl -s -o /dev/null -w "  HTTP %{http_code}  type=%{content_type}\n" -m 15 "https://robertpelloni.com/41799-2/feed/"

echo "=== feed <link> tags in a post head ==="
curl -s -m 20 "https://robertpelloni.com/41799-2/" | grep -iE "alternate.*(rss|feed)|rel=.canonical" | head -5

echo
echo "=== admin-ajax wp_statistics: what headers? ==="
curl -s -o /dev/null -D - -m 15 "https://robertpelloni.com/wp-admin/admin-ajax.php?action=wp_statistics_custom_event&nonce=ab12756abb" 2>/dev/null | grep -iE "^HTTP|robots|x-robots" | head -6

echo
echo "=== does core send X-Robots-Tag on wp-admin? ==="
curl -s -o /dev/null -D - -m 15 "https://robertpelloni.com/wp-admin/" 2>/dev/null | grep -iE "^HTTP|x-robots" | head -4

echo
echo "=== how many posts share a base slug (-2/-3 pattern)? ==="
$M -e "SELECT COUNT(*) AS total_posts FROM wp_posts WHERE post_type='post' AND post_status='publish';" 2>/dev/null
$M -e "SELECT post_name FROM wp_posts WHERE post_type='post' AND post_status='publish' AND post_name REGEXP '-[0-9]+$';" 2>/dev/null | wc -l
