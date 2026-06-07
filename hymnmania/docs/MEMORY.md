# Project Memory & Architectural Observations

- **Hybrid Architecture:** The project is a hybrid C++/Python/TypeScript system. While TypeScript initially handled symbolic logic, core algorithmic sequencing was ported to Python (`psy_sequencer.py`) to eliminate subprocess latency and improve integration with the ML ecosystem (`librosa`, `torch`).
- **Real-time Playback & Mixing:** The native C++ engine (`hymn_player_ext`) has been enhanced with a real-time `fluid_audio_driver` and supports real-time multi-channel mixing (`set_channel_volume`) for the Studio V5 interface.
- **Psy-Mono Pipeline:** This is the core algorithmic psytrance engine. It focuses on extracting melodic intervals from hymns and mapping them to a high-velocity 145 BPM grid.
- **Neural Synthesis:** We use Suno and Udio as "texture mappers." To ensure high-quality output, we render "transient-only" MIDI files (dry, staccato sines) for AI conditioning. Suno is the primary service as of v1.36.0.
- **AI Service Tuning:** Optimal parameters for hymn-based remixes are: Suno (Audio Influence), Udio (`audio_influence=0.35`, `prompt_strength=0.65`, `manual_mode=True`).
- **FFmpeg for Audio-Visuals:** FFmpeg remains the backbone for final assembly, vocal processing, and creating audio-reactive visuals (kaleidoscope, line, cline modes).
- **Native C++ Engine:** The `HymnPlayer` engine (pybind11 wrapper around FluidSynth) provides fast, thread-safe rendering and is optimized for the Python `PsyGenerator` output.
- **Vocal Alignment:** Vocal grid-locking uses automated ratio-based time-stretching to snap any input BPM to the 145 BPM project grid without pitch artifacts.
- **Quality Metrics:** The `QualityEvaluator` uses a weighted heuristic (50% Rhythm, 30% Brightness, 20% Dynamics) to score tracks, ensuring generated psytrance meets festival-grade spectral profiles.
- **Live Performance State:** Studio V5 maintains an ephemeral state for live jams; using "Load Studio" from the Library hydrates this state with specific track metadata and pre-calculated quality scores.
