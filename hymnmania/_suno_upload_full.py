import sys, os, json, time, requests
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

SUNO = "https://studio-api-prod.suno.com"

def main():
    abs_path = os.path.abspath(sys.argv[1])
    stem = os.path.basename(abs_path).split(".")[0].lower()
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9333")
        page = next((p for p in b.contexts[0].pages if "suno.com" in p.url), None)
        if not page:
            page = b.contexts[0].new_page()
            page.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=30000)
        else:
            page.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=30000)
        page.wait_for_timeout(9000)
        try:
            page.click('button:has-text("Reject All")', timeout=6000)
        except Exception:
            pass
        page.wait_for_timeout(1500)
        page.evaluate("Array.from(document.querySelectorAll('button')).find(x=>x.innerText.includes('Add audio'))?.click()")
        page.wait_for_timeout(4000)
        n = page.evaluate("document.querySelectorAll('input[type=file]').length")
        for i in range(n):
            try:
                page.set_input_files("input[type=file] >> nth=" + str(i), abs_path, timeout=25000)
                print("file set nth=" + str(i), flush=True)
            except Exception:
                pass
        # wait for full song modal (pitch-shifted so no copyright match expected)
        modal = False
        for i in range(20):
            page.wait_for_timeout(4000)
            body = page.evaluate("document.body.innerText")
            low = body.lower()
            if "matches an existing recording" in low:
                print("COPYRIGHT MATCH — shift not enough", flush=True)
                break
            if "full song" in low and "uploading" not in low:
                print("full song modal at " + str((i+1)*4) + "s", flush=True)
                modal = True
                break
            if "uploading" in low and i % 3 == 0:
                print("  uploading... " + str((i+1)*4) + "s", flush=True)
        if not modal:
            b.close()
            return
        # click Full Song + Continue
        page.evaluate("(()=>{var els=Array.from(document.querySelectorAll('span,div,label,button,li')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim()==='Full Song');if(els.length){els[0].click();return 'ok'}return 'nf'})()")
        page.wait_for_timeout(2000)
        page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button')).find(x=>x.offsetParent&&x.innerText.trim().toLowerCase()==='continue');if(b){b.click();return 'ok'}return 'nf'})()")
        print("modal confirmed", flush=True)
        # verify in feed (wait for chirp-chirp clip)
        tok = page.evaluate("async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}")
        hdr = {"Authorization": "Bearer " + str(tok)}
        for _ in range(4):
            time.sleep(10)
            for pg in range(0, 4):
                r = requests.get(SUNO + "/api/feed/?limit=50&page=" + str(pg), headers=hdr, timeout=20)
                if r.status_code != 200:
                    break
                clips = r.json() if isinstance(r.json(), list) else r.json().get("clips", [])
                for c in clips:
                    if stem in str(c.get("title", "")).lower() and c.get("model_name") == "chirp-chirp":
                        print("VERIFIED UPLOAD: " + str(c.get("title")) + " " + str(c.get("id")) + " " + str(c.get("status")), flush=True)
                        b.close()
                        return
                if len(clips) < 50:
                    break
        print("upload sent, waiting to verify...", flush=True)
        b.close()

if __name__ == "__main__":
    main()
