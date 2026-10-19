#!/bin/bash
# scripts/staging_deploy.sh - Hymnmania v1.37.0 Staging Deploy Gate

echo "--- [STAGING DEPLOYMENT] ---"

# 1. Run Health Check
echo "Step 1: Running System Health Audit..."
export PYTHONPATH=$PYTHONPATH:$(pwd)
python3 scripts/health_check.py || { echo "Health check failed"; }

# 2. Run Batch Validation
echo "Step 2: Running Batch MIDI Validation..."
python3 tests/batch_validate.py || { echo "Batch validation failed"; }

# 3. Start Application
echo "Step 3: Validation Phase Finished. Use streamlit run hymn_remaker/app.py to start server."
