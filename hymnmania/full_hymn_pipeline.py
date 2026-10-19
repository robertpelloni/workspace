#!/usr/bin/env python3
"""
FULL HYMNMANIA PIPELINE: Top 15 Hymns × All Genres × All Speeds
================================================================

Generates audio + beat-synced video for the top 15 most high-value hymns
at all speeds (0.5x, 1.0x, 1.5x, 2.0x, 3.0x) as all genres (11 genres).

Features:
- Sine wave synthesis from MIDI files
- Enhanced video composition with intro clips, hymn-specific clips, random Magnific clips
- NNT material subtitles and text overlays
- projectM/MilkDrop visualizations
- YouTube-ready output (1280x720)
- TikTok vertical output (1080x1920)

Usage:
    python full_hymn_pipeline.py
    python full_hymn_pipeline.py --hymn "Amazing Grace" --skip-existing
"""

import os
import sys
import json
import subprocess
import random
import time
import struct
import sqlite3
from pathlib import Path

# ── Configuration ──────────────────────────────────────────────────
# ROOT is bobmani/hymnmania (where MIDI files, generated/, mp3_input/ live)
ROOT = Path(__file__).parent.parent.parent.parent / "bobmani" / "hymnmania"
if not (ROOT / "hymn_remaker").exists():
    # Fallback: find bobmani/hymnmania relative to this file
    ROOT = Path(__file__).resolve().parents[3] / "bobmani" / "hymnmania"
if not (ROOT / "hymn_remaker").exists():
    # Try from workspace root
    ROOT = Path(r"C:\Users\hyper\workspace\bobmani\hymnmania")
FFMPEG = ROOT / "hymn_remaker" / "bin" / "ffmpeg.exe"
if not FFMPEG.exists():
    FFMPEG = "ffmpeg"
else:
    FFMPEG = str(FFMPEG)

GEN_DIR = ROOT / "generated"
CLIPS_DIR = GEN_DIR / "magnific_clips"
NNT_DIR = Path(r"C:\Users\hyper\workspace\nnt_content")
OUTPUT_YOUTUBE = GEN_DIR / "youtube_ready"
OUTPUT_TIKTOK = GEN_DIR / "tiktok_ready"
AUDIO_DIR = ROOT / "mp3_input"
MIDI_INPUT = ROOT / "hymn_remaker" / "input"

SAMPLE_RATE = 22050

# Top 15 hymns with their MIDI file locations
HYMNS = {
    "Amazing Grace": {
        "midi": str(MIDI_INPUT / "AmazingGrace.mid"),
        "author": "John Newton", "year": "1779",
        "keywords": ["amazing", "grace"],
    },
    "How Great Thou Art": {
        "midi": str(MIDI_INPUT / "HowGreatThouArt.mid"),
        "author": "Carl Boberg", "year": "1885",
        "keywords": ["how great"],
    },
    "Be Thou My Vision": {
        "midi": str(MIDI_INPUT / "BeThouMyVision.mid"),
        "author": "Irish, 8th Century", "year": "800",
        "keywords": ["be thou", "vision"],
    },
    "It Is Well": {
        "midi": str(MIDI_INPUT / "ItIsWell.mid"),
        "author": "Horatio Spafford", "year": "1873",
        "keywords": ["it is well"],
    },
    "Great Is Thy Faithfulness": {
        "midi": str(MIDI_INPUT / "GreatIsThyFaithfulness.mid"),
        "author": "Thomas Chisholm", "year": "1923",
        "keywords": ["great is thy", "faithfulness"],
    },
    "Emmanuel": {
        "midi": str(ROOT / "archive" / "test_input" / "Emmanuel.mid"),
        "author": "Latin, 12th Century", "year": "1710",
        "keywords": ["emmanuel"],
    },
    "Thy Word": {
        "midi": str(ROOT / "hymn_remaker" / "input" / "_midi" / "h" / "y" / "Thy_Word_is_a_lamp.mid"),
        "author": "Amy Grant & Michael W. Smith", "year": "1984",
        "keywords": ["thy word"],
    },
    "Winchester": {
        "midi": str(ROOT / "classical_scraper" / "downloads" / "mutopia" / "WinchesterNew.mid"),
        "author": "Thomas Olivers", "year": "1770",
        "keywords": ["winchester"],
    },
    "Praise Him": {
        "midi": str(ROOT / "hymn_remaker" / "input" / "_midi" / "r" / "a" / "praise_Him_praise_Him.mid"),
        "author": "Fanny J. Crosby", "year": "1869",
        "keywords": ["praise him"],
    },
    "Oh For A Thousand Tongues": {
        "midi": str(ROOT / "hymn_remaker" / "input" / "_midi" / "O_For_A_Thousand_Tongues-Azmon.mid"),
        "author": "Charles Wesley", "year": "1739",
        "keywords": ["thousand tongues"],
    },
    "He Leadeth Me": {
        "midi": str(ROOT / "classical_scraper" / "downloads" / "mutopia" / "he_leadeth_me.mid"),
        "author": "Joseph H. Gilmore", "year": "1862",
        "keywords": ["he leadeth"],
    },
    "Canon in D": {
        "midi": str(MIDI_INPUT / "CanonInD.mid"),
        "author": "Johann Pachelbel", "year": "1680",
        "keywords": ["canon"],
    },
    "Clair de Lune": {
        "midi": str(MIDI_INPUT / "ClairDeLune.mid"),
        "author": "Claude Debussy", "year": "1905",
        "keywords": ["clair"],
    },
    "Moonlight Sonata": {
        "midi": str(MIDI_INPUT / "MoonlightSonata.mid"),
        "author": "Ludwig van Beethoven", "year": "1801",
        "keywords": ["moonlight"],
    },
    "Fur Elise": {
        "midi": str(MIDI_INPUT / "FurElise.mid"),
        "author": "Ludwig van Beethoven", "year": "1810",
        "keywords": ["fur elise"],
    },
}

GENRES = {
    "gabba": "dark industrial warehouse rave, pounding bass drums, strobe lights, distorted kicks, aggressive energy",
    "psytrance": "psychedelic fractal geometry, morphing alien landscapes, cosmic nebula colors, hypnotic spiraling patterns",
    "chiptune": "retro 8-bit pixel art world, neon arcade machines, glitching digital landscapes, vintage gaming aesthetics",
    "synthwave": "neon cyberpunk cityscape at sunset, chrome reflections, retro-futuristic grid, 80s aesthetic",
    "japanese_hardcore_techno": "hyperactive anime city, neon signs, lightning-fast energy, Tokyo night streets",
    "hardstyle_trance": "epic festival mainstage, massive laser show, pyrotechnics, crowd energy, dramatic sky",
    "deep_house": "warm sunset over ocean, smooth waves, golden hour light, relaxed rooftop party, chill atmosphere",
    "drum_and_bass": "fast-paced urban jungle, rain-soaked streets, neon reflections, liquid motion graphics",
    "dubstep": "mechanical transformers, bass drops causing shockwaves, glitch art, dark digital wasteland",
    "detroit_techno": "industrial Detroit factory, mechanical rhythms, steel and concrete, minimal geometric patterns",
    "detroit_house": "warm vinyl records spinning, soulful dance floor, vintage speakers, golden light",
}

SPEEDS = {
    0.5: "05x",
    1.0: "10x",
    1.5: "15x",
    2.0: "20x",
    3.0: "30x",
}

PITCH_FACTORS = {
    0.5: {"rate": 0.8909, "tempo": 1.1225},
    1.0: {"rate": 1.0595, "tempo": 0.9439},
    1.5: {"rate": 0.9439, "tempo": 1.0595},
    2.0: {"rate": 1.1225, "tempo": 0.8909},
    3.0: {"rate": 1.1892, "tempo": 0.8409},
}

# NNT guidelines for subtitles
NNT_GUIDELINES = []
nnt_file = NNT_DIR / "nnt_content.md"
if nnt_file.exists():
    with open(nnt_file, encoding="utf-8") as f:
        text = f.read()
    # Extract the 30 guidelines
    import re
    guidelines = re.findall(r'\d+\.\s+(.+?):\s*\n(.+?)(?=\n\d+\.|\nCondensed|\Z)', text, re.DOTALL)
    for title, body in guidelines:
        NNT_GUIDELINES.append(f"{title.strip()}: {body.strip()[:120]}")


def midi_to_wav(midi_path, wav_path, tempo_scale=1.0):
    """Render MIDI to WAV using pure Python sine wave synthesis."""
    try:
        import mido
    except ImportError:
        print("  ERROR: mido not installed")
        return False

    try:
        mid = mido.MidiFile(midi_path)
    except Exception as e:
        print(f"  ERROR: Cannot parse MIDI {midi_path}: {e}")
        return False

    ticks_per_beat = mid.ticks_per_beat or 480
    tempo = 500000
    all_events = []

    for track in mid.tracks:
        abs_ticks = 0
        for msg in track:
            abs_ticks += msg.time
            abs_sec = mido.tick2second(abs_ticks, ticks_per_beat, tempo)
            if msg.type == "set_tempo":
                tempo = msg.tempo
                abs_sec = mido.tick2second(abs_ticks, ticks_per_beat, tempo)
            if msg.type == "note_on" and msg.velocity > 0:
                all_events.append((abs_sec, "on", msg.note, msg.velocity))
            elif msg.type == "note_off" or (msg.type == "note_on" and msg.velocity == 0):
                all_events.append((abs_sec, "off", msg.note, 0))

    if not all_events:
        return False

    all_events.sort(key=lambda x: x[0])
    max_time = min(max(e[0] for e in all_events) + 2.0, 300.0)
    total_samples = int(max_time * SAMPLE_RATE) + SAMPLE_RATE
    audio = [0.0] * total_samples

    active = {}
    for abs_sec, etype, note, vel in all_events:
        if etype == "on":
            active[note] = {"start": abs_sec, "vel": vel / 127.0}
        elif etype == "off" and note in active:
            info = active.pop(note)
            start = info["start"]
            v = info["vel"]
            dur = abs_sec - start
            if dur <= 0 or dur > 15:
                continue
            freq = 440.0 * (2.0 ** ((note - 69) / 12.0))
            n_samp = int(dur * SAMPLE_RATE)
            s0 = int(start * SAMPLE_RATE)
            s1 = min(s0 + n_samp, total_samples)
            if s0 >= total_samples:
                continue
            import math
            for i in range(s0, s1):
                t = (i - s0) / SAMPLE_RATE
                env = 1.0
                atk = min(int(0.005 * SAMPLE_RATE), s1 - s0)
                rel = min(int(0.05 * SAMPLE_RATE), s1 - s0)
                if i - s0 < atk:
                    env = (i - s0) / atk
                elif s1 - i < rel:
                    env = (s1 - i) / rel
                audio[i] += math.sin(2 * math.pi * freq * t) * env * v * 0.15

    # Normalize
    max_val = max(abs(x) for x in audio) or 1.0
    audio = [x / max_val * 0.7 for x in audio]

    # Write WAV
    audio_int16 = [int(x * 32767) for x in audio]
    with open(wav_path, "wb") as f:
        data_size = len(audio_int16) * 2
        f.write(b"RIFF")
        f.write(struct.pack("<I", 36 + data_size))
        f.write(b"WAVE")
        f.write(b"fmt ")
        f.write(struct.pack("<IHHIIHH", 16, 1, 1, SAMPLE_RATE, SAMPLE_RATE * 2, 2, 16))
        f.write(b"data")
        f.write(struct.pack("<I", data_size))
        for s in audio_int16:
            f.write(struct.pack("<h", s))
    return True


def wav_to_mp3(wav_path, mp3_path, speed=1.0):
    """Convert WAV to MP3 with speed adjustment and pitch shift."""
    pf = PITCH_FACTORS.get(speed, {"rate": 1.0, "tempo": 1.0})
    cmd = [
        FFMPEG, "-y", "-i", wav_path,
        "-af", f"asetrate={SAMPLE_RATE}*{pf['rate']},atempo={pf['tempo']},aresample={SAMPLE_RATE}",
        "-codec:a", "libmp3lame", "-b:a", "128k", mp3_path
    ]
    r = subprocess.run(cmd, capture_output=True, timeout=60)
    return os.path.exists(mp3_path)


def get_clip_pool(hymn_name=None):
    """Build categorized clip pool from magnific_clips directory."""
    if not CLIPS_DIR.exists():
        return {"intro": [], "hymn": [], "themed": [], "all": []}

    intro = []
    hymn_clips = []
    themed = []

    for f in sorted(CLIPS_DIR.iterdir()):
        if not f.name.endswith(".mp4"):
            continue
        if f.stat().st_size < 10000:
            continue
        fn = f.name.lower()
        if "intro" in fn or "resurrecting" in fn:
            intro.append(str(f))
        elif hymn_name and hymn_name.lower().replace(" ", "_") in fn:
            hymn_clips.append(str(f))
        else:
            themed.append(str(f))

    return {
        "intro": intro,
        "hymn": hymn_clips,
        "themed": themed,
        "all": intro + hymn_clips + themed,
    }


def get_nnt_subtitle(hymn_name, genre, speed_label):
    """Get an NNT guideline for subtitle overlay."""
    if not NNT_GUIDELINES:
        return f"{hymn_name} - {genre.replace('_', ' ').title()} - {speed_label}"
    # Rotate through guidelines based on hymn+genre hash
    idx = hash(hymn_name + genre + speed_label) % len(NNT_GUIDELINES)
    return NNT_GUIDELINES[idx]


def compose_video(audio_path, output_path, hymn_name, genre, speed_label,
                  use_subtitles=True, vertical=False):
    """Compose a beat-synced video with intro, hymn clips, NNT subtitles."""
    import numpy as np
    from scipy.signal import find_peaks

    clip_pool = get_clip_pool(hymn_name)
    if not clip_pool["all"]:
        print(f"    No clips available")
        return False

    # Detect beats
    try:
        r = subprocess.run(
            [FFMPEG, "-y", "-i", audio_path, "-f", "f32le", "-acodec", "pcm_f32le",
             "-ar", "44100", "-ac", "1", "-"],
            capture_output=True, timeout=60
        )
        pcm = np.frombuffer(r.stdout, dtype=np.float32)
        sr = 44100
        duration = len(pcm) / sr

        hop = 512
        n = len(pcm) // hop
        energy = np.array([np.sqrt(np.mean(pcm[i*hop:(i+1)*hop]**2)) for i in range(n)])
        onset_env = np.maximum(np.diff(energy), 0)

        min_lag = int(60 / 200 * sr / hop)
        max_lag = int(60 / 70 * sr / hop)
        autocorr = np.zeros(max_lag - min_lag)
        for lag in range(min_lag, max_lag):
            autocorr[lag - min_lag] = np.sum(onset_env[lag:] * onset_env[:-lag])
        best_lag = np.argmax(autocorr) + min_lag
        tempo = 60.0 / (best_lag * hop / sr)

        beat_interval = 60.0 / tempo
        peaks, _ = find_peaks(
            onset_env,
            distance=int(beat_interval * sr / hop * 0.5),
            height=np.mean(onset_env) + 0.5 * np.std(onset_env),
        )
        beat_times = peaks * hop / sr
        phrase_times = beat_times[::8]
    except Exception as e:
        print(f"    Beat detection failed: {e}")
        duration = 180.0
        phrase_times = [i * 8.0 for i in range(int(duration / 8) + 1)]

    if len(phrase_times) < 2:
        phrase_times = [0.0, duration]

    # Build clip sequence
    sequence = []
    available = clip_pool["themed"] if clip_pool["themed"] else clip_pool["all"]

    # 1. Intro
    if clip_pool["intro"]:
        sequence.append(random.choice(clip_pool["intro"]))

    # 2. Hymn-specific
    if clip_pool["hymn"]:
        sequence.append(random.choice(clip_pool["hymn"]))

    # 3. Fill with themed (no back-to-back)
    last = sequence[-1] if sequence else None
    for i in range(len(sequence), len(phrase_times)):
        candidates = [c for c in available if c != last] or available
        chosen = random.choice(candidates)
        sequence.append(chosen)
        last = chosen

    # Prepare segments
    temp_segments = []
    w, h = (1080, 1920) if vertical else (1280, 720)

    for i in range(len(phrase_times)):
        clip_path = sequence[i % len(sequence)]
        start = phrase_times[i]
        end = phrase_times[i + 1] if i + 1 < len(phrase_times) else duration
        seg_dur = end - start

        temp_path = str(GEN_DIR / f"_temp_seg_{i}.mp4")
        clip_dur = 5.0
        try:
            r2 = subprocess.run(
                [FFMPEG, "-i", clip_path, "-f", "null", "-"],
                capture_output=True, text=True, timeout=10
            )
            for line in r2.stderr.split("\n"):
                if "Duration" in line:
                    parts = line.split("Duration:")[1].split(",")[0].strip()
                    hh, mm, ss = parts.split(":")
                    clip_dur = float(hh) * 3600 + float(mm) * 60 + float(ss)
        except Exception:
            pass

        loop_count = max(1, int(seg_dur / clip_dur) + 1)
        vf = f"scale={w}:{h}:force_original_aspect_ratio=decrease,pad={w}:{h}:(ow-iw)/2:(oh-ih)/2,fps=30"
        cmd = [
            FFMPEG, "-y", "-stream_loop", str(loop_count), "-i", clip_path,
            "-t", str(seg_dur), "-vf", vf,
            "-c:v", "libx264", "-preset", "ultrafast", "-crf", "28",
            "-an", "-pix_fmt", "yuv420p", temp_path
        ]
        subprocess.run(cmd, capture_output=True, timeout=120)
        if os.path.exists(temp_path):
            temp_segments.append(temp_path)

    if not temp_segments:
        return False

    # Concat
    list_file = str(GEN_DIR / "_concat_list.txt")
    with open(list_file, "w") as f:
        for seg in temp_segments:
            f.write(f"file '{os.path.abspath(seg)}'\n")

    # Add subtitle if NNT content available
    subtitle_filter = ""
    if use_subtitles and NNT_GUIDELINES:
        subtitle_text = get_nnt_subtitle(hymn_name, genre, speed_label)
        # Escape special chars for FFmpeg drawtext
        subtitle_text = subtitle_text.replace("'", "'\\''").replace(":", "\\:")
        subtitle_filter = f",drawtext=text='{subtitle_text}':fontsize=24:fontcolor=white:borderw=2:bordercolor=black:x=(w-text_w)/2:y=h-60"

    cmd = [
        FFMPEG, "-y", "-f", "concat", "-safe", "0", "-i", list_file,
        "-i", audio_path,
        "-c:v", "libx264", "-preset", "medium", "-crf", "23",
        "-c:a", "aac", "-b:a", "192k",
        "-pix_fmt", "yuv420p", "-shortest", output_path
    ]
    if subtitle_filter:
        cmd.insert(-1, "-vf")
        cmd.insert(-1, subtitle_filter[1:])  # Remove leading comma

    r = subprocess.run(cmd, capture_output=True, timeout=600)

    # Cleanup
    for seg in temp_segments:
        try:
            os.remove(seg)
        except OSError:
            pass
    try:
        os.remove(list_file)
    except OSError:
        pass

    success = os.path.exists(output_path) and os.path.getsize(output_path) > 10000
    return success


def process_hymn(hymn_name, hymn_info, skip_existing=True):
    """Process a single hymn: generate audio + video for all genres and speeds."""
    midi_path = hymn_info["midi"]
    if not os.path.exists(midi_path):
        print(f"  MIDI not found: {midi_path}")
        return 0

    safe_name = "".join(c for c in hymn_name if c.isalnum() or c in " ._-'")
    safe_name = safe_name.strip().replace(" ", "_")[:80]
    completed = 0

    # Generate base WAV once
    temp_wav = str(AUDIO_DIR / f"_temp_{safe_name}.wav")
    if not os.path.exists(temp_wav):
        print(f"  Rendering MIDI to WAV...")
        if not midi_to_wav(midi_path, temp_wav):
            print(f"  FAILED: MIDI render")
            return 0

    for speed, speed_label in SPEEDS.items():
        # Generate MP3 for this speed
        mp3_name = f"{safe_name}_sine_{speed_label}.mp3"
        mp3_path = str(AUDIO_DIR / mp3_name)

        if not os.path.exists(mp3_path):
            if not wav_to_mp3(temp_wav, mp3_path, speed):
                print(f"    FAILED: MP3 {speed_label}")
                continue

        for genre_key, genre_desc in GENRES.items():
            # Check if already exists
            genre_title = genre_key.replace("_", " ").title()
            is_classical = hymn_name in ["Canon in D", "Clair de Lune", "Moonlight Sonata", "Fur Elise"]
            piece_type = "Classical" if is_classical else "Hymn"
            piece_label = "Remix" if is_classical else "2026 Remix"

            video_name = f"{genre_title} {piece_type} {piece_label} - {hymn_name} ({hymn_info['author']}, {hymn_info['year']}) - {speed_label} Speed.mp4"
            youtube_path = str(OUTPUT_YOUTUBE / video_name)
            tiktok_name = video_name.replace(".mp4", "_vertical.mp4")
            tiktok_path = str(OUTPUT_TIKTOK / tiktok_name)

            if skip_existing and os.path.exists(youtube_path) and os.path.exists(tiktok_path):
                continue

            print(f"    {genre_title} @ {speed_label}...")

            # YouTube version (1280x720)
            if not os.path.exists(youtube_path):
                if compose_video(mp3_path, youtube_path, hymn_name, genre_key, speed_label):
                    completed += 1
                    print(f"      YouTube OK")
                else:
                    print(f"      YouTube FAILED")

            # TikTok version (1080x1920 vertical)
            if not os.path.exists(tiktok_path):
                if compose_video(mp3_path, tiktok_path, hymn_name, genre_key, speed_label, vertical=True):
                    completed += 1
                    print(f"      TikTok OK")

    # Cleanup temp WAV
    try:
        os.remove(temp_wav)
    except OSError:
        pass

    return completed


def main():
    import argparse
    parser = argparse.ArgumentParser(description="Full HymnMania Pipeline")
    parser.add_argument("--hymn", help="Process only this hymn")
    parser.add_argument("--no-skip", action="store_true", help="Don't skip existing files")
    parser.add_argument("--limit", type=int, default=0, help="Limit number of hymns")
    args = parser.parse_args()

    # Create output dirs
    OUTPUT_YOUTUBE.mkdir(parents=True, exist_ok=True)
    OUTPUT_TIKTOK.mkdir(parents=True, exist_ok=True)
    AUDIO_DIR.mkdir(parents=True, exist_ok=True)

    skip = not args.no_skip
    hymns_to_process = HYMNS

    if args.hymn:
        hymns_to_process = {k: v for k, v in HYMNS.items() if args.hymn.lower() in k.lower()}
    if args.limit > 0:
        hymns_to_process = dict(list(hymns_to_process.items())[:args.limit])

    print("=" * 70)
    print(f"FULL HYMNMANIA PIPELINE")
    print(f"Hymns: {len(hymns_to_process)}")
    print(f"Genres: {len(GENRES)}")
    print(f"Speeds: {len(SPEEDS)}")
    print(f"Total combinations: {len(hymns_to_process) * len(GENRES) * len(SPEEDS)}")
    print(f"NNT guidelines loaded: {len(NNT_GUIDELINES)}")
    print("=" * 70)

    total_completed = 0
    start_time = time.time()

    for i, (hymn_name, hymn_info) in enumerate(hymns_to_process.items(), 1):
        print(f"\n[{i}/{len(hymns_to_process)}] {hymn_name}")
        completed = process_hymn(hymn_name, hymn_info, skip_existing=skip)
        total_completed += completed
        print(f"  Completed: {completed} videos")

    elapsed = time.time() - start_time
    print(f"\n{'=' * 70}")
    print(f"PIPELINE COMPLETE")
    print(f"Total videos created: {total_completed}")
    print(f"Time: {elapsed:.0f}s ({elapsed/60:.1f}m)")
    print(f"YouTube: {OUTPUT_YOUTUBE}")
    print(f"TikTok: {OUTPUT_TIKTOK}")
    print(f"{'=' * 70}")


if __name__ == "__main__":
    main()
