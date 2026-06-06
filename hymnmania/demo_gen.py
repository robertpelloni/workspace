import os
import sys
import logging
import json

# Add src to path
sys.path.append(os.path.join(os.getcwd(), 'hymn_remaker', 'src'))

from psy_sequencer import PsyGenerator
from quality_evaluator import QualityEvaluator
from midi_renderer import MidiRenderer

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger("DemoGen")

def run_demo():
    input_dir = "demo_input"
    output_dir = "demo_output"
    os.makedirs(output_dir, exist_ok=True)

    gen = PsyGenerator()
    evaluator = QualityEvaluator()
    renderer = MidiRenderer()

    midis = [f for f in os.listdir(input_dir) if f.endswith(".mid")]
    results = []

    for midi_file in midis:
        input_path = os.path.join(input_dir, midi_file)
        name = os.path.splitext(midi_file)[0]
        psy_midi = os.path.join(output_dir, f"{name}_psy.mid")
        psy_wav = os.path.join(output_dir, f"{name}_psy.wav")

        logger.info(f"Processing {name}...")

        # 1. Generate Psy MIDI
        try:
            gen.generate(input_path, psy_midi, config={"targetBpm": 145, "mode": "loop"})
        except Exception as e:
            logger.error(f"Failed to generate MIDI for {name}: {e}")
            continue

        # 2. Render to WAV
        try:
            renderer.render(psy_midi, psy_wav)
        except Exception as e:
            logger.error(f"Failed to render WAV for {name}: {e}")
            continue

        # 3. Evaluate Quality
        try:
            score = evaluator.evaluate(psy_wav)
            logger.info(f"Quality for {name}: {score:.2f}")
            results.append({
                "name": name,
                "score": score
            })
        except Exception as e:
            logger.error(f"Failed to evaluate {name}: {e}")

    with open(os.path.join(output_dir, "demo_results.json"), "w") as f:
        json.dump(results, f, indent=4)

    print("\n--- DEMO RESULTS ---")
    for r in results:
        print(f"{r['name']}: {r['score']:.2f}")

if __name__ == "__main__":
    run_demo()
