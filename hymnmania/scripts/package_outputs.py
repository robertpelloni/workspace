"""Package Hymnmania Outputs for Deployment/Review.

Aggregates generated audio, video, and MIDI from hymn_remaker/output/
into a structured directory or ZIP file.
"""

import os
import shutil
import argparse
import zipfile
from datetime import datetime

def package_outputs(output_path, source_dir="hymn_remaker/output"):
    if not os.path.exists(source_dir):
        print(f"Source directory {source_dir} not found.")
        return

    # Create temporary packaging dir
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    pkg_name = f"hymnmania_bundle_{timestamp}"
    pkg_dir = os.path.join(os.path.dirname(output_path) if os.path.dirname(output_path) else ".", pkg_name)
    os.makedirs(pkg_dir, exist_ok=True)

    print(f"Packaging outputs from {source_dir} to {pkg_dir}...")

    # Define subfolders
    folders = ["audio", "video", "midi", "metadata", "experiments"]
    for f in folders:
        os.makedirs(os.path.join(pkg_dir, f), exist_ok=True)

    # Walk and copy
    for root, dirs, files in os.walk(source_dir):
        for file in files:
            src = os.path.join(root, file)
            ext = os.path.splitext(file)[1].lower()

            # Map to target
            dst_folder = None
            if "dry_render" in root or "house_skeletons" in root or "symbolic_midi" in root:
                dst_folder = "experiments"
            elif ext in [".wav", ".mp3"]:
                dst_folder = "audio"
            elif ext in [".mp4", ".mov"]:
                dst_folder = "video"
            elif ext in [".mid", ".midi"]:
                dst_folder = "midi"
            elif ext in [".json", ".jsonl"]:
                dst_folder = "metadata"

            if dst_folder:
                dst = os.path.join(pkg_dir, dst_folder, file)
                shutil.copy2(src, dst)

    # ZIP if requested
    if output_path.endswith(".zip"):
        print(f"Creating ZIP archive: {output_path}...")
        with zipfile.ZipFile(output_path, 'w', zipfile.ZIP_DEFLATED) as zipf:
            for root, dirs, files in os.walk(pkg_dir):
                for file in files:
                    # Maintain relative path inside ZIP
                    rel_path = os.path.relpath(os.path.join(root, file), pkg_dir)
                    zipf.write(os.path.join(root, file), rel_path)
        shutil.rmtree(pkg_dir)
        print(f"Bundle created: {output_path}")
    else:
        # Just rename the pkg_dir to output_path if it's not a ZIP
        if os.path.exists(output_path):
             shutil.rmtree(output_path)
        os.rename(pkg_dir, output_path)
        print(f"Folder bundle created: {output_path}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Package Hymnmania outputs.")
    parser.add_argument("--output", default="hymnmania_bundle.zip", help="Output path (ZIP or folder)")
    parser.add_argument("--source", default="hymn_remaker/output", help="Source directory")
    args = parser.parse_args()
    package_outputs(args.output, args.source)
