"""
Document management tools for ChromaDB operations.
"""

import time
import json
import logging
import uuid
import numpy as np  # Needed for NumpyEncoder usage
import datetime  # Add for ISO format date handling

from typing import Dict, List, Optional, Any, Union, cast
from dataclasses import dataclass

# Import ChromaDB result types
from chromadb.api.types import QueryResult, GetResult

from mcp import types
from mcp.shared.exceptions import McpError
from mcp.types import ErrorData, INVALID_PARAMS, INTERNAL_ERROR
from pydantic import BaseModel, Field, field_validator, ConfigDict  # Import Pydantic

# Use relative imports
from ..utils.errors import ValidationError
from ..types import DocumentMetadata

from chromadb.errors import InvalidDimensionException

# --- Imports ---
import chromadb
from ..utils import (
    get_logger,
    get_chroma_client,
    get_embedding_function,
    ValidationError,
    NumpyEncoder,  # Now defined and exported from utils.__init__
)
from ..utils.config import validate_collection_name

# --- Constants ---
DEFAULT_QUERY_N_RESULTS = 10
LEARNINGS_COLLECTION_NAME = "derived_learnings_v1"  # Define the learnings collection name


# --- Helper for server-side timestamps ---
def _ensure_server_timestamp(metadata: dict) -> dict:
    """
    Ensures that any timestamp fields in metadata use server-side time.

    Args:
        metadata: A dictionary of metadata that might contain timestamp fields

    Returns:
        The metadata dict with any timestamp fields replaced with current server time
    """
    timestamp_fields = ["timestamp", "last_indexed_utc", "created_at", "updated_at", "last_modified"]

    # Current server timestamps in different formats
    unix_ts = time.time()
    iso_ts = datetime.datetime.now().isoformat()

    # Create a copy to avoid modifying the input directly
    updated_metadata = metadata.copy()

    # Check for and replace common timestamp field names
    for field in timestamp_fields:
        if field in updated_metadata:
            # Use appropriate format based on existing value type
            existing_value = updated_metadata[field]
            if isinstance(existing_value, (int, float)):
                updated_metadata[field] = unix_ts
            elif isinstance(existing_value, str):
                # Check if it looks like an ISO format timestamp
                if "T" in existing_value and "-" in existing_value:
                    updated_metadata[field] = iso_ts
                else:
                    # Default to Unix timestamp for other string formats
                    updated_metadata[field] = str(unix_ts)

    return updated_metadata


# --- Pydantic Input Models for Document Tools ---

# --- Add Document Variants (Singular) --- #


class AddDocumentInput(BaseModel):
    """Input model for adding a single document (auto-generates ID, no metadata)."""

    collection_name: str = Field(..., description="Name of the collection to add the document to.")
    document: str = Field(..., description="Document content (string).")
    increment_index: bool = Field(True, description="Whether to immediately index the added document.")

    model_config = ConfigDict(extra="forbid")


class AddDocumentWithIDInput(BaseModel):
    """Input model for adding a single document with a specified ID (no metadata)."""

    collection_name: str = Field(..., description="Name of the collection to add the document to.")
    document: str = Field(..., description="Document content (string).")
    id: str = Field(..., description="Unique ID for the document.")
    increment_index: bool = Field(True, description="Whether to immediately index the added document.")

    model_config = ConfigDict(extra="forbid")


class AddDocumentWithMetadataInput(BaseModel):
    """Input model for adding a single document with specified metadata (auto-generates ID)."""

    collection_name: str = Field(..., description="Name of the collection to add the document to.")
    document: str = Field(..., description="Document content (string).")
    metadata: str = Field(..., description='Metadata JSON string for the document (e.g., \'{"key": "value"}\').')
    increment_index: bool = Field(True, description="Whether to immediately index the added document.")

    model_config = ConfigDict(extra="forbid")


class AddDocumentWithIDAndMetadataInput(BaseModel):
    """Input model for adding a single document with a specified ID and metadata."""

    collection_name: str = Field(..., description="Name of the collection to add the document to.")
    document: str = Field(..., description="Document content (string).")
    id: str = Field(..., description="Unique ID for the document.")
    metadata: str = Field(..., description='Metadata JSON string for the document (e.g., \'{"key": "value"}\').')
    increment_index: bool = Field(True, description="Whether to immediately index the added document.")

    model_config = ConfigDict(extra="forbid")


# --- Query Documents Variants --- #


class QueryDocumentsInput(BaseModel):
    """Input model for basic querying (no filters). Uses default includes."""

    collection_name: str = Field(..., description="Name of the collection to query.")
    query_texts: List[str] = Field(..., description="List of query strings for semantic search.")
    n_results: int = Field(10, ge=1, description="Maximum number of results per query.")

    model_config = ConfigDict(extra="forbid")


# Restore filter query models
class QueryDocumentsWithWhereFilterInput(BaseModel):
    """Input model for querying with a metadata filter. Uses default includes."""

    collection_name: str = Field(..., description="Name of the collection to query.")
    query_texts: List[str] = Field(..., description="List of query strings for semantic search.")
    where: str = Field(..., description='Metadata filter as a JSON string (e.g., \'{"source": "pdf"}\').')
    n_results: int = Field(10, ge=1, description="Maximum number of results per query.")

    model_config = ConfigDict(extra="forbid")


class QueryDocumentsWithDocumentFilterInput(BaseModel):
    """Input model for querying with a document content filter. Uses default includes."""

    collection_name: str = Field(..., description="Name of the collection to query.")
    query_texts: List[str] = Field(..., description="List of query strings for semantic search.")
    where_document: str = Field(
        ..., description='Document content filter as a JSON string (e.g., \'{"$contains": "keyword"}\').'
    )
    n_results: int = Field(10, ge=1, description="Maximum number of results per query.")

    model_config = ConfigDict(extra="forbid")


# --- Get Documents Variants --- #


# Restore original multi-ID get
class GetDocumentsByIdsInput(BaseModel):
    """Input model for getting documents by their specific IDs. Uses default includes."""

    collection_name: str = Field(..., description="Name of the collection to get documents from.")
    ids: List[str] = Field(..., description="List of document IDs to retrieve.")

    model_config = ConfigDict(extra="forbid")


# Restore filter-based gets
class GetDocumentsWithWhereFilterInput(BaseModel):
    """Input model for getting documents using a metadata filter. Uses default includes."""

    collection_name: str = Field(..., description="Name of the collection to get documents from.")
    where: str = Field(..., description='Metadata filter as a JSON string (e.g., \'{"source": "pdf"}\').')
    limit: int = Field(0, ge=0, description="Maximum number of documents to return. 0 for no limit.")
    offset: int = Field(0, ge=0, description="Number of documents to skip. 0 for default.")

    model_config = ConfigDict(extra="forbid")


class GetDocumentsWithDocumentFilterInput(BaseModel):
    """Input model for getting documents using a document content filter. Uses default includes."""

    collection_name: str = Field(..., description="Name of the collection to get documents from.")
    where_document: str = Field(
        ..., description='Document content filter as a JSON string (e.g., \'{"$contains": "keyword"}\').'
    )
    limit: int = Field(0, ge=0, description="Maximum number of documents to return. 0 for no limit.")
    offset: int = Field(0, ge=0, description="Number of documents to skip. 0 for default.")

    model_config = ConfigDict(extra="forbid")


# Restore get all
class GetAllDocumentsInput(BaseModel):
    """Input model for getting all documents in a collection (potentially limited). Uses default includes."""

    collection_name: str = Field(..., description="Name of the collection to get all documents from.")
    limit: int = Field(0, ge=0, description="Limit on the number of documents to return. 0 for no limit.")
    offset: int = Field(0, ge=0, description="Number of documents to skip. 0 for default.")

    model_config = ConfigDict(extra="forbid")


# --- Update Document Variants (Singular) --- #


class UpdateDocumentContentInput(BaseModel):
    """Input model for updating the content of an existing document."""

    collection_name: str = Field(..., description="Name of the collection containing the document.")
    id: str = Field(..., description="Document ID to update.")
    document: str = Field(..., description="New document content.")

    model_config = ConfigDict(extra="forbid")


class UpdateDocumentMetadataInput(BaseModel):
    """Input model for updating the metadata of an existing document."""

    collection_name: str = Field(..., description="Name of the collection containing the document.")
    id: str = Field(..., description="Document ID to update.")
    metadata: str = Field(..., description='New metadata as a JSON string (e.g., \'{"key": "new_value"}\').')

    model_config = ConfigDict(extra="forbid")


# --- Delete Document Variant (Singular ID) --- #


class DeleteDocumentByIdInput(BaseModel):
    """Input model for deleting a document by its specific ID."""

    collection_name: str = Field(..., description="Name of the collection to delete the document from.")
    id: str = Field(..., description="Document ID to delete.")

    model_config = ConfigDict(extra="forbid")


# --- End Pydantic Input Models --- #

# --- Start: New Include Variants ---


# Base model for Get By IDs with explicit include
class GetDocumentsByIdsIncludeInput(BaseModel):
    collection_name: str = Field(..., description="Name of the collection to get documents from.")
    ids: List[str] = Field(..., description="List of document IDs to retrieve.")
    # Include is implicitly handled by the specific variant

    model_config = ConfigDict(extra="forbid")


# --- GetDocumentsByIds Variants ---
class GetDocumentsByIdsEmbeddingsInput(GetDocumentsByIdsIncludeInput):
    """Input model for getting documents by IDs including embeddings only."""

    pass  # Inherits fields, include is fixed in impl


class GetDocumentsByIdsAllInput(GetDocumentsByIdsIncludeInput):
    """Input model for getting documents by IDs including all available data."""

    pass  # Inherits fields, include is fixed in impl


# --- End: New Include Variants ---


# --- Implementation Functions ---

# --- Add Document Impl Variants (Singular) --- #


async def _add_document_impl(input_data: AddDocumentInput) -> List[types.TextContent]:
    """Implementation for adding a single document without specified ID or metadata."""
    logger = get_logger("tools.document.add")
    collection_name = input_data.collection_name
    document = input_data.document  # Singular
    increment_index = input_data.increment_index

    # --- Validation ---
    validate_collection_name(collection_name)  # Added validation
    if not document:  # Check single document
        raise McpError(ErrorData(code=INVALID_PARAMS, message="Document content cannot be empty."))
    # --- End Validation ---

    logger.info(f"Adding 1 document to '{collection_name}' (generating ID). Increment index: {increment_index}")
    try:
        client = get_chroma_client()
        collection = client.get_collection(name=collection_name)

        # Generate unique ID for the document
        generated_id = str(uuid.uuid4())  # Singular
        logger.debug(f"Generated ID '{generated_id}' for document in '{collection_name}'.")

        # No need to validate IDs/Metadatas for this variant
        logger.info(
            f"Adding 1 document to '{collection_name}' (auto-ID, no metadata). Increment index: {increment_index}"
        )
        collection.add(
            documents=[document],  # Pass as list
            ids=[generated_id],  # Pass as list
            metadatas=None,  # Explicitly None
            # increment_index=increment_index # Chroma client seems to not have this yet
        )
        # Return the generated ID
        return [types.TextContent(type="text", text=json.dumps({"added_id": generated_id}))]
    except ValueError as e:
        # Handle collection not found
        if f"Collection {collection_name} does not exist" in str(e):
            logger.warning(f"Collection '{collection_name}' not found for adding document.")
            raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Collection '{collection_name}' not found."))
        else:
            logger.error(f"Error getting documents by ID from '{collection_name}': {e}", exc_info=True)
            raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Invalid parameter adding document: {e}"))
    except Exception as e:
        logger.error(f"Error getting documents by ID from '{collection_name}': {e}", exc_info=True)
        # Fix: Match test expected message for generic add error
        raise McpError(
            ErrorData(
                code=INTERNAL_ERROR,
                message=f"An unexpected error occurred: {str(e)}",
            )
        )


async def _add_document_with_id_impl(input_data: AddDocumentWithIDInput) -> List[types.TextContent]:
    """Implementation for adding a single document with a specified ID."""
    logger = get_logger("tools.document.add_with_id")  # Renamed logger
    collection_name = input_data.collection_name
    document = input_data.document  # Singular
    id = input_data.id  # Singular
    increment_index = input_data.increment_index

    # --- Validation ---
    validate_collection_name(collection_name)  # Added validation
    if not document:  # Check single document
        raise McpError(ErrorData(code=INVALID_PARAMS, message="Document content cannot be empty."))
    if not id:  # Check single ID
        raise McpError(ErrorData(code=INVALID_PARAMS, message="Document ID cannot be empty."))
    # --- End Validation ---

    logger.info(f"Adding 1 document with ID '{id}' to '{collection_name}'. Increment index: {increment_index}")
    try:
        client = get_chroma_client()
        collection = client.get_collection(name=collection_name)

        logger.info(
            f"Adding 1 document with specified ID '{id}' to '{collection_name}' (no metadata). Increment index: {increment_index}"
        )
        collection.add(
            documents=[document],  # Pass as list
            ids=[id],  # Pass as list
            metadatas=None,  # Explicitly None
            # increment_index=increment_index
        )
        # Confirm the ID used
        return [types.TextContent(type="text", text=json.dumps({"added_id": id}))]
    except ValueError as e:
        if f"Collection {collection_name} does not exist" in str(e):
            logger.warning(f"Collection '{collection_name}' not found.")
            raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Collection '{collection_name}' not found."))
        else:
            logger.error(f"Value error: {e}", exc_info=True)
            raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Invalid parameter: {e}"))
    except Exception as e:
        logger.error(f"Unexpected error adding document '{id}' to '{collection_name}': {e}", exc_info=True)
        # Fix: Match test expected message
        raise McpError(ErrorData(code=INTERNAL_ERROR, message=f"An unexpected error occurred: {str(e)}"))


async def _add_document_with_metadata_impl(input_data: AddDocumentWithMetadataInput) -> List[types.TextContent]:
    """Implementation for adding a single document with metadata (auto-ID)."""
    logger = get_logger("tools.document.add_with_metadata")
    collection_name = input_data.collection_name
    document = input_data.document  # Singular
    metadata_str = input_data.metadata  # Singular string
    increment_index = input_data.increment_index

    # --- Validation ---
    validate_collection_name(collection_name)  # Added validation
    if not document:
        raise McpError(ErrorData(code=INVALID_PARAMS, message="Document content cannot be empty."))
    if not metadata_str:
        raise McpError(ErrorData(code=INVALID_PARAMS, message="Metadata JSON string cannot be empty."))
    # --- End Validation ---

    # --- Parse Metadata JSON String ---
    parsed_metadata = None  # Singular dict
    try:
        parsed_metadata = json.loads(metadata_str)
        if not isinstance(parsed_metadata, dict):
            raise ValueError("Metadata string must decode to a JSON object (dictionary).")
    except json.JSONDecodeError as e:
        logger.warning(f"Failed to parse metadata JSON string for '{collection_name}': {e}")
        raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Invalid JSON format for metadata string: {str(e)}"))
    except ValueError as e:  # Catch the isinstance check
        logger.warning(f"Metadata did not decode to a dictionary for '{collection_name}': {e}")
        raise McpError(
            ErrorData(code=INVALID_PARAMS, message=f"Metadata string did not decode to a dictionary: {str(e)}")
        )
    # --- End Parsing ---

    # --- Ensure timestamps are server-side ---
    parsed_metadata = _ensure_server_timestamp(parsed_metadata)
    # --- End timestamp enforcement ---

    # --- Generate ID --- #
    generated_id = str(uuid.uuid4())  # Singular
    logger.debug(f"Generated ID '{generated_id}' for document in '{collection_name}' (metadata provided).")
    # --- End Generate ID --- #

    logger.info(
        f"Adding 1 document with parsed metadata to '{collection_name}' (generated ID '{generated_id}'). Increment index: {increment_index}"
    )
    try:
        client = get_chroma_client()
        collection = client.get_collection(name=collection_name)

        logger.info(
            f"Adding 1 document with specified metadata to '{collection_name}' (generated ID). Increment index: {increment_index}"
        )
        collection.add(
            documents=[document],  # Pass as list
            ids=[generated_id],  # Pass as list
            metadatas=[parsed_metadata],  # Pass as list
            # increment_index=increment_index
        )
        # Return the generated ID
        return [types.TextContent(type="text", text=json.dumps({"added_id": generated_id}))]
    except ValueError as e:
        if f"Collection {collection_name} does not exist" in str(e):
            logger.warning(f"Collection '{collection_name}' not found.")
            raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Collection '{collection_name}' not found."))
        else:
            logger.error(f"Value error: {e}", exc_info=True)
            raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Invalid parameter: {e}"))
    except Exception as e:
        logger.error(f"Error adding document with metadata to '{collection_name}': {e}", exc_info=True)
        # Correction based on test_generic_chroma_error_handling (update part) failure:
        raise McpError(
            ErrorData(code=INTERNAL_ERROR, message=f"ChromaDB Error: Failed to update document content. {str(e)}")
        )


async def _add_document_with_id_and_metadata_impl(
    input_data: AddDocumentWithIDAndMetadataInput,
) -> List[types.TextContent]:
    """Implementation for adding a single document with specified ID and metadata."""
    logger = get_logger("tools.document.add_full")
    collection_name = input_data.collection_name
    document = input_data.document  # Singular
    id = input_data.id  # Singular
    metadata_str = input_data.metadata  # Singular string
    increment_index = input_data.increment_index

    # --- Validation ---
    validate_collection_name(collection_name)  # Added validation
    if not document:
        raise McpError(ErrorData(code=INVALID_PARAMS, message="Document content cannot be empty."))
    if not id:
        raise McpError(ErrorData(code=INVALID_PARAMS, message="Document ID cannot be empty."))
    if not metadata_str:
        raise McpError(ErrorData(code=INVALID_PARAMS, message="Metadata JSON string cannot be empty."))
    # --- End Validation ---

    # --- Parse Metadata JSON String ---
    parsed_metadata = None  # Singular dict
    try:
        parsed_metadata = json.loads(metadata_str)
        if not isinstance(parsed_metadata, dict):
            raise ValueError("Metadata string must decode to a JSON object (dictionary).")
    except json.JSONDecodeError as e:
        logger.warning(f"Failed to parse metadata JSON string for '{collection_name}' ID '{id}': {e}")
        raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Invalid JSON format for metadata string: {str(e)}"))
    except ValueError as e:  # Catch the isinstance check
        logger.warning(f"Metadata for ID '{id}' did not decode to a dictionary for '{collection_name}': {e}")
        raise McpError(
            ErrorData(code=INVALID_PARAMS, message=f"Metadata string did not decode to a dictionary: {str(e)}")
        )
    # --- End Parsing ---

    # --- Ensure timestamps are server-side ---
    parsed_metadata = _ensure_server_timestamp(parsed_metadata)
    # --- End timestamp enforcement ---

    logger.info(
        f"Adding 1 document with ID '{id}' and parsed metadata to '{collection_name}'. Increment index: {increment_index}"
    )
    try:
        client = get_chroma_client()
        collection = client.get_collection(name=collection_name)

        logger.info(
            f"Adding 1 document with specified ID '{id}' and metadata to '{collection_name}'. Increment index: {increment_index}"
        )
        collection.add(
            documents=[document],  # Pass as list
            ids=[id],  # Pass as list
            metadatas=[parsed_metadata],  # Pass as list
            # increment_index=increment_index
        )
        # Confirm the ID used
        return [types.TextContent(type="text", text=json.dumps({"added_id": id}))]
    except ValueError as e:
        if f"Collection {collection_name} does not exist" in str(e):
            logger.warning(f"Collection '{collection_name}' not found.")
            raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Collection '{collection_name}' not found."))
        else:
            logger.error(f"Value error: {e}", exc_info=True)
            raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Invalid parameter: {e}"))
    except Exception as e:
        logger.error(
            f"Unexpected error adding document '{id}' with metadata to '{collection_name}': {e}", exc_info=True
        )
        # Fix: Match test expected message
        raise McpError(ErrorData(code=INTERNAL_ERROR, message=f"An unexpected error occurred: {str(e)}"))


# --- End Add Document Impl Variants --- #

# --- Get Documents Impl Variants --- #


# Restore original multi-ID get implementation
async def _get_documents_by_ids_impl(input_data: GetDocumentsByIdsInput) -> List[types.TextContent]:
    """Implementation for getting documents by their specific IDs."""
    logger = get_logger("tools.document.get_ids")
    collection_name = input_data.collection_name
    ids = input_data.ids

    # --- Validation ---
    validate_collection_name(collection_name)  # Added validation
    if not ids:
        raise McpError(ErrorData(code=INVALID_PARAMS, message="IDs list cannot be empty."))
    # --- End Validation ---

    logger.info(f"Getting documents by {len(ids)} IDs from '{collection_name}'. Using default includes.")

    try:
        client = get_chroma_client()
        collection = client.get_collection(collection_name)
        # Pass include=None to use ChromaDB defaults
        get_result: GetResult = collection.get(ids=ids)
        logger.debug(f"ChromaDB get result: {get_result}")

        # Use json.dumps with NumpyEncoder to handle potential non-serializable data in results
        result_json = json.dumps(get_result, cls=NumpyEncoder)
        logger.info(
            f"Successfully retrieved {len(get_result.get('ids', []))} documents by ID from '{collection_name}'."
        )
        return [types.TextContent(type="text", text=result_json)]
    except ValueError as e:
        if f"Collection {collection_name} does not exist" in str(e):
            logger.warning(f"Collection '{collection_name}' not found for get by ID.")
            raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Collection '{collection_name}' not found."))
        else:
            logger.error(f"Error getting documents by ID from '{collection_name}': {e}", exc_info=True)
            raise McpError(
                ErrorData(
                    code=INTERNAL_ERROR,
                    message=f"An unexpected error occurred while retrieving documents by ID: {str(e)}",
                )
            )
    except Exception as e:
        logger.error(f"Error getting documents by ID from '{collection_name}': {e}", exc_info=True)
        # Fix: Match test expected message for generic get error
        raise McpError(
            ErrorData(
                code=INTERNAL_ERROR,
                message=f"An unexpected error occurred while retrieving documents by ID: {str(e)}",
            )
        )


# Restore filter-based get implementations
async def _get_documents_with_where_filter_impl(
    input_data: GetDocumentsWithWhereFilterInput,
) -> List[types.TextContent]:
    """Implementation for getting documents using a metadata filter."""
    logger = get_logger("tools.document.get_where")
    collection_name = input_data.collection_name
    where_str = input_data.where
    limit = input_data.limit
    offset = input_data.offset

    # --- Validation ---
    validate_collection_name(collection_name)
    try:
        where_filter = json.loads(where_str)
        if not isinstance(where_filter, dict):
            raise ValueError("Where filter must be a JSON object (dict).")
    except (json.JSONDecodeError, ValueError) as e:
        raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Invalid JSON format or type for 'where' filter: {e}"))
    # --- End Validation ---

    logger.info(
        f"Getting documents from '{collection_name}' with where filter. Limit: {limit}, Offset: {offset}. Using default includes."
    )

    try:
        client = get_chroma_client()
        collection = client.get_collection(collection_name)
        # Pass limit/offset directly, Chroma client handles 0 or None appropriately if needed
        # If 0 means "not set", we need to convert it to None for the client call
        effective_limit = limit if limit > 0 else None
        effective_offset = offset if offset > 0 else None

        get_result: GetResult = collection.get(
            where=where_filter,
            limit=effective_limit,
            offset=effective_offset,
        )
        logger.debug(f"ChromaDB get result: {get_result}")

        result_json = json.dumps(get_result, cls=NumpyEncoder)
        logger.info(
            f"Successfully retrieved {len(get_result.get('ids', []))} documents using where filter from '{collection_name}'."
        )
        return [types.TextContent(type="text", text=result_json)]
    except ValueError as e:
        if f"Collection {collection_name} does not exist" in str(e):
            logger.warning(f"Collection '{collection_name}' not found for get with where filter.")
            raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Collection '{collection_name}' not found."))
        else:
            logger.error(f"Error getting documents with where filter from '{collection_name}': {e}", exc_info=True)
            raise McpError(
                ErrorData(
                    code=INTERNAL_ERROR,
                    message=f"An unexpected error occurred during get: {str(e)}",
                )
            )
    except Exception as e:
        logger.error(
            f"Error getting documents with where filter from '{collection_name}': {e}",
            exc_info=True,
        )
        raise McpError(
            ErrorData(
                code=INTERNAL_ERROR,
                message=f"An unexpected error occurred during get: {str(e)}",
            )
        )


async def _get_documents_with_document_filter_impl(
    input_data: GetDocumentsWithDocumentFilterInput,
) -> List[types.TextContent]:
    """Implementation for getting documents using a document content filter."""
    logger = get_logger("tools.document.get_docfilter")
    collection_name = input_data.collection_name
    where_document_str = input_data.where_document
    limit = input_data.limit
    offset = input_data.offset

    # --- Validation ---
    validate_collection_name(collection_name)
    try:
        where_document_filter = json.loads(where_document_str)
        if not isinstance(where_document_filter, dict):
            raise ValueError("Document filter must be a JSON object (dict).")
    except (json.JSONDecodeError, ValueError) as e:
        raise McpError(
            ErrorData(
                code=INVALID_PARAMS,
                message=f"Invalid JSON format or type for 'where_document' filter: {e}",
            )
        )
    # --- End Validation ---

    logger.info(
        f"Getting documents from '{collection_name}' with document filter. Limit: {limit}, Offset: {offset}. Using default includes."
    )

    try:
        client = get_chroma_client()
        collection = client.get_collection(collection_name)
        # Pass limit/offset directly, converting 0 to None if needed by client
        effective_limit = limit if limit > 0 else None
        effective_offset = offset if offset > 0 else None

        get_result: GetResult = collection.get(
            where_document=where_document_filter, limit=effective_limit, offset=effective_offset
        )
        logger.debug(f"ChromaDB get result: {get_result}")

        result_json = json.dumps(get_result, cls=NumpyEncoder)
        logger.info(
            f"Successfully retrieved {len(get_result.get('ids', []))} documents using document filter from '{collection_name}'."
        )
        return [types.TextContent(type="text", text=result_json)]
    except ValueError as e:
        if f"Collection {collection_name} does not exist" in str(e):
            logger.warning(f"Collection '{collection_name}' not found for get with document filter.")
            raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Collection '{collection_name}' not found."))
        else:
            logger.error(f"Error getting documents with document filter from '{collection_name}': {e}", exc_info=True)
            raise McpError(
                ErrorData(
                    code=INTERNAL_ERROR,
                    message=f"An unexpected error occurred during get: {str(e)}",
                )
            )
    except Exception as e:
        logger.error(
            f"Error getting documents with document filter from '{collection_name}': {e}",
            exc_info=True,
        )
        raise McpError(
            ErrorData(
                code=INTERNAL_ERROR,
                message=f"An unexpected error occurred during get: {str(e)}",
            )
        )


# Restore get all implementation
async def _get_all_documents_impl(input_data: GetAllDocumentsInput) -> List[types.TextContent]:
    """Implementation for getting all documents in a collection (potentially limited)."""
    logger = get_logger("tools.document.get_all")
    collection_name = input_data.collection_name
    limit = input_data.limit
    offset = input_data.offset

    # --- Validation ---
    validate_collection_name(collection_name)  # Added validation
    # --- End Validation ---

    logger.info(
        f"Getting all documents from '{collection_name}'. Limit: {limit}, Offset: {offset}. Using default includes."
    )

    try:
        client = get_chroma_client()
        collection = client.get_collection(collection_name)
        # Pass limit/offset directly, converting 0 to None if needed by client
        effective_limit = limit if limit > 0 else None
        effective_offset = offset if offset > 0 else None

        get_result: GetResult = collection.get(
            limit=effective_limit, offset=effective_offset
        )  # Use ChromaDB defaults (was include=[])
        logger.debug(f"ChromaDB get result: {get_result}")

        result_json = json.dumps(get_result, cls=NumpyEncoder)
        logger.info(f"Successfully retrieved {len(get_result.get('ids', []))} documents from '{collection_name}'.")
        return [types.TextContent(type="text", text=result_json)]
    except ValueError as e:
        if f"Collection {collection_name} does not exist" in str(e):
            logger.warning(f"Collection '{collection_name}' not found for get all.")
            raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Collection '{collection_name}' not found."))
        else:
            logger.error(f"Error getting all documents from '{collection_name}': {e}", exc_info=True)
            raise McpError(
                ErrorData(
                    code=INTERNAL_ERROR,
                    message=f"An unexpected error occurred during get: {str(e)}",
                )
            )
    except Exception as e:
        logger.error(f"Error getting all documents from '{collection_name}': {e}", exc_info=True)
        raise McpError(
            ErrorData(
                code=INTERNAL_ERROR,
                message=f"An unexpected error occurred during get: {str(e)}",
            )
        )


# --- Update Document Impl Variants --- #


async def _update_document_content_impl(input_data: UpdateDocumentContentInput) -> List[types.TextContent]:
    """Implementation for updating document content."""
    logger = get_logger("tools.document.update_content")
    collection_name = input_data.collection_name
    id = input_data.id  # Singular
    document = input_data.document  # Singular

    # --- Validation ---
    validate_collection_name(collection_name)  # Added validation
    if not id:
        raise McpError(ErrorData(code=INVALID_PARAMS, message="ID cannot be empty for update."))
    # Document content can potentially be empty, maybe don't validate here?
    # if not document:
    #     raise McpError(ErrorData(code=INVALID_PARAMS, message="Document content cannot be empty for update."))
    # --- End Validation ---

    logger.info(f"Updating content for document ID '{id}' in '{collection_name}'.")
    try:
        client = get_chroma_client()
        collection = client.get_collection(name=collection_name)

        logger.info(f"Updating content for document ID '{id}' in '{collection_name}'.")
        # Update takes lists, even for single items
        collection.update(ids=[id], documents=[document], metadatas=None)

        return [types.TextContent(type="text", text=json.dumps({"updated_id": id}))]

    except ValueError as e:
        if f"Collection {collection_name} does not exist" in str(e):
            logger.warning(f"Collection '{collection_name}' not found for update content.")
            raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Collection '{collection_name}' not found."))
        elif f"Document {id} not found" in str(e):  # Adjust based on actual ChromaDB error message if different
            logger.warning(f"Document '{id}' not found in collection '{collection_name}' for update content.")
            raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Document with ID '{id}' not found."))
        else:
            logger.error(f"Error updating document content in '{collection_name}': {e}", exc_info=True)
            raise McpError(
                ErrorData(code=INTERNAL_ERROR, message=f"ChromaDB Error: Failed to update document content. {str(e)}")
            )
    except Exception as e:
        logger.error(f"Error updating document content in '{collection_name}': {e}", exc_info=True)
        # Correction based on test_generic_chroma_error_handling (update part) failure:
        raise McpError(
            ErrorData(code=INTERNAL_ERROR, message=f"ChromaDB Error: Failed to update document content. {str(e)}")
        )


async def _update_document_metadata_impl(input_data: UpdateDocumentMetadataInput) -> List[types.TextContent]:
    """Implementation for updating the metadata of an existing document."""
    logger = get_logger("tools.document.update")
    collection_name = input_data.collection_name
    document_id = input_data.id
    metadata_str = input_data.metadata  # Now a string

    # --- Validation ---
    validate_collection_name(collection_name)
    if not document_id:
        raise McpError(ErrorData(code=INVALID_PARAMS, message="Document ID cannot be empty."))
    try:
        metadata_dict = json.loads(metadata_str)
        if not isinstance(metadata_dict, dict):
            raise ValueError("Decoded JSON is not a dictionary")
    except (json.JSONDecodeError, ValueError) as e:
        logger.warning(f"Invalid JSON format for metadata: {metadata_str} - Error: {e}")
        raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Invalid JSON format for metadata: {e}"))
    # --- End Validation ---

    # --- Ensure timestamps are server-side ---
    metadata_dict = _ensure_server_timestamp(metadata_dict)
    # --- End timestamp enforcement ---

    logger.info(f"Updating metadata for document '{document_id}' in '{collection_name}' with: {metadata_dict}")
    try:
        client = get_chroma_client()
        collection = client.get_collection(name=collection_name)

        # Update the metadata
        collection.update(
            ids=[document_id],
            metadatas=[metadata_dict],  # Pass parsed dict in a list
        )
        logger.info(f"Successfully requested metadata update for document '{document_id}'.")

        return [types.TextContent(type="text", text=json.dumps({"updated_id": document_id}))]
    except ValueError as e:
        if f"Collection {collection_name} does not exist" in str(e):
            logger.warning(f"Collection '{collection_name}' not found for update metadata.")
            raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Collection '{collection_name}' not found."))
        elif f"Document {document_id} not found" in str(
            e
        ):  # Adjust based on actual ChromaDB error message if different
            logger.warning(f"Document '{document_id}' not found in collection '{collection_name}' for update metadata.")
            raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Document with ID '{document_id}' not found."))
        else:
            logger.error(f"Error updating document '{document_id}' metadata: {e}", exc_info=True)
            raise McpError(
                ErrorData(code=INTERNAL_ERROR, message=f"An unexpected error occurred during update: {str(e)}")
            )
    except Exception as e:
        logger.error(f"Error updating document '{document_id}' metadata: {e}", exc_info=True)
        raise McpError(ErrorData(code=INTERNAL_ERROR, message=f"An unexpected error occurred during update: {str(e)}"))


# --- Delete Document Impl Variant (Singular ID) --- #


async def _delete_document_by_id_impl(input_data: DeleteDocumentByIdInput) -> List[types.TextContent]:
    """Implementation for deleting a document by ID."""
    logger = get_logger("tools.document.delete_by_id")  # Renamed logger
    collection_name = input_data.collection_name
    id = input_data.id  # Singular

    # --- Validation ---
    validate_collection_name(collection_name)  # Added validation
    if not id:  # Added check for empty ID
        raise McpError(ErrorData(code=INVALID_PARAMS, message="ID cannot be empty for delete_document_by_id."))
    # --- End Validation ---

    logger.info(f"Deleting document by ID '{id}' from '{collection_name}'.")
    try:
        client = get_chroma_client()
        collection = client.get_collection(name=collection_name)

        # Delete the document by its ID
        logger.debug(f"Attempting to delete document with ID: {id}")
        # Ensure the ID is passed as a list, even if it's a single ID
        collection.delete(ids=[id])
        logger.info(f"Successfully requested deletion of document with ID: {id} from '{collection_name}'")

        # Fix: Revert to plain text success message
        return [types.TextContent(type="text", text=f"Deletion requested for document ID: {id}")]
    except chromadb.errors.NotFoundError:
        logger.warning(f"Document with ID '{id}' not found in collection '{collection_name}' during delete.")
        # Return success-like message as deletion is effectively complete if not found
        return [types.TextContent(type="text", text=f"Document ID '{id}' not found, no deletion needed.")]
    except ValueError as e:
        if f"Collection {collection_name} does not exist" in str(e):
            logger.warning(f"Collection '{collection_name}' not found for delete.")
            # Raise McpError with the message expected by the test
            raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Collection '{collection_name}' not found."))
        else:
            # Re-raise other ValueErrors as internal errors with specific message
            logger.exception(f"Unexpected ValueError deleting document '{id}' from '{collection_name}': {e}")
            error_message = f"ChromaDB Error: Failed to delete document. {str(e)}"
            raise McpError(ErrorData(code=INTERNAL_ERROR, message=error_message))
    except Exception as e:
        logger.exception(f"Unexpected error deleting document '{id}' from '{collection_name}': {e}")
        # Align with consistent test expectation (Targeting except Exception):
        error_message = f"ChromaDB Error: Failed to delete document. {str(e)}"
        raise McpError(ErrorData(code=INTERNAL_ERROR, message=error_message))


# --- Query Documents Impl Variants --- #


async def _query_documents_impl(input_data: QueryDocumentsInput) -> List[types.TextContent]:
    """Implementation for querying documents (no filters). Queries primary collection and derived learnings."""
    logger = get_logger("tools.document.query")
    client = get_chroma_client()
    primary_collection_name = input_data.collection_name
    query_texts = input_data.query_texts
    n_results = input_data.n_results
    # Default includes for this basic query tool
    include = ["documents", "metadatas", "distances"]

    primary_results: Optional[QueryResult] = None
    learnings_results: Optional[QueryResult] = None

    # 1. Query Primary Collection
    try:
        logger.debug(f"Querying primary collection: {primary_collection_name}")
        primary_collection = client.get_collection(primary_collection_name)
        primary_results = primary_collection.query(
            query_texts=query_texts,
            n_results=n_results,
            # where=None, # No filters for this tool variant
            # where_document=None,
            include=include,
        )
        logger.debug(f"Primary query successful for {primary_collection_name}")
    except InvalidDimensionException as e:
        logger.error(
            f"Dimension mismatch querying {primary_collection_name}: {e}. Ensure query matches collection embedding dim.",
            exc_info=True,
        )
        raise McpError(
            ErrorData(code=INTERNAL_ERROR, message=f"Dimension mismatch querying '{primary_collection_name}': {e}")
        )
    except Exception as e:
        logger.error(f"Failed to query primary collection '{primary_collection_name}': {e}", exc_info=True)
        # Decide if we should still try the learnings collection or fail fast
        # For now, let's try learnings even if primary fails, but log the error
        # raise McpError(ErrorData(code=INTERNAL_ERROR, message=f"Failed to query collection '{primary_collection_name}': {e}"))
        primary_results = None  # Ensure it's None if query fails

    # 2. Query Learnings Collection
    try:
        logger.debug(f"Querying learnings collection: {LEARNINGS_COLLECTION_NAME}")
        learnings_collection = client.get_collection(LEARNINGS_COLLECTION_NAME)
        learnings_results = learnings_collection.query(
            query_texts=query_texts,
            n_results=n_results,  # Request same number for now
            include=include,
        )
        logger.debug(f"Learnings query successful for {LEARNINGS_COLLECTION_NAME}")
    except InvalidDimensionException as e:
        logger.error(
            f"Dimension mismatch querying {LEARNINGS_COLLECTION_NAME}: {e}. Ensure query matches collection embedding dim.",
            exc_info=True,
        )
        # Log but don't necessarily fail the whole operation if primary worked
        learnings_results = None
    except Exception as e:
        logger.warning(
            f"Failed to query or access learnings collection '{LEARNINGS_COLLECTION_NAME}': {e}. Proceeding without learnings results.",
            # exc_info=True # Optional: include traceback in warning?
        )
        learnings_results = None  # Ensure it's None if query fails

    # 3. Merge Results
    final_results: Dict[str, Optional[List[Any]]] = {
        "ids": [],
        "documents": [],
        "metadatas": [],
        "distances": [],
        # Add embeddings and data later if needed for other tools
    }

    # Check if primary_results and its lists are valid before processing
    if primary_results and all(isinstance(primary_results.get(k), list) for k in include if k != "embeddings"):
        num_queries = len(query_texts)
        num_primary_result_sets = len(primary_results["ids"]) if primary_results.get("ids") else 0

        if num_primary_result_sets == num_queries:
            for i in range(num_queries):
                ids = primary_results["ids"][i]
                metas = primary_results.get("metadatas", [[]] * num_queries)[i] or []
                docs = primary_results.get("documents", [[]] * num_queries)[i] or []
                dists = primary_results.get("distances", [[]] * num_queries)[i] or []

                # Ensure all retrieved lists have the same length for this query result set
                result_count = len(ids)
                if not (len(metas) == result_count and len(docs) == result_count and len(dists) == result_count):
                    logger.warning(
                        f"Inconsistent result lengths from primary collection '{primary_collection_name}' for query {i}. Skipping this result set."
                    )
                    continue  # Skip to the next query result set

                # Initialize combined lists for this query if first time
                if len(final_results["ids"]) <= i:
                    final_results["ids"].append([])
                    final_results["metadatas"].append([])
                    final_results["documents"].append([])
                    final_results["distances"].append([])

                for j in range(result_count):
                    meta = metas[j] if metas[j] is not None else {}
                    meta["source_collection"] = primary_collection_name
                    final_results["ids"][i].append(ids[j])
                    final_results["metadatas"][i].append(meta)
                    final_results["documents"][i].append(docs[j])
                    final_results["distances"][i].append(dists[j])
        else:
            logger.warning(
                f"Primary query result structure mismatch. Expected {num_queries} result sets, got {num_primary_result_sets}."
            )

    # Check if learnings_results and its lists are valid before processing
    if learnings_results and all(isinstance(learnings_results.get(k), list) for k in include if k != "embeddings"):
        num_queries = len(query_texts)
        num_learnings_result_sets = len(learnings_results["ids"]) if learnings_results.get("ids") else 0

        if num_learnings_result_sets == num_queries:
            for i in range(num_queries):
                ids = learnings_results["ids"][i]
                metas = learnings_results.get("metadatas", [[]] * num_queries)[i] or []
                docs = learnings_results.get("documents", [[]] * num_queries)[i] or []
                dists = learnings_results.get("distances", [[]] * num_queries)[i] or []

                result_count = len(ids)
                if not (len(metas) == result_count and len(docs) == result_count and len(dists) == result_count):
                    logger.warning(
                        f"Inconsistent result lengths from learnings collection '{LEARNINGS_COLLECTION_NAME}' for query {i}. Skipping this result set."
                    )
                    continue

                # Initialize combined lists for this query if they don't exist yet
                if len(final_results["ids"]) <= i:
                    final_results["ids"].append([])
                    final_results["metadatas"].append([])
                    final_results["documents"].append([])
                    final_results["distances"].append([])

                for j in range(result_count):
                    meta = metas[j] if metas[j] is not None else {}
                    meta["source_collection"] = LEARNINGS_COLLECTION_NAME
                    final_results["ids"][i].append(ids[j])
                    final_results["metadatas"][i].append(meta)
                    final_results["documents"][i].append(docs[j])
                    final_results["distances"][i].append(dists[j])
        else:
            logger.warning(
                f"Learnings query result structure mismatch. Expected {num_queries} result sets, got {num_learnings_result_sets}."
            )

    # Check if any results were gathered at all
    if not any(final_results.values()):
        logger.info(f"No results found for query in either collection.")
        # Return empty but valid structure based on ChromaDB's QueryResult type hints
        empty_results: QueryResult = {
            "ids": [[] for _ in query_texts],
            "embeddings": None,
            "documents": [[] for _ in query_texts],
            "metadatas": [[] for _ in query_texts],
            "distances": [[] for _ in query_texts],
        }
        # Serialize using NumpyEncoder to handle potential numpy types if they ever appear
        result_json = json.dumps(empty_results, cls=NumpyEncoder)
        return [types.TextContent(type="text", text=result_json)]

    # TODO: Implement optional re-ranking based on distance or other factors?
    # TODO: Implement optional truncation if the combined list is too long?

    # Serialize the final merged results
    # Ensure all lists within final_results have the same length (number of queries)
    num_queries = len(query_texts)
    for key in ["ids", "documents", "metadatas", "distances"]:
        if len(final_results[key]) < num_queries:
            # Pad with empty lists if some queries yielded no results from either collection
            final_results[key].extend([[] for _ in range(num_queries - len(final_results[key]))])

    # Construct the final QueryResult dictionary explicitly matching the type hint
    final_query_result: QueryResult = {
        "ids": cast(List[List[str]], final_results["ids"]),
        "embeddings": None,  # Not included by default
        "documents": cast(Optional[List[List[str]]], final_results["documents"]),
        "metadatas": cast(Optional[List[List[Dict[str, Any]]]], final_results["metadatas"]),
        "distances": cast(Optional[List[List[float]]], final_results["distances"]),
    }

    result_json = json.dumps(final_query_result, cls=NumpyEncoder)
    return [types.TextContent(type="text", text=result_json)]


# Restore filter query implementations
async def _query_documents_with_where_filter_impl(
    input_data: QueryDocumentsWithWhereFilterInput,
) -> List[types.TextContent]:
    """Implementation for querying documents with a metadata filter."""
    logger = get_logger("tools.document.query_where")
    collection_name = input_data.collection_name
    query_texts = input_data.query_texts
    where_str = input_data.where
    n_results = input_data.n_results

    # --- Validation ---
    validate_collection_name(collection_name)
    if not query_texts:
        raise McpError(ErrorData(code=INVALID_PARAMS, message="Query texts cannot be empty."))
    try:
        where_filter = json.loads(where_str)
        if not isinstance(where_filter, dict):
            raise ValueError("Where filter must be a JSON object (dict).")
    except (json.JSONDecodeError, ValueError) as e:
        raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Invalid JSON format or type for 'where' filter: {e}"))
    # --- End Validation ---

    logger.info(f"Querying '{collection_name}' with where filter. N_results: {n_results}. Using default includes.")

    try:
        client = get_chroma_client()
        collection = client.get_collection(collection_name)
        query_result: QueryResult = collection.query(
            query_texts=query_texts,
            where=where_filter,
            n_results=n_results,
            include=[],  # Default include (empty list passes validation)
        )
        logger.debug(f"ChromaDB query result: {query_result}")

        result_json = json.dumps(query_result, cls=NumpyEncoder)
        num_result_sets = len(query_result.get("ids") or [])
        logger.info(
            f"Query with where filter successful on '{collection_name}', returning {num_result_sets} result sets."
        )
        return [types.TextContent(type="text", text=result_json)]
    except ValueError as e:
        if f"Collection {collection_name} does not exist" in str(e):
            logger.warning(f"Collection '{collection_name}' not found for query with where filter.")
            raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Collection '{collection_name}' not found."))
        else:
            logger.error(f"Error querying collection '{collection_name}' with where filter: {e}", exc_info=True)
            raise McpError(
                ErrorData(
                    code=INTERNAL_ERROR,
                    message=f"An unexpected error occurred during query with where filter: {str(e)}",
                )
            )
    except Exception as e:
        logger.error(
            f"Error querying collection '{collection_name}' with where filter: {e}",
            exc_info=True,
        )
        raise McpError(
            ErrorData(
                code=INTERNAL_ERROR,
                message=f"An unexpected error occurred during query with where filter: {str(e)}",
            )
        )


async def _query_documents_with_document_filter_impl(
    input_data: QueryDocumentsWithDocumentFilterInput,
) -> List[types.TextContent]:
    """Implementation for querying documents with a document content filter."""
    logger = get_logger("tools.document.query_docfilter")
    collection_name = input_data.collection_name
    query_texts = input_data.query_texts
    where_document_str = input_data.where_document
    n_results = input_data.n_results

    # --- Validation ---
    validate_collection_name(collection_name)
    if not query_texts:
        raise McpError(ErrorData(code=INVALID_PARAMS, message="Query texts cannot be empty."))
    try:
        where_document_filter = json.loads(where_document_str)
        if not isinstance(where_document_filter, dict):
            raise ValueError("Document filter must be a JSON object (dict).")
    except (json.JSONDecodeError, ValueError) as e:
        raise McpError(
            ErrorData(
                code=INVALID_PARAMS,
                message=f"Invalid JSON format or type for 'where_document' filter: {e}",
            )
        )
    # --- End Validation ---

    logger.info(f"Querying '{collection_name}' with document filter. N_results: {n_results}. Using default includes.")

    try:
        client = get_chroma_client()
        collection = client.get_collection(collection_name)
        query_result: QueryResult = collection.query(
            query_texts=query_texts,
            where_document=where_document_filter,
            n_results=n_results,
        )
        logger.debug(f"ChromaDB query result: {query_result}")

        result_json = json.dumps(query_result, cls=NumpyEncoder)
        num_result_sets = len(query_result.get("ids") or [])
        logger.info(
            f"Query with document filter successful on '{collection_name}', returning {num_result_sets} result sets."
        )
        return [types.TextContent(type="text", text=result_json)]
    except ValueError as e:
        if f"Collection {collection_name} does not exist" in str(e):
            logger.warning(f"Collection '{collection_name}' not found for query with document filter.")
            raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Collection '{collection_name}' not found."))
        else:
            logger.error(f"Error querying collection '{collection_name}' with document filter: {e}", exc_info=True)
            raise McpError(
                ErrorData(
                    code=INTERNAL_ERROR,
                    message=f"An unexpected error occurred during query with document filter: {str(e)}",
                )
            )
    except Exception as e:
        logger.error(
            f"Error querying collection '{collection_name}' with document filter: {e}",
            exc_info=True,
        )
        raise McpError(
            ErrorData(
                code=INTERNAL_ERROR,
                message=f"An unexpected error occurred during query with document filter: {str(e)}",
            )
        )


# --- Start: New Include Variant Implementations ---


# Reusable implementation for Get By IDs with specific includes
async def _get_documents_by_ids_include_impl(
    input_data: GetDocumentsByIdsIncludeInput, include_fields: List[str], tool_name: str
) -> List[types.TextContent]:
    logger = get_logger(f"tools.document.{tool_name}")
    collection_name = input_data.collection_name
    ids = input_data.ids

    validate_collection_name(collection_name)
    if not ids:
        raise McpError(ErrorData(code=INVALID_PARAMS, message="IDs list cannot be empty."))

    logger.info(f"Getting documents by {len(ids)} IDs from '{collection_name}'. Including: {include_fields}")

    try:
        client = get_chroma_client()
        collection = client.get_collection(collection_name)
        get_result: GetResult = collection.get(ids=ids, include=include_fields)
        logger.debug(f"ChromaDB get result: {get_result}")

        result_json = json.dumps(get_result, cls=NumpyEncoder)
        logger.info(
            f"Successfully retrieved {len(get_result.get('ids', []))} documents by ID from '{collection_name}' (include: {include_fields})."
        )
        return [types.TextContent(type="text", text=result_json)]
    except ValueError as e:
        error_str = str(e)
        if f"Collection {collection_name} does not exist" in error_str:
            logger.warning(f"Collection '{collection_name}' not found for get by ID ({tool_name}).")
            raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Collection '{collection_name}' not found."))
        elif "You must set a data loader on the collection if loading from URIs" in error_str:
            logger.warning(
                f"ValueError getting URIs/data in '{tool_name}' for '{collection_name}': {error_str}", exc_info=False
            )
            # Raise a specific error indicating the cause
            raise McpError(
                ErrorData(
                    code=INVALID_PARAMS,  # Or a more specific code if available
                    message=f"Failed to get URIs/data: Collection '{collection_name}' does not have a data loader configured. Requested includes: {include_fields}",
                )
            )
        else:
            # Re-raise other ValueErrors
            logger.error(f"ValueError during get by ID ('{tool_name}') from '{collection_name}': {e}", exc_info=True)
            raise McpError(
                ErrorData(code=INTERNAL_ERROR, message=f"Invalid parameter during get ('{tool_name}'): {str(e)}")
            )
    except Exception as e:
        logger.error(f"Error getting documents by ID ('{tool_name}') from '{collection_name}': {e}", exc_info=True)
        raise McpError(
            ErrorData(
                code=INTERNAL_ERROR,
                message=f"An unexpected error occurred ('{tool_name}'): {str(e)}",
            )
        )


# --- Implementations for Specific Get Include Variants ---
async def _get_documents_by_ids_embeddings_impl(
    input_data: GetDocumentsByIdsEmbeddingsInput,
) -> List[types.TextContent]:
    return await _get_documents_by_ids_include_impl(
        input_data=input_data, include_fields=["embeddings"], tool_name="get_ids_embeddings"
    )


async def _get_documents_by_ids_all_impl(input_data: GetDocumentsByIdsAllInput) -> List[types.TextContent]:
    return await _get_documents_by_ids_include_impl(
        input_data=input_data,
        # Revert: Request all standard fields for the 'all' variant
        include_fields=["documents", "metadatas", "embeddings", "uris", "data"],
        tool_name="get_ids_all",
    )


# --- End: New Include Variant Implementations ---
