import os
import pytest
import numpy as np
import hymn_player_ext

def test_hymn_player_ext():
    # Attempt to initialize
    player = hymn_player_ext.HymnPlayer()

    # Check initial state
    assert not player.is_playing()

    # Try rendering some silence
    audio_buffer = player.render_audio(512)
    assert isinstance(audio_buffer, np.ndarray)
    assert audio_buffer.shape == (1024,)
    assert np.all(audio_buffer == 0.0)

if __name__ == "__main__":
    test_hymn_player_ext()
    print("Pybind11 extension test passed!")
