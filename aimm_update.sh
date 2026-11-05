#!/bin/bash
R=/var/www/aimoneymachine
D=/root/aimm-incident-20260914
PW=$(grep "DB_PASSWORD" $R/wp-config.php | cut -d"'" -f4)
DB=aimoneymachine_wp
U=wp_aimoneymachine

echo "=== backing up DB before core update ==="
mysqldump -u"$U" -p"$PW" "$DB" 2>/dev/null | gzip >"$D/pre-update-7.0.sql.gz"
ls -lh "$D/pre-update-7.0.sql.gz" | awk '{print "  "$5, $9}'

echo
echo "=== version before ==="
sudo -u www-data wp core version --path="$R" 2>&1

echo
echo "=== running core update ==="
sudo -u www-data wp core update --path="$R" 2>&1 | tail -20

echo
echo "=== version after ==="
sudo -u www-data wp core version --path="$R" 2>&1

echo
echo "=== database upgrade (if needed) ==="
sudo -u www-data wp core update-db --path="$R" 2>&1 | tail -8
