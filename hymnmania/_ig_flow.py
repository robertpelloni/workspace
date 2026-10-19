"""Full IG login + create-post flow test. Usage: python _ig_flow.py"""
import subprocess, os, sys, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

EDGE_PATH = r"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe"
IG_PROFILE = r"C:\Users\jakeg\ig-local-profile"
PORT = 9337

def main():
    d = json.load(open(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".secrets.json")))
    user = d["INSTAGRAM_EMAIL"]
    pw = d["INSTAGRAM_PASSWORD"]
    video = os.path.abspath("pipeline_output/shorts/Jesus_Comes_With_Power_10x_synthwave_A_cover_beatsynced_short_tt.mp4")

    proc = subprocess.Popen([EDGE_PATH, f"--remote-debugging-port={PORT}",
        f"--user-data-dir={IG_PROFILE}", "--no-first-run", "--no-default-browser-check",
        "about:blank"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    time.sleep(6)
    try:
        with sync_playwright() as pw:
            b = pw.chromium.connect_over_cdp(f"http://127.0.0.1:{PORT}")
            p = b.contexts[0].new_page()
            # LOGIN
            p.goto("https://www.instagram.com/accounts/login/", wait_until="domcontentloaded", timeout=40000)
            p.wait_for_timeout(6000)
            em = p.query_selector("input[name='email']")
            if em:
                em.fill(user)
                pwf = p.query_selector("input[name='pass']")
                pwf.fill(pw)
                p.wait_for_timeout(1000)
                p.evaluate("Array.from(document.querySelectorAll('div[role=button],button')).find(x=>x.offsetParent&&(x.innerText||'').trim()==='Log in')?.click()")
                p.wait_for_timeout(10000)
                print("after login URL:", p.url[:50])
            else:
                # maybe already logged in
                print("no login form - maybe logged in already")
                p.goto("https://www.instagram.com/", wait_until="domcontentloaded", timeout=30000)
                p.wait_for_timeout(6000)
            # NEW POST
            r1 = p.evaluate("(function(){var s=document.querySelector('svg[aria-label=\\\"New post\\\"]');if(!s)return 'no new post svg';var el=s.closest('[role=button],a,span')||s;var c=el.closest('[role=button],a')||el;c.click();return 'clicked'})()")
            print("new post:", r1)
            p.wait_for_timeout(3500)
            r2 = p.evaluate("(function(){var els=Array.from(document.querySelectorAll('span,div,button,a'));for(var i=0;i<els.length;i++){var e=els[i];if((e.innerText||'').trim()==='Post'&&e.offsetParent){e.click();return 'clicked'}}return 'nf'})()")
            print("post option:", r2)
            p.wait_for_timeout(5000)
            # find file input
            fi = p.query_selector("input[type=file]")
            print("file input:", "yes" if fi else "no")
            if not fi:
                # click 'Select from computer'
                r3 = p.evaluate("(function(){var els=Array.from(document.querySelectorAll('span,div,button'));for(var i=0;i<els.length;i++){var e=els[i];if((e.innerText||'').trim()==='Select from computer'&&e.offsetParent){e.click();return 'clicked'}}return 'nf'})()")
                print("select from computer:", r3)
                p.wait_for_timeout(3000)
                fi = p.query_selector("input[type=file]")
                print("file input after select:", "yes" if fi else "no")
            if fi:
                try:
                    fi.set_input_files(video, timeout=90000)
                    print("FILE SET SUCCESS")
                except Exception as e:
                    print("set err:", str(e)[:100])
                p.wait_for_timeout(20000)
                body = p.evaluate("document.body.innerText")
                print("after file set:", body[:250].replace(chr(10), " | "))
            b.close()
    except Exception as e:
        print("err:", str(e)[:200])
    finally:
        try:
            proc.terminate()
        except Exception:
            pass

if __name__ == "__main__":
    main()
