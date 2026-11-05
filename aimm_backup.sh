#!/bin/bash
# Full backup of the AI Money Machine before/after stopping it.
# Creates a timestamped, restorable snapshot with checksums.
set -u

STAMP=$(date +%Y%m%d-%H%M%S)
DEST="/root/backups/aimoneymachine-$STAMP"
mkdir -p "$DEST"

LOG="$DEST/BACKUP.log"
exec > >(tee -a "$LOG") 2>&1

echo "==================================================="
echo " AI Money Machine backup — $STAMP"
echo " destination: $DEST"
echo "==================================================="
df -h / | tail -1
echo

# ---------------------------------------------------------------- 1. code/data
echo "[1/7] /opt/aimoneymachine (incl. the 2.9G model; venv excluded)"
tar -C /opt -czf "$DEST/opt-aimoneymachine.tar.gz" \
	--exclude='aimoneymachine/venv' \
	--exclude='__pycache__' \
	--exclude='*.pyc' \
	aimoneymachine 2>&1 | tail -3
echo "  -> $(du -h "$DEST/opt-aimoneymachine.tar.gz" 2>/dev/null | cut -f1)"

# ---------------------------------------------------------------- 2. legacy dir
echo "[2/7] /opt/aimoney (legacy duplicate)"
tar -C /opt -czf "$DEST/opt-aimoney.tar.gz" aimoney 2>&1 | tail -2
echo "  -> $(du -h "$DEST/opt-aimoney.tar.gz" 2>/dev/null | cut -f1)"

# ---------------------------------------------------------------- 3. wordpress
echo "[3/7] /var/www/aimoneymachine (WordPress, caches excluded)"
tar -C /var/www -czf "$DEST/www-aimoneymachine.tar.gz" \
	--exclude='aimoneymachine/wp-content/cache' \
	--exclude='aimoneymachine/wp-content/upgrade' \
	--exclude='aimoneymachine/wp-content/uploads/wp-statistics' \
	aimoneymachine 2>&1 | tail -2
echo "  -> $(du -h "$DEST/www-aimoneymachine.tar.gz" 2>/dev/null | cut -f1)"

# ---------------------------------------------------------------- 4. database
echo "[4/7] MySQL dump (aimoneymachine_wp)"
WP=/var/www/aimoneymachine/wp-config.php
DBNAME=$(grep -oP "define\(\s*'DB_NAME'\s*,\s*'\K[^']+" "$WP" 2>/dev/null)
DBUSER=$(grep -oP "define\(\s*'DB_USER'\s*,\s*'\K[^']+" "$WP" 2>/dev/null)
DBPASS=$(grep -oP "define\(\s*'DB_PASSWORD'\s*,\s*'\K[^']+" "$WP" 2>/dev/null)
DBHOST=$(grep -oP "define\(\s*'DB_HOST'\s*,\s*'\K[^']+" "$WP" 2>/dev/null)
DBHOST=${DBHOST%%:*}
echo "  db=$DBNAME user=$DBUSER host=$DBHOST"
mysqldump --single-transaction --quick --routines --triggers \
	-h"$DBHOST" -u"$DBUSER" -p"$DBPASS" "$DBNAME" 2>/dev/null |
	gzip -6 >"$DEST/mysql-$DBNAME.sql.gz"
echo "  -> $(du -h "$DEST/mysql-$DBNAME.sql.gz" 2>/dev/null | cut -f1)"
echo "  tables in dump: $(zcat "$DEST/mysql-$DBNAME.sql.gz" 2>/dev/null | grep -c '^CREATE TABLE')"

# ---------------------------------------------------------------- 5. configs
echo "[5/7] systemd units, nginx config, cron"
mkdir -p "$DEST/config"
tar -czf "$DEST/config/systemd-units.tar.gz" \
	-C /etc/systemd/system $(ls /etc/systemd/system/ | grep -E '^aimm-.*\.(service|timer)$|^aimoney\.service$') 2>/dev/null
tar -czf "$DEST/config/nginx.tar.gz" \
	-C /etc/nginx sites-available sites-enabled 2>/dev/null
crontab -l >"$DEST/config/root-crontab.txt" 2>/dev/null
tar -czf "$DEST/config/cron.tar.gz" -C /etc cron.d 2>/dev/null
cp /root/aimm-state-before.txt "$DEST/config/service-state-before-stop.txt" 2>/dev/null
echo "  -> units=$(du -h "$DEST/config/systemd-units.tar.gz" 2>/dev/null | cut -f1) nginx=$(du -h "$DEST/config/nginx.tar.gz" 2>/dev/null | cut -f1)"

# ---------------------------------------------------------------- 6. ledger snapshots
echo "[6/7] ledger / status snapshots (raw, as found)"
mkdir -p "$DEST/ledgers"
for f in /opt/aimoneymachine/STATUS.json /opt/aimoney/STATUS.json \
	/opt/aimoneymachine/tasks.json /opt/aimoney/tasks.json \
	/opt/aimoneymachine/chains.json /opt/aimoney/chains.json; do
	[ -f "$f" ] && cp "$f" "$DEST/ledgers/$(echo "$f" | sed 's|/|_|g')"
done
ls -la "$DEST/ledgers/" | tail -n +2

# ---------------------------------------------------------------- 7. manifest
echo "[7/7] manifest + checksums"
{
	echo "AI Money Machine backup"
	echo "created : $STAMP"
	echo "host    : $(hostname)"
	echo "reason  : stopped the AI Money Machine after finding it running in mock"
	echo "          mode for 84-92 days, burning ~24% CPU, fabricating ledger"
	echo "          figures, and writing ~18MB/day of syslog noise."
	echo
	echo "CONTENTS"
	ls -lh "$DEST" | tail -n +2
	echo
	echo "RESTORE OUTLINE"
	echo "  1) tar xzf opt-aimoneymachine.tar.gz -C /opt"
	echo "  2) tar xzf opt-aimoney.tar.gz        -C /opt"
	echo "  3) tar xzf www-aimoneymachine.tar.gz -C /var/www"
	echo "  4) zcat mysql-aimoneymachine_wp.sql.gz | mysql -u<user> -p <db>"
	echo "  5) tar xzf config/systemd-units.tar.gz -C /etc/systemd/system && systemctl daemon-reload"
	echo "  6) systemctl unmask <unit> && systemctl enable --now <unit>"
	echo
	echo "EXCLUDED (recreatable, not backed up)"
	echo "  /opt/aimoneymachine/venv        -> pip install -r requirements.txt"
	echo "  **/__pycache__                  -> regenerated"
	echo "  wp-content/cache, wp-content/upgrade, wp-statistics -> regenerated"
	echo
	echo "MODEL INCLUDED: gemma-4-E2B-it-ultra-uncensored-heretic-Q4_K_M.gguf (2.9G)"
	echo
	echo "SERVICE STATE AT STOP"
	cat /root/aimm-state-before.txt 2>/dev/null
} >"$DEST/MANIFEST.txt"

cd "$DEST" && sha256sum *.tar.gz *.sql.gz config/*.tar.gz >checksums.sha256 2>/dev/null
echo "  checksums written: $(wc -l <checksums.sha256) files"

# ---------------------------------------------------------------- verify
echo
echo "=== VERIFY (test each archive) ==="
for f in *.tar.gz config/*.tar.gz; do
	if tar -tzf "$f" >/dev/null 2>&1; then
		printf "  OK   %-40s %s\n" "$f" "$(du -h "$f" | cut -f1)"
	else
		printf "  FAIL %-40s (archive is corrupt!)\n" "$f"
	fi
done
if zcat "mysql-$DBNAME.sql.gz" 2>/dev/null | tail -1 | grep -q "Dump completed"; then
	echo "  OK   mysql-$DBNAME.sql.gz (dump completed cleanly)"
else
	echo "  WARN mysql-$DBNAME.sql.gz (no 'Dump completed' trailer)"
fi
if sha256sum -c checksums.sha256 >/dev/null 2>&1; then
	echo "  OK   checksums verify"
else
	echo "  FAIL checksum mismatch"
fi

echo
echo "=== TOTAL ==="
du -sh "$DEST"
df -h / | tail -1
echo "backup path: $DEST"
