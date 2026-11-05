#!/bin/bash
echo "=== which nginx file serves aimoneymachine.site ==="
grep -rln "aimoneymachine" /etc/nginx/ 2>/dev/null
echo
echo "=== its server block ==="
for f in $(grep -rln "aimoneymachine" /etc/nginx/sites-enabled/ 2>/dev/null); do
	echo "--- $f ---"
	cat "$f"
done
