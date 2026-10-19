import sys, json, time
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

upload = "1c59abae-1e8a-4ccd-a20a-7c35600ee47a"
with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
    page = next((p for p in b.contexts[0].pages if "suno.com" in p.url), None)
    # Go to the SONG page (not create)
    page.goto(f"https://suno.com/song/{upload}", wait_until="load", timeout=40000)
    page.wait_for_timeout(10000)
    print("URL:", page.url[:70])
    body = page.evaluate("document.body.innerText")
    print("song title:", [l for l in body.split(chr(10)) if 'just over' in l.lower()][:2])
    # Find the More menu button
    has_more = page.evaluate("!!document.querySelector('button[aria-label=\\\"More menu contents\\\"]')")
    print("more menu btn:", has_more)
    if has_more:
        page.evaluate("document.querySelector('button[aria-label=\\\"More menu contents\\\"]')?.click()")
        page.wait_for_timeout(4000)
        # list menu items
        items = page.evaluate("""JSON.stringify(Array.from(document.querySelectorAll('[role=menuitem],div[class*=menu] button,button')).map(e=>(e.innerText||'').trim()).filter(t=>t&&t.length<25).slice(0,30))""")
        print("menu items:", items)
        # click Remix
        page.evaluate("Array.from(document.querySelectorAll('[role=menuitem],button')).filter(e=>e.offsetParent&&e.innerText&&e.innerText.trim().toLowerCase()==='remix')[0]?.click()")
        page.wait_for_timeout(4000)
        items2 = page.evaluate("""JSON.stringify(Array.from(document.querySelectorAll('[role=menuitem],div[class*=menu] button,button')).map(e=>(e.innerText||'').trim()).filter(t=>t&&t.length<25).slice(0,40))""")
        print("after remix items:", items2)
    b.close()
