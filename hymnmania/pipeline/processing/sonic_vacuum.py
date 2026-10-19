import mido
import pretty_midi
import numpy as np
from scipy.io import wavfile
import os
import logging

logger = logging.getLogger(__name__)

class SonicVacuumProcessor:
    def __init__(self, midi_path: str):
        self.midi_path = midi_path
        try:
            self.pm = pretty_midi.PrettyMIDI(midi_path)
        except Exception as e:
            logger.error(f"Failed to load MIDI file {midi_path}: {e}")
            self.pm = None

    def render_sine_wave(self, output_path, sample_rate=44100):
        """Toggle Option A: Pure Sine Wave"""
        if self.pm is None: return None
        duration = self.pm.get_end_time()

        if duration <= 0:
            logger.warning(f"MIDI file {self.midi_path} has zero duration. Generating 1s silence.")
            audio = np.zeros(sample_rate, dtype=np.float32)
        else:
            audio = np.zeros(int(sample_rate * duration), dtype=np.float32)

        for track in self.pm.instruments:
            for note in track.notes:
                start_sample = int(note.start * sample_rate)
                end_sample = int(note.end * sample_rate)
                if start_sample >= len(audio): continue

                freq = 440 * (2 ** ((note.pitch - 69) / 12))
                t = np.arange(end_sample - start_sample) / sample_rate
                sine = np.sin(2 * np.pi * freq * t) * note.velocity / 127.0
                audio[start_sample:end_sample] += sine

        if audio.size > 0 and np.max(np.abs(audio)) > 0:
            audio = audio / np.max(np.abs(audio))

        wavfile.write(output_path, sample_rate, (audio * 32767).astype(np.int16))
        return output_path

    def render_dry_piano(self, output_path, sample_rate=44100, return_audio=False):
        """Toggle Option B: Dry Piano Rendering (Staccato Sine Blend)"""
        if self.pm is None: return None if not return_audio else (None, sample_rate)
        duration = self.pm.get_end_time()

        if duration <= 0:
            logger.warning(f"MIDI file {self.midi_path} has zero duration. Generating 1s silence.")
            audio = np.zeros(sample_rate, dtype=np.float32)
        else:
            audio = np.zeros(int(sample_rate * duration), dtype=np.float32)

        for track in self.pm.instruments:
            for note in track.notes:
                start_sample = int(note.start * sample_rate)
                note_dur = min(note.end - note.start, 0.1)
                end_sample = int((note.start + note_dur) * sample_rate)

                if start_sample >= len(audio): continue

                freq = 440 * (2 ** ((note.pitch - 69) / 12))
                t = np.arange(end_sample - start_sample) / sample_rate
                envelope = np.exp(-10 * t)
                sine = np.sin(2 * np.pi * freq * t) * (note.velocity / 127.0) * envelope
                audio[start_sample:end_sample] += sine

        if audio.size > 0 and np.max(np.abs(audio)) > 0:
            audio = audio / np.max(np.abs(audio))

        if output_path:
            wavfile.write(output_path, sample_rate, (audio * 32767).astype(np.int16))

        if return_audio:
            return audio, sample_rate
        return output_path

    def export_speed_variants(self, audio_array, sample_rate, output_base_path):
        """
        Exports three speed variants of the raw staccato hymn audio.
        0.5x (Slower), 1.0x (Base), 2.0x (Faster).
        """
        logger.info(f"Exporting speed variants to {output_base_path}...")

        # 1.0x Base
        wavfile.write(f"{output_base_path}_1x.wav", sample_rate, (audio_array * 32767).astype(np.int16))

        # 0.5x Speed (Slower)
        indices_05 = np.arange(0, len(audio_array), 0.5)
        indices_05 = np.clip(indices_05, 0, len(audio_array) - 1).astype(np.int64)
        audio_05 = audio_array[indices_05]
        wavfile.write(f"{output_base_path}_05x.wav", sample_rate, (audio_05 * 32767).astype(np.int16))

        # 2.0x Speed (Faster)
        audio_20 = audio_array[::2]
        wavfile.write(f"{output_base_path}_2x.wav", sample_rate, (audio_20 * 32767).astype(np.int16))

        return [
            f"{output_base_path}_05x.wav",
            f"{output_base_path}_1x.wav",
            f"{output_base_path}_2x.wav"
        ]
