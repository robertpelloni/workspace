"""Suno DRM download helper — captures playing track via MediaRecorder.

WHY: Suno changed download protection (2026-09-01):
- audio_url now returns https://studio-api.prod.suno.com/api/forbidden
- media_urls m4a (CloudFront) = encrypted blob (no ftyp/mdat); mp3 (cdn1) = 403
- Direct URL fetch fails (403 / CORS / encryption)

WORKING METHOD (verified 2026-09-01):
1. Open the song page in the Suno CDP browser (port 9222)
2. Click the track's play button → audio element src becomes blob:https://suno.com/...
3. AudioContext.createMediaElementSource(audioEl) + MediaRecorder → webm
4. Save webm, ffmpeg to mp3

NOTE: createMediaElementSource can only attach once per page — reload between captures.
Record for (duration + 5s) to capture the full track.

Usage:
    python scripts/suno_download_via_mediarecorder.py <clip_id> [output_mp3]
"""
import os, sys, json, time, base64, subprocess, argparse

from playwright.sync_api import sync_playwright

SUNO_BASE = "https://studio-api-prod.suno.com"


def get_clip_info(page, clip_id):
    """Return media_urls + duration via page-context fetch (has auth)."""
    return json.loads(page.evaluate("""async (cid) => {
        const tok = await Clerk.session.getToken();
        const r = await fetch('https://studio-api-prod.suno.com/api/clip/' + cid + '/', {headers: {Authorization: 'Bearer ' + tok}});
        const j = await r.json();
        return JSON.stringify({
            status: j.status,
            duration: j.metadata && j.metadata.duration,
            title: j.title,
            make_instrumental: j.metadata && j.metadata.make_instrumental,
            media_urls: (j.media_urls || []).map(u => ({content_type: u.content_type, url: u.url}))
        });
    }""", clip_id))


def capture_track(page, clip_id, record_ms=260000):
    """Play the track and capture via MediaRecorder. Returns webm bytes."""
    # Navigate to song page (fresh load resets MediaElementSource)
    page.goto(f"https://suno.com/song/{clip_id}", wait_until="domcontentloaded", timeout=30000)
    page.wait_for_timeout(8000)

    # Click play buttons until blob stream starts
    for attempt in range(3):
        page.evaluate("""(()=>{
            var btns = Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent);
            var cand = btns.filter(b=>(b.getAttribute('aria-label')||'').toLowerCase().includes('play'));
            for(var b of cand) b.click();
        })()""")
        page.wait_for_timeout(5000)
        has_blob = page.evaluate(
            "!!Array.from(document.querySelectorAll('audio')).find(e=>(e.currentSrc||'').startsWith('blob:'))"
        )
        if has_blob:
            break
        print(f"  attempt {attempt}: no blob yet, retrying...")

    result = page.evaluate("""async (ms) => {
        const a = Array.from(document.querySelectorAll('audio')).find(e => (e.currentSrc||'').startsWith('blob:'));
        if (!a) return JSON.stringify({err: 'no blob audio'});
        a.currentTime = 0;
        await a.play();
        const Ctx = window.AudioContext || window.webkitAudioContext;
        const ac = new Ctx();
        const src = ac.createMediaElementSource(a);
        const dest = ac.createMediaStreamDestination();
        src.connect(dest);
        const rec = new MediaRecorder(dest.stream);
        const chunks = [];
        rec.ondataavailable = e => { if (e.data && e.data.size > 0) chunks.push(e.data); };
        rec.start(5000);
        await new Promise(r => setTimeout(r, ms));
        rec.stop();
        await new Promise(r => rec.onstop = r);
        const blob = new Blob(chunks, {type: 'audio/webm'});
        const buf = await blob.arrayBuffer();
        const bytes = new Uint8Array(buf);
        let bin = '';
        for (let i = 0; i < bytes.length; i += 0x8000) bin += String.fromCharCode.apply(null, bytes.subarray(i, i+0x8000));
        return JSON.stringify({size: bytes.length, b64: btoa(bin)});
    }""", record_ms)

    d = json.loads(result)
    if 'err' in d:
        raise RuntimeError(d['err'])
    return base64.b64decode(d['b64'])


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("clip_id", help="Suno clip id")
    ap.add_argument("output", nargs="?", default=None, help="output mp3 path")
    args = ap.parse_args()

    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        page = next((p for p in b.contexts[0].pages if "suno.com" in p.url), None)
        if not page:
            print("No suno.com page found in CDP browser")
            sys.exit(1)

        info = get_clip_info(page, args.clip_id)
        print(f"Clip: {info.get('title')} | status={info.get('status')} | dur={info.get('duration')}s")

        dur = float(info.get('duration') or 240)
        record_ms = int((dur + 5) * 1000)
        print(f"Recording {record_ms/1000:.0f}s...")

        webm = capture_track(page, args.clip_id, record_ms)
        webm_path = args.output.replace(".mp3", ".webm") if args.output else f"generated/{args.clip_id}.webm"
        os.makedirs(os.path.dirname(webm_path) or ".", exist_ok=True)
        with open(webm_path, "wb") as f:
            f.write(webm)
        print(f"Saved webm: {webm_path} ({len(webm)//1024}KB)")

        if args.output:
            subprocess.run(["ffmpeg", "-y", "-loglevel", "error", "-i", webm_path,
                            "-c:a", "libmp3lame", "-b:a", "192k", args.output], check=True)
            print(f"Converted: {args.output} ({os.path.getsize(args.output)//1024}KB)")
        b.close()


if __name__ == "__main__":
    main()
