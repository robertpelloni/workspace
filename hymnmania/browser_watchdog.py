"""Keep the CDP browsers alive - relaunch if down, prune tabs if clogged.

Hit 2026-09-21: the Suno browser (9333) died silently and the throttle kept failing with
confusing "copyright match" noise while the browser was actually just gone. This watchdog
runs on a schedule and self-heals both browsers.

    python browser_watchdog.py
"""
import os, subprocess, sys, time, urllib.request

ROOT = os.path.dirname(os.path.abspath(__file__))
PY = sys.executable

BROWSERS = {
    9222: ("socials", r"C:\Users\jakeg\edge-cdp-profile"),
    9333: ("Suno", os.path.join(ROOT, ".dedicated-edge-profile")),
}
EDGE = r"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe"


def up(port):
    try:
        urllib.request.urlopen(f"http://127.0.0.1:{port}/json/version", timeout=5)
        return True
    except Exception:
        return False


def launch(port, profile):
    if port == 9333 and os.path.exists(os.path.join(ROOT, "launch_dedicated_browser.py")):
        subprocess.Popen([PY, os.path.join(ROOT, "launch_dedicated_browser.py")])
    else:
        subprocess.Popen([EDGE, f"--remote-debugging-port={port}",
                          f"--user-data-dir={profile}", "--no-first-run",
                          "--no-default-browser-check",
                          "--disable-features=msEdgeDisableStartupBoost"])
    time.sleep(20)


def main():
    for port, (name, profile) in BROWSERS.items():
        if up(port):
            if port == 9222:
                try:
                    from cleanup_tabs import clean
                    clean(port, verbose=False)
                except Exception:
                    pass
            print(f"  {port} ({name}): OK", flush=True)
        else:
            print(f"  {port} ({name}): DOWN -> relaunching", flush=True)
            launch(port, profile)
            if up(port):
                print(f"  {port} ({name}): relaunched OK", flush=True)
            else:
                print(f"  {port} ({name}): STILL DOWN", flush=True)


if __name__ == "__main__":
    main()
