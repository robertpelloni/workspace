import mido
import pretty_midi
import numpy as np
from scipy.io import wavfile
import os

class SonicVacuumProcessor:
    def __init__(self, midi_path: str):
        self.midi_path = midi_path
        self.pm = pretty_midi.PrettyMIDI(midi_path)

    def render_sine_wave(self, output_path, sample_rate=44100):
        """Toggle Option A: Pure Sine Wave"""
        # Estimate duration
        duration = self.pm.get_end_time()
        audio = np.zeros(int(sample_rate * duration), dtype=np.float32)

        for track in self.pm.instruments:
            for note in track.notes:
                start_sample = int(note.start * sample_rate)
                end_sample = int(note.end * sample_rate)
                if start_sample >= len(audio): continue

                # Frequency formula
                freq = 440 * (2 ** ((note.pitch - 69) / 12))

                # Generate sine
                t = np.arange(end_sample - start_sample) / sample_rate
                sine = np.sin(2 * np.pi * freq * t) * note.velocity / 127.0

                # Add to buffer (instant cutoff, no envelope)
                audio[start_sample:end_sample] += sine

        # Normalize
        if audio.size > 0 and np.max(np.abs(audio)) > 0:
            audio = audio / np.max(np.abs(audio))

        wavfile.write(output_path, sample_rate, (audio * 32767).astype(np.int16))
        return output_path

    def render_dry_piano(self, output_path, sample_rate=44100):
        """Toggle Option B: Dry Piano Rendering (Staccato Sine Blend)"""
        duration = self.pm.get_end_time()
        audio = np.zeros(int(sample_rate * duration), dtype=np.float32)

        for track in self.pm.instruments:
            for note in track.notes:
                start_sample = int(note.start * sample_rate)
                # Force staccato: max 100ms duration
                note_dur = min(note.end - note.start, 0.1)
                end_sample = int((note.start + note_dur) * sample_rate)

                if start_sample >= len(audio): continue

                freq = 440 * (2 ** ((note.pitch - 69) / 12))
                t = np.arange(end_sample - start_sample) / sample_rate

                # Sharp decay envelope
                envelope = np.exp(-10 * t)
                sine = np.sin(2 * np.pi * freq * t) * (note.velocity / 127.0) * envelope

                audio[start_sample:end_sample] += sine

        if audio.size > 0 and np.max(np.abs(audio)) > 0:
            audio = audio / np.max(np.abs(audio))

        wavfile.write(output_path, sample_rate, (audio * 32767).astype(np.int16))
        return output_path
