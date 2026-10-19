import sys, os, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

def main():
    video = os.path.abspath(sys.argv[1])
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        p = b.contexts[0].new_page()
        p.goto("https://www.instagram.com/", wait_until="domcontentloaded", timeout=30000)
        p.wait_for_timeout(7000)
        # click the new-post svg by finding center
        js = """
        () => {
            var s = document.querySelector('svg[aria-label="New post"]');
            if (!s) return 'none';
            var r = s.getBoundingClientRect();
            return JSON.stringify({x: Math.round(r.x + r.width/2), y: Math.round(r.y + r.height/2)});
        }
        """
        pos = json.loads(p.evaluate(js))
        print("pos:", pos)
        p.mouse.click(pos["x"], pos["y"])
        p.wait_for_timeout(3500)
        body = p.evaluate("document.body.innerText")
        print("after click:", body[:150].replace(chr(10), " | "))
        # now click 'Post' (create post)
        r = p.evaluate("(function(){var els=Array.from(document.querySelectorAll('span,div,button,a'));for(var i=0;i<els.length;i++){var e=els[i];if((e.innerText||'').trim()==='Post'&&e.offsetParent){e.click();return 'clicked'}}return 'nf'})()")
        print("post option:", r)
        p.wait_for_timeout(4000)
        # check file input
        n = p.evaluate("document.querySelectorAll('input[type=file]').length")
        print("file inputs:", n)
        if n > 0:
            try:
                p.set_input_files("input[type=file]", video, timeout=60000)
                print("SET OK")
            except Exception as e:
                print("set err:", str(e)[:120])
        else:
            body = p.evaluate("document.body.innerText")
            print("no input, dialog:", body[:250].replace(chr(10), " | "))
        p.wait_for_timeout(8000)
        body = p.evaluate("document.body.innerText")
        print("after:", body[:200].replace(chr(10), " | "))
        b.close()

if __name__ == "__main__":
    main()
