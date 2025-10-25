"""
Handles direct connection to ChromaDB based on .env configuration.
Reuses configuration loading and client creation logic from the server's utils.
"""

import sys
import os
import chromadb
from pathlib import Path
from typing import Tuple, Optional
from chromadb import EmbeddingFunction
from functools import lru_cache

from chroma_mcp.utils.chroma_client import get_chroma_client, get_embedding_function
from chroma_mcp.types import ChromaClientConfig

# Default collection name used by the client
DEFAULT_COLLECTION_NAME = "codebase_v1"


def find_project_root(marker=".git"):
    """Find the project root by searching upwards for a marker file/directory."""
    path = Path(os.getcwd()).resolve()
    while path != path.parent:
        if (path / marker).exists():
            return path
        path = path.parent
    # If marker not found, fallback or raise error
    # Fallback to current dir might be risky, let's default to raising error
    # or returning None and handling it in the caller
    # For now, let's return current dir as a last resort but log a warning
    print(f"Warning: Could not find project root marker '{marker}'. Using CWD as fallback.", file=sys.stderr)
    return Path(os.getcwd()).resolve()


# Use lru_cache to ensure client/EF are initialized only once
@lru_cache(maxsize=1)
def get_client_and_ef(
    env_path: Optional[str] = None,
) -> Tuple[chromadb.ClientAPI, Optional[chromadb.EmbeddingFunction]]:
    """Initializes and returns a cached tuple of ChromaDB client and embedding function.

    Reads configuration from environment variables or a .env file located at the project root.
    Ensures single initialization using lru_cache.

    Args:
        env_path: Optional explicit path to a .env file (overrides root search).

    Returns:
        Tuple[chromadb.ClientAPI, Optional[chromadb.EmbeddingFunction]]

    Raises:
        Exception: If configuration loading or client/EF initialization fails.
    """
    print(f"Initializing ChromaDB connection and embedding function (env_path={env_path})...", file=sys.stderr)

    # Determine the base directory for resolving paths and loading .env
    if env_path:
        dotenv_path = Path(env_path).resolve()
        base_dir = dotenv_path.parent
        print(f"Using explicit env_path: {dotenv_path}", file=sys.stderr)
    else:
        base_dir = find_project_root()  # Find root based on .git marker
        dotenv_path = base_dir / ".env"
        print(f"Project root identified as: {base_dir}", file=sys.stderr)

    # Load .env from the determined path
    # from dotenv import load_dotenv # Import moved inside conditional
    if dotenv_path.exists():
        from dotenv import load_dotenv

        print(f"Loading .env file from: {dotenv_path}", file=sys.stderr)
        load_dotenv(dotenv_path=dotenv_path, override=True)
    else:
        print(f"Warning: .env file not found at {dotenv_path}. Using environment variables.", file=sys.stderr)

    # Resolve relative data path if persistent client is used
    client_type = os.getenv("CHROMA_CLIENT_TYPE", "persistent")
    data_dir_env = os.getenv("CHROMA_DATA_DIR", "./chroma_data")
    resolved_data_dir = data_dir_env
    if client_type == "persistent" and data_dir_env:
        data_path = Path(data_dir_env)
        if not data_path.is_absolute():
            # Resolve relative to the base_dir (either env_path parent or project root)
            resolved_data_dir = str(base_dir / data_path)
            print(f"Resolved relative CHROMA_DATA_DIR to: {resolved_data_dir}", file=sys.stderr)

    # 2. Construct ChromaClientConfig directly from environment variables
    #    Ensure all necessary fields expected by ChromaClientConfig are mapped.
    client_config = ChromaClientConfig(
        client_type=client_type,
        data_dir=resolved_data_dir,  # Use the resolved path
        host=os.getenv("CHROMA_HOST", "localhost"),
        port=os.getenv("CHROMA_PORT", "8000"),  # Keep as string (or None)
        ssl=os.getenv("CHROMA_SSL", "false").lower() in ["true", "1", "yes"],
        tenant=os.getenv("CHROMA_TENANT", chromadb.DEFAULT_TENANT),
        database=os.getenv("CHROMA_DATABASE", chromadb.DEFAULT_DATABASE),
        # embedding_function_name is NOT part of client connection config
        # Add any other required fields from ServerConfig here
    )
    print(
        f"Client Config from Env - Type: {client_config.client_type}, Host: {client_config.host}, Port: {client_config.port}, Path: {client_config.data_dir}",
        file=sys.stderr,
    )

    # 3. Get the ChromaDB client using the constructed client_config
    #    get_chroma_client handles the actual client creation logic
    print(f"Getting ChromaDB client (Type: {client_config.client_type})...", file=sys.stderr)
    # Pass the explicitly constructed config
    client: chromadb.ClientAPI = get_chroma_client(config=client_config)

    # 4. Get the embedding function name directly from environment
    #    (EF name is often part of the general config, not client-specific connection)
    ef_name = os.getenv("CHROMA_EMBEDDING_FUNCTION", "default")  # Use default if not set
    print(f"Getting Embedding Function ('{ef_name}')...", file=sys.stderr)
    embedding_function: Optional[chromadb.EmbeddingFunction] = get_embedding_function(ef_name)

    print("Client and EF initialization complete.", file=sys.stderr)
    return client, embedding_function


class ChromaMcpClient:
    """Encapsulates a ChromaDB client and its embedding function."""

    def __init__(self, env_path: Optional[str] = None):
        """Initialize the client, fetching or creating the connection."""
        self.client, self.embedding_function = get_client_and_ef(env_path=env_path)

    def get_client(self) -> chromadb.ClientAPI:
        """Return the underlying ChromaDB client."""
        return self.client

    def get_embedding_function(self) -> Optional[chromadb.EmbeddingFunction]:
        """Return the configured embedding function."""
        return self.embedding_function

    # Add other convenience methods here as needed


# Example usage (optional, for testing connection module directly)
# if __name__ == "__main__":
