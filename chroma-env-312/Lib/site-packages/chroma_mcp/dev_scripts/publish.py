#!/usr/bin/env python3
"""
Python implementation of the publish.sh script.
This module provides functionality for publishing the chroma-mcp-server package to PyPI.
"""

import argparse
import os
import subprocess
import sys
from pathlib import Path
import getpass
import time
from chroma_mcp.dev_scripts.project_root import get_project_root


def run_command(cmd: list[str], cwd: Path = None) -> int:
    """Run a shell command and return its exit code."""
    # Create a copy of the command for logging to avoid modifying the original
    log_cmd = list(cmd)

    # Sanitize command for logging: redact sensitive data
    sensitive_flags = ["-p", "--password", "--token"]
    for flag in sensitive_flags:
        try:
            flag_index = log_cmd.index(flag)
            if flag_index + 1 < len(log_cmd):  # Ensure there's an argument after the flag
                log_cmd[flag_index + 1] = "<REDACTED>"
        except ValueError:
            # Flag not found, continue to the next one
            continue

    # Further sanitize long commands for display purposes, if necessary,
    # after specific redaction has occurred.
    if len(log_cmd) > 7:  # Adjusted length for better visibility, can be tuned
        display_cmd_str = " ".join(log_cmd[:7]) + " ..."
    else:
        display_cmd_str = " ".join(log_cmd)

    if "<REDACTED>" in display_cmd_str:
        print("Running: [Command contains sensitive data, redacted]")
    else:
        print(f"Running: {display_cmd_str}")
    result = subprocess.run(cmd, cwd=cwd)
    return result.returncode


def check_dist_files(project_root: Path) -> bool:
    """Check if distribution files exist."""
    dist_dir = project_root / "dist"
    if not dist_dir.exists() or not list(dist_dir.glob("*.whl")) or not list(dist_dir.glob("*.tar.gz")):
        return False
    return True


def main() -> int:
    """Main entry point for the publish script."""
    parser = argparse.ArgumentParser(description="Publish the chroma-mcp-server package to PyPI")

    # Add arguments
    parser.add_argument(
        "--repo", default="pypi", choices=["pypi", "testpypi"], help="Repository to publish to (pypi or testpypi)"
    )
    parser.add_argument("--version", help="Version number being published (optional)")
    parser.add_argument("-y", "--yes", action="store_true", help="Non-interactive mode, assume yes to prompts")
    parser.add_argument("--skip-build", action="store_true", help="Skip building the package before publishing")
    parser.add_argument("--skip-tests", action="store_true", help="Skip running tests before publishing")
    parser.add_argument("--upload-retries", type=int, default=0, help="Number of times to retry upload on failure")

    args = parser.parse_args()

    # Get project root
    project_root = get_project_root()
    print(f"ℹ️ Publishing package from: {project_root}")

    # Ensure build dependencies are installed
    print("Ensuring build dependencies are installed...")
    if run_command([sys.executable, "-m", "pip", "install", "--upgrade", "pip", "build", "twine"]) != 0:
        print("Failed to install build dependencies. Aborting.")
        return 1

    # Ensure Hatch is installed
    try:
        subprocess.run(["hatch", "--version"], check=True, capture_output=True)
    except (subprocess.CalledProcessError, FileNotFoundError):
        print("Hatch not found. Installing hatch...")
        if run_command([sys.executable, "-m", "pip", "install", "hatch"]) != 0:
            print("Failed to install Hatch. Aborting.")
            return 1

    # Run tests if not skipped
    if not args.skip_tests:
        print("Running tests before publishing...")
        if run_command(["hatch", "test"], cwd=project_root) != 0:
            print("Tests failed. Aborting publication.")
            return 1

    # Build the package if not skipped
    if not args.skip_build:
        print("Building distribution packages...")
        # Clean previous builds
        dist_dir = project_root / "dist"
        if dist_dir.exists():
            import shutil

            shutil.rmtree(dist_dir)

        if run_command(["hatch", "build"], cwd=project_root) != 0:
            print("Failed to build the package. Aborting.")
            return 1

    # Check if distribution files exist
    if not check_dist_files(project_root):
        print("Distribution files not found. Run 'hatch build' first.")
        return 1

    # Determine repository URL
    repo_url = "https://test.pypi.org/legacy/" if args.repo == "testpypi" else "https://upload.pypi.org/legacy/"

    # Upload to PyPI
    print(f"Uploading package to {args.repo}...")
    # Use ~/.pypirc config if available; otherwise prompt for token
    pypirc_path = Path.home() / ".pypirc"
    if pypirc_path.exists():
        cmd = ["twine", "upload", "-r", args.repo, "dist/*"]
    else:
        try:
            token = getpass.getpass(f"Enter your API token for {args.repo}: ")
        except Exception:
            # Non-interactive environment or prompt failed; fallback to using repository alias
            cmd = ["twine", "upload", "-r", args.repo, "dist/*"]
        else:
            cmd = ["twine", "upload", "--repository-url", repo_url, "-u", "__token__", "-p", token, "dist/*"]
    # Attempt upload with retries, adding verbose flag on retry attempts
    retries = args.upload_retries
    attempt = 0
    base_cmd = cmd
    verbose_cmd = base_cmd + ["--verbose"]
    while True:
        current_cmd = base_cmd if attempt == 0 else verbose_cmd
        exit_code = run_command(current_cmd, cwd=project_root)
        if exit_code == 0:
            break
        attempt += 1
        if attempt > retries:
            print(f"Failed to upload package to {args.repo}.")
            return 1
        print(f"Upload failed, retrying {attempt}/{retries} with verbose output...")
        time.sleep(5)
    print(f"Package successfully published to {args.repo}!")
    return 0


if __name__ == "__main__":
    sys.exit(main())
