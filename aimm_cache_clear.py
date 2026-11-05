import os
import shutil
import subprocess

ROOT = "/var/www/aimoneymachine"
CACHE = os.path.join(ROOT, "wp-content", "cache")


def size(p):
    t = 0
    for r, d, f in os.walk(p):
        for n in f:
            try:
                t += os.path.getsize(os.path.join(r, n))
            except OSError:
                pass
    return t


print(
    "cache size before:",
    f"{size(CACHE) / 1e6:.1f} MB" if os.path.isdir(CACHE) else "n/a",
)

# remove cached page trees (safe: regenerated on demand)
targets = []
if os.path.isdir(CACHE):
    for name in os.listdir(CACHE):
        if name.startswith("supercache") or name.startswith("wp-cache"):
            targets.append(os.path.join(CACHE, name))
for t in targets:
    shutil.rmtree(t, ignore_errors=True)
    print("  removed", t)

removed = 0
if os.path.isdir(CACHE):
    for r, d, f in os.walk(CACHE):
        for n in f:
            if n.endswith((".html", ".html.gz")):
                try:
                    os.remove(os.path.join(r, n))
                    removed += 1
                except OSError:
                    pass
print(f"  removed {removed} cached html files")
print(
    "cache size after:",
    f"{size(CACHE) / 1e6:.1f} MB" if os.path.isdir(CACHE) else "n/a",
)

# scan for any remaining defacement traces on disk
print()
print("=== scanning web root for defacement markers ===")
markers = (b"KZFULL", b"kzfp", b"kamikaze_root")
hits = []
for r, d, f in os.walk(ROOT):
    if "/venv/" in r:
        continue
    for n in f:
        p = os.path.join(r, n)
        try:
            if os.path.getsize(p) > 8_000_000:
                continue
            with open(p, "rb") as fh:
                data = fh.read()
            if any(m in data for m in markers):
                hits.append(p)
        except OSError:
            pass
print("matches:", hits if hits else "NONE — clean")

r = subprocess.run(
    ["systemctl", "reload", "php8.4-fpm"], capture_output=True, text=True
)
print("php-fpm reload:", "ok" if r.returncode == 0 else r.stderr[:200])
