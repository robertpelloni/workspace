#!/usr/bin/env python3
import argparse
import subprocess
import sys
import shutil
import os
from pathlib import Path


def get_repo_root():
    script_path = Path(__file__).resolve()
    return script_path.parent.parent


def setup_environment(repo_root):
    env = os.environ.copy()

    sdk_path = repo_root / "aios" / "software-agent-sdk" / "src"

    if sdk_path.exists():
        current_pythonpath = env.get("PYTHONPATH", "")
        env["PYTHONPATH"] = f"{sdk_path}{os.pathsep}{current_pythonpath}"
        print(f"[*] Added SDK to PYTHONPATH: {sdk_path}")
    else:
        print(f"[!] Warning: SDK path not found at {sdk_path}")

    return env


def check_dependencies():
    if not shutil.which("uv"):
        print(
            "[!] Warning: 'uv' not found. It is recommended for running agents efficiently."
        )
        return False
    return True


def run_trae_agent(repo_root, prompt, env, verbose=False):
    agent_dir = repo_root / "trae-agent"

    if not agent_dir.exists():
        print(f"[x] Error: trae-agent directory not found at {agent_dir}")
        return

    print(f"[*] Launching Trae Agent...")
    print(f"    Prompt: '{prompt}'")
    print(f"    Working Directory: {agent_dir}")

    cmd = ["uv", "run", "trae-cli", "run", prompt]

    if verbose:
        cmd.append("--verbose")

    try:
        subprocess.run(cmd, cwd=agent_dir, env=env, check=True)
        print("[*] Trae Agent task completed.")
    except subprocess.CalledProcessError as e:
        print(f"[x] Error running Trae Agent (Exit Code {e.returncode})")
    except FileNotFoundError:
        print("[x] Error: Command not found. Ensure 'uv' is installed.")
    except Exception as e:
        print(f"[x] Unexpected error: {e}")


def run_ii_agent(repo_root, prompt, env, verbose=False):
    agent_dir = repo_root / "ii-agent"

    if not agent_dir.exists():
        print(f"[x] Error: ii-agent directory not found at {agent_dir}")
        return

    print(f"[*] Launching II-Agent Server...")
    print(
        f"    Note: II-Agent runs as a server. Prompt '{prompt}' will be logged but not auto-executed yet."
    )

    start_script = agent_dir / "start.sh"
    if not start_script.exists():
        print(f"[x] Error: start.sh not found in {agent_dir}")
        return

    if not os.access(start_script, os.X_OK):
        try:
            os.chmod(start_script, 0o755)
            print("[*] Made start.sh executable")
        except Exception as e:
            print(f"[!] Warning: Could not chmod start.sh: {e}")

    cmd = ["./start.sh"]

    try:
        print("[*] Starting process (Ctrl+C to stop)...")
        subprocess.run(cmd, cwd=agent_dir, env=env, check=True)
    except subprocess.CalledProcessError as e:
        print(f"[x] Error running II-Agent: {e}")
    except KeyboardInterrupt:
        print("\n[*] Stopping II-Agent...")
    except Exception as e:
        print(f"[x] Unexpected error: {e}")


def main():
    parser = argparse.ArgumentParser(description="AIOS Agent Orchestrator (v1.0.5)")
    parser.add_argument(
        "--agent", choices=["trae", "ii"], required=True, help="Which agent to run"
    )
    parser.add_argument("prompt", help="The task or prompt for the agent")
    parser.add_argument(
        "-v", "--verbose", action="store_true", help="Enable verbose output"
    )

    args = parser.parse_args()

    repo_root = get_repo_root()
    env = setup_environment(repo_root)
    check_dependencies()

    if args.agent == "trae":
        run_trae_agent(repo_root, args.prompt, env, args.verbose)
    elif args.agent == "ii":
        run_ii_agent(repo_root, args.prompt, env, args.verbose)


if __name__ == "__main__":
    main()
