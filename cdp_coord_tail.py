#!/usr/bin/env python3
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

async def main():
    import websockets
    targets = http_json("http://localhost:9222/json/list")
    for t in targets:
        if t.get("type") != "page":
            continue
        u = t.get("url", "")
        if "muse.ai" not in u and "gemini.google.com" not in u:
            continue
        kind = "MUSE" if "muse.ai" in u else "GEMINI"
        async with websockets.connect(t["webSocketDebuggerUrl"], max_size=20_000_000) as ws:
            c = CDP(ws)
            txt = str(await c.eval("document.body.innerText") or "")
            print(f"\n===== {kind} len={len(txt)} LAST 2600 =====")
            print(txt[-2600:])

asyncio.run(main())
print("TAIL_DONE")
