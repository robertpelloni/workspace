"""Debug: launch local IG browser, inspect login state."""
import subprocess, os, sys, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

EDGE_PATH = r"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe"
IG_PROFILE = r"C:\Users\jakeg\ig-local-profile"
PORT = 9333

proc = subprocess.Popen([
    EDGE_PATH, f"--remote-debugging-port={PORT}",
    f"--user-data-dir={IG_PROFILE}",
    "--no-first-run", "--no-default-browser-check",
    "about:blank"
], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
time.sleep(6)
try:
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp(f"http://127.0.0.1:{PORT}")
        ctx = b.contexts[0]
        p = ctx.new_page()
        p.goto("https://www.instagram.com/accounts/login/", wait_until="domcontentloaded", timeout=45000)
        p.wait_for_timeout(10000)
        body = p.evaluate("document.body.innerText")
        print('URL:', p.url[:60])
        print('body:', body[:400].replace(chr(10),' | '))
        # all inputs
        inputs = p.evaluate('JSON.stringify(Array.from(document.querySelectorAll("input")).map((i,idx)=>({idx,name:i.name,type:i.type,ph:i.placeholder||""})))')
        print('inputs:', inputs)
        # buttons
        btns = p.evaluate('JSON.stringify(Array.from(document.querySelectorAll("button")).map(b=>(b.innerText||"").trim()).filter(Boolean).slice(0,10))')
        print('buttons:', btns)
        b.close()
except Exception as e:
    print('err:', str(e)[:150])
finally:
    proc.terminate()
