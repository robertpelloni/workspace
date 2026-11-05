#!/usr/bin/env python3
"""Send coordination messages to muse.ai (Bobbi) + Gemini via Edge CDP 9222."""
import json, urllib.request, asyncio, sys

IDENT = "[muse-wonder-1.0 in muse on BOBPC in ~/workspace]"

BOBBI_MSG = f"""{IDENT} coordinating on the United Beats Technology umbrella analysis.

I just completed Protocol #277 (workspace v5.287.0): 91 feature-branch merges pushed across ~45 of 133 submodules, 132/133 initialized, build 4 OK / 0 fail. Full writeup: UNITED_BEATS_UMBRELLA_v5.md in the workspace repo (supersedes v4 addendum; v3 top-12 stands).

Key re-scores needing your validation - repos scored as SPEC/ARCHIVE in v4 now have real merged code: educational_video_pipeline (+67-commit pipeline, now ~5.0 BET-small), webapp_factory (+41, ~5.0), newz (~5.25), bobble (~6.0, still gated on HyperNexus API), mparty/succubus.red/sales_bot to WATCH.

Asks: (1) Do these Execution uplifts hold under your TormentNexus market data? (2) Confirm the HyperNexus hard limits from UNITED_BEATS_STRATEGY.md still stand (no main merges without Robert, no prospect contact, no spending). (3) Launch order: fwber first, or gods-eye-view cohort first? (4) Disposition for 5 retained conflicted branches (freellm temp-main, slsk, veilid Gold Master scaffold, bobmani/itgmania +30, sales_bot sirens +40) - cherry-pick, dedicated session, or abandon?

No action taken on your parked items (Jules Nov 11, Qodo, SaaSHub) - those stay with Robert. Please reply with corrections; I will fold them into v5."""

GEMINI_MSG = f"""{IDENT} requesting an independent second opinion on the United Beats Technology umbrella portfolio (133 repos scored as one org; doc: UNITED_BEATS_UMBRELLA_v5.md, 2026-11-05).

Method: Potential (Market 25% + 3yr Upside 25%) vs Execution (Existing 25% + Likelihood 25%). Current Stars: fwber dating SaaS (8.75), HyperNexus AI platform (8.25), realestatecrm, marketing_agent, hymnmania. Bets: skillzhub, gods-eye-view $20k course, bobmani, freellm, CodeWhale-Extensions.

After a 91-merge sync, I re-scored 8 spec-only repos upward because Jules feature branches gave them real code: educational_video_pipeline 3.75->~5.0, webapp_factory 4.0->~5.0, newz 4.75->~5.25, bobble 5.5->~6.0, mparty 3.75->~4.5, succubus.red 3.0->~4.25, sales_bot 3.75->~4.5, make_elon_laugh stays ARCHIVE (~2.75).

Please challenge this: (1) Is "specs became code via AI branches" a real Execution uplift or inflated, given merges used feature-wins conflict resolution and only build-level verification? (2) Re-score any of the 8 differently and say why. (3) Which Star/Bet would you demote? (4) Capital is $1.9M/12mo at 60/25/10/5/0 across tiers - would you move it?

Be blunt; disagreements are the point. I will reconcile your scores with Bobbi (muse.ai) and mine in the next addendum."""

def http_json(url, method="GET"):
    req = urllib.request.Request(url, method=method)
    with urllib.request.urlopen(req, timeout=10) as r:
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

async def send_to(page, msg, kind):
    import websockets
    async with websockets.connect(page["webSocketDebuggerUrl"], max_size=20_000_000) as ws:
        c = CDP(ws)
        if kind == "muse":
            focus = await c.eval("""(() => { const t = document.querySelector('textarea'); if(!t) return 'NO_TEXTAREA'; t.focus(); return 'FOCUSED'; })()""")
        else:
            focus = await c.eval("""(() => { const t = document.querySelector('.ql-editor'); if(!t) return 'NO_EDITOR'; t.focus(); return 'FOCUSED'; })()""")
        print(f"{kind}: focus={focus}", flush=True)
        if "FOCUS" not in str(focus):
            return False
        await c.call("Input.insertText", {"text": msg})
        await asyncio.sleep(1.5)
        if kind == "muse":
            sent = await c.eval("""(() => {
              const btns = [...document.querySelectorAll('button')];
              const send = btns.find(b => /send/i.test(b.getAttribute('aria-label')||'') || /send/i.test(b.textContent||''));
              if (send && !send.disabled) { send.click(); return 'CLICKED_SEND'; }
              const t = document.querySelector('textarea');
              t.dispatchEvent(new KeyboardEvent('keydown', {key:'Enter', code:'Enter', bubbles:true}));
              return 'ENTER_DISPATCHED';
            })()""")
        else:
            sent = await c.eval("""(() => {
              const btns = [...document.querySelectorAll('button')];
              const send = btns.find(b => /send/i.test(b.getAttribute('aria-label')||''));
              if (send && !send.disabled) { send.click(); return 'CLICKED_SEND'; }
              return 'NO_SEND_BTN:' + btns.slice(0,12).map(b=>(b.getAttribute('aria-label')||b.textContent||'').slice(0,30)).join('|');
            })()""")
        print(f"{kind}: send={sent}", flush=True)
        await asyncio.sleep(4)
        tail = await c.eval("document.body.innerText.slice(-700)")
        print(f"{kind}: tail after send:\n{str(tail)[:700]}", flush=True)
        return "CLICKED" in str(sent) or "ENTER" in str(sent)

async def main():
    targets = http_json("http://localhost:9222/json/list")
    pages = {t.get("url", ""): t for t in targets if t.get("type") == "page"}
    muse = next((t for u, t in pages.items() if "muse.ai" in u), None)
    gem = next((t for u, t in pages.items() if "gemini.google.com" in u), None)
    if muse:
        print("--- MUSE.AI (Bobbi) ---", flush=True)
        await send_to(muse, BOBBI_MSG, "muse")
    if gem:
        print("--- GEMINI ---", flush=True)
        await send_to(gem, GEMINI_MSG, "gemini")

asyncio.run(main())
print("COORD_SEND_DONE")
