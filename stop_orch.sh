#!/bin/bash
echo "=== restart policy of the stubborn unit ==="
grep -E "^(Restart|RestartSec|ExecStart)" /etc/systemd/system/aimm-orchestrator.service 2>/dev/null | head -5
echo
echo "=== proper stop (stop mask prevents auto-restart) ==="
systemctl stop aimm-orchestrator.service 2>/dev/null
sleep 5
echo "  after stop    : $(systemctl is-active aimm-orchestrator.service)"
systemctl disable aimm-orchestrator.service 2>/dev/null
systemctl mask aimm-orchestrator.service 2>/dev/null && echo "  masked (cannot auto-start)"

echo
echo "=== ensure nothing restarts it ==="
sleep 10
echo "  after 10s     : $(systemctl is-active aimm-orchestrator.service)"
echo
echo "=== FINAL: all aimm units ==="
for u in $(ls /etc/systemd/system/ | grep -E "^aimm-.*\.service$|^aimoney\.service$"); do
	printf "  %-34s active=%-9s enabled=%s\n" "$u" "$(systemctl is-active $u 2>/dev/null)" "$(systemctl is-enabled $u 2>/dev/null)"
done
echo
echo "=== processes ==="
ps aux | grep -iE "aimoney|aimoneymachine" | grep -v grep | head
echo "(empty = all stopped)"
echo
echo "=== ports ==="
ss -tlnp 2>/dev/null | grep -E ":8080|:8082|:8083|:8779" | head -4
echo "(empty = down)"
echo
uptime
