"""Download specific cover clips via MediaRecorder (full song). 
Usage: python scripts/download_covers.py <clip_id>:<genre> <clip_id>:<genre> ...
Downloads full audio to generated/<hymn>_10x_<genre>_A_cover.mp3
"""
import sys, os, json, time, requests, subprocess, base64, argparse
from playwright.sync_api import sync_playwright

SUNO_BASE = "https://studio-api-prod.suno.com"
GEN_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "generated")

def download_clip(page, clip_id, out_mp3):
    page.goto(f"https://suno.com/song/{clip_id}", wait_until="domcontentloaded", timeout=30000)
    page.wait_for_timeout(8000)
    # get duration
    tok = page.evaluate('async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}')
    hdr = {"Authorization": f"Bearer {tok}"}
    dur = 240
    try:
        r = requests.get(f"{SUNO_BASE}/api/clip/{clip_id}/", headers=hdr, timeout=30)
        if r.status_code == 200:
            d = r.json().get('metadata', {}).get('duration', 240)
            dur = float(d)
    except Exception:
        pass
    record_ms = int((dur + 5) * 1000)
    print(f"    {clip_id[:12]} dur={dur:.0f}s recording {record_ms/1000:.0f}s...")
    # click ONLY the main track play button (aria 'Play' in track area y<500)
    for _ in range(4):
        page.evaluate('''(()=>{var btns=Array.from(document.querySelectorAll('button')).filter(b=>b.offsetParent);var t=btns.find(b=>(b.getAttribute('aria-label')||'').trim()==='Play'&&b.getBoundingClientRect().y<500);if(t){t.click();return 'ok'}return 'nf'})()''')
        page.wait_for_timeout(5000)
        has_blob = page.evaluate("!!Array.from(document.querySelectorAll('audio')).find(e=>(e.currentSrc||'').startsWith('blob:'))")
        if has_blob:
            break
    result = page.evaluate('''async (ms) => {
        const a = Array.from(document.querySelectorAll('audio')).find(e => (e.currentSrc||'').startsWith('blob:'));
        if (!a) return JSON.stringify({err:'no blob'});
        try { a.currentTime = 0; await a.play(); } catch(e) {}
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
        const blob = new Blob(chunks, {type:'audio/webm'});
        const buf = await blob.arrayBuffer();
        const bytes = new Uint8Array(buf);
        let bin = '';
        for (let i = 0; i < bytes.length; i += 0x8000) bin += String.fromCharCode.apply(null, bytes.subarray(i, i+0x8000));
        return JSON.stringify({size:bytes.length, b64: btoa(bin)});
    }''', record_ms)
    try:
        d = json.loads(result)
    except Exception:
        return False
    if 'err' in d:
        print(f"    err: {d['err']}")
        return False
    data = base64.b64decode(d['b64'])
    webm_tmp = out_mp3.replace('.mp3', '.webm')
    with open(webm_tmp, 'wb') as f:
        f.write(data)
    subprocess.run(["ffmpeg", "-y", "-loglevel", "error", "-i", webm_tmp,
                    "-c:a", "libmp3lame", "-b:a", "192k", out_mp3], check=True)
    os.remove(webm_tmp) if os.path.exists(webm_tmp) else None
    return True

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--hymn", default="Jesus_Comes_With_Power")
    ap.add_argument("jobs", nargs="+", help="clip_id:genre pairs")
    args = ap.parse_args()
    os.makedirs(GEN_DIR, exist_ok=True)
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9222")
        page = next((p for p in b.contexts[0].pages if "suno.com" in p.url), None)
        if not page:
            page = b.contexts[0].new_page()
            page.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=30000)
            page.wait_for_timeout(8000)
        for job in args.jobs:
            cid, genre = job.split(":")
            out = os.path.join(GEN_DIR, f"{args.hymn}_10x_{genre}_A_cover.mp3")
            print(f"=== {genre} ({cid[:12]}) ===")
            ok = download_clip(page, cid, out)
            if ok:
                print(f"  saved -> {os.path.basename(out)} ({os.path.getsize(out)//1024}KB)")
            else:
                print(f"  FAILED")
        b.close()
    print("DONE")

if __name__ == "__main__":
    main()
