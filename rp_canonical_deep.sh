#!/bin/bash
R=/srv/www/robertpelloni.com
PW=$(grep "DB_PASSWORD" $R/wp-config.php | cut -d"'" -f4)
DB=rp_wp
U=robertpelloni
M="mysql -u$U -p$PW $DB -N -B"

echo "=== permalink structure ==="
$M -e "SELECT option_name,option_value FROM wp_options WHERE option_name IN ('permalink_structure','show_on_front','page_on_front','page_for_posts','blogname');" 2>/dev/null

echo
echo "=== all canonical-ish hooks registered ==="
grep -rn "rel_canonical\|wp_get_canonical_url\|'canonical'" $R/wp-content/plugins/*/ $R/wp-content/themes/ 2>/dev/null |
	grep -v "/vendor/\|node_modules\|\.min\." | head -20

echo
echo "=== raw <head> canonical lines on /page/2/ ==="
curl -s -m 20 "https://robertpelloni.com/page/2/" | grep -inE "canonical|<title>" | head -10

echo
echo "=== does post ID 2 exist? ==="
$M -e "SELECT ID,post_title,post_status,post_type,post_name FROM wp_posts WHERE ID IN (2,3,41027) OR post_name IN ('2','3');" 2>/dev/null

echo
echo "=== what does wp_get_canonical_url return on /page/2/? ==="
cat >/tmp/rp_canon_test.php <<'PHP'
<?php
$_SERVER['REQUEST_URI'] = '/page/2/';
$_SERVER['HTTP_HOST']   = 'robertpelloni.com';
$_SERVER['REQUEST_METHOD'] = 'GET';
require_once('/srv/www/robertpelloni.com/wp-load.php');
echo "is_singular:   " . var_export(is_singular(), true) . "\n";
echo "is_home:       " . var_export(is_home(), true) . "\n";
echo "is_archive:    " . var_export(is_archive(), true) . "\n";
echo "is_paged:      " . var_export(is_paged(), true) . "\n";
echo "get_query_var(paged): " . get_query_var('paged') . "\n";
echo "get_query_var(page):  " . get_query_var('page') . "\n";
$qo = get_queried_object();
echo "queried object: " . (is_object($qo) ? get_class($qo) . ' #' . ($qo->ID ?? '?') . ' ' . ($qo->post_name ?? '') : var_export($qo, true)) . "\n";
echo "wp_get_canonical_url: " . var_export(wp_get_canonical_url(), true) . "\n";
PHP
php /tmp/rp_canon_test.php 2>&1 | head -20
