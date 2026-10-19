#!/usr/bin/env python
"""Use real CDP mouse clicks to trigger Suno's upload flow, then set file."""

import os
import sys
import time
import json
import logging
import websocket

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))
from src.suno_browser_automation import SunoBrowserAutomation

logging.basicConfig(
    level=logging.INFO, format="%(asctime)s [%(levelname)s] %(message)s"
)
logger = logging.getLogger("RealClick")

sba = SunoBrowserAutomation()
tab = sba._get_active_tab(require_suno=True)
ws_url = tab.get("webSocketDebuggerUrl")

sba.execute_js(ws_url, "window.location.href='https://suno.com/create'")
time.sleep(10)


def check_ui(label):
    """Quick check for upload-related UI changes."""
    info = sba.execute_js(
        ws_url,
        """
(function() {
    var btns = Array.from(document.querySelectorAll('button'))
        .filter(function(b) { return b.offsetParent !== null; })
        .map(function(b) { return {text:(b.innerText||'').trim().slice(0,30), 
                                   aria:(b.getAttribute('aria-label')||'').slice(0,40)}; })
        .filter(function(b) { return b.text || b.aria; });
    var texts = Array.from(document.querySelectorAll('*'))
        .filter(function(e) { return e.offsetParent !== null && e.children.length === 0; })
        .map(function(e) { return (e.innerText||'').trim(); })
        .filter(function(t) { return t.length > 0 && t.length < 50; });
    var upload = texts.filter(function(t) { return /browse|upload|drop|drag|choose|file|record|melody|percussion/i.test(t); });
    var dialogs = document.querySelectorAll('[role="dialog"], dialog, [class*="modal"]');
    var visibleDialogs = Array.from(dialogs).filter(function(d) { return d.offsetParent !== null; });
    return {uploadTexts: upload, dialogCount: visibleDialogs.length, 
            dialogTexts: visibleDialogs.map(function(d) { return (d.innerText||'').trim().slice(0,100); })};
})()
""",
    )
    logger.info(
        f"  [{label}] uploads={info.get('uploadTexts', [])} dialogs={info.get('dialogCount', 0)} dialogTexts={info.get('dialogTexts', [])}"
    )
    return info


# Find the Audio button's screen coordinates
audio_rect = sba.execute_js(
    ws_url,
    """
(function() {
    var btn = Array.from(document.querySelectorAll('button')).find(function(el) {
        return (el.getAttribute('aria-label')||'').includes('Add audio') && el.offsetParent !== null;
    });
    if (!btn) return null;
    var r = btn.getBoundingClientRect();
    return {x: Math.round(r.left + r.width/2), y: Math.round(r.top + r.height/2), w: r.width, h: r.height};
})()
""",
)
logger.info(f"Audio button rect: {audio_rect}")

if not audio_rect:
    logger.error("Audio button not found!")
    sys.exit(1)

# Use CDP Input.dispatchMouseEvent for a REAL click
ws = websocket.create_connection(
    ws_url.replace("localhost", "127.0.0.1"), suppress_origin=True, timeout=30
)

x, y = audio_rect["x"], audio_rect["y"]
logger.info(f"Clicking Audio button at ({x}, {y})...")

# Move mouse to position
ws.send(
    json.dumps(
        {
            "id": 1,
            "method": "Input.dispatchMouseEvent",
            "params": {"type": "mouseMoved", "x": x, "y": y},
        }
    )
)
time.sleep(0.1)

# Mouse press
ws.send(
    json.dumps(
        {
            "id": 2,
            "method": "Input.dispatchMouseEvent",
            "params": {
                "type": "mousePressed",
                "x": x,
                "y": y,
                "button": "left",
                "clickCount": 1,
            },
        }
    )
)
time.sleep(0.05)

# Mouse release
ws.send(
    json.dumps(
        {
            "id": 3,
            "method": "Input.dispatchMouseEvent",
            "params": {
                "type": "mouseReleased",
                "x": x,
                "y": y,
                "button": "left",
                "clickCount": 1,
            },
        }
    )
)

# Wait and check
time.sleep(5)
info = check_ui("after real click")

# If a dialog appeared, find the upload/browse area and click it too
if info.get("dialogCount", 0) > 0 or info.get("uploadTexts"):
    logger.info("Dialog/upload area detected after real click!")

    # Find any "Browse" or upload area in the dialog
    browse_rect = sba.execute_js(
        ws_url,
        """
(function() {
    var els = Array.from(document.querySelectorAll('*')).filter(function(e) {
        return e.offsetParent !== null && /browse|upload|drop|drag|choose/i.test((e.innerText||''));
    });
    if (els.length === 0) return null;
    var r = els[0].getBoundingClientRect();
    return {x: Math.round(r.left + r.width/2), y: Math.round(r.top + r.height/2), 
            text: (els[0].innerText||'').trim().slice(0,40)};
})()
""",
    )
    if browse_rect:
        logger.info(f"Found browse area: {browse_rect}")
        # Click it
        ws.send(
            json.dumps(
                {
                    "id": 4,
                    "method": "Input.dispatchMouseEvent",
                    "params": {
                        "type": "mousePressed",
                        "x": browse_rect["x"],
                        "y": browse_rect["y"],
                        "button": "left",
                        "clickCount": 1,
                    },
                }
            )
        )
        time.sleep(0.05)
        ws.send(
            json.dumps(
                {
                    "id": 5,
                    "method": "Input.dispatchMouseEvent",
                    "params": {
                        "type": "mouseReleased",
                        "x": browse_rect["x"],
                        "y": browse_rect["y"],
                        "button": "left",
                        "clickCount": 1,
                    },
                }
            )
        )
        time.sleep(1)

# Now set the file via CDP
audio_path = r"C:\Users\hyper\workspace\bobmani\hymnmania\hymn_remaker\output_speed_test\Abide_O_Dearest_Jesus-Christus_Der_Ist_Mein_Leben_normal.wav"
logger.info(f"Setting file: {os.path.getsize(audio_path) / (1024 * 1024):.1f}MB")

ws.send(json.dumps({"id": 10, "method": "DOM.enable"}))
while True:
    resp = json.loads(ws.recv())
    if resp.get("id") == 10:
        break

ws.send(json.dumps({"id": 11, "method": "DOM.getDocument"}))
while True:
    resp = json.loads(ws.recv())
    if resp.get("id") == 11:
        root = resp["result"]["root"]["nodeId"]
        break

ws.send(
    json.dumps(
        {
            "id": 12,
            "method": "DOM.querySelectorAll",
            "params": {"nodeId": root, "selector": "input[type='file']"},
        }
    )
)
while True:
    resp = json.loads(ws.recv())
    if resp.get("id") == 12:
        node_ids = resp["result"]["nodeIds"]
        break

logger.info(f"File input nodes: {node_ids}")

# Try EACH node individually and check which one triggers the upload
for i, nid in enumerate(node_ids):
    logger.info(f"Trying node {nid}...")
    ws.send(
        json.dumps(
            {
                "id": 20 + i,
                "method": "DOM.setFileInputFiles",
                "params": {"files": [os.path.abspath(audio_path)], "nodeId": nid},
            }
        )
    )
    time.sleep(1)
    check_ui(f"node {nid} set")

# Also try with the other file input
time.sleep(5)
check_ui("5s after all nodes set")

# Wait longer
time.sleep(10)
check_ui("15s total")

time.sleep(15)
check_ui("30s total")

ws.close()
