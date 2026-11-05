#!/bin/bash
R=/var/www/aimoneymachine
PW=$(grep "DB_PASSWORD" $R/wp-config.php | cut -d"'" -f4)
DB=aimoneymachine_wp
U=wp_aimoneymachine

echo "=== Yoast noindex settings (what Yoast is told to exclude) ==="
cat >/tmp/y.php <<'PHP'
<?php
require_once('/var/www/aimoneymachine/wp-load.php');
$t = get_option('wpseo_titles', []);
if (!is_array($t)) { echo "no wpseo_titles\n"; exit; }
foreach ($t as $k => $v) {
    if (stripos($k, 'noindex') !== false || stripos($k, 'disable') !== false) {
        printf("  %-42s %s\n", $k, is_scalar($v) ? var_export($v, true) : gettype($v));
    }
}
echo "  --- media/attachment handling ---\n";
foreach (['disable-attachment','noindex-attachment','noindex-media','media'] as $k) {
    if (isset($t[$k])) printf("  %-42s %s\n", $k, var_export($t[$k], true));
}
PHP
php /tmp/y.php 2>&1 | head -40

echo
echo "=== front page / posts page ==="
cat >/tmp/f.php <<'PHP'
<?php
require_once('/var/www/aimoneymachine/wp-load.php');
foreach ([get_option('page_on_front'), get_option('page_for_posts')] as $id) {
    $p = get_post($id);
    printf("  ID %-6s slug=%-16s type=%-8s permalink=%s\n", $id, $p?$p->post_name:'?', $p?$p->post_type:'?', $p?get_permalink($id):'n/a');
}
PHP
php /tmp/f.php 2>&1 | head -5

echo
echo "=== live surface behaviour ==="
for u in "/" "/blog/" "/page/2/" "/page/3/" "/feed/" "/category/ai-automation/" "/category/ai-automation/page/2/"; do
	printf "  %-34s HTTP %s  redirect=%s\n" "$u" \
		"$(curl -s -o /dev/null -w '%{http_code}' -m 15 "https://aimoneymachine.site$u")" \
		"$(curl -s -o /dev/null -w '%{redirect_url}' -m 15 "https://aimoneymachine.site$u")"
done

echo
echo "=== canonical + robots on key pages ==="
for u in "/" "/page/2/" "/category/ai-automation/"; do
	echo "  --- $u ---"
	curl -s -m 20 "https://aimoneymachine.site$u" | grep -oiE "<link rel=[\"']canonical[\"'][^>]*>|<meta name=[\"']robots[\"'][^>]*>" | head -2 | sed 's/^/    /'
done

echo
echo "=== attachment page (1026 of them) ==="
ATT=$(mysql -u$U -p$PW $DB -N -B -e "SELECT ID FROM wp_posts WHERE post_type='attachment' AND post_status='inherit' LIMIT 1;" 2>/dev/null)
echo "  sample attachment id: $ATT"
curl -s -m 20 "https://aimoneymachine.site/?attachment_id=$ATT" | grep -oiE "<link rel=[\"']canonical[\"'][^>]*>|<meta name=[\"']robots[\"'][^>]*>|<title>[^<]*</title>" | head -3 | sed 's/^/    /'
curl -s -o /dev/null -w "    attachment page HTTP %{http_code}\n" -m 15 "https://aimoneymachine.site/?attachment_id=$ATT"
