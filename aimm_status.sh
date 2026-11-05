#!/bin/bash
echo "=== STATUS.json (money machine ledger) ==="
for f in /opt/aimoneymachine/STATUS.json /opt/aimoney/STATUS.json; do
	[ -f "$f" ] && {
		echo "--- $f ---"
		cat "$f" | head -12
		echo
	}
done
echo "=== all aimm-* services ==="
systemctl list-units 'aimm-*' --type=service --all --no-pager 2>/dev/null | grep -E "aimm-" | awk '{print "  "$1, $3, $4}' | head -12
echo
echo "=== is the old /opt/aimoney duplicate referenced anywhere? ==="
ls -la /opt/aimoney/ 2>/dev/null | head -8
echo "--- unit files pointing at /opt/aimoney ---"
grep -rl "/opt/aimoney" /etc/systemd/system/ 2>/dev/null | head -5
echo "(none above = it is an orphan process, not a managed service)"
echo
echo "=== total CPU burned by the two daemons ==="
ps -o pid,etime,time,pcpu,cmd -p 2364672,3770691 2>/dev/null
