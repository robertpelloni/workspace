#!/bin/bash
set -e
R=/srv/www/robertpelloni.com
PW=$(grep "DB_PASSWORD" $R/wp-config.php | cut -d"'" -f4)
DB=rp_wp
U=robertpelloni
M="mysql -u$U -p$PW $DB"

echo "=== BEFORE ==="
mysql -u"$U" -p"$PW" "$DB" -N -B -e "SELECT option_name,option_value FROM wp_options WHERE option_name IN ('posts_per_page','posts_per_rss');" 2>/dev/null

echo "=== applying ==="
$M -e "UPDATE wp_options SET option_value='12' WHERE option_name='posts_per_page';" 2>/dev/null
$M -e "UPDATE wp_options SET option_value='20' WHERE option_name='posts_per_rss';" 2>/dev/null

echo "=== AFTER ==="
mysql -u"$U" -p"$PW" "$DB" -N -B -e "SELECT option_name,option_value FROM wp_options WHERE option_name IN ('posts_per_page','posts_per_rss');" 2>/dev/null

echo
echo "=== flush caches ==="
rm -f $R/wp-content/cache/*.html 2>/dev/null || true
sudo -u www-data wp cache flush --path=$R 2>&1 | tail -1 || true

echo
echo "=== robots.txt: block feeds ==="
cat >$R/robots.txt <<'EOF'
User-agent: ia_archiver
Disallow: /

#WP Import Export Rule
User-agent: *
Disallow: /wp-admin/
Disallow: /wp-content/uploads/wp-import-export-lite/
Disallow: /wp-json/
Disallow: /*/feed/
Disallow: /*/trackback/
Disallow: /?s=
Disallow: /*&s=
Disallow: /search/
Disallow: /*?replytocom=
Disallow: /page/

# Discover the sitemap (was missing entirely)
Sitemap: https://robertpelloni.com/wp-sitemap.xml
EOF
chown www-data:www-data $R/robots.txt
chmod 644 $R/robots.txt
echo "  written"
cat $R/robots.txt
