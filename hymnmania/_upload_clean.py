import sys, os, json, time, requests
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

SUNO = "https://studio-api-prod.suno.com"

def main():
    abs_path = os.path.abspath(sys.argv[1])
    fname = os.path.basename(abs_path)
    stem = fname.split(".")[0].lower()
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9333")
        # reuse existing suno page on /create
        page = next((p for p in b.contexts[0].pages if "suno.com" in p.url), None)
        if not page:
            page = b.contexts[0].new_page()
        page.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=30000)
        page.wait_for_timeout(8000)
        # click Add audio
        page.evaluate("Array.from(document.querySelectorAll('button')).find(x=>x.innerText.includes('Add audio'))?.click()")
        page.wait_for_timeout(4000)
        n = page.evaluate("document.querySelectorAll('input[type=file]').length")
        for i in range(n):
            try:
                page.set_input_files("input[type=file] >> nth=" + str(i), abs_path, timeout=30000)
                print("file set nth=" + str(i), flush=True)
            except Exception as e:
                print("nth" + str(i) + " err: " + str(e)[:50], flush=True)
        # wait and watch for outcome (re-acquire page if handle dies)
        outcome = None
        for i in range(25):
            try:
                page.wait_for_timeout(4000)
            except Exception:
                # re-acquire the suno page
                page = next((p for p in b.contexts[0].pages if "suno.com" in p.url), None)
                if not page:
                    page = b.contexts[0].new_page()
                    page.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=30000)
                    page.wait_for_timeout(5000)
                # if we lost the modal, re-trigger by clicking Add audio and setting file
                try:
                    page.evaluate("Array.from(document.querySelectorAll('button')).find(x=>x.innerText.includes('Add audio'))?.click()")
                    page.wait_for_timeout(2000)
                    n2 = page.evaluate("document.querySelectorAll('input[type=file]').length")
                    for j in range(n2):
                        try:
                            page.set_input_files("input[type=file] >> nth=" + str(j), abs_path, timeout=20000)
                        except Exception:
                            pass
                except Exception:
                    pass
                continue
            try:
                body = page.evaluate("document.body.innerText")
            except Exception:
                continue
            body = page.evaluate("document.body.innerText")
            low = body.lower()
            if "matches an existing recording" in low:
                print("COPYRIGHT MATCH", flush=True)
                outcome = "copyright"
                break
            if "full song" in low and "uploading" not in low:
                print("UPLOAD OK - full song modal", flush=True)
                outcome = "ok"
                # click full song + continue
                page.evaluate("(()=>{var els=Array.from(document.querySelectorAll('span,div,label,button,li')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim()==='Full Song');if(els.length){els[0].click();return 'ok'}return 'nf'})()")
                page.wait_for_timeout(2000)
                page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button')).find(x=>x.offsetParent&&x.innerText.trim().toLowerCase()==='continue');if(b){b.click();return 'ok'}return 'nf'})()")
                print("confirmed", flush=True)
                break
            if "uploading" in low and i % 3 == 0:
                print("  uploading... " + str((i+1)*4) + "s", flush=True)
        # verify in feed
        time.sleep(10)
        tok = page.evaluate("async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}")
        hdr = {"Authorization": "Bearer " + str(tok)}
        for pg in range(0, 5):
            r = requests.get(SUNO + "/api/feed/?limit=50&page=" + str(pg), headers=hdr, timeout=20)
            if r.status_code != 200:
                break
            clips = r.json() if isinstance(r.json(), list) else r.json().get("clips", [])
            for c in clips:
                if stem in str(c.get("title", "")).lower() and c.get("model_name") == "chirp-chirp":
                    print("VERIFIED: " + str(c.get("title")) + " " + str(c.get("id")), flush=True)
            if len(clips) < 50:
                break
        b.close()

if __name__ == "__main__":
    main()
