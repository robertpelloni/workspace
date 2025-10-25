"""
Implementation of the auto_log_chat rule functionality.

This module provides the implementation for the auto_log_chat rule, which
automatically captures rich context from AI interactions and stores them
in the chat_history_v1 collection.
"""

import json
import logging
from datetime import datetime
from typing import Dict, List, Any, Optional
import uuid

from .context import (
    extract_code_snippets,
    generate_diff_summary,
    track_tool_sequence,
    calculate_confidence_score,
    determine_modification_type,
    manage_bidirectional_links,
)

# Set up logging
logger = logging.getLogger(__name__)


def process_chat_for_logging(
    prompt_summary: str,
    response_summary: str,
    raw_prompt: str,
    raw_response: str,
    tool_usage: List[Dict[str, Any]],
    file_changes: List[Dict[str, Any]],
    involved_entities: str,
    session_id: str = None,
) -> Dict[str, Any]:
    """
    Process chat for logging with enhanced context capture.

    Args:
        prompt_summary: Summary of the user's prompt
        response_summary: Summary of the AI's response
        raw_prompt: The raw user prompt text
        raw_response: The raw AI response text
        tool_usage: List of tools used during the interaction
        file_changes: List of files modified with before/after content
        involved_entities: Comma-separated string of entities involved
        session_id: Optional session ID (UUID string)

    Returns:
        Dictionary containing document and metadata for ChromaDB logging
    """
    # Generate a session ID if not provided
    if not session_id:
        session_id = str(uuid.uuid4())

    # Extract tool sequence
    tool_names = []
    for i, tool in enumerate(tool_usage):
        if "name" in tool:
            tool_names.append(tool["name"])
        elif "tool" in tool:  # Handle the alternative format for backward compatibility
            tool_names.append(tool["tool"])
            # Log a warning to encourage using the standard format
            logger.warning(
                f"Tool usage item at index {i} uses deprecated 'tool' key instead of 'name'. "
                f"Please update to use 'name' and 'args' keys: {tool}"
            )
        else:
            # Log warning about missing keys
            logger.warning(
                f"Tool usage item at index {i} is missing required 'name' or 'tool' key. " f"Skipping this tool: {tool}"
            )
            continue

    tool_sequence = track_tool_sequence(tool_names)

    # Process file changes to extract context and diffs
    code_context = ""
    diff_summary_list = []

    for change in file_changes:
        file_path = change.get("file_path", "unknown_file")
        before_content = change.get("before_content", "")
        after_content = change.get("after_content", "")

        # Extract code snippets for context
        snippet = extract_code_snippets(before_content, after_content)
        if snippet:
            code_context += f"\nFile: {file_path}\n{snippet}\n"

        # Generate human-readable diff summary
        diff = generate_diff_summary(before_content, after_content, file_path)
        if diff:
            diff_summary_list.append(diff)

    diff_summary = "\n".join(diff_summary_list) if diff_summary_list else ""

    # Determine modification type
    mod_type = determine_modification_type(file_changes, prompt_summary, response_summary)

    # Calculate confidence score
    confidence = calculate_confidence_score(tool_sequence, file_changes, len(raw_response))

    # Create metadata
    metadata = {
        "session_id": session_id,
        "timestamp": datetime.utcnow().isoformat(),
        "prompt_summary": prompt_summary,
        "response_summary": response_summary,
        "involved_entities": involved_entities,
        "modification_type": mod_type.value if hasattr(mod_type, "value") else str(mod_type),
        "confidence_score": confidence,
        "status": "captured",
    }

    # Add enhanced context fields if available
    if code_context:
        metadata["code_context"] = code_context

    if diff_summary:
        metadata["diff_summary"] = diff_summary

    if tool_sequence:
        metadata["tool_sequence"] = tool_sequence

    # Create the document content
    if diff_summary:
        document = f"Prompt: {prompt_summary}\nResponse: {response_summary}\nCode Changes: {diff_summary}"
    else:
        document = f"Prompt: {prompt_summary}\nResponse: {response_summary}"

    return {
        "document": document,
        "metadata": metadata,
    }


def log_chat_to_chroma(
    chroma_client,
    prompt_summary: str,
    response_summary: str,
    raw_prompt: str,
    raw_response: str,
    tool_usage: List[Dict[str, Any]],
    file_changes: List[Dict[str, Any]],
    involved_entities: str,
    session_id: str = None,
) -> str:
    """
    Log chat to ChromaDB with enhanced context capture.

    Args:
        chroma_client: ChromaDB client instance
        prompt_summary: Summary of the user's prompt
        response_summary: Summary of the AI's response
        raw_prompt: The raw user prompt text
        raw_response: The raw AI response text
        tool_usage: List of tools used during the interaction
        file_changes: List of files modified with before/after content
        involved_entities: Comma-separated string of entities involved
        session_id: Optional session ID (UUID string)

    Returns:
        ID of the added document
    """
    try:
        # Process the chat for logging
        log_data = process_chat_for_logging(
            prompt_summary=prompt_summary,
            response_summary=response_summary,
            raw_prompt=raw_prompt,
            raw_response=raw_response,
            tool_usage=tool_usage,
            file_changes=file_changes,
            involved_entities=involved_entities,
            session_id=session_id,
        )

        # Get or create the chat_history_v1 collection
        collection_name = "chat_history_v1"
        try:
            collection = chroma_client.get_collection(name=collection_name)
        except ValueError:
            # Collection doesn't exist, create it
            logger.info(f"Collection {collection_name} not found. Creating it.")
            collection = chroma_client.create_collection(name=collection_name)

        # Generate a unique ID for the document
        chat_id = str(uuid.uuid4())

        # Use the collection.add method with properly formatted lists
        collection.add(documents=[log_data["document"]], ids=[chat_id], metadatas=[log_data["metadata"]])

        logger.info(f"Successfully added chat log to collection {collection_name} with ID: {chat_id}")

        # Process bidirectional links if we modified files
        if file_changes:
            related_chunks = manage_bidirectional_links(
                chat_id=chat_id, file_changes=file_changes, chroma_client=chroma_client
            )

            # If we got related chunks, update the chat entry with this information
            if related_chunks:
                # Format related code chunks for metadata
                related_code_chunks = []
                for file_path, chunk_ids in related_chunks.items():
                    related_code_chunks.extend(chunk_ids)

                if related_code_chunks:
                    # Update the chat history entry with the related chunk IDs
                    # Get existing metadata
                    chat_data = collection.get(ids=[chat_id])
                    if chat_data and chat_data.get("metadatas") and len(chat_data["metadatas"]) > 0:
                        metadata = chat_data["metadatas"][0]

                        # Add related code chunks
                        metadata["related_code_chunks"] = ",".join(related_code_chunks)

                        # Update metadata
                        collection.update(ids=[chat_id], metadatas=[metadata])
                        logger.debug(f"Updated chat {chat_id} with related code chunks: {related_code_chunks}")

        return chat_id
    except Exception as e:
        logger.error(f"Failed to log chat to ChromaDB: {e}")
        raise
