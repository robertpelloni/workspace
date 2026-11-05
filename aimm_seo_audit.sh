#!/bin/bash
R=/var/www/aimoneymachine
PW=$(grep "DB_PASSWORD" $R/wp-config.php | cut -d"'" -f4)
DB=aimoneymachine_wp
U=wp_aimoneymachine
M="mysql -u$U -p$PW $DB -N -B"

echo "=== core settings ==="
$M -e "SELECT option_name,option_value FROM wp_options WHERE option_name IN
 ('show_on_front','page_on_front','page_for_posts','posts_per_page','posts_per_rss','blog_public','permalink_structure','blogname');" 2>/dev/null

echo
echo "=== post counts ==="
$M -e "SELECT post_type,post_status,COUNT(*) FROM wp_posts GROUP BY post_type,post_status ORDER BY post_type,post_status;" 2>/dev/null

echo
echo "=== categories / tags ==="
$M -e "SELECT tt.taxonomy, t.name, t.slug, tt.count FROM wp_terms t JOIN wp_term_taxonomy tt ON t.term_id=tt.term_id WHERE tt.taxonomy IN ('category','post_tag') ORDER BY tt.count DESC LIMIT 20;" 2>/dev/null

echo
echo "=== Yoast: indexation-relevant options ==="
$M -e "SELECT option_name, LEFT(option_value,160) FROM wp_options WHERE option_name LIKE 'wpseo%' AND (option_name LIKE '%noindex%' OR option_name LIKE '%titles%' OR option_name LIKE '%social%' OR option_name='wpseo');" 2>/dev/null | head -20

echo
echo "=== Yoast: meta-robots noindex overrides per post ==="
$M -e "SELECT meta_value, COUNT(*) FROM wp_postmeta WHERE meta_key='_yoast_wpseo_meta-robots-noindex' GROUP BY meta_value;" 2>/dev/null
echo "(empty = none set)"

echo
echo "=== physical robots.txt? ==="
ls -la $R/robots.txt 2>/dev/null || echo "  none (WordPress/Yoast serves a virtual one)"

echo
echo "=== live robots.txt ==="
curl -s -m 15 https://aimoneymachine.site/robots.txt | head -20

echo
echo "=== sitemap ==="
for u in /sitemap_index.xml /wp-sitemap.xml /sitemap.xml; do
	printf "  %-22s HTTP %s\n" "$u" "$(curl -s -o /dev/null -w '%{http_code}' -m 15 "https://aimoneymachine.site$u")"
done

echo
echo "=== attachments ==="
$M -e "SELECT COUNT(*) FROM wp_posts WHERE post_type='attachment';" 2>/dev/null
