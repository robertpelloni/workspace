import os
import sys
import argparse
import subprocess

ROOT = os.path.dirname(os.path.abspath(__file__))
FFMPEG = os.path.join(ROOT, "..", "hymn_remaker", "bin", "ffmpeg.exe")
if not os.path.exists(FFMPEG):
    FFMPEG = "ffmpeg"

def apply_dsp_filters(input_wav, output_mp3, speed=1.0):
    """Apply speed-dependent pitch shifts, bandpass, and delay filters to defeat ACRCloud matching."""
    from pipeline_config_central_definitions_genres_speeds import PITCH_SHIFT_FACTORS
    pf = PITCH_SHIFT_FACTORS.get(speed, {"rate": 1.0595, "tempo": 0.9439})

    cf = subprocess.CREATE_NO_WINDOW if hasattr(subprocess, "CREATE_NO_WINDOW") else 0
    cmd = [
        FFMPEG, "-y", "-i", input_wav,
        "-af", f"asetrate=44100*{pf['rate']},atempo={pf['tempo']},aresample=44100,lowpass=f=3500,highpass=f=120,adelay=400|400",
        "-codec:a", "libmp3lame", "-b:a", "128k", output_mp3
    ]
    subprocess.run(cmd, capture_output=True, text=True, timeout=60, creationflags=cf)
    print(f"Applied bypass filters to MP3: {output_mp3}")

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--wav", required=True)
    parser.add_argument("--mp3", required=True)
    parser.add_argument("--speed", type=float, default=1.0)
    args = parser.parse_args()
    apply_dsp_filters(args.wav, args.mp3, args.speed)

if __name__ == "__main__":
    main()
