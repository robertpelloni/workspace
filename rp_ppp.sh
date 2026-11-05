#!/bin/bash
R=/srv/www/robertpelloni.com
PW=$(grep "DB_PASSWORD" $R/wp-config.php | cut -d"'" -f4)
DB=rp_wp
U=robertpelloni
M="mysql -u$U -p$PW $DB -N -B"
echo "=== posts_per_page + related ==="
$M -e "SELECT option_name,option_value FROM wp_options WHERE option_name IN ('posts_per_page','posts_per_rss','rss_use_excerpt','blog_public');" 2>/dev/null
echo
echo "=== published posts total / oldest / newest ==="
$M -e "SELECT COUNT(*), MIN(post_date), MAX(post_date) FROM wp_posts WHERE post_type='post' AND post_status='publish';" 2>/dev/null
echo
echo "=== posts by month ==="
$M -e "SELECT DATE_FORMAT(post_date,'%Y-%m') AS m, COUNT(*) FROM wp_posts WHERE post_type='post' AND post_status='publish' GROUP BY m ORDER BY m;" 2>/dev/null
echo
echo "=== categories with post counts ==="
$M -e "SELECT t.name, t.slug, tt.count FROM wp_terms t JOIN wp_term_taxonomy tt ON t.term_id=tt.term_id WHERE tt.taxonomy='category' ORDER BY tt.count DESC;" 2>/dev/null
echo
echo "=== templates the theme uses for archives ==="
ls $R/wp-content/themes/blank-canvas/ 2>/dev/null
echo "--- parent seedlet archive/index templates ---"
ls $R/wp-content/themes/seedlet/*.php 2>/dev/null | head -20
