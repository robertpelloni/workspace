"""Test cover flow in an ISOLATED Edge instance sharing the CDP profile.
The shared browser (port 9222) keeps closing pages on Remix->Cover.
Usage: python _isolated_suno_test.py <upload_clip_id>
"""
import subprocess, sys, os, json, time
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

EDGE_PATH = r"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe"
EDGE_PROFILE = r"C:\Users\jakeg\edge-cdp-profile"  # same profile as CDP browser (has suno login)
PORT = 9338

def main():
    upload_cid = sys.argv[1]
    proc = subprocess.Popen([EDGE_PATH, f"--remote-debugging-port={PORT}",
        f"--user-data-dir={EDGE_PROFILE}", "--no-first-run", "--no-default-browser-check",
        "--headless=new", "about:blank"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    time.sleep(6)
    try:
        with sync_playwright() as pw:
            b = pw.chromium.connect_over_cdp(f"http://127.0.0.1:{PORT}")
            ctx = b.contexts[0]
            # reuse an existing suno page if present (login persists)
            page = next((p for p in ctx.pages if "suno.com" in p.url), None)
            if not page:
                page = ctx.new_page()
                page.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=30000)
                page.wait_for_timeout(6000)
            tok = page.evaluate("async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}")
            print("token:", "YES" if tok else "NO", flush=True)
            if not tok:
                print("isolated browser NOT logged into suno", flush=True)
                b.close()
                return
            # More menu -> Remix -> Cover
            page.goto(f"https://suno.com/song/{upload_cid}", wait_until="load", timeout=30000)
            page.wait_for_timeout(8000)
            try:
                page.focus('button[aria-label="More menu contents"]')
                page.keyboard.press("Enter")
            except Exception:
                page.evaluate("document.querySelector('button[aria-label=\\\"More menu contents\\\"]')?.click()")
            page.wait_for_timeout(3000)
            page.evaluate("Array.from(document.querySelectorAll('[role=menuitem],button')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim().toLowerCase()==='remix')[0]?.click()")
            page.wait_for_timeout(3000)
            page.evaluate("Array.from(document.querySelectorAll('[role=menuitem],button,div')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim().toLowerCase()==='cover')[0]?.click()")
            try:
                page.wait_for_url("**/create**", timeout=20000)
                print("NAVIGATED to /create (cover form)", flush=True)
            except Exception:
                print("no nav — checking", flush=True)
            page.wait_for_timeout(6000)
            print("url:", page.url[:60], flush=True)
            body = page.evaluate("document.body.innerText")
            print("has Song Description:", "song description" in body.lower(), flush=True)
            b.close()
    except Exception as e:
        print("err:", str(e)[:150], flush=True)
    finally:
        proc.terminate()

if __name__ == "__main__":
    main()
