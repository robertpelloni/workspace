"""
Command Line Interface for the Direct ChromaDB Client.

Provides commands for indexing, querying, and managing the ChromaDB instance
used for automation tasks like RAG context building.
"""

import argparse
import os
import sys
import logging
from pathlib import Path
from dotenv import load_dotenv
import uuid
import time
import json
import click
from typing import Tuple, Dict, Any, List
import re
import datetime

# Get our specific logger
logger = logging.getLogger(__name__)

# Removed sys.path manipulation logic
# Imports should work directly when the package is installed
from .connection import get_client_and_ef
from .indexing import index_file, index_git_files
from .analysis import analyze_chat_history  # Import the new function
from .auto_log_chat_impl import log_chat_to_chroma  # Import the chat logging function

# Import from utils to set the main logger
from chroma_mcp.utils import set_main_logger, BASE_LOGGER_NAME as UTILS_BASE_LOGGER_NAME

# Import the function for the new subcommand
from .interactive_promoter import run_interactive_promotion

# Import the refactored promotion function
from .learnings import promote_to_learnings_collection

# Import the cleanup_test_artifacts function
from .validation.test_workflow import (
    check_for_completed_workflows,
    setup_automated_workflow,
    cleanup_test_artifacts,
)

# Import the schema for CodeQualityEvidence
from .validation.schemas import CodeQualityEvidence

# --- Constants ---
DEFAULT_COLLECTION_NAME = "codebase_v1"
DEFAULT_QUERY_RESULTS = 5

# Load environment variables from .env file
load_dotenv()

# Determine default log level from environment or fallback
default_log_level_env = os.getenv("LOG_LEVEL", "INFO").upper()
if default_log_level_env not in ["DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"]:
    default_log_level_env = "INFO"  # Fallback if invalid value in env


def main():
    """Main entry point for the chroma-mcp-client CLI."""
    # Configure logging EARLY inside main()
    log_format = "%(asctime)s - %(name)s - %(levelname)s - %(message)s"
    # Set a default level; will be adjusted based on verbosity later
    logging.basicConfig(level=logging.WARNING, format=log_format)

    # Get the logger for the current module (chroma_mcp_client.cli)
    # This specific logger is fine, but we also need to set the main one for utils.
    logger = logging.getLogger(__name__)

    # --- Setup Logging Level based on verbosity (occurs after arg parsing) ---
    # The actual setting of levels will happen after args are parsed.
    # For now, we ensure a basic config is up.

    parser = argparse.ArgumentParser(
        description="ChromaDB Client CLI for indexing and querying.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument(
        "-v",
        "--verbose",
        action="count",
        default=0,
        help="Increase output verbosity (e.g., -v for INFO, -vv for DEBUG)",
    )

    subparsers = parser.add_subparsers(dest="command", required=True, help="Available commands")

    # --- Index Subparser ---
    index_parser = subparsers.add_parser(
        "index",
        help="Index specific files or all git-tracked files into ChromaDB.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    index_parser.add_argument(
        "paths",
        nargs="*",
        help="Optional specific file or directory paths to index.",
        type=Path,
        default=[],
    )
    index_parser.add_argument(
        "--repo-root",
        type=Path,
        default=Path(os.getcwd()),
        help="Repository root path (used for determining relative paths for IDs).",
    )
    index_parser.add_argument(
        "--all", action="store_true", help="Index all files currently tracked by git in the repo."
    )
    index_parser.add_argument(
        "--collection-name",
        default=DEFAULT_COLLECTION_NAME,
        help="Name of the ChromaDB collection to use.",
    )

    # --- Count Subparser ---
    count_parser = subparsers.add_parser("count", help="Count documents in a ChromaDB collection.")
    count_parser.add_argument(
        "--collection-name",
        default=DEFAULT_COLLECTION_NAME,
        help="Name of the ChromaDB collection to count.",
    )

    # --- Query Subparser ---
    query_parser = subparsers.add_parser("query", help="Query a ChromaDB collection.")
    query_parser.add_argument("query_text", help="The text to query for.")
    query_parser.add_argument(
        "--collection-name",
        default=DEFAULT_COLLECTION_NAME,
        help="Name of the ChromaDB collection to query.",
    )
    query_parser.add_argument(
        "-n",
        "--n-results",
        type=int,
        default=DEFAULT_QUERY_RESULTS,
        help="Number of results to return.",
    )

    # --- Analyze Chat History Subparser ---
    analyze_parser = subparsers.add_parser(
        "analyze-chat-history",
        help="Analyze recent chat history to correlate with Git changes.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    analyze_parser.add_argument(
        "--collection-name",
        default="chat_history_v1",
        help="Name of the ChromaDB chat history collection.",
    )
    analyze_parser.add_argument(
        "--repo-path",
        type=Path,
        default=Path(os.getcwd()),
        help="Path to the Git repository to analyze.",
    )
    analyze_parser.add_argument(
        "--status-filter",
        default="captured",
        help="Metadata status value to filter entries for analysis.",
    )
    analyze_parser.add_argument(
        "--new-status",
        default="analyzed",
        help="Metadata status value to set after analysis.",
    )
    analyze_parser.add_argument(
        "--days-limit",
        type=int,
        default=7,
        help="How many days back to look for entries to analyze.",
    )
    analyze_parser.add_argument(
        "--prioritize-by-confidence",
        action="store_true",
        help="Prioritize entries with higher confidence scores for analysis.",
    )

    # --- Update Collection EF Subparser ---
    update_ef_parser = subparsers.add_parser(
        "update-collection-ef",
        help="Update the embedding function name stored in a collection's metadata.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    update_ef_parser.add_argument(
        "--collection-name",
        required=True,
        help="Name of the ChromaDB collection to update.",
    )
    update_ef_parser.add_argument(
        "--ef-name",
        required=True,
        help="The new embedding function name string to store (e.g., 'sentence_transformer').",
    )

    # --- Setup Collections Subparser ---
    setup_collections_parser = subparsers.add_parser(
        "setup-collections",
        help="Check and create all required ChromaDB collections if they do not exist.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    # No arguments needed for this command yet, but parser is set up for future extension

    # --- Review and Promote Subparser ---
    review_promote_parser = subparsers.add_parser(
        "review-and-promote",
        help="Interactively review 'analyzed' chat entries and promote them to learnings.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    review_promote_parser.add_argument(
        "--days-limit",
        type=int,
        default=7,
        help="How many days back to look for 'analyzed' entries.",
    )
    review_promote_parser.add_argument(
        "--fetch-limit",
        type=int,
        default=50,
        help="Maximum number of entries to fetch for review in one go.",
    )
    review_promote_parser.add_argument(
        "--chat-collection-name",
        default="chat_history_v1",
        help="Name of the ChromaDB chat history collection.",
    )
    review_promote_parser.add_argument(
        "--learnings-collection-name",
        default="derived_learnings_v1",
        help="Name of the collection to add derived learnings to.",
    )
    review_promote_parser.add_argument(
        "--modification-type",
        choices=[
            "all",
            "refactor",
            "bugfix",
            "feature",
            "documentation",
            "optimization",
            "test",
            "config",
            "style",
            "unknown",
        ],
        default="all",
        help="Filter entries by modification type.",
    )
    review_promote_parser.add_argument(
        "--min-confidence",
        type=float,
        default=0.0,
        help="Minimum confidence score threshold (0.0-1.0).",
    )
    review_promote_parser.add_argument(
        "--sort-by-confidence",
        action="store_true",
        default=True,
        help="Sort entries by confidence score (highest first).",
    )
    review_promote_parser.add_argument(
        "--no-sort-by-confidence",
        action="store_false",
        dest="sort_by_confidence",
        help="Don't sort entries by confidence score.",
    )

    # --- Promote Learning Subparser ---
    promote_parser = subparsers.add_parser(
        "promote-learning",
        help="Promote an analyzed insight or manual finding into the derived learnings collection.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    promote_parser.add_argument(
        "--description",
        required=True,
        help="Natural language description of the learning (will be embedded).",
    )
    promote_parser.add_argument(
        "--pattern",
        required=True,
        help="Core pattern identified (e.g., code snippet, regex, textual description).",
    )
    promote_parser.add_argument(
        "--code-ref",
        required=True,
        help="Code reference illustrating the learning (e.g., chunk_id 'path:sha:index').",
    )
    promote_parser.add_argument(
        "--tags",
        required=True,
        help="Comma-separated tags for categorization (e.g., 'python,refactor,logging').",
    )
    promote_parser.add_argument(
        "--confidence",
        required=True,
        type=float,
        help="Confidence score for this learning (e.g., 0.0 to 1.0).",
    )
    promote_parser.add_argument(
        "--source-chat-id",
        help="Optional ID of the source entry in the chat history collection.",
    )
    promote_parser.add_argument(
        "--collection-name",
        default="derived_learnings_v1",
        help="Name of the collection to add the derived learning to.",
    )
    promote_parser.add_argument(
        "--chat-collection-name",
        default="chat_history_v1",
        help="Name of the chat history collection to update status if source ID is provided.",
    )
    promote_parser.add_argument(
        "--include-chat-context",
        action="store_true",
        default=True,
        help="Include rich context from the source chat entry (code context, diff summary, etc.)",
    )
    promote_parser.add_argument(
        "--no-include-chat-context",
        action="store_false",
        dest="include_chat_context",
        help="Don't include rich context from the source chat entry",
    )
    promote_parser.add_argument(
        "--validation-evidence-id",
        help="ID of validation evidence to associate with this learning.",
    )
    promote_parser.add_argument(
        "--validation-score",
        type=float,
        help="Optional validation score (0.0 to 1.0) for this learning.",
    )
    promote_parser.add_argument(
        "--require-validation",
        action="store_true",
        help="If set, promotion will fail if validation score does not meet threshold.",
    )
    promote_parser.add_argument(
        "--validation-threshold",
        type=float,
        default=0.7,
        help="Threshold for validation score (0.0 to 1.0) when --require-validation is set.",
    )

    # --- Log Chat Subparser ---
    log_chat_parser = subparsers.add_parser(
        "log-chat",
        help="Log chat interaction with enhanced context to ChromaDB.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    log_chat_parser.add_argument(
        "--prompt-summary",
        required=True,
        help="Summary of the user's prompt/question.",
    )
    log_chat_parser.add_argument("--response-summary", required=True, help="Summary of the AI's response/solution.")
    log_chat_parser.add_argument(
        "--raw-prompt",
        help="Full text of the user's prompt.",
    )
    log_chat_parser.add_argument(
        "--raw-response",
        help="Full text of the AI's response.",
    )
    log_chat_parser.add_argument(
        "--tool-usage-file",
        help="JSON file containing tool usage information.",
    )
    log_chat_parser.add_argument(
        "--file-changes-file",
        help="JSON file containing information about file changes.",
    )
    log_chat_parser.add_argument(
        "--involved-entities",
        help="Comma-separated list of entities involved in the interaction.",
        default="",
    )
    log_chat_parser.add_argument(
        "--session-id",
        help="Session ID for the interaction (UUID). Generated if not provided.",
    )
    log_chat_parser.add_argument(
        "--collection-name",
        default="chat_history_v1",
        help="Name of the ChromaDB collection to log to.",
    )

    # --- Log Error Subparser ---
    log_error_parser = subparsers.add_parser(
        "log-error",
        help="Log runtime errors for validation evidence.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    log_error_parser.add_argument(
        "--error-type",
        required=True,
        help="Type of error (e.g., 'TypeError', 'FileNotFoundError').",
    )
    log_error_parser.add_argument(
        "--error-message",
        required=True,
        help="Error message content.",
    )
    log_error_parser.add_argument(
        "--stacktrace",
        help="Full stacktrace of the error.",
    )
    log_error_parser.add_argument(
        "--affected-files",
        help="Comma-separated list of affected file paths.",
    )
    log_error_parser.add_argument(
        "--resolution",
        help="Description of how the error was resolved.",
    )
    log_error_parser.add_argument(
        "--resolution-verified",
        action="store_true",
        help="Whether the resolution has been verified.",
    )
    log_error_parser.add_argument(
        "--collection-name",
        default="validation_evidence_v1",
        help="Name of the ChromaDB collection to store errors.",
    )

    # --- Log Test Results Subparser ---
    log_test_parser = subparsers.add_parser(
        "log-test-results",
        help="Log test results from JUnit XML for validation evidence.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    log_test_parser.add_argument(
        "xml_path",
        help="Path to the JUnit XML file with test results.",
    )
    log_test_parser.add_argument(
        "--before-xml",
        help="Optional path to a JUnit XML file from before code changes.",
    )
    log_test_parser.add_argument(
        "--commit-before",
        help="Optional git commit hash from before the change.",
    )
    log_test_parser.add_argument(
        "--commit-after",
        help="Optional git commit hash from after the change.",
    )
    log_test_parser.add_argument(
        "--collection-name",
        default="test_results_v1",
        help="Name of the ChromaDB collection to store test results.",
    )

    # --- Log Code Quality Subparser ---
    log_quality_parser = subparsers.add_parser(
        "log-quality-check",
        help="Log code quality metrics for validation evidence.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    log_quality_parser.add_argument(
        "--tool",
        required=True,
        choices=["ruff", "flake8", "pylint", "coverage"],
        help="Quality tool that generated the output.",
    )
    log_quality_parser.add_argument(
        "--before-output",
        help="Path to the tool output file from before changes.",
    )
    log_quality_parser.add_argument(
        "--after-output",
        required=True,
        help="Path to the tool output file from after changes.",
    )
    log_quality_parser.add_argument(
        "--metric-type",
        default="linting",
        choices=["linting", "complexity", "coverage", "maintainability"],
        help="Type of metric being measured.",
    )
    log_quality_parser.add_argument(
        "--collection-name",
        default="validation_evidence_v1",
        help="Name of the ChromaDB collection to store quality metrics.",
    )

    # --- Validate Evidence Subparser ---
    validate_parser = subparsers.add_parser(
        "validate-evidence",
        help="Calculate validation score for evidence and determine promotion eligibility.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    validate_parser.add_argument(
        "--evidence-file",
        help="Path to JSON file with validation evidence.",
    )
    validate_parser.add_argument(
        "--test-transitions",
        help="IDs of test transitions to include in validation.",
    )
    validate_parser.add_argument(
        "--runtime-errors",
        help="IDs of runtime errors to include in validation.",
    )
    validate_parser.add_argument(
        "--code-quality",
        help="IDs of code quality evidence to include in validation.",
    )
    validate_parser.add_argument(
        "--threshold",
        type=float,
        default=0.7,
        help="Validation score threshold for promotion eligibility (0.0-1.0).",
    )
    validate_parser.add_argument(
        "--output-file",
        help="Path to save the validation results as JSON.",
    )

    # --- Check Test Transitions Subparser ---
    check_transitions_parser = subparsers.add_parser(
        "check-test-transitions",
        help="Check for completed test-driven learning workflows and process transitions.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    check_transitions_parser.add_argument("--workspace-dir", default=".", help="Root directory of the workspace.")
    check_transitions_parser.add_argument(
        "--auto-promote",
        action="store_true",
        help="Automatically promote validated learnings from successful test transitions.",
    )
    check_transitions_parser.add_argument(
        "--confidence-threshold", type=float, default=0.8, help="Confidence threshold for auto-promotion (0.0-1.0)."
    )

    # --- Setup Test Workflow Subparser ---
    setup_workflow_parser = subparsers.add_parser(
        "setup-test-workflow",
        help="Set up the automated test-driven learning workflow.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    setup_workflow_parser.add_argument("--workspace-dir", default=".", help="Root directory of the workspace.")
    setup_workflow_parser.add_argument("--force", action="store_true", help="Force overwrite of existing git hooks.")

    # --- Cleanup Test Artifacts Subparser ---
    cleanup_test_parser = subparsers.add_parser(
        "cleanup-test-artifacts",
        help="Clean up test artifacts from a completed workflow.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    cleanup_test_parser.add_argument(
        "workflow_file",
        help="Path to the workflow file that references the artifacts to clean up.",
    )

    args = parser.parse_args()

    # --- Setup Logging Level based on verbosity ---
    if args.verbose == 1:
        log_level = logging.INFO
    elif args.verbose >= 2:
        log_level = logging.DEBUG
    else:
        # Default to INFO if not specified or 0, to ensure our logs are seen
        # unless the user *really* wants less (which isn't an option here)
        log_level = logging.INFO

    # Set the level for the root logger AND the main 'chromamcp' base logger from utils
    # This affects all loggers unless they have their own level set
    logging.getLogger().setLevel(log_level)
    logging.getLogger(UTILS_BASE_LOGGER_NAME).setLevel(log_level)  # Configure the base 'chromamcp' logger

    # Set the main logger instance for chroma_mcp.utils
    # This uses the already configured 'chromamcp' base logger.
    set_main_logger(logging.getLogger(UTILS_BASE_LOGGER_NAME))

    # Set the level specifically for our client's own sub-loggers if desired
    # (e.g., chroma_mcp_client.cli, chroma_mcp_client.connection)
    # This ensures that even if the root/base is INFO, client can be DEBUG if -vv
    logging.getLogger("chroma_mcp_client").setLevel(log_level)

    # Optionally set levels for other loggers if needed (e.g., sentence_transformers)
    logging.getLogger("sentence_transformers").setLevel(logging.WARNING)

    # logger.info(f"Log level set to {logging.getLevelName(log_level)}")
    # Use the utils logger to announce this, as it's now configured.
    utils_logger = logging.getLogger(f"{UTILS_BASE_LOGGER_NAME}.cli_setup")  # Get a child of the main logger
    utils_logger.info(
        f"Client CLI log level set to {logging.getLevelName(log_level)} for base '{UTILS_BASE_LOGGER_NAME}' and 'chroma_mcp_client'"
    )

    # Initialize client/EF early to catch connection errors
    try:
        logger.info("Initializing ChromaDB connection...")
        client, ef = get_client_and_ef()  # Loads config from .env via connection module
        logger.info(
            f"ChromaDB connection successful (Client type: {client.__class__.__name__}, EF: {ef.__class__.__name__ if ef else 'Default'})"
        )
    except Exception as e:
        logger.critical(f"Failed to initialize ChromaDB client: {e}", exc_info=True)
        sys.exit(1)

    # --- Command Handling ---
    if args.command == "index":
        collection_name = args.collection_name
        logger.info(f"Executing 'index' command for collection '{collection_name}'...")
        # Resolve repo root path - specific to index command
        repo_root_path = args.repo_root.resolve()
        # REMOVED: Premature get_or_create_collection call
        # collection = client.get_or_create_collection(
        #     name=collection_name,
        #     embedding_function=ef,  # Pass embedding function here
        #     # Add metadata if needed: metadata=get_collection_settings(...)
        # )

        if args.all:
            logger.info(f"Indexing all tracked git files in {repo_root_path}...")
            # Pass the collection_name string
            count = index_git_files(repo_root_path, collection_name)
            logger.info(f"Git index command finished. Indexed {count} files.")
        elif args.paths:
            logger.info(f"Processing {len(args.paths)} specified file/directory paths...")
            indexed_count = 0
            for path_item in args.paths:
                if path_item.is_file():
                    # Pass the collection_name string
                    if index_file(path_item, repo_root_path, collection_name):
                        indexed_count += 1
                elif path_item.is_dir():
                    logger.warning(
                        f"Skipping directory: {path_item}. Indexing directories directly is not yet supported."
                    )
                    # TODO: Implement recursive directory indexing if needed
                else:
                    logger.warning(f"Skipping non-existent path: {path_item}")
            logger.info(f"File/directory index command finished. Indexed {indexed_count} files.")
        else:
            logger.warning("Index command called without --all flag or specific paths. Nothing to index.")

    elif args.command == "count":
        collection_name = args.collection_name
        logger.info(f"Executing 'count' command for collection '{collection_name}'...")
        try:
            collection = client.get_collection(name=collection_name)
            count = collection.count()
            print(f"Collection '{collection_name}' contains {count} documents.")
        except Exception as e:
            logger.error(f"Failed to get count for collection '{collection_name}': {e}", exc_info=True)
            print(f"Error: Could not retrieve collection '{collection_name}'. Does it exist?", file=sys.stderr)
            sys.exit(1)

    elif args.command == "query":
        collection_name = args.collection_name
        logger.info(f"Executing 'query' command for collection '{collection_name}'...")
        logger.info(f"Query text: '{args.query_text}'")
        logger.info(f"Number of results: {args.n_results}")
        try:
            collection = client.get_collection(name=collection_name, embedding_function=ef)
            results = collection.query(
                query_texts=[args.query_text], n_results=args.n_results, include=["metadatas", "documents", "distances"]
            )

            print(f"\n--- Query Results for '{args.query_text}' ({args.n_results} requested) ---")
            if not results or not results.get("ids") or not results["ids"][0]:
                print("No results found.")
            else:
                # Results is a dict with lists for each query_text (we only have one)
                ids = results["ids"][0]
                distances = results["distances"][0]
                metadatas = results["metadatas"][0]
                documents = results["documents"][0]

                for i, doc_id in enumerate(ids):
                    print(f"\nResult {i+1}:")
                    print(f"  ID: {doc_id}")
                    print(f"  Distance: {distances[i]:.4f}")
                    if metadatas and metadatas[i]:
                        print(f"  Metadata: {metadatas[i]}")
                    if documents and documents[i]:
                        # Show first N characters as snippet
                        snippet = documents[i].replace("\n", " ").strip()
                        max_snippet_len = 150
                        print(
                            f"  Snippet: {snippet[:max_snippet_len]}{'...' if len(snippet) > max_snippet_len else ''}"
                        )
                print("---------------------------------------------")

        except Exception as e:
            logger.error(f"Failed to query collection '{collection_name}': {e}", exc_info=True)
            print(f"Error: Could not query collection '{collection_name}'. Does it exist?", file=sys.stderr)
            sys.exit(1)

    elif args.command == "analyze-chat-history":
        logger.info(f"Executing 'analyze-chat-history' command...")
        # Note: The analysis function uses the client and ef initialized earlier
        try:
            processed, correlated = analyze_chat_history(
                client=client,  # Pass the initialized client
                embedding_function=ef,  # Pass the initialized EF
                repo_path=str(args.repo_path.resolve()),  # Pass resolved absolute path
                collection_name=args.collection_name,
                days_limit=args.days_limit,
                # Pass limit from args if needed, or keep default from analysis function
                # limit=args.limit, # Assuming limit arg exists or is added
                status_filter=args.status_filter,
                new_status=args.new_status,
                prioritize_by_confidence=args.prioritize_by_confidence,
            )
            logger.info("'analyze-chat-history' command finished. Processed=%d, Correlated=%d", processed, correlated)
            print("Chat history analysis finished.")  # Keep simple user output
        except Exception as e:
            logger.error(f"An error occurred during chat history analysis: {e}", exc_info=True)
            print(f"Error during analysis: {e}")  # Inform user
            sys.exit(1)  # Exit with non-zero code on error

    elif args.command == "update-collection-ef":
        collection_name = args.collection_name
        ef_name = args.ef_name
        logger.info(
            f"Executing 'update-collection-ef' command for collection '{collection_name}' with new EF name '{ef_name}'..."
        )
        try:
            collection = client.get_collection(name=collection_name)  # Get it first to ensure it exists
            metadata = collection.metadata or {}
            metadata["embedding_function_name"] = ef_name
            collection.modify(metadata=metadata)
            logger.info(f"Successfully updated embedding function name for collection '{collection_name}'.")
            print(f"Embedding function name for '{collection_name}' updated to '{ef_name}'.")
        except Exception as e:
            logger.error(
                f"Failed to update embedding function name for collection '{collection_name}': {e}",
                exc_info=True,
            )
            print(
                f"Error: Could not update collection '{collection_name}'. Does it exist?",
                file=sys.stderr,
            )
            sys.exit(1)

    elif args.command == "setup-collections":
        logger.info("Executing 'setup-collections' command...")
        required_collections = [
            "codebase_v1",
            "chat_history_v1",
            "derived_learnings_v1",
            "thinking_sessions_v1",
            "validation_evidence_v1",  # New collection for validation evidence
            "test_results_v1",  # New collection for test results
        ]
        collections_created = 0
        collections_existing = 0

        for collection_name in required_collections:
            logger.info(f"Checking/Creating collection: '{collection_name}'")
            try:
                # Attempt to get the collection first to see if it exists
                # This is a bit more verbose but gives clearer logging
                try:
                    client.get_collection(name=collection_name)
                    logger.info(f"Collection '{collection_name}' already exists.")
                    collections_existing += 1
                except Exception:  # Should be a more specific exception if Chroma client provides one for not found
                    logger.info(f"Collection '{collection_name}' not found, creating...")
                    client.get_or_create_collection(
                        name=collection_name,
                        embedding_function=ef,
                        # metadata={"description": f"Default collection for {collection_name}"} # Example metadata
                    )
                    logger.info(f"Collection '{collection_name}' created successfully.")
                    collections_created += 1
            except Exception as e:
                logger.error(
                    f"Failed to check/create collection '{collection_name}': {e}",
                    exc_info=True,
                )
                print(
                    f"Error processing collection '{collection_name}'. See logs for details.",
                    file=sys.stderr,
                )
                # Optionally, decide if we should exit or continue with other collections
                # sys.exit(1) # Uncomment to exit on first error

        summary_message = (
            f"Collections setup finished. Created: {collections_created}, Already Existed: {collections_existing}."
        )
        logger.info(summary_message)
        print(summary_message)

    elif args.command == "review-and-promote":
        logger.info("Executing 'review-and-promote' command...")
        try:
            run_interactive_promotion(
                days_limit=args.days_limit,
                fetch_limit=args.fetch_limit,
                chat_collection_name=args.chat_collection_name,
                learnings_collection_name=args.learnings_collection_name,
                modification_type_filter=args.modification_type,
                min_confidence=args.min_confidence,
                sort_by_confidence=args.sort_by_confidence,
            )
            logger.info("'review-and-promote' command finished.")
            print("Interactive review and promotion process complete.")
        except Exception as e:
            logger.error(f"An error occurred during interactive promotion: {e}", exc_info=True)
            print(f"Error during interactive promotion: {e}")
            sys.exit(1)

    elif args.command == "promote-learning":
        logger.info(f"Executing 'promote-learning' command...")

        # Check validation requirements if set
        if args.require_validation:
            if args.validation_evidence_id is None and args.validation_score is None:
                logger.error("Validation required but no validation evidence or score provided")
                print("Error: --require-validation set but no validation evidence or score provided")
                sys.exit(1)

            if args.validation_score is not None and args.validation_score < args.validation_threshold:
                logger.error(f"Validation score {args.validation_score} is below threshold {args.validation_threshold}")
                print(
                    f"Error: Validation score {args.validation_score} does not meet threshold {args.validation_threshold}"
                )
                sys.exit(1)

            # If we have evidence ID but no score, we need to validate
            if args.validation_evidence_id and args.validation_score is None:
                logger.info(
                    f"Validating evidence {args.validation_evidence_id} against threshold {args.validation_threshold}"
                )
                try:
                    from chroma_mcp_client.validation.promotion import LearningPromoter

                    promoter = LearningPromoter(client)
                    evidence = promoter.get_validation_evidence(args.validation_evidence_id)

                    if evidence is None:
                        logger.error(f"Validation evidence {args.validation_evidence_id} not found")
                        print(f"Error: Validation evidence {args.validation_evidence_id} not found")
                        sys.exit(1)

                    if evidence.score < args.validation_threshold:
                        logger.error(
                            f"Validation score {evidence.score} is below threshold {args.validation_threshold}"
                        )
                        print(
                            f"Error: Validation score {evidence.score} does not meet threshold {args.validation_threshold}"
                        )
                        sys.exit(1)
                except Exception as e:
                    logger.error(f"Error validating evidence: {e}")
                    print(f"Error: Failed to validate evidence: {e}")
                    sys.exit(1)

        # Call the refactored function
        # Note: client and ef are already initialized earlier in main()
        learning_id = promote_to_learnings_collection(
            client=client,
            embedding_function=ef,
            description=args.description,
            pattern=args.pattern,
            code_ref=args.code_ref,
            tags=args.tags,
            confidence=args.confidence,
            learnings_collection_name=args.collection_name,  # from --collection-name
            source_chat_id=args.source_chat_id,
            chat_history_collection_name=args.chat_collection_name,
            include_chat_context=args.include_chat_context,
            validation_evidence_id=args.validation_evidence_id,
            validation_score=args.validation_score,
        )

        if learning_id:
            # The function already prints messages, so we might not need more here
            # or we can have a simpler success message.
            logger.info(f"'promote-learning' command completed for learning ID: {learning_id}")
        else:
            logger.error("'promote-learning' command failed. See previous logs for details.")
            sys.exit(1)  # Exit if the promotion function indicated failure by returning None

    elif args.command == "log-error":
        logger.info("Executing 'log-error' command...")
        try:
            # Import at runtime to avoid circular imports
            from chroma_mcp_client.validation.runtime_collector import (
                store_runtime_error,
                create_runtime_error_evidence_cli,
            )

            # Create runtime error evidence
            error_evidence = create_runtime_error_evidence_cli(
                error_type=args.error_type,
                error_message=args.error_message,
                stacktrace=args.stacktrace or "",
                affected_files=args.affected_files.split(",") if args.affected_files else [],
                resolution=args.resolution,
                resolution_verified=args.resolution_verified,
            )

            # Store the evidence
            error_id = store_runtime_error(error_evidence, collection_name=args.collection_name, chroma_client=client)

            logger.info(f"'log-error' command finished. Error ID: {error_id}")
            print(f"Runtime error logged successfully with ID: {error_id}")
        except Exception as e:
            logger.error(f"An error occurred during error logging: {e}", exc_info=True)
            print(f"Error during logging: {e}")
            sys.exit(1)

    elif args.command == "log-test-results":
        logger.info("Executing 'log-test-results' command...")
        try:
            # Import at runtime to avoid circular imports
            from chroma_mcp_client.validation.test_collector import parse_junit_xml, store_test_results
            from chroma_mcp_client.validation.test_collector import create_test_transition_evidence

            # Parse the JUnit XML file
            test_results = parse_junit_xml(args.xml_path)

            # Store the test results
            test_run_id = store_test_results(
                results_dict=test_results, collection_name=args.collection_name, chroma_client=client
            )

            # If before-xml is provided, create transition evidence
            if args.before_xml:
                from chroma_mcp_client.validation.evidence_collector import collect_validation_evidence

                transitions = create_test_transition_evidence(
                    before_xml=args.before_xml,
                    after_xml=args.xml_path,
                    commit_before=args.commit_before,
                    commit_after=args.commit_after,
                )

                # Create validation evidence including test transitions
                evidence = collect_validation_evidence(
                    test_transitions=transitions, runtime_errors=[], code_quality_improvements=[]
                )

                # Print validation score
                print(f"Test transitions: {len(transitions)}")
                print(f"Validation score: {evidence.score:.2f}")
                print(f"Meets threshold: {evidence.meets_threshold()}")

            logger.info(f"'log-test-results' command finished. Test Run ID: {test_run_id}")
            print(f"Test results logged successfully with ID: {test_run_id}")
        except Exception as e:
            logger.error(f"An error occurred during test result logging: {e}", exc_info=True)
            print(f"Error during logging: {e}")
            sys.exit(1)

    elif args.command == "log-quality-check":
        logger.info("Executing 'log-quality-check' command...")
        try:
            from chroma_mcp_client.validation.code_quality_collector import (
                create_code_quality_evidence,
                parse_ruff_output,
                parse_pylint_output,
                parse_flake8_output,
            )

            # Import from evidence_collector
            from chroma_mcp_client.validation.evidence_collector import (
                collect_validation_evidence,
                store_validation_evidence,
            )

            # Placeholder for a coverage parsing function - this was added in a previous step
            def parse_coverage_output(output_str: str) -> Tuple[float, Dict[str, Any]]:
                total_coverage = 0.0
                detailed_metrics = {}
                match = re.search(r"TOTAL\s+\d+\s+\d+\s+(\d+)%", output_str)
                if match:
                    total_coverage = float(match.group(1))
                else:
                    logger.warning("Could not parse total coverage percentage from output.")
                return total_coverage, detailed_metrics

            before_results_parsed: Dict[str, List[Dict[str, Any]]] = {}
            after_results_parsed: Dict[str, List[Dict[str, Any]]] = {}
            before_value_metric: float = 0.0
            after_value_metric: float = 0.0

            if args.before_output:
                try:
                    with open(args.before_output, "r") as f_before:
                        before_content = f_before.read()
                    if args.tool == "coverage":
                        before_value_metric, _ = parse_coverage_output(before_content)
                    elif args.tool == "ruff":
                        before_results_parsed = parse_ruff_output(before_content)
                        before_value_metric = sum(len(issues) for issues in before_results_parsed.values())
                    elif args.tool == "pylint":
                        before_results_parsed = parse_pylint_output(before_content)
                        before_value_metric = sum(len(issues) for issues in before_results_parsed.values())
                    elif args.tool == "flake8":
                        before_results_parsed = parse_flake8_output(before_content)
                        before_value_metric = sum(len(issues) for issues in before_results_parsed.values())
                    else:
                        logger.warning(f"Parsing for tool {args.tool} 'before' output not fully implemented.")
                except FileNotFoundError:
                    logger.warning(f"Before output file not found: {args.before_output}")
                except Exception as e:
                    logger.error(f"Error parsing before output file {args.before_output}: {e}")

            try:
                with open(args.after_output, "r") as f_after:
                    after_content = f_after.read()
                if args.tool == "coverage":
                    after_value_metric, _ = parse_coverage_output(after_content)
                elif args.tool == "ruff":
                    after_results_parsed = parse_ruff_output(after_content)
                    after_value_metric = sum(len(issues) for issues in after_results_parsed.values())
                elif args.tool == "pylint":
                    after_results_parsed = parse_pylint_output(after_content)
                    after_value_metric = sum(len(issues) for issues in after_results_parsed.values())
                elif args.tool == "flake8":
                    after_results_parsed = parse_flake8_output(after_content)
                    after_value_metric = sum(len(issues) for issues in after_results_parsed.values())
                else:
                    logger.warning(f"Parsing for tool {args.tool} 'after' output not fully implemented.")
            except FileNotFoundError:
                logger.error(f"After output file not found: {args.after_output}. This is required.")
                sys.exit(1)
            except Exception as e:
                logger.error(f"Error parsing after output file {args.after_output}: {e}")
                sys.exit(1)

            code_quality_evidence_list = []
            if args.tool == "coverage":
                logger.info(f"[DEBUG COVERAGE] tool: {args.tool}, metric_type: {args.metric_type}")
                logger.info(
                    f"[DEBUG COVERAGE] before_value_metric: {before_value_metric}, after_value_metric: {after_value_metric}"
                )
                # For coverage, we handle it directly as it's a single metric typically.
                # We don't use before_results_parsed/after_results_parsed for coverage in this path.
                evidence_item = CodeQualityEvidence(
                    tool=args.tool,
                    metric_type=args.metric_type,  # Should be 'coverage'
                    before_value=before_value_metric,
                    after_value=after_value_metric,
                    percentage_improvement=(after_value_metric - before_value_metric),  # For coverage, higher is better
                    file_path="overall",  # Coverage is usually project-wide
                    measured_at=datetime.datetime.now().isoformat(),
                )
                code_quality_evidence_list.append(evidence_item)
                logger.info(f"[DEBUG COVERAGE] code_quality_evidence_list after append: {code_quality_evidence_list}")
            else:
                # For other tools (linting), use the existing structured approach
                code_quality_evidence_list = create_code_quality_evidence(
                    tool_name=args.tool, before_results=before_results_parsed, after_results=after_results_parsed
                )

            if not code_quality_evidence_list:
                logger.error("Failed to create code quality evidence list.")
                sys.exit(1)

            # Assuming we might get multiple evidence items if, for example,
            # the function processed multiple files or metric types internally.
            # For now, let's assume it gives one primary piece of evidence,
            # or we focus on the first if multiple.
            # The evidence object itself will have before_value, after_value, metric_type

            # We need to wrap this list into a collect_validation_evidence call
            validation_evidence_to_store = collect_validation_evidence(
                code_quality_improvements=code_quality_evidence_list  # Pass the list here
            )

            evidence_id = store_validation_evidence(
                evidence=validation_evidence_to_store, collection_name=args.collection_name, chroma_client=client
            )

            logger.info(f"Code quality evidence stored with ID: {evidence_id}")
            print(f"Code quality evidence stored with ID: {evidence_id}")

            actual_before_value = 0.0
            actual_after_value = 0.0
            actual_metric_type = args.metric_type  # Default to args, but prefer from evidence

            if validation_evidence_to_store.code_quality_improvements:
                # Assuming the first item is the primary one for this CLI call's direct output
                primary_cq_evidence = validation_evidence_to_store.code_quality_improvements[0]
                actual_before_value = primary_cq_evidence.before_value
                actual_after_value = primary_cq_evidence.after_value
                actual_metric_type = primary_cq_evidence.metric_type

            # Use actual_metric_type derived from the evidence object for consistent output
            print(f"  Tool: {args.tool}, Metric: {actual_metric_type}")

            print(
                f"  Before ({actual_metric_type}): {actual_before_value}, After ({actual_metric_type}): {actual_after_value}"
            )

            improvement = 0.0
            # Recalculate improvement based on actual values from evidence
            if actual_metric_type == "coverage":  # Coverage increases
                improvement = actual_after_value - actual_before_value
                print(f"  Change: {improvement:+.2f}%")
            elif actual_before_value > 0:  # For things like error counts, where lower is better
                improvement = ((actual_before_value - actual_after_value) / actual_before_value) * 100
                print(f"  Improvement: {improvement:+.2f}%")
            else:  # If before was 0, and after is > 0, it's a regression. If both 0, no change.
                if actual_after_value > 0:
                    print(f"  Regression: {actual_after_value} new issues/points.")
                else:
                    print("  No change (both before and after are 0).")

        except Exception as e:
            logger.error(f"An error occurred during quality check logging: {e}", exc_info=True)
            print(f"Error during logging: {e}")
            sys.exit(1)

    elif args.command == "validate-evidence":
        logger.info("Executing 'validate-evidence' command...")
        try:
            # Import at runtime to avoid circular imports
            from chroma_mcp_client.validation.schemas import ValidationEvidence, calculate_validation_score
            from chroma_mcp_client.validation.evidence_collector import collect_validation_evidence

            evidence = None

            # If evidence file provided, load from JSON
            if args.evidence_file:
                with open(args.evidence_file, "r") as f:
                    evidence_data = json.load(f)
                    evidence = ValidationEvidence.model_validate(evidence_data)

            # Otherwise collect from provided IDs
            else:
                # Get test transitions, runtime errors, and code quality improvements
                # from ChromaDB collections using the provided IDs
                test_transitions = []
                runtime_errors = []
                code_quality_improvements = []

                # Here we would implement lookup logic for the various IDs
                # For now just print a message
                if args.test_transitions or args.runtime_errors or args.code_quality:
                    print("ID lookup not yet implemented. Please provide evidence file instead.")
                    evidence = collect_validation_evidence(
                        test_transitions=[], runtime_errors=[], code_quality_improvements=[]
                    )

            if evidence:
                # Calculate score if needed
                if evidence.score == 0:
                    evidence.score = calculate_validation_score(evidence)

                # Check if meets threshold
                meets_threshold = evidence.meets_threshold(args.threshold)

                # Print results
                print(f"Validation score: {evidence.score:.2f}")
                print(f"Threshold: {args.threshold}")
                print(f"Meets threshold: {meets_threshold}")
                print(f"Evidence types: {', '.join(e.value for e in evidence.evidence_types)}")

                # Save to output file if specified
                if args.output_file:
                    with open(args.output_file, "w") as f:
                        json.dump(evidence.model_dump(), f, indent=2)
                    print(f"Evidence saved to {args.output_file}")
            else:
                print("No evidence provided. Use --evidence-file or evidence type IDs.")

            logger.info(f"'validate-evidence' command finished.")
        except Exception as e:
            logger.error(f"An error occurred during evidence validation: {e}", exc_info=True)
            print(f"Error during validation: {e}")
            sys.exit(1)

    elif args.command == "log-chat":
        logger.info("Executing 'log-chat' command...")
        try:
            # Parse tool usage from file if provided
            tool_usage = []
            if args.tool_usage_file:
                with open(args.tool_usage_file, "r") as f:
                    tool_usage = json.load(f)
                logger.debug(f"Loaded tool usage from {args.tool_usage_file}: {len(tool_usage)} tools")

            # Parse file changes from file if provided
            file_changes = []
            if args.file_changes_file:
                with open(args.file_changes_file, "r") as f:
                    file_changes = json.load(f)
                logger.debug(f"Loaded file changes from {args.file_changes_file}: {len(file_changes)} files")

            # Call the implementation
            chat_id = log_chat_to_chroma(
                chroma_client=client,  # Use the initialized client
                prompt_summary=args.prompt_summary,
                response_summary=args.response_summary,
                raw_prompt=args.raw_prompt or args.prompt_summary,
                raw_response=args.raw_response or args.response_summary,
                tool_usage=tool_usage,
                file_changes=file_changes,
                involved_entities=args.involved_entities,
                session_id=args.session_id,
            )

            logger.info(f"'log-chat' command finished. Chat ID: {chat_id}")
            print(f"Chat history logged successfully with ID: {chat_id}")
        except Exception as e:
            logger.error(f"An error occurred during chat history logging: {e}", exc_info=True)
            print(f"Error during logging: {e}")
            sys.exit(1)

    elif args.command == "check-test-transitions":
        logger.info("Executing 'check-test-transitions' command...")
        try:
            # Import at runtime to avoid circular imports
            from chroma_mcp_client.validation.test_workflow import check_for_completed_workflows, TestWorkflowManager

            # Check for completed workflows
            num_processed = check_for_completed_workflows()

            if args.auto_promote:
                # TODO: Add additional logic for auto-promotion
                pass

            logger.info(f"'check-test-transitions' command finished. Processed {num_processed} workflows")
            print(f"Processed {num_processed} test transitions")

        except Exception as e:
            logger.error(f"An error occurred during checking test transitions: {e}", exc_info=True)
            print(f"Error during checking test transitions: {e}")
            sys.exit(1)

    elif args.command == "setup-test-workflow":
        logger.info("Executing 'setup-test-workflow' command...")
        try:
            # Import at runtime to avoid circular imports
            from chroma_mcp_client.validation.test_workflow import setup_automated_workflow

            # Set up the workflow
            success = setup_automated_workflow(workspace_dir=args.workspace_dir)

            if success:
                logger.info("'setup-test-workflow' command finished successfully")
                print("Test-driven learning workflow set up successfully")
            else:
                logger.error("Failed to set up test-driven learning workflow")
                print("Failed to set up test-driven learning workflow")
                sys.exit(1)

        except Exception as e:
            logger.error(f"An error occurred during setup of test workflow: {e}", exc_info=True)
            print(f"Error during setup of test workflow: {e}")
            sys.exit(1)

    elif args.command == "cleanup-test-artifacts":
        logger.info("Executing 'cleanup-test-artifacts' command...")
        try:
            if not os.path.isfile(args.workflow_file):
                logger.error(f"Workflow file not found: {args.workflow_file}")
                sys.exit(1)

            logger.info(f"Cleaning up test artifacts from workflow: {args.workflow_file}")

            success = cleanup_test_artifacts(args.workflow_file)

            if success:
                logger.info("✅ Test artifacts cleanup completed successfully")
            else:
                logger.error("❌ Failed to clean up test artifacts")
                sys.exit(1)
        except Exception as e:
            logger.error(f"An error occurred during test artifacts cleanup: {e}", exc_info=True)
            print(f"Error during cleanup: {e}")
            sys.exit(1)

    else:
        logger.error(f"Unknown command: {args.command}")


if __name__ == "__main__":
    main()
