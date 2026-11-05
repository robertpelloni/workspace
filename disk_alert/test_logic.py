"""Simulate disk levels and verify alerting decisions. Sends no real email."""
import importlib.util
import os
from datetime import datetime, timedelta, timezone

spec = importlib.util.spec_from_file_location("dc", "/usr/local/bin/disk-check.py")
m = importlib.util.module_from_spec(spec)
spec.loader.exec_module(m)

# --- isolate from production state, capture instead of sending
m.STATE_FILE = "/tmp/disk-alert-test-state.json"
if os.path.exists(m.STATE_FILE):
    os.remove(m.STATE_FILE)

sent = []
m.send_email = lambda cfg, subject, body: (sent.append(subject), True)[1]

# no remediation during the test
m.binlog_info = lambda: (0, 0)
m.top_consumers = lambda limit=6, timeout=25: []

TOTAL = 75 * 1024**3


def set_pct(pct):
    used = int(TOTAL * pct / 100)
    m.disk_usage = lambda mount: (float(pct), TOTAL, used, TOTAL - used)


def run(label, pct):
    set_pct(pct)
    before = len(sent)
    rc = m.main()
    fired = sent[before:]
    print(f"{label:<34} {pct:>5.1f}%  rc={rc}  emails={len(fired)}"
          + (f"  {fired[0][:46]}" if fired else ""))


print("=" * 96)
run("1. normal", 78)
run("2. crosses WARN", 87)
run("3. still WARN (no spam)", 88)
run("4. escalates to CRIT", 93)
run("5. still CRIT (no spam)", 93.5)
run("6. back to WARN", 87)
run("7. recovered", 70)
run("8. still OK (no spam)", 71)

# --- re-alert after RE_ALERT_HOURS while still bad
print("-" * 96)
set_pct(93)
m.main()
st = m.load_state()
old = (datetime.now(timezone.utc) - timedelta(hours=7)).isoformat(timespec="seconds")
st["last_alert_at"] = old
st["level"] = "CRITICAL"
m.save_state(st)
before = len(sent)
m.main()
print(f"{'9. re-alert after 7h critical':<34}  93.0%  rc={m.EXIT_CRIT}  "
      f"emails={len(sent) - before}  {(sent[-1][:46] if len(sent) > before else 'NONE')}")

print("=" * 96)
print("total emails sent:", len(sent))
os.remove(m.STATE_FILE)
