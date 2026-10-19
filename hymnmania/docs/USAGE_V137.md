# Hymnmania v1.37.0 - Usage Instructions

This document provides instructions for using the new "Studio Reversal" and "Suno Experiment Matrix" features introduced in v1.37.0.

## 1. Automated Pipeline (CLI)

You can trigger the new experimental preprocessors and Suno matrix via the command line.

### Suno Experiment Matrix
Run a 9-way experiment (3 speeds x 3 genres) for a specific hymn:
```bash
python3 hymn_remaker/main.py --input-dir hymn_remaker/input/ --suno-matrix
```

### Preprocessing Variants
Use specific preprocessors individually:
- **Sonic Vacuum (Dry Render):** `--sonic-vacuum`
- **Symbolic Norm:** `--symbolic-norm`
- **House Quantizer:** `--house-quantizer`

Example with custom speed:
```bash
python3 hymn_remaker/main.py --input-dir hymn_remaker/input/ --sonic-vacuum --speed 2.0
```

## 2. Studio Reversal (AI-to-DAW)

The "Reverse to Ableton" feature is accessible via the **Library** tab in the Streamlit UI.

### Manual Workflow
If running programmatically via `PsyMonoBridge`:
```python
from hymn_remaker.src.psy_mono_bridge import PsyMonoBridge

bridge = PsyMonoBridge()
bridge.run_full_reversal("path/to/ai_generated.wav", "output/directory")
```
**Requirements:**
- `demucs` and `basic-pitch` must be installed.
- Ableton Live must be running with the `AbletonOSC` plugin on port 11000.

## 3. Streamlit Interface

### v1.37.0 Highlights
- **Welcome Tab:** Overview of new features.
- **Tab 1 (Automated Pipeline):** New "Preview Preprocessing" button to audition local renders before committing AI credits.
- **Tab 4 (Library):**
    - **Official Demos:** Pre-generated high-quality examples.
    - **Reverse Button:** Click to trigger the stem separation and MIDI extraction pipeline.
- **Tab 5 (Optimization):** "System Health Audit" to verify binary and library compatibility.

## 4. Troubleshooting
- If "Reverse to Ableton" fails, ensure `ffmpeg` and `fluidsynth` are in your system PATH.
- Verify AbletonOSC connectivity in the `PsyMonoBridge` logs.
