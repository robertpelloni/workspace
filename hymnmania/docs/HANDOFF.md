# Handoff - Version 1.36.0 (Suno Transition & Psy-Mono Finalization)

## Session Summary
Completed the strategic transition of the primary AI music generation service from Udio to **Suno**, while simultaneously finalizing the Psy-Mono production pipeline. The system now prioritizes Suno for its superior melody retention and high-fidelity electronic output, while maintaining Udio and Local MusicGen as robust fallbacks. This release marks the completion of the v1.36.0 milestone.

## Major Changes
- **Suno Integration:**
    - `main.py`: Reordered remake priority to place Suno first.
    - `api.py` / `app.py`: Set Suno as the default AI remake service.
    - `suno_remaker.py`: Fixed critical method call bug (`upload_audio`).
- **Psy-Mono Studio V5 Finalization:**
    - Integrated algorithmic psytrance sequencing (v1.36.0) with real-time parameter tweaking.
    - Added "Performance Mode" to Streamlit UI for cleaner live jamming.
- **Workflow & Sync:**
    - Performed a comprehensive sync-merge with all active GitHub branches (`master` and `psy-mono-pipeline-1.27.0-9908176330949525010`).
    - Resolved complex conflicts in core modules (`main.py`, `app.py`, `midi_renderer.py`) while preserving Suno-first orchestration.

## Verification Status
- Verified Suno priority logic via mock unit tests (`tests/test_suno_priority.py`).
- Verified Udio fallback mechanism via simulated API failures (`tests/test_suno_fallback.py`).
- Full end-to-end pipeline run successful for both Suno and Local MusicGen modes.

# Handoff - Version 1.35.0 (Interactive Live Parameters & Internal Streaming)

## Session Summary
Achieved full real-time interactivity for the Psy-Mono pipeline. Parameters like BPM, Euclidean Density, and Gallop Variant now update the sequence on the next bar without stopping playback. This was accomplished by bridging the C++ engine via an `InternalMidiPort` and upgrading the streaming engine to use dynamic config getters.

## Major Changes
- **Interactive Streaming:**
    - `psy_sequencer.py`: Added `InternalMidiPort` and dynamic `config` support in `stream_to_port`.
    - `app.py`: Integrated `get_live_config` callback into streaming threads.
- **Panic & Safety:**
    - Added a global "Panic" button that sends CC 123 (All Notes Off) to the C++ engine and halts all streaming threads.
- **Workflow Optimization:**
    - The "GENERATE & PLAY" button now triggers low-latency internal streaming while still generating a persistent MIDI file in the background for download/visuals.

## Verification Status
- Verified parameter update reactivity via unit tests (`tests/test_psy_live.py`).
- Verified UI stability and "Panic" button visibility via Playwright screenshots.

# Handoff - Version 1.34.0 (Real-time MIDI I/O & Streaming)

## Session Summary
Successfully integrated real-time MIDI I/O capabilities into the Psy-Mono pipeline. The system now supports external hardware controllers and can stream generated sequences to external VSTs/synths. The `PsyGenerator` was upgraded with a streaming engine, and the Streamlit UI now includes a dedicated "External MIDI Control" section.

## Major Changes
- **MIDI I/O Integration:**
    - `python-rtmidi` added to dependencies.
    - `app.py`: Added MIDI Input/Output selection and background callback listeners.
- **Sequencer Streaming Engine:**
    - `psy_sequencer.py`: Added `stream_to_port` and `generate_bar_messages`.
    - Supports live parameter updates (Density, Gallop, Style) by regenerating the sequence bar-by-bar.
- **Hardware Mapping:**
    - Pre-configured mapping for CC 1 (Mod Wheel) to Global Energy and CC 74 (Brightness) to Filter Cutoff.

## Verification Status
- Verified UI elements (dropdowns, info messages) via Playwright.
- Verified `mido`/`rtmidi` library presence and basic functionality.
- Unit tests for `generate_bar_messages` passed.

# Handoff - Version 1.33.0 (Optimization, Analytics & Final Refinement)

## Session Summary
Reached a major milestone with the release of v1.33.0. The system has matured into a production-ready "Hymn-to-Psytrance" pipeline. This session focused on closing the loop between algorithmic generation and user satisfaction through an Integrated Optimization & Analytics suite, as well as refining the live performance capabilities with high-intensity macros and real-time monitoring.

## Major Changes
- **Algorithmic Style Presets & Model Refinement:**
    - Integrated logic in `psy_sequencer.py` to support multi-style generation (Full-On, DarkPsy, Progressive, Morning).
    - Implemented a **Feedback & Refinement System** in the UI to collect data for continuous model tuning.
- **Optimization & Analytics (Tab 5):**
    - Built an A/B/C/D testing framework for parameter sweeps.
    - Added a Plotly-based analytics dashboard to correlate user preferences with generation parameters.
- **Performance & Monitoring:**
    - Added a **Performance Mode** toggle to declutter the UI for live use.
    - Integrated a **Real-time MIDI Event Log** for monitoring engine activity.
    - Re-engineered the **Psy-Energy Macro** for unified control over intensity (Filters + Gain).
- **Video Rendering & Export:**
    - Enhanced the `rendering` module to support MP4 exports with kaleidoscope-based audio-reactive visuals.

## Environment & Infrastructure
- Centralized versioning in root `VERSION`.
- C++ Engine (`hymn_player_ext`) verified for 128-voice stability.
- Streamlit UI (`hymn_remaker/app.py`) optimized for multi-tab state persistence.

## Verification Status
- Verified UI Performance Mode and Analytics Tab via Playwright screenshots.
- Verified Style Preset logic and MIDI generation stability.

# Handoff - Version 1.32.0 (Studio V5 & Library Management)

## Session Summary
Completed the "Live Jam" evolution of the Hymnmania pipeline. Studio V5 now supports real-time FX triggers, text-to-audio novel generation, and a comprehensive library management system with automated quality scoring. The C++ engine has been tuned for high polyphony, and the UI is fully synchronized for multi-track mixing and live performance.

## Major Changes
- **Studio V5: Live Jam Edition:**
    - Real-time manual triggers for Acid Fills, Rising Sweeps, and Crash Cymbals via MIDI CC/Note events in the C++ engine.
    - Integrated "Novel AI" mode for pure text-to-psytrance generation using local MusicGen.
- **Library & Quality Evaluator:**
    - `hymn_remaker/src/quality_evaluator.py`: Automated 0-100 scoring based on spectral/rhythmic features.
    - Persistent library UI with "Load Studio" and deletion capabilities.
- **Optimized Local ML:**
    - MusicGen now runs in FP16 with IPEX/CUDA optimizations, supporting faster iterations.
- **Frontend Verification:**
    - Established a Playwright-based verification suite for UI regression testing.

# Handoff - Version 1.30.0 (Python-Native Psy-Mono Studio & Mixer)

## Session Summary
Successfully transitioned the core "Psy-Mono" pipeline to a high-performance Python-native implementation, eliminating Node.js overhead for the real-time studio. Upgraded the C++ audio engine with multi-channel volume control and implemented a sophisticated vocal alignment pipeline for hip-hop remixes.

## Major Changes
- **Python-Native Psy-Sequencer:**
    - `hymn_remaker/src/psy_sequencer.py`: Ported TypeScript logic to Python using `mido`. Supports instant pattern generation for Kick, Rolling Bass (3 variants), and Euclidean Arpeggios.
- **Enhanced C++ Engine (`hymn_player_ext`):**
    - Added `set_gain(float)` and `set_channel_volume(int, float)` bindings.
    - Enables real-time mixing of separate tracks directly from the Streamlit UI.
- **Vocal Remix Pipeline:**
    - `hymn_remaker/src/vocal_remix.py`: Uses `yt-dlp` for downloads, `Demucs` for isolation, and `librosa` for grid-locking.
    - **Grid-Locking:** Automated calculation of time-stretch ratios to snap vocals to 145 BPM.
    - **Harmonic Alignment:** Automated pitch-shifting of vocals to match the detected hymn root key.
- **Live Studio V3:**
    - `hymn_remaker/app.py`: Integrated **Plotly Piano Roll** for visual feedback.
    - Interactive Mixer: Real-time volume sliders for Kick, Bass, and Lead tracks.
- **Unified Versioning:**
    - Centrally managed version `1.30.0` in root `VERSION` and `hymn_remaker/VERSION.md`.

## Environment Updates
- **Python:** Added `mido`, `plotly`.
- **C++:** Recompiled `hymn_player_ext.so` with new Mixer API.

## Verification Status
- Verified Python sequencer MIDI output via `verify_midi.py`.
- Verified C++ Mixer bindings via `verify_bindings.py`.
- Verified `main.py` integration with the new Python pipeline.
- Verified file presence and version consistency across the repo.

# Handoff - Version 1.28.0 (Live Psy-Mono Studio & Real-time Integration)

## Session Summary
Completed the transformation of Hymnmania into a full-fledged hybrid music production system. The "Psy-Mono" pipeline is now fully interactive, featuring a live studio UI, real-time audio output via a native C++ engine, and support for both local and cloud-based generative AI rendering.

## Major Changes
- **Live Psy-Mono Studio:**
  - `hymn_remaker/app.py`: New tab for real-time parameter tweaking of the algorithmic psytrance sequencer.
  - `hymn_player_ext`: Upgraded C++ engine with `fluid_audio_driver` for low-latency real-time system audio playback.
  - Interactive sliders for BPM, Euclidean density, gallop variants, and track mixer (Kick/Bass/Lead).
- **Real-time Audio Input:**
  - `hymn_remaker/src/audio_to_midi.py`: Implemented monophonic melody transcription using librosa's **pYIN algorithm**.
  - `app.py`: Integrated `streamlit-mic-recorder` for capturing live user humming/singing.
- **Vocal Remix & YouTube Pipeline:**
  - `src/integrators/vocal_processor.ts`: Automated hip-hop vocal isolation (Demucs) and grid-locking (FFmpeg).
  - Native `yt-dlp` integration for pulling hip-hop vocals directly from YouTube URLs.
- **Generative AI Overhaul:**
  - `hymn_remaker/src/local_remaker.py`: Integrated `facebook/musicgen-melody` for local, on-device audio generation.
  - Refactored `UdioRemaker` and `UdioOAuthRemaker` for better stylistic consistency via the "Udio Extension Hack."
- **Security & Reliability:**
  - **Security Hardening:** Refactored all external CLI calls (FFmpeg, yt-dlp, Demucs, ts-node) to use secure argument arrays, mitigating shell injection vulnerabilities.
  - Optimized Node.js execution using `npx ts-node --transpile-only` for faster, cross-platform orchestration.

## Environment Updates
- **System:** `libfluidsynth-dev`, `ffmpeg`, `yt-dlp`.
- **Python:** `librosa`, `torch`, `transformers`, `streamlit-mic-recorder`, `pYIN`.
- **Node.js:** `@tonejs/midi`, `commander`, `lodash`.

## Verification Status
- Verified pYIN transcription accuracy via `verify_end_to_end.py`.
- Verified native C++ bindings for real-time and offline rendering.
- Verified Local MusicGen inference on CPU.
- Verified UI functional wiring and layout via Playwright screenshots.
- All core Python tests passed.

## Outstanding Items / Next Steps
- Implement LALAL.AI REST API as a fallback for cloud-based stem isolation.
- Optimize local AI model weights to INT8/FP16 for reduced latency.
- Integrate a VST3 host into the C++ engine for high-end local instrument rendering.

--- Newly Discovered Project Context ---
--- Context from: C:/Users/jakeg/workspace/hymnmania/docs/GEMINI.md ---
# Gemini Specific Instructions

> **CRITICAL**: Before reading this, you MUST read and adhere to `docs/AGENTS.md`.

## Strengths
*   You excel at scanning the entire repository context rapidly.
*   You are great at scripting out massive directory restructurings or complex multi-file logic changes.

## Directives
*   When performing large refactors in this repo, leverage your large context window to double-check that you haven't broken any cross-references in the UI (`app.py`) or the CLI (`main.py`).
--- End of Context from: C:/Users/jakeg/workspace/hymnmania/docs/GEMINI.md ---
--- End Project Context ---
