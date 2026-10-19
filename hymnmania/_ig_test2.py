import sys, os, json, time, subprocess
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

EDGE_PATH = r"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe"
IG_PROFILE = r"C:\Users\jakeg\ig-local-profile"
PORT = 9341

proc = subprocess.Popen([EDGE_PATH, f"--remote-debugging-port={PORT}",
    f"--user-data-dir={IG_PROFILE}", "--no-first-run", "--no-default-browser-check",
    "about:blank"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
time.sleep(6)
try:
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp(f"http://127.0.0.1:{PORT}")
        p = b.contexts[0].new_page()
        p.goto("https://www.instagram.com/", wait_until="domcontentloaded", timeout=40000)
        p.wait_for_timeout(9000)
        body = p.evaluate("document.body.innerText")
        logged = "resurrecting" in body.lower() or ("log in" not in body.lower())
        print("logged in:", logged)
        print("body head:", body[:150].replace(chr(10), " | "))
        b.close()
except Exception as e:
    print("err:", str(e)[:150])
finally:
    proc.terminate()
