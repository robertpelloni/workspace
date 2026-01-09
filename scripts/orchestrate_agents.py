#!/usr/bin/env python3
import argparse
import subprocess
import sys
import shutil
from pathlib import Path


def check_dependencies():
    """Check if required tools are available."""
    if not shutil.which("uv"):
        print("Warning: 'uv' not found. It is recommended for running agents.")


def run_trae_agent(prompt, verbose=False):
    """Run Trae Agent with the given prompt."""
    print(f"🚀 Launching Trae Agent with prompt: '{prompt}'")

    # Locate trae-agent directory
    agent_dir = Path("trae-agent")
    if not agent_dir.exists():
        print("Error: trae-agent directory not found.")
        return

    # Construct command
    # Assuming 'uv run trae-cli run' is the method, based on common uv usage patterns
    # If trae-cli is installed globally or in venv, adjustment might be needed.
    # We will try running it via python module if cli isn't directly exposed,
    # but based on findings, let's try direct CLI or uv run.

    cmd = ["uv", "run", "trae-cli", "run", prompt]

    try:
        subprocess.run(cmd, cwd=agent_dir, check=True)
    except subprocess.CalledProcessError as e:
        print(f"Error running Trae Agent: {e}")
    except FileNotFoundError:
        print("Error: 'uv' command not found. Please install uv.")


def run_ii_agent(prompt, verbose=False):
    """Run II-Agent (Interpretable Intelligence Agent)."""
    print(f"🚀 Launching II-Agent...")
    print("Note: II-Agent typically runs as a WebSocket server.")

    # Locate ii-agent directory
    agent_dir = Path("ii-agent")
    if not agent_dir.exists():
        print("Error: ii-agent directory not found.")
        return

    # For now, we will attempt to start the server as the 'task'
    # since a direct 'run task' CLI wasn't clearly identified in the quick scan.
    # We will pass the prompt as an env var or arg if supported later.

    print("Starting II-Agent Server (Ctrl+C to stop)...")
    cmd = ["./start.sh"]

    try:
        subprocess.run(cmd, cwd=agent_dir, check=True)
    except subprocess.CalledProcessError as e:
        print(f"Error running II-Agent: {e}")
    except KeyboardInterrupt:
        print("\nStopping II-Agent...")


def main():
    parser = argparse.ArgumentParser(description="AIOS Agent Orchestrator")
    parser.add_argument(
        "--agent", choices=["trae", "ii"], required=True, help="Which agent to run"
    )
    parser.add_argument("prompt", help="The task or prompt for the agent")
    parser.add_argument(
        "-v", "--verbose", action="store_true", help="Enable verbose output"
    )

    args = parser.parse_args()

    check_dependencies()

    if args.agent == "trae":
        run_trae_agent(args.prompt, args.verbose)
    elif args.agent == "ii":
        run_ii_agent(args.prompt, args.verbose)


if __name__ == "__main__":
    main()
