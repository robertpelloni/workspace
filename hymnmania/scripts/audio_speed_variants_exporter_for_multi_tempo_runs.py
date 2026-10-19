import os
import sys
import argparse
import subprocess

ROOT = os.path.dirname(os.path.abspath(__file__))

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--midi", required=True)
    parser.add_argument("--outdir", required=True)
    args = parser.parse_args()

    hymn_name = os.path.splitext(os.path.basename(args.midi))[0]
    os.makedirs(args.outdir, exist_ok=True)

    from pipeline_config_central_definitions_genres_speeds import SPEEDS, SPEED_LABEL_MAP
    speeds = SPEEDS
    speed_labels = SPEED_LABEL_MAP

    synth_script = os.path.join(ROOT, "audio_synthesis_render_midi_to_sine_wave_clean.py")
    filter_script = os.path.join(ROOT, "audio_dsp_apply_lowpass_highpass_delay_filters_for_copyright_bypass.py")

    for speed in speeds:
        label = speed_labels[speed]
        temp_wav = os.path.join(args.outdir, f"{hymn_name}_temp_{label}.wav")
        output_mp3 = os.path.join(args.outdir, f"{hymn_name}_sine_{label}.mp3")

        print(f"Generating speed variant: {speed}x...")
        # 1. Synthesize WAV
        subprocess.run([
            sys.executable, synth_script,
            "--midi", args.midi,
            "--wav", temp_wav,
            "--speed", str(speed)
        ])

        # 2. Filter to MP3
        subprocess.run([
            sys.executable, filter_script,
            "--wav", temp_wav,
            "--mp3", output_mp3,
            "--speed", str(speed)
        ])

        if os.path.exists(temp_wav):
            os.remove(temp_wav)

if __name__ == "__main__":
    main()
