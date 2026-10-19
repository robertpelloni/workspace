"""Debug: local IG create-post flow after login."""
import subprocess, os, sys, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

EDGE_PATH = r"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe"
IG_PROFILE = r"C:\Users\jakeg\ig-local-profile"
PORT = 9335

proc = subprocess.Popen([EDGE_PATH, f"--remote-debugging-port={PORT}", f"--user-data-dir={IG_PROFILE}", "--no-first-run", "--no-default-browser-check", "about:blank"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
time.sleep(6)
try:
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp(f"http://127.0.0.1:{PORT}")
        p = b.contexts[0].new_page()
        p.goto("https://www.instagram.com/", wait_until="domcontentloaded", timeout=40000)
        p.wait_for_timeout(9000)
        body = p.evaluate("document.body.innerText")
        print("logged in:", "resurrectingbeats" in body.lower() or ("home" in body.lower() and "log in" not in body.lower()))
        # New post
        p.evaluate("document.querySelector('svg[aria-label=\\\"New post\\\"]')?.closest('a,div[role=button]')?.click()")
        p.wait_for_timeout(3500)
        body2 = p.evaluate("document.body.innerText")
        print("after new post:", body2[:200].replace(chr(10),' | '))
        # Click Post
        r = p.evaluate("Array.from(document.querySelectorAll('span,div,button,a')).filter(e=>(e.innerText||'').trim()==='Post'&&e.offsetParent)[0]?.click()")
        print("post click:", r)
        p.wait_for_timeout(5000)
        body3 = p.evaluate("document.body.innerText")
        print("after post:", body3[:300].replace(chr(10),' | '))
        # Look for dialog and file input
        dlg = p.evaluate("""JSON.stringify(Array.from(document.querySelectorAll('[role=dialog]')).map(d=>({txt:(d.innerText||'').slice(0,150),inputs:d.querySelectorAll('input[type=file]').length})))""")
        print("dialogs:", dlg)
        fi = p.evaluate("document.querySelectorAll('input[type=file]').length")
        print("file inputs:", fi)
        b.close()
except Exception as e:
    print("err:", str(e)[:150])
finally:
    proc.terminate()
