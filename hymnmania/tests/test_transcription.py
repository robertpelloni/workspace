import os
from hymn_remaker.src.audio_to_midi import transcribe_audio_to_midi
import mido

def test_sine_transcription():
    # Setup
    audio_path = 'tests/sine_440_test.wav'
    midi_path = 'tests/sine_440_test.mid'
    import numpy as np
    from scipy.io import wavfile
    sr = 22050
    t = np.linspace(0, 1, sr)
    data = np.sin(2 * np.pi * 440 * t)
    wavfile.write(audio_path, sr, (data * 32767).astype(np.int16))

    # Transcribe
    transcribe_audio_to_midi(audio_path, midi_path)

    # Verify
    mid = mido.MidiFile(midi_path)
    notes = [msg.note for msg in mid.tracks[0] if msg.type == 'note_on']
    assert 69 in notes # A4 is 69

    # Cleanup
    os.remove(audio_path)
    os.remove(midi_path)
