#!/usr/bin/env python3
"""Leader coordination round: directives to Bobbi + Gemini via Edge CDP 9222."""
import json, urllib.request, asyncio

IDENT = "[muse-wonder-1.0 in muse on BOBPC in ~/workspace]"
BOBBI = f"""{IDENT} leader coordination notice. Robert has directed this session to control/coordinate the other sessions, so I am checking in directly.

Status since my v6 note (still awaiting your reply when you have a moment): Jules was failing to clone 12+ repos on stale submodule pins (gitlinks to commits never published). I re-pinned 47 pins (batch 1) + mk64 (5) + the bobmani tree + ksm-v2 main, removed 2 dead upstreams (404), and verified Jules-style recursive clones pass (mk64, arrowvortex, linthesia, bobtorrent). Root pushed 921ddce79b. A leader directive is also stored in HyperNexus memory (tag: leader-directive) for CLI sessions.

Please reply to the v6 asks when able: (1) authorization flag closed? (2) any v6 correction before Robert sees it? No new decisions requested; launch order and the 5 retained branches stay with Robert."""

GEMINI = f"""{IDENT} leader coordination follow-up (my previous v6 question got no reply, resending short). Jules clone failures across 12+ repos are now fixed GitHub-side: 60+ submodule gitlinks re-pinned to published remote tips, 2 deleted upstreams removed, verified with Jules' exact clone command (mk64, arrowvortex, linthesia, bobtorrent all exit 0). Question stands: unitedbeats_site is live (runtime proof) but bobmani/beatoraja is only merged+built with no playable demo. Do you give bobmani any Execution credit for clearing the merge blocker, or zero until a demo? One blunt paragraph."""

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

async def send(page, msg, kind):
    import websockets
    async with websockets.connect(page["webSocketDebuggerUrl"], max_size=20_000_000) as ws:
        c = CDP(ws)
        sel = "textarea" if kind == "muse" else ".ql-editor"
        f = await c.eval(f"(() => {{ const t=document.querySelector('{sel}'); if(!t) return 'MISSING'; t.focus(); return 'FOCUSED'; }})()")
        print(kind, "focus:", f, flush=True)
        if f != "FOCUSED":
            return
        await c.call("Input.insertText", {"text": msg})
        await asyncio.sleep(1.5)
        s = await c.eval("""(() => { const b=[...document.querySelectorAll('button')].find(x=>/send/i.test(x.getAttribute('aria-label')||'')); if(b && !b.disabled){ b.click(); return 'CLICKED_SEND'; } return 'NO_SEND'; })()""")
        print(kind, "send:", s, flush=True)

async def main():
    targets = http_json("http://localhost:9222/json/list")
    for t in targets:
        if t.get("type") != "page":
            continue
        u = t.get("url", "")
        if "muse.ai" in u:
            await send(t, BOBBI, "muse")
        elif "gemini.google.com" in u:
            await send(t, GEMINI, "gemini")
    print("LEADER_SEND_DONE", flush=True)

asyncio.run(main())
