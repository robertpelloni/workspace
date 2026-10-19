"""Capture a full track in 12s segments, each on a fresh page (reliable).
Usage: python cap_segs_simple.py <clip_id> <output_mp3>
"""
import sys, json, time, base64, os, subprocess, requests
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright
FFM = r"C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin\ffmpeg.exe"

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
        # get token + duration from an existing suno page without navigating
        page = next((p for p in b.contexts[0].pages if "suno.com" in p.url), None)
        tok = None
        if page:
            tok = page.evaluate("async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}")
        if not tok:
            p2 = b.contexts[0].new_page()
            p2.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=30000)
            p2.wait_for_timeout(5000)
            tok = p2.evaluate("async()=>{try{return await Clerk.session.getToken()}catch(e){return null}}")
            p2.close()
        hdr = {"Authorization": "Bearer " + str(tok)}
        md_dur = 240
        try:
            r = requests.get("https://studio-api-prod.suno.com/api/clip/" + cid + "/", headers=hdr, timeout=20)
            if r.status_code == 200:
                md_dur = r.json().get("metadata", {}).get("duration", 240)
        except Exception:
            pass
        print("duration:", md_dur, flush=True)
        # capture 12s segments every 12s
        seg_files = []
        for pos in range(0, int(md_dur), 12):
            # fresh page each segment
            pg = b.contexts[0].new_page()
            try:
                pg.goto("https://suno.com/song/" + cid, wait_until="load", timeout=30000)
                pg.wait_for_timeout(8000)
                # seek audio to pos then play
                pg.evaluate("(()=>{var a=Array.from(document.querySelectorAll('audio')).find(e=>(e.currentSrc||'').startsWith('blob:'));if(a){a.currentTime=" + str(pos) + ";a.play();return 'ok'}var b=Array.from(document.querySelectorAll('button')).find(x=>x.offsetParent&&(x.getAttribute('aria-label')||'').trim()==='Play'&&x.getBoundingClientRect().y<500);if(b){b.click();return 'clicked'}return 'nf'})()")
                pg.wait_for_timeout(5000)
                js = """async (ms) => {
                    const a = Array.from(document.querySelectorAll('audio')).find(e => (e.currentSrc||'').startsWith('blob:')) || document.querySelector('audio');
                    if (!a) return JSON.stringify({err:'no blob'});
                    const Ctx = window.AudioContext || window.webkitAudioContext;
                    const ac = new Ctx(); await ac.resume();
                    const src = ac.createMediaElementSource(a);
                    const dest = ac.createMediaStreamDestination();
                    src.connect(dest);
                    const rec = new MediaRecorder(dest.stream);
                    const chunks=[]; rec.ondataavailable = e => { if(e.data&&e.data.size>0) chunks.push(e.data); };
                    rec.start(1000);
                    await new Promise(r => setTimeout(r, ms));
                    rec.stop(); await new Promise(r => rec.onstop = r);
                    const blob = new Blob(chunks,{type:'audio/webm'});
                    const ab = await blob.arrayBuffer(); const bytes = new Uint8Array(ab);
                    let bin=''; for(let i=0;i<bytes.length;i+=0x8000) bin+=String.fromCharCode.apply(null,bytes.subarray(i,i+0x8000));
                    return JSON.stringify({size:bytes.length,b64:btoa(bin)});
                }"""
                res = pg.evaluate(js, 12000)
                d = json.loads(res)
                if "err" not in d:
                    sf = f"_seg_{pos}.webm"
                    with open(sf, "wb") as f:
                        f.write(base64.b64decode(d["b64"]))
                    seg_files.append(sf)
                    print("seg " + str(pos) + "s ok", flush=True)
                else:
                    print("seg " + str(pos) + " err: " + d["err"], flush=True)
            except Exception as e:
                print("seg " + str(pos) + " ex: " + str(e)[:50], flush=True)
            try:
                pg.close()
            except Exception:
                pass
            time.sleep(1)
        print("segments:", len(seg_files), flush=True)
        if len(seg_files) >= 3:
            listfile = "_seglist.txt"
            with open(listfile, "w") as f:
                for sf in seg_files:
                    f.write(f"file '{os.path.abspath(sf)}'\n")
            tmpw = out.replace(".mp3", "_c.webm")
            subprocess.run([FFM, "-y", "-loglevel", "error", "-f", "concat", "-safe", "0", "-i", listfile, "-c", "copy", tmpw], check=True)
            subprocess.run([FFM, "-y", "-loglevel", "error", "-i", tmpw, "-c:a", "libmp3lame", "-b:a", "192k", out], check=True)
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
            print("RESULT centroid=" + str(c) + " size=" + str(os.path.getsize(out)//1024) + "KB", flush=True)
        b.close()

if __name__ == "__main__":
    main()
