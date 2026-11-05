#!/bin/bash
echo "=== syslog refill rate (waits 45s) ==="
before=$(stat -c%s /var/log/syslog)
sleep 45
after=$(stat -c%s /var/log/syslog)
rate=$(((after - before) / 45))
echo "  grew ${after}B in 45s  (~${rate} B/s)"
if [ "$rate" -gt 0 ]; then
	echo "  => ~$(numfmt --to=iec $((rate * 86400)))/day"
fi
echo
echo "=== who is writing to syslog right now ==="
tail -400 /var/log/syslog | sed -E 's/^[0-9T:.+-]+ [^ ]+ //' | awk '{print $1}' | sort | uniq -c | sort -rn | head -8
echo
echo "=== the three overlapping AI processes ==="
ps -o pid,ppid,etime,time,pcpu,pmem,rss,cmd -p 1573011,2364672,3770691 2>/dev/null
echo
echo "=== their command lines / start source ==="
for p in 1573011 2364672 3770691; do
	echo "  --- pid $p ---"
	tr '\0' ' ' </proc/$p/cmdline 2>/dev/null
	echo
	echo "      cwd: $(readlink /proc/$p/cwd 2>/dev/null)"
done
echo
echo "=== systemd units for these ==="
systemctl list-units --all 2>/dev/null | grep -iE "aimoney|hustle|orchestr" | head -8
echo "--- crontab entries ---"
crontab -l 2>/dev/null | grep -iE "hustle|orchestr|aimoney" | head -5
