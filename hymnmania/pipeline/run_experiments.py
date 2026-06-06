import sys
import os
import logging

# Ensure parent directory is in path for imports
sys.path.append(os.path.dirname(os.path.abspath(__file__)))

from processing.sonic_vacuum import SonicVacuumProcessor
from processing.symbolic_norm import SymbolicNormalizer
from processing.house_quantizer import HouseStructuralQuantizer

logging.basicConfig(level=logging.INFO, format='%(levelname)s: %(message)s')
logger = logging.getLogger("PipelineOrchestrator")

def run_experiments(midi_path):
    if not os.path.exists(midi_path):
        logger.error(f"Input file not found: {midi_path}")
        return

    filename = os.path.basename(midi_path)
    name_no_ext = os.path.splitext(filename)[0]

    # Ensure output directories exist
    os.makedirs("pipeline/output/dry_render", exist_ok=True)
    os.makedirs("pipeline/output/symbolic_midi", exist_ok=True)
    os.makedirs("pipeline/output/house_skeletons", exist_ok=True)

    # Module 1: Sonic Vacuum
    logger.info(f"--- Experiment 1: Sonic Vacuum for {filename} ---")
    vacuum = SonicVacuumProcessor(midi_path)
    sv_path = os.path.join("pipeline/output/dry_render", f"{name_no_ext}_dry.wav")
    vacuum.render_dry_piano(sv_path)
    logger.info(f"Dry render exported to {sv_path}")

    # Module 2: Symbolic Normalizer
    logger.info(f"--- Experiment 2: Symbolic Normalization for {filename} ---")
    norm = SymbolicNormalizer(midi_path)
    sn_path = os.path.join("pipeline/output/symbolic_midi", f"{name_no_ext}_norm.mid")
    norm.normalize(sn_path)
    logger.info(f"Symbolic MIDI exported to {sn_path}")

    # Module 3: House Structural Quantizer
    logger.info(f"--- Experiment 3: House Structural Quantization for {filename} ---")
    quantizer = HouseStructuralQuantizer(midi_path)
    hq_path = os.path.join("pipeline/output/house_skeletons", f"{name_no_ext}_house.mid")
    quantizer.quantize(hq_path)
    logger.info(f"House skeleton exported to {hq_path}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python run_experiments.py <midi_path>")
    else:
        run_experiments(sys.argv[1])
