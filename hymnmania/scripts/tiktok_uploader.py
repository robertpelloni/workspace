"""
TikTok Uploader via Browser Automation
=======================================
Uploads videos to TikTok using Playwright browser automation.

Usage:
    python tiktok_uploader.py --video generated/video_vertical.mp4 --title "Title" --tags "tag1,tag2"

TikTok Content Requirements:
- Format: MP4, MOV, WebM (H.264 video + AAC audio)
- Aspect Ratio: 9:16 (1080x1920) vertical preferred
- Duration: 3 seconds to 10 minutes (API) / 60 minutes (web)
- AI Content: Must set is_aigc=true flag
- Links: NOT clickable in captions (bio link only)
"""
import os
import time
import argparse

ROOT = os.path.dirname(os.path.abspath(__file__))
STATE_FILE = os.path.join(ROOT, "..", ".tiktok_state.json")


def build_caption(title, tags=None, description=None):
    """Build TikTok caption with hashtags."""
    parts = [title]
    if description:
        parts.append(description)
    
    default_tags = [
        "#ResurrectingBeats", "#Hymnmania", "#ElectronicMusic",
        "#ChristianMusic", "#Worship", "#Remix", "#AIMusic",
        "#HymnRemix", "#ElectronicWorship", "#2026"
    ]
    
    if tags:
        tag_list = [f"#{t.strip().replace(' ', '')}" for t in tags.split(",")]
    else:
        tag_list = default_tags
    
    caption = " ".join(parts) + "\n\n" + " ".join(tag_list)
    return caption[:2200]


def upload_via_playwright(video_path, caption, is_aigc=True, privacy="PUBLIC_TO_EVERYONE"):
    """Upload video to TikTok using Playwright browser automation."""
    try:
        from playwright.sync_api import sync_playwright
    except ImportError:
        print("ERROR: playwright not installed")
        return False
    
    if not os.path.exists(video_path):
        print(f"ERROR: Video not found: {video_path}")
        return False
    
    video_abs = os.path.abspath(video_path)
    
    with sync_playwright() as p:
        browser_args = ["--disable-blink-features=AutomationControlled"]
        
        if os.path.exists(STATE_FILE):
            browser = p.chromium.launch(headless=False, args=browser_args)
            context = browser.new_context(
                storage_state=STATE_FILE,
                user_agent="Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/126.0.0.0 Safari/537.36",
                viewport={"width": 1280, "height": 800}
            )
        else:
            browser = p.chromium.launch(headless=False, args=browser_args)
            context = browser.new_context(
                user_agent="Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/126.0.0.0 Safari/537.36",
                viewport={"width": 1280, "height": 800}
            )
        
        page = context.new_page()
        
        print("Opening TikTok upload page...")
        page.goto("https://www.tiktok.com/creator#/upload?scene=creator_center",
                  timeout=30000, wait_until="domcontentloaded")
        time.sleep(5)
        
        if "login" in page.url.lower() or "signup" in page.url.lower():
            print("Not logged in. Please log in to TikTok manually.")
            print("After logging in, press Enter to continue...")
            input()
            page.goto("https://www.tiktok.com/creator#/upload?scene=creator_center",
                      timeout=30000, wait_until="domcontentloaded")
            time.sleep(5)
        
        context.storage_state(path=STATE_FILE)
        
        print(f"Uploading: {os.path.basename(video_path)}...")
        file_input = page.locator("input[type='file']").first
        if file_input:
            file_input.set_input_files(video_abs)
            print("Video file selected")
        else:
            print("ERROR: Could not find file input")
            browser.close()
            return False
        
        print("Waiting for video to process...")
        time.sleep(15)
        
        print("Filling caption...")
        caption_input = page.locator("[data-text='true'], public-DraftEditor-content, [role='textbox']").first
        if caption_input:
            caption_input.click()
            time.sleep(1)
            page.keyboard.press("Control+a")
            page.keyboard.type(caption[:2200], delay=10)
            print("Caption filled")
        
        if is_aigc:
            try:
                aigc_toggle = page.get_by_text("AI-generated content", exact=False)
                if aigc_toggle.is_visible():
                    aigc_toggle.click()
                    print("AIGC flag set")
            except Exception:
                pass
        
        time.sleep(5)
        
        print("Publishing...")
        try:
            post_btn = page.get_by_role("button", name="Post")
            if post_btn.is_visible():
                post_btn.click()
                print("Clicked Post button")
                time.sleep(10)
                page.screenshot(path=os.path.join(ROOT, "..", "tiktok_upload_result.png"))
                print("Upload complete!")
                context.storage_state(path=STATE_FILE)
                browser.close()
                return True
        except Exception as e:
            print(f"Error clicking Post: {e}")
        
        page.screenshot(path=os.path.join(ROOT, "..", "tiktok_debug.png"))
        browser.close()
        return False


def main():
    parser = argparse.ArgumentParser(description="TikTok Video Uploader")
    parser.add_argument("--video", required=True, help="Video to upload")
    parser.add_argument("--title", help="Video title/caption")
    parser.add_argument("--tags", help="Comma-separated hashtags")
    parser.add_argument("--description", help="Video description")
    parser.add_argument("--aigc", action="store_true", default=True, help="Mark as AI-generated")
    parser.add_argument("--privacy", default="PUBLIC_TO_EVERYONE")
    args = parser.parse_args()
    
    title = args.title or os.path.basename(args.video).replace(".mp4", "").replace("_", " ")
    caption = build_caption(title, args.tags, args.description)
    
    print(f"Uploading: {title}")
    print(f"Caption: {caption}")
    
    ok = upload_via_playwright(args.video, caption, args.aigc, args.privacy)
    print(f"Result: {'SUCCESS' if ok else 'FAILED'}")


if __name__ == "__main__":
    main()
