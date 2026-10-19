import os
import sys
import argparse
from playwright.sync_api import sync_playwright

def inject_file(audio_path):
    if not os.path.exists(audio_path):
        print(f"File not found: {audio_path}")
        return False

    print("Connecting over CDP to inject file...")
    try:
        with sync_playwright() as pw:
            b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
            pp = next((page for page in b.contexts[0].pages if "suno.com" in page.url), None)
            if pp:
                if "/create" not in pp.url:
                    print("Page not at /create. Navigating to suno.com/create...")
                    pp.goto("https://suno.com/create", wait_until="load", timeout=20000)
                    pp.wait_for_timeout(3000) # extra buffer
                with pp.expect_file_chooser(timeout=15000) as fc_info:
                    pp.evaluate("document.querySelector('input[type=file]')?.click()")
                fc_info.value.set_files(audio_path)
                print(f"Successfully injected file: {audio_path}")
                b.close()
                return True
            else:
                print("Suno tab not found in active browser contexts.")
                b.close()
    except Exception as e:
        print(f"CDP injection error: {e}")
    return False

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--audio", required=True)
    args = parser.parse_args()
    success = inject_file(args.audio)
    sys.exit(0 if success else 1)

if __name__ == "__main__":
    main()
