"""Chroma MCP Server Package."""

# Import key types for easier access, but be careful about circular dependencies
from .types import (
    # Document, # Removed: Not defined in types.py
    DocumentMetadata,
    # QueryResult, # Removed: Not defined in types.py
    ThoughtMetadata,
)
from .utils import (
    chroma_client,
    config,
    errors,
)

from .tools import collection_tools, document_tools, thinking_tools

# Import key components for easier access from outside
from .utils import get_logger, get_chroma_client, get_embedding_function
from .utils.errors import McpError, ValidationError  # Assuming McpError is defined here or imported

__version__ = "0.1.0"


# Define __all__ to control what `from chroma_mcp import *` imports
__all__ = [
    # Types
    "DocumentMetadata",
    "ThoughtMetadata",
    # Utils
    "config",
    "chroma_client",
    "errors",
    # Tools
    "collection_tools",
    "document_tools",
    "thinking_tools",
    # Server - Only expose get_mcp
    "get_mcp",
    # Version
    "__version__",
]

__author__ = "Nold Coaching & Consulting"
__license__ = "MIT"
