# Deployment & Environment Setup

## v1.37.0 Prerequisites

### System Dependencies
- **FFmpeg**: For video assembly, audio-reactive visualizers, and time-stretching.
- **FluidSynth**: For MIDI rendering.
- **Node.js (v18+)**: For the algorithmic psytrance pipeline.
- **Python (v3.12+)**: Core application logic.

### Studio Reversal Dependencies (v1.37.0)
- **Demucs**: For stem separation.
- **Basic-Pitch**: For audio-to-MIDI extraction.
- **Ableton Live**: To use the `Psy-Mono Bridge` assembly features.
- **AbletonOSC**: Must be installed in Ableton's Remote Scripts folder.
- **pylive**: Python library for OSC communication.

### API Keys
Set these in a `.env` file in the project root:
- `GEMINI_API_KEY`: For metadata and art generation.
- `REPLICATE_API_TOKEN`: For MusicGen fallback.
- `ELEVENLABS_API_KEY`: For vocal generation.
- `UDIO_AUTH_TOKEN` / `UDIO_CLIENT_ID` / `UDIO_CLIENT_SECRET`: For Udio remakes.
- `SUNO_SESSION_TOKEN`: For Suno remakes (Web Session Mode).

## Installation

### Local Setup
1. Clone the repository and submodules: `git clone --recursive`.
2. Install Python dependencies: `pip install -r hymn_remaker/requirements.txt`.
3. Install reversal tools: `pip install demucs basic-pitch pylive`.
4. Install Node.js dependencies: `npm install`.
5. Build the native C++ engine: `make` (requires `libfluidsynth-dev` and `pybind11`).

### Docker (Recommended)
```bash
docker compose up --build
```

## Running the Pipeline
- **Streamlit UI**: `python -m streamlit run hymn_remaker/app.py`
- **Daemon Mode**: `python hymn_remaker/main.py --daemon`
- **Matrix Mode**: `python hymn_remaker/main.py --suno-matrix --input-dir hymn_remaker/input/test`

## Packaging for Deployment
To bundle outputs for user review:
```bash
python scripts/package_outputs.py --output bundle.zip
```
