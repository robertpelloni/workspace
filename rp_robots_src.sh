#!/bin/bash
R=/srv/www/robertpelloni.com
echo "=== who outputs the robots meta? (single-quoted = not core) ==="
grep -rn "name=.robots\|wp_robots\|max-image-preview" $R/wp-content/themes/ 2>/dev/null | grep -v "\.min\." | head -20
echo
echo "=== plugins doing the same ==="
grep -rln "wp_robots\|name=.robots" $R/wp-content/plugins/ 2>/dev/null | head -10
echo
echo "=== raw head snippet from author archive ==="
curl -s -m 20 "https://robertpelloni.com/author/robertpelloni/" | grep -iE "robots" | head -3
echo
echo "=== raw head snippet from an empty category ==="
curl -s -m 20 "https://robertpelloni.com/category/old-stuff/" | grep -iE "robots" | head -3
echo
echo "=== is /2026/07/ a 404 or empty date archive? ==="
curl -s -o /dev/null -w "  /2026/07/ HTTP %{http_code}\n" -m 15 "https://robertpelloni.com/2026/07/"
echo
echo "=== theme header.php robots handling ==="
grep -n "robots\|wp_head" $R/wp-content/themes/blank-canvas/*.php $R/wp-content/themes/seedlet/header.php 2>/dev/null | head -10
echo
echo "=== does the active theme call wp_head? ==="
grep -rn "wp_head" $R/wp-content/themes/blank-canvas/ $R/wp-content/themes/seedlet/header.php 2>/dev/null | head -5
