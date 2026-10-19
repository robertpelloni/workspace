import os
import sys
import time
import json
import urllib.request
import websocket

def get_ws_url():
    pages = json.load(urllib.request.urlopen("http://127.0.0.1:9222/json"))
    for p in pages:
        if "suno.com" in p.get("url", "") and "stripe" not in p.get("url", ""):
            return p["webSocketDebuggerUrl"].replace("localhost", "127.0.0.1")
    return pages[0]["webSocketDebuggerUrl"].replace("localhost", "127.0.0.1")

def js(ws_url, expr):
    try:
        ws = websocket.create_connection(ws_url, suppress_origin=True, timeout=5)
        ws.send(json.dumps({
            "id": 2,
            "method": "Runtime.evaluate",
            "params": {
                "expression": expr,
                "returnByValue": True,
                "awaitPromise": True
            }
        }))
        for _ in range(15):
            r = ws.recv()
            d = json.loads(r)
            if d.get("id") == 2:
                val = d.get("result", {}).get("result", {}).get("value")
                ws.close()
                return val
        ws.close()
    except Exception as e:
        pass
    return None

def monitor_and_dismiss_modals():
    ws_url = get_ws_url()
    print("Monitoring and resolving Suno upload modals...", flush=True)
    for i in range(45):
        time.sleep(2)
        body = js(ws_url, "document.body.innerText.toLowerCase().substring(0,1000)") or ""
        has_identify = any(p in body for p in ["identify this", "identify vocals", "identify song"])
        has_describe = any(p in body for p in ["describe style", "describe your", "describe audio"])

        # Check overwrite prompt first
        if "overwrite" in body or "replace" in body:
            print("  Resolving overwrite modal...", flush=True)
            js(ws_url, """
                (() => {
                    var btn = Array.from(document.querySelectorAll('button'))
                        .find(b => b.offsetParent !== null && /overwrite|replace|yes|confirm/i.test(b.textContent || ''));
                    if (btn) btn.click();
                })()
            """)
        elif has_identify:
            print("  Resolving identify modal...", flush=True)
            js(ws_url, """
                (() => {
                    var btn = Array.from(document.querySelectorAll('span, p, div, label, button'))
                        .find(el => el.offsetParent !== null && /instrumental/i.test(el.textContent || ''));
                    if (btn) btn.click();
                    setTimeout(function() {
                        var cb = Array.from(document.querySelectorAll('button'))
                            .find(b => b.offsetParent !== null && b.textContent.trim() === 'Continue');
                        if (cb) cb.click();
                    }, 500);
                })()
            """)
        elif has_describe and not has_identify:
            print("  Resolving describe modal...", flush=True)
            js(ws_url, """
                (() => {
                    var tas = Array.from(document.querySelectorAll("textarea"));
                    var ns = Object.getOwnPropertyDescriptor(window.HTMLTextAreaElement.prototype,"value").set;
                    var ta = tas.find(t => t.offsetParent !== null);
                    if (ta) {
                        ns.call(ta, "hymn");
                        ta.dispatchEvent(new Event("input", {bubbles:true}));
                    }
                    setTimeout(function() {
                        var cb = Array.from(document.querySelectorAll('button'))
                            .find(b => b.offsetParent !== null && b.textContent.trim() === 'Continue');
                        if (cb) cb.click();
                    }, 500);
                })()
            """)
        elif "matches an existing recording" in body or "copyright" in body or "error" in body:
            print("  Upload rejected by Copyright engine.", flush=True)
            return False
        else:
            is_modal_active = js(ws_url, "!!Array.from(document.querySelectorAll('span, p, div, label, button, h2')).find(x => /identify this|identify vocals|identify song|describe style|describe your|describe audio/i.test(x.textContent || ''))")
            if not is_modal_active:
                print("  Modals successfully cleared.", flush=True)
                return True
    return False

def main():
    success = monitor_and_dismiss_modals()
    sys.exit(0 if success else 1)

if __name__ == "__main__":
    main()
