# Disk Space Alert

Server-side disk monitoring for the `robertpelloni.com` / hypernexus box.

## Why this exists

On **2026-09-14** the site went down hard. Root cause chain:

1. MySQL binary logs had grown to **17 GB** (188 files) — MySQL 8 enables
   binary logging by default with **30-day retention**, and nothing capped it.
   The actual WordPress database is only ~106 MB.
2. That filled the root filesystem to **100%**.
3. MySQL could not complete commits, so a WordPress cron query sat in
   `waiting for handler commit` for **753 seconds**, cascading into
   `Waiting for table level lock` on `wp_options` and hanging the whole site.

There *was* already a cron at `/etc/cron.d/disk-alert`, but it never fired:

```bash
# BROKEN — the awk field specifier was missing (should be $5)
awk "{print \}"      # printed the whole line, so the numeric compare failed
... | wall           # and `wall` reaches nobody when no one is logged in
```

Backup of that broken file: `/root/disk-alert.cron.BROKEN-20260914`

## Files

| Path | Purpose |
|---|---|
| `/usr/local/bin/disk-check.py` | The monitor |
| `/etc/disk-alert.conf` | Config, `chmod 600` (holds SMTP password) |
| `/etc/cron.d/disk-alert` | Runs the monitor every 15 minutes |
| `/etc/logrotate.d/disk-alert` | Weekly rotation, 8 kept, of the log |
| `/var/log/disk-alert.log` | Human-readable history |
| `/var/lib/disk-alert/state.json` | Last level / last alert time |
| `/var/log/syslog` | Same events, tagged `disk-alert` |

## Behaviour

- **Emails** `ALERT_TO` via Gmail SMTP when a threshold is crossed.
- **Does not spam** — one email per threshold crossing. Re-alerts only on level
  change, or every `RE_ALERT_HOURS` while still bad, plus one recovery notice.
- **Auto-remediates** at `AUTOFIX_PCT`: purges MySQL binlogs older than
  `BINLOG_KEEP_DAYS` (safe here — this host has **no** MySQL replicas).
- **Exit codes**: `0` OK, `1` warning, `2` critical, `3` error.
- Reports the same percentage as `df` (see note below).

## Config keys

```ini
MOUNTS=/                 # comma-separated mount points to watch
WARN_PCT=85              # email a warning at/above this
CRIT_PCT=92              # email a critical alert at/above this
AUTOFIX_PCT=90           # try the binlog purge at/above this
BINLOG_KEEP_DAYS=1       # purge binlogs older than this many days
RE_ALERT_HOURS=6         # re-notify this often while still over threshold
ALERT_TO=pelloni.robert@gmail.com
SMTP_HOST=smtp.gmail.com
SMTP_PORT=587
SMTP_USER=...
SMTP_PASS=...            # Gmail app password
```

## The `df` percentage detail

`used / total` reads about **3 points lower** than `df`, because ~5% of the
filesystem is reserved for root and is not counted in `df`'s denominator. At the
time of the incident: `used/total` = 77.7% but `df` = **82%**.

Since the services run as `www-data` / `mysql` (not root), `df`'s number is the
one that actually predicts an outage, so the script reproduces it exactly:

```
df Use% = ceil( used / (used + avail) * 100 )
```

Inode usage is likewise ceiled to match `df -i`.

## Testing

```bash
# normal run (exit 0 when healthy)
/usr/bin/python3 /usr/local/bin/disk-check.py; echo $?

# verify the percentage matches df
df -h / | tail -1
/usr/bin/python3 /usr/local/bin/disk-check.py --help 2>/dev/null || true
```

Alert behaviour (threshold crossings, no-spam, escalation, re-alert, recovery)
is covered by `test_logic.py`, which monkeypatches `disk_usage` and
`send_email` so it sends no mail and touches no production state:

```bash
scp test_logic.py server:/tmp/ && ssh server /usr/bin/python3 /tmp/test_logic.py
```

## If the disk fills again

```bash
df -h /                                   # confirm
du -sh /var/lib/mysql /var/lib/containerd /var/www /opt /root
ls /var/lib/mysql/binlog.* | wc -l        # binlog count
mysql -e "PURGE BINARY LOGS BEFORE DATE_SUB(NOW(), INTERVAL 1 DAY);"
df -h /
```

If `PURGE` hangs, MySQL is stuck on the full disk — free space *outside* MySQL
first (`journalctl --vacuum-size=100M`, `apt-get clean`,
`docker builder prune -af`), then retry.

## Prevention

- `binlog_expire_logs_seconds = 259200` (3 days) added to
  `/etc/mysql/mysql.conf.d/mysqld.cnf` — previously defaulting to 30 days.
  Backup: `mysqld.cnf.bak-20260914`.
- This monitor.
