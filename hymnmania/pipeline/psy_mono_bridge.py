import sys
import os
import subprocess
import json

def generate_psytrance_pipeline(input_midi, output_dir, psy_config=None, ai_prompt=None):
    """
    Invokes the TypeScript Psy-Mono Pipeline to generate procedural psytrance
    from a hymn MIDI and optionally render AI-mastered audio.
    """
    # Ensure output dir exists
    if not os.path.exists(output_dir):
        os.makedirs(output_dir, exist_ok=True)

    # Construct arguments for npx ts-node src/pipeline.ts
    cmd = [
        "npx", "ts-node", "--transpile-only",
        "src/pipeline.ts",
        input_midi,
        output_dir
    ]

    # Add optional config as JSON string if provided
    if psy_config:
        cmd.append(json.dumps(psy_config))

    # If ai_prompt is provided, the TS pipeline will handle the Replicate call
    # Note: In src/pipeline.ts, we currently have aiPrompt hardcoded for CLI entry,
    # but we can pass it if we modify the TS pipeline further.

    print(f"Executing Psy-Mono Pipeline: {' '.join(cmd)}")

    try:
        result = subprocess.run(cmd, capture_output=True, text=True, check=True)
        print(result.stdout)
        return True
    except subprocess.CalledProcessError as e:
        print(f"Psy-Mono Pipeline failed: {e}")
        print(f"Error output: {e.stderr}")
        return False

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python -m pipeline.psy_mono_bridge <input_midi> <output_dir>")
        sys.exit(1)

    generate_psytrance_pipeline(sys.argv[1], sys.argv[2])
