"""Enhanced beat video composer with crossfade, end screens, and audio-reactive overlay."""
import subprocess, os, random, json, time, math

CLIPS = [f for f in os.listdir("pipeline_output/magnific_videos") if f.endswith((".mp4", ".webm", ".mov"))]
CLIP_DIR = os.path.abspath("pipeline_output/magnific_videos")
OUT_DIR = os.path.abspath("pipeline_output/beat_videos")

GENRE_STYLES = {
    "Psytrance": {"color": "white@0.9", "border": "purple@0.8", "hex": "#9933FF"},
    "Deep House": {"color": "gold@0.9", "border": "darkblue@0.6", "hex": "#FFD700"},
    "Dubstep": {"color": "red@0.9", "border": "black@0.8", "hex": "#FF2222"},
    "Drum and Bass": {"color": "cyan@0.9", "border": "navy@0.7", "hex": "#00CCFF"},
    "Chiptune": {"color": "#00FF00@0.9", "border": "#003300@0.8", "hex": "#00FF00"},
    "Gabba": {"color": "orange@0.9", "border": "darkred@0.8", "hex": "#FF6600"},
    "Detroit Techno": {"color": "silver@0.9", "border": "#222222@0.8", "hex": "#CCCCCC"},
    "Detroit House": {"color": "#FFD700@0.9", "border": "#8B4513@0.7", "hex": "#FFD700"},
    "Hardstyle Trance": {"color": "yellow@0.9", "border": "orange@0.7", "hex": "#FFFF00"},
    "Synthwave": {"color": "#FF00FF@0.9", "border": "#000066@0.8", "hex": "#FF00FF"},
    "Japanese Hardcore Techno": {"color": "cyan@0.9", "border": "magenta@0.7", "hex": "#00FFFF"},
}

def get_duration(fpath):
    r = subprocess.run(["ffprobe", "-v", "quiet", "-show_entries", "format=duration",
        "-of", "csv=p=0", fpath], capture_output=True, text=True)
    return float(r.stdout.strip())

def get_resolution(fpath):
    r = subprocess.run(["ffprobe", "-v", "quiet", "-select_streams", "v:0",
        "-show_entries", "stream=width,height", "-of", "csv=s=x:p=0", fpath],
        capture_output=True, text=True)
    w, h = r.stdout.strip().split("x")
    return int(w), int(h)

def make_intro(duration=2.5, genre="Psytrance"):
    style = GENRE_STYLES.get(genre, GENRE_STYLES["Psytrance"])
    out = os.path.join(OUT_DIR, f"_intro_{os.getpid()}_{random.randint(1000,9999)}.mp4")
    bg = random.choice(CLIPS)
    bg_path = os.path.join(CLIP_DIR, bg)
    bg_dur = get_duration(bg_path)
    bg_start = random.uniform(0, max(0.1, bg_dur - duration))
    cmd = [
        "ffmpeg", "-y", "-loglevel", "error",
        "-ss", str(bg_start), "-i", bg_path, "-t", str(duration),
        "-vf", f"scale=1280:720:force_original_aspect_ratio=increase,crop=1280:720,drawtext=text='RESURRECTING':fontcolor={style['color']}:fontsize=48:fontfile=/Windows/Fonts/impact.ttf:x=(w-text_w)/2:y=(h/2-text_h-10):bordercolor={style['border']}:borderw=3,drawtext=text='BEATS':fontcolor={style['color']}:fontsize=56:fontfile=/Windows/Fonts/impact.ttf:x=(w-text_w)/2:y=(h/2+10):bordercolor={style['border']}:borderw=3,drawtext=text='{genre}':fontcolor=white@0.6:fontsize=24:fontfile=/Windows/Fonts/tahoma.ttf:x=(w-text_w)/2:y=(h/2+70)",
        "-c:v", "libx264", "-preset", "ultrafast", "-pix_fmt", "yuv420p", "-an", out
    ]
    try:
        subprocess.run(cmd, check=True, capture_output=True)
        if os.path.exists(out) and os.path.getsize(out) > 10000: return out
    except: pass
    return None

def make_outro(duration=3.0, genre="Psytrance"):
    style = GENRE_STYLES.get(genre, GENRE_STYLES["Psytrance"])
    out = os.path.join(OUT_DIR, f"_outro_{os.getpid()}_{random.randint(1000,9999)}.mp4")
    bg = random.choice(CLIPS)
    bg_path = os.path.join(CLIP_DIR, bg)
    bg_dur = get_duration(bg_path)
    bg_start = random.uniform(0, max(0.1, bg_dur - duration))
    cmd = [
        "ffmpeg", "-y", "-loglevel", "error",
        "-ss", str(bg_start), "-i", bg_path, "-t", str(duration),
        "-vf", f"scale=1280:720:force_original_aspect_ratio=increase,crop=1280:720,drawtext=text='RESURRECTING':fontcolor={style['color']}:fontsize=42:fontfile=/Windows/Fonts/impact.ttf:x=(w-text_w)/2:y=(h/2-text_h-15):bordercolor={style['border']}:borderw=3,drawtext=text='BEATS':fontcolor={style['color']}:fontsize=48:fontfile=/Windows/Fonts/impact.ttf:x=(w-text_w)/2:y=(h/2+10):bordercolor={style['border']}:borderw=3,drawtext=text='Subscribe for more!':fontcolor=white@0.7:fontsize=20:fontfile=/Windows/Fonts/tahoma.ttf:x=(w-text_w)/2:y=(h/2+65),fade=t=out:st=2.5:d=0.5",
        "-c:v", "libx264", "-preset", "ultrafast", "-pix_fmt", "yuv420p", "-an", out
    ]
    try:
        subprocess.run(cmd, check=True, capture_output=True)
        if os.path.exists(out) and os.path.getsize(out) > 10000: return out
    except: pass
    return None

def generate_thumbnail(video_path, hymn, genre, out_name):
    """Generate custom thumbnail with genre + hymn title overlay."""
    out = os.path.join(OUT_DIR, f"{out_name}_thumb.jpg")
    if os.path.exists(out): return out
    
    style = GENRE_STYLES.get(genre, GENRE_STYLES["Psytrance"])
    
    # Extract a frame from 1/3 into the video for the best visual
    dur = get_duration(video_path)
    thumb_time = dur * 0.33
    
    cmd = [
        "ffmpeg", "-y", "-loglevel", "error",
        "-ss", str(thumb_time), "-i", video_path,
        "-vframes", "1",
        "-vf", f"drawtext=text='{genre}':fontcolor={style['color']}:fontsize=36:fontfile=/Windows/Fonts/impact.ttf:x=20:y=20:bordercolor={style['border']}:borderw=3,drawtext=text='{hymn}':fontcolor=white@0.9:fontsize=28:fontfile=/Windows/Fonts/impact.ttf:x=20:y=65:bordercolor=black@0.7:borderw=2,drawtext=text='RESURRECTING BEATS':fontcolor={style['color']}:fontsize=24:fontfile=/Windows/Fonts/impact.ttf:x=w-text_w-20:y=20:bordercolor={style['border']}:borderw=2",
        out
    ]
    try:
        subprocess.run(cmd, check=True, capture_output=True)
        if os.path.exists(out): return out
    except: pass
    return None

def compose(audio_fp, hymn, genre_tag, add_branding=True, force=False):
    """force=True rebuilds even if the output already exists.

    NOTE (2026-09-15): this used to silently return the existing file, which meant a
    REGENERATED cover (e.g. tempo-corrected psytrance) never produced a new beat video -
    the stale one kept the old audio. Always pass force=True when the source changed.
    """
    base = os.path.splitext(os.path.basename(audio_fp))[0]
    out_fp = os.path.join(OUT_DIR, f"{base}_beatsynced.mp4")
    if os.path.exists(out_fp) and not force:
        return out_fp
    if force and os.path.exists(out_fp):
        try:
            os.remove(out_fp)
        except Exception:
            pass
    
    # Use ffprobe/ffmpeg duration (librosa mis-reads VBR MP3s from Suno)
    audio_dur = get_duration(audio_fp)
    
    try:
        import librosa
        import numpy as np
        y, sr = librosa.load(audio_fp, sr=22050)
        tempo, _ = librosa.beat.beat_track(y=y, sr=sr)
        if isinstance(tempo, (list,)): tempo = tempo[0]
        tempo = float(np.asarray(tempo).ravel()[0])
        tempo = max(60, min(200, tempo))
    except:
        tempo = 130
    
    beat_dur = 60.0 / tempo
    if tempo >= 160: beats_per_phrase = 16
    elif tempo >= 130: beats_per_phrase = 12
    elif tempo >= 100: beats_per_phrase = 8
    else: beats_per_phrase = 4
    cut_dur = beats_per_phrase * beat_dur
    n_cuts = max(5, int(audio_dur / cut_dur))
    cut_dur = audio_dur / n_cuts
    
    genre = "Psytrance"
    for g in GENRE_STYLES:
        if g.lower() in genre_tag.lower():
            genre = g
            break
    
    # Sample clips with replacement to ensure enough video for full song length
    # (loops clips when song is longer than available clip material)
    chosen = random.choices(CLIPS, k=n_cuts + 8)
    
    segments = []
    for i, clip in enumerate(chosen):
        cp = os.path.join(CLIP_DIR, clip)
        seg = os.path.join(OUT_DIR, f"_seg_{i}_{os.getpid()}.mp4")
        try:
            cdur = get_duration(cp)
            # Clamp start so it's always valid
            max_start = max(0.0, cdur - cut_dur)
            start = random.uniform(0, max_start) if max_start > 0.5 else 0.0
            # Loop the clip so each segment is EXACTLY cut_dur (guarantees full-length)
            subprocess.run(["ffmpeg", "-y", "-loglevel", "error",
                "-stream_loop", "-1", "-ss", str(start), "-i", cp,
                "-t", str(cut_dur),
                "-vf", "scale=1280:720:force_original_aspect_ratio=increase,crop=1280:720",
                "-c:v", "libx264", "-preset", "ultrafast", "-pix_fmt", "yuv420p", seg], check=True)
            segments.append(seg)
        except: continue
    
    if len(segments) < 2: return None
    
    # === SIMPLE CONCAT (reliable full-length) ===
    inputs_list = []
    if add_branding:
        intro = make_intro(2.5, genre)
        outro = make_outro(3.0, genre)
        if intro: inputs_list.append(intro)
    inputs_list.extend(segments)
    if add_branding and outro: inputs_list.append(outro)
    
    seg_list = os.path.join(OUT_DIR, f"_list_{os.getpid()}.txt")
    with open(seg_list, "w") as f:
        for s in inputs_list:
            f.write(f"file '{os.path.abspath(s)}'\n")
    
    # Delay audio to account for intro branding
    audio_out = os.path.join(OUT_DIR, f"_audio_{os.getpid()}.aac")
    audio_delay = 2500 if add_branding else 0
    subprocess.run(["ffmpeg", "-y", "-loglevel", "error", "-i", audio_fp,
        "-af", f"adelay={audio_delay}|{audio_delay}", "-c:a", "aac", "-b:a", "192k", audio_out], check=True)
    
    # Concat video + full audio with audio-reactive waveform overlay
    style = GENRE_STYLES.get(genre, GENRE_STYLES["Psytrance"])
    wave_color = style.get("hex", "#9933FF")
    
    cmd = ["ffmpeg", "-y", "-loglevel", "error", "-f", "concat", "-safe", "0", "-i", seg_list,
        "-i", audio_out,
        "-filter_complex",
        f"[0:v]scale=1280:720,format=yuv420p[v];[1:a]showwaves=s=1280x120:mode=cline:colors={wave_color}@0.55:rate=30[wave];[v][wave]overlay=x=0:y=H-120[vout]",
        "-map", "[vout]", "-map", "1:a",
        "-c:v", "libx264", "-preset", "medium", "-pix_fmt", "yuv420p",
        "-c:a", "aac", "-b:a", "192k", "-shortest", out_fp]
    
    subprocess.run(cmd, check=True)
    
    # Generate custom thumbnail
    thumbnail = generate_thumbnail(out_fp, hymn, genre, base)
    if thumbnail:
        # Set as YouTube thumbnail via API later
        pass
    
    # Cleanup
    cleanup = segments + [seg_list, audio_out]
    for s in cleanup:
        try: os.remove(s)
        except: pass
    
    sz = os.path.getsize(out_fp)//1024//1024
    print(f"  {hymn[:20]} - {genre_tag[:30]:30s} {sz:4d}MB")
    return out_fp

if __name__ == "__main__":
    import sys
    audio = sys.argv[1] if len(sys.argv) > 1 else None
    hymn = sys.argv[2] if len(sys.argv) > 2 else "Track"
    genre = sys.argv[3] if len(sys.argv) > 3 else "Electronic"
    if audio:
        compose(audio, hymn, genre)
