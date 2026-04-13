# Comprehensive Project Summary: Hymn Remaker Pipeline

## 1. Project Overview & Vision
The **Hymn Remaker** is an automated, AI-driven pipeline designed to convert public domain classical and religious MIDI files into highly polished, stylized music videos (e.g., Deep House, Synthwave). Operating as a node within the larger Robert Pelloni "Omni-Workspace," it is built for zero-touch autonomy from input to YouTube upload.

## 2. Architecture & Pipeline Stages
The application is structured sequentially as a pipeline, primarily orchestrated by `hymn_remaker/main.py` and accessed via CLI or a Streamlit Web UI (`hymn_remaker/app.py`).

*   **Stage 1: MIDI Rendering (`src/midi_renderer.py`)**
    *   Uses `midi2audio` wrapping `fluidsynth` to render `.mid` to `.wav`.
    *   Relies on a system-level SoundFont (default: `/usr/share/sounds/sf2/FluidR3_GM.sf2`).
*   **Stage 2: Audio Remaking (`src/remaker.py`)**
    *   Uses the `replicate` API to interact with Meta's `musicgen-melody` model.
    *   Takes the rendered WAV and a stylistic text prompt to generate a new musical arrangement conditioned on the original melody.
*   **Stage 3: Content Generation (`src/content_generator.py`)**
    *   **Metadata & Lyrics:** Uses OpenAI `gpt-4-turbo` with JSON mode to generate YouTube titles, descriptions, tags, and timestamped lyrics.
    *   **Album Art:** Uses OpenAI `dall-e-3`. *Design Decision:* Art is now locally cached to `hymn_remaker/.cache/art/` using an MD5 hash of the prompt to drastically reduce API costs on repeated runs.
*   **Stage 4: Vocal Synthesis (`src/tts_generator.py`)**
    *   Uses the `elevenlabs` API to generate spoken/sung vocals from the generated lyrics.
    *   *Design Decision:* Highly configurable via `voice_id` and `model` parameters, mapped through the UI/CLI.
    *   Vocals are mixed with the instrumental track using `pydub`, applying volume ducking to the instrumental.
*   **Stage 5: Video Assembly (`src/video_uploader.py`)**
    *   Uses system-level `ffmpeg` via `subprocess`.
    *   *Pattern:* Includes complex video formatting filters. Supports standard `16:9` and vertical `9:16` (TikTok/Reels) by scaling and padding the square DALL-E image.
    *   *Pattern:* Robust SRT subtitle burning. If FFmpeg fails due to weird characters in the lyrics, it catches the exception, sanitizes the text (ASCII-only), retries, and falls back to no-subtitles if all 3 retries fail.
*   **Stage 6: YouTube Upload (`src/video_uploader.py`)**
    *   Uses the Google/YouTube Data API with OAuth2 (`client_secrets.json`).
    *   *Pattern:* Chunked uploading dynamically reports progress back to the Streamlit UI via a custom callback hook passed down from the orchestrator.

## 3. Key Technical Decisions & Patterns
*   **Aggressive Garbage Collection:** In `process_single_midi`, if an exception occurs mid-pipeline, a `try/except` cleanup block aggressively deletes partially rendered audio/video files. Path variables are initialized to `None` at the top of the scope to prevent `UnboundLocalError`.
*   **Concurrency & State Management:** The Streamlit app uses `concurrent.futures.ThreadPoolExecutor` to process multiple MIDI files simultaneously. It uses `add_script_run_ctx` to safely allow background threads to update UI progress bars (`st.progress`).
*   **Idempotency & Fallbacks:** CLI flags like `--skip-render` and `--skip-remake` allow developers to resume failed pipelines without re-running expensive or slow operations. The local DALL-E cache follows this same philosophy.
*   **Global Versioning:** A single source of truth for the version exists at the workspace root (`VERSION`). The Streamlit app dynamically parses this file.

## 4. Documentation Standards (Omni-Workspace)
The repository adheres strictly to the Robert Pelloni Omni-Workspace documentation protocols:
*   `UNIVERSAL_LLM_INSTRUCTIONS.md` serves as the global law for AI agents.
*   Model-specific files (`CLAUDE.md`, `GEMINI.md`, `GPT.md`) inherit from the universal instructions and outline model-specific strengths.
*   `CHANGELOG.md`, `ROADMAP.md`, `TODO.md`, and `VISION.md` are actively updated during every session to maintain state continuity for the next AI agent or developer.

## 5. Future Roadmap (Phase 3 & 4)
*   **Input Expansion:** Support for MusicXML and Optical Music Recognition (OMR) for sheet music PDFs.
*   **Autonomy:** Implementation of a daemon mode/cron scheduler for headless overnight processing and automated uploads.