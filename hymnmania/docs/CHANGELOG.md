# Changelog

## [1.35.0] - 2026-06-01
### Added
- **Interactive Live Streaming Engine:**
    - Implemented `InternalMidiPort` wrapper to bridge C++ audio engine with MIDI streaming logic.
    - Upgraded `PsyGenerator.stream_to_port` to support real-time parameter reactivity via dynamic config getters.
    - Added "Live Internal Streaming" to the Studio UI, allowing seamless parameter updates (BPM, Density, Style) during playback.
- **Panic Mechanism:**
    - New "🚨 PANIC (Stop All)" button in the UI to instantly kill all active notes and stop streaming threads.

## [1.34.0] - 2026-05-31
### Added
- **Real-time MIDI I/O Integration:**
    - Integrated `python-rtmidi` and `mido` for external hardware/controller support.
    - Added MIDI Input & Output port selection to the "Live Psy-Mono Studio" UI.
    - Implemented a background MIDI listener to map hardware CC messages (e.g., Mod Wheel, Brightness) to engine parameters.
- **Sequencer Streaming Engine:**
    - New `stream_to_port` method in `PsyGenerator` for continuous, low-latency MIDI streaming to external VSTs or synths.
    - Added `generate_bar_messages` for granular bar-by-bar generation, enabling live parameter updates during playback.

## [1.33.0] - 2026-05-30
### Added
- **Style Presets & Model Refinement:**
    - Integrated **Algorithmic Style Presets** (Full-On, DarkPsy, Progressive, Morning) into `psy_sequencer.py` to automatically configure Euclidean density and gallop patterns.
    - Added a **Model Refinement & Feedback** system in the Studio UI to capture star ratings and text feedback, stored in `output/feedback_log.jsonl` for continuous improvement.
- **Studio Rendering & Export:**
    - New **Export & Render** suite allows users to render their live studio jams directly to MP4 videos with audio-reactive visuals (Kaleidoscope, Avectorscope, etc.) and download the generated MIDI files.
- **Enhanced Performance Controls:**
    - Re-engineered the **Psy-Energy Macro** to simultaneously control Filter Cutoff, Resonance, and Global Gain for high-intensity live performance.

## [1.32.0] - 2026-05-28
### Added
- **Studio V5: Live Jam Edition:**
    - Integrated **Novel AI Generation** (Local MusicGen) directly into the studio for text-to-audio production.
    - Added **Manual FX & Jam Triggers** (Crash Cymbal, Rising Sweep, Acid Fill) for real-time performance.
    - Enhanced the **Real-time Mixer** with Global Gain control.
- **Output Library Management:**
    - New "Library" tab to manage generated tracks.
    - Integrated **Quality Evaluator** providing a 0-100 score for tracks based on brightness, rhythmic clarity, and dynamic range.
    - "Load Studio" functionality to instantly bring library tracks into the live Jam environment.
- **C++ Engine Optimization:**
    - Optimized `HymnPlayer` for 128-voice polyphony and multi-core CPU utilization.
    - Improved thread safety for high-frequency MIDI event handling.
- **Automated Verification Suite:** Integrated Playwright-based frontend testing and comprehensive module verification scripts.

## [1.31.0] - 2026-05-23
### Added
- **Studio V4: Arrangement Edition:** Introduced a 56-bar structured arrangement mode (Intro -> Verse -> Build -> Drop -> Outro) with automated energy curves.
- **Real-time Performance & Automation:**
    - Added native C++ bindings for `send_cc`, `send_note_on`, and `send_note_off` to the `HymnPlayer` engine.
    - Implemented UI-driven automation for Filter Cutoff (CC 74) and Resonance (CC 71).
    - Added manual FX trigger buttons for Crash Cymbals and Rising Sweeps.
- **Kaleidoscope Visualizer:** New audio-reactive video rendering mode using recursive FFmpeg symmetry filters to create psychedelic visuals synchronized to the BPM.
- **Performance Optimizations:**
    - Enabled **FP16 (Half-Precision)** for local MusicGen inference on CUDA.
    - Integrated **Intel IPEX** hooks for CPU-bound ML acceleration.

### Fixed
- **UI Module Unpacking:** Resolved a critical `ValueError` in `app.py` by correctly synchronizing return values from `load_modules()`.
- **Vocal Grid-Locking:** Corrected the time-stretch ratio calculation in `vocal_remix.py` to ensure hip-hop vocals lock perfectly to the 145 BPM grid.

## [1.30.0] - 2026-05-22
### Added
- **Python-Native Psy-Sequencer:** Ported the algorithmic psytrance generation logic from TypeScript to Python (`hymn_remaker/src/psy_sequencer.py`), enabling low-latency integration with the Streamlit UI and removing Node.js overhead for the core pipeline.
- **Enhanced C++ Audio Engine:** Added real-time `set_gain()` and `set_channel_volume()` bindings to the `hymn_player_ext` FluidSynth wrapper, enabling dynamic mixing during playback.
- **Vocal Grid-Locking & LALAL.AI Integration:** Implemented a dedicated `VocalRemixPipeline` in Python (`hymn_remaker/src/vocal_remix.py`) with automated time-stretching and pitch-shifting. Integrated the LALAL.AI REST API (`hymn_remaker/src/lalal_api.py`) as a high-fidelity cloud fallback for vocal isolation.
- **Live Studio V3:**
    - Integrated a **Plotly Piano Roll** visualizer for real-time pattern inspection.
    - Added a **Multi-Channel Mixer** in the UI to control individual volume levels for Kick, Bass, and Lead tracks via the upgraded C++ engine.
    - Enhanced the arpeggiator with **Markov-Chain transition rules** for more organic and evolving lead melodies.
- **Unified Versioning:** Centralized version control to `VERSION` and mirrored in `hymn_remaker/VERSION.md`.

### Changed
- **Architecture Shift:** Migrated core symbolic music generation from TypeScript to Python for tighter integration with the ML ecosystem (`librosa`, `torch`).
- **Streamlit Optimization:** Replaced legacy subprocess calls to `ts-node` with direct Python imports, drastically improving UI responsiveness.
- **Merge & Sync:** Reconciled upstream changes and consolidated the codebase across hybrid Python/C++ boundaries.

## [1.28.0] - 2026-05-21
### Added
- **Live Psy-Mono Studio:** Interactive Streamlit tab for real-time algorithmic psytrance parameter tweaking.
- **Real-time Audio Input (pYIN):** Microphone recording and monophonic melody transcription using librosa's pYIN algorithm.
- **Native C++ Real-time Bindings:** Upgraded `HymnPlayer` engine with `fluid_audio_driver` for low-latency system audio output.
- **Local Generative AI:** Integrated `facebook/musicgen-melody` via HuggingFace Transformers for offline, on-device audio rendering.
- **YouTube Audio Extraction:** Native `yt-dlp` integration for pulling hip-hop vocals directly from URL into the remix pipeline.
- **High-Fidelity Export:** Offline WAV rendering module for exporting studio sessions with 44.1kHz stereo quality.

### Changed
- **Security Hardening:** Refactored all CLI-based integrations (FFmpeg, Demucs, yt-dlp) to use argument arrays, mitigating shell injection vulnerabilities.
- **Pipeline Orchestration:** Optimized `main.ts` with `--transpile-only` and better error handling for seamless cross-language execution.

## [1.27.0] - 2026-05-20
### Added
- **Algorithmic Psytrance Pipeline (Psy-Mono):** Initial implementation of a symbolic music generation engine in TypeScript.
- **Hymn DNA Extraction:** Logic to extract chord roots and melodic patterns from MIDI/MusicXML hymns.
- **Procedural Psytrance Generation:** Algorithmic rolling basslines (K-B-B-B) and Euclidean arpeggio gating.
- **Vocal Remix Pipeline:** Automated isolation, time-stretching, and pitch-shifting of hip-hop vocals for psytrance integration.
- **TypeScript/Node.js Environment:** Added a TypeScript-based symbolic processing layer to the project.

### Changed
- Shifted project philosophy from "black box" AI audio generation to hybrid symbolic-algorithmic composition + neural texture mapping.
- Updated documentation across the entire project to reflect the new Psy-Mono architecture.
