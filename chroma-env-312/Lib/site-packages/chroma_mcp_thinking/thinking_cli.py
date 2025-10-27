#!/usr/bin/env python
"""
CLI interface for working with Chroma MCP Thinking Sessions.
Provides commands for recording thoughts, creating branches, and searching thoughts.
"""

import argparse
import json
import sys
import uuid
from typing import List, Optional, Dict, Any
import os
import asyncio  # Needed for eventual async implementation
from datetime import timedelta
import logging  # Add logging import

from mcp import ClientSession, StdioServerParameters
from mcp import types as mcp_types
from mcp.client.stdio import stdio_client

from chroma_mcp_thinking.thinking_session import ThinkingSession
from chroma_mcp_thinking.utils import (
    record_thought_chain,
    create_thought_branch,
    find_thoughts_across_sessions,
)

# Configure logging
logging.basicConfig(level=logging.INFO, format="%(asctime)s - %(name)s - %(levelname)s - %(message)s")
logger = logging.getLogger(__name__)  # Create logger instance


def _get_server_params() -> StdioServerParameters:
    """Helper to create StdioServerParameters, passing necessary environment variables."""
    # Use the cli.py entry point with the '--mode stdio' flag
    server_command = "python"
    server_args = ["-m", "chroma_mcp.cli", "--mode", "stdio"]

    # Explicitly pass necessary environment variables from the current environment
    # These are typically set by hatch run based on pyproject.toml
    server_env = {
        key: os.environ[key]
        for key in [
            "CHROMA_CLIENT_TYPE",
            "CHROMA_DATA_DIR",
            "CHROMA_LOG_DIR",
            "LOG_LEVEL",
            "MCP_LOG_LEVEL",
            # Add any other relevant CHROMA_ variables if needed (HOST, PORT, SSL, TENANT, DATABASE, API_KEY, EMBEDDING_FUNCTION)
            "CHROMA_HOST",
            "CHROMA_PORT",
            "CHROMA_SSL",
            "CHROMA_TENANT",
            "CHROMA_DATABASE",
            "CHROMA_API_KEY",
            "CHROMA_EMBEDDING_FUNCTION",
        ]
        if key in os.environ  # Only pass if they exist in the current env
    }
    # Add PATH to ensure the correct python/modules are found if necessary
    # This might be important if VS Code's integrated terminal has a different PATH
    if "PATH" in os.environ:
        server_env["PATH"] = os.environ["PATH"]

    logger.debug(f"Passing environment to server subprocess: {server_env}")

    return StdioServerParameters(
        command=server_command,
        args=server_args,
        env=server_env,  # Pass the explicit environment
        cwd=os.getcwd(),  # Run server in the same CWD
        # Consider adding a startup timeout if needed
        # startup_timeout=timedelta(seconds=30)
    )


async def cmd_record_async(args: argparse.Namespace) -> None:
    """Record a thought or chain of thoughts (Async Version)."""
    server_params = _get_server_params()
    async with stdio_client(server_params) as (read_stream, write_stream):
        async with ClientSession(read_stream, write_stream) as client:
            try:
                await client.initialize()
            except Exception as init_error:
                print(f"ERROR during client.initialize(): {init_error}", file=sys.stderr)
                raise

            # Handle direct thought input vs file input vs environment variable
            thoughts = []
            thought_source = None  # Keep track of where the thought came from

            if args.thought:
                thoughts = [args.thought]
                thought_source = "--thought argument"
            elif args.file:
                try:
                    with open(args.file, "r") as f:
                        thoughts = [line.strip() for line in f.readlines() if line.strip()]
                    thought_source = f"--file {args.file}"
                except Exception as e:
                    print(f"Error reading thoughts from file: {e}", file=sys.stderr)
                    sys.exit(1)
            else:
                # Check environment variable as fallback
                env_thought = os.environ.get("RECORD_THOUGHT_TEXT")
                if env_thought:
                    thoughts = [env_thought]
                    thought_source = "RECORD_THOUGHT_TEXT environment variable"
                # If still no thought, could add stdin read here later if desired

            if not thoughts:
                # Modify error message
                print(
                    "Error: No thought provided via --thought, --file, or RECORD_THOUGHT_TEXT environment variable.",
                    file=sys.stderr,
                )
                sys.exit(1)

            # logger.info(f"Received thought from: {thought_source}") # Optional debug log

            # Parse metadata if provided
            metadata = {}
            if args.metadata:
                try:
                    metadata = json.loads(args.metadata)
                except json.JSONDecodeError:
                    print("Invalid metadata JSON format.", file=sys.stderr)
                    sys.exit(1)

            # Record the thought(s)
            session_id_to_use = args.session_id  # Might be None

            if len(thoughts) == 1 and args.thought_number:
                # Record a single thought with specific number
                arguments = {
                    "thought": thoughts[0],
                    "thought_number": args.thought_number,
                    "total_thoughts": args.total_thoughts or args.thought_number,
                    "session_id": session_id_to_use,  # Can be None
                }
                # Only include optional args if they are not None/False
                if args.next_thought_needed:
                    arguments["next_thought_needed"] = True

                # Use call_tool with CORRECT name
                result = await client.call_tool(name="chroma_sequential_thinking", arguments=arguments)

                # Safely extract session_id from result content
                result_content_list = result.content if result else []
                result_text = (
                    result_content_list[0].text
                    if result_content_list and isinstance(result_content_list[0], mcp_types.TextContent)
                    else "{}"
                )

                try:
                    result_data = json.loads(result_text)
                    session_id_to_use = result_data.get("session_id", session_id_to_use or "unknown")
                except json.JSONDecodeError:
                    logger.warning("Could not parse JSON from tool result content: %s", result_text)
                    session_id_to_use = session_id_to_use or "unknown"

            else:
                # Record a chain of thoughts
                if not session_id_to_use:
                    session_id_to_use = str(uuid.uuid4())
                total_thoughts_chain = len(thoughts)
                for i, thought_text in enumerate(thoughts):
                    # Use call_tool with CORRECT name
                    chain_args = {
                        "thought": thought_text,
                        "thought_number": i + 1,
                        "total_thoughts": total_thoughts_chain,
                        "session_id": session_id_to_use,
                    }
                    result = await client.call_tool(
                        name="chroma_sequential_thinking",
                        arguments=chain_args,
                    )

            # Use the final session_id determined
            recorded_session_id = session_id_to_use
            print(f"Recorded {len(thoughts)} thought(s) in session: {recorded_session_id}")
            if args.verbose:
                for i, thought in enumerate(thoughts, 1):
                    print(f"  {i}. {thought[:50]}{'...' if len(thought) > 50 else ''}")

    # The 'async with' statement handles exiting the contexts


# Synchronous wrapper
def cmd_record(args: argparse.Namespace) -> None:
    # Note: This structure with manual __aenter__/__aexit__ might be less robust
    # than using 'async with' directly if the logic within becomes complex.
    # Reverting to 'async with' might be preferable once the core issue is found.
    # Back to async with
    try:
        asyncio.run(cmd_record_async(args))
    except Exception as e:
        print(f"Error in cmd_record: {e}", file=sys.stderr)
        sys.exit(1)


async def cmd_branch_async(args: argparse.Namespace) -> None:
    """Create a thought branch from an existing session (Async Version)."""
    server_params = _get_server_params()
    try:
        async with stdio_client(server_params) as (read_stream, write_stream):
            async with ClientSession(read_stream, write_stream) as client:
                try:
                    await client.initialize()
                except Exception as init_error:
                    print(f"ERROR during client.initialize(): {init_error}", file=sys.stderr)
                    raise

                # Get branch thoughts
                branch_thoughts = []
                if args.thoughts:
                    branch_thoughts = args.thoughts
                elif args.file:
                    try:
                        with open(args.file, "r") as f:
                            branch_thoughts = [line.strip() for line in f.readlines() if line.strip()]
                    except Exception as e:
                        print(f"Error reading branch thoughts from file: {e}", file=sys.stderr)
                        sys.exit(1)

                if not branch_thoughts:
                    print("No branch thoughts provided. Use --thoughts or --file.", file=sys.stderr)
                    sys.exit(1)

                # Generate branch ID if not provided
                branch_id = args.branch_id or str(uuid.uuid4())[:8]

                # Use direct client calls in a loop
                total_branch_thoughts = len(branch_thoughts)
                for i, thought_text in enumerate(branch_thoughts):
                    # Use call_tool with CORRECT name
                    await client.call_tool(
                        name="chroma_sequential_thinking",
                        arguments={
                            "thought": thought_text,
                            "thought_number": i + 1,
                            "total_thoughts": total_branch_thoughts,
                            "session_id": args.parent_session_id,
                            "branch_id": branch_id,
                            "branch_from_thought": args.parent_thought_number if i == 0 else 0,
                        },
                    )

                print(
                    f"Created branch '{branch_id}' from session {args.parent_session_id} thought #{args.parent_thought_number}"
                )
                print(f"Branch contains {len(branch_thoughts)} thought(s)")
                if args.verbose:
                    for i, thought in enumerate(branch_thoughts, 1):
                        print(f"  {i}. {thought[:50]}{'...' if len(thought) > 50 else ''}")

    except Exception as e:
        print(f"Error during command execution: {e}", file=sys.stderr)
        sys.exit(1)


# Synchronous wrapper
def cmd_branch(args: argparse.Namespace) -> None:
    try:
        asyncio.run(cmd_branch_async(args))
    except Exception as e:
        print(f"Error in cmd_branch: {e}", file=sys.stderr)
        sys.exit(1)


async def cmd_search_async(args: argparse.Namespace) -> None:
    """Search for thoughts similar to a query (Async Version)."""
    server_params = _get_server_params()
    try:
        async with stdio_client(server_params) as (read_stream, write_stream):
            async with ClientSession(read_stream, write_stream) as client:
                try:
                    await client.initialize()
                except Exception as init_error:
                    print(f"ERROR during client.initialize(): {init_error}", file=sys.stderr)
                    raise

                # Use call_tool with CORRECT name
                results_raw = await client.call_tool(
                    name="chroma_find_similar_thoughts",
                    arguments={
                        "query": args.query,
                        "session_id": args.session_id if args.session_id is not None else "",  # Send default "" if None
                        "n_results": args.n_results,
                        "threshold": args.threshold,  # Always send the value (default is -1.0)
                        "include_branches": args.include_branches,
                    },
                )
                # Process results - results_raw is a CallToolResult object
                results_content_list = results_raw.content if results_raw else []
                results_text = (
                    results_content_list[0].text
                    if results_content_list and isinstance(results_content_list[0], mcp_types.TextContent)
                    else "{}"
                )
                try:
                    # Parse the text content
                    results = json.loads(results_text)
                    similar_thoughts = results.get("similar_thoughts", [])
                except json.JSONDecodeError:
                    logger.warning("Could not parse JSON from search result content: %s", results_text)
                    similar_thoughts = []
                if not similar_thoughts:
                    print("No similar thoughts found.")
                else:
                    print(f"Found {len(similar_thoughts)} similar thoughts:")
                    for i, thought_info in enumerate(similar_thoughts, 1):
                        thought_text = thought_info.get("thought", "")
                        session_id = thought_info.get("session_id", "N/A")
                        thought_num = thought_info.get("thought_number", "?")
                        branch_id = thought_info.get("branch_id", "")
                        score = thought_info.get("score", -1.0)
                        prefix = f"  {i}. [S:{session_id} T:{thought_num}{' B:' + branch_id if branch_id else ''} Score:{score:.4f}]"
                        print(f"{prefix} {thought_text[:80]}{'...' if len(thought_text) > 80 else ''}")

    except Exception as e:
        print(f"Error during command execution: {e}", file=sys.stderr)
        sys.exit(1)


# Synchronous wrapper
def cmd_search(args: argparse.Namespace) -> None:
    try:
        asyncio.run(cmd_search_async(args))
    except Exception as e:
        print(f"Error in cmd_search: {e}", file=sys.stderr)
        sys.exit(1)


async def cmd_summary_async(args: argparse.Namespace) -> None:
    """Get a summary of a thinking session (Async Version)."""
    server_params = _get_server_params()
    try:
        async with stdio_client(server_params) as (read_stream, write_stream):
            async with ClientSession(read_stream, write_stream) as client:
                try:
                    await client.initialize()
                except Exception as init_error:
                    print(f"ERROR during client.initialize(): {init_error}", file=sys.stderr)
                    raise

                # Use call_tool with CORRECT name
                logger.info("[CLI] Calling chroma_get_session_summary tool...")
                results_raw = await client.call_tool(
                    name="chroma_get_session_summary",
                    arguments={
                        "session_id": args.session_id,
                        "include_branches": args.include_branches,
                    },
                )
                logger.info(f"[CLI] Tool call returned: {results_raw}")

                # Process results - results_raw is a CallToolResult object
                results_content_list = results_raw.content if results_raw else []
                results_text = (
                    results_content_list[0].text
                    if results_content_list and isinstance(results_content_list[0], mcp_types.TextContent)
                    else "{}"
                )

                try:
                    # Parse the text content of the first result part
                    results = json.loads(results_text)
                    session_thoughts = results.get("session_thoughts", [])
                except json.JSONDecodeError:
                    logger.warning("Could not parse JSON from summary result content: %s", results_text)
                    session_thoughts = []
                if not session_thoughts:
                    print(f"No thoughts found for session: {args.session_id}")
                else:
                    print(f"Summary for session: {args.session_id}")
                    # Sort thoughts for consistent display (optional, but helpful)
                    session_thoughts.sort(
                        key=lambda x: (
                            x.get("metadata", {}).get("branch_id", ""),
                            x.get("metadata", {}).get("thought_number", 0),
                        )
                    )
                    current_branch = None
                    for thought_info in session_thoughts:
                        # Extract data based on the actual JSON structure
                        thought_text = thought_info.get("content", "")  # Get content directly
                        metadata = thought_info.get("metadata", {})
                        thought_num = metadata.get("thought_number", "?")  # Get from metadata
                        branch_id = metadata.get("branch_id", "")  # Get from metadata
                        branch_from = metadata.get("branch_from_thought", 0)  # Get from metadata

                        if branch_id and branch_id != current_branch:
                            print(f"  --- Branch: {branch_id} (from thought #{branch_from}) ---")
                            current_branch = branch_id
                        elif not branch_id and current_branch:
                            print("  --- Main Thread ---")
                            current_branch = None

                        indent = "    " if branch_id else "  "
                        print(f"{indent}{thought_num}. {thought_text[:100]}{'...' if len(thought_text) > 100 else ''}")

    except Exception as e:
        # Log the specific exception *before* exiting
        logger.error(f"[CLI] Caught exception in cmd_summary_async: {type(e).__name__}: {e}", exc_info=True)
        print(f"Error during command execution: {e}", file=sys.stderr)
        sys.exit(1)


# Synchronous wrapper
def cmd_summary(args: argparse.Namespace) -> None:
    try:
        asyncio.run(cmd_summary_async(args))
    except Exception as e:
        print(f"Error in cmd_summary: {e}", file=sys.stderr)
        sys.exit(1)


def main():
    parser = argparse.ArgumentParser(description="Chroma MCP Thinking Tools CLI")
    subparsers = parser.add_subparsers(dest="command", required=True)

    # --- Record Command ---
    parser_record = subparsers.add_parser("record", help="Record a thought or chain of thoughts.")
    parser_record.add_argument("--thought", help="The text content of the thought.")
    parser_record.add_argument("--file", help="Path to a file containing thoughts (one per line).")
    parser_record.add_argument("--session-id", help="Optional session ID to continue an existing session.")
    parser_record.add_argument(
        "--thought-number", type=int, help="Specific thought number (only for single --thought)."
    )
    parser_record.add_argument(
        "--total-thoughts", type=int, help="Total anticipated thoughts (only for single --thought)."
    )
    parser_record.add_argument(
        "--next-thought-needed", action="store_true", help="Flag if next thought is needed (only for single --thought)."
    )
    parser_record.add_argument("--metadata", help="Optional JSON string for metadata.")
    parser_record.add_argument("-v", "--verbose", action="store_true", help="Print recorded thoughts.")
    parser_record.set_defaults(func=cmd_record)

    # --- Branch Command ---
    parser_branch = subparsers.add_parser("branch", help="Create a new thought branch from an existing session.")
    parser_branch.add_argument("parent_session_id", help="Session ID of the parent thought.")
    parser_branch.add_argument(
        "parent_thought_number", type=int, help="Thought number within the parent session to branch from."
    )
    group = parser_branch.add_mutually_exclusive_group(required=True)
    group.add_argument("--thoughts", nargs="+", help="Text content of the branch thoughts (space-separated).")
    group.add_argument("--file", help="Path to a file containing branch thoughts (one per line).")
    parser_branch.add_argument("--branch-id", help="Optional ID for the new branch (auto-generated if not provided).")
    parser_branch.add_argument("-v", "--verbose", action="store_true", help="Print created branch thoughts.")
    parser_branch.set_defaults(func=cmd_branch)

    # --- Search Command ---
    parser_search = subparsers.add_parser("search", help="Search for thoughts similar to a query.")
    parser_search.add_argument("query", help="The text query to search for.")
    parser_search.add_argument("--session-id", help="Optional session ID to limit search scope.")
    parser_search.add_argument("-n", "--n-results", type=int, default=5, help="Max number of results (default: 5).")
    parser_search.add_argument(
        "--threshold", type=float, default=-1.0, help="Similarity threshold (0.0 to 1.0, -1.0 for default)."
    )
    parser_search.add_argument(
        "--include-branches", action="store_true", help="Include thoughts from branches in the search."
    )
    parser_search.set_defaults(func=cmd_search)

    # --- Summary Command ---
    parser_summary = subparsers.add_parser("summary", help="Get a summary of a thinking session.")
    parser_summary.add_argument("session_id", help="The session ID to summarize.")
    parser_summary.add_argument(
        "--include-branches", action="store_true", help="Include thoughts from branches in the summary."
    )
    parser_summary.set_defaults(func=cmd_summary)

    # Parse arguments
    args = parser.parse_args()

    # Execute the corresponding function
    args.func(args)


if __name__ == "__main__":
    main()
