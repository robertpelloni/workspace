# Deployment Instructions

## Docker Compose (Recommended)
1. Ensure Docker Desktop is running.
2. In the project root, run: `docker compose up --build -d`
3. Access the Streamlit UI at `http://localhost:8501`.

## Local Virtual Environment
*Note: This project targets Python 3.12.*

1. Ensure `ffmpeg`, `fluidsynth`, `libfluidsynth-dev`, and `fluid-soundfont-gm` are installed on your OS (`sudo apt install ffmpeg fluidsynth libfluidsynth-dev fluid-soundfont-gm`).
2. Run `pip install -r requirements.txt`.
3. Compile the `pybind11` C++ engine extension from the project root by running `make`.
4. Start the UI: `python -m streamlit run app.py`

## User Testing (v1.37.0)
1. Download the `v137_testing_bundle.zip`.
2. Extract to a local directory.
3. Import the contents of the `audio/` and `midi/` folders into your DAW (e.g., Ableton Live) to verify the "Reverse Engineering" quality.
4. Launch the Hymnmania Studio and use the **Library** tab to audition the "Official v1.37.0 Demos" and provide feedback using the integrated star ratings and comments.

## Integration Testing (v1.37.0 Benchmarks)
- **Baseline Integration:** Verified on Ubuntu 22.04 with Python 3.12.
- **Pipeline Latency:** ~2.5s for local symbolic processing and dry rendering of a 30s hymn.
- **Artifact Validation:** High-fidelity 16-bit PCM WAVs (Dry) and quantized 480 PPQ MIDI (Norm) confirmed.
