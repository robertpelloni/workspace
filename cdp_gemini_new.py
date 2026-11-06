#!/usr/bin/env python3
"""Ask the bobmani proof question in the NEW Gemini tab (by target id)."""
import json, urllib.request, asyncio, sys

IDENT = "[muse-wonder-1.0 in muse on BOBPC in ~/workspace]"
MSG = f"""{IDENT} quick blunt question. United Beats portfolio scoring: a repo (bobmani/beatoraja, rhythm games) had a 125-commit branch tangle that blocked all cloning; it is now merged into master, pushed, and clone-verified, but there is no playable demo yet. A sister site (unitedbeats.org) shipped live and was fetch-verified. In a Potential-vs-Execution score (0-10 each), does clearing the merge/clone blocker earn bobmani any Execution credit, or zero until a playable demo exists? One paragraph, disagree if you think merged code is being overcredited."""

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
    gem = next(t for t in targets if t.get("id") == "B84A17B114040AC7FFEAA1F4CDB72DFD")
    async with websockets.connect(gem["webSocketDebuggerUrl"], max_size=20_000_000) as ws:
        c = CDP(ws)
        await asyncio.sleep(3)
        print("focus:", await c.eval("(() => { const t=document.querySelector('.ql-editor'); if(!t) return 'MISSING'; t.focus(); return 'FOCUSED'; })()"), flush=True)
        await c.call("Input.insertText", {"text": MSG})
        await asyncio.sleep(1.5)
        print("send:", await c.eval("""(() => { const b=[...document.querySelectorAll('button')].find(x=>/send/i.test(x.getAttribute('aria-label')||'')); if(b && !b.disabled){ b.click(); return 'CLICKED_SEND'; } return 'NO_SEND'; })()"""), flush=True)
        await asyncio.sleep(40)
        txt = str(await c.eval("document.body.innerText") or "")
        idx = txt.rfind("Gemini said")
        print(txt[idx:idx+2200] if idx >= 0 else txt[-2200:], flush=True)

asyncio.run(main())
print("GEMINI_NEW_DONE")
