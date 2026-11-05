#!/bin/bash
echo "=== disk headroom ==="
df -h / | tail -1
echo
echo "=== top-level sizes ==="
for d in /opt/aimoneymachine /opt/aimoney /var/www/aimoneymachine; do
	[ -e "$d" ] && echo "  $(du -sh "$d" 2>/dev/null)"
done
echo
echo "=== biggest things inside /opt/aimoneymachine ==="
du -sh /opt/aimoneymachine/* 2>/dev/null | sort -rh | head -20
echo
echo "=== biggest inside /opt/aimoney ==="
du -sh /opt/aimoney/* 2>/dev/null | sort -rh | head -8
echo
echo "=== MySQL databases ==="
mysql -N -B -e "SELECT table_schema, ROUND(SUM(data_length+index_length)/1024/1024,1) AS mb FROM information_schema.tables GROUP BY table_schema ORDER BY SUM(data_length+index_length) DESC;" 2>/dev/null | head -12
echo
echo "=== aimm systemd units ==="
ls /etc/systemd/system/ | grep -iE "aimm|aimoney" | head -20
echo
echo "=== related cron ==="
crontab -l 2>/dev/null | grep -icE "aimm|hustle|aimoney"
ls /etc/cron.d/ 2>/dev/null | head -10
