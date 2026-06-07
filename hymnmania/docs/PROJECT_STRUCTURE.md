# Project Structure

## Directory Layout
```
/
├── docs/                   # Omni-Workspace and project-specific documentation.
├── hymn_remaker/           # Core application folder.
│   ├── input/              # Drop MIDI files here.
│   ├── output/             # Generated WAVs, MP4s, and JSON metadata.
│   ├── src/                # Pipeline modules.
│   │   ├── content_generator.py # OpenAI GPT/DALL-E logic.
│   │   ├── midi_renderer.py     # FluidSynth logic.
│   │   ├── remaker.py           # Replicate MusicGen logic.
│   │   ├── tts_generator.py     # ElevenLabs logic.
│   │   ├── utils.py             # Audio mixing and retries.
│   │   └── video_uploader.py    # FFmpeg and YouTube API logic.
│   ├── app.py              # Streamlit Web UI.
│   ├── main.py             # CLI Entrypoint.
│   └── tests/              # Pytest suite.
├── scripts/                # Utility scripts (e.g., test midi generation).
└── VERSION                 # Global Single Source of Truth for the version.
```

## Submodules / External Dependencies
-   **OpenAI**: API (gpt-4-turbo, dall-e-3)
-   **Replicate**: API (meta/musicgen-melody)
-   **ElevenLabs**: API
-   **FluidSynth**: System Dependency
-   **FFmpeg**: System Dependency
# Project Structure & Submodules

This document provides a comprehensive overview of the Hymn Remaker directory layout, the purpose of each component, and the external libraries, APIs, and submodules utilized within the Omni-Workspace.

## Directory Layout

```text
hymnmania/
├── VERSION                     # Global version source of truth (e.g., 1.15.0).
├── Makefile                    # Build script for the native C++ HymnPlayer engine.
├── Dockerfile                  # Multi-stage container build targeting Pybind11.
├── docker-compose.yml          # Orchestrates UI, Daemon, and Streamer services.
├── docs/                       # Comprehensive Omni-Workspace documentation suite.
│   ├── AGENTS.md               # Overview of AI agent roles and workflows.
│   ├── UNIVERSAL_LLM_INSTRUCTIONS.md # Core instructions that all models must obey.
│   ├── CLAUDE.md / GPT.md      # Model-specific overrides and prompts.
│   ├── VISION.md               # Ultimate project goals and design philosophy.
│   ├── ROADMAP.md              # Long-term phases and architectural goals.
│   ├── TODO.md                 # Immediate, actionable developer tasks.
│   ├── IDEAS.md                # Creative brainstorms and feature expansions.
│   ├── MEMORY.md               # Technical observations and workflow preferences.
│   ├── DEPLOY.md               # Instructions for system prep, Docker, and API keys.
│   ├── CHANGELOG.md            # Version history following "Keep a Changelog".
│   ├── HANDOFF.md              # State summary passed between AI sessions.
│   ├── SUBMODULE_DASHBOARD.md  # Dashboard of conceptual submodules and APIs.
│   ├── VERSION.md              # Mirrored version file for documentation links.
│   └── PROJECT_STRUCTURE.md    # This file.
├── hymn_remaker/               # Primary Python application package.
│   ├── main.py                 # The core orchestrator and daemon loop.
│   ├── app.py                  # The Streamlit Web UI and Hymn Editor Tab.
│   ├── settings.py             # Centralized constants, fallback paths, and API defaults.
│   ├── requirements.txt        # Hard-pinned Python dependencies.
│   ├── input/                  # Monitored by watchdog for incoming MIDI/MXL/PDF/PNG files.
│   ├── output/                 # Destination for final .mp4 videos, stems, and Shorts.
│   └── tests/                  # Pytest suite for the Python pipeline.
│       └── test_*.py           # Mocks and unit tests for pipeline components.
├── src/                        # Cross-language source files and utilities.
│   ├── engine/                 # Native C++ Audio Engine.
│   │   ├── HymnPlayer.h        # Header defining the FluidSynth wrapper class.
│   │   ├── HymnPlayerBinding.cpp # Pybind11 bridge exposing C++ to Python.
│   │   └── HymnPlayer.cpp      # Implementation of native audio loading and rendering.
│   ├── musicxml_parser.py      # Parses .mxl/.xml natively to extract exact lyric timestamps.
│   ├── omr_processor.py        # Utilizes ONNX/OpenCV (oemer) to translate physical sheet music.
│   ├── stem_separator.py       # Utilizes Facebook's Demucs to isolate drums/bass/vocals/melody.
│   ├── radio_streamer.py       # Background FFmpeg RTMP Live streamer daemon.
│   └── video_uploader.py       # Python module for FFmpeg assembly and YouTube OAuth.
├── tests/                      # Native C++ tests.
│   └── HymnPlayerTests.cpp     # Unit tests for the C++ engine (builds to `run_tests`).
└── .cache/                     # Local caching directory.
    └── art/                    # Stores DALL-E generated images (hashed by prompt).
```

## System Submodules & Dependencies (Native)
While this repository does not use Git `.gitmodules`, its architecture is heavily reliant on deeply integrated system-level submodules and frameworks:
*   **FluidSynth** (`libfluidsynth-dev`): Required for the C++ `HymnPlayer` engine to parse MIDI data and render audio buffers natively using SoundFonts (`.sf2`).
*   **FFmpeg**: The multimedia backbone. It handles audio mixing, `atempo` vocal time-stretching, `scale`/`pad` aspect ratio conversions, `showwaves` audio-reactive visualizers, SRT subtitle burning, and RTMP live streaming.
*   **Pybind11**: Acts as the compilation bridge linking the `HymnPlayer.cpp` logic to the `hymn_remaker/main.py` Python orchestrator.

## External Intelligence Submodules (APIs & Libraries)
*   **music21**: Extracts mathematically perfect timestamps from MusicXML (`.mxl`) note offsets, completely bypassing AI hallucinations for SRT generation.
*   **oemer**: An ONNX-backed Optical Music Recognition (OMR) library that translates `.pdf`, `.jpg`, and `.png` physical sheet music scans into raw `.mxl` files.
*   **demucs**: Facebook's PyTorch-backed source separation library. It splits the generated house tracks into four stems (`drums`, `bass`, `vocals`, `other`), allowing the pipeline to duck the melody volume during singing while keeping the drum beat intact.
*   **OpenAI (`gpt-4-turbo`, `dall-e-3`)**: Used to generate SEO-optimized titles, descriptions, contextual lyrics, and MD5-cached cover art.
*   **Replicate (`musicgen-melody`)**: Transforms the raw FluidSynth audio render into a stylized Deep House track perfectly locked to the `.mxl`'s native BPM.
*   **ElevenLabs**: Generates hyper-realistic vocal tracks. The pipeline dynamically shifts the pitch (`+4`, `+7` semitones) of secondary voices to construct 3-part spatial harmonies.
*   **YouTube Data API v3**: Automatically publishes completed videos to the user's channel via OAuth2.