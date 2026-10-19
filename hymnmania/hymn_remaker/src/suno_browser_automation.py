"""
Suno Browser Automation Client — Driving Suno.com via CDP (Chrome DevTools Protocol).
"""

import json
import time
import logging
import requests
import websocket
import os

logger = logging.getLogger(__name__)


class SunoBrowserAutomation:
    """Automates Suno.com generation by injecting prompts directly into the active Edge tab."""

    def __init__(self, port=9222, base_url="https://suno.com"):
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
                logger.warning(
                    f"Could not connect to Edge debugging port {self.port}: {e}"
                )
                return []

        return [
            t
            for t in targets
            if t.get("type") == "page" and "webSocketDebuggerUrl" in t
        ]

    def _get_active_tab(self, require_suno=False):
        """Find or prioritize the Suno tab."""
        targets = self._get_page_targets()
        suno_targets = [t for t in targets if "suno.com" in t.get("url", "").lower()]
        if suno_targets:
            res_tab = suno_targets[0]
            # Prioritize create page
            for t in suno_targets:
                if "/create" in t.get("url", "").lower():
                    res_tab = t
                    break
            logger.info(
                f"Selected Suno tab: {res_tab.get('url')} (ID: {res_tab.get('id')})"
            )
            return res_tab

        if require_suno:
            raise RuntimeError("No Suno tab found. Please open suno.com in Edge.")
        return targets[0] if targets else None

    def execute_js(self, ws_url, script, timeout=60):
        """Evaluate arbitrary JavaScript on the target tab via CDP and return result."""
        ws = None
        last_err = None
        for attempt in range(6):
            if attempt > 0:
                try:
                    tab = self._get_active_tab(require_suno=True)
                    ws_url = tab.get("webSocketDebuggerUrl")
                except Exception as e:
                    logger.warning(f"Could not re-fetch Suno tab: {e}")

            ws_url_variants = [
                ws_url.replace("localhost", "127.0.0.1"),
                ws_url.replace("127.0.0.1", "localhost"),
            ]
            target_ws = ws_url_variants[attempt % 2]
            try:
                ws = websocket.create_connection(
                    target_ws, suppress_origin=True, timeout=30
                )
                ws.send(json.dumps({"id": 1, "method": "Runtime.enable"}))
                payload = {
                    "id": 2,
                    "method": "Runtime.evaluate",
                    "params": {
                        "expression": script,
                        "returnByValue": True,
                        "awaitPromise": True,
                    },
                }
                ws.send(json.dumps(payload))
                start_poll = time.time()
                while time.time() - start_poll < timeout:
                    try:
                        resp = json.loads(ws.recv())
                        if resp.get("id") == 2:
                            result = resp.get("result", {}).get("result", {})
                            if "exceptionDetails" in resp.get("result", {}):
                                exception = resp["result"]["exceptionDetails"].get(
                                    "exception", {}
                                )
                                if "description" in exception:
                                    raise RuntimeError(
                                        f"JS Error: {exception['description']}"
                                    )
                            return result.get("value")
                    except websocket.WebSocketTimeoutException:
                        pass
                raise TimeoutError(f"CDP Timeout after {timeout}s")
            except Exception as e:
                last_err = e
                logger.warning(f"WebSocket attempt {attempt + 1} failed: {e}")
                time.sleep(3)
            finally:
                if ws:
                    ws.close()
        raise last_err or RuntimeError(
            "Failed to connect to WebSocket after multiple attempts"
        )

    def _send_cdp_cmd(self, ws, msg_id, method, params=None):
        payload = {"id": msg_id, "method": method}
        if params:
            payload["params"] = params
        ws.send(json.dumps(payload))
        start_time = time.time()
        while time.time() - start_time < 30:
            try:
                resp = json.loads(ws.recv())
                if resp.get("id") == msg_id:
                    return resp
            except websocket.WebSocketTimeoutException:
                pass
        raise TimeoutError(f"No response for {method}")

    def cdp_click(self, ws_url, selector):
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
            return False

        self._cdp_click_coords(ws_url, coords[0], coords[1])
        return True

    def _cdp_click_coords(self, ws_url, x, y):
        ws_url = ws_url.replace("localhost", "127.0.0.1")
        ws = None
        try:
            ws = websocket.create_connection(ws_url, suppress_origin=True, timeout=10)
            ws.send(
                json.dumps(
                    {
                        "id": 71,
                        "method": "Input.dispatchMouseEvent",
                        "params": {"type": "mouseMoved", "x": x, "y": y},
                    }
                )
            )
            ws.recv()
            time.sleep(0.1)
            ws.send(
                json.dumps(
                    {
                        "id": 72,
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
            ws.recv()
            time.sleep(0.5)
            ws.send(
                json.dumps(
                    {
                        "id": 73,
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
            ws.recv()
        finally:
            if ws:
                ws.close()

    def _clear_suno_popups(self, ws_url):
        """Clear modals/overlays in Suno."""
        clear_js = """
        (function() {
            // Dismiss cookie banners or intro modals
            const all = Array.from(document.querySelectorAll('button, [role="button"]'));
            const closeBtn = all.find(el => {
                const t = (el.innerText || '').toLowerCase();
                const a = (el.getAttribute('aria-label') || '').toLowerCase();
                return (t.includes('close') || t.includes('dismiss') || t.includes('got it') || a.includes('close'));
            });
            if (closeBtn && closeBtn.offsetParent !== null) {
                closeBtn.click();
                return "closed_modal";
            }
            return "ready";
        })()
        """
        self.execute_js(ws_url, clear_js)
        return True

    def _save_debug_screenshot(self, ws_url):
        try:
            ws_url = ws_url.replace("localhost", "127.0.0.1")
            ws = websocket.create_connection(ws_url, suppress_origin=True, timeout=10)
            ws.send(json.dumps({"id": 99, "method": "Page.captureScreenshot"}))
            resp = json.loads(ws.recv())
            if "result" in resp and "data" in resp["result"]:
                import base64

                with open("cdp_debug_suno.png", "wb") as f:
                    f.write(base64.b64decode(resp["result"]["data"]))
                logger.info("Saved debug screenshot to cdp_debug_suno.png")
            ws.close()
        except Exception as e:
            logger.warning(f"Failed to save debug screenshot: {e}")

    def trigger_generation(
        self, prompt, audio_path=None, make_instrumental=True, lyrics=None
    ):
        tab = self._get_active_tab(require_suno=True)
        if not tab:
            raise RuntimeError("No Suno tab found for trigger_generation")
        ws_url = tab.get("webSocketDebuggerUrl")

        # Navigate to create if needed
        if "/create" not in tab.get("url", ""):
            self.execute_js(ws_url, f"window.location.href = '{self.base_url}/create'")
            time.sleep(8)

        self._clear_suno_popups(ws_url)

        # 0. Ensure Custom Mode is ON
        custom_mode_js = """
        (function() {
            const allBtns = Array.from(document.querySelectorAll('button'));
            const b = allBtns.find(el => {
                const txt = (el.innerText || '').toLowerCase();
                return txt.includes('custom') && el.offsetParent !== null;
            });
            if (b) {
                const isChecked = b.className.includes('checked') || b.getAttribute('aria-checked') === 'true';
                if (!isChecked) {
                    b.click();
                    return "toggled_custom";
                }
                return "custom_already_on";
            }
            return "custom_btn_not_found";
        })()
        """
        logger.info(
            f"Suno: Checking Custom Mode... {self.execute_js(ws_url, custom_mode_js)}"
        )
        time.sleep(3)

        # 1. Handle Audio Upload (if provided)
        if audio_path and os.path.exists(audio_path):
            logger.info(f"Suno: Uploading audio {audio_path}...")
            # Switch to Audio tab
            upload_tab_js = """
            (function() {
                const b = Array.from(document.querySelectorAll('button, a')).find(el => el.innerText.includes('Audio') && el.offsetParent !== null);
                if (b) { b.click(); return true; }
                return false;
            })()
            """
            self.execute_js(ws_url, upload_tab_js)
            time.sleep(3)

            ws = None
            try:
                ws = websocket.create_connection(
                    ws_url.replace("localhost", "127.0.0.1"),
                    suppress_origin=True,
                    timeout=15,
                )
                self._send_cdp_cmd(ws, 10, "DOM.enable")
                root = self._send_cdp_cmd(ws, 11, "DOM.getDocument")["result"]["root"][
                    "nodeId"
                ]
                nodes = self._send_cdp_cmd(
                    ws,
                    12,
                    "DOM.querySelectorAll",
                    {"nodeId": root, "selector": "input[type='file']"},
                )
                if nodes["result"]["nodeIds"]:
                    target_node_id = nodes["result"]["nodeIds"][0]
                    self._send_cdp_cmd(
                        ws,
                        13,
                        "DOM.setFileInputFiles",
                        {
                            "files": [os.path.abspath(audio_path)],
                            "nodeId": target_node_id,
                        },
                    )
                    logger.info(
                        "Suno: Audio file injected. Waiting for upload to complete (25s)..."
                    )
                    time.sleep(25)  # Longer wait for Suno upload processing

                    # Handle influence panel after upload (Melody, Percussion, Lyrics)
                    logger.info("Suno: Checking for influence panel...")
                    influence_js = """
                    (function() {
                        // Wait a bit for panel to appear
                        const checkPanel = () => {
                            const buttons = Array.from(document.querySelectorAll('button'));
                            // Find influence options
                            const melody = buttons.find(b =>
                                (b.innerText || '').toLowerCase().includes('melody') && b.offsetParent !== null
                            );
                            const percussion = buttons.find(b =>
                                (b.innerText || '').toLowerCase().includes('percussion') && b.offsetParent !== null
                            );
                            const lyrics = buttons.find(b =>
                                (b.innerText || '').toLowerCase().includes('lyric') && b.offsetParent !== null
                            );
                            return {melody: !!melody, percussion: !!percussion, lyrics: !!lyrics};
                        };
                        return checkPanel();
                    })()
                    """
                    influence = self.execute_js(ws_url, influence_js)
                    logger.info(f"Suno: Influence panel options: {influence}")

                    # Click Melody and Percussion (optionally add Lyrics if provided)
                    select_influence_js = """
                    (function() {
                        const buttons = Array.from(document.querySelectorAll('button'));
                        let clicked = [];

                        const melodyBtn = buttons.find(b =>
                            (b.innerText || '').toLowerCase().includes('melody') && b.offsetParent !== null
                        );
                        if (melodyBtn) { melodyBtn.click(); clicked.push('melody'); }

                        const percussionBtn = buttons.find(b =>
                            (b.innerText || '').toLowerCase().includes('percussion') && b.offsetParent !== null
                        );
                        if (percussionBtn) { percussionBtn.click(); clicked.push('percussion'); }

                        // Click Lyrics if provided and button exists
                        const lyricsBtn = buttons.find(b =>
                            (b.innerText || '').toLowerCase().includes('lyric') && b.offsetParent !== null
                        );
                        if (lyricsBtn && arguments[0]) {
                            lyricsBtn.click();
                            clicked.push('lyrics');
                        }

                        // Look for a Done/Confirm/Apply button
                        const doneBtn = buttons.find(b =>
                            (b.innerText || '').toLowerCase().includes('done') ||
                            (b.innerText || '').toLowerCase().includes('apply') ||
                            (b.innerText || '').toLowerCase().includes('confirm')
                        );
                        if (doneBtn && doneBtn.offsetParent !== null) {
                            doneBtn.click();
                            clicked.push('done');
                        }
                        return clicked;
                    })(!!arguments[0])
                    """
                    clicked = self.execute_js(ws_url, select_influence_js)
                    logger.info(f"Suno: Selected influence options: {clicked}")
                    time.sleep(2)

                    # 2.x Fill lyrics if they were supplied
                    if lyrics:
                        logger.info(
                            "Suno: Injecting lyrics into the lyrics textarea..."
                        )
                        lyrics_js = f"""
                        (function() {{
                            // After clicking the Lyrics button, a textarea usually appears.
                            const textareas = Array.from(document.querySelectorAll('textarea')).filter(t => t.offsetParent !== null);
                            const lyricTa = textareas.find(t => (t.placeholder || '').toLowerCase().includes('lyric'));
                            if (!lyricTa) return "no_lyrics_textarea";

                            // Set value via React props (if available) then native setter
                            const propsKey = Object.keys(lyricTa).find(k => k.startsWith('__reactProps$'));
                            if (propsKey && lyricTa[propsKey] && lyricTa[propsKey].onChange) {{
                                lyricTa[propsKey].onChange({{ target: {{ value: {json.dumps(lyrics)} }}, persist: () => {{}} }});
                            }}
                            const setter = Object.getOwnPropertyDescriptor(window.HTMLTextAreaElement.prototype, 'value').set;
                            setter.call(lyricTa, {json.dumps(lyrics)});
                            lyricTa.dispatchEvent(new Event('input', {{bubbles:true}}));
                            lyricTa.dispatchEvent(new Event('change', {{bubbles:true}}));
                            return "lyrics_set";
                        }})()
                        """
                        logger.info(
                            f"Suno: Lyrics injection result: {self.execute_js(ws_url, lyrics_js)}"
                        )
                        time.sleep(1)

                    self._clear_suno_popups(ws_url)
            finally:
                if ws:
                    ws.close()

        # 1.5 Click "Simple" mode (Suno's new UI uses Simple/Advanced tabs)
        logger.info("Suno: Switching to Simple mode...")
        simple_js = """
        (function() {
            const btns = Array.from(document.querySelectorAll('button'));
            const simpleBtn = btns.find(el =>
                el.innerText.trim() === 'Simple' && el.offsetParent !== null
            );
            if (simpleBtn) {
                const isActive = simpleBtn.className.includes('active');
                if (!isActive) {
                    simpleBtn.click();
                    return "clicked_simple";
                }
                return "already_simple";
            }
            return "simple_btn_not_found";
        })()
        """
        logger.info(f"Suno: Mode switch result: {self.execute_js(ws_url, simple_js)}")
        time.sleep(2)

        # 2. Set Prompt (Style) on the FIRST visible textarea
        logger.info(f"Suno: Setting style/prompt: {prompt[:50]}...")
        prompt_js = f"""
        (function() {{
            const textareas = Array.from(document.querySelectorAll('textarea')).filter(el => el.offsetParent !== null);
            if (textareas.length === 0) return "no_textareas";
            let ta = textareas[0];

            // Try React Props first
            const propsKey = Object.keys(ta).find(k => k.startsWith('__reactProps$'));
            if (propsKey && ta[propsKey] && ta[propsKey].onChange) {{
                ta[propsKey].onChange({{ target: {{ value: {json.dumps(prompt)} }}, persist: () => {{}} }});
            }}

            const setter = Object.getOwnPropertyDescriptor(window.HTMLTextAreaElement.prototype, 'value').set;
            setter.call(ta, {json.dumps(prompt)});
            ta.dispatchEvent(new Event('input', {{ bubbles: true }}));
            ta.dispatchEvent(new Event('change', {{ bubbles: true }}));
            return "set_on_" + (ta.placeholder || "first_textarea");
        }}())
        """
        logger.info(
            f"Suno: Prompt injection result: {self.execute_js(ws_url, prompt_js)}"
        )

        # 3. Toggle Instrumental
        if make_instrumental:
            instr_js = """
            (function() {
                const b = Array.from(document.querySelectorAll('button')).find(el => el.innerText.includes('Instrumental') && el.offsetParent !== null);
                if (b) {
                    const isChecked = b.className.includes('checked') || b.getAttribute('aria-checked') === 'true' || b.innerText.includes('ON');
                    if (!isChecked) {
                        b.click();
                        return "toggled_instrumental";
                    }
                    return "instrumental_already_on";
                }
                return "instrumental_btn_not_found";
            })()
            """
            logger.info(
                f"Suno: Instrumental check: {self.execute_js(ws_url, instr_js)}"
            )

        # 4. Click Create
        logger.info("Suno: Clicking Create...")
        create_js = """
        (function() {
            const allBtns = Array.from(document.querySelectorAll('button'));
            const b = allBtns.find(el => (el.getAttribute('aria-label') || '').includes('Create') && el.offsetParent !== null)
                    || allBtns.find(el => (el.innerText || '').includes('Create') && el.offsetParent !== null);
            if (b) {
                const info = {
                    text: b.innerText,
                    disabled: b.disabled,
                    classes: b.className
                };
                if (b.disabled) {
                    return "disabled:" + JSON.stringify(info);
                }
                b.click();
                return "clicked:" + JSON.stringify(info);
            }
            return "not_found";
        })()
        """
        res = self.execute_js(ws_url, create_js)
        if res and "clicked" in res:
            logger.info(f"Suno: Generation triggered! Button info: {res}")
            return True
        else:
            logger.warning(f"Suno: Could not trigger generation: {res}")
            self._save_debug_screenshot(ws_url)
            return False

    def wait_for_completion_and_download(self, timeout=400):
        """Poll for completion and trigger download of the latest track."""
        start = time.time()
        logger.info("Suno: Polling for track completion...")
        while time.time() - start < timeout:
            tab = self._get_active_tab(require_suno=True)
            if not tab:
                raise RuntimeError(
                    "No Suno tab found for wait_for_completion_and_download"
                )
            ws_url = tab.get("webSocketDebuggerUrl")

            poll_js = """
            (function() {
                // Find latest track row
                const rows = Array.from(document.querySelectorAll('[data-testid="song-row"], [class*="SongRow"]'));
                if (rows.length === 0) return "no_tracks";

                const latest = rows[0];
                const text = (latest.innerText || '').toLowerCase();

                if (text.includes('error') || text.includes('failed')) return "error";
                if (text.includes('creating') || text.includes('queue') || text.includes('generating')) return "generating";

                // Track is ready if it has a duration and no "creating" text
                const hasDuration = /\\d+:\\d+/.test(text);
                if (hasDuration) {
                    // Try to find download button
                    // Suno often hides it in a "..." menu
                    let moreBtn = latest.querySelector('button[aria-label*="More"], [data-testid*="more-actions"]');
                    if (moreBtn) {
                        moreBtn.click();
                        return "menu_opened";
                    }
                }
                return "waiting";
            })()
            """
            res = self.execute_js(ws_url, poll_js)
            if res == "menu_opened":
                time.sleep(3)
                # Now find "Download" in the menu
                download_js = """
                (function() {
                    const menuItems = Array.from(document.querySelectorAll('[role="menuitem"], button, a'));
                    const dl = menuItems.find(el => (el.innerText || '').toLowerCase().includes('download') && el.offsetParent !== null);
                    if (dl) {
                        dl.click();
                        return "download_clicked";
                    }
                    return "dl_not_found";
                })()
                """
                res2 = self.execute_js(ws_url, download_js)
                if res2 == "download_clicked":
                    logger.info("Suno: Download triggered!")
                    return True

            logger.info(f"Suno status: {res} ({int(time.time() - start)}s)")
            time.sleep(15)
        return False
