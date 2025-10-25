#!/usr/bin/env python3
"""
Python implementation of the log_chat.sh script.
This module provides a command-line interface for logging chat interactions to ChromaDB.
"""

import argparse
import sys
import os
import subprocess
from typing import List, Optional


def main() -> int:
    """Main entry point for the log-chat command."""
    parser = argparse.ArgumentParser(description="Log chat interactions to ChromaDB")

    # Add arguments matching the CLI interface
    parser.add_argument("--prompt-summary", required=True, help="Summary of the user's prompt")
    parser.add_argument("--response-summary", required=True, help="Summary of the AI's response")
    parser.add_argument("--raw-prompt", help="Full text of the user's prompt")
    parser.add_argument("--raw-response", help="Full text of the AI's response")
    parser.add_argument("--involved-entities", help="Comma-separated string of entities involved")
    parser.add_argument("--session-id", help="Session ID for the interaction")
    parser.add_argument(
        "--collection-name", default="chat_history_v1", help="Name of the ChromaDB collection to log to"
    )

    args = parser.parse_args()

    # Convert to the format expected by the CLI
    cli_args = ["chroma-mcp-client", "log-chat"]
    for arg, value in vars(args).items():
        if value is not None:
            cli_args.append(f"--{arg.replace('_', '-')}")
            cli_args.append(value)

    # Call the chroma-mcp-client CLI command
    try:
        result = subprocess.run(cli_args, check=False)
        return result.returncode
    except Exception as e:
        print(f"Error executing chroma-mcp-client: {e}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
