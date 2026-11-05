#!/bin/bash
echo "=== is 'hustle' still running? (it spams syslog) ==="
ps aux | grep -iE "hustle|orchestrator" | grep -v grep | head -5
echo "(empty above = stopped)"
echo
echo "=== BEFORE ==="
df -h / | tail -1
echo "  syslog   : $(du -h /var/log/syslog 2>/dev/null | cut -f1)"
echo "  syslog.1 : $(du -h /var/log/syslog.1 2>/dev/null | cut -f1)"
echo "  journal  : $(journalctl --disk-usage 2>/dev/null | grep -oE '[0-9.]+[MG]')"
echo "  nginx    : $(du -sh /var/log/nginx 2>/dev/null | cut -f1)"
echo "  hypernex : $(du -sh /var/log/hypernexus 2>/dev/null | cut -f1)"
echo

echo "=== clearing ==="

# --- active logs: truncate so the writing process keeps its file handle ---
for f in /var/log/syslog /var/log/kern.log /var/log/auth.log /var/log/fail2ban.log \
	/var/log/ufw.log /var/log/dmesg /var/log/cloud-init.log \
	/var/log/nginx/error.log /var/log/nginx/access.log \
	/var/log/php8.4-fpm.log /var/log/mysql/error.log \
	/var/log/hypernexus/watchdog.log; do
	if [ -f "$f" ]; then
		before=$(stat -c%s "$f" 2>/dev/null || echo 0)
		truncate -s 0 "$f" 2>/dev/null && echo "  truncated $f ($(numfmt --to=iec $before 2>/dev/null || echo ${before}B))"
	fi
done

# --- rotated logs: safe to delete ---
removed=0
for pat in "/var/log/syslog.[0-9]*" "/var/log/syslog.*.gz" \
	"/var/log/kern.log.[0-9]*" "/var/log/auth.log.[0-9]*" \
	"/var/log/auth.log.*.gz" "/var/log/ufw.log.[0-9]*" \
	"/var/log/dmesg.[0-9]*" "/var/log/nginx/*.gz" "/var/log/nginx/*.[0-9]" \
	"/var/log/nginx/*.[0-9].gz" "/var/log/hypernexus/watchdog.*.log" \
	"/var/log/php8.4-fpm.log.[0-9]*" "/var/log/mysql/error.log.[0-9]*"; do
	for f in $pat; do
		if [ -f "$f" ]; then
			sz=$(stat -c%s "$f" 2>/dev/null || echo 0)
			rm -f "$f" && {
				echo "  removed   $f ($(numfmt --to=iec $sz 2>/dev/null || echo ${sz}B))"
				removed=$((removed + 1))
			}
		fi
	done
done
echo "  rotated files removed: $removed"

# --- journal ---
journalctl --vacuum-size=50M 2>&1 | tail -2

echo
echo "=== AFTER ==="
df -h / | tail -1
echo "  syslog   : $(du -h /var/log/syslog 2>/dev/null | cut -f1)"
echo "  journal  : $(journalctl --disk-usage 2>/dev/null | grep -oE '[0-9.]+[MG]')"
echo "  nginx    : $(du -sh /var/log/nginx 2>/dev/null | cut -f1)"
echo "  hypernex : $(du -sh /var/log/hypernexus 2>/dev/null | cut -f1)"
echo
echo "=== PRESERVED (security audit trail) ==="
ls -lh /var/log/btmp /var/log/lastlog /var/log/wtmp 2>/dev/null | awk '{print "  "$5, $9}'
echo
echo "=== services still writing OK? ==="
systemctl is-active nginx php8.4-fpm mysql rsyslog 2>&1 | tr '\n' ' '
echo
