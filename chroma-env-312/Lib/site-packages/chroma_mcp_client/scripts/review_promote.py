#!/usr/bin/env python3
"""
Python implementation of the review_and_promote.sh script.
This module provides an interactive command-line interface for reviewing
and promoting chat history to derived learnings.
"""

import argparse
import sys
import subprocess
from typing import List, Optional


def main() -> int:
    """Main entry point for the review-promote command."""
    parser = argparse.ArgumentParser(
        description="Interactive review and promotion of chat history to derived learnings"
    )

    # Add arguments matching the CLI interface
    parser.add_argument("--query", help="Query string to search chat history for relevant chats")
    parser.add_argument("--threshold", type=float, default=0.7, help="Similarity threshold for results")
    parser.add_argument("--n-results", type=int, default=5, help="Number of results to show for review")
    parser.add_argument("--source-collection", default="chat_history_v1", help="Source collection for chat history")
    parser.add_argument(
        "--target-collection", default="derived_learnings_v1", help="Target collection for promoted learning"
    )
    parser.add_argument("--interactive", action="store_true", default=True, help="Enable interactive review mode")

    args = parser.parse_args()

    # Convert to the format expected by the CLI
    cli_args = ["chroma-mcp-client", "review-promote"]
    for arg, value in vars(args).items():
        if value is not None:
            if isinstance(value, bool) and arg != "interactive":
                if value:
                    cli_args.append(f"--{arg.replace('_', '-')}")
            elif arg == "interactive" and value:
                cli_args.append("--interactive")
            elif not isinstance(value, bool):
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
