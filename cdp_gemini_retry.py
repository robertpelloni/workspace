#!/usr/bin/env python3
"""Retry Gemini with a condensed prompt via CDP (first attempt errored signed-out)."""
import json, urllib.request, asyncio

IDENT = "[muse-wonder-1.0 in muse on BOBPC in ~/workspace]"
MSG = f"""{IDENT} short version: score 133 repos as one United Beats Technology portfolio. Potential (market+upside) vs Execution (existing+likelihood), each 0-10. Stars: fwber dating SaaS 8.75, HyperNexus AI platform 8.25. After merging 91 AI feature branches, I raised 8 former spec-only repos: educational_video_pipeline 3.75 to 5.0, webapp_factory 4.0 to 5.0, newz 4.75 to 5.25, bobble 5.5 to 6.0. Question: is "specs became real code via AI branches" a genuine Execution uplift when verification was build-level only, or inflated? Give one blunt paragraph: agree/disagree, one repo you would score differently, and whether you would move capital from Stars to these Bets."""

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
    gem = next(t for t in targets if t.get("type") == "page" and "gemini.google.com" in t.get("url", ""))
    async with websockets.connect(gem["webSocketDebuggerUrl"], max_size=20_000_000) as ws:
        c = CDP(ws)
        print(await c.eval("(() => { const t=document.querySelector('.ql-editor'); if(!t) return 'NO_EDITOR'; t.focus(); return 'FOCUSED'; })()"))
        await c.call("Input.insertText", {"text": MSG})
        await asyncio.sleep(1.5)
        print(await c.eval("""(() => { const b=[...document.querySelectorAll('button')].find(x=>/send/i.test(x.getAttribute('aria-label')||'')); if(b && !b.disabled){ b.click(); return 'CLICKED_SEND'; } return 'NO_SEND'; })()"""))
        await asyncio.sleep(45)
        txt = str(await c.eval("document.body.innerText") or "")
        idx = txt.rfind(IDENT)
        print(txt[idx:][-4500:] if idx >= 0 else txt[-4500:])

asyncio.run(main())
print("GEMINI_RETRY_DONE")
