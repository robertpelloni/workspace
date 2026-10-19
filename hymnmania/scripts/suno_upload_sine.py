"""Upload sine MP3s to Suno and verify they appear in the feed.
Usage: python scripts/suno_upload_sine.py <mp3_path> [mp3_path2 ...]
"""
import sys, os, json, time, requests
from playwright.sync_api import sync_playwright

SUNO_BASE = "https://studio-api-prod.suno.com"

def upload_one(page, abs_path):
    print(f"Uploading: {os.path.basename(abs_path)}")
    page.evaluate('Array.from(document.querySelectorAll("button")).find(x=>x.innerText.includes("Add audio"))?.click()')
    page.wait_for_timeout(3000)
    n = page.evaluate('document.querySelectorAll("input[type=file]").length')
    ok = False
    for i in range(n):
        try:
            page.set_input_files(f'input[type=file] >> nth={i}', abs_path, timeout=8000)
            ok = True
        except Exception as e:
            print(f"  nth={i} err: {str(e)[:40]}")
    if not ok:
        return False
    page.wait_for_timeout(15000)
    # wait for upload to complete
    for _ in range(10):
        body = page.evaluate('document.body.innerText')
        if 'uploading' not in body.lower():
            break
        page.wait_for_timeout(5000)
    # select Full Song + Continue
    page.evaluate('Array.from(document.querySelectorAll("span,div,label,button,li")).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim()==="Full Song")[0]?.click()')
    page.wait_for_timeout(1500)
    page.evaluate('Array.from(document.querySelectorAll("button")).find(x=>x.offsetParent&&x.innerText.trim().toLowerCase()==="continue")?.click()')
    page.wait_for_timeout(5000)
    print("  submitted")
    return True

def verify_feed(hdr, keywords):
    """Find upload clips matching keywords. Returns {title: clip_id}."""
    found = {}
    for pg in range(0, 8):
        r = requests.get(f"{SUNO_BASE}/api/feed/?limit=50&page={pg}", headers=hdr, timeout=30)
        if r.status_code != 200:
            break
        clips = r.json() if isinstance(r.json(), list) else r.json().get('clips', [])
        if not clips:
            break
        for c in clips:
            t = str(c.get('title', ''))
            if c.get('model_name') == 'chirp-chirp' and any(k in t.lower() for k in keywords):
                found[t] = c.get('id')
        if len(clips) < 50:
            break
    return found

if __name__ == "__main__":
    paths = sys.argv[1:]
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        page = next((p for p in b.contexts[0].pages if "suno.com" in p.url), None)
        if not page:
            page = b.contexts[0].new_page()
            page.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=30000)
            page.wait_for_timeout(8000)
        # dismiss cookies
        page.evaluate('Array.from(document.querySelectorAll("button")).find(b=>b.innerText.trim()==="Allow All")?.click()')
        page.wait_for_timeout(1500)
        for p in paths:
            upload_one(page, os.path.abspath(p))
        # verify
        tok = page.evaluate('async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}')
        hdr = {"Authorization": f"Bearer {tok}"}
        time.sleep(10)
        kw = ["jesus", "just over", "happy day", "love shines"]
        found = verify_feed(hdr, kw)
        print("=== uploads in feed ===")
        for t, cid in found.items():
            print(f"  {t[:50]:52s} {cid}")
        b.close()
