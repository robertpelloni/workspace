"""
Collection management tools for ChromaDB operations.
"""

import json
import logging
import chromadb
from chromadb.api.client import ClientAPI
from chromadb.errors import InvalidDimensionException
import numpy as np
import time  # Add explicit import for time
import datetime  # Add for ISO format dates

from pydantic import BaseModel, Field, ConfigDict
from typing import Any, Dict, List, Optional, Union, cast
from dataclasses import dataclass

from chromadb.api.types import CollectionMetadata, GetResult, QueryResult
from chromadb.errors import InvalidDimensionException

from mcp import types
from mcp.types import ErrorData, INVALID_PARAMS, INTERNAL_ERROR
from mcp.shared.exceptions import McpError

from ..utils import (
    get_logger,
    get_chroma_client,
    get_embedding_function,
    get_server_config,
    ValidationError,
    ClientError,
    ConfigurationError,
)
from ..utils.config import get_collection_settings, validate_collection_name
from ..types import ChromaClientConfig


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


# --- Pydantic Input Models for Collection Tools ---


class CreateCollectionInput(BaseModel):
    """Input model for creating a collection (using default settings)."""

    collection_name: str = Field(
        ..., description="The name for the new collection. Must adhere to ChromaDB naming conventions."
    )

    model_config = ConfigDict(extra="forbid")


class CreateCollectionWithMetadataInput(BaseModel):
    """Input model for creating a collection with specified metadata (as JSON string)."""

    collection_name: str = Field(
        ..., description="The name for the new collection. Must adhere to ChromaDB naming conventions."
    )
    # Change type to string, expect JSON string from client
    metadata: str = Field(
        ...,
        description='Metadata and settings as a JSON string (e.g., \'{"description": "...", "settings": {"hnsw:space": "cosine"}}\' ).',
    )

    model_config = ConfigDict(extra="forbid")


class ListCollectionsInput(BaseModel):
    """Input model for listing collections."""

    limit: int = Field(default=0, ge=0, description="Maximum number of collections to return. 0 for no limit.")
    offset: int = Field(default=0, ge=0, description="Number of collections to skip. 0 for default.")
    name_contains: str = Field(
        default="", description="Filter collections by name (case-insensitive contains). Empty for no filter."
    )


class GetCollectionInput(BaseModel):
    """Input model for retrieving collection information."""

    collection_name: str = Field(..., description="The name of the collection to retrieve information for.")


class RenameCollectionInput(BaseModel):
    """Input model for renaming a collection."""

    collection_name: str = Field(..., description="The current name of the collection to rename.")
    new_name: str = Field(..., description="The new name for the collection.")


class DeleteCollectionInput(BaseModel):
    """Input model for deleting a collection."""

    collection_name: str = Field(..., description="The name of the collection to delete.")


class PeekCollectionInput(BaseModel):
    """Input model for peeking into a collection."""

    collection_name: str = Field(..., description="The name of the collection to peek into.")
    limit: int = Field(
        default=10,
        ge=1,
        description="Maximum number of documents to return (defaults to 10). Must be >= 1.",
    )


# --- End Pydantic Input Models ---


def _reconstruct_metadata(metadata: Optional[Dict[str, Any]]) -> Dict[str, Any]:
    """Reconstructs the structured metadata (with 'settings') from ChromaDB's internal format."""
    if not metadata:
        return {}

    reconstructed = {}
    settings = {}
    for key, value in metadata.items():
        setting_key_to_store = None
        # Check for flattened setting keys
        if key.startswith("chroma:setting:"):
            # Convert 'chroma_setting_hnsw_space' back to 'hnsw:space'
            original_key = key[len("chroma:setting:") :].replace("_", ":")
            setting_key_to_store = original_key
        # Also recognize common raw keys like hnsw:*
        elif key.startswith("hnsw:"):
            setting_key_to_store = key

        if setting_key_to_store:
            settings[setting_key_to_store] = value
        # Explicitly check for 'description' as it's handled separately
        elif key == "description":
            reconstructed[key] = value
        # Store other keys directly (custom user keys)
        elif not key.startswith("chroma:"):  # Avoid other potential internal chroma keys
            reconstructed[key] = value

    if settings:
        reconstructed["settings"] = settings

    return reconstructed


# --- Implementation Functions ---


# Signature changed to return List[Content]
async def _create_collection_impl(input_data: CreateCollectionInput) -> List[types.TextContent]:
    """Implementation for creating a new collection.

    Returns:
        List containing a single TextContent object with JSON details of the created collection.
    Raises:
        McpError: If validation fails, the collection already exists, or another error occurs.
    """
    logger = get_logger("tools.collection")
    collection_name = input_data.collection_name
    # REMOVE: metadata = input_data.metadata (Field no longer exists)

    try:
        validate_collection_name(collection_name)

        client = get_chroma_client()
        # Get the configured default embedding function name from the global config
        server_config = get_server_config()
        # Use the correctly named field
        ef_name = server_config.embedding_function_name

        # Instantiate the configured embedding function
        embedding_function = get_embedding_function(ef_name)
        logger.info(f"Using configured embedding function: '{ef_name}'")

        # Handle metadata and default settings
        # REMOVE: Logic branch checking for provided metadata
        # if metadata:
        #     ...
        # else:
        # Always apply default settings for this base tool variant
        default_settings = get_collection_settings()
        final_metadata = {f"chroma:setting:{k.replace(':', '_')}": v for k, v in default_settings.items()}
        logger.debug(f"Creating collection '{collection_name}' with default settings: {final_metadata}")

        # Create the collection
        collection = client.create_collection(
            name=collection_name,
            metadata=final_metadata,  # Pass the processed metadata
            embedding_function=embedding_function,  # Pass the instantiated default EF
            get_or_create=False,  # Explicitly False to ensure creation error
        )

        # Prepare success result data
        count = collection.count()
        result_data = {
            "name": collection.name,
            "id": str(collection.id),  # Ensure ID is string if it's UUID
            "metadata": _reconstruct_metadata(collection.metadata),
            "count": count,
        }
        result_json = json.dumps(result_data, indent=2)
        # Return content list directly
        return [types.TextContent(type="text", text=result_json)]

    except ValidationError as e:
        logger.warning(f"Validation error creating collection '{collection_name}': {e}")
        # Raise McpError
        raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Validation Error: {str(e)}"))
    except ValueError as e:
        if f"Collection {collection_name} already exists." in str(e):
            logger.warning(f"Collection '{collection_name}' already exists.")
            # Raise McpError
            raise McpError(
                ErrorData(code=INVALID_PARAMS, message=f"Tool Error: Collection '{collection_name}' already exists.")
            )
        else:
            logger.error(f"Validation error during collection creation '{collection_name}': {e}", exc_info=True)
            # Raise McpError
            raise McpError(
                ErrorData(
                    code=INVALID_PARAMS,
                    message=f"Tool Error: Invalid parameter during collection creation. Details: {e}",
                )
            )
    except InvalidDimensionException as e:
        logger.error(f"Dimension error creating collection '{collection_name}': {e}", exc_info=True)
        # Raise McpError
        raise McpError(
            ErrorData(code=INTERNAL_ERROR, message=f"ChromaDB Error: Invalid dimension configuration. {str(e)}")
        )
    except Exception as e:
        logger.error(f"Unexpected error creating collection '{collection_name}': {e}", exc_info=True)
        # Raise McpError
        raise McpError(
            ErrorData(
                code=INTERNAL_ERROR,
                message=f"Tool Error: An unexpected error occurred while creating collection '{collection_name}'. Details: {str(e)}",
            )
        )


# Signature changed to return List[Content]
async def _list_collections_impl(input_data: ListCollectionsInput) -> List[types.TextContent]:
    """Lists collections, optionally filtering by name and applying pagination.

    Args:
        input_data: A ListCollectionsInput object containing validated arguments.

    Returns:
        A list containing a single TextContent object with a JSON string
        detailing the paginated collection names and counts.

    Raises:
        McpError: If a validation error occurs or an unexpected exception
                  happens during client interaction.
    """
    logger = get_logger("tools.collection")
    limit = input_data.limit
    offset = input_data.offset
    name_contains = input_data.name_contains

    try:
        # Pydantic handles validation for limit/offset >= 0

        client = get_chroma_client()
        collections = client.list_collections()
        # Determine list of collection names from raw collection values
        if all(isinstance(c, str) for c in collections):
            names_list = collections
        else:
            names_list = [ci["name"] for c in collections for ci in (_get_collection_info(c),) if "name" in ci]

        # Apply filtering if name_contains is provided
        if name_contains:
            filtered_names = [n for n in names_list if name_contains.lower() in n.lower()]
        else:
            filtered_names = names_list

        total_matching_count = len(filtered_names)

        # Apply pagination
        start_index = offset if offset > 0 else 0
        if limit > 0:
            paginated_names = filtered_names[start_index : start_index + limit]
        else:
            paginated_names = filtered_names[start_index:]

        # Prepare result
        result_data = {
            "collection_names": paginated_names,
            "total_count": total_matching_count,
            "limit": limit,
            "offset": offset,
        }
        result_json = json.dumps(result_data, indent=2)
        return [types.TextContent(type="text", text=result_json)]

    except Exception as e:
        logger.error(f"Error listing collections: {e}", exc_info=True)
        # Raise McpError
        raise McpError(
            ErrorData(code=INTERNAL_ERROR, message=f"Tool Error: Error listing collections. Details: {str(e)}")
        )


# Signature changed to return List[Content]
async def _get_collection_impl(input_data: GetCollectionInput) -> List[types.TextContent]:
    """Retrieves details about a specific ChromaDB collection.

    Returns:
        A list containing a single TextContent object with JSON details of the collection.

    Raises:
        McpError: If the collection is not found or another error occurs.
        # ValidationError is caught and wrapped in McpError
    """
    logger = get_logger("tools.collection")
    collection_name = input_data.collection_name

    try:
        # --- Validation Inside ---
        validate_collection_name(collection_name)
        # -------------------------
        client = get_chroma_client()
        # Use get_collection which raises an error if not found
        collection = client.get_collection(name=collection_name)

        count = collection.count()
        # Process peek results carefully, handle potential large embeddings
        peek_results = None
        try:
            # Limit peek to avoid large payloads
            peek_results = collection.peek(limit=5)
            # Remove embeddings if present, as they can be large and aren't needed for info
            if peek_results and "embeddings" in peek_results:
                del peek_results["embeddings"]
        except Exception as peek_err:
            logger.warning(f"Could not peek into collection '{collection_name}': {peek_err}")
            peek_results = {"error": f"Could not peek: {str(peek_err)}"}

        result_data = {
            "name": collection.name,
            "id": str(collection.id),
            "metadata": _reconstruct_metadata(collection.metadata),
            "count": count,
            "sample_entries": peek_results,  # Include processed/limited peek
        }
        result_json = json.dumps(result_data, indent=2)
        # Return content list directly
        return [types.TextContent(type="text", text=result_json)]

    except ValueError as e:
        # Handle case where collection is not found
        error_str = str(e).lower()
        not_found = False
        if f"collection {collection_name} does not exist." in error_str:
            not_found = True
        if f"collection {collection_name} not found" in error_str:
            not_found = True

        if not_found:
            logger.warning(f"Collection '{collection_name}' not found.")
            raise McpError(
                ErrorData(code=INVALID_PARAMS, message=f"Tool Error: Collection '{collection_name}' not found.")
            )
        else:
            # Handle other ValueErrors
            logger.error(f"Value error getting collection '{collection_name}': {e}", exc_info=True)
            raise McpError(
                ErrorData(
                    code=INVALID_PARAMS, message=f"Tool Error: Invalid parameter getting collection. Details: {e}"
                )
            )
    except ValidationError as e:
        logger.warning(f"Validation error getting collection '{collection_name}': {e}")
        raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Validation Error: {str(e)}"))
    except Exception as e:
        logger.error(f"Unexpected error getting collection '{collection_name}': {e}", exc_info=True)
        # Raise McpError
        raise McpError(
            ErrorData(
                code=INTERNAL_ERROR,
                message=f"Tool Error: An unexpected error occurred while getting collection '{collection_name}'. Details: {str(e)}",
            )
        )


# Signature changed to return List[Content]
async def _rename_collection_impl(input_data: RenameCollectionInput) -> List[types.TextContent]:
    """Implementation for renaming a collection.

    Returns:
        List containing a single TextContent object confirming the rename.

    Raises:
        McpError: If validation fails (McpError used internally), collection not found, name exists, or another error occurs.
        # ValidationError is caught and wrapped in McpError
    """
    logger = get_logger("tools.collection")
    original_name = input_data.collection_name
    new_name = input_data.new_name

    try:
        # --- Validation Inside ---
        validate_collection_name(original_name)
        validate_collection_name(new_name)
        # -------------------------
        client = get_chroma_client()

        # Check if original collection exists
        logger.info(f"Attempting to rename collection '{original_name}' to '{new_name}'.")
        collection = client.get_collection(name=original_name)

        # Attempt to modify the name
        collection.modify(name=new_name)  # Use modify with the new name
        logger.info(f"Collection rename attempt from '{original_name}' to '{new_name}' completed.")

        # Return confirmation message
        return [
            types.TextContent(type="text", text=f"Collection '{original_name}' successfully renamed to '{new_name}'.")
        ]

    except ValidationError as e:
        logger.warning(f"Validation error renaming collection '{original_name}' or '{new_name}': {e}")
        # Raise McpError for validation failure
        raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Validation Error: {str(e)}"))
    except ValueError as e:
        error_str = str(e).lower()
        # Check for original not found from get_collection
        original_not_found = False
        if f"collection {original_name} does not exist." in error_str:
            original_not_found = True
        if f"collection {original_name} not found" in error_str:
            original_not_found = True

        if original_not_found:
            logger.warning(f"Cannot rename: Collection '{original_name}' not found.")
            raise McpError(
                ErrorData(code=INVALID_PARAMS, message=f"Tool Error: Collection '{original_name}' not found.")
            )

        # Check for new name exists from modify
        new_name_exists = False
        if f"collection {new_name} already exists." in error_str:
            new_name_exists = True

        if new_name_exists:
            logger.warning(f"Cannot rename: New collection name '{new_name}' already exists.")
            raise McpError(
                ErrorData(code=INVALID_PARAMS, message=f"Tool Error: Collection name '{new_name}' already exists.")
            )

        # Handle other ValueErrors
        logger.error(f"Value error renaming collection '{original_name}': {e}", exc_info=True)
        raise McpError(
            ErrorData(code=INVALID_PARAMS, message=f"Tool Error: Invalid parameter during rename. Details: {e}")
        )
    except Exception as e:
        logger.error(f"Unexpected error renaming collection '{original_name}': {e}", exc_info=True)
        # Raise McpError
        raise McpError(
            ErrorData(
                code=INTERNAL_ERROR,
                message=f"Tool Error: An unexpected error occurred renaming collection '{original_name}'. Details: {str(e)}",
            )
        )


# Signature changed to return List[Content]
async def _delete_collection_impl(input_data: DeleteCollectionInput) -> List[types.TextContent]:
    """Implementation for deleting a collection.

    Returns:
        List containing a single TextContent object confirming deletion.

    Raises:
        McpError: If the collection is not found or another error occurs.
        # ValidationError is caught and wrapped in McpError
    """
    logger = get_logger("tools.collection")
    collection_name = input_data.collection_name

    try:
        # --- Validation Inside ---
        validate_collection_name(collection_name)
        # -------------------------
        client = get_chroma_client()

        # Attempt to delete the collection directly
        logger.info(f"Attempting to delete collection '{collection_name}'.")
        client.delete_collection(name=collection_name)
        logger.info(f"Collection '{collection_name}' deleted successfully.")

        # Return confirmation message
        return [types.TextContent(type="text", text=f"Collection '{collection_name}' deleted successfully.")]

    except ValidationError as e:  # Catch validation first
        logger.warning(f"Validation error deleting collection '{collection_name}': {e}")
        raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Validation Error: {str(e)}"))
    except ValueError as e:  # Catch ValueError second (should include 'not found')
        # Handle collection not found during delete
        error_str = str(e).lower()
        not_found = False
        # Check standard ChromaDB message
        if f"collection {collection_name} does not exist." in error_str:
            not_found = True
        # Check alternate message format sometimes seen
        if f"collection named {collection_name} does not exist" in error_str:
            not_found = True
        # Check for InvalidCollectionException message if it gets wrapped
        if f"collection {collection_name} does not exist." in error_str:
            not_found = True

        if not_found:
            logger.warning(f"Collection '{collection_name}' not found for deletion.")
            raise McpError(
                ErrorData(code=INVALID_PARAMS, message=f"Tool Error: Collection '{collection_name}' not found.")
            )
        else:  # Other ValueErrors from delete_collection
            logger.error(f"Value error during delete_collection call for '{collection_name}': {e}", exc_info=True)
            raise McpError(
                ErrorData(
                    code=INVALID_PARAMS,
                    message=f"Tool Error: Invalid parameter during delete operation for '{collection_name}'. Details: {e}",
                )
            )
    except Exception as e:  # Catch generic Exception last
        logger.error(f"Unexpected error deleting collection '{collection_name}': {e}", exc_info=True)
        # Raise McpError
        raise McpError(
            ErrorData(
                code=INTERNAL_ERROR,
                message=f"Tool Error: An unexpected error occurred deleting collection '{collection_name}'. Details: {str(e)}",
            )
        )


# Signature changed to return List[Content]
async def _peek_collection_impl(input_data: PeekCollectionInput) -> List[types.TextContent]:
    """Retrieves a small sample of entries from a collection.

    Returns:
        List containing a single TextContent object with JSON results of the peek.

    Raises:
        McpError: If the collection is not found or another error occurs.
        # ValidationError is caught and wrapped in McpError
    """
    logger = get_logger("tools.collection")
    collection_name = input_data.collection_name
    limit = input_data.limit

    try:
        # --- Validation Inside ---
        validate_collection_name(collection_name)
        # -------------------------
        client = get_chroma_client()
        collection = client.get_collection(name=collection_name)

        # Call peek with the validated limit (pass directly as it has a non-zero default)
        peek_results = collection.peek(limit=limit)
        # --- DEBUG LOGGING ---
        logger.debug(f"Peek results raw type: {type(peek_results)}")
        logger.debug(f"Peek results raw content: {peek_results}")
        # --- END DEBUG LOGGING ---

        # Process results to make them JSON serializable if needed
        # Check if peek_results is not None before attempting to copy
        processed_peek = peek_results.copy() if peek_results is not None else {}
        # Convert numpy arrays (or anything with a tolist() method) to lists
        # Check existence and non-None value explicitly before processing
        if "embeddings" in processed_peek and processed_peek["embeddings"] is not None:
            # Embeddings can be List[Optional[np.ndarray]] or List[List[Optional[np.ndarray]]]
            embeddings_list = processed_peek["embeddings"]
            new_embeddings = []
            for item in embeddings_list:
                if isinstance(item, list):  # Handle potential nested lists
                    inner_list = []
                    for emb_arr in item:
                        inner_list.append(emb_arr.tolist() if hasattr(emb_arr, "tolist") else emb_arr)
                    new_embeddings.append(inner_list)
                elif hasattr(item, "tolist"):  # Handle top-level numpy arrays
                    new_embeddings.append(item.tolist())
                else:  # Handle other types or None
                    new_embeddings.append(item)
            processed_peek["embeddings"] = new_embeddings

        # Also process distances if present
        # Check existence and non-None value explicitly before processing
        if "distances" in processed_peek and processed_peek["distances"] is not None:
            distances_list = processed_peek["distances"]
            new_distances = []
            for item in distances_list:
                if isinstance(item, list):
                    inner_list = []
                    for dist_arr in item:
                        inner_list.append(dist_arr.tolist() if hasattr(dist_arr, "tolist") else dist_arr)
                    new_distances.append(inner_list)
                elif hasattr(item, "tolist"):
                    new_distances.append(item.tolist())
                else:
                    new_distances.append(item)
            processed_peek["distances"] = new_distances

        result_json = json.dumps(processed_peek, indent=2)
        # Return content list directly
        return [types.TextContent(type="text", text=result_json)]

    except ValueError as e:  # Catch collection not found from get_collection
        error_str = str(e).lower()
        not_found = False
        if f"collection {collection_name} does not exist." in error_str:
            not_found = True
        if f"collection {collection_name} not found" in error_str:
            not_found = True

        if not_found:
            logger.warning(f"Cannot peek: Collection '{collection_name}' not found.")
            # Raise McpError
            raise McpError(
                ErrorData(code=INVALID_PARAMS, message=f"Tool Error: Collection '{collection_name}' not found.")
            )
        else:
            logger.error(f"Value error peeking collection '{collection_name}': {e}", exc_info=True)
            # Raise McpError
            raise McpError(
                ErrorData(
                    code=INVALID_PARAMS,
                    message=f"Tool Error: Problem accessing collection '{collection_name}'. Details: {e}",
                )
            )
    except ValidationError as e:
        logger.warning(f"Validation error peeking collection '{collection_name}': {e}")
        raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Validation Error: {str(e)}"))
    except Exception as e:
        logger.error(f"Unexpected error peeking collection '{collection_name}': {e}", exc_info=True)
        # Raise McpError
        raise McpError(
            ErrorData(
                code=INTERNAL_ERROR,
                message=f"Tool Error: An unexpected error occurred peeking collection '{collection_name}'. Details: {str(e)}",
            )
        )


def _get_collection_info(collection) -> dict:
    """Helper to get basic info (name, id, metadata) about a collection object."""
    # ADD logger assignment inside the function
    logger = get_logger("tools.collection")
    try:
        return {
            "name": collection.name,
            "id": str(collection.id),
            "metadata": _reconstruct_metadata(collection.metadata),
        }
    except Exception as e:
        logger.error(f"Failed to get info for collection: {e}", exc_info=True)
        return {"error": f"Failed to retrieve collection info: {str(e)}"}


# --- New _impl function for variant ---
async def _create_collection_with_metadata_impl(
    input_data: CreateCollectionWithMetadataInput,
) -> List[types.TextContent]:
    """Core logic to create a collection with specified metadata (provided as JSON string)."""
    logger = get_logger("create_collection_with_metadata")
    collection_name = input_data.collection_name
    # Metadata is now a JSON string
    metadata_str = input_data.metadata

    try:
        # Parse the JSON string into a dictionary
        try:
            metadata_dict = json.loads(metadata_str)
            if not isinstance(metadata_dict, dict):
                raise ValueError("Metadata string must decode to a JSON object (dictionary).")
        except json.JSONDecodeError as e:
            logger.warning(f"Failed to parse metadata JSON string for '{collection_name}': {e}")
            raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Invalid JSON format for metadata field: {str(e)}"))
        except ValueError as e:  # Catch the isinstance check
            logger.warning(f"Metadata did not decode to a dictionary for '{collection_name}': {e}")
            raise McpError(ErrorData(code=INVALID_PARAMS, message=str(e)))

        # Ensure any timestamps are server-side
        metadata_dict = _ensure_server_timestamp(metadata_dict)

        # Validate name (can raise ValidationError)
        validate_collection_name(collection_name)
        logger.debug(f"Validated collection name: {collection_name}")

        # Get the configured embedding function name from server config
        server_config = get_server_config()
        configured_ef_name = server_config.embedding_function_name
        # Instantiate the configured embedding function
        embedding_function = get_embedding_function(configured_ef_name)
        logger.info(f"Using configured embedding function '{configured_ef_name}' for collection '{collection_name}'")

        # Get the client
        chroma_client = get_chroma_client()

        logger.info(
            f"Attempting to create collection '{collection_name}' with provided parsed metadata: {metadata_dict}"
        )

        # Call ChromaDB
        collection = chroma_client.create_collection(
            name=collection_name,
            metadata=metadata_dict,  # Pass the PARSED dictionary
            # Pass the embedding function resolved from server config
            embedding_function=embedding_function,
            get_or_create=False,  # Explicitly create only
        )

        logger.info(f"Successfully created collection '{collection_name}' with ID: {collection.id}")

        # Reconstruct metadata for the response
        reconstructed_meta = _reconstruct_metadata(collection.metadata)

        result_dict = {
            "name": collection.name,
            "id": str(collection.id),  # Ensure ID is string
            "metadata": reconstructed_meta,
            "count": collection.count(),  # Get current count
            "status": "success",
        }
        return [types.TextContent(type="text", text=json.dumps(result_dict))]

    except ValidationError as e:
        # Handle specific validation error for name
        logger.warning(f"Collection name validation failed: {str(e)}")
        raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Validation Error: {str(e)}"))
    except McpError as e:  # Re-raise McpError from JSON parsing
        raise
    except Exception as e:
        # Catch-all for other Chroma/unexpected errors during creation
        logger.error(f"Failed to create collection '{collection_name}': {str(e)}", exc_info=True)
        # Check for duplicate collection error specifically
        if f"Collection {collection_name} already exists." in str(e):
            logger.warning(f"Collection '{collection_name}' already exists.")
            raise McpError(
                ErrorData(code=INVALID_PARAMS, message=f"Tool Error: Collection '{collection_name}' already exists.")
            )

        # Use handle_chroma_error or raise directly
        raise McpError(
            ErrorData(
                code=INTERNAL_ERROR,
                message=f"Tool Error: An unexpected error occurred while creating collection '{collection_name}'. Details: {str(e)}",
            )
        )
