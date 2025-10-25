"""
Bridge module to connect MCP tool calls with chroma_mcp_client implementation.

This module provides functions that receive calls from MCP tools and forwards
them to the appropriate chroma_mcp_client implementation.
"""

import json
import logging
from typing import Dict, Any, List, Optional
import os
from pydantic import BaseModel, Field

# Import server-side types for response/content handling
from mcp.types import TextContent

# Get our specific logger
logger = logging.getLogger(__name__)


# Define ToolUsageItem model to enforce the required structure
class ToolUsageItem(BaseModel):
    """Model for a single tool usage item with required structure."""

    name: str = Field(description="The name of the tool used.")
    args: Dict[str, Any] = Field(description="The arguments passed to the tool.", default_factory=dict)


# Define Pydantic input model for the tool
class LogChatInput(BaseModel):
    """Input model for logging chat with enhanced context."""

    prompt_summary: str = Field(description="Summary of the user's prompt/question.")
    response_summary: str = Field(description="Summary of the AI's response/solution.")
    raw_prompt: str = Field(description="Full text of the user's prompt.")
    raw_response: str = Field(description="Full text of the AI's response.")
    tool_usage: List[ToolUsageItem] = Field(
        description="List of tools used during the interaction. Each tool must have a 'name' and optional 'args'.",
        default_factory=list,
    )
    file_changes: List[Dict[str, Any]] = Field(
        description="List of files modified with before/after content.", default_factory=list
    )
    involved_entities: str = Field(
        description="Comma-separated string of entities involved in the interaction.", default=""
    )
    session_id: str = Field(description="Session ID for the interaction. Generated if not provided.", default="")
    collection_name: str = Field(description="Name of the ChromaDB collection to log to.", default="chat_history_v1")


# Implementation function compatible with MCP server call_tool format
async def _log_chat_impl(input_model: LogChatInput) -> List[TextContent]:
    """Implementation function for logging chat with enhanced context."""
    try:
        # Call the client implementation
        chat_id = _do_log_chat(input_model)

        # Create a successful response
        result = {"success": True, "chat_id": chat_id}

        # Return as TextContent list as expected by MCP server
        return [TextContent(type="text", text=json.dumps(result))]
    except Exception as e:
        logger.error(f"Error in _log_chat_impl: {e}", exc_info=True)
        # Return error response
        error_result = {"success": False, "error": str(e)}
        return [TextContent(type="text", text=json.dumps(error_result))]


# Helper function to actually perform the logging
def _do_log_chat(input_model: LogChatInput) -> str:
    """
    Actual implementation to log chat with enhanced context.

    Args:
        input_model: LogChatInput model with all required parameters

    Returns:
        ID of the added document
    """
    # Dynamically import at runtime to avoid circular imports
    from chroma_mcp_client.connection import get_client_and_ef
    from chroma_mcp_client.auto_log_chat_impl import log_chat_to_chroma

    # Get client and embedding function
    client, _ = get_client_and_ef()

    # Extract parameters from the input model
    prompt_summary = input_model.prompt_summary
    response_summary = input_model.response_summary
    raw_prompt = input_model.raw_prompt
    raw_response = input_model.raw_response
    tool_usage = input_model.tool_usage
    file_changes = input_model.file_changes
    involved_entities = input_model.involved_entities
    session_id = input_model.session_id or None  # Convert empty string to None

    # Add additional validation with helpful error messages
    # (These are now mostly redundant due to the Pydantic model but serve as a defensive layer)
    if tool_usage:
        for i, tool in enumerate(tool_usage):
            if not hasattr(tool, "name") or not tool.name:
                raise ValueError(f"Tool usage item at index {i} is missing required 'name' field")

            # Convert Pydantic model to dict for compatibility with the implementation
            if hasattr(tool, "model_dump"):  # Pydantic v2
                tool_usage[i] = tool.model_dump()
            elif hasattr(tool, "dict"):  # Pydantic v1
                tool_usage[i] = tool.dict()

    # Call the client implementation
    chat_id = log_chat_to_chroma(
        chroma_client=client,
        prompt_summary=prompt_summary,
        response_summary=response_summary,
        raw_prompt=raw_prompt,
        raw_response=raw_response,
        tool_usage=tool_usage,
        file_changes=file_changes,
        involved_entities=involved_entities,
        session_id=session_id,
    )

    logger.info(f"Successfully logged chat to ChromaDB with ID: {chat_id}")
    return chat_id


# Main entry point for MCP call_tool
def mcp_log_chat(input_model: LogChatInput) -> str:
    """
    Entry point for MCP tools to log chat with enhanced context.

    Args:
        input_model: LogChatInput model with all required parameters

    Returns:
        ID of the added document
    """
    try:
        return _do_log_chat(input_model)
    except Exception as e:
        logger.error(f"Failed to log chat to ChromaDB via bridge: {e}", exc_info=True)
        raise
