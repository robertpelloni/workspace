"""
SUNO COVER GENERATOR — Browser UI approach (v5.5 covers)

Verified working: 2026-07-14. Thy_Word all 5 speeds × all 11 genres = 88 clips.

Flow: Find upload clip → More menu → Remix → Cover → Fill form → Create

CRITICAL IMPLEMENTATION DETAILS:
1. The SONG DESCRIPTION textarea (maxLength=3000) sets gpt_description_prompt,
   NOT the style textarea (maxLength=1000) which does nothing.
2. Must use React fiber depth-3 onChange to update state — native DOM events don't work.
3. Must use page.click() for Create button — page.evaluate() with btn.click() navigates away.
4. Feed API is 0-indexed — page=0 has newest clips, page=1 has older.
5. Poll by ISO timestamp comparison — clips created after create_time are new.

Usage: python suno_cover_remix_options_form_style_submitter.py <genre> <speed_lbl> <hymn_name> [--instrumental|--lyrics]
Output: CLIPS:id1,id2 on stdout
"""

import os
import sys
import time
import requests
from playwright.sync_api import sync_playwright

SUNO_BASE = "https://studio-api-prod.suno.com"

from pipeline_config_central_definitions_genres_speeds import GENRES


def trigger_cover(
    genre_name, speed_lbl, hymn_name, make_instrumental=True, lyrics=None
):
    genre_desc = GENRES.get(genre_name, genre_name)
    try:
        os.makedirs(
            os.path.join(os.path.dirname(__file__), "..", "generated"), exist_ok=True
        )
    except OSError:
        pass

    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        ctx = b.contexts[0]
        page = next((p for p in ctx.pages if "suno.com" in p.url), None)
        if not page:
            page = ctx.new_page()
            page.goto(
                "https://suno.com/create", timeout=30000, wait_until="domcontentloaded"
            )
            time.sleep(5)

        token = page.evaluate(
            "async () => { try { return await Clerk.session.getToken(); } catch(e) { return null; } }"
        )
        if not token:
            print("Error: No auth token", flush=True)
            b.close()
            return None

        hdr = {"Authorization": f"Bearer {token}"}

        # Find upload clip in feed
        print("Locating upload clip...", flush=True)
        upload_clip_id = None
        for _ in range(10):
            time.sleep(3)
            for pg in range(0, 15):
                r = requests.get(
                    f"{SUNO_BASE}/api/feed/?limit=50&page={pg}", headers=hdr, timeout=10
                )
                if r.status_code != 200:
                    break
                for c in (
                    r.json()
                    if isinstance(r.json(), list)
                    else r.json().get("clips", [])
                ):
                    title = (c.get("title", "") or "").lower()
                    if (
                        f"sine_{speed_lbl}" in title
                        and hymn_name.lower().replace(" ", "_") in title
                        and c.get("model_name") in (None, "chirp-chirp", "chirp-upload")
                    ):
                        upload_clip_id = c["id"]
                        break
                if upload_clip_id:
                    break
            if upload_clip_id:
                break

        if not upload_clip_id:
            print("Error: No upload clip found", flush=True)
            b.close()
            return None
        print(f"Upload: {upload_clip_id[:16]}", flush=True)

        # Navigate to song page
        page.goto(
            f"https://suno.com/song/{upload_clip_id}",
            timeout=30000,
            wait_until="domcontentloaded",
        )
        time.sleep(6)

        # More menu -> Remix -> Cover
        print("Opening More menu...", flush=True)
        page.evaluate(
            'document.querySelector("button[aria-label=\\"More menu contents\\"]")?.click()'
        )
        time.sleep(2)
        page.evaluate(
            'Array.from(document.querySelectorAll("button, [role=\\"menuitem\\"]")).find(el=>(el.textContent||"").trim()==="Remix")?.click()'
        )
        time.sleep(2)
        page.evaluate(
            'Array.from(document.querySelectorAll("button, [role=\\"menuitem\\"], span")).find(el=>(el.textContent||"").trim()==="Cover")?.click()'
        )
        # Wait for navigation to /create page
        try:
            page.wait_for_url("**/create**", timeout=15000)
        except Exception:
            pass
        # Wait for cover form to load — must have song description textarea
        try:
            page.wait_for_selector(
                'textarea[maxlength="3000"]', state="visible", timeout=30000
            )
        except Exception:
            print("Warning: song description textarea not found after 30s", flush=True)
        time.sleep(3)

        # Fill SONG DESCRIPTION textarea (maxLen=3000) — this is what sets gpt_description_prompt
        # NOT the style textarea (maxLen=1000) which does nothing
        print(f"Filling song description with: {genre_desc}", flush=True)
        genre_safe = (
            str(genre_desc or "electronic").replace("\\", "\\\\").replace('"', '\\"')
        )
        result = page.evaluate(f"""(() => {{
            var ns = Object.getOwnPropertyDescriptor(window.HTMLTextAreaElement.prototype, 'value').set;
            var t = document.querySelector('textarea[maxlength="3000"]');
            if (!t) return 'no song description textarea';
            ns.call(t, "{genre_safe}");
            // Walk fiber tree to find the actual state setter
            var fiberKey = Object.keys(t).find(k => k.startsWith('__reactFiber'));
            var fiber = t[fiberKey];
            var current = fiber;
            for (var i = 0; i < 8 && current; i++) {{
                if (i >= 3 && current.memoizedProps && typeof current.memoizedProps.onChange === 'function') {{
                    current.memoizedProps.onChange({{ target: t }});
                    return 'called depth' + i + ' onChange, val=' + t.value.slice(0,30);
                }}
                current = current.return;
            }}
            return 'no onChange found in fiber tree';
        }})()""")
        print(f"  {result}", flush=True)
        time.sleep(3)

        # Verify value is still set after delay
        verify = page.evaluate("""() => {
            var t = document.querySelector('textarea[maxlength="3000"]');
            return t ? t.value.slice(0,30) : 'not found';
        }""")
        print(f"  Verified: {verify}", flush=True)

        # Click Create using Playwright click (NOT evaluate - that navigates away)
        print("Create...", flush=True)
        create_time = time.strftime("%Y-%m-%dT%H:%M:%S", time.gmtime())
        page.click('button[aria-label="Create song"]', timeout=15000)
        time.sleep(25)

        # Poll for new clips — timestamp filter only
        print(f"Polling (after {create_time})...", flush=True)
        found = []
        for wait_loop in range(80):
            time.sleep(3)
            for pg in range(0, 6):
                r = requests.get(
                    f"{SUNO_BASE}/api/feed/?limit=50&page={pg}", headers=hdr, timeout=10
                )
                if r.status_code != 200:
                    continue
                for c in (
                    r.json()
                    if isinstance(r.json(), list)
                    else r.json().get("clips", [])
                ):
                    cid = c.get("id")
                    created_str = c.get("created_at", "")
                    if (
                        cid
                        and created_str >= create_time
                        and cid not in [fc["id"] for fc in found]
                    ):
                        found.append(c)
                        gpt = c.get("metadata", {}).get("gpt_description_prompt", "")
                        print(f'  Found: {cid[:12]} gpt="{str(gpt)[:20]}"', flush=True)
            if len(found) >= 2:
                break
            if wait_loop % 5 == 4:
                print(f"  Waiting... ({wait_loop + 1}/80)", flush=True)
        b.close()

    if found:
        print(f"Covers: {[c['id'] for c in found]}", flush=True)
        return [c["id"] for c in found]
    else:
        print("Error: No new clips appeared", flush=True)
        return None


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument("genre")
    parser.add_argument("speed_lbl")
    parser.add_argument("hymn_name")
    parser.add_argument("--lyrics", default=None)
    parser.add_argument("--instrumental", action="store_true")
    args = parser.parse_args()
    clips = trigger_cover(
        args.genre,
        args.speed_lbl,
        args.hymn_name,
        make_instrumental=args.instrumental,
        lyrics=args.lyrics,
    )
    if clips:
        print(f"CLIPS:{','.join(clips)}")
        sys.exit(0)
    sys.exit(1)
