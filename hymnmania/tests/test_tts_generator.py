import os
import sys
import pytest
import numpy as np
from pydub import AudioSegment
from pydub.generators import Sine

# Ensure hymn_remaker path is valid for importing tts_generator
sys.path.insert(0, os.path.abspath('hymn_remaker'))
from src.tts_generator import TTSGenerator


def test_pitch_shift_length_and_samples():
    """
    Test that the pyrubberband pitch shift implementation correctly shifts pitch
    without altering the duration or number of samples of the original audio.
    Also verifies that the output dtype matches the input sample_width
    (fixes the old sound.array_type AttributeError bug).
    """
    # Create a 1-second 16-bit mono sine wave
    sound = Sine(440).to_audio_segment(duration=1000)

    tts = TTSGenerator()
    tts.api_key = "dummy"

    # Apply a pitch shift (+4 semitones)
    shifted = tts._pitch_shift(sound, 4)

    # Assert duration remains unchanged (1000ms)
    assert len(shifted) == len(sound), "Duration changed after pitch shift!"

    # Assert number of samples remains unchanged
    assert len(shifted.get_array_of_samples()) == len(sound.get_array_of_samples()), \
        "Number of samples changed after pitch shift!"

    # Assert the output dtype is correct for 16-bit audio (2 bytes per sample)
    samples = np.array(shifted.get_array_of_samples())
    assert samples.dtype == np.int16, f"Expected np.int16 for 16-bit audio, got {samples.dtype}"


def test_pitch_shift_stereo():
    """Test pitch shift preserves stereo channel structure."""
    # Create a 1-second stereo sine wave
    mono = Sine(440).to_audio_segment(duration=1000)
    stereo = mono.set_channels(2)

    tts = TTSGenerator()
    tts.api_key = "dummy"

    shifted = tts._pitch_shift(stereo, 7)

    # Assert duration unchanged
    assert len(shifted) == len(stereo), "Stereo duration changed after pitch shift!"

    # Assert channel count preserved
    assert shifted.channels == 2, f"Expected 2 channels, got {shifted.channels}"


def test_pitch_shift_negative_semitones():
    """Test that negative semitone shifts (pitch down) work correctly."""
    sound = Sine(440).to_audio_segment(duration=1000)

    tts = TTSGenerator()
    tts.api_key = "dummy"

    shifted = tts._pitch_shift(sound, -5)

    assert len(shifted) == len(sound), "Duration changed after negative pitch shift!"
    assert len(shifted.get_array_of_samples()) == len(sound.get_array_of_samples()), \
        "Sample count changed after negative pitch shift!"
