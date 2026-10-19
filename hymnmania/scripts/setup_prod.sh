#!/bin/bash
# setup_prod.sh - v1.37.0 Production Setup Script

set -e

echo "--- Hymnmania Production Setup ---"

# 1. Update System & Install Binaries
# Note: Requires root or sudo if not in container
echo "Installing system dependencies..."
# apt-get update && apt-get install -y fluidsynth fluid-soundfont-gm ffmpeg rubberband-cli

# 2. Python Environment
echo "Installing Python dependencies..."
pip install -r hymn_remaker/requirements.txt
pip install demucs basic-pitch pylive requests_oauthlib diffusers accelerate flask

# 3. Native Engine Build
echo "Building C++ engine..."
# cd src/engine && make && cd ../..

# 4. Verify Toggles
echo "Running health check..."
python scripts/health_check.py

echo "Production setup complete."
