#!/usr/bin/env python3
"""
Python implementation of the promote_learning.sh script.
This module provides a command-line interface for promoting learning from chat history.
"""

import argparse
import sys
import subprocess
from typing import List, Optional


def main() -> int:
    """Main entry point for the promote-learning command."""
    parser = argparse.ArgumentParser(description="Promote learning from chat history")

    # Add arguments matching the CLI interface
    parser.add_argument("--id", required=True, help="ID of the chat to promote")
    parser.add_argument(
        "--target-collection", default="derived_learnings_v1", help="Target collection for promoted learning"
    )
    parser.add_argument("--source-collection", default="chat_history_v1", help="Source collection for chat history")
    parser.add_argument("--reason", help="Reason for promoting this chat")
    parser.add_argument("--confidence", type=float, default=0.85, help="Confidence score for the promoted learning")
    parser.add_argument("--category", help="Category for the promoted learning")

    args = parser.parse_args()

    # Convert to the format expected by the CLI
    cli_args = ["chroma-mcp-client", "promote-learning"]
    for arg, value in vars(args).items():
        if value is not None:
            cli_args.append(f"--{arg.replace('_', '-')}")
            cli_args.append(str(value))

    # Call the chroma-mcp-client CLI command
    try:
        result = subprocess.run(cli_args, check=False)
        return result.returncode
    except Exception as e:
        print(f"Error executing chroma-mcp-client: {e}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
