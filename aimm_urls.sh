#!/bin/bash
R=/var/www/aimoneymachine
PW=$(grep "DB_PASSWORD" $R/wp-config.php | cut -d"'" -f4)
DB=aimoneymachine_wp
U=wp_aimoneymachine
cat >/tmp/u.php <<'PHP'
<?php
require_once('/var/www/aimoneymachine/wp-load.php');
// a duplicate group from the audit
foreach ([5469, 5126, 5349, 5391, 168] as $id) {
    $p = get_post($id);
    if ($p) printf("  id=%-6s slug=%-58s\n     permalink=%s\n", $id, substr($p->post_name,0,58), get_permalink($id));
}
echo "\n  permalink_structure: " . get_option('permalink_structure') . "\n";
PHP
php /tmp/u.php 2>&1 | head -20

echo
echo "=== live status of a few ==="
for s in best-ai-tools-for-document-processing-and-extraction best-ai-tools-for-document-processing-and-extraction-2 best-ai-tools-for-document-processing-and-extraction-3; do
	for suf in "" "/" ".htm"; do
		printf "  %-72s HTTP %s\n" "/$s$suf" "$(curl -s -o /dev/null -w '%{http_code}' -m 15 "https://aimoneymachine.site/$s$suf")"
	done
done

echo
echo "=== blog pagination ==="
for u in "/blog" "/blog/page/2" "/blog/page/3" "/blog/page/40"; do
	printf "  %-18s HTTP %s\n" "$u" "$(curl -s -o /dev/null -w '%{http_code}' -m 15 "https://aimoneymachine.site$u")"
done

echo
echo "=== how many /page/N/ exist? ==="
for n in 2 3 5 10 20 40; do
	printf "  /page/%-3s HTTP %s\n" "$n" "$(curl -s -o /dev/null -w '%{http_code}' -m 15 "https://aimoneymachine.site/page/$n/")"
done
