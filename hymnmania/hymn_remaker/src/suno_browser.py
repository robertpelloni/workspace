"""
Suno AI browser automation — Playwright-based song generation.

Uses Playwright with playwright-stealth to automate the Suno web UI,
bypassing Cloudflare Turnstile bot detection. The browser handles the
Turnstile challenge automatically, making this the most reliable
generation mode.

Key implementation details (from reverse engineering):
    - The endpoint is /api/generate/v2-web/ (not /v2/)
    - Turnstile token can be null when using proper session cookies
    - The description textarea has placeholder "Describe the sound you want"
    - React state must be updated via __reactProps$ onChange handler
    - Audio upload: POST /api/uploads/audio/ → S3 presigned URL → poll status
    - Button shows "Out of Credits" when credits are exhausted
"""

import os
import time
import json
import logging

logger = logging.getLogger(__name__)


def get_turnstile_token(session_token=None, client_token=None, timeout=30):
    """Obtain a Cloudflare Turnstile token using Playwright.

    Opens a headless browser to the Suno create page, lets the invisible
    Turnstile widget auto-solve, and captures the token from the generate
    request.

    Args:
        session_token (str): Suno __session JWT from browser cookies.
        client_token (str): Suno __client JWT from browser cookies.
        timeout (int): Max seconds to wait for token.

    Returns:
        str: Valid Turnstile token, or None if failed.
    """
    try:
        from playwright.sync_api import sync_playwright
    except ImportError:
        logger.error("Playwright not installed. Run: pip install playwright && python -m playwright install chromium")
        return None

    from hymn_remaker.src.suno_api import GEN_ENDPOINT

    session_token = session_token or os.environ.get("SUNO_SESSION_TOKEN", "")
    client_token = client_token or os.environ.get("SUNO_CLIENT_TOKEN", "")

    captured_token = None

    with sync_playwright() as p:
        browser = p.chromium.launch(
            headless=False,
            args=['--disable-blink-features=AutomationControlled', '--no-sandbox'],
        )
        context = browser.new_context(
            viewport={'width': 1280, 'height': 720},
            user_agent=(
                'Mozilla/5.0 (Windows NT 10.0; Win64; x64) '
                'AppleWebKit/537.36 (KHTML, like Gecko) '
                'Chrome/131.0.0.0 Safari/537.36'
            ),
        )

        # Set auth cookies
        if session_token:
            context.add_cookies([{
                'name': '__session', 'value': session_token,
                'domain': '.suno.com', 'path': '/',
            }])
        if client_token:
            context.add_cookies([{
                'name': '__client', 'value': client_token,
                'domain': '.suno.com', 'path': '/',
            }])

        page = context.new_page()
        page.add_init_script(
            'Object.defineProperty(navigator, "webdriver", {get: () => undefined})'
        )

        # Intercept the generate request to capture the token
        def handle_request(request):
            nonlocal captured_token
            if GEN_ENDPOINT in request.url and request.method == 'POST':
                if request.post_data:
                    try:
                        data = json.loads(request.post_data)
                        token = data.get('token', '')
                        if token and len(str(token)) > 20:
                            captured_token = token
                            logger.info(f"Captured Turnstile token: {str(token)[:40]}...")
                    except Exception:
                        pass

        page.on('request', handle_request)

        # Navigate to create page
        logger.info("Opening Suno create page to harvest Turnstile token...")
        page.goto('https://suno.com/create', timeout=30000, wait_until='domcontentloaded')

        # Wait for the page to fully load
        time.sleep(8)

        # Fill in the description
        try:
            textarea = page.locator('textarea:visible').first
            textarea.click()
            time.sleep(0.3)
            page.keyboard.press('Control+a')
            time.sleep(0.2)
            page.keyboard.type('Deep house instrumental test', delay=30)
            time.sleep(1)

            # Toggle Instrumental
            instr = page.locator('text=Instrumental').first
            if instr.is_visible(timeout=3000):
                instr.click()
                time.sleep(1)

            # Click Create to trigger the Turnstile
            create_btn = page.locator('button[aria-label*="Create"]').first
            if create_btn.is_visible(timeout=5000):
                create_btn.click(timeout=10000)
        except Exception as e:
            logger.warning(f"Error during browser interaction: {e}")

        # Wait for token
        start = time.time()
        while time.time() - start < timeout:
            if captured_token:
                break
            time.sleep(1)

        browser.close()

        if captured_token:
            logger.info(f"Turnstile token captured successfully ({len(str(captured_token))} chars)")
        else:
            logger.warning("Failed to capture Turnstile token")

        return captured_token


def generate_songs_browser(prompt, session_token=None, client_token=None,
                           make_instrumental=True, timeout=300,
                           audio_influence_path=None):
    """Generate songs using Playwright browser automation with stealth.

    Automates the Suno web UI to create a song. Uses playwright-stealth
    to bypass Cloudflare Turnstile bot detection.

    Args:
        prompt (str): Text description for the song.
        session_token (str): Suno __session JWT.
        client_token (str): Suno __client JWT.
        make_instrumental (bool): Generate without vocals.
        timeout (int): Max seconds to wait for generation (default 300).
        audio_influence_path (str): Path to MP3/WAV to upload as influence.

    Returns:
        list: List of clip dictionaries with clip IDs.

    Raises:
        RuntimeError: If browser automation fails or credits exhausted.
    """
    try:
        from playwright.sync_api import sync_playwright
    except ImportError:
        raise RuntimeError(
            "Playwright not installed. Run: pip install playwright && python -m playwright install chromium"
        )

    try:
        from playwright_stealth import Stealth
        use_stealth = True
    except ImportError:
        logger.warning("playwright-stealth not installed. Turnstile may fail.")
        use_stealth = False

    from hymn_remaker.src.suno_api import GEN_ENDPOINT

    session_token = session_token or os.environ.get("SUNO_SESSION_TOKEN", "")
    client_token = client_token or os.environ.get("SUNO_CLIENT_TOKEN", "")

    captured_clips = []

    with sync_playwright() as p:
        # Apply stealth to bypass Turnstile bot detection
        if use_stealth:
            stealth = Stealth()
            stealth.hook_playwright_context(p)

        browser = p.chromium.launch(headless=False, args=['--no-sandbox'])
        context = browser.new_context(viewport={'width': 1280, 'height': 720})

        # Set auth cookies on all relevant domains
        if session_token:
            context.add_cookies([
                {'name': '__session', 'value': session_token, 'domain': '.suno.com', 'path': '/'},
                {'name': '__session', 'value': session_token, 'domain': 'auth.suno.com', 'path': '/'},
            ])
        if client_token:
            context.add_cookies([
                {'name': '__client', 'value': client_token, 'domain': '.suno.com', 'path': '/'},
                {'name': '__client', 'value': client_token, 'domain': 'auth.suno.com', 'path': '/'},
            ])

        page = context.new_page()

        # Response filter for page.expect_response
        def is_generate_response(response):
            return '/api/generate/v2' in response.url and response.status == 200

        # Navigate to create page
        logger.info("Opening Suno create page with stealth...")
        page.goto('https://suno.com/create', timeout=30000, wait_until='domcontentloaded')
        time.sleep(15)

        # ---- Dismiss overlays/modals ----
        for _ in range(3):
            page.keyboard.press('Escape')
            time.sleep(0.5)
        try:
            close_btn = page.locator('[aria-label="Close"]')
            if close_btn.count() > 0:
                close_btn.first.click(force=True)
                time.sleep(1)
        except Exception:
            pass

        # ---- Check for "Out of Credits" ----
        create_btn = page.locator('button[aria-label*="Create"]').first
        btn_text = create_btn.text_content() or ''
        if 'out of credit' in btn_text.lower():
            browser.close()
            raise RuntimeError(
                "Suno account is out of credits. Wait for daily reset "
                "or upgrade the plan at suno.com."
            )

        # ---- Audio Influence Upload ----
        if audio_influence_path and os.path.exists(audio_influence_path):
            logger.info(f"Uploading audio influence: {audio_influence_path}")
            try:
                audio_tab = page.locator('text=Audio').first
                if audio_tab.is_visible(timeout=5000):
                    audio_tab.click(force=True)
                    logger.info("Clicked Audio tab")
                    time.sleep(3)

                file_input = page.locator('input[type="file"]').first
                file_input.set_input_files(audio_influence_path)
                logger.info(f"Uploaded audio: {os.path.basename(audio_influence_path)}")

                logger.info("Waiting for audio upload to process...")
                for i in range(30):
                    time.sleep(2)
                    status = page.evaluate('''() => {
                        const el = document.querySelector('[data-upload-status]');
                        return el ? el.getAttribute('data-upload-status') : null;
                    }''')
                    if status == 'complete':
                        logger.info("Audio upload complete!")
                        break
                    if i % 5 == 4:
                        logger.info(f"Upload still processing... ({(i+1)*2}s)")
                time.sleep(3)
            except Exception as e:
                logger.warning(f"Audio influence upload failed: {e}")
                logger.info("Continuing without audio influence...")

        # ---- Set Prompt via React Fiber ----
        logger.info(f"Setting prompt via React fiber: {prompt[:60]}...")
        try:
            result = page.evaluate(f'''() => {{
                const textareas = document.querySelectorAll('textarea');
                let descTextarea = null;
                for (const ta of textareas) {{
                    const ph = (ta.placeholder || '').toLowerCase();
                    if (ph.includes('describe') || ph.includes('sound you want')) {{
                        descTextarea = ta;
                        break;
                    }}
                }}
                if (!descTextarea) {{
                    descTextarea = textareas[textareas.length - 1];
                }}
                if (!descTextarea) return "no description textarea found";

                const prompt = {json.dumps(prompt)};
                const propsKey = Object.keys(descTextarea).find(k => k.startsWith('__reactProps$'));
                if (propsKey) {{
                    const props = descTextarea[propsKey];
                    if (props && props.onChange) {{
                        props.onChange({{
                            target: {{ value: prompt }},
                            currentTarget: {{ value: prompt }},
                            persist: () => {{}},
                        }});
                        return "ok: " + descTextarea.placeholder;
                    }}
                }}

                const setter = Object.getOwnPropertyDescriptor(
                    window.HTMLTextAreaElement.prototype, 'value'
                ).set;
                setter.call(descTextarea, prompt);
                descTextarea.dispatchEvent(new Event('input', {{ bubbles: true }}));
                descTextarea.dispatchEvent(new Event('change', {{ bubbles: true }}));
                return "fallback: " + descTextarea.placeholder;
            }}''')
            logger.info(f"React fiber result: {result}")
            time.sleep(3)
        except Exception as e:
            logger.warning(f"React fiber approach failed: {e}")
            # Fallback: use fill() on the visible textarea
            try:
                textarea = page.locator('textarea:visible').last
                textarea.click(force=True)
                time.sleep(0.3)
                textarea.fill(prompt)
                logger.info("Used fill() as fallback")
                time.sleep(2)
            except Exception as e2:
                logger.error(f"All prompt input methods failed: {e2}")

        # ---- Toggle Instrumental ----
        if make_instrumental:
            try:
                instr = page.locator('button:has-text("Instrumental")').first
                if instr.is_visible(timeout=5000):
                    instr.click(force=True)
                    logger.info("Clicked Instrumental toggle")
                    time.sleep(1)
            except Exception as e:
                logger.debug(f"Instrumental toggle: {e}")

        # ---- Click Create and Wait for Response ----
        create_btn = page.locator('button[aria-label*="Create"]').first
        if create_btn.is_disabled():
            btn_text = create_btn.text_content() or ''
            if 'out of credit' in btn_text.lower():
                browser.close()
                raise RuntimeError("Suno account is out of credits. Wait for daily reset.")
            else:
                logger.warning(f"Create button disabled: {btn_text}")

        if not create_btn.is_disabled():
            logger.info("Clicking Create button...")
            try:
                with page.expect_response(is_generate_response, timeout=timeout * 1000) as resp_info:
                    create_btn.click(force=True, timeout=10000)
                    logger.info("Create button clicked! Waiting for generate response...")

                response = resp_info.value
                logger.info(f"Generate response: {response.status}")
                try:
                    data = response.json()
                    clips = data if isinstance(data, list) else [data]
                    for clip in clips:
                        cid = clip.get('id')
                        if cid:
                            captured_clips.append(clip)
                            logger.info(f"Clip captured: {cid} status={clip.get('status', '?')}")
                except Exception as e:
                    logger.error(f"Error parsing generate response: {e}")
            except Exception as e:
                logger.error(f"Generate response timeout or error: {e}")
        else:
            logger.error("Create button is disabled, cannot generate")

        # Keep browser open briefly for any pending requests
        time.sleep(3)
        browser.close()

    if not captured_clips:
        raise RuntimeError(
            "Browser automation failed - no clips generated. "
            "Possible causes: out of credits, Turnstile blocked, or prompt issue."
        )
    return captured_clips
