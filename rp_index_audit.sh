#!/bin/bash
R=/srv/www/robertpelloni.com
PW=$(grep "DB_PASSWORD" $R/wp-config.php | cut -d"'" -f4)
DB=rp_wp
U=robertpelloni
M="mysql -u$U -p$PW $DB -N -B"

echo "=== active plugins ==="
mysql -u"$U" -p"$PW" "$DB" -N -B -e "SELECT option_value FROM wp_options WHERE option_name='active_plugins';" 2>/dev/null |
	tr ';' '\n' | grep -oE '"[^"]+\.php"' | tr -d '"'

echo
echo "=== robots.txt (live) ==="
curl -s -m 15 https://robertpelloni.com/robots.txt | head -25

echo
echo "=== blog_public / front page ==="
$M -e "SELECT option_name,option_value FROM wp_options WHERE option_name IN ('blog_public','show_on_front','page_on_front','blogdescription');" 2>/dev/null

echo
echo "=== post counts ==="
$M -e "SELECT post_type,post_status,COUNT(*) FROM wp_posts GROUP BY post_type,post_status ORDER BY post_type,post_status;" 2>/dev/null

echo
echo "=== Yoast index/noindex related options ==="
$M -e "SELECT option_name, LEFT(option_value,100) FROM wp_options WHERE option_name LIKE '%yoast%' LIMIT 25;" 2>/dev/null

echo
echo "=== noindex meta count in postmeta ==="
$M -e "SELECT meta_key, COUNT(*) FROM wp_postmeta WHERE meta_key LIKE '%noindex%' GROUP BY meta_key;" 2>/dev/null
$M -e "SELECT meta_value, COUNT(*) FROM wp_postmeta WHERE meta_key='_yoast_wpseo_meta-robots-noindex' GROUP BY meta_value;" 2>/dev/null
