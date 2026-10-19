import os
import sys
import logging
import numpy as np
import mido
import librosa

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

def transcribe_audio_to_midi(audio_path, output_midi_path):
    """
    Transcribes monophonic audio to MIDI using librosa's pYIN algorithm.
    """
    if not os.path.exists(audio_path):
        raise FileNotFoundError(f"Audio file not found: {audio_path}")

    logger.info(f"Transcribing {audio_path} to MIDI using pYIN...")

    y, sr = librosa.load(audio_path, sr=22050) # Use 22k for speed

    # fmin/fmax for typical human voice / hymn range
    f0, voiced_flag, voiced_probs = librosa.pyin(y,
                                                 fmin=librosa.note_to_hz('C2'),
                                                 fmax=librosa.note_to_hz('C7'),
                                                 sr=sr)

    mid = mido.MidiFile()
    track = mido.MidiTrack()
    mid.tracks.append(track)

    ticks_per_beat = mid.ticks_per_beat
    tempo = 500000 # 120 BPM

    times = librosa.times_like(f0, sr=sr)
    last_midi = None
    last_time_ticks = 0

    # Process frames into notes
    for val, t in zip(f0, times):
        current_time_ticks = int(mido.second2tick(t, ticks_per_beat, tempo))

        if np.isnan(val):
            if last_midi is not None:
                delta = current_time_ticks - last_time_ticks
                track.append(mido.Message('note_off', note=last_midi, velocity=0, time=max(0, delta)))
                last_time_ticks = current_time_ticks
                last_midi = None
            continue

        midi_note = int(round(librosa.hz_to_midi(val)))

        if midi_note != last_midi:
            if last_midi is not None:
                delta = current_time_ticks - last_time_ticks
                track.append(mido.Message('note_off', note=last_midi, velocity=0, time=max(0, delta)))
                last_time_ticks = current_time_ticks

            track.append(mido.Message('note_on', note=midi_note, velocity=100, time=0))
            last_midi = midi_note
            logger.info(f"Detected Note: {midi_note} at {t:.2f}s")

    # Close last note
    if last_midi is not None:
        total_duration = len(y) / sr
        current_time_ticks = int(mido.second2tick(total_duration, ticks_per_beat, tempo))
        delta = current_time_ticks - last_time_ticks
        track.append(mido.Message('note_off', note=last_midi, velocity=0, time=max(0, delta)))

    mid.save(output_midi_path)
    logger.info(f"MIDI saved to {output_midi_path}")
    return output_midi_path

if __name__ == "__main__":
    if len(sys.argv) > 2:
        transcribe_audio_to_midi(sys.argv[1], sys.argv[2])
    else:
        print("Usage: python audio_to_midi.py <input_audio> <output_midi>")
