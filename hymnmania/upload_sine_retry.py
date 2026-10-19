"""Upload a sine MP3 to Suno with patient retries + modal handling.
Usage: python upload_sine_retry.py <mp3_path> [max_attempts]
"""
import sys, os, json, time, requests
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

SUNO = "https://studio-api-prod.suno.com"

def main():
    abs_path = os.path.abspath(sys.argv[1])
    fname = os.path.basename(abs_path)
    stem = fname.split(".")[0].lower()
    max_attempts = int(sys.argv[2]) if len(sys.argv) > 2 else 5
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9333")
        # fresh page
        for p in list(b.contexts[0].pages):
            if "suno.com" in p.url:
                try:
                    p.close()
                except Exception:
                    pass
        time.sleep(1)
        page = b.contexts[0].new_page()

        for attempt in range(max_attempts):
            print(f"\n--- Attempt {attempt+1}/{max_attempts} ---", flush=True)
            page.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=30000)
            page.wait_for_timeout(9000)
            try:
                page.click('button:has-text("Reject All")', timeout=6000)
            except Exception:
                pass
            page.wait_for_timeout(1000)
            # Click Add audio
            page.evaluate("Array.from(document.querySelectorAll('button')).find(x=>x.innerText.includes('Add audio'))?.click()")
            page.wait_for_timeout(4000)
            # Set file
            n = page.evaluate("document.querySelectorAll('input[type=file]').length")
            set_ok = False
            for i in range(n):
                try:
                    page.set_input_files("input[type=file] >> nth=" + str(i), abs_path, timeout=15000)
                    set_ok = True
                    print(f"  file set nth={i}", flush=True)
                except Exception:
                    pass
            if not set_ok:
                print("  file set failed", flush=True)
                continue
            # Agree to Upload Terms if the dialog requires it (new Suno step)
            try:
                agreed = page.evaluate("(()=>{var els=Array.from(document.querySelectorAll('button,span,div')).filter(e=>e.offsetParent&&/agree to terms|i agree|accept terms/i.test((e.innerText||'').replace(/\\s+/g,' ')));if(els.length){els[0].click();return 'ok'}return 'nf'})()")
                if agreed == 'ok':
                    print("  agreed to upload terms", flush=True)
                    page.wait_for_timeout(2000)
            except Exception:
                pass
            # Wait patiently for the modal (upload can take 30-90s)
            modal_seen = False
            for i in range(25):
                page.wait_for_timeout(4000)
                body = page.evaluate("document.body.innerText")
                low = body.lower()
                if "full song" in low and "uploading" not in low:
                    print(f"  full-song modal at {(i+1)*4}s", flush=True)
                    modal_seen = True
                    break
                elif "uploading clip" in low or ("uploading" in low and "uploads" not in low):
                    if i % 4 == 0:
                        print(f"  uploading... ({(i+1)*4}s)", flush=True)
            if not modal_seen:
                print("  no modal appeared — retrying", flush=True)
                continue
            # Click Full Song then Continue
            page.evaluate("(()=>{var els=Array.from(document.querySelectorAll('span,div,label,button,li')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim()==='Full Song');if(els.length){els[0].click();return 'ok'}return 'nf'})()")
            page.wait_for_timeout(2000)
            page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button')).find(x=>x.offsetParent&&x.innerText.trim().toLowerCase()==='continue');if(b){b.click();return 'ok'}return 'nf'})()")
            print("  modal confirmed", flush=True)
            page.wait_for_timeout(8000)
            # Verify in feed
            tok = page.evaluate("async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}")
            hdr = {"Authorization": "Bearer " + str(tok)}
            for _ in range(3):
                time.sleep(10)
                for pg in range(0, 4):
                    r = requests.get(SUNO + "/api/feed/?limit=50&page=" + str(pg), headers=hdr, timeout=20)
                    if r.status_code != 200:
                        break
                    clips = r.json() if isinstance(r.json(), list) else r.json().get("clips", [])
                    for c in clips:
                        if stem in str(c.get("title", "")).lower() and c.get("model_name") == "chirp-chirp":
                            print("SUCCESS: " + str(c.get("title")) + " " + str(c.get("id")) + " " + str(c.get("status")), flush=True)
                            b.close()
                            return True
                    if len(clips) < 50:
                        break
            print("  not verified — retrying", flush=True)
        b.close()
        print("FAILED after " + str(max_attempts) + " attempts", flush=True)
        return False

if __name__ == "__main__":
    ok = main()
    print("RESULT: " + str(ok))
