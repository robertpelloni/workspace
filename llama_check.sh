#!/bin/bash
echo "=== llama-server ownership ==="
for pid in $(pgrep -f llama-server 2>/dev/null); do
	echo "--- pid $pid ---"
	echo "  cmd : $(tr '\0' ' ' </proc/$pid/cmdline 2>/dev/null | cut -c1-200)"
	echo "  cwd : $(readlink /proc/$pid/cwd 2>/dev/null)"
	echo "  unit: $(cat /proc/$pid/cgroup 2>/dev/null | head -1)"
	ppid=$(awk '{print $4}' /proc/$pid/stat 2>/dev/null)
	echo "  ppid: $ppid  ($(tr '\0' ' ' </proc/$ppid/cmdline 2>/dev/null | cut -c1-90))"
done
echo
echo "=== which unit starts llama-server? ==="
grep -rl "llama-server\|llamafile" /etc/systemd/system/*.service 2>/dev/null | head -5
echo
echo "=== reset failed unit states (cosmetic) ==="
systemctl reset-failed 2>/dev/null
for u in $(ls /etc/systemd/system/ | grep -E "^aimm-.*\.service$|^aimoney\.service$"); do
	printf "  %-34s %s\n" "$u" "$(systemctl is-active $u 2>/dev/null)"
done
