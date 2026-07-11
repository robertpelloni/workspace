from playwright.sync_api import sync_playwright, expect
import time

def verify_midi_ui():
    with sync_playwright() as p:
        browser = p.chromium.launch(headless=True)
        page = browser.new_page()

        # 1. Navigate to the app
        page.goto("http://localhost:8501")

        # 2. Wait for app to load
        page.wait_for_selector("text=Hymn Remaker Pipeline")

        # 3. Click on the Live Psy-Mono Studio tab
        page.click("text=Live Psy-Mono Studio")

        # 4. Verify "External MIDI Control" section
        expect(page.get_by_text("External MIDI Control")).to_be_visible()

        # 5. Verify dropdowns
        expect(page.get_by_text("MIDI Input (Hardware/Controller)")).to_be_visible()
        expect(page.get_by_text("MIDI Output (External VST/Synth)")).to_be_visible()

        # 6. Scroll down to PANIC
        panic_btn = page.get_by_text("🚨 PANIC (Stop All)")
        panic_btn.scroll_into_view_if_needed()
        time.sleep(2)
        # 7. Take screenshot
        page.screenshot(path="/home/jules/verification/v135_panic_ui.png")

        browser.close()

if __name__ == "__main__":
    # Wait a bit for streamlit to start
    time.sleep(10)
    verify_midi_ui()
