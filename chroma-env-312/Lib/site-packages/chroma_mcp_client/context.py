"""
Context Capture Module for Enhanced Chat Logging

This module provides functionality for extracting rich contextual information from
code changes, tool usage patterns, and chat interactions. It supports the enhanced
context capture features of the auto_log_chat rule and other components.

Key features:
- Code snippet extraction from before/after edits
- Diff generation and summarization
- Tool sequence tracking and pattern recognition
- Confidence score calculation
- Bidirectional link management
"""

import os
import re
import json
import logging
import difflib
from typing import List, Dict, Any, Optional, Tuple, Union
from enum import Enum
from datetime import datetime
import uuid

# Set up logging
logger = logging.getLogger(__name__)


class ModificationType(Enum):
    """Enumeration of standardized modification types for chat interactions."""

    REFACTOR = "refactor"
    BUGFIX = "bugfix"
    FEATURE = "feature"
    DOCUMENTATION = "documentation"
    OPTIMIZATION = "optimization"
    TEST = "test"
    CONFIG = "config"
    STYLE = "style"
    UNKNOWN = "unknown"


class ToolPatterns:
    """Common tool usage patterns and their significance."""

    MULTIPLE_READS = "multiple_reads"  # Multiple read_file operations before an edit
    SEARCH_THEN_EDIT = "search_then_edit"  # Search operations followed by edits
    ITERATIVE_REFINEMENT = "iterative_refinement"  # Edit followed by reapply
    EXPLORATION = "exploration"  # Multiple search or read operations
    CODE_EXECUTION = "code_execution"  # Running terminal commands to test code

    @classmethod
    def identify_patterns(cls, tool_sequence: str) -> List[str]:
        """
        Identify common patterns in a tool sequence.

        Args:
            tool_sequence: String representation of tool usage sequence
                           (e.g., "read_file→edit_file→run_terminal_cmd")

        Returns:
            List of pattern identifiers found in the sequence
        """
        patterns = []
        tools = tool_sequence.split("→")

        # Count occurrences of each tool
        read_count = tools.count("read_file")
        edit_count = tools.count("edit_file")
        search_count = sum(1 for t in tools if t in ["grep_search", "codebase_search"])
        terminal_count = tools.count("run_terminal_cmd")
        reapply_count = tools.count("reapply")

        # Identify patterns
        if read_count > 2:
            patterns.append(cls.MULTIPLE_READS)

        if search_count > 0 and edit_count > 0:
            patterns.append(cls.SEARCH_THEN_EDIT)

        if edit_count > 0 and reapply_count > 0:
            patterns.append(cls.ITERATIVE_REFINEMENT)

        if read_count + search_count > 3 and edit_count == 0:
            patterns.append(cls.EXPLORATION)

        if terminal_count > 0:
            patterns.append(cls.CODE_EXECUTION)

        return patterns


def extract_code_snippets(before_content: str, after_content: str, max_context_lines: int = 50) -> str:
    """
    Extract relevant code snippets showing changes between before and after content.

    Args:
        before_content: Original content before changes
        after_content: Modified content after changes
        max_context_lines: Maximum number of lines to include in snippets

    Returns:
        Formatted string with before/after code snippets
    """
    if not before_content and not after_content:
        return ""

    # Handle case where one content is empty (new file or deleted file)
    if not before_content:
        after_lines = after_content.splitlines()[:max_context_lines]
        if len(after_lines) == max_context_lines:
            after_lines.append("... (truncated)")
        return f"NEW FILE:\n```\n{os.linesep.join(after_lines)}\n```"

    if not after_content:
        before_lines = before_content.splitlines()[:max_context_lines]
        if len(before_lines) == max_context_lines:
            before_lines.append("... (truncated)")
        return f"DELETED FILE:\n```\n{os.linesep.join(before_lines)}\n```"

    # Use difflib to find differences
    diff = list(
        difflib.unified_diff(before_content.splitlines(), after_content.splitlines(), n=3, lineterm="")  # Context lines
    )

    # Extract relevant sections (headers + changes with context)
    relevant_diff = []
    in_hunk = False

    for line in diff:
        if line.startswith("+++") or line.startswith("---"):
            continue

        if line.startswith("@@"):
            in_hunk = True
            relevant_diff.append(line)
            continue

        if in_hunk:
            relevant_diff.append(line)

    # Truncate if too long
    if len(relevant_diff) > max_context_lines:
        half_max = max_context_lines // 2
        # Keep beginning and end
        truncated_diff = relevant_diff[:half_max] + ["... (truncated) ..."] + relevant_diff[-half_max:]
        relevant_diff = truncated_diff

    return "CHANGED FILE:\n```diff\n" + os.linesep.join(relevant_diff) + "\n```"


def generate_diff_summary(before_content: str, after_content: str, file_path: str) -> str:
    """
    Generate a concise summary of changes between two contents.

    Args:
        before_content: Original content before changes
        after_content: Modified content after changes
        file_path: Path to the file being modified

    Returns:
        Human-readable summary of the key changes
    """
    # Handle file creation/deletion
    if not before_content:
        return f"Created new file {file_path}"

    if not after_content:
        return f"Deleted file {file_path}"

    # Count added/removed lines
    diff = list(difflib.unified_diff(before_content.splitlines(), after_content.splitlines(), n=0))

    added = len([line for line in diff if line.startswith("+")])
    removed = len([line for line in diff if line.startswith("-")])

    # Basic summary
    summary = f"Modified {file_path}: {added} lines added, {removed} lines removed"

    # Try to determine nature of change if possible
    before_lines = before_content.splitlines()
    after_lines = after_content.splitlines()

    # Look for function/class changes
    function_pattern = re.compile(r"^\s*(def|class)\s+(\w+)")
    before_funcs = set()
    after_funcs = set()

    for line in before_lines:
        match = function_pattern.match(line)
        if match:
            before_funcs.add(f"{match.group(1)} {match.group(2)}")

    for line in after_lines:
        match = function_pattern.match(line)
        if match:
            after_funcs.add(f"{match.group(1)} {match.group(2)}")

    new_funcs = after_funcs - before_funcs
    removed_funcs = before_funcs - after_funcs

    if new_funcs:
        summary += f". Added: {', '.join(new_funcs)}"

    if removed_funcs:
        summary += f". Removed: {', '.join(removed_funcs)}"

    return summary


def track_tool_sequence(tools_used: List[str]) -> str:
    """
    Convert a list of used tools into a standardized sequence string.

    Args:
        tools_used: List of tool names in order of use

    Returns:
        Standardized tool sequence string (e.g., "read_file→edit_file→run_terminal_cmd")
    """
    if not tools_used:
        return ""

    # Filter out duplicate consecutive tools (e.g., read_file→read_file→edit_file becomes read_file→edit_file)
    filtered_tools = []
    for tool in tools_used:
        if not filtered_tools or filtered_tools[-1] != tool:
            filtered_tools.append(tool)

    return "→".join(filtered_tools)


def calculate_confidence_score(tool_sequence: str, file_changes: List[Dict[str, Any]], response_length: int) -> float:
    """
    Calculate a confidence score (0.0-1.0) for the value of an interaction.

    Args:
        tool_sequence: The sequence of tools used
        file_changes: List of files modified with change information
        response_length: Length of AI response in characters

    Returns:
        Confidence score between 0.0 and 1.0
    """
    base_score = 0.5  # Start at middle

    # Adjust based on tool usage
    tools = tool_sequence.split("→")

    # Complex interactions tend to be more valuable
    if len(tools) > 3:
        base_score += 0.1

    # File edits are usually high value
    if "edit_file" in tools:
        base_score += 0.15

    # Multiple file reads suggests research/understanding
    if tools.count("read_file") > 2:
        base_score += 0.05

    # Terminal command execution suggests testing/verification
    if "run_terminal_cmd" in tools:
        base_score += 0.05

    # Reapplies suggest iteration/refinement
    if "reapply" in tools:
        base_score += 0.05

    # File changes are valuable
    if file_changes:
        base_score += 0.1

        # Multiple file changes suggest larger impact
        if len(file_changes) > 1:
            base_score += 0.05

    # Very short responses may indicate less value
    if response_length < 100:
        base_score -= 0.15

    # Ensure score is within bounds
    return min(1.0, max(0.0, base_score))


def determine_modification_type(
    file_changes: List[Dict[str, Any]], prompt_summary: str, response_summary: str
) -> ModificationType:
    """
    Determine the type of modification based on changes and summaries.

    Args:
        file_changes: List of files modified with change information
        prompt_summary: Summary of the user's prompt
        response_summary: Summary of the AI's response

    Returns:
        ModificationType enum value
    """
    # Look for clues in the summaries
    combined_text = (prompt_summary + " " + response_summary).lower()

    # Check for documentation changes first (highest priority for these keywords)
    if any(term in combined_text for term in ["document", "comment", "explain", "readme", "documentation"]):
        return ModificationType.DOCUMENTATION

    # Check for test-related changes (higher priority)
    if any(term in combined_text for term in ["test", "unittest", "pytest", "testing", "test case"]):
        return ModificationType.TEST

    # Check for style changes
    if any(term in combined_text for term in ["style", "format", "indent", "lint", "formatting"]):
        return ModificationType.STYLE

    # Continue with other categories
    if any(term in combined_text for term in ["bug", "fix", "issue", "problem", "error"]):
        return ModificationType.BUGFIX

    if any(term in combined_text for term in ["refactor", "clean", "restructure", "improve"]):
        return ModificationType.REFACTOR

    if any(term in combined_text for term in ["add", "feature", "implement", "new"]):
        return ModificationType.FEATURE

    if any(term in combined_text for term in ["optimize", "performance", "faster", "efficient"]):
        return ModificationType.OPTIMIZATION

    if any(term in combined_text for term in ["config", "setting", "parameter", "environment"]):
        return ModificationType.CONFIG

    # Default if no clear indicators
    return ModificationType.UNKNOWN


def manage_bidirectional_links(chat_id: str, file_changes: List[Dict[str, str]], chroma_client) -> Dict[str, List[str]]:
    """
    Manage bidirectional links between chat history and code chunks.

    Args:
        chat_id: ID of the current chat history entry
        file_changes: List of files modified
        chroma_client: ChromaDB client instance for interacting with collections

    Returns:
        Dictionary mapping file paths to their chunk IDs in codebase_v1
    """
    result = {}

    try:
        # Get the codebase collection
        codebase_collection = chroma_client.get_collection(name="codebase_v1")
        if not codebase_collection:
            logger.warning(f"Codebase collection not found, cannot create bidirectional links for chat {chat_id}")
            return result

        # Process each file change to find related code chunks
        for file_change in file_changes:
            file_path = file_change.get("file_path", "")
            if not file_path:
                continue

            # Query codebase_v1 to find chunks containing this file
            query_response = codebase_collection.query(
                query_texts=[f"file:{file_path}"],
                n_results=10,  # Get multiple chunks if file is split
                where={"file_path": {"$eq": file_path}},
            )

            # Process results if we found any
            if query_response and "ids" in query_response and len(query_response["ids"]) > 0:
                chunk_ids = query_response["ids"][0]  # First query result's ids

                # Only add to result if we have actual chunk IDs
                if chunk_ids:
                    # Store in result map for return
                    result[file_path] = chunk_ids

                    # For each chunk, update the related_chat_ids field
                    for chunk_id in chunk_ids:
                        try:
                            # Get current metadata for this chunk
                            chunk_data = codebase_collection.get(ids=[chunk_id])

                            if chunk_data and "metadatas" in chunk_data and chunk_data["metadatas"]:
                                metadata = chunk_data["metadatas"][0]

                                # Update related_chat_ids field
                                related_chat_ids = metadata.get("related_chat_ids", "")
                                chat_ids = set(related_chat_ids.split(",")) if related_chat_ids else set()
                                chat_ids.add(chat_id)

                                # Update metadata with new related_chat_ids
                                metadata["related_chat_ids"] = ",".join(filter(None, chat_ids))

                                # Update the chunk's metadata
                                codebase_collection.update(ids=[chunk_id], metadatas=[metadata])
                                logger.debug(f"Updated bidirectional link for chunk {chunk_id} with chat {chat_id}")
                        except Exception as e:
                            logger.error(f"Failed to update bidirectional link for chunk {chunk_id}: {e}")

    except Exception as e:
        logger.error(f"Error managing bidirectional links: {e}")

    return result
