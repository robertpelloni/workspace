#!/usr/bin/env python3
"""
Run the Chroma MCP Server.

This module allows the server to be started using:
python -m chroma_mcp
"""

import sys
from chroma_mcp.cli import main

if __name__ == "__main__":
    sys.exit(main())
