#!/usr/bin/env python3
"""
Python implementation of the log_error.sh script.
This module provides a command-line interface for logging error information to ChromaDB.
"""

import argparse
import sys
import subprocess
from typing import List, Optional


def main() -> int:
    """Main entry point for the log-error command."""
    parser = argparse.ArgumentParser(description="Log error information to ChromaDB")

    # Add arguments matching the CLI interface
    parser.add_argument("--error-message", required=True, help="Error message or description")
    parser.add_argument("--error-type", required=True, help="Type or category of the error")
    parser.add_argument("--file-path", help="Path to the file where the error occurred")
    parser.add_argument("--line-number", type=int, help="Line number where the error occurred")
    parser.add_argument("--stack-trace", help="Stack trace of the error")
    parser.add_argument("--context", help="Additional context information")
    parser.add_argument("--workflow-id", help="ID of the associated workflow")
    parser.add_argument("--collection-name", default="error_logs_v1", help="Name of the ChromaDB collection to log to")

    args = parser.parse_args()

    # Convert to the format expected by the CLI
    cli_args = ["chroma-mcp-client", "log-error"]
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
