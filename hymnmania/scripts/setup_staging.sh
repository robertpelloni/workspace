#!/bin/bash
# setup_staging.sh - v1.37.0 Staging Deployment Script

set -e

echo "--- Hymnmania Staging Deployment ---"

# 1. Clean Staging Directories
echo "Cleaning staging workspace..."
rm -rf staging_input staging_output
mkdir -p staging_input staging_output

# 2. Python Environment & Dependencies
echo "Ensuring Python environment is up to date..."
pip install -r hymn_remaker/requirements.txt
pip install demucs basic-pitch pylive requests_oauthlib diffusers accelerate flask

# 3. Environment Variables Check
echo "Checking staging environment variables..."
if [ -z "$GEMINI_API_KEY" ]; then echo "[WARN] GEMINI_API_KEY not set"; fi
if [ -z "$REPLICATE_API_TOKEN" ]; then echo "[WARN] REPLICATE_API_TOKEN not set"; fi

# 4. System Audit
echo "Executing system health audit..."
python3 scripts/health_check.py

echo "Staging deployment complete. Use scripts/automated_validation.sh to run tests."
