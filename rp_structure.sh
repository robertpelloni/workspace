#!/bin/bash
R=/srv/www/robertpelloni.com
PW=$(grep "DB_PASSWORD" $R/wp-config.php | cut -d"'" -f4)
DB=rp_wp
U=robertpelloni
M="mysql -u$U -p$PW $DB -N -B"

echo "=== front page / posts page config ==="
$M -e "SELECT option_name,option_value FROM wp_options WHERE option_name IN ('show_on_front','page_on_front','page_for_posts');" 2>/dev/null

echo
echo "=== page 41027 (front) and 12572 (posts page) ==="
$M -e "SELECT ID,post_title,post_name,post_status,post_type,CHAR_LENGTH(post_content) FROM wp_posts WHERE ID IN (41027,12572);" 2>/dev/null

echo
echo "=== permalinks for those ==="
cat >/tmp/pl.php <<'PHP'
<?php
require_once('/srv/www/robertpelloni.com/wp-load.php');
foreach ([41027, 12572] as $id) {
    $p = get_post($id);
    printf("  ID %d  slug=%-14s status=%-8s permalink=%s\n",
        $id, $p ? $p->post_name : '?', $p ? $p->post_status : '?',
        $p ? get_permalink($id) : 'n/a');
}
echo "  home_url:       " . home_url('/') . "\n";
echo "  get_permalink(page_for_posts): " . get_permalink(get_option('page_for_posts')) . "\n";
PHP
php /tmp/pl.php 2>&1 | head -10

echo
echo "=== is the blog reachable? try the posts page + posts/ ==="
for u in "/" "/posts/" "/blog/" "/home/" "/12572/"; do
	printf "  %s  -> HTTP %s\n" "$u" "$(curl -s -o /dev/null -w '%{http_code}' -m 15 "https://robertpelloni.com$u")"
done

echo
echo "=== do any published posts appear in the menu? (nav_menu_item targets) ==="
$M -e "SELECT p.ID, LEFT(p.post_title,40), pm.meta_value FROM wp_posts p LEFT JOIN wp_postmeta pm ON p.ID=pm.post_id AND pm.meta_key='_menu_item_object_id' WHERE p.post_type='nav_menu_item' AND p.post_status='publish';" 2>/dev/null | head -20
