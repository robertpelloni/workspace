import sys
import json, time
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
    ctx = b.contexts[0]
    pages = ctx.pages
    print("total pages before cleanup:", len(pages))
    keep_suno = False
    keep_tt = False
    keep_ig = False
    keep_fb = False
    keep_yt = False
    closed = 0
    for p in pages:
        url = p.url
        is_suno = "suno.com" in url
        is_tt = "tiktok.com" in url
        is_ig = "instagram.com" in url
        is_fb = "facebook.com" in url
        is_yt = "youtube.com" in url or "studio.youtube" in url
        if is_suno and not keep_suno:
            keep_suno = True
            continue
        if is_tt and not keep_tt:
            keep_tt = True
            continue
        if is_ig and not keep_ig:
            keep_ig = True
            continue
        if is_fb and not keep_fb:
            keep_fb = True
            continue
        if is_yt and not keep_yt:
            keep_yt = True
            continue
        # close duplicates and other junk (bing, msn, blank, etc.)
        try:
            p.close()
            closed += 1
        except Exception:
            pass
    time.sleep(2)
    print("closed:", closed)
    print("remaining:", len(ctx.pages))
    b.close()
