import sys, os, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

def main():
    video = os.path.abspath(sys.argv[1])
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        fb = b.contexts[0].new_page()
        fb.goto("https://www.facebook.com/reels/create", wait_until="domcontentloaded", timeout=40000)
        fb.wait_for_timeout(10000)
        r0 = fb.evaluate("""() => { var els = Array.from(document.querySelectorAll('div,span,[role=button]')); for (var i=0;i<els.length;i++){ var e=els[i]; var t=(e.innerText||'').trim(); if(t==='Create reel'&&e.offsetParent){ var rr=e.getBoundingClientRect(); if(rr.y>40&&rr.y<150) return JSON.stringify({x:Math.round(rr.x+rr.width/2),y:Math.round(rr.y+rr.height/2)}); } } return 'none'; }""")
        if r0 != 'none':
            d0 = json.loads(r0)
            fb.mouse.click(d0["x"], d0["y"])
            fb.wait_for_timeout(5000)
        r1 = fb.evaluate("""() => { var els=Array.from(document.querySelectorAll('div,span,[role=button]')); for(var i=0;i<els.length;i++){ var e=els[i]; if((e.innerText||'').trim()==='Add video'&&e.offsetParent){ var ir=e.getBoundingClientRect(); return JSON.stringify({x:Math.round(ir.x+ir.width/2),y:Math.round(ir.y+ir.height/2)}); } } return 'none'; }""")
        if r1 != 'none':
            d1 = json.loads(r1)
            fb.mouse.click(d1["x"], d1["y"])
        fb.wait_for_timeout(3000)
        fb.set_input_files("input[type=file]", video, timeout=120000)
        print("file set")
        for i in range(20):
            fb.wait_for_timeout(5000)
            body = fb.evaluate("document.body.innerText")
            if "checking for copyrighted" not in body.lower():
                print(f"ready at {i*5}s"); break
        # Dump ALL buttons visible with positions, plus editors
        dump = fb.evaluate("""() => {
            var btns = Array.from(document.querySelectorAll('div[role=button],button')).filter(e=>e.offsetParent).map((e,i)=>{
                var r=e.getBoundingClientRect();
                return {t:(e.innerText||e.getAttribute('aria-label')||'').trim().slice(0,30), x:Math.round(r.x), y:Math.round(r.y)};
            }).filter(b=>b.t);
            var eds = Array.from(document.querySelectorAll('[contenteditable=true],textarea,[role=textbox]')).filter(e=>e.offsetParent).map((e,i)=>({tag:e.tagName, ce:e.getAttribute('contenteditable'), ar:e.getAttribute('aria-label')||'', x:Math.round(e.getBoundingClientRect().x), y:Math.round(e.getBoundingClientRect().y)}));
            return JSON.stringify({buttons: btns, editors: eds});
        }""")
        d = json.loads(dump)
        print("BUTTONS:", json.dumps(d["buttons"], indent=0))
        print("EDITORS:", json.dumps(d["editors"]))
        b.close()

if __name__ == "__main__":
    main()
