import sys, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
    fb = b.contexts[0].new_page()
    # Try the documented create URL and watch redirects
    fb.goto("https://www.facebook.com/reels/create", wait_until="domcontentloaded", timeout=30000)
    fb.wait_for_timeout(8000)
    print("URL after /reels/create:", fb.url[:80])
    body = fb.evaluate("document.body.innerText")
    has_create = "create reel" in body.lower() or "add video" in body.lower() or "upload" in body.lower()
    print("has create UI:", has_create)
    print("body:", body[:200].replace(chr(10), " | "))
    b.close()
