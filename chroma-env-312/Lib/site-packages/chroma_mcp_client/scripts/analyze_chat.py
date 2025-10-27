#!/usr/bin/env python3
"""
Python implementation of the analyze_chat_history.sh script.
This module provides a command-line interface for analyzing chat history in ChromaDB.
"""

import argparse
import sys
import subprocess
from typing import List, Optional


def main() -> int:
    """Main entry point for the analyze-chat command."""
    parser = argparse.ArgumentParser(description="Analyze chat history in ChromaDB")

    # Add arguments matching the CLI interface
    parser.add_argument("--query", help="Query string to search chat history")
    parser.add_argument("--n-results", type=int, default=5, help="Number of results to return")
    parser.add_argument("--session-id", help="Session ID to filter results")
    parser.add_argument("--collection-name", default="chat_history_v1", help="Name of the ChromaDB collection to query")
    parser.add_argument(
        "--output-format", choices=["text", "json", "yaml"], default="text", help="Output format for results"
    )
    parser.add_argument("--verbose", action="store_true", help="Enable verbose output")

    args = parser.parse_args()

    # Convert to the format expected by the CLI
    cli_args = ["chroma-mcp-client", "analyze-chat"]
    for arg, value in vars(args).items():
        if value is not None:
            if isinstance(value, bool) and value:  # For flag arguments
                cli_args.append(f"--{arg.replace('_', '-')}")
            elif not isinstance(value, bool):  # For arguments with values
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
