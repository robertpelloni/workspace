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
        for p in list(b.contexts[0].pages):
            if "suno.com" in p.url:
                try:
                    p.close()
                except Exception:
                    pass
        time.sleep(1)
        page = b.contexts[0].new_page()
        page.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=30000)
        page.wait_for_timeout(9000)
        try:
            page.click('button:has-text("Reject All")', timeout=8000)
        except Exception:
            pass
        page.wait_for_timeout(1500)
        page.evaluate("Array.from(document.querySelectorAll('button')).find(x=>x.innerText.includes('Add audio'))?.click()")
        page.wait_for_timeout(3000)
        n = page.evaluate("document.querySelectorAll('input[type=file]').length")
        print("file inputs: " + str(n), flush=True)
        ok = False
        for i in range(n):
            try:
                page.set_input_files("input[type=file] >> nth=" + str(i), abs_path, timeout=10000)
                ok = True
                print("set nth=" + str(i), flush=True)
            except Exception:
                pass
        if not ok:
            print("file set failed", flush=True)
            b.close()
            return False
        print("waiting for upload modal...", flush=True)
        for i in range(20):
            page.wait_for_timeout(4000)
            body = page.evaluate("document.body.innerText")
            if "uploading" not in body.lower() and ("full song" in body.lower() or stem in body.lower()):
                print("modal ready at " + str(i * 4) + "s", flush=True)
                break
        r = page.evaluate("(()=>{var els=Array.from(document.querySelectorAll('span,div,label,button,li')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim()==='Full Song');if(els.length){els[0].click();return 'clicked'}return 'nf'})()")
        print("full song: " + str(r), flush=True)
        page.wait_for_timeout(2000)
        c = page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button')).find(x=>x.offsetParent&&x.innerText.trim().toLowerCase()==='continue');if(b){b.click();return 'clicked'}return 'nf'})()")
        print("continue: " + str(c), flush=True)
        page.wait_for_timeout(5000)
        tok = page.evaluate("async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}")
        hdr = {"Authorization": "Bearer " + str(tok)}
        time.sleep(15)
        found = False
        for pg in range(0, 6):
            r2 = requests.get(SUNO + "/api/feed/?limit=50&page=" + str(pg), headers=hdr, timeout=20)
            if r2.status_code != 200:
                break
            clips = r2.json() if isinstance(r2.json(), list) else r2.json().get("clips", [])
            if not clips:
                break
            for c in clips:
                t = str(c.get("title", ""))
                if stem in t.lower() and c.get("model_name") == "chirp-chirp":
                    print("UPLOADED: " + t + " " + str(c.get("id")) + " " + str(c.get("status")), flush=True)
                    found = True
            if len(clips) < 50:
                break
        if not found:
            print("not verified yet", flush=True)
        b.close()
        return found

if __name__ == "__main__":
    ok = main()
    print("RESULT: " + str(ok))
