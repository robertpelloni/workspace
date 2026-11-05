#!/bin/bash
echo "=== waiting 20s for graceful shutdown ==="
sleep 20
echo
echo "=== service states ==="
for u in $(ls /etc/systemd/system/ | grep -E "^aimm-.*\.service$|^aimoney\.service$"); do
	printf "  %-34s active=%-10s enabled=%s\n" "$u" "$(systemctl is-active $u 2>/dev/null)" "$(systemctl is-enabled $u 2>/dev/null)"
done
echo
echo "=== remaining processes ==="
ps aux | grep -iE "aimoney|aimoneymachine|hustle" | grep -v grep | head -10
echo "(empty = clean)"
echo
echo "=== force-stop anything stubborn ==="
for u in aimm-orchestrator aimoney aimm-twitter; do
	if [ "$(systemctl is-active $u.service 2>/dev/null)" != "inactive" ] && [ "$(systemctl is-active $u.service 2>/dev/null)" != "failed" ]; then
		echo "  $u still $(systemctl is-active $u.service) — sending SIGKILL"
		systemctl kill -s SIGKILL $u.service 2>/dev/null
	fi
done
sleep 3
pkill -9 -f "/opt/aimoneymachine/orchestrator" 2>/dev/null && echo "  killed stray orchestrator"
pkill -9 -f "/opt/aimoney/hustle" 2>/dev/null && echo "  killed stray hustle"
sleep 2
echo
echo "=== FINAL process check ==="
ps aux | grep -iE "aimoney|aimoneymachine|hustle" | grep -v grep | head
echo "(empty above = all stopped)"
echo
echo "=== ports 8080/8082 (the daemons' APIs) ==="
ss -tlnp 2>/dev/null | grep -E ":8080|:8082" | head -4
echo "(empty = APIs down)"
echo
echo "=== system load / cpu ==="
uptime
echo
echo "=== top CPU now ==="
ps -eo pcpu,pmem,comm --sort=-pcpu | head -6
