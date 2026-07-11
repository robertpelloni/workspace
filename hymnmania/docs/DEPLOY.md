# Deployment & Environment Setup

## Prerequisites

### System Dependencies
- **FFmpeg**: For video assembly, audio-reactive visualizers, and time-stretching.
- **FluidSynth**: For MIDI rendering.
- **Node.js (v18+)**: For the algorithmic psytrance pipeline.
- **Python (v3.10+)**: Core application logic.

### API Keys
Set these in a `.env` file in the project root:
- `GEMINI_API_KEY`: For metadata and art generation.
- `REPLICATE_API_TOKEN`: For MusicGen fallback.
- `ELEVENLABS_API_KEY`: For vocal generation.
- `UDIO_AUTH_TOKEN` / `UDIO_CLIENT_ID` / `UDIO_CLIENT_SECRET`: For Udio remakes.
- `SUNO_SESSION_TOKEN`: For Suno remakes.

## Installation

### Local Setup
1. Clone the repository.
2. Install Python dependencies: `pip install -r hymn_remaker/requirements.txt`.
3. Install Node.js dependencies: `npm install`.
4. Build the native C++ engine: `make`.

### Docker (Recommended)
```bash
docker compose up --build
```

## Running the Pipeline
- **Streamlit UI**: `python -m streamlit run hymn_remaker/app.py`
- **Daemon Mode**: `python hymn_remaker/main.py --daemon`
