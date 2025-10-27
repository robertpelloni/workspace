#!/usr/bin/env python3
"""
Python implementation of the build.sh script.
This module provides functionality for building the chroma-mcp-server package.
"""

import os
import shutil
import subprocess
import sys
from pathlib import Path
from chroma_mcp.dev_scripts.project_root import get_project_root


def run_command(cmd: list[str], cwd: Path = None) -> int:
    """Run a shell command and return its exit code."""
    print(f"Running: {' '.join(cmd)}")
    result = subprocess.run(cmd, cwd=cwd)
    return result.returncode


def main() -> int:
    """Main entry point for the build script."""
    # Get project root
    project_root = get_project_root()

    print(f"ℹ️ Using project root: {project_root}")

    # Ensure Hatch is installed
    try:
        subprocess.run(["hatch", "--version"], check=True, capture_output=True)
    except (subprocess.CalledProcessError, FileNotFoundError):
        print("Hatch not found. Installing hatch...")
        if run_command([sys.executable, "-m", "pip", "install", "hatch"]) != 0:
            print("Failed to install Hatch. Aborting.")
            return 1

    # Clean previous builds
    print("Cleaning previous builds...")
    for path in ["dist", "build"]:
        full_path = project_root / path
        if full_path.exists():
            shutil.rmtree(full_path)

    # Remove egg-info directories
    for path in project_root.glob("*.egg-info"):
        if path.is_dir():
            shutil.rmtree(path)

    # Format code before building
    print("Formatting code with Black via Hatch...")
    if run_command(["hatch", "run", "black", "."], cwd=project_root) != 0:
        print("Warning: Code formatting failed, continuing with build.")

    # Build the package
    print("Building package with Hatch...")
    if run_command(["hatch", "build"], cwd=project_root) != 0:
        print("Build failed.")
        return 1

    print("Build complete. Distribution files are in the 'dist' directory:")
    run_command(["ls", "-la", "dist"], cwd=project_root)

    return 0


if __name__ == "__main__":
    sys.exit(main())
