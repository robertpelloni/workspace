#!/usr/bin/env python3
"""Inspect muse.ai + gemini tabs over Edge CDP 9222 (read-only DOM probe)."""
import json, urllib.request, asyncio, sys

def http_json(url):
    with urllib.request.urlopen(url, timeout=10) as r:
        return json.loads(r.read().decode())

async def eval_js(ws_url, expr):
    try:
        import websockets
    except ImportError:
        print("NO_WEBSOCKETS_LIB")
        return None
    async with websockets.connect(ws_url, max_size=20_000_000) as ws:
        await ws.send(json.dumps({"id": 1, "method": "Runtime.evaluate",
                                  "params": {"expression": expr, "returnByValue": True}}))
        msg = json.loads(await ws.recv())
        return msg.get("result", {}).get("result", {}).get("value")

async def main():
    targets = http_json("http://localhost:9222/json/list")
    pages = [t for t in targets if t.get("type") == "page"]
    for p in pages:
        print(f"\n=== PAGE {p.get('title')} | {p.get('url')} | id={p.get('id')}")
        expr = """(() => {
          const els = [...document.querySelectorAll('textarea,[contenteditable=true],[role=textbox],input[type=text]')].map(e => ({tag:e.tagName, cls:(e.className||'').slice(0,80), ph:e.getAttribute('placeholder')||'', aria:e.getAttribute('aria-label')||''}));
          return JSON.stringify({title: document.title, url: location.href, text: document.body.innerText.slice(0, 900), inputs: els.slice(0,8)}, null, 1);
        })()"""
        val = await eval_js(p["webSocketDebuggerUrl"], expr)
        print(val[:2500] if val else "EVAL_FAIL")

asyncio.run(main())
