"""Robust Suno upload with full page-recovery. Usage: python upload_robust2.py <mp3>
Retries through page closures until the upload either passes copyright or registers.
"""
import sys, os, json, time, requests
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

SUNO = "https://studio-api-prod.suno.com"

def main():
    abs_path = os.path.abspath(sys.argv[1])
    fname = os.path.basename(abs_path)
    stem = fname.split(".")[0].lower()
    max_try = int(sys.argv[2]) if len(sys.argv) > 2 else 5
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9333")
        for attempt in range(max_try):
            print(f"\n--- attempt {attempt+1} ---", flush=True)
            # use the existing suno page or make one, then reload fresh
            page = next((p for p in b.contexts[0].pages if "suno.com" in p.url), None)
            if not page:
                page = b.contexts[0].new_page()
            try:
                page.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=30000)
                page.wait_for_timeout(8000)
                # click Add audio
                try:
                    page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button')).find(x=>x.innerText.includes('Add audio'));if(b){b.click();return}var t=Array.from(document.querySelectorAll('button')).find(x=>x.innerText.trim()==='Audio');if(t){t.click();return}})()")
                except Exception:
                    pass
                page.wait_for_timeout(4000)
                # set file (may throw on page close)
                try:
                    n = page.evaluate("document.querySelectorAll('input[type=file]').length")
                except Exception:
                    continue
                for i in range(n):
                    try:
                        page.set_input_files("input[type=file] >> nth=" + str(i), abs_path, timeout=30000)
                        print("file set nth=" + str(i), flush=True)
                    except Exception as e:
                        print("set err: " + str(e)[:40], flush=True)
                # watch outcome with page recovery
                outcome = None
                for i in range(30):
                    try:
                        page.wait_for_timeout(4000)
                        body = page.evaluate("document.body.innerText")
                    except Exception:
                        # page closed - re-acquire
                        print("  page closed, re-acquiring...", flush=True)
                        try:
                            page.close()
                        except Exception:
                            pass
                        page = next((p for p in b.contexts[0].pages if "suno.com" in p.url), None)
                        if not page:
                            page = b.contexts[0].new_page()
                            page.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=30000)
                            page.wait_for_timeout(4000)
                        # re-trigger add audio + file
                        try:
                            page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button')).find(x=>x.innerText.includes('Add audio'));if(b){b.click();return}var t=Array.from(document.querySelectorAll('button')).find(x=>x.innerText.trim()==='Audio');if(t){t.click();return}})()")
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
                    low = body.lower()
                    if "matches an existing recording" in low:
                        print("COPYRIGHT MATCH", flush=True)
                        outcome = "copyright"
                        break
                    if "full song" in low and "uploading" not in low:
                        print("UPLOAD OK - full song modal", flush=True)
                        outcome = "ok"
                        # confirm full song + continue
                        try:
                            page.evaluate("(()=>{var els=Array.from(document.querySelectorAll('span,div,label,button,li')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim()==='Full Song');if(els.length){els[0].click();return 'ok'}return 'nf'})()")
                            page.wait_for_timeout(2000)
                            page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button')).find(x=>x.offsetParent&&x.innerText.trim().toLowerCase()==='continue');if(b){b.click();return 'ok'}return 'nf'})()")
                        except Exception:
                            pass
                        break
                    if "uploading" in low and i % 3 == 0:
                        print("  uploading... " + str((i+1)*4) + "s", flush=True)
                if outcome == "copyright":
                    break  # no point retrying same file
                if outcome == "ok":
                    # verify via the page's own JWT. Suno removed the Clerk JS SDK
                    # (typeof Clerk == undefined), so the token now lives in the __session
                    # cookie and is sent as 'Authorization: Bearer <jwt>'.
                    time.sleep(12)
                    tok = None
                    try:
                        from suno_auth import get_jwt
                        # the real API JWT is the Authorization header the page sends,
                        # NOT the __session cookie (that rotates and returns 401)
                        tok = get_jwt(page, navigate=False)
                    except Exception:
                        tok = None
                    if tok:
                        hdr = {"Authorization": "Bearer " + str(tok)}
                        found = False
                        for _ in range(8):
                            try:
                                r = requests.post(SUNO + "/api/feed/v3", headers=hdr, json={"page": 0}, timeout=20)
                                if r.status_code == 200:
                                    clips = r.json() if isinstance(r.json(), list) else r.json().get("clips", [])
                                    for c in clips:
                                        if stem in str(c.get("title", "")).lower():
                                            print("VERIFIED: " + str(c.get("title")) + " " + str(c.get("id")), flush=True)
                                            found = True
                                            break
                            except Exception as e:
                                print("verify err: " + str(e)[:60], flush=True)
                            if found:
                                break
                            time.sleep(6)
                    print("upload confirmed (or timed out verifying)", flush=True)
                    break
            except Exception as e:
                print("attempt err: " + str(e)[:60], flush=True)
                time.sleep(3)
        b.close()

if __name__ == "__main__":
    main()
