"""Inspect the IG upload modal structure to find the right upload trigger."""
import sys, json, time
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
from playwright.sync_api import sync_playwright

with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp('http://127.0.0.1:9222')
    p = next((x for x in b.contexts[0].pages if 'instagram' in x.url), None)
    p.goto('https://www.instagram.com/', wait_until='domcontentloaded', timeout=30000)
    p.wait_for_timeout(6000)
    # Click New post
    p.evaluate("document.querySelector('svg[aria-label=\"New post\"]')?.closest('[role=button],a')?.click()")
    p.wait_for_timeout(3000)
    body = p.evaluate('document.body.innerText')
    print('after new post:', body[:250].replace(chr(10),' | '))
    # Click Post
    p.evaluate("Array.from(document.querySelectorAll('span,div,button,a')).filter(e=>(e.innerText||'').trim()==='Post'&&e.offsetParent)[0]?.click()")
    p.wait_for_timeout(4000)
    body2 = p.evaluate('document.body.innerText')
    print()
    print('after Post:', body2[:400].replace(chr(10),' | '))
    # Inspect all dialogs / modals
    modals = p.evaluate('''JSON.stringify(Array.from(document.querySelectorAll('[role=dialog],[role=menu]')).map(d=>({role:d.getAttribute('role'),txt:(d.innerText||'').slice(0,200)})))''')
    print()
    print('dialogs:', modals[:500])
    b.close()
