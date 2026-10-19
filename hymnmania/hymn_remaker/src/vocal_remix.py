import os
import subprocess
import librosa
import soundfile as sf
import numpy as np
from hymn_remaker.src.lalal_api import LalalAPI

class VocalRemixer:
    def __init__(self):
        pass

    def process_remix(self, input_path, output_path, target_bpm=145, target_key_root=None):
        """
        Isolates vocals (if needed), time-stretches to target_bpm,
        and pitch-shifts to target_key_root.
        """
        print(f"Processing vocal remix: {input_path}")

        # 1. Download if URL (using yt-dlp)
        work_path = input_path
        if input_path.startswith("http"):
            work_path = "vocal_download.wav"
            subprocess.run(["yt-dlp", "-x", "--audio-format", "wav", "-o", work_path, input_path], check=True)

        # 2. Separate Stems (using Demucs with LALAL.AI fallback)
        # Note: In a production environment, we'd check if it's already an acapella
        vocal_path = work_path
        if not input_path.endswith("_vocals.wav"):
            print("Attempting vocal separation...")
            try:
                print("Running local Demucs separation...")
                subprocess.run(["python", "-m", "demucs.separate", "--two-stems=vocals", work_path, "-o", "separated"], check=True)
                filename = os.path.splitext(os.path.basename(work_path))[0]
                vocal_path = os.path.join("separated", "htdemucs", filename, "vocals.wav")
            except Exception as e:
                print(f"Local Demucs failed: {e}. Checking LALAL.AI fallback...")
                lalal = LalalAPI()
                if lalal.is_available():
                    vocal_path = lalal.separate_vocals(work_path, os.path.dirname(output_path))
                else:
                    print("LALAL.AI not configured. Proceeding with original audio (remix may be noisy).")

        # 3. Audio Analysis & Stretching
        print("Analyzing and stretching audio...")
        y, sr = librosa.load(vocal_path, sr=None)

        # Detect BPM
        tempo, _ = librosa.beat.beat_track(y=y, sr=sr)
        if isinstance(tempo, np.ndarray):
            tempo = tempo[0]

        print(f"Detected original BPM: {tempo}")

        # Time stretch ratio
        ratio = target_bpm / tempo
        print(f"Time stretch ratio: {ratio}")

        # librosa.effects.time_stretch
        y_stretched = librosa.effects.time_stretch(y, rate=ratio)

        # 4. Pitch Shift (if key provided)
        if target_key_root is not None:
            # Detect current key (simplistic)
            chroma = librosa.feature.chroma_stft(y=y_stretched, sr=sr)
            curr_key_idx = np.argmax(np.mean(chroma, axis=1))

            # target_key_root should be 0-11 (C=0)
            shift = target_key_root - curr_key_idx
            if shift > 6: shift -= 12
            if shift < -6: shift += 12

            print(f"Pitch shifting by {shift} semitones...")
            y_stretched = librosa.effects.pitch_shift(y_stretched, sr=sr, n_steps=shift)

        # 5. Save
        sf.write(output_path, y_stretched, sr)
        print(f"Vocal remix saved to {output_path}")
        return True
