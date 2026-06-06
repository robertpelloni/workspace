import os
import pytest
from hymn_remaker.src.local_remaker import LocalMusicRemaker
import numpy as np
from scipy.io import wavfile

def test_local_musicgen_generation():
    # Setup
    melody_path = 'tests/local_test_melody.wav'
    output_path = 'tests/local_test_output.wav'
    sr = 22050
    t = np.linspace(0, 1, sr)
    data = np.sin(2 * np.pi * 440 * t)
    wavfile.write(melody_path, sr, (data * 32767).astype(np.int16))

    # Test
    # Using a very short duration for the test
    remaker = LocalMusicRemaker()
    remaker.generate(melody_path, "test prompt", duration=1, output_path=output_path)

    # Verify
    assert os.path.exists(output_path)
    assert os.path.getsize(output_path) > 1000

    # Cleanup
    os.remove(melody_path)
    os.remove(output_path)
