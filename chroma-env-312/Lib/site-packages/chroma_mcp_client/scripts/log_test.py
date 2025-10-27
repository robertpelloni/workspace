#!/usr/bin/env python3
"""
Python implementation of the log_test_results.sh script.
This module provides a command-line interface for logging test results to ChromaDB.
"""

import argparse
import sys
import os
import subprocess
from typing import List, Optional


def main() -> int:
    """Main entry point for the log-test command."""
    parser = argparse.ArgumentParser(description="Log test results to ChromaDB")

    # Add arguments matching the CLI interface
    parser.add_argument("--test-name", required=True, help="Name of the test or test suite")
    parser.add_argument("--status", choices=["pass", "fail", "skip", "error"], required=True, help="Status of the test")
    parser.add_argument("--file-path", help="Path to the test file")
    parser.add_argument("--duration", type=float, help="Test execution duration in seconds")
    parser.add_argument("--message", help="Additional message or test output")
    parser.add_argument("--workspace-dir", default=os.getcwd(), help="Path to the workspace directory")
    parser.add_argument("--workflow-id", help="ID of the associated workflow")
    parser.add_argument(
        "--collection-name", default="test_results_v1", help="Name of the ChromaDB collection to log to"
    )

    args = parser.parse_args()

    # Convert to the format expected by the CLI
    cli_args = ["chroma-mcp-client", "log-test"]
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
