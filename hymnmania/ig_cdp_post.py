"""Instagram Reel poster — WORKING flow (verified 2026-09-10).

Order matters: Next (crop) -> Next (edit) -> THEN type the caption with keyboard.type
(execCommand is ignored by React) -> Share. Earlier versions clicked Share BEFORE typing
the caption, which closed the composer without publishing anything.

Importable:  post(video_path, caption_file) -> bool
CLI:         python ig_cdp_post.py <video_path> <caption_file>
"""
import sys, os, json, io
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright


def click_text(p, texts, roles="div[role=button],button,span,a"):
    return p.evaluate(
        "(function(ts){"
        "var els=Array.from(document.querySelectorAll('" + roles + "'));"
        "for(var e of els){var t=(e.innerText||'').trim().toLowerCase();"
        "if(ts.includes(t)&&e.offsetParent){e.click();return t}}return 'nf'})(" + json.dumps(texts) + ")"
    )


def post(video_path, caption_file):
    """Post a Reel to Instagram. Returns True if the Share was submitted."""
    video = os.path.abspath(video_path)
    caption = io.open(caption_file, encoding="utf-8").read() if os.path.exists(caption_file) else str(caption_file)

    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        ctx = b.contexts[0]
        p = ctx.new_page()
        p.on("dialog", lambda d: d.accept())
        p.goto("https://www.instagram.com/", wait_until="domcontentloaded", timeout=40000)
        p.wait_for_timeout(7000)

        # 1. New post
        p.evaluate("""(function(){var s=document.querySelector('svg[aria-label="New post"]');
            if(s){(s.closest('[role=button],a')||s.parentElement||s).click();return 'ok'}return 'nf'})()""")
        p.wait_for_timeout(3000)
        # 2. Post
        print("  menu post:", click_text(p, ["post"]))
        p.wait_for_timeout(4000)
        # 3. upload
        n = p.evaluate("document.querySelectorAll('input[type=file]').length")
        if not n:
            print("  NO FILE INPUT")
            b.close()
            return False
        p.set_input_files("input[type=file]", video, timeout=240000)
        print("  file set")
        # 4. wait for processing -> Next
        for i in range(24):
            p.wait_for_timeout(5000)
            body = p.evaluate("document.body.innerText").lower()
            if "next" in body and "processing" not in body:
                break
        # 5. Next twice (crop, edit)
        for step in range(2):
            print(f"  next {step}:", click_text(p, ["next"]))
            p.wait_for_timeout(6000)
        # 6. Caption via keyboard.type (BEFORE Share)
        p.wait_for_timeout(2500)
        focused = p.evaluate("""(function(){var es=Array.from(document.querySelectorAll('[contenteditable=true],textarea,[role=textbox]')).filter(x=>x.offsetParent&&x.tagName!=='BODY');
            var e=es.find(x=>/caption|write/i.test((x.getAttribute('aria-label')||'')+(x.getAttribute('placeholder')||'')))||es[0];
            if(e){e.click();e.focus();return 'focused'}return 'nf'})()""")
        print("  caption editor:", focused)
        p.wait_for_timeout(1200)
        if focused == "focused":
            p.keyboard.type(caption, delay=6)
            p.wait_for_timeout(2500)
        # 7. Share
        r = click_text(p, ["share"])
        print("  share click:", r)
        p.wait_for_timeout(10000)
        b.close()
        return r == "share"


if __name__ == "__main__":
    ok = post(sys.argv[1], sys.argv[2])
    print("RESULT:", ok)
