import sys, json, time, base64, os, subprocess, tempfile
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
from playwright.sync_api import sync_playwright
FFM = r"C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin\ffmpeg.exe"

def centroid(file):
    import numpy as np
    tmp = tempfile.mktemp(suffix=".f32")
    subprocess.run([FFM, "-y", "-loglevel", "error", "-i", file, "-ac", "1", "-ar", "48000", "-f", "f32le", tmp], capture_output=True)
    d = np.frombuffer(open(tmp, "rb").read(), dtype=np.float32)
    os.remove(tmp)
    cents = []
    for i in range(0, len(d) - 2048, 2048):
        spec = np.abs(np.fft.rfft(d[i:i+2048] * np.hanning(2048)))
        fr = np.fft.rfftfreq(2048, 1/48000)
        if spec.sum() > 0:
            cents.append((spec * fr).sum() / spec.sum())
    return round(float(np.mean(cents)), 1) if cents else 0

def check(page, cid, tag):
    try:
        page.goto(f"https://suno.com/song/{cid}", wait_until="load", timeout=30000)
        page.wait_for_timeout(7000)
        page.evaluate("(()=>{var b=Array.from(document.querySelectorAll('button')).find(x=>x.offsetParent&&(x.getAttribute('aria-label')||'').trim()==='Play'&&x.getBoundingClientRect().y<500);if(b){b.click();return 'ok'}return 'nf'})()")
        page.wait_for_timeout(6000)
        js = """async (ms) => {
            const a = Array.from(document.querySelectorAll('audio')).find(e => (e.currentSrc||'').startsWith('blob:'));
            if (!a) return JSON.stringify({err:'no blob'});
            const Ctx = window.AudioContext || window.webkitAudioContext;
            const ac = new Ctx(); await ac.resume();
            const src = ac.createMediaElementSource(a);
            const dest = ac.createMediaStreamDestination();
            src.connect(dest);
            const rec = new MediaRecorder(dest.stream);
            const chunks=[]; rec.ondataavailable = e => { if(e.data&&e.data.size>0) chunks.push(e.data); };
            rec.start(1000);
            await new Promise(r => setTimeout(r, 12000));
            rec.stop(); await new Promise(r => rec.onstop = r);
            const blob = new Blob(chunks,{type:'audio/webm'});
            const ab = await blob.arrayBuffer(); const bytes = new Uint8Array(ab);
            let bin=''; for(let i=0;i<bytes.length;i+=0x8000) bin+=String.fromCharCode.apply(null,bytes.subarray(i,i+0x8000));
            return JSON.stringify({size:bytes.length,b64:btoa(bin)});
        }"""
        res = page.evaluate(js, 12000)
        d = json.loads(res)
        if "err" in d:
            print(f"{tag} ({cid[:10]}): {d['err']}", flush=True)
            return
        with open("qc_tmp.webm", "wb") as f:
            f.write(base64.b64decode(d["b64"]))
        subprocess.run([FFM, "-y", "-loglevel", "error", "-i", "qc_tmp.webm", "-c:a", "libmp3lame", "-b:a", "192k", "qc_tmp.mp3"], check=True)
        c = centroid("qc_tmp.mp3")
        print(f"{tag} ({cid[:10]}): centroid={c} {'FULL' if c>2000 else 'DEGRADED'}", flush=True)
    except Exception as e:
        print(f"{tag} ({cid[:10]}): ERR {str(e)[:50]}", flush=True)

with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp("http://127.0.0.1:9333")
    suno = [p for p in b.contexts[0].pages if "suno.com" in p.url]
    page = suno[0] if suno else b.contexts[0].new_page()
    clips = [
        ("JOTM-A 14:55", "670618df-350e-4938-a3e0-36ca8037e9af"),
        ("JOTM-B 14:55", "d5965570-baee-4971-9779-317625f9adc5"),
        ("JOTM-C 15:20", "4fbc4f6c-0603-4bd3-b73e-e2d8390da226"),
        ("JOTM-D 15:20", "05067f3e-85b7-4f53-a928-9aa481cf7397"),
    ]
    for tag, cid in clips:
        try:
            check(page, cid, tag)
        except Exception:
            pass
        # fresh page for next clip (MediaElementSource can only attach once per page)
        try:
            page.close()
        except Exception:
            pass
        page = b.contexts[0].new_page()
        page.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=25000)
        page.wait_for_timeout(3000)
    b.close()
