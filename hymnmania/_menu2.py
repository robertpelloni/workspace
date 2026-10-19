import sys, json, time
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

upload = "1c59abae-1e8a-4ccd-a20a-7c35600ee47a"
with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
    page = next((p for p in b.contexts[0].pages if "suno.com" in p.url), None)
    page.goto(f"https://suno.com/song/{upload}", wait_until="load", timeout=40000)
    page.wait_for_timeout(9000)
    # Close any open emoji picker / overlay first
    page.keyboard.press("Escape")
    page.wait_for_timeout(1000)
    # Open More menu via keyboard focus+enter (proven method)
    try:
        page.focus('button[aria-label="More menu contents"]')
        page.keyboard.press("Enter")
        print("more menu opened via keyboard", flush=True)
    except Exception as e:
        print("keyboard more err:", str(e)[:50], flush=True)
        page.evaluate("document.querySelector('button[aria-label=\\\"More menu contents\\\"]')?.click()")
    page.wait_for_timeout(4000)
    # Dump the actual visible menu items (top-level, excluding emoji)
    items = page.evaluate("""JSON.stringify(Array.from(document.querySelectorAll('[role=menuitem],[role=menuitemradio],[role=menuitemcheckbox],li,[data-orientation=vertical] *,div[role=menu] *,div[class*=menu] button,button')).map(e=>(e.innerText||'').trim()).filter(t=>t&&t.length<25&&!/[🔥😍😱]/.test(t)).slice(0,30))""")
    print("menu items:", items, flush=True)
    b.close()
