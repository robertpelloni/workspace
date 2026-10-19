"""
Udio Browser Automation Client — Driving Udio.com via CDP (Chrome DevTools Protocol).
"""

import json
import time
import logging
import requests
import websocket
import sys
import os

logger = logging.getLogger(__name__)

class UdioBrowserAutomation:
    """Automates Udio.com generation by injecting prompts directly into the active Edge tab."""

    def __init__(self, port=9222, base_url="https://www.udio.com"):
        self.port = port
        self.base_url = base_url

    def _get_page_targets(self):
        """Fetch all debuggable targets from Edge and filter for pages."""
        try:
            res = requests.get(f"http://127.0.0.1:{self.port}/json", timeout=3)
            targets = res.json()
        except Exception:
            try:
                res = requests.get(f"http://localhost:{self.port}/json", timeout=3)
                targets = res.json()
            except Exception as e:
                logger.warning(f"Could not connect to Edge debugging port {self.port}: {e}")
                return []

        return [t for t in targets if t.get('type') == 'page' and 'webSocketDebuggerUrl' in t]

    def _get_active_tab(self, require_udio=False):
        """Find or prioritize the Udio tab."""
        targets = self._get_page_targets()
        udio_targets = [t for t in targets if 'udio.com' in t.get('url', '').lower()]
        if udio_targets:
            res_tab = udio_targets[0]
            for t in udio_targets:
                if '/create' in t.get('url', '').lower(): res_tab = t; break
            logger.info(f"Selected Udio tab: {res_tab.get('url')} (ID: {res_tab.get('id')})")
            return res_tab

        if require_udio:
            raise RuntimeError("No Udio tab found.")
        return targets[0] if targets else None

    def execute_js(self, ws_url, script, timeout=60):
        """Evaluate arbitrary JavaScript on the target tab via CDP and return result."""
        ws = None
        last_err = None
        for attempt in range(6):
            # Re-fetch active tab if ID changed or on retry
            if attempt > 0:
                try:
                    tab = self._get_active_tab(require_udio=True)
                    ws_url = tab.get('webSocketDebuggerUrl')
                except Exception as e:
                    logger.warning(f"Could not re-fetch Udio tab: {e}")

            ws_url_variants = [ws_url.replace('localhost', '127.0.0.1'), ws_url.replace('127.0.0.1', 'localhost')]
            target_ws = ws_url_variants[attempt % 2]
            try:
                ws = websocket.create_connection(target_ws, suppress_origin=True, timeout=30)
                ws.send(json.dumps({"id": 1, "method": "Runtime.enable"}))
                payload = {
                    "id": 2,
                    "method": "Runtime.evaluate",
                    "params": {
                        "expression": script,
                        "returnByValue": True,
                        "awaitPromise": True
                    }
                }
                ws.send(json.dumps(payload))
                start_poll = time.time()
                while time.time() - start_poll < timeout:
                    try:
                        resp = json.loads(ws.recv())
                        if resp.get('id') == 2:
                            result = resp.get('result', {}).get('result', {})
                            if 'exceptionDetails' in resp.get('result', {}):
                                exception = resp['result']['exceptionDetails'].get('exception', {})
                                if 'description' in exception:
                                     raise RuntimeError(f"JS Error: {exception['description']}")
                            return result.get('value')
                    except websocket.WebSocketTimeoutException: pass
                raise TimeoutError(f"CDP Timeout after {timeout}s")
            except Exception as e:
                last_err = e
                logger.warning(f"WebSocket attempt {attempt+1} to {target_ws} failed: {e}")
                time.sleep(3)
            finally:
                if ws: ws.close()
        raise last_err or RuntimeError("Failed to connect to WebSocket after multiple attempts")

    def _send_cdp_cmd(self, ws, msg_id, method, params=None):
        payload = {"id": msg_id, "method": method}
        if params: payload["params"] = params
        ws.send(json.dumps(payload))
        start_time = time.time()
        while time.time() - start_time < 30:
            try:
                resp = json.loads(ws.recv())
                if resp.get("id") == msg_id: return resp
            except websocket.WebSocketTimeoutException: pass
        raise TimeoutError(f"No response for {method}")

    def navigate_to(self, tab, url):
        logger.info(f"Navigating tab to {url}...")
        ws_url = tab.get('webSocketDebuggerUrl')
        try: self.execute_js(ws_url, f"(function() {{ window.location.href = '{url}'; }})()")
        except: pass
        time.sleep(10)

    def navigate_to_create(self, tab):
        self.navigate_to(tab, f"{self.base_url}/create")

    def cdp_click(self, ws_url, selector):
        """Perform a real mouse click on the element matched by selector via CDP."""
        find_js = f"""
        (function() {{
            const el = document.querySelector("{selector}");
            if (!el || el.offsetParent === null) return null;
            el.scrollIntoView({{ block: 'center' }});
            const r = el.getBoundingClientRect();
            return [r.left + r.width/2, r.top + r.height/2];
        }})()
        """
        coords = self.execute_js(ws_url, find_js)
        if not coords:
            logger.warning(f"Could not find or visible element for selector: {selector}")
            return False

        logger.info(f"Clicking coords {coords} for {selector}")
        self._cdp_click_coords(ws_url, coords[0], coords[1])
        return True

    def _clear_udio_popups(self, ws_url):
        """Detect and clear Udio modals like 'Upload Confirmation' and selection mode."""
        find_popup_js = """
        (function() {
            function findByText(text) {
                const xpath = `//*[contains(translate(text(), 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 'abcdefghijklmnopqrstuvwxyz'), '${text.toLowerCase()}')]`;
                const result = document.evaluate(xpath, document, null, XPathResult.ANY_TYPE, null);
                let node = result.iterateNext();
                while(node) {
                    if (node.offsetParent !== null && (node.tagName === 'BUTTON' || node.getAttribute('role') === 'button' || node.onclick)) return node;
                    node = result.iterateNext();
                }
                return null;
            }

            const all = Array.from(document.querySelectorAll('*')).filter(el => el.tagName !== 'SCRIPT' && el.tagName !== 'STYLE');

            // 0. Credit Check
            const creditEl = all.find(el => el.textContent.includes('Credits') && /\\d+/.test(el.textContent) && el.offsetParent !== null && el.children.length === 0);
            const credits = creditEl ? creditEl.textContent.trim() : "Unknown";

            // 1. Confirm Modals (Prioritized)
            const confirmBtn = findByText('i understand and confirm') || findByText('confirm') || findByText('i understand') || findByText('got it');
            if (confirmBtn) {
                return { action: "click_confirm", text: confirmBtn.textContent.trim(), credits: credits };
            }

            // 2. Selection Mode
            const clearBtn = all.find(el => {
                const a = (el.getAttribute('aria-label') || '').toLowerCase();
                return (a.includes('clear selected') || a === 'clear selection') && el.offsetParent !== null;
            });
            if (clearBtn) { return { action: "clear_selection", selector: "button[aria-label*='ear selected']", credits: credits }; }

            // 3. Close/Dismiss Modals
            const closeBtn = findByText('close') || findByText('dismiss') || findByText('ok') || all.find(el => (el.getAttribute('aria-label') || '').toLowerCase().includes('close') && el.offsetParent !== null);
            if (closeBtn) {
                const t = closeBtn.textContent.trim() || closeBtn.getAttribute('aria-label') || 'close';
                if (!t.toLowerCase().includes('play') && !t.toLowerCase().includes('track')) {
                    return { action: "close_modal", text: t, credits: credits };
                }
            }

            return { action: null, credits: credits };
        })()
        """
        logger.info("Clearing Udio modals and checking credits...")
        for i in range(12):
            popup = self.execute_js(ws_url, find_popup_js, timeout=30)
            if popup:
                credits = popup.get('credits', 'Unknown')
                if i == 0: logger.info(f"  Current Udio Credits: {credits}")

                action = popup.get('action')
                if action:
                    text = popup.get('text')
                    selector = popup.get('selector')
                    logger.info(f"  Action (attempt {i+1}): {action} on {text or selector}")

                    if text:
                        click_js = f"""
                        (function() {{
                            function findByText(text) {{
                                const xpath = `//*[contains(translate(text(), 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 'abcdefghijklmnopqrstuvwxyz'), '${{text.toLowerCase()}}')]`;
                                const result = document.evaluate(xpath, document, null, XPathResult.ANY_TYPE, null);
                                let node = result.iterateNext();
                                while(node) {{
                                    if (node.offsetParent !== null && (node.tagName === 'BUTTON' || node.getAttribute('role') === 'button')) return node;
                                    node = result.iterateNext();
                                }}
                                return null;
                            }}
                            const el = findByText("{text}");
                            if (el) {{
                                el.click();
                                // Aggressive: hide modal container
                                let p = el.parentElement;
                                for(let j=0; j<8; j++) {{
                                    if(!p) break;
                                    if(p.getAttribute('role') === 'dialog' || p.className.toLowerCase().includes('modal')) {{
                                        p.style.visibility = 'hidden';
                                        p.style.pointerEvents = 'none';
                                        break;
                                    }}
                                    p = p.parentElement;
                                }}
                                const r = el.getBoundingClientRect();
                                return [r.left + r.width/2, r.top + r.height/2];
                            }}
                            return null;
                        }})()
                        """
                        coords = self.execute_js(ws_url, click_js)
                        if coords:
                            self._cdp_click_coords(ws_url, coords[0], coords[1])
                    else:
                        self.cdp_click(ws_url, selector)

                    time.sleep(3)
                    if i >= 10: self.execute_js(ws_url, "window.location.reload()"); time.sleep(12); return True
                else:
                    time.sleep(1)
                    if i > 1: break
        return True

    def _cdp_click_coords(self, ws_url, x, y):
        # We try both 127.0.0.1 and localhost
        ws_variants = [ws_url.replace('localhost', '127.0.0.1'), ws_url.replace('127.0.0.1', 'localhost')]
        ws = None
        last_err = None
        for variant in ws_variants:
            try:
                ws = websocket.create_connection(variant, suppress_origin=True, timeout=10)
                # Hover/Move
                ws.send(json.dumps({"id": 71, "method": "Input.dispatchMouseEvent", "params": {"type": "mouseMoved", "x": x, "y": y}}))
                ws.recv()
                time.sleep(0.2)
                # Click sequence
                ws.send(json.dumps({"id": 72, "method": "Input.dispatchMouseEvent", "params": {"type": "mousePressed", "x": x, "y": y, "button": "left", "clickCount": 1}}))
                ws.recv()
                time.sleep(1.2) # Solid hold time for complex UIs
                ws.send(json.dumps({"id": 73, "method": "Input.dispatchMouseEvent", "params": {"type": "mouseReleased", "x": x, "y": y, "button": "left", "clickCount": 1}}))
                ws.recv()
                return
            except Exception as e:
                last_err = e
                continue
            finally:
                if ws: ws.close()
        if last_err: logger.warning(f"CDP Click coords failed on all variants: {last_err}")

    def _cdp_type(self, ws_url, text):
        ws_variants = [ws_url.replace('localhost', '127.0.0.1'), ws_url.replace('127.0.0.1', 'localhost')]
        ws = None
        for variant in ws_variants:
            try:
                ws = websocket.create_connection(variant, suppress_origin=True, timeout=10)
                ws.send(json.dumps({"id": 80, "method": "Input.insertText", "params": {"text": text}}))
                ws.recv()
                # Press Enter
                ws.send(json.dumps({"id": 81, "method": "Input.dispatchKeyEvent", "params": {"type": "keyDown", "windowsVirtualKeyCode": 13, "nativeVirtualKeyCode": 13, "key": "Enter", "code": "Enter"}}))
                ws.recv()
                ws.send(json.dumps({"id": 82, "method": "Input.dispatchKeyEvent", "params": {"type": "keyUp", "windowsVirtualKeyCode": 13, "nativeVirtualKeyCode": 13, "key": "Enter", "code": "Enter"}}))
                ws.recv()
                return
            except Exception: continue
            finally:
                if ws: ws.close()

    def _save_debug_screenshot(self, ws_url):
        try:
            ws_url = ws_url.replace('localhost', '127.0.0.1')
            ws = websocket.create_connection(ws_url, suppress_origin=True, timeout=10)
            ws.send(json.dumps({"id": 99, "method": "Page.captureScreenshot"}))
            resp = json.loads(ws.recv())
            if 'result' in resp and 'data' in resp['result']:
                import base64
                with open("cdp_debug.png", "wb") as f:
                    f.write(base64.b64decode(resp['result']['data']))
                logger.info("Saved debug screenshot to cdp_debug.png")
            ws.close()
        except Exception as e:
            logger.warning(f"Failed to save debug screenshot: {e}")

    def trigger_generation(self, prompt, audio_path=None, variance=0.85, negative_prompt="organ, classical, baroque, church organ, cathedral"):
        tab = self._get_active_tab(require_udio=True)
        ws_url = tab.get('webSocketDebuggerUrl')
        self.navigate_to_create(tab)

        if audio_path and os.path.exists(audio_path):
            logger.info(f"Uploading {audio_path}...")

            # Click the Upload button first to "wake it up"
            self.execute_js(ws_url, "(function() { const b = Array.from(document.querySelectorAll('button')).find(el => el.textContent.trim().includes('Upload Audio')); if(b) b.click(); })()")
            time.sleep(3)

            ws = None
            try:
                # Use a specific variant for the persistent connection
                ws = websocket.create_connection(ws_url.replace('localhost', '127.0.0.1'), suppress_origin=True, timeout=15)
                self._send_cdp_cmd(ws, 10, "DOM.enable")
                root = self._send_cdp_cmd(ws, 11, "DOM.getDocument")['result']['root']['nodeId']

                # Find the visible file input index
                file_input_idx = self.execute_js(ws_url, "(function() { return Array.from(document.querySelectorAll('input[type=file]')).findIndex(el => el.offsetParent !== null); })()")
                if file_input_idx == -1: file_input_idx = 0

                nodes = self._send_cdp_cmd(ws, 12, "DOM.querySelectorAll", {"nodeId": root, "selector": "input[type='file']"})
                target_node_id = nodes['result']['nodeIds'][file_input_idx]
                self._send_cdp_cmd(ws, 13, "DOM.setFileInputFiles", {"files": [os.path.abspath(audio_path)], "nodeId": target_node_id})
            finally:
                if ws: ws.close()
            time.sleep(15)
            self._clear_udio_popups(ws_url)
            time.sleep(5)

        # Focus prompt area first
        focus_js = """
        (function() {
            // Set Variance slider if present
            let varianceSlider = document.querySelector('input[type="range"][min="0.1"][max="1"]');
            if (varianceSlider) {
                const proto = window.HTMLInputElement.prototype;
                const setter = Object.getOwnPropertyDescriptor(proto, 'value').set;
                setter.call(varianceSlider, "%VARIANCE%");
                varianceSlider.dispatchEvent(new Event('input', { bubbles: true }));
                varianceSlider.dispatchEvent(new Event('change', { bubbles: true }));
            }

            // Set Style Reduction (negative prompt) if present
            let negInput = document.querySelector('input[placeholder*="avoid"]') || document.querySelector('input[cmdk-input=""]');
            if (negInput) {
                const proto = window.HTMLInputElement.prototype;
                const setter = Object.getOwnPropertyDescriptor(proto, 'value').set;
                setter.call(negInput, "%NEG_PROMPT%");
                negInput.dispatchEvent(new Event('input', { bubbles: true }));
                negInput.dispatchEvent(new Event('change', { bubbles: true }));
            }

            let textareas = Array.from(document.querySelectorAll('textarea'));
            let inputs = Array.from(document.querySelectorAll('input[type="text"]'));
            let els = textareas.concat(inputs);
            let inp = els.find(el => {
                let p = (el.placeholder || '').toLowerCase();
                let rect = el.getBoundingClientRect();
                return rect.width > 0 && rect.height > 20 && el.offsetParent !== null && (p.includes('describe') || p.includes('prompt') || p.includes('imagine'));
            });
            if (inp) {
                inp.focus();
                const r = inp.getBoundingClientRect();
                return [r.left + r.width/2, r.top + r.height/2];
            }
            return null;
        })()
        """.replace("%VARIANCE%", str(variance)).replace("%NEG_PROMPT%", negative_prompt.replace('"', '\\"').replace('\n', ' '))

        coords = self.execute_js(ws_url, focus_js)
        if coords:
            self._cdp_click_coords(ws_url, coords[0], coords[1])
            time.sleep(1)
            # Clear existing text
            self.execute_js(ws_url, "(function() { document.activeElement.value = ''; })()")
            self._cdp_type(ws_url, prompt)
            logger.info("Prompt typed via CDP.")
        else:
            logger.warning("Could not focus prompt area for CDP typing, falling back to JS injection.")
            # Fallback to JS injection if CDP focus fails
            inj_js = """
            (function() {
                let textareas = Array.from(document.querySelectorAll('textarea'));
                let inp = textareas.find(el => el.offsetParent !== null);
                if (!inp) return "no_input";
                const setter = Object.getOwnPropertyDescriptor(window.HTMLTextAreaElement.prototype, 'value').set;
                setter.call(inp, "%PROMPT%");
                inp.dispatchEvent(new Event('input', { bubbles: true }));
                inp.dispatchEvent(new Event('change', { bubbles: true }));
                return "ready_to_click";
            })()
            """.replace("%PROMPT%", prompt.replace('"', '\\"').replace('\n', ' '))
            self.execute_js(ws_url, inj_js)

        logger.info("Clicking Create...")
        for i in range(12):
            # Re-fetch tab and ws_url on each attempt to be safe
            tab = self._get_active_tab(require_udio=True)
            ws_url = tab.get('webSocketDebuggerUrl')

            # Try specific Magenta button first
            if self.cdp_click(ws_url, "button.bg-brand-magenta"):
                logger.info("SUCCESS: CDP Click triggered! Verifying...")

                for j in range(12):
                    time.sleep(5)
                    verify_js = "(function() { return document.body.innerText.includes('Creating') || document.body.innerText.includes('Generating') || document.body.innerText.includes('Remixing') || document.body.innerText.includes('HYMNMANIA') || document.body.innerText.includes('0/4'); })()"
                    if self.execute_js(ws_url, verify_js):
                        logger.info("SUCCESS: Generation verified.")
                        return True

                    # Aggressive retry click during verification
                    self.execute_js(ws_url, "(function() { const b = Array.from(document.querySelectorAll('button')).find(el => (el.textContent.trim() === 'Create' || el.textContent.trim() === 'Remix') && el.offsetParent !== null); if(b) b.click(); })()")

                    screen_text = self.execute_js(ws_url, "(function() { return document.body.innerText.substring(0, 1000).replace(/\\n/g, ' '); })()")
                    logger.info(f"  Verifying... (attempt {j+1}/12). Screen: {screen_text}")
                    if j == 11: self._save_debug_screenshot(ws_url)

            logger.warning(f"Injection attempt {i+1} failed or verification timed out. Retrying...")
            self._clear_udio_popups(ws_url)
            time.sleep(5)
        raise RuntimeError("Failed to trigger generation")

    def wait_for_completion_and_download(self, timeout=400):
        """Poll the browser for the latest track's status and trigger download when ready."""
        start = time.time()
        logger.info(f"Polling browser for track completion...")
        while time.time() - start < timeout:
            try:
                tab = self._get_active_tab(require_udio=True)
                ws_url = tab.get('webSocketDebuggerUrl')
            except Exception as e:
                logger.warning(f"Waiting for Udio tab recovery: {e}")
                time.sleep(15); continue

            poll_js = """
            (function() {
                const clearBtn = document.querySelector('button[aria-label*="clear selected"]');
                if (clearBtn && clearBtn.offsetParent !== null) { clearBtn.click(); return "clearing_selection"; }
                const all = Array.from(document.querySelectorAll('*'));
                const tracks = all.filter(el => {
                    const txt = el.textContent || '';
                    const h = el.offsetHeight;
                    const hasTime = /\\d+:\\d+/.test(txt);
                    const isNew = /\\d+(s|m) ago/.test(txt) || /\\d+ (sec|min) ago/.test(txt) || txt.includes('000m') || txt.includes('001m') || txt.includes('002m') || txt.includes('003m') || txt.includes('<1m');
                    const isCreating = txt.toLowerCase().includes('creating') || txt.toLowerCase().includes('generating') || txt.includes('0/4');
                    return (isNew || isCreating) && h >= 50 && h <= 250 && el.querySelector('button');
                });
                if (tracks.length === 0) {
                    const libBtn = Array.from(document.querySelectorAll('button')).find(b => b.textContent.toLowerCase().includes('library') || (b.getAttribute('aria-label') || '').toLowerCase().includes('library'));
                    if (libBtn && libBtn.offsetParent !== null) { libBtn.click(); return "opening_library"; }
                    return "DIAG_no_tracks";
                }
                tracks.sort((a, b) => a.getBoundingClientRect().top - b.getBoundingClientRect().top);
                const latest = tracks[0];
                const text = latest.textContent.toLowerCase();
                if (text.includes('error') || text.includes('failed')) return "error_row";
                const isReady = text.includes(':') && !text.includes('creating') && !text.includes('generating') && !text.includes('0/4');
                if (!isReady) return "generating (" + text.substring(0, 30).replace(/\\n/g, ' ') + ")";

                // Try Download button directly in the row if present
                let d = latest.querySelector('button[aria-label*="Download"], button[title*="Download"]');
                if (d && d.offsetParent !== null) { d.click(); return "clicked_direct_download"; }

                let b = latest.querySelector('button[aria-label*="More"], button[aria-label*="actions"], [data-testid*="more"]');
                if (!b) {
                    b = document.querySelector('button[aria-label*="Download"]');
                }

                // If the download button was already clicked and the sub-menu is open, find "Audio"
                const subMenuItems = Array.from(document.querySelectorAll('*')).filter(el => {
                    const t = (el.textContent || '').trim().toLowerCase();
                    return (t === 'audio' || t === 'download audio' || t.includes('audio (mp3)') || t === 'mp3' || t.includes('mp3')) && el.offsetParent !== null && el.tagName !== 'SCRIPT';
                });
                if (subMenuItems.length > 0) {
                    const audioBtn = subMenuItems[0];
                    audioBtn.scrollIntoView({ block: 'center' });
                    ['mousedown', 'mouseup', 'click'].forEach(v => audioBtn.dispatchEvent(new MouseEvent(v, { bubbles: true, view: window })));
                    audioBtn.click();
                    return "downloading";
                }

                if (b) {
                    b.scrollIntoView({ block: 'center' });
                    ['mousedown', 'mouseup', 'click'].forEach(v => b.dispatchEvent(new MouseEvent(v, { bubbles: true, view: window })));
                    b.click();
                    return "clicked_download_init";
                }

                const allMenu = Array.from(document.querySelectorAll('[role="menu"] *, .menu *, [class*="menu"] *')).map(el => el.textContent.trim()).filter(t => t.length > 1 && t.length < 30);
                return "ready_no_btn_menu:" + allMenu.join('|').substring(0, 100);
            })()
            """
            try:
                res = self.execute_js(ws_url, poll_js, timeout=15)
                if not res: res = "empty_result"
                if res == "downloading": logger.info("SUCCESS: Download triggered!"); return True
                elif res == "error_row": logger.error("FAILURE: Udio reported error."); return False
                logger.info(f"  Status: {res} ({int(time.time()-start)}s)")
                if "DIAG" in res or "ready_no_btn" in res or "clearing_selection" in res or "clicked_download_init" in res or "waiting_menu" in res or "clicked_direct_download" in res:
                    if res == "clicked_download_init" or "waiting_menu" in res or "clicked_direct_download" in res: time.sleep(4) # Give menu time to pop
                    else:
                        self.execute_js(ws_url, "(function() { window.scrollBy(0, 200); setTimeout(()=>window.scrollBy(0,-200), 200); })()")
                        self._clear_udio_popups(ws_url)
            except Exception as e: logger.warning(f"Error while polling: {e}")
            time.sleep(15)
        return False
