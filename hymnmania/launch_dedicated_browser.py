"""Launch a dedicated Edge browser (own profile + port) for our pipeline only.
Then copy session cookies from the shared browser (port 9222) so logins persist.
Usage: python launch_dedicated_browser.py
"""
import subprocess, sys, os, json, time, urllib.request
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

EDGE_PATH = r"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe"
SHARED_PORT = 9222
DEDICATED_PORT = 9333
DEDICATED_PROFILE = os.path.join(os.path.dirname(os.path.abspath(__file__)), ".dedicated-edge-profile")

def get_cookies_from(port, domain_hint=None):
    """Get cookies from a CDP browser session."""
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp(f"http://127.0.0.1:{port}")
        ctx = b.contexts[0]
        cookies = ctx.cookies()
        if domain_hint:
            cookies = [c for c in cookies if domain_hint in c.get("domain", "")]
        # also get localStorage/sessionStorage from suno page if present
        storage = {}
        for p in ctx.pages:
            if "suno.com" in p.url:
                try:
                    storage = p.evaluate("() => { let o={}; for(let i=0;i<localStorage.length;i++){let k=localStorage.key(i); if(k.includes('clerk')||k.includes('suno')||k.includes('session')) o[k]=localStorage.getItem(k);} return o; }")
                except Exception:
                    pass
                break
        b.close()
        return cookies, storage

def set_cookies(port, cookies):
    """Inject cookies into a browser session (must be on the right domain first)."""
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp(f"http://127.0.0.1:{port}")
        ctx = b.contexts[0]
        # ensure a suno.com page exists so cookies apply to that domain
        page = next((p for p in ctx.pages if "suno.com" in p.url), None)
        if not page:
            page = ctx.new_page()
            page.goto("https://suno.com", wait_until="domcontentloaded", timeout=30000)
            page.wait_for_timeout(3000)
        for c in cookies:
            try:
                ctx.add_cookies([{
                    "name": c["name"], "value": c["value"],
                    "domain": c["domain"], "path": c.get("path", "/"),
                    "expires": c.get("expires", -1) if isinstance(c.get("expires"), (int, float)) else -1,
                    "httpOnly": c.get("httpOnly", False), "secure": c.get("secure", False),
                    "sameSite": c.get("sameSite", "Lax"),
                }])
            except Exception:
                pass
        page.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=30000)
        page.wait_for_timeout(5000)
        tok = page.evaluate("async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}")
        print("suno token after cookie inject:", "YES" if tok else "NO")
        b.close()

def main():
    # 1. launch dedicated Edge
    print("Launching dedicated Edge on port", DEDICATED_PORT)
    proc = subprocess.Popen([
        EDGE_PATH, f"--remote-debugging-port={DEDICATED_PORT}",
        f"--user-data-dir={DEDICATED_PROFILE}",
        "--no-first-run", "--no-default-browser-check",
        "about:blank"
    ], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    time.sleep(6)
    # verify it's up
    try:
        r = urllib.request.urlopen(f"http://127.0.0.1:{DEDICATED_PORT}/json/version", timeout=5)
        print("dedicated browser up:", json.loads(r.read()).get("Browser"))
    except Exception as e:
        print("dedicated browser failed:", str(e)[:60])
        return

    # 2. copy suno + tiktok + fb + ig cookies from shared browser
    print("Copying cookies from shared browser (port", SHARED_PORT, ")...")
    all_cookies = []
    try:
        with sync_playwright() as pw:
            b = pw.chromium.connect_over_cdp(f"http://127.0.0.1:{SHARED_PORT}")
            all_cookies = b.contexts[0].cookies()
            b.close()
        print("got", len(all_cookies), "cookies from shared browser")
    except Exception as e:
        print("could not read shared cookies:", str(e)[:60])

    # 3. inject into dedicated browser
    suno_cookies = [c for c in all_cookies if "suno" in c.get("domain","") or "clerk" in c.get("domain","")]
    print("suno cookies:", len(suno_cookies))
    set_cookies(DEDICATED_PORT, suno_cookies)

    # keep browser alive
    print("Dedicated browser running on port", DEDICATED_PORT)
    print("profile:", DEDICATED_PROFILE)
    # don't terminate — leave running
    # (we can't easily keep the subprocess handle across calls, so write a marker)

if __name__ == "__main__":
    main()
