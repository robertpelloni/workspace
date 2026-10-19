"""
Udio AI Browser Automation — Advanced Remix Workflow via Playwright.
Handles file upload, advanced sliders, and high-fidelity downloading.
"""

import os
import time
import logging
from pathlib import Path
from playwright.sync_api import sync_playwright
from playwright_stealth import stealth

from hymn_remaker import settings

logger = logging.getLogger(__name__)

def generate_songs_browser(audio_path, prompt, variance=0.35, prompt_strength=0.65, timeout=600):
    """
    Automate the Udio web UI to perform a high-fidelity remix.
    """
    with sync_playwright() as p:
        # 1. Launch Browser with Stealth
        browser = p.chromium.launch(headless=True) # Set to False for debugging
        context = browser.new_context(
            user_agent="Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/148.0.0.0 Safari/537.36 Edg/148.0.0.0",
            viewport={'width': 1920, 'height': 1080}
        )
        page = context.new_page()
        stealth(page)

        # 2. Add Authentication Cookies
        cookie0 = os.environ.get("UDIO_COOKIE_0", "")
        cookie1 = os.environ.get("UDIO_COOKIE_1", "")

        if not cookie0:
            raise RuntimeError("UDIO_COOKIE_0 not found in environment. Run refresh_udio_token.py first.")

        # Udio uses Supabase auth tokens
        context.add_cookies([
            {
                'name': 'sb-ssr-production-auth-token.0',
                'value': cookie0,
                'domain': 'www.udio.com',
                'path': '/',
            }
        ])
        if cookie1:
            context.add_cookies([
                {
                    'name': 'sb-ssr-production-auth-token.1',
                    'value': cookie1,
                    'domain': 'www.udio.com',
                    'path': '/',
                }
            ])

        try:
            logger.info("Navigating to Udio Studio...")
            page.goto("https://www.udio.com/studio", wait_until="networkidle")
            time.sleep(5)

            # 3. Handle File Upload
            logger.info(f"Uploading inspiration media: {os.path.basename(audio_path)}")
            # Find the upload input
            file_input = page.locator("input[type='file']")
            file_input.set_input_files(audio_path)
            time.sleep(5)

            # 4. Select Remix Mode
            # Look for the 'Remix' button that appears after upload
            logger.info("Selecting Remix mode...")
            page.get_by_role("button", name="Remix").click()
            time.sleep(2)

            # 5. Advanced Controls
            logger.info("Configuring Advanced Controls...")
            # Open advanced settings if not visible
            adv_btn = page.get_by_role("button", name="Advanced Controls")
            if adv_btn.is_visible():
                adv_btn.click()
                time.sleep(1)

            # Toggle Manual Mode
            manual_toggle = page.get_by_label("Manual Mode")
            if manual_toggle.is_visible() and not manual_toggle.is_checked():
                manual_toggle.check()

            # Set Sliders (Variance and Prompt Strength)
            # Note: Udio uses custom sliders, we often have to click or type into inputs
            # Here we attempt to find the numeric inputs associated with the sliders
            variance_input = page.locator("input[aria-label='Audio Influence']").or_(page.locator("input[aria-label='Variance']"))
            if variance_input.is_visible():
                variance_input.fill(str(variance))

            strength_input = page.locator("input[aria-label='Prompt Strength']")
            if strength_input.is_visible():
                strength_input.fill(str(prompt_strength))

            # 6. Enter Prompt
            logger.info(f"Entering prompt: {prompt[:50]}...")
            prompt_box = page.get_by_placeholder("Describe the track...")
            prompt_box.fill(prompt)

            # 7. Create!
            logger.info("Triggering generation...")
            page.get_by_role("button", name="Create").click()
            time.sleep(5)

            # 8. Poll for completion
            logger.info("Remix started. Polling for track completion...")
            start_time = time.time()
            final_path = None

            while time.time() - start_time < timeout:
                # Check for 'Download' button on the latest track
                # This is a bit tricky, we usually look for the top-most track in the feed
                latest_track = page.locator(".track-row").first()
                if latest_track.is_visible():
                    status = latest_track.get_attribute("data-status")
                    if status == "ready":
                        # Find the download link
                        # We might need to click the context menu (three dots) first
                        latest_track.locator(".more-actions").click()
                        time.sleep(1)
                        with page.expect_download() as download_info:
                            page.get_by_role("menuitem", name="Download").click()
                        download = download_info.value

                        output_dir = os.path.dirname(audio_path)
                        final_path = os.path.join(output_dir, f"{Path(audio_path).stem}_remake.mp3")
                        download.save_as(final_path)
                        logger.info(f"Download complete: {final_path}")
                        break

                logger.info(f"  Still generating... ({int(time.time() - start_time)}s)")
                time.sleep(15)

            if not final_path:
                # Fallback: check the output folder for any new mp3s
                # in case the download logic failed but the file arrived
                pass

            browser.close()
            return final_path

        except Exception as e:
            logger.error(f"Browser automation failed: {e}")
            # Take screenshot for debugging
            page.screenshot(path="udio_error.png")
            browser.close()
            return None

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    # generate_songs_browser("test.mp3", "Deep House")
