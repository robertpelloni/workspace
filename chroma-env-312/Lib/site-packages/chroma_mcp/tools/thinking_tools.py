"""
Sequential thinking tools for managing thought chains and context in ChromaDB.
"""

import time
import uuid
import json
import logging

from typing import Dict, List, Optional, Any
from dataclasses import dataclass, asdict

from mcp import types
from mcp.shared.exceptions import McpError
from mcp.types import ErrorData, INVALID_PARAMS, INTERNAL_ERROR
from pydantic import BaseModel, Field, field_validator, ConfigDict

# Import InvalidDimensionException
from chromadb.errors import InvalidDimensionException

from ..types import ThoughtMetadata
from ..utils import (
    get_logger,
    get_chroma_client,
    get_embedding_function,
    ValidationError,
    get_server_config,
)

# Constants
THOUGHTS_COLLECTION = "sequential_thoughts_v1"
SESSIONS_COLLECTION = "thinking_sessions"
DEFAULT_SIMILARITY_THRESHOLD = 0.6


@dataclass
class ThoughtMetadata:
    """Metadata structure for thoughts."""

    session_id: str
    thought_number: int
    total_thoughts: int
    timestamp: int
    branch_from_thought: Optional[int] = None
    branch_id: Optional[str] = None
    next_thought_needed: bool = False
    custom_data: Optional[Dict[str, Any]] = None


# Get logger instance for this module
# logger = get_logger("tools.thinking")

# --- Pydantic Input Models for Thinking Tools ---


class SequentialThinkingInput(BaseModel):
    thought: str = Field(..., description="Content of the thought being recorded.")
    thought_number: int = Field(..., gt=0, description="Sequential number of this thought (must be > 0).")
    total_thoughts: int = Field(..., description="Total anticipated number of thoughts in this sequence.")
    session_id: str = Field(default="", description="Unique session ID. If empty, a new session ID is generated.")
    branch_id: str = Field(
        default="", description="Optional identifier for a branch within the session. Empty if none."
    )
    branch_from_thought: int = Field(
        default=0,
        description="If creating a new branch, the parent thought number (> 0) it originates from. 0 if not branching.",
    )
    next_thought_needed: bool = Field(False, description="Flag indicating if a subsequent thought is expected.")

    model_config = ConfigDict(extra="forbid")


class SequentialThinkingWithCustomDataInput(SequentialThinkingInput):
    custom_data: str = Field(
        ..., description='Dictionary for arbitrary metadata as a JSON string (e.g., \'{"key": "value"}\').'
    )

    model_config = ConfigDict(extra="forbid")


class FindSimilarThoughtsInput(BaseModel):
    query: str = Field(..., description="Text to search for similar thoughts.")
    session_id: str = Field(
        default="", description="If provided, limits search to this session. Empty for global search."
    )
    n_results: int = Field(5, ge=1, description="Maximum number of similar thoughts to return (must be >= 1).")
    threshold: float = Field(
        default=-1.0,
        description="Similarity score threshold (0.0 to 1.0). Lower distance is more similar. -1.0 to use default.",
    )
    include_branches: bool = Field(True, description="Whether to include thoughts from branches in the search.")

    model_config = ConfigDict(extra="forbid")


class GetSessionSummaryInput(BaseModel):
    session_id: str = Field(..., description="The unique identifier for the thinking session to summarize.")
    include_branches: bool = Field(True, description="Whether to include thoughts from branches in the summary.")

    model_config = ConfigDict(extra="forbid")


class FindSimilarSessionsInput(BaseModel):
    query: str = Field(..., description="Text to search for similar thinking sessions based on overall content.")
    n_results: int = Field(5, ge=1, description="Maximum number of similar sessions to return (must be >= 1).")
    threshold: float = Field(
        default=-1.0,
        description="Similarity score threshold (0.0 to 1.0). Lower distance is more similar. -1.0 to use default.",
    )

    model_config = ConfigDict(extra="forbid")


# --- End Pydantic Input Models ---

# --- Implementation Functions ---


# Wrapper for the base variant (no custom_data)
async def _sequential_thinking_impl(input_data: SequentialThinkingInput) -> List[types.TextContent]:
    """Records a thought within a thinking session (without custom data).

    Args:
        input_data: A SequentialThinkingInput object containing validated arguments.

    Returns:
        A list containing a single TextContent object.
    """
    # Pass custom_data as None explicitly
    return await _base_sequential_thinking_impl(input_data, custom_data_json=None)


# Wrapper for the variant with custom_data
async def _sequential_thinking_with_custom_data_impl(
    input_data: SequentialThinkingWithCustomDataInput,
) -> List[types.TextContent]:
    """Records a thought within a thinking session (with custom data).

    Args:
        input_data: A SequentialThinkingWithCustomDataInput object containing validated arguments.

    Returns:
        A list containing a single TextContent object.
    """
    # Extract custom_data and pass it to the base implementation
    return await _base_sequential_thinking_impl(input_data, custom_data_json=input_data.custom_data)


# Base implementation (renamed from original _sequential_thinking_impl)
async def _base_sequential_thinking_impl(
    input_data: SequentialThinkingInput, custom_data_json: Optional[str]
) -> List[types.TextContent]:
    """Base implementation for recording a thought.

    Args:
        input_data: A SequentialThinkingInput (or subclass that conforms) object.
        custom_data_json: The custom data as a JSON string (can be None).

    Returns:
        A list containing a single TextContent object.
    """
    # Use root logger for entry debug
    logging.info("--- ENTERING _base_sequential_thinking_impl ---")

    logger = get_logger("tools.thinking")  # Keep module logger for other messages
    try:
        # Access validated data from input model
        thought = input_data.thought
        thought_number = input_data.thought_number
        total_thoughts = input_data.total_thoughts
        session_id = input_data.session_id  # Could be ""
        branch_id = input_data.branch_id  # Could be ""
        branch_from_thought = input_data.branch_from_thought  # Could be 0
        next_thought_needed = input_data.next_thought_needed  # Has default
        # custom_data_json is passed as an argument (remains Optional[str])

        # --- Parse Custom Data JSON --- #
        parsed_custom_data: Optional[Dict[str, Any]] = None
        if custom_data_json:
            try:
                parsed_custom_data = json.loads(custom_data_json)
                if not isinstance(parsed_custom_data, dict):
                    raise ValueError("Custom data string must decode to a JSON object (dictionary).")
            except json.JSONDecodeError as e:
                logger.warning(f"Failed to parse custom_data JSON string: {e}")
                raise McpError(
                    ErrorData(code=INVALID_PARAMS, message=f"Invalid JSON format for custom_data string: {str(e)}")
                )
            except ValueError as e:  # Catch the isinstance check
                logger.warning(f"Custom data did not decode to a dictionary: {e}")
                raise McpError(ErrorData(code=INVALID_PARAMS, message=str(e)))
        # --- End Parsing --- #

        # Use root logger before client calls
        logging.info("--- Getting Chroma client... ---")
        client = get_chroma_client()
        logging.info("--- Chroma client obtained. ---")

        # Get the server's default embedding function
        server_ef_name = get_server_config().embedding_function_name
        default_ef = get_embedding_function(server_ef_name)
        logger.debug(f"Using embedding function '{server_ef_name}' for thinking collections.")

        # Ensure the collection exists before proceeding
        logging.info("--- Getting/Creating collection... ---")
        try:
            collection = client.get_or_create_collection(name=THOUGHTS_COLLECTION, embedding_function=default_ef)
            logging.info(f"--- Collection '{collection.name}' obtained/created. ---")
        except Exception as e:
            logging.error(f"--- FAILED to get/create collection: {e} ---", exc_info=True)  # Root log error
            raise McpError(ErrorData(code=INTERNAL_ERROR, message=f"Could not access thinking collection: {str(e)}"))

        # Validate branch logic

        # Handle default values for session_id and branch_from_thought
        effective_session_id = session_id if session_id else str(uuid.uuid4())
        effective_branch_from_thought = branch_from_thought if branch_from_thought > 0 else None
        effective_branch_id = branch_id if branch_id else None
        # IMPORTANT: Server-side timestamp generation - no reliance on AI model's perception
        timestamp = int(time.time())  # ← Using server-side timestamp
        metadata = ThoughtMetadata(
            session_id=effective_session_id,
            thought_number=thought_number,
            total_thoughts=total_thoughts,
            timestamp=timestamp,  # ← Using server-side timestamp from above
            branch_from_thought=effective_branch_from_thought,  # Use effective value
            branch_id=effective_branch_id,  # Use effective value
            next_thought_needed=next_thought_needed,
            custom_data=parsed_custom_data,
        )

        thought_id = f"thought_{effective_session_id}_{thought_number}"
        if effective_branch_id:  # Check effective value
            thought_id += f"_branch_{effective_branch_id}"

        # FIX: Construct metadata dictionary correctly using asdict for dataclass
        # Convert dataclass instance to dictionary
        base_metadata_dict = asdict(metadata)

        # Manually filter out None values
        filtered_metadata_dict = {k: v for k, v in base_metadata_dict.items() if v is not None}

        # Extract custom_data if it exists (and remove it from the main dict)
        # Use .pop on the filtered dict to get custom_data and remove it in one step
        custom_data_to_flatten = filtered_metadata_dict.pop("custom_data", None)

        # If custom_data was present and is a dict, flatten it with prefix
        if isinstance(custom_data_to_flatten, dict):
            for ck, cv in custom_data_to_flatten.items():
                filtered_metadata_dict[f"custom:{ck}"] = cv

        # The filtered_metadata_dict now contains the correct structure for Chroma
        metadata_dict_for_chroma = filtered_metadata_dict

        try:
            # Use root logger around add
            logging.info(f"--- Attempting collection.add for ID: {thought_id} ---")
            collection.add(documents=[thought], metadatas=[metadata_dict_for_chroma], ids=[thought_id])
            logging.info(f"--- Successfully added thought ID: {thought_id} ---")
        except (ValueError, InvalidDimensionException) as e:
            # Use root logger for error
            logging.error(f"--- FAILED collection.add: {e} ---", exc_info=True)
            raise McpError(
                ErrorData(
                    code=INTERNAL_ERROR,
                    message=f"ChromaDB Error adding thought: {str(e)}",
                )
            )

        # --- KEEPING Previous Thoughts Logic ---
        previous_thoughts = []
        if thought_number > 1:
            # Fetch ALL thoughts for the session first
            where_clause_get = {"session_id": effective_session_id}

            try:
                # Simpler get call, fetch all thoughts for the session
                results = collection.get(
                    where=where_clause_get,
                    include=["documents", "metadatas"],
                )

                thought_data = []
                if results and results.get("ids"):
                    for i in range(len(results["ids"])):
                        raw_meta = results["metadatas"][i] or {}
                        thought_num = raw_meta.get("thought_number")

                        # Filter for previous thoughts ONLY
                        if thought_num is None or thought_num >= thought_number:
                            continue  # Skip current/future thoughts

                        # --- Python-based branch filtering ---
                        thought_branch_id = raw_meta.get("branch_id")

                        if effective_branch_id:
                            # If we are IN a branch, include thoughts from this branch
                            # OR from the main trunk before the branch point
                            thought_branch_from = raw_meta.get("branch_from_thought")
                            is_in_correct_branch = thought_branch_id == effective_branch_id
                            is_on_main_trunk_before_branch = thought_branch_id is None and (
                                effective_branch_from_thought is None or thought_num < effective_branch_from_thought
                            )
                            if not (is_in_correct_branch or is_on_main_trunk_before_branch):
                                continue  # Skip thoughts not relevant to this branch history
                        else:
                            # If we are NOT in a branch, skip any thought that has a branch_id
                            if thought_branch_id is not None:
                                continue
                        # --- End Python-based branch filtering ---

                        # Reconstruct custom data (if any)
                        reconstructed_custom = {
                            k[len("custom:") :]: v for k, v in raw_meta.items() if k.startswith("custom:")
                        }
                        base_meta = {k: v for k, v in raw_meta.items() if not k.startswith("custom:")}
                        if reconstructed_custom:
                            base_meta["custom_data"] = reconstructed_custom

                        thought_data.append(
                            {
                                "id": results["ids"][i],
                                "content": results["documents"][i],
                                "metadata": base_meta,
                                "thought_number_sort_key": thought_num,  # Use the already retrieved thought_number
                            }
                        )

                # Sort based on thought_number
                sorted_thoughts = sorted(thought_data, key=lambda x: x["thought_number_sort_key"])

                # Final list without the sort key
                previous_thoughts = [
                    {k: v for k, v in thought.items() if k != "thought_number_sort_key"} for thought in sorted_thoughts
                ]

            except Exception as e:
                logger.warning(
                    f"Could not retrieve previous thoughts for session {effective_session_id}: {e}",
                    exc_info=True,
                )
        # --- END Previous Thoughts Logic ---

        # REMOVED: Call to non-existent _update_session_summary
        # if thought_number == total_thoughts and not next_thought_needed:
        #     await _update_session_summary(effective_session_id, collection, branch_id) # This function doesn't exist

        # Return List[TextContent] on success
        result_data = {
            "session_id": effective_session_id,
            "thought_id": thought_id,
            "previous_thoughts_count": len(previous_thoughts),
        }
        result_json = json.dumps(result_data, indent=2)

        logging.info("--- EXITING _base_sequential_thinking_impl NORMALLY ---")  # Root log exit
        return [types.TextContent(type="text", text=result_json)]

    except ValidationError as e:
        logger.error(f"Validation Error in sequential thinking: {e}", exc_info=True)
        # Raise McpError instead of returning CallToolResult
        raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Invalid parameters: {str(e)}"))
    except McpError as e:  # Re-raise already caught McpError (from custom_data parsing)
        raise e
    except Exception as e:  # Catch other unexpected errors
        # Root log unexpected exceptions
        logging.error(
            f"--- EXITING _base_sequential_thinking_impl VIA EXCEPTION: {type(e).__name__} ---", exc_info=True
        )
        logger.error(f"Unexpected error during sequential thinking: {e}", exc_info=True)
        # Raise McpError instead of returning CallToolResult
        raise McpError(ErrorData(code=INTERNAL_ERROR, message=f"An unexpected error occurred: {str(e)}"))


async def _find_similar_thoughts_impl(input_data: FindSimilarThoughtsInput) -> List[types.TextContent]:
    """Performs a semantic search for similar thoughts.

    Args:
        input_data: A FindSimilarThoughtsInput object containing validated arguments.

    Returns:
        A list containing a single TextContent object with a JSON string representing
        the query results (similar to ChromaDB query results, including lists for ids,
        documents/thoughts, metadatas, distances).
        On error (e.g., invalid parameters, collection not found, unexpected issue),
        raises McpError.
    """

    logger = get_logger("tools.thinking")
    try:
        # Access validated data
        query = input_data.query
        session_id = input_data.session_id
        n_results = input_data.n_results  # Has default
        threshold = input_data.threshold
        include_branches = input_data.include_branches  # Has default

        # Use default threshold if -1.0 is passed
        effective_threshold = DEFAULT_SIMILARITY_THRESHOLD if threshold == -1.0 else threshold
        # Validate threshold range (0.0 to 1.0)
        if not (0.0 <= effective_threshold <= 1.0):
            raise McpError(
                ErrorData(
                    code=INVALID_PARAMS, message=f"Threshold must be between 0.0 and 1.0, got {effective_threshold}"
                )
            )

        client = get_chroma_client()

        # Get the server's default embedding function
        server_ef_name = get_server_config().embedding_function_name
        default_ef = get_embedding_function(server_ef_name)
        logger.debug(f"Using embedding function '{server_ef_name}' for {THOUGHTS_COLLECTION}.")

        # Get collection, handle not found specifically
        try:
            collection = client.get_collection(name=THOUGHTS_COLLECTION, embedding_function=default_ef)
        except ValueError as e:
            if f"Collection {THOUGHTS_COLLECTION} does not exist." in str(e):
                logger.warning(f"Cannot find similar thoughts: Collection '{THOUGHTS_COLLECTION}' not found.")
                # Return success with empty results, indicating collection doesn't exist
                return [  # Return list
                    types.TextContent(
                        type="text",
                        text=json.dumps(
                            {
                                "similar_thoughts": [],
                                "total_found": 0,
                                "threshold_used": effective_threshold,
                                "message": f"Collection '{THOUGHTS_COLLECTION}' not found.",
                            },
                            indent=2,
                        ),
                    )
                ]
            else:
                raise e  # Re-raise other ValueErrors
        except Exception as e:  # Catch other potential errors during get_collection
            logger.error(f"Error getting collection '{THOUGHTS_COLLECTION}' for query: {e}", exc_info=True)
            # Raise McpError instead of returning CallToolResult
            raise McpError(
                ErrorData(
                    code=INTERNAL_ERROR,
                    message=f"ChromaDB Error accessing collection '{THOUGHTS_COLLECTION}': {str(e)}",
                )
            )

        # Prepare where clause if session_id is provided
        where_clause = None
        if session_id:
            where_clause = {"session_id": session_id}
            # TODO: Add branch filtering logic if needed based on include_branches

        # Perform query, handle errors
        try:
            results = collection.query(
                query_texts=[query],
                n_results=n_results,
                where=where_clause,
                include=["documents", "metadatas", "distances"],
            )
        except ValueError as e:  # Catch query-specific errors
            logger.error(f"Error querying thoughts collection '{THOUGHTS_COLLECTION}': {e}", exc_info=True)
            # Raise McpError instead of returning CallToolResult
            raise McpError(
                ErrorData(
                    code=INTERNAL_ERROR,  # Use INTERNAL_ERROR for query issues
                    message=f"ChromaDB Query Error: {str(e)}",
                )
            )

        # Process results and filter by threshold
        similar_thoughts = []
        if results and results.get("ids") and results["ids"][0]:
            for i in range(len(results["ids"][0])):
                distance = results["distances"][0][i]
                similarity = 1.0 - distance  # Ensure float calculation

                if similarity >= effective_threshold:
                    raw_meta = results["metadatas"][0][i] or {}
                    # Reconstruct custom data
                    reconstructed_custom = {
                        k[len("custom:") :]: v for k, v in raw_meta.items() if k.startswith("custom:")
                    }
                    base_meta = {k: v for k, v in raw_meta.items() if not k.startswith("custom:")}
                    if reconstructed_custom:
                        base_meta["custom_data"] = reconstructed_custom

                    thought = {
                        "id": results["ids"][0][i],  # Include ID
                        "content": results["documents"][0][i],
                        "metadata": base_meta,
                        "similarity": similarity,
                    }
                    similar_thoughts.append(thought)

        # Success result
        result_data = {
            "similar_thoughts": similar_thoughts,
            "total_found": len(similar_thoughts),
            "threshold_used": effective_threshold,
        }
        result_json = json.dumps(result_data, indent=2)
        return [types.TextContent(type="text", text=result_json)]

    except ValueError as e:  # Catch ValueErrors re-raised from get_collection
        logger.error(f"Value error accessing collection '{THOUGHTS_COLLECTION}' for query: {e}", exc_info=False)
        # Raise McpError instead of returning CallToolResult
        raise McpError(
            ErrorData(
                code=INTERNAL_ERROR,  # Treat re-raised access error as internal
                message=f"ChromaDB Value Error accessing collection: {str(e)}",
            )
        )
    except Exception as e:
        logger.error(f"Unexpected error finding similar thoughts: {e}", exc_info=True)
        # Raise McpError instead of returning CallToolResult
        raise McpError(
            ErrorData(
                code=INTERNAL_ERROR,
                message=f"Tool Error: An unexpected error occurred while finding similar thoughts. Details: {str(e)}",
            )
        )


async def _get_session_summary_impl(input_data: GetSessionSummaryInput) -> List[types.TextContent]:
    """Fetches all thoughts belonging to a specific session.

    Args:
        input_data: A GetSessionSummaryInput object containing validated arguments.

    Returns:
        A list containing a single TextContent object with a JSON string containing
        a list of thoughts (documents/metadata), ordered sequentially by thought_number
        (and potentially by branch structure if included).
        On error (e.g., session not found, database error, unexpected issue),
        raises McpError.
    """

    logger = get_logger("tools.thinking")
    try:
        # Access validated data
        session_id = input_data.session_id
        include_branches = input_data.include_branches  # Has default

        client = get_chroma_client()

        # Get the server's default embedding function
        server_ef_name = get_server_config().embedding_function_name
        default_ef = get_embedding_function(server_ef_name)
        logger.debug(f"Using embedding function '{server_ef_name}' for {THOUGHTS_COLLECTION}.")

        # Ensure the collection exists before proceeding
        logger.debug(f"Ensuring collection '{THOUGHTS_COLLECTION}' exists for summary...")
        try:
            collection = client.get_or_create_collection(name=THOUGHTS_COLLECTION, embedding_function=default_ef)
            logger.debug(f"Collection '{THOUGHTS_COLLECTION}' obtained or created for summary.")
        except Exception as e:
            logger.error(f"Failed to get or create collection '{THOUGHTS_COLLECTION}' for summary: {e}", exc_info=True)
            raise McpError(ErrorData(code=INTERNAL_ERROR, message=f"Could not access thinking collection: {str(e)}"))

        # Get thoughts, handle errors
        try:
            # Fetch ALL documents first
            logger.debug(f"Fetching all documents from {THOUGHTS_COLLECTION}...")
            results = collection.get(include=["documents", "metadatas"])  # Fetch all
            logger.debug(f"Fetched {len(results.get('ids', []))} documents in total.")
        except ValueError as e:  # Catch errors from get (e.g., bad filter)
            logger.error(f"Error getting thoughts for session '{session_id}': {e}", exc_info=True)
            # Raise McpError instead of returning CallToolResult
            raise McpError(
                ErrorData(code=INTERNAL_ERROR, message=f"ChromaDB Get Error: {str(e)}")  # Treat get errors as internal
            )

        # Process and sort results
        session_thoughts = []
        if results and results.get("ids"):
            thought_data = []
            for i in range(len(results["ids"])):
                raw_meta = results["metadatas"][i] or {}
                # --- Filter by session_id in Python ---
                if raw_meta.get("session_id") != session_id:
                    continue
                # --- Filter by branch_id if needed ---
                if not include_branches and raw_meta.get("branch_id") is not None:
                    continue

                # Reconstruct custom data (Corrected logic)
                reconstructed_custom = {k[len("custom:") :]: v for k, v in raw_meta.items() if k.startswith("custom:")}
                base_meta = {k: v for k, v in raw_meta.items() if not k.startswith("custom:")}
                if reconstructed_custom:
                    base_meta["custom_data"] = reconstructed_custom

                thought_data.append(
                    {
                        "id": results["ids"][i],  # Include ID
                        "content": results["documents"][i],
                        "metadata": base_meta,  # Use the fully reconstructed base_meta
                        "thought_number_sort_key": base_meta.get("thought_number", 999999),  # Get from base_meta
                    }
                )

            # Sort based on thought_number
            sorted_thoughts = sorted(thought_data, key=lambda x: x["thought_number_sort_key"])

            # Final list without the sort key
            session_thoughts = [
                {k: v for k, v in thought.items() if k != "thought_number_sort_key"} for thought in sorted_thoughts
            ]

        # Success result - RESTORED
        result_data = {
            "session_id": session_id,
            "session_thoughts": session_thoughts,
            "total_thoughts_in_session": len(session_thoughts),
        }
        result_json = json.dumps(result_data, indent=2)
        return [types.TextContent(type="text", text=result_json)]

    except ValueError as e:  # Catch ValueErrors re-raised from get_collection
        logger.error(
            f"Value error accessing collection '{THOUGHTS_COLLECTION}' for session summary: {e}", exc_info=False
        )
        # Raise McpError instead of returning CallToolResult
        raise McpError(
            ErrorData(
                code=INTERNAL_ERROR,  # Treat re-raised access error as internal
                message=f"ChromaDB Value Error accessing collection: {str(e)}",
            )
        )
    except Exception as e:
        logger.error(f"Unexpected error getting session summary for '{session_id}': {e}", exc_info=True)
        # Raise McpError instead of returning CallToolResult
        raise McpError(
            ErrorData(
                code=INTERNAL_ERROR,
                message=f"Tool Error: An unexpected error occurred while getting session summary for '{session_id}'. Details: {str(e)}",
            )
        )


async def _find_similar_sessions_impl(input_data: FindSimilarSessionsInput) -> List[types.TextContent]:
    """Performs a semantic search for sessions similar to the query.

    (Note: This functionality might require pre-calculating session embeddings
     or performing aggregation queries, depending on the implementation.)

    Args:
        input_data: A FindSimilarSessionsInput object containing validated arguments.

    Returns:
        A list containing a single TextContent object with a JSON string listing
        similar session IDs and potentially their similarity scores.
        On error (e.g., supporting collection/index not found, invalid query,
        unexpected issue), raises McpError.
    """

    logger = get_logger("tools.thinking")
    try:
        # Access validated data
        query = input_data.query
        n_results = input_data.n_results  # Has default
        threshold = input_data.threshold

        # Use default threshold if -1.0 is passed
        effective_threshold = DEFAULT_SIMILARITY_THRESHOLD if threshold == -1.0 else threshold
        # Validate threshold range (0.0 to 1.0)
        if not (0.0 <= effective_threshold <= 1.0):
            raise McpError(
                ErrorData(
                    code=INVALID_PARAMS, message=f"Threshold must be between 0.0 and 1.0, got {effective_threshold}"
                )
            )

        client = get_chroma_client()

        # Get the server's default embedding function
        server_ef_name = get_server_config().embedding_function_name
        default_ef = get_embedding_function(server_ef_name)
        logger.debug(f"Using embedding function '{server_ef_name}' for thinking collections.")

        # --- Step 1: Get all unique session IDs from the thoughts collection ---
        thoughts_collection = None
        all_session_ids = set()
        try:
            thoughts_collection = client.get_collection(name=THOUGHTS_COLLECTION, embedding_function=default_ef)
            # Efficiently get all unique session_ids from metadata
            # This might be slow for very large collections, consider optimization if needed
            all_metadata = thoughts_collection.get(include=["metadatas"])
            if all_metadata and all_metadata.get("metadatas"):
                for meta in all_metadata["metadatas"]:
                    if meta and "session_id" in meta:
                        all_session_ids.add(meta["session_id"])
        except ValueError as e:
            if f"Collection {THOUGHTS_COLLECTION} does not exist." in str(e):
                logger.warning(f"Cannot find similar sessions: Collection '{THOUGHTS_COLLECTION}' not found.")
                # Return empty result if thoughts collection is missing
                return [  # Return list
                    types.TextContent(
                        type="text",
                        text=json.dumps(
                            {"similar_sessions": [], "total_found": 0, "threshold_used": effective_threshold}, indent=2
                        ),
                    )
                ]
            else:
                raise e  # Re-raise other ValueErrors
        except Exception as e:
            logger.error(f"Error accessing thoughts collection '{THOUGHTS_COLLECTION}': {e}", exc_info=True)
            # Raise McpError instead of returning CallToolResult
            raise McpError(
                ErrorData(code=INTERNAL_ERROR, message=f"ChromaDB Error accessing thoughts collection: {str(e)}")
            )

        if not all_session_ids:
            logger.info("No sessions found in the thoughts collection.")
            return [  # Return list
                types.TextContent(
                    type="text",
                    text=json.dumps(
                        {"similar_sessions": [], "total_found": 0, "threshold_used": effective_threshold}, indent=2
                    ),
                )
            ]

        # --- Step 2: Create/Get Sessions Collection and Embed Session Summaries ---
        sessions_collection = None
        try:
            # Try getting the sessions collection
            sessions_collection = client.get_or_create_collection(
                name=SESSIONS_COLLECTION, embedding_function=default_ef
            )
        except ValueError as e:
            # Handle case where SESSIONS_COLLECTION specifically does not exist
            if f"Collection {SESSIONS_COLLECTION} does not exist." in str(e):
                logger.warning(f"Cannot find similar sessions: Required collection '{SESSIONS_COLLECTION}' not found.")
                # Raise McpError instead of returning CallToolResult
                raise McpError(
                    ErrorData(
                        code=INTERNAL_ERROR,  # Use INTERNAL_ERROR as it's a required backend component
                        message=f"Tool Error: Collection '{SESSIONS_COLLECTION}' not found",
                    )
                )
            else:
                # Re-raise other ValueErrors to be caught by the general exception handler below
                raise e
        except Exception as e:
            # Catch other errors during get_collection (non-ValueError)
            logger.error(f"Error accessing sessions collection '{SESSIONS_COLLECTION}': {e}", exc_info=True)
            # Raise McpError instead of returning CallToolResult
            raise McpError(
                ErrorData(code=INTERNAL_ERROR, message=f"ChromaDB Error accessing sessions collection: {str(e)}")
            )

        # If collection exists, proceed with embedding and adding summaries
        try:
            # Embed summaries for sessions not already in the sessions collection
            existing_session_ids = set(sessions_collection.get().get("ids", []))
            sessions_to_embed = []
            ids_to_embed = []

            for session_id in all_session_ids:
                if session_id not in existing_session_ids:
                    try:
                        # Get session summary (returns List[TextContent] on success)
                        summary_result_list = await _get_session_summary_impl(
                            GetSessionSummaryInput(session_id=session_id)
                        )
                        # Safely parse the JSON content from the first TextContent item
                        summary_data = json.loads(summary_result_list[0].text)
                        summary_text = " ".join(
                            [t.get("content", "") for t in summary_data.get("session_thoughts", [])]
                        )
                        if summary_text:  # Only embed if there's content
                            logger.debug(
                                f"Generated summary for session '{session_id}': '{summary_text[:100]}...'"
                            )  # Log summary
                            sessions_to_embed.append(summary_text)
                            ids_to_embed.append(session_id)
                    except McpError as summary_error:
                        logger.warning(
                            f"Failed to get summary for session '{session_id}' to embed: {summary_error.message}"
                        )
                    except (json.JSONDecodeError, IndexError, AttributeError) as parse_error:
                        logger.warning(f"Could not parse summary result for session '{session_id}': {parse_error}")

            if sessions_to_embed:
                logger.info(f"Embedding summaries for {len(sessions_to_embed)} new/updated sessions.")
                logger.debug(f"IDs to embed: {ids_to_embed}")  # Log IDs before add
                logger.debug(f"Summaries to embed: {sessions_to_embed}")  # Log summaries before add
                sessions_collection.add(documents=sessions_to_embed, ids=ids_to_embed)
                logger.info(f"Finished adding/embedding summaries to '{SESSIONS_COLLECTION}'.")  # Log after add

        except Exception as e:
            # Catch errors during the embedding/adding process
            logger.error(f"Error embedding/adding to sessions collection '{SESSIONS_COLLECTION}': {e}", exc_info=True)
            # Raise McpError instead of returning CallToolResult
            raise McpError(ErrorData(code=INTERNAL_ERROR, message=f"ChromaDB Error updating sessions: {str(e)}"))

        # --- Step 3: Query the Sessions Collection ---
        similar_sessions = []
        if sessions_collection:  # Ensure collection was accessed successfully
            try:
                query_results = sessions_collection.query(
                    query_texts=[query],
                    n_results=n_results,
                    include=["metadatas", "distances"],  # Only need distance and ID (implicit)
                )

                if query_results and query_results.get("ids") and query_results["ids"][0]:
                    for i in range(len(query_results["ids"][0])):
                        session_id = query_results["ids"][0][i]
                        distance = query_results["distances"][0][i]
                        similarity = 1.0 - distance

                        if similarity >= effective_threshold:
                            try:
                                # Fetch the full summary details again for the result
                                summary_result_list = await _get_session_summary_impl(
                                    GetSessionSummaryInput(session_id=session_id)
                                )
                                # Safely parse the JSON content
                                summary_data = json.loads(summary_result_list[0].text)
                                summary_data["similarity_score"] = similarity  # Add score
                                similar_sessions.append(summary_data)
                            except McpError as summary_error:
                                logger.warning(
                                    f"Failed to get final summary for session '{session_id}': {summary_error.message}"
                                )
                            except (json.JSONDecodeError, IndexError, AttributeError) as parse_error:
                                logger.warning(
                                    f"Could not parse final summary result for session '{session_id}': {parse_error}"
                                )
            except ValueError as e:
                logger.error(f"Error querying sessions collection '{SESSIONS_COLLECTION}': {e}", exc_info=True)
                # Raise McpError instead of returning CallToolResult
                raise McpError(ErrorData(code=INTERNAL_ERROR, message=f"ChromaDB Query Error on sessions: {str(e)}"))

        # Success result
        result_data = {
            "similar_sessions": similar_sessions,
            "total_found": len(similar_sessions),
            "threshold_used": effective_threshold,
        }
        result_json = json.dumps(result_data, indent=2)
        return [types.TextContent(type="text", text=result_json)]

    except ValueError as e:  # Catch ValueErrors re-raised from get_collection (thoughts)
        logger.error(f"Value error accessing thoughts collection '{THOUGHTS_COLLECTION}': {e}", exc_info=False)
        # Raise McpError instead of returning CallToolResult
        raise McpError(
            ErrorData(
                code=INTERNAL_ERROR,  # Treat re-raised access error as internal
                message=f"ChromaDB Value Error accessing thoughts collection: {str(e)}",
            )
        )
    except Exception as e:
        logger.error(f"Unexpected error finding similar sessions: {e}", exc_info=True)
        # Raise McpError instead of returning CallToolResult
        raise McpError(
            ErrorData(
                code=INTERNAL_ERROR,
                message=f"Tool Error: An unexpected error occurred while finding similar sessions. Details: {str(e)}",
            )
        )


# Ensure mcp instance is imported/available for decorators
