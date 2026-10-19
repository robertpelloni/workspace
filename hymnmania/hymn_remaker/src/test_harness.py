import os
import time
import json
import numpy as np
from hymn_remaker.src.psy_sequencer import PsyGenerator
from hymn_remaker.src.midi_renderer import MidiRenderer
from hymn_remaker.src.quality_evaluator import QualityEvaluator
from hymn_remaker import settings

def run_parameter_sweep(corpus_dir, output_dir):
    """
    Sweeps parameters for the PsyGenerator and evaluates quality.
    """
    os.makedirs(output_dir, exist_ok=True)
    generator = PsyGenerator()
    renderer = MidiRenderer()
    evaluator = QualityEvaluator()

    hymns = [f for f in os.listdir(corpus_dir) if f.endswith(('.mid', '.midi'))]
    if not hymns:
        print(f"No hymns found in {corpus_dir}")
        return

    results = []

    # Sweep parameters
    densities = [3, 5, 8]
    gallops = ["classic", "triplet", "rolling"]

    for hymn in hymns[:3]: # Test with first 3 hymns for speed
        hymn_path = os.path.join(corpus_dir, hymn)
        print(f"Testing hymn: {hymn}")

        for density in densities:
            for gallop in gallops:
                test_id = f"{hymn.split('.')[0]}_d{density}_{gallop}"
                midi_out = os.path.join(output_dir, f"{test_id}.mid")
                wav_out = os.path.join(output_dir, f"{test_id}.wav")

                print(f"  -> Density: {density}, Gallop: {gallop}")

                generator.generate(hymn_path, midi_out, {
                    "targetBpm": 145,
                    "euclideanDensity": density,
                    "gallopVariant": gallop,
                    "mode": "loop"
                })

                renderer.render(midi_out, wav_out)
                score = evaluator.evaluate(wav_out)

                results.append({
                    "hymn": hymn,
                    "density": density,
                    "gallop": gallop,
                    "score": score,
                    "test_id": test_id
                })

    # Save results
    report_path = os.path.join(output_dir, "parameter_sweep_results.json")
    with open(report_path, "w") as f:
        json.dump(results, f, indent=4)

    generate_report(results)

def generate_report(results):
    report = "# Parameter Refinement Report\n\n"
    report += "## Summary\n"
    avg_score = np.mean([r["score"] for r in results])
    report += f"Average Quality Score: {avg_score:.2f}\n\n"

    report += "## Top Performing Configurations\n"
    sorted_res = sorted(results, key=lambda x: x["score"], reverse=True)
    for r in sorted_res[:5]:
        report += f"- **{r['test_id']}**: Score {r['score']} (D:{r['density']}, G:{r['gallop']})\n"

    report += "\n## Parameter Analysis\n"
    for g in ["classic", "triplet", "rolling"]:
        g_scores = [r["score"] for r in results if r["gallop"] == g]
        if g_scores:
            report += f"- **Gallop {g}**: Avg Score {np.mean(g_scores):.2f}\n"

    with open("docs/PARAMETER_REFINE_REPORT.md", "w") as f:
        f.write(report)
    print("Report generated: docs/PARAMETER_REFINE_REPORT.md")

if __name__ == "__main__":
    run_parameter_sweep(settings.INPUT_DIR, "output/harness_test")
