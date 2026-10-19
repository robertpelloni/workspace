"""Robust Instagram Reel poster with caption via keyboard.type + verification.
Usage: python ig_post_verify.py <video> <caption_file>
"""
import sys, os, json, io
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

video = os.path.abspath(sys.argv[1])
caption = io.open(sys.argv[2], encoding="utf-8").read()


def click_text(p, texts, roles="div[role=button],button,span,a"):
    return p.evaluate(
        "(function(ts){" 
        "var els=Array.from(document.querySelectorAll('" + roles + "'));"
        "for(var e of els){var t=(e.innerText||'').trim().toLowerCase();"
        "if(ts.includes(t)&&e.offsetParent){e.click();return t}}return 'nf'})(" + json.dumps(texts) + ")"
    )


with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
    ctx = b.contexts[0]
    p = ctx.new_page()
    p.on("dialog", lambda d: d.accept())
    p.goto("https://www.instagram.com/", wait_until="domcontentloaded", timeout=40000)
    p.wait_for_timeout(7000)

    # 1. New post
    p.evaluate("""(function(){var s=document.querySelector('svg[aria-label="New post"]');
        if(s){(s.closest('[role=button],a')||s.parentElement||s).click();return 'ok'}return 'nf'})()""")
    p.wait_for_timeout(3000)
    # 2. Post
    print("menu post:", click_text(p, ["post"]))
    p.wait_for_timeout(4000)
    # 3. upload
    n = p.evaluate("document.querySelectorAll('input[type=file]').length")
    print("file inputs:", n)
    if not n:
        print("NO FILE INPUT"); b.close(); raise SystemExit
    p.set_input_files("input[type=file]", video, timeout=120000)
    print("file set")
    # 4. wait for processing -> Next enabled
    for i in range(24):
        p.wait_for_timeout(5000)
        body = p.evaluate("document.body.innerText").lower()
        if "next" in body and "processing" not in body:
            print(f" ready ({i*5}s)")
            break
    # 5. Next twice (crop, edit)
    for step in range(2):
        r = click_text(p, ["next"])
        print(f" next {step}: {r}")
        p.wait_for_timeout(6000)

    # 6. Wait for caption editor ("Write a caption...")
    p.wait_for_timeout(3000)
    eds = p.evaluate("""JSON.stringify(Array.from(document.querySelectorAll('[contenteditable=true],textarea,[role=textbox]')).filter(x=>x.offsetParent).map(x=>x.getAttribute('aria-label')||x.getAttribute('placeholder')||x.tagName))""")
    print("editors:", eds)
    focused = p.evaluate("""(function(){var es=Array.from(document.querySelectorAll('[contenteditable=true],textarea,[role=textbox]')).filter(x=>x.offsetParent&&x.tagName!=='BODY');
        var e=es.find(x=>/caption|write/i.test((x.getAttribute('aria-label')||'')+(x.getAttribute('placeholder')||'')))||es[0];
        if(e){e.click();e.focus();return 'focused'}return 'nf'})()""")
    print("caption editor:", focused)
    p.wait_for_timeout(1200)
    if focused == "focused":
        p.keyboard.type(caption, delay=6)
        p.wait_for_timeout(2500)
        clen = p.evaluate("""(()=>{var es=Array.from(document.querySelectorAll('[contenteditable=true],textarea')).filter(x=>x.offsetParent);return es.map(e=>(e.innerText||e.value||'').length).join(',')})()""")
        print("caption lengths:", clen)

    # 7. Share
    r = click_text(p, ["share"])
    print("share click:", r)
    p.wait_for_timeout(8000)
    body = p.evaluate("document.body.innerText").lower()
    print("after share url:", p.url[:60])
    if "share" in body and "processing" in body:
        print("still processing; waiting...")
        p.wait_for_timeout(15000)
    print("done")
    b.close()
