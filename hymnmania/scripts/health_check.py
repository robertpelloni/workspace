import subprocess
import sys
import os
import logging
import mido
import librosa
import numpy as np
import importlib.util

# Add repo root to path
sys.path.append(os.getcwd())

from pipeline.processing.sonic_vacuum import SonicVacuumProcessor
from hymn_remaker.src.quality_evaluator import QualityEvaluator

logging.basicConfig(level=logging.INFO, format='%(levelname)s: %(message)s')
logger = logging.getLogger("HealthCheck")

def check_binary(name):
    try:
        # Some binaries might return non-zero for --version but still exist
        subprocess.run([name, "-version" if name == "ffmpeg" else "--version"], capture_output=True, check=False)
        logger.info(f"Binary check attempted: {name}")
        # Better check for existence
        from shutil import wheel
        import shutil
        if shutil.which(name):
            return True
        return False
    except FileNotFoundError:
        logger.error(f"Binary NOT found: {name}")
        return False

def check_python_module(module_name):
    try:
        spec = importlib.util.find_spec(module_name)
        if spec is not None:
            logger.info(f"Module found: {module_name}")
            return True
        else:
            logger.error(f"Module NOT found: {module_name}")
            return False
    except Exception as e:
        logger.error(f"Error checking module {module_name}: {e}")
        return False

def smoke_test_pipeline():
    """Run a minimal MIDI through Sonic Vacuum and QualityEvaluator."""
    test_input = "test_input_single/short_hymn.mid"
    test_output_wav = "output_test_batch/smoke_test.wav"
    os.makedirs("test_input_single", exist_ok=True)
    os.makedirs("output_test_batch", exist_ok=True)

    # Create a tiny 1-bar MIDI if it doesn't exist
    if not os.path.exists(test_input):
        mid = mido.MidiFile()
        track = mido.MidiTrack()
        mid.tracks.append(track)
        track.append(mido.Message('note_on', note=60, velocity=100, time=0))
        track.append(mido.Message('note_off', note=60, velocity=0, time=480))
        mid.save(test_input)

    logger.info("Starting Pipeline Smoke Test...")
    try:
        vacuum = SonicVacuumProcessor(test_input)
        vacuum.render_dry_piano(test_output_wav)
        if not os.path.exists(test_output_wav):
            raise RuntimeError("Smoke test WAV not generated.")

        evaluator = QualityEvaluator()
        score = evaluator.evaluate(test_output_wav)
        logger.info(f"Smoke test quality score: {score}")
        return True
    except Exception as e:
        logger.error(f"Pipeline Smoke Test FAILED: {e}")
        return False

def run_health_check():
    results = {
        "ffmpeg": check_binary("ffmpeg"),
        "fluidsynth": check_binary("fluidsynth"),
        "mido": check_python_module("mido"),
        "librosa": check_python_module("librosa"),
        "smoke_test": smoke_test_pipeline()
    }

    logger.info("Health Check Summary:")
    for component, status in results.items():
        print(f"{component:15} : {'PASSED' if status else 'FAILED'}")

    if not all(results.values()):
        # We don't exit 1 here if run as module for UI, but as script we might.
        if __name__ == "__main__":
             # Check if it's a critical failure (smoke test or at least one core lib)
             if not results["smoke_test"]:
                 sys.exit(1)

if __name__ == "__main__":
    run_health_check()
