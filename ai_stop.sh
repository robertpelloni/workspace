#!/bin/bash
echo "=== STOPPING AIMONEYMACHINE AUTOMATION ==="
echo
echo "--- state BEFORE (so we can restore exactly) ---"
systemctl list-units 'aimm-*' 'aimoney*' --type=service --all --no-pager --plain 2>/dev/null |
	awk '/loaded/{print $1, $3, $4}' | grep -vE "^\s*$" >/root/aimm-state-before.txt
cat /root/aimm-state-before.txt
echo
echo "--- timers before ---"
systemctl list-timers 'aimm-*' --all --no-pager 2>/dev/null | head -6 | tee /root/aimm-timers-before.txt
echo

echo "--- stopping timers first (so they don't restart services) ---"
for t in $(systemctl list-timers 'aimm-*' --all --no-pager --plain 2>/dev/null | awk '/aimm-.*\.timer/{print $NF}'); do
	systemctl stop "$t" 2>/dev/null && echo "  stopped timer $t"
	systemctl disable "$t" 2>/dev/null >/dev/null && echo "    disabled $t"
done

echo
echo "--- stopping + disabling services ---"
for u in $(systemctl list-units 'aimm-*' 'aimoney*' --type=service --all --no-pager --plain 2>/dev/null | awk '{print $1}' | grep -E "\.service$" | sort -u); do
	state=$(systemctl is-active "$u" 2>/dev/null)
	systemctl stop "$u" 2>/dev/null
	systemctl disable "$u" 2>/dev/null >/dev/null
	now=$(systemctl is-active "$u" 2>/dev/null)
	printf "  %-32s %-9s -> %s\n" "$u" "$state" "$now"
done

echo
echo "--- killing the orphan /opt/aimoney/hustle (not a systemd unit) ---"
for pid in $(pgrep -f "/opt/aimoney/hustle" 2>/dev/null); do
	echo "  killing pid $pid"
	kill "$pid" 2>/dev/null
done
sleep 3
for pid in $(pgrep -f "/opt/aimoney/hustle" 2>/dev/null); do
	echo "  still alive, SIGKILL pid $pid"
	kill -9 "$pid" 2>/dev/null
done

echo
echo "--- any aimm/aimoney processes left? ---"
ps aux | grep -iE "aimoney|aimoneymachine" | grep -v grep | head -10
echo "(empty = fully stopped)"

echo
echo "--- load average now ---"
uptime
