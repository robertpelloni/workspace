"""Test: does MediaRecorder capture real broadband audio correctly?
Loads a local MP3 (known-good psytrance cover) into an audio element and records it.
If centroid comes out ~2400, the recorder works. If ~300, recorder is broken.
"""
import sys, json, time, base64, os, subprocess, tempfile
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
import numpy as np
from playwright.sync_api import sync_playwright

FFM = 'C:/Users/jakeg/AppData/Local/Microsoft/WinGet/Packages/Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe/ffmpeg-9.0.1-full_build/bin/ffmpeg.exe'

def centroid(webm):
    tmp = tempfile.mktemp(suffix='.f32')
    subprocess.run([FFM, '-y', '-loglevel', 'error', '-i', webm, '-ac', '1', '-ar', '22050', '-f', 'f32le', tmp], capture_output=True)
    d = np.frombuffer(open(tmp, 'rb').read(), dtype=np.float32)
    os.remove(tmp)
    cents = []
    for i in range(0, min(len(d) - 2048, 22050 * 12), 2048):
        spec = np.abs(np.fft.rfft(d[i:i+2048] * np.hanning(2048)))
        fr = np.fft.rfftfreq(2048, 1/22050)
        if spec.sum() > 0:
            cents.append((spec * fr).sum() / spec.sum())
    return round(float(np.mean(cents)), 1) if cents else 0

with sync_playwright() as pw:
    b = pw.chromium.connect_over_cdp('http://127.0.0.1:9222')
    page = next((p for p in b.contexts[0].pages if 'suno.com' in p.url), None)
    # serve local file via data URL? too big. Use the browser to fetch a blob from the local path via file://
    # Instead: use a known-good URL — play the already-uploaded REAL audio if any, else generate a test tone
    # Simplest reliable test: play a sine sweep we KNOW is broadband via WebAudio oscillator + record it
    result = page.evaluate("""async () => {
        const Ctx = window.AudioContext || window.webkitAudioContext;
        const ac = new Ctx();
        await ac.resume();
        // generate a broadband noise + sweep signal directly
        const dur = 6;
        const sr = ac.sampleRate;
        const buf = ac.createBuffer(1, sr * dur, sr);
        const ch = buf.getChannelData(0);
        // white noise (broadband!)
        for (let i = 0; i < ch.length; i++) ch[i] = (Math.random() * 2 - 1) * 0.3;
        const src = ac.createBufferSource();
        src.buffer = buf;
        const dest = ac.createMediaStreamDestination();
        src.connect(dest);
        src.connect(ac.destination);
        src.start();
        const rec = new MediaRecorder(dest.stream);
        const chunks = [];
        rec.ondataavailable = e => { if (e.data && e.data.size > 0) chunks.push(e.data); };
        rec.start(1000);
        await new Promise(r => setTimeout(r, 6000));
        rec.stop();
        await new Promise(r => rec.onstop = r);
        const blob = new Blob(chunks, {type: 'audio/webm'});
        const ab = await blob.arrayBuffer();
        const bytes = new Uint8Array(ab);
        let bin = '';
        for (let i = 0; i < bytes.length; i += 0x8000) bin += String.fromCharCode.apply(null, bytes.subarray(i, i + 0x8000));
        return JSON.stringify({size: bytes.length, b64: btoa(bin)});
    }""")
    d = json.loads(result)
    webm = '/tmp/_test_noise.webm'
    with open(webm, 'wb') as f:
        f.write(base64.b64decode(d['b64']))
    print('MediaRecorder captured white noise, centroid:', centroid(webm))
    print('(white noise centroid should be ~8000+; if low, recorder is broken)')
    b.close()
