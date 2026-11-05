#!/bin/bash
R=/srv/www/robertpelloni.com
echo "=== who emits rel=canonical? ==="
grep -rn "canonical" $R/wp-content/themes/ $R/wp-content/plugins/ $R/wp-content/mu-plugins/ 2>/dev/null |
	grep -vi "\.min\.\|node_modules\|/vendor/\|\.map:" |
	grep -iE "canonical" | grep -iE "add_action|add_filter|rel=|link rel|<link" | head -25

echo
echo "=== mu-plugins present ==="
ls -la $R/wp-content/mu-plugins/ 2>/dev/null

echo
echo "=== theme functions referencing pagination/canonical ==="
grep -rn "rel_canonical\|get_pagenum_link\|paged" $R/wp-content/themes/blank-canvas/functions.php $R/wp-content/themes/blank-canvas/inc/*.php 2>/dev/null | head -20

echo
echo "=== parent (seedlet) canonical? ==="
grep -rn "canonical\|wp_head" $R/wp-content/themes/seedlet/functions.php 2>/dev/null | head -15
