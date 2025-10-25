#!/usr/bin/env python3
"""
Python implementation of the validate_evidence.sh script.
This module provides a command-line interface for validating evidence in test workflows.
"""

import argparse
import sys
import os
import subprocess
from typing import List, Optional


def main() -> int:
    """Main entry point for the validate-evidence command."""
    parser = argparse.ArgumentParser(description="Validate evidence in test workflows")

    # Add arguments matching the CLI interface
    parser.add_argument("--workflow-id", help="ID of the workflow to validate")
    parser.add_argument("--test-name", help="Name of the test to validate evidence for")
    parser.add_argument("--status", choices=["pass", "fail"], help="Filter by test status")
    parser.add_argument("--workspace-dir", default=os.getcwd(), help="Path to the workspace directory")
    parser.add_argument("--source-collection", default="test_results_v1", help="Source collection for test results")
    parser.add_argument("--interactive", action="store_true", help="Enable interactive validation mode")
    parser.add_argument("--promote", action="store_true", help="Automatically promote validated evidence")
    parser.add_argument(
        "--output-format", choices=["text", "json"], default="text", help="Output format for validation results"
    )

    args = parser.parse_args()

    # Convert to the format expected by the CLI
    cli_args = ["chroma-mcp-client", "validate-evidence"]
    for arg, value in vars(args).items():
        if value is not None:
            if isinstance(value, bool) and value:
                cli_args.append(f"--{arg.replace('_', '-')}")
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
