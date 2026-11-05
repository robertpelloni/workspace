#!/bin/bash
ROOT=/var/www/aimoneymachine
PW=$(grep "DB_PASSWORD" $ROOT/wp-config.php | cut -d"'" -f4)
DB=aimoneymachine_wp
U=wp_aimoneymachine
M="mysql -u$U -p$PW $DB -N -B"

echo "=== JWT secret strength (no values shown) ==="
python3 - <<'PY'
import re
s = open('/var/www/aimoneymachine/wp-config.php', encoding='utf-8', errors='replace').read()
for m in re.finditer(r"define\s*\(\s*['\"]JWT_AUTH_SECRET_KEY['\"]\s*,\s*['\"](.*?)['\"]\s*\)", s, re.S):
    v = m.group(1)
    print(f"  found secret: length={len(v)}  is_wordpress_salt={'|' in v}  looks_default={v.lower() in ('secret','changeme','your-secret-key','',' ')}")
    print(f"    preview: {v[:6]}...{v[-4:]}")
print("  total JWT_AUTH_SECRET_KEY defines:", len(re.findall(r"JWT_AUTH_SECRET_KEY", s)))
print("  JWT_AUTH_CORS_ENABLE:", "yes" if "JWT_AUTH_CORS_ENABLE" in s else "no")
PY

echo
echo "=== test/auth helper scripts (attacker or dev?) ==="
for f in test-auth.php test-wp-auth.php test-rest-filter.php update_post.php ads.txt manifest.json sw.js; do
	echo "----- $f -----"
	cat "$ROOT/$f" 2>/dev/null | head -25
	echo
done

echo "=== KAMIKAZE payload: external refs / scripts ==="
$M -e "SELECT post_content FROM wp_posts WHERE ID=6064;" 2>/dev/null | grep -oiE "(src|href)=[\"'][^\"']{4,120}[\"']|https?://[a-z0-9./?=_%:-]{6,120}" | sort -u | head -30

echo
echo "=== other posts/pages with suspicious markers ==="
$M -e "SELECT ID,post_author,LEFT(post_title,50),LENGTH(post_content) FROM wp_posts WHERE (post_content LIKE '%KZFULL%' OR post_content LIKE '%kzfp%' OR post_content LIKE '%<script%' ) AND post_type IN ('post','page') LIMIT 20;" 2>/dev/null

echo
echo "=== mu-plugins / drop-ins ==="
ls -la $ROOT/wp-content/mu-plugins/ 2>/dev/null
ls -la $ROOT/wp-content/*.php 2>/dev/null

echo
echo "=== wp_options: recently added autoloaded options ==="
$M -e "SELECT option_name, LENGTH(option_value) FROM wp_options WHERE autoload='yes' AND option_name NOT LIKE '\_transient%' AND option_name NOT LIKE '%yoast%' ORDER BY LENGTH(option_value) DESC LIMIT 15;" 2>/dev/null
