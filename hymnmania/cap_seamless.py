"""Full seamless capture — consecutive 12s MediaRecorder rounds on ONE page.
Each round captures the next 12s of continuous playback (no gaps).
Usage: python cap_seamless.py <clip_id> <output_mp3>
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

def main():
    cid = sys.argv[1]
    out = sys.argv[2]
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp("http://127.0.0.1:9333")
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
        print("target duration:", md_dur, flush=True)

        # ONE page, navigate to clip, play
        cap_page = b.contexts[0].new_page()
        cap_page.goto("https://suno.com/song/" + cid, wait_until="load", timeout=40000)
        cap_page.wait_for_timeout(10000)
        cap_page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button')).find(x=>x.offsetParent&&(x.getAttribute('aria-label')||'').trim()==='Play'&&x.getBoundingClientRect().y<500);if(b){b.click();return 'ok'}return 'nf'})()")
        cap_page.wait_for_timeout(7000)

        # Capture rounds on ONE page (12s each, sequential)
        n_rounds = int(md_dur // 12) + 1
        js = """async (nRounds, roundMs) => {
            const a = Array.from(document.querySelectorAll('audio')).find(e => (e.currentSrc||'').startsWith('blob:'));
            if (!a) return JSON.stringify({err:'no blob'});
            const Ctx = window.AudioContext || window.webkitAudioContext;
            const ac = new Ctx(); await ac.resume();
            const src = ac.createMediaElementSource(a);
            const dest = ac.createMediaStreamDestination();
            src.connect(dest);
            const results = [];
            for (let round = 0; round < nRounds; round++) {
                const rec = new MediaRecorder(dest.stream);
                const chunks=[]; rec.ondataavailable = e => { if(e.data&&e.data.size>0) chunks.push(e.data); };
                rec.start(1000);
                await new Promise(r => setTimeout(r, roundMs));
                rec.stop(); await new Promise(r => rec.onstop = r);
                const blob = new Blob(chunks,{type:'audio/webm'});
                const ab = await blob.arrayBuffer(); const bytes = new Uint8Array(ab);
                let bin=''; for(let i=0;i<bytes.length;i+=0x8000) bin+=String.fromCharCode.apply(null,bytes.subarray(i,i+0x8000));
                results.push({round, ct: Math.round(a.currentTime), size: bytes.length, b64: btoa(bin)});
            }
            return JSON.stringify({results});
        }"""
        res = cap_page.evaluate(js, {"nRounds": n_rounds, "roundMs": 12000})
        d = json.loads(res)
        if "err" in d:
            print("capture err:", d["err"], flush=True)
            b.close()
            return False
        results = d["results"]
        print("rounds captured:", len(results), flush=True)
        seg_files = []
        for r in results:
            sf = f"_seam_{r['round']}.webm"
            with open(sf, "wb") as f:
                f.write(base64.b64decode(r["b64"]))
            seg_files.append(sf)
        # concat
        listfile = "_seamlist.txt"
        with open(listfile, "w") as f:
            for sf in seg_files:
                f.write(f"file '{os.path.abspath(sf)}'\n")
        tmpw = out.replace(".mp3", "_c.webm")
        # re-encode concat (webm segments don't stream-copy cleanly)
        subprocess.run([FFM, "-y", "-loglevel", "error", "-f", "concat", "-safe", "0", "-i", listfile, "-c:a", "libmp3lame", "-b:a", "192k", "-ar", "48000", "-ac", "1", out], check=True)
        for sf in seg_files:
            try:
                os.remove(sf)
            except Exception:
                pass
        try:
            os.remove(tmpw)
            os.remove(listfile)
        except Exception:
            pass
        c = centroid(out)
        r2 = subprocess.run([FFM.replace("ffmpeg", "ffprobe"), "-v", "quiet", "-show_entries", "format=duration", "-of", "csv=p=0", out], capture_output=True, text=True)
        actual = round(float(r2.stdout.strip())) if r2.stdout.strip() else 0
        ok = "FULL-OK" if c > 2000 and actual >= md_dur - 3 else ("PARTIAL " + str(actual) + "s" if c > 2000 else "DEGRADED")
        print("RESULT duration=" + str(actual) + "s centroid=" + str(c) + " " + ok + " size=" + str(os.path.getsize(out)//1024) + "KB", flush=True)
        b.close()
        return c > 2000

if __name__ == "__main__":
    ok = main()
    print("SUCCESS: " + str(ok))
