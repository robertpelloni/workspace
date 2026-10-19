"""Robust full capture: cycle pages every ~48s (avoids page-close on long sessions).
Each page captures 4x12s rounds (48s), then a new page seeks to continue.
Usage: python cap_cycle.py <clip_id> <output_mp3>
"""
import sys, json, time, base64, os, subprocess, requests
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright

FFM = r"C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin\ffmpeg.exe"
SUNO = "https://studio-api-prod.suno.com"

def centroid(file):
    import numpy as np, tempfile as _tf
    tmp = _tf.mktemp(suffix=".f32")
    subprocess.run([FFM, "-y", "-loglevel", "error", "-i", file, "-ac", "1", "-ar", "48000", "-f", "f32le", tmp], capture_output=True)
    d = np.frombuffer(open(tmp, "rb").read(), dtype=np.float32)
    os.remove(tmp)
    cents = []
    for i in range(0, len(d) - 2048, 2048):
        sp = np.abs(np.fft.rfft(d[i:i+2048] * np.hanning(2048)))
        fr = np.fft.rfftfreq(2048, 1/48000)
        if sp.sum() > 0:
            cents.append((sp * fr).sum() / sp.sum())
    return round(float(np.mean(cents)), 1) if cents else 0

def _find_blob_js():
    return "(()=>{var a=Array.from(document.querySelectorAll('audio')).find(e=>(e.currentSrc||'').startsWith('blob:'));return a||null})()"


def seek_and_play(page, start_time, tries=25):
    """Ensure blob audio is loaded, seek to start_time, wait until the seek lands.
    Returns the achieved currentTime (or -1 on failure)."""
    # 1) make sure the blob audio element exists (play button starts streaming)
    for _ in range(tries):
        has = page.evaluate("(!!Array.from(document.querySelectorAll('audio')).find(e=>(e.currentSrc||'').startsWith('blob:')))")
        if has:
            break
        page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button')).find(x=>x.offsetParent&&(x.getAttribute('aria-label')||'').trim()==='Play'&&x.getBoundingClientRect().y<500);if(b)b.click()})()")
        page.wait_for_timeout(1000)
    # 2) wait until it is seekable-ish (duration known)
    for _ in range(tries):
        dur = page.evaluate("(()=>{var a=Array.from(document.querySelectorAll('audio')).find(e=>(e.currentSrc||'').startsWith('blob:'));return a?Math.round(a.duration||0):0})()")
        if dur and dur > 0:
            break
        page.wait_for_timeout(1000)
    # 3) seek (clamp to duration-2) and play
    page.evaluate(
        "(()=>{var a=Array.from(document.querySelectorAll('audio')).find(e=>(e.currentSrc||'').startsWith('blob:'));"
        "if(!a)return -1;var t=Math.min(" + str(start_time) + ",Math.max(0,(a.duration||1e9)-2));a.currentTime=t;a.play();return Math.round(a.currentTime)})()"
    )
    # 4) wait for the seek to actually take effect (currentTime lands near target)
    target = start_time
    for _ in range(30):
        page.wait_for_timeout(500)
        ct = page.evaluate("(()=>{var a=Array.from(document.querySelectorAll('audio')).find(e=>(e.currentSrc||'').startsWith('blob:'));return a?Math.round(a.currentTime):-1})()")
        if isinstance(ct, (int, float)) and ct >= max(0, target - 2):
            return ct
    return page.evaluate("(()=>{var a=Array.from(document.querySelectorAll('audio')).find(e=>(e.currentSrc||'').startsWith('blob:'));return a?Math.round(a.currentTime):-1})()")


def capture_page_rounds(b, cid, start_time, n_rounds, round_ms=12000):
    """New page, play clip, seek to start_time, capture n_rounds x round_ms on ONE page."""
    page = b.contexts[0].new_page()
    try:
        page.goto("https://suno.com/song/" + cid, wait_until="load", timeout=40000)
        page.wait_for_timeout(9000)
        # Proper seek: wait for blob, seek, CONFIRM, then record
        achieved = seek_and_play(page, start_time)
        print("  seek -> target " + str(int(start_time)) + "s, actual " + str(achieved) + "s", flush=True)
        page.wait_for_timeout(1000)
        js = """async (opts) => {
            const a = Array.from(document.querySelectorAll('audio')).find(e => (e.currentSrc||'').startsWith('blob:'));
            if (!a) return JSON.stringify({err:'no blob'});
            const Ctx = window.AudioContext || window.webkitAudioContext;
            const ac = new Ctx(); await ac.resume();
            const src = ac.createMediaElementSource(a);
            const dest = ac.createMediaStreamDestination();
            src.connect(dest);
            const out=[];
            for (let r = 0; r < opts.nRounds; r++) {
                const rec = new MediaRecorder(dest.stream);
                const chunks=[]; rec.ondataavailable = e => { if(e.data&&e.data.size>0) chunks.push(e.data); };
                rec.start(500);
                await new Promise(res => setTimeout(res, opts.roundMs));
                rec.stop(); await new Promise(res => rec.onstop = res);
                const blob = new Blob(chunks,{type:'audio/webm'});
                const ab = await blob.arrayBuffer(); const bytes = new Uint8Array(ab);
                let bin=''; for(let i=0;i<bytes.length;i+=0x8000) bin+=String.fromCharCode.apply(null,bytes.subarray(i,i+0x8000));
                out.push({b64: btoa(bin), ct: Math.round(a.currentTime)});
            }
            return JSON.stringify({out});
        }"""
        res = page.evaluate(js, {"nRounds": n_rounds, "roundMs": round_ms})
        d = json.loads(res)
        if "err" in d:
            return [], start_time
        base = achieved if isinstance(achieved, (int, float)) and achieved >= 0 else start_time
        return d["out"], base + n_rounds * (round_ms / 1000)
    except Exception as e:
        print("page err: " + str(e)[:50], flush=True)
        return [], start_time
    finally:
        try:
            page.close()
        except Exception:
            pass

def main():
    cid = sys.argv[1]
    out = sys.argv[2]
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9333")
        # get duration
        page = next((p for p in b.contexts[0].pages if "suno.com" in p.url), None)
        tok = page.evaluate("async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}") if page else None
        if not tok:
            page = b.contexts[0].new_page()
            page.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=30000)
            page.wait_for_timeout(5000)
            tok = page.evaluate("async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}")
        hdr = {"Authorization": "Bearer " + str(tok)}
        md_dur = 196
        try:
            r = requests.get(SUNO + "/api/clip/" + cid + "/", headers=hdr, timeout=20)
            if r.status_code == 200:
                md_dur = r.json().get("metadata", {}).get("duration", 196)
        except Exception:
            pass
        print("target:", md_dur, "s", flush=True)

        all_segs = []
        pos = 0
        rounds_per_page = 4  # 48s per page
        round_ms = 12000
        import math
        while pos < md_dur:
            # never record past the song end (would wrap to 0)
            remaining = md_dur - pos
            nr = min(rounds_per_page, max(1, math.ceil(remaining / (round_ms / 1000.0))))
            print("capturing from " + str(pos) + "s (" + str(nr) + " rounds)...", flush=True)
            segs, new_pos = capture_page_rounds(b, cid, pos, nr)
            for s in segs:
                all_segs.append(s)
                print("  seg at ~" + str(s["ct"]) + "s (" + str(len(s["b64"])//1024) + "KB)", flush=True)
            if not segs:
                # failed - try smaller
                segs2, new_pos2 = capture_page_rounds(b, cid, pos, 2)
                if not segs2:
                    print("  stuck at " + str(pos) + " - moving on", flush=True)
                    pos += 12
                else:
                    all_segs.extend(segs2)
                    pos = new_pos2
            else:
                pos = new_pos
            if pos > md_dur:
                break
            time.sleep(1)
        print("total segments:", len(all_segs), flush=True)
        if len(all_segs) < 3:
            print("too few segments", flush=True)
            b.close()
            return False
        # save + concat
        seg_files = []
        for i, s in enumerate(all_segs):
            sf = f"_cyc_{i}.webm"
            with open(sf, "wb") as f:
                f.write(base64.b64decode(s["b64"]))
            seg_files.append(sf)
        listfile = "_cyc_list.txt"
        with open(listfile, "w") as f:
            for sf in seg_files:
                f.write(f"file '{os.path.abspath(sf)}'\n")
        subprocess.run([FFM, "-y", "-loglevel", "error", "-f", "concat", "-safe", "0", "-i", listfile, "-c:a", "libmp3lame", "-b:a", "192k", "-ar", "48000", "-ac", "1", out], check=True)
        # trim any overshoot past the true song duration (avoids trailing wrap)
        tmp_trim = out + ".trim.mp3"
        subprocess.run([FFM, "-y", "-loglevel", "error", "-i", out, "-t", str(md_dur), "-c:a", "libmp3lame", "-b:a", "192k", tmp_trim], check=True)
        os.replace(tmp_trim, out)
        for sf in seg_files:
            try:
                os.remove(sf)
            except Exception:
                pass
        try:
            os.remove(listfile)
        except Exception:
            pass
        c = centroid(out)
        lc = loop_score(out)
        FFP = os.path.join(os.path.dirname(FFM), "ffprobe.exe")
        r2 = subprocess.run([FFP, "-v", "quiet", "-show_entries", "format=duration", "-of", "csv=p=0", out], capture_output=True, text=True)
        actual = round(float(r2.stdout.strip())) if r2.stdout.strip() else 0
        print("RESULT duration=" + str(actual) + "s centroid=" + str(c) + " loop_check=" + str(lc) + " size=" + str(os.path.getsize(out)//1024) + "KB", flush=True)
        if lc > 0.7:
            print("WARN: loop detected (48s repeat) - capture may be invalid", flush=True)
        b.close()
        return c > 2000 and lc <= 0.7


def loop_score(f):
    """Detect a 48s repeat (the cap_cycle seek bug). >0.7 = looped/broken."""
    import numpy as np
    tmp = os.path.join(os.path.dirname(os.path.abspath(f)), "_loopcheck.f32")
    subprocess.run([FFM, "-y", "-loglevel", "error", "-i", f, "-ac", "1", "-ar", "8000", "-f", "f32le", tmp], capture_output=True)
    try:
        d = np.frombuffer(open(tmp, "rb").read(), dtype=np.float32)
    finally:
        try:
            os.remove(tmp)
        except Exception:
            pass
    bins = []
    for i in range(0, len(d) - 4 * 8000, 4 * 8000):
        w = d[i:i + 4 * 8000]
        sp = np.abs(np.fft.rfft(w * np.hanning(len(w))))
        fr = np.fft.rfftfreq(len(w), 1 / 8000)
        bins.append((sp * fr).sum() / sp.sum() if sp.sum() > 0 else 0)
    b = np.array(bins)
    if len(b) < 36:
        return 0.0
    def cc(x, y):
        x = x - x.mean(); y = y - y.mean()
        s = x.std() * y.std()
        return float((x * y).mean() / s) if s > 1e-9 else 0.0
    # Capture-bug signature: two CONSECUTIVE 48s blocks that are near-identical
    # (>=3 identical blocks total). A single high pair is just genre repetition.
    c = [cc(b[i * 12:(i + 1) * 12], b[(i + 1) * 12:(i + 2) * 12]) for i in range(len(b) // 12 - 1)]
    worst = 0.0
    for i in range(len(c) - 1):
        if c[i] > 0.9 and c[i + 1] > 0.9:
            worst = max(worst, min(c[i], c[i + 1]))
    return round(worst, 3)

if __name__ == "__main__":
    ok = main()
    print("SUCCESS: " + str(ok))
