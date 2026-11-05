#!/usr/bin/env python3
"""Read latest responses from muse.ai + Gemini tabs via CDP."""
import json, urllib.request, asyncio

def http_json(url):
    with urllib.request.urlopen(url, timeout=10) as r:
        return json.loads(r.read().decode())

class CDP:
    def __init__(self, ws):
        self.ws = ws
        self.i = 0
    async def call(self, method, params=None):
        self.i += 1
        await self.ws.send(json.dumps({"id": self.i, "method": method, "params": params or {}}))
        while True:
            msg = json.loads(await self.ws.recv())
            if msg.get("id") == self.i:
                return msg
    async def eval(self, expr):
        r = await self.call("Runtime.evaluate", {"expression": expr, "returnByValue": True, "awaitPromise": True})
        return r.get("result", {}).get("result", {}).get("value")

async def read_page(page, kind):
    import websockets
    async with websockets.connect(page["webSocketDebuggerUrl"], max_size=20_000_000) as ws:
        c = CDP(ws)
        txt = await c.eval("document.body.innerText")
        txt = str(txt or "")
        print(f"\n===== {kind} ({page.get('title')}) len={len(txt)} =====")
        # Print from our identity marker onward, capped
        idx = txt.rfind("[muse-wonder-1.0")
        seg = txt[idx:] if idx >= 0 else txt[-6000:]
        print(seg[-7000:])

async def main():
    targets = http_json("http://localhost:9222/json/list")
    for t in targets:
        if t.get("type") != "page":
            continue
        u = t.get("url", "")
        if "gemini.google.com" in u:
            await read_page(t, "GEMINI")
        elif "muse.ai" in u:
            await read_page(t, "MUSE/BOBBI")

asyncio.run(main())
print("\nCOORD_READ_DONE")
