"""Type definitions for the ChromaMCP server."""

from dataclasses import dataclass
from typing import Optional, Dict, Any, List
from pydantic import BaseModel

# Error codes
INTERNAL_ERROR = "INTERNAL_ERROR"
INVALID_PARAMS = "INVALID_PARAMS"


class ErrorData(BaseModel):
    """Standard error data structure."""

    code: str
    message: str
    data: Optional[Dict[str, Any]] = None


# Moved from utils/client.py
@dataclass
class ChromaClientConfig:
    """Configuration for the ChromaDB client."""

    client_type: str = "ephemeral"
    embedding_function_name: str = "default"
    data_dir: Optional[str] = None
    host: Optional[str] = None
    port: Optional[str] = None
    ssl: bool = False
    tenant: Optional[str] = None
    database: Optional[str] = None
    api_key: Optional[str] = None
    use_cpu_provider: Optional[bool] = None  # None means auto-detect


@dataclass
class ThoughtMetadata:
    """Metadata structure for thoughts."""

    session_id: str  # Unique identifier for the thinking session
    thought_number: int  # Position of the thought in the sequence
    total_thoughts: int  # Total number of thoughts expected in the sequence
    timestamp: int  # Unix timestamp when the thought was recorded
    branch_from_thought: Optional[int] = None  # Thought number this branches from
    branch_id: Optional[str] = None  # Identifier for the branch
    next_thought_needed: bool = False  # Whether another thought is needed
    custom_data: Optional[Dict[str, Any]] = None  # Additional metadata
    tags: Optional[List[str]] = None  # Make tags optional too for consistency


@dataclass
class DocumentMetadata:
    """Standardized structure for document metadata."""

    source: Optional[str] = None
    timestamp: Optional[int] = None
    tags: Optional[List[str]] = None  # Make tags optional too for consistency
    custom_data: Optional[Dict[str, Any]] = None
