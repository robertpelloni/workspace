"""
Error handling utility module for standardized error management.
"""

from typing import Optional, Dict, Any
from dataclasses import dataclass

from mcp.shared.exceptions import McpError
from mcp.types import ErrorData, INTERNAL_ERROR, INVALID_PARAMS

# Remove old logger setup
# from .logger_setup import LoggerSetup
# Replace with get_logger from server
# from ..server import get_logger

# Initialize logger using the central function
# logger = LoggerSetup.create_logger(
#     "ChromaErrors",
#     log_file="chroma_errors.log"
# )


# Custom Exception Classes (Kept as they are raised directly now)
class ValidationError(Exception):
    """Raised when input validation fails."""

    def __init__(self, message: str):
        self.message = message
        super().__init__(message)


# Removed unused CollectionNotFoundError and DocumentNotFoundError
# class CollectionNotFoundError(Exception): ...
# class DocumentNotFoundError(Exception): ...


class EmbeddingError(Exception):
    """Raised when there is an error with embeddings."""

    def __init__(self, message: str):
        self.message = message
        super().__init__(message)


class ClientError(Exception):
    """Raised when there is an error with the ChromaDB client."""

    def __init__(self, message: str):
        self.message = message
        super().__init__(message)


class ConfigurationError(Exception):
    """Raised when there is an error with the configuration."""

    def __init__(self, message: str):
        self.message = message
        super().__init__(message)


# Removed ChromaError dataclass and constants as handle_chroma_error is removed
# @dataclass
# class ChromaError: ...
# COLLECTION_NOT_FOUND = ...
# ... etc ...

# Removed handle_chroma_error function
# def handle_chroma_error(error: Exception, operation: str) -> McpError:
#     """Maps specific ChromaDB exceptions to McpError."""
#     from ..server import get_logger # Import locally
#     logger = get_logger("utils.errors")
#
#     logger.error(f"Handling Chroma error during {operation}: {error}", exc_info=True)
#
#     # Map specific Chroma errors or common Python errors
#     if isinstance(error, ValueError) and "does not exist" in str(error):
#         error_code = INVALID_PARAMS # Or a custom code if defined
#         error_message = f"Resource not found during {operation}: {str(error)}"
#     elif isinstance(error, ValueError): # Other ValueErrors
#         error_code = INVALID_PARAMS
#         error_message = f"Invalid parameter during {operation}: {str(error)}"
#     # Add more specific ChromaDB error types here if needed
#     # elif isinstance(error, chromadb.errors.SomeSpecificError):
#     #     error_code = ...
#     #     error_message = ...
#     else: # Default for unexpected errors
#         error_code = INTERNAL_ERROR
#         error_message = f"An unexpected server error occurred during {operation}."
#
#     return McpError(
#         code=error_code,
#         message=error_message,
#         data=ErrorData(details=str(error)) # Include original error string
#     )


# Kept validate_input as it might be useful elsewhere
# def validate_input(
#     value: Any,
#     name: str,
#     required: bool = True,
#     max_length: Optional[int] = None,
#     min_length: Optional[int] = None,
#     pattern: Optional[str] = None
# ) -> Optional[str]:
#     """
#     Validate input parameters.
#
#     Args:
#         value: Value to validate
#         name: Name of the parameter
#         required: Whether the parameter is required
#         max_length: Maximum length for string values
#         min_length: Minimum length for string values
#         pattern: Regex pattern for string validation
#
#     Returns:
#         Error message if validation fails, None otherwise
#     """
#     # Check required
#     if required and value is None:
#         return f"{name} is required"
#
#     # Skip further validation if value is None and not required
#     if value is None:
#         return None
#
#     # String validations
#     if isinstance(value, str):
#         if max_length and len(value) > max_length:
#             return f"{name} exceeds maximum length of {max_length}"
#
#         if min_length and len(value) < min_length:
#             return f"{name} is shorter than minimum length of {min_length}"
#
#         if pattern:
#             import re
#             if not re.match(pattern, value):
#                 return f"{name} does not match required pattern"
#
#     return None

# Removed raise_validation_error function
# def raise_validation_error(error_message: str) -> None:
