# Submodule Dashboard

This project is an automated pipeline that takes public domain MIDI hymn files and transforms them into modern "Deep House" (or other styles) music videos for YouTube.

Currently, this repository is focused primarily on the Hymn Remaker Pipeline. While it operates within the context of the Omni-Workspace, it primarily relies on the following internal structure and external dependencies:

## Core Pipeline Structure
- **`hymn_remaker/`**: The root directory for the Hymn Remaker application.
- **`hymn_remaker/src/`**: Contains the core logic modules.
  - `midi_renderer.py`: Converts MIDI to WAV using FluidSynth.
  - `remaker.py`: Interacts with Replicate's MusicGen for style-conditioned audio generation.
  - `content_generator.py`: Uses OpenAI for lyrics and metadata generation, and DALL-E 3 for album art.
  - `tts_generator.py`: Utilizes ElevenLabs for vocal synthesis.
  - `video_uploader.py`: Combines assets into an MP4 video using FFmpeg and optionally uploads to YouTube.
  - `utils.py`: Provides utility functions for audio processing and API retries.
- **`hymn_remaker/tests/`**: Contains the Pytest suite for the pipeline.
- **`hymn_remaker/scripts/`**: Utility scripts for testing and automation.

## External Submodules & Libraries
- **OpenAI**: Used for generating video metadata, lyrics, and DALL-E 3 album art.
- **Replicate**: Used for accessing Meta's `musicgen-melody` model.
- **ElevenLabs**: Used for synthesizing high-quality vocal tracks.
- **FluidSynth**: A real-time software synthesizer used for rendering MIDI files to audio using SoundFonts.
- **FFmpeg**: A multimedia framework used to combine audio and image assets into the final video output and handle subtitle formatting.
- **Librosa & PyRubberband**: Used for high-fidelity audio pitch-shifting algorithms without altering temporal speed, enhancing ElevenLabs TTS harmonies.
