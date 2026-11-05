#!/bin/bash
R=/srv/www/robertpelloni.com
PW=$(grep "DB_PASSWORD" $R/wp-config.php | cut -d"'" -f4)
DB=rp_wp
U=robertpelloni
M="mysql -u$U -p$PW $DB -N -B"

echo "=== DB options containing 'canonical' ==="
$M -e "SELECT option_name, LEFT(option_value,300) FROM wp_options WHERE option_value LIKE '%canonical%';" 2>/dev/null | head -20

echo
echo "=== DB options containing 'rel=\"canonical\"' or home_url paging patterns ==="
$M -e "SELECT option_name, LEFT(option_value,300) FROM wp_options WHERE option_value LIKE '%rel=%canonical%';" 2>/dev/null | head -10

echo
echo "=== head context lines 105-125 of /page/2/ ==="
curl -s -m 20 "https://robertpelloni.com/page/2/" | sed -n '100,126p' | sed 's/^/  /'

echo
echo "=== plugins with 'canonical' anywhere (incl. js/php) ==="
grep -rln "canonical" $R/wp-content/plugins/ 2>/dev/null | grep -v "/vendor/\|node_modules\|\.min\." | head -20

echo
echo "=== theme files with canonical ==="
grep -rln "canonical" $R/wp-content/themes/ 2>/dev/null | head -20
