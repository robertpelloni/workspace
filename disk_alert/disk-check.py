#!/usr/bin/env python3
"""
Disk space monitor + alert for the robertpelloni server.

Checks disk/inode usage, emails an alert when thresholds are crossed, logs to
syslog + /var/log/disk-alert.log, and auto-purges MySQL binlogs when the disk
is critically full (safe: this host has no MySQL replicas configured).

State is tracked in a JSON file so a sustained problem does not spam -- one
alert per threshold crossing, plus a single recovery notice.

Config: /etc/disk-alert.conf   (shell-style KEY=VALUE, mode 600)

Exit codes: 0 = OK, 1 = WARNING, 2 = CRITICAL, 3 = script/config error
"""

import json
import math
import os
import shutil
import smtplib
import socket
import subprocess
import sys
import time
from datetime import datetime, timezone
from email.mime.text import MIMEText

CONFIG = "/etc/disk-alert.conf"
STATE_FILE = "/var/lib/disk-alert/state.json"
LOG_FILE = "/var/log/disk-alert.log"

DEFAULTS = {
    "MOUNTS": "/",
    "WARN_PCT": "85",
    "CRIT_PCT": "92",
    "AUTOFIX_PCT": "90",
    "BINLOG_KEEP_DAYS": "1",
    "RE_ALERT_HOURS": "6",
    "ALERT_TO": "pelloni.robert@gmail.com",
    "SMTP_HOST": "smtp.gmail.com",
    "SMTP_PORT": "587",
    "SMTP_USER": "",
    "SMTP_PASS": "",
    "HOSTNAME_LABEL": socket.gethostname(),
}

EXIT_OK, EXIT_WARN, EXIT_CRIT, EXIT_ERR = 0, 1, 2, 3


# ----------------------------------------------------------------- config


def load_config(path=CONFIG):
    cfg = dict(DEFAULTS)
    try:
        with open(path, encoding="utf-8") as fh:
            for line in fh:
                line = line.strip()
                if not line or line.startswith("#") or "=" not in line:
                    continue
                key, _, val = line.partition("=")
                key = key.strip()
                val = val.strip().strip('"').strip("'")
                if key in cfg:
                    cfg[key] = val
    except OSError as exc:
        log(f"WARN: cannot read {path}: {exc}")
    return cfg


def cfg_int(cfg, key, fallback):
    try:
        return int(str(cfg.get(key, fallback)).strip())
    except (TypeError, ValueError):
        return fallback


# -------------------------------------------------------------- logging


def log(msg):
    stamp = datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")
    line = f"{stamp} {msg}"
    try:
        with open(LOG_FILE, "a", encoding="utf-8") as fh:
            fh.write(line + "\n")
    except OSError:
        pass
    try:
        subprocess.run(
            ["logger", "-t", "disk-alert", msg],
            check=False,
            timeout=10,
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
        )
    except (OSError, subprocess.SubprocessError):
        pass


# --------------------------------------------------------------- checks


def disk_usage(mount):
    """Return (used_pct, total, used, avail) for a mount, or None.

    The percentage deliberately matches GNU `df`'s Use%: it is computed over
    the space available to non-root users (used + avail, excluding the ~5%
    reserved blocks) and rounded up. That is the number that matters, because
    the services here run as www-data/mysql, not root. Using used/total would
    read ~3 points lower and delay the alert.
    """
    try:
        total, used, avail = shutil.disk_usage(mount)
    except OSError:
        return None
    denom = used + avail
    pct = math.ceil(used / denom * 100.0) if denom else 0
    return pct, total, used, avail


def inode_usage(mount):
    """Inode usage percent on POSIX (ceil, to match `df -i`); None where unsupported."""
    statvfs = getattr(os, "statvfs", None)
    if statvfs is None:
        return None
    try:
        st = statvfs(mount)
    except OSError:
        return None
    total = st.f_files
    if not total:
        return 0
    return math.ceil((total - st.f_ffree) / total * 100.0)


def human(n):
    for unit in ("B", "K", "M", "G", "T"):
        if abs(n) < 1024.0:
            return f"{n:.1f}{unit}"
        n /= 1024.0
    return f"{n:.1f}P"


def binlog_info():
    """Return (count, bytes) of mysql binlog files."""
    try:
        names = [
            n
            for n in os.listdir("/var/lib/mysql")
            if n.startswith("binlog.") and n != "binlog.index"
        ]
    except OSError:
        return 0, 0
    total = 0
    for n in names:
        try:
            total += os.path.getsize(os.path.join("/var/lib/mysql", n))
        except OSError:
            pass
    return len(names), total


def top_consumers(limit=6, timeout=25):
    """Best-effort list of the biggest top-level dirs (skips silently)."""
    targets = [
        "/var/lib/mysql",
        "/var/lib/containerd",
        "/var/lib/docker",
        "/var/www",
        "/opt",
        "/root",
        "/home",
        "/srv",
        "/var/log",
    ]
    rows = []
    for t in targets:
        if not os.path.isdir(t):
            continue
        try:
            r = subprocess.run(
                ["du", "-sb", t],
                capture_output=True,
                text=True,
                timeout=timeout,
            )
            if r.returncode == 0 and r.stdout.split():
                rows.append((int(r.stdout.split()[0]), t))
        except (OSError, subprocess.SubprocessError, ValueError):
            continue
    rows.sort(reverse=True)
    return rows[:limit]


# ----------------------------------------------------------- remediation


def purge_binlogs(keep_days):
    """Purge MySQL binlogs older than keep_days. Returns (ok, detail)."""
    try:
        days = int(str(keep_days).strip())
    except (TypeError, ValueError):
        return False, f"invalid BINLOG_KEEP_DAYS: {keep_days!r}"
    sql = f"PURGE BINARY LOGS BEFORE DATE_SUB(NOW(), INTERVAL {days} DAY);"
    before = shutil.disk_usage("/").free
    try:
        r = subprocess.run(
            ["mysql", "-e", sql],
            capture_output=True,
            text=True,
            timeout=180,
        )
    except (OSError, subprocess.SubprocessError) as exc:
        return False, f"purge failed to run: {exc}"
    if r.returncode != 0:
        return False, f"purge rc={r.returncode}: {r.stderr.strip()[:200]}"
    time.sleep(2)
    after = shutil.disk_usage("/").free
    return (
        True,
        f"purged binlogs older than {keep_days}d, freed {human(after - before)}",
    )


# ------------------------------------------------------------ alerting


def send_email(cfg, subject, body):
    user = cfg.get("SMTP_USER", "")
    pwd = cfg.get("SMTP_PASS", "")
    to = cfg.get("ALERT_TO", "")
    if not (user and pwd and to):
        log("WARN: email skipped (SMTP_USER/SMTP_PASS/ALERT_TO not configured)")
        return False

    msg = MIMEText(body, "plain", "utf-8")
    msg["Subject"] = subject
    msg["From"] = f"disk-alert <{user}>"
    msg["To"] = to

    try:
        with smtplib.SMTP(
            cfg.get("SMTP_HOST", "smtp.gmail.com"),
            cfg_int(cfg, "SMTP_PORT", 587),
            timeout=30,
        ) as s:
            s.ehlo()
            s.starttls()
            s.ehlo()
            s.login(user, pwd)
            s.sendmail(user, [to], msg.as_string())
        log(f"email sent to {to}: {subject}")
        return True
    except Exception as exc:  # noqa: BLE001 - alerting must never crash
        log(f"ERROR: email failed: {type(exc).__name__}: {exc}")
        return False


# --------------------------------------------------------------- state


def load_state():
    try:
        with open(STATE_FILE, encoding="utf-8") as fh:
            return json.load(fh)
    except (OSError, ValueError):
        return {}


def save_state(state):
    try:
        os.makedirs(os.path.dirname(STATE_FILE), exist_ok=True)
        tmp = STATE_FILE + ".tmp"
        with open(tmp, "w", encoding="utf-8") as fh:
            json.dump(state, fh, indent=2)
        os.replace(tmp, STATE_FILE)
    except OSError as exc:
        log(f"WARN: cannot save state: {exc}")


# ----------------------------------------------------------------- main


def build_report(cfg, results, inodes, extra_lines):
    host = cfg.get("HOSTNAME_LABEL", socket.gethostname())
    lines = [
        f"Host: {host}",
        f"Time: {datetime.now(timezone.utc):%Y-%m-%d %H:%M:%S} UTC",
        "",
    ]
    lines.append(f"{'Mount':<12}{'Size':>8}{'Used':>8}{'Avail':>8}{'Use%':>7}  Inodes")
    for mount, (pct, total, used, avail) in results.items():
        ipct = inodes.get(mount)
        ilabel = f"{ipct:.0f}%" if ipct is not None else "-"
        lines.append(
            f"{mount:<12}{human(total):>8}{human(used):>8}"
            f"{human(avail):>8}{pct:>6.0f}%  {ilabel}"
        )
    if extra_lines:
        lines += ["", *extra_lines]

    rows = top_consumers()
    if rows:
        lines += ["", "Top consumers:"]
        lines += [f"  {human(sz):>9}  {path}" for sz, path in rows]

    cnt, size = binlog_info()
    lines += ["", f"MySQL binlogs: {cnt} files, {human(size)}"]
    return "\n".join(lines)


def main():
    cfg = load_config()
    warn = cfg_int(cfg, "WARN_PCT", 85)
    crit = cfg_int(cfg, "CRIT_PCT", 92)
    autofix = cfg_int(cfg, "AUTOFIX_PCT", 90)
    keep_days = cfg_int(cfg, "BINLOG_KEEP_DAYS", 1)
    mounts = [m.strip() for m in str(cfg.get("MOUNTS", "/")).split(",") if m.strip()]

    results, inodes = {}, {}
    worst, worst_mount = 0.0, "/"
    for m in mounts:
        du_ = disk_usage(m)
        if du_ is None:
            continue
        results[m] = du_
        iu = inode_usage(m)
        if iu is not None:
            inodes[m] = iu
        if du_[0] > worst:
            worst, worst_mount = du_[0], m

    if not results:
        log("ERROR: no mounts could be checked")
        return EXIT_ERR

    level = "CRITICAL" if worst >= crit else "WARNING" if worst >= warn else "OK"
    log(f"check: {worst:.1f}% on {worst_mount} -> {level}")

    state = load_state()
    prev = state.get("level", "OK")
    extra = []

    # ---- remediation while critically full
    if worst >= autofix:
        cnt, size = binlog_info()
        if cnt and size > 200 * 1024 * 1024:
            ok, detail = purge_binlogs(keep_days)
            extra.append(f"Auto-remediation: {detail}")
            log(f"autofix: {detail}")
            fresh = disk_usage(worst_mount)
            if fresh:
                results[worst_mount] = fresh
                worst = fresh[0]
                level = (
                    "CRITICAL"
                    if worst >= crit
                    else "WARNING"
                    if worst >= warn
                    else "OK"
                )

    host = cfg.get("HOSTNAME_LABEL", socket.gethostname())

    # ---- decide whether to notify
    #  * alert on any threshold crossing (OK -> WARN/CRIT, WARN <-> CRIT)
    #  * re-alert periodically while still bad, so a sustained problem is not
    #    missed just because the first email went unread
    #  * send one recovery notice when back to OK
    realert_hours = cfg_int(cfg, "RE_ALERT_HOURS", 6)
    last_alert = state.get("last_alert_at")
    due_for_realert = False
    if level != "OK" and last_alert:
        try:
            prev_dt = datetime.fromisoformat(last_alert)
            if prev_dt.tzinfo is None:
                prev_dt = prev_dt.replace(tzinfo=timezone.utc)
            age_h = (datetime.now(timezone.utc) - prev_dt).total_seconds() / 3600.0
            due_for_realert = age_h >= realert_hours
        except ValueError:
            due_for_realert = False

    alerted = False
    if level != "OK" and (level != prev or due_for_realert):
        tag = "" if level != prev else " (reminder)"
        subject = f"[{level}] Disk {worst:.0f}% on {host} ({worst_mount}){tag}"
        body = (
            f"DISK {level}: {worst_mount} is {worst:.0f}% full "
            f"(warning {warn}%, critical {crit}%)\n\n"
            + build_report(cfg, results, inodes, extra)
        )
        alerted = send_email(cfg, subject, body)
    elif level == "OK" and prev in ("WARNING", "CRITICAL"):
        subject = f"[RECOVERED] Disk {worst:.0f}% on {host}"
        body = "Disk usage is back within normal range.\n\n" + build_report(
            cfg, results, inodes, extra
        )
        send_email(cfg, subject, body)
        alerted = True

    now_iso = datetime.now(timezone.utc).isoformat(timespec="seconds")
    state.update(
        {
            "level": level,
            "last_pct": round(worst, 1),
            "last_mount": worst_mount,
            "last_check": now_iso,
            "last_alert_level": prev,
        }
    )
    if alerted:
        state["last_alert_at"] = now_iso
    save_state(state)

    return (
        EXIT_CRIT
        if level == "CRITICAL"
        else EXIT_WARN
        if level == "WARNING"
        else EXIT_OK
    )


if __name__ == "__main__":
    try:
        sys.exit(main())
    except Exception as exc:  # noqa: BLE001 - never leave cron noisy
        log(f"FATAL: {type(exc).__name__}: {exc}")
        sys.exit(EXIT_ERR)
