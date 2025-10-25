"""
Chroma MCP Server - Main Implementation

This module provides the core server implementation for the Chroma MCP service,
integrating ChromaDB with the Model Context Protocol (MCP).
"""

import os
import argparse
import importlib.metadata
from typing import Dict, List, Optional, Any
from dotenv import load_dotenv
import logging
import logging.handlers  # Add this for FileHandler
import sys  # Import sys for stderr output as last resort
import json
import tempfile  # Add tempfile import

from mcp.types import ErrorData, INTERNAL_ERROR, INVALID_PARAMS

from mcp.shared.exceptions import McpError
from mcp.server import stdio

# ADD: Import the shared mcp instance from app
from .app import server

# Import ThoughtMetadata from .types
# Import ChromaClientConfig now also from .types
from .types import ThoughtMetadata, ChromaClientConfig

# Import config loading and tool registration
from .utils.config import load_config

# Import errors and specific utils (setters/getters for globals)
from .utils import (
    get_logger,
    set_main_logger,
    get_server_config,  # Keep getter for potential internal use
    set_server_config,
    get_embedding_function,
    BASE_LOGGER_NAME,
    # raise_validation_error # Keep these if used directly in server?
)
from pydantic import ValidationError  # Import for validation handling
from mcp import types  # Import base MCP types

# Import all Pydantic input models
from .tools.collection_tools import (
    CreateCollectionInput,
    CreateCollectionWithMetadataInput,
    ListCollectionsInput,
    GetCollectionInput,
    RenameCollectionInput,
    DeleteCollectionInput,
    PeekCollectionInput,
)
from .tools.document_tools import (
    AddDocumentInput,
    AddDocumentWithIDInput,
    AddDocumentWithMetadataInput,
    AddDocumentWithIDAndMetadataInput,
    QueryDocumentsInput,
    QueryDocumentsWithWhereFilterInput,
    QueryDocumentsWithDocumentFilterInput,
    GetDocumentsByIdsInput,
    GetDocumentsWithWhereFilterInput,
    GetDocumentsWithDocumentFilterInput,
    GetAllDocumentsInput,
    UpdateDocumentContentInput,
    UpdateDocumentMetadataInput,
    DeleteDocumentByIdInput,
    GetDocumentsByIdsEmbeddingsInput,
    GetDocumentsByIdsAllInput,
)
from .tools.thinking_tools import (
    SequentialThinkingInput,
    SequentialThinkingWithCustomDataInput,
    FindSimilarThoughtsInput,
    GetSessionSummaryInput,
    FindSimilarSessionsInput,
)

# Import our new LogChatInput model
from .tools.auto_log_chat_bridge import LogChatInput

# Import all _impl functions
from .tools.collection_tools import (
    _create_collection_impl,
    _create_collection_with_metadata_impl,
    _list_collections_impl,
    _get_collection_impl,
    _rename_collection_impl,
    _delete_collection_impl,
    _peek_collection_impl,
)
from .tools.document_tools import (
    _add_document_impl,
    _add_document_with_id_impl,
    _add_document_with_metadata_impl,
    _add_document_with_id_and_metadata_impl,
    _query_documents_impl,
    _query_documents_with_where_filter_impl,
    _query_documents_with_document_filter_impl,
    _get_documents_by_ids_impl,
    _get_documents_with_where_filter_impl,
    _get_documents_with_document_filter_impl,
    _get_all_documents_impl,
    _update_document_content_impl,
    _update_document_metadata_impl,
    _delete_document_by_id_impl,
    _get_documents_by_ids_embeddings_impl,
    _get_documents_by_ids_all_impl,
)
from .tools.thinking_tools import (
    _sequential_thinking_impl,
    _sequential_thinking_with_custom_data_impl,
    _find_similar_thoughts_impl,
    _get_session_summary_impl,
    _find_similar_sessions_impl,
)

# Import our log_chat implementation
from .tools.auto_log_chat_bridge import mcp_log_chat, _log_chat_impl

# Add this near the top of the file, after imports but before any other code
CHROMA_AVAILABLE = False
try:
    import chromadb
    from chromadb.config import Settings

    CHROMA_AVAILABLE = True
except ImportError:
    # Use logger if available later, print is too early here
    # We will log this warning properly within config_server
    pass

MCP_AVAILABLE = False
try:
    import mcp

    MCP_AVAILABLE = True
except ImportError:
    # Use logger if available later, print is too early here
    # We will log this warning properly within config_server
    pass

# Global variable to hold the initialized client (accessed via utils.get_chroma_client)
_chroma_client_instance = None


def _initialize_chroma_client(args: argparse.Namespace) -> None:
    """Initializes the ChromaDB client based on args and stores it globally."""
    global _chroma_client_instance
    logger = get_logger()  # Get the potentially pre-configured logger

    if _chroma_client_instance:
        logger.warning("Chroma client already initialized. Skipping re-initialization.")
        return

    try:
        # --- Load .env if specified in args ---
        if args.dotenv_path and os.path.exists(args.dotenv_path):
            load_dotenv(dotenv_path=args.dotenv_path)
            logger.info(f"Loaded environment variables from: {args.dotenv_path}")

        # --- Handle CPU provider setting ---
        use_cpu_provider = None  # Auto-detect
        if args.cpu_execution_provider != "auto":
            use_cpu_provider = args.cpu_execution_provider == "true"

        # --- Create ChromaClientConfig ---
        # Use os.getenv as fallback if args attribute doesn't exist (e.g., simpler stdio setup)
        # This makes it more robust if stdio mode doesn't parse all args

        # Get port value robustly
        port_arg = getattr(args, "port", None)
        port_env = os.getenv("CHROMA_PORT")
        port_val = port_arg if port_arg is not None else port_env if port_env is not None else 8000

        client_config = ChromaClientConfig(
            client_type=getattr(args, "client_type", os.getenv("CHROMA_CLIENT_TYPE", "persistent")),
            data_dir=getattr(args, "data_dir", os.getenv("CHROMA_DATA_DIR")),
            host=getattr(args, "host", os.getenv("CHROMA_HOST")),
            port=int(port_val),  # Use the robustly determined port value
            ssl=bool(getattr(args, "ssl", os.getenv("CHROMA_SSL", "False").lower() == "true")),
            tenant=getattr(args, "tenant", os.getenv("CHROMA_TENANT", "default_tenant")),
            database=getattr(args, "database", os.getenv("CHROMA_DATABASE", "default_database")),
            api_key=getattr(args, "api_key", os.getenv("CHROMA_API_KEY")),
            use_cpu_provider=use_cpu_provider,
            embedding_function_name=getattr(
                args, "embedding_function_name", os.getenv("CHROMA_EMBEDDING_FUNCTION", "default")
            ),
        )

        # Store the config globally via setter
        set_server_config(client_config)
        logger.info(f"Chroma client configuration set: {client_config.client_type}")

        # --- Initialize ChromaDB Client Instance ---
        # Reuse logic similar to get_chroma_client but store globally
        if not CHROMA_AVAILABLE:
            logger.error("chromadb library not found. Cannot initialize client.")
            raise McpError(ErrorData(code=INTERNAL_ERROR, message="chromadb library not installed"))

        client_type = client_config.client_type
        embedding_function = get_embedding_function(client_config.embedding_function_name)

        if client_type == "persistent":
            data_path = client_config.data_dir or "./chroma_data"
            logger.info(f"Initializing persistent ChromaDB client at: {data_path}")
            _chroma_client_instance = chromadb.PersistentClient(
                path=data_path, settings=Settings(anonymized_telemetry=False)
            )
        elif client_type == "http":
            host = client_config.host or "localhost"
            port = client_config.port or 8000
            ssl = client_config.ssl
            logger.info(f"Initializing HTTP ChromaDB client for: host={host}, port={port}, ssl={ssl}")
            _chroma_client_instance = chromadb.HttpClient(
                host=host, port=port, ssl=ssl, settings=Settings(anonymized_telemetry=False)
            )
        elif client_type == "cloud":
            # Assuming API key etc. are handled by chromadb library via env vars or config
            logger.info("Initializing Cloud ChromaDB client")
            tenant = client_config.tenant
            database = client_config.database
            api_key = client_config.api_key
            # Basic validation
            if not tenant or not database or not api_key:
                logger.error("Missing Chroma Cloud configuration (tenant, database, api_key).")
                raise ValueError("Missing Chroma Cloud configuration.")

            _chroma_client_instance = chromadb.HttpClient(
                host=client_config.host or "api.trychroma.com",  # Default cloud host
                port=client_config.port or 443,  # Default cloud port
                ssl=True,  # Cloud always uses SSL
                headers={"Authorization": f"Bearer {api_key}"},
                tenant=tenant,
                database=database,
                settings=Settings(anonymized_telemetry=False),
            )
        else:  # ephemeral
            logger.info("Initializing ephemeral ChromaDB client (in-memory)")
            # Ephemeral client (chromadb.Client) does not take EF in constructor directly.
            # It will use its own internal default or EF specified at collection creation.
            _chroma_client_instance = chromadb.Client(settings=Settings(anonymized_telemetry=False))

        # --- Ensure Essential Collections Exist ---
        if _chroma_client_instance:
            logger.info("Ensuring essential ChromaDB collections exist...")
            essential_collections = [
                "codebase_v1",
                "chat_history_v1",
                "derived_learnings_v1",
                "thinking_sessions_v1",
                "validation_evidence_v1",
                "test_results_v1",
            ]
            collections_created_on_startup = 0
            for coll_name in essential_collections:
                try:
                    # Try to get the collection to see if it exists
                    _chroma_client_instance.get_collection(name=coll_name, embedding_function=embedding_function)
                    logger.debug(f"Essential collection '{coll_name}' already exists.")
                except Exception as e:  # Broad exception to catch various ways Chroma might indicate non-existence
                    logger.info(
                        f"Essential collection '{coll_name}' not found (error: {type(e).__name__}), attempting to create..."
                    )
                    try:
                        _chroma_client_instance.get_or_create_collection(
                            name=coll_name,
                            embedding_function=embedding_function,
                            # Optionally add default metadata if desired
                            # metadata={"description": f"Auto-created essential collection: {coll_name}"}
                        )
                        logger.info(f"Successfully created essential collection '{coll_name}'.")
                        collections_created_on_startup += 1
                    except Exception as ce:
                        logger.error(f"Failed to create essential collection '{coll_name}': {ce}", exc_info=True)
            if collections_created_on_startup > 0:
                logger.info(f"Created {collections_created_on_startup} essential collections on server startup.")
        else:
            logger.error("Chroma client instance is not available. Cannot ensure essential collections.")

        # Set embedding function ONLY for persistent and http (non-cloud)
        # This check is removed as PersistentClient gets embedding_function at init
        # if hasattr(_chroma_client_instance, 'set_embedding_function') and callable(getattr(_chroma_client_instance, 'set_embedding_function')):
        #     _chroma_client_instance.set_embedding_function(embedding_function)
        # else:
        #     logger.warning(f"Client type '{client_type}' instance does not have set_embedding_function method. Skipping.")

        logger.info(f"ChromaDB client ({client_type}) initialized successfully.")

    except Exception as e:
        if logger:
            logger.critical(f"Failed to initialize Chroma client: {e}", exc_info=True)
        else:
            print(f"CRITICAL: Failed to initialize Chroma client: {e}", file=sys.stderr)
        # Use ErrorData
        raise McpError(ErrorData(code=INTERNAL_ERROR, message=f"Chroma client initialization failed: {e}"))


def config_server(args: argparse.Namespace) -> None:
    """
    Configures the Chroma MCP server based on parsed command-line arguments.
    Now focuses on logger setup and calling client initialization.
    """
    logger = None  # Initialize logger to None before try block
    try:
        # --- Load .env --- > (No longer needed here, handled in _initialize_chroma_client)
        # if args.dotenv_path and os.path.exists(args.dotenv_path):
        #    load_dotenv(dotenv_path=args.dotenv_path)

        # --- Start: Logger Configuration --- (Keep this section)
        try:
            log_dir = args.log_dir
            # If log_dir is not specified, use a relative path
            if log_dir and not os.path.isabs(log_dir):
                # Ensure relative paths are relative to current directory
                log_dir = os.path.join(os.getcwd(), log_dir)
            elif not log_dir:
                # Default to a logs directory in current working directory
                log_dir = os.path.join(os.getcwd(), "logs")

            # Try to create the directory, catch permission errors
            try:
                if log_dir:
                    os.makedirs(log_dir, exist_ok=True)
            except (PermissionError, OSError):
                # If there's a permission error, fall back to a system temp directory
                log_dir = os.path.join(tempfile.gettempdir(), "chroma_mcp_logs")
                os.makedirs(log_dir, exist_ok=True)
                print(f"WARNING: Using temporary log directory due to permission issues: {log_dir}", file=sys.stderr)

        except Exception as e:
            # Last resort fallback to temp directory
            log_dir = tempfile.gettempdir()
            print(f"WARNING: Using system temp directory for logs due to error: {e}", file=sys.stderr)

        log_level_str = os.getenv("LOG_LEVEL", "INFO").upper()
        log_level = getattr(logging, log_level_str, logging.INFO)
        logger = logging.getLogger(BASE_LOGGER_NAME)
        logger.setLevel(log_level)
        if not logger.hasHandlers():
            formatter = logging.Formatter(
                f"%(asctime)s | %(name)-{len(BASE_LOGGER_NAME)+15}s | %(levelname)-8s | %(message)s",
                datefmt="%Y-%m-%d %H:%M:%S",
            )
            console_handler = logging.StreamHandler()
            console_handler.setFormatter(formatter)
            logger.addHandler(console_handler)
            if log_dir:
                # Try to create a file handler, with fallback if it fails
                try:
                    log_file = os.path.join(log_dir, "chroma_mcp_server.log")
                    file_handler = logging.handlers.RotatingFileHandler(
                        log_file, maxBytes=10 * 1024 * 1024, backupCount=5  # 10 MB
                    )
                    file_handler.setFormatter(formatter)
                    logger.addHandler(file_handler)
                except (PermissionError, OSError) as e:
                    print(f"WARNING: Could not create log file. Logging to console only: {e}", file=sys.stderr)
        set_main_logger(logger)
        # --- End: Logger Configuration ---

        # --- Initialize Chroma Client --- > Call the new function
        _initialize_chroma_client(args)

        # --- Log Status / Warnings --- (Keep this part)
        provider_status = (
            "auto-detected"
            if getattr(args, "cpu_execution_provider", "auto") == "auto"
            else ("enabled" if getattr(args, "cpu_execution_provider", "auto") == "true" else "disabled")
        )
        logger.info(f"Server configured (CPU provider: {provider_status})")
        if log_dir:
            logger.info(f"Logs will be saved to: {log_dir}")
        if not CHROMA_AVAILABLE:
            logger.warning("Optional dependency 'chromadb' not found. ChromaDB functionality will be unavailable.")
        if not MCP_AVAILABLE:
            logger.warning("Optional dependency 'fastmcp' not found. MCP server functionality might be limited.")

    except McpError as e:
        # Re-raise McpError directly if it came from _initialize_chroma_client
        raise e
    except Exception as e:
        # Log critical error if logger exists, otherwise print
        # Use ErrorData for other unexpected config errors
        error_msg = f"Server configuration failed: {str(e)}"
        if logger:
            logger.critical(error_msg)
        else:
            print(f"CRITICAL: {error_msg}", file=sys.stderr)
        err_data = ErrorData(code=INTERNAL_ERROR, message=error_msg)
        raise McpError(err_data)


# --- Tool Registration (list_tools) ---

# Tool names dictionary for consistency
TOOL_NAMES = {
    "CREATE_COLLECTION": "chroma_create_collection",
    "CREATE_COLLECTION_WITH_META": "chroma_create_collection_with_metadata",
    "LIST_COLLECTIONS": "chroma_list_collections",
    "GET_COLLECTION": "chroma_get_collection",
    "RENAME_COLLECTION": "chroma_rename_collection",
    "DELETE_COLLECTION": "chroma_delete_collection",
    "PEEK_COLLECTION": "chroma_peek_collection",
    "ADD_DOCS": "chroma_add_document",
    "ADD_DOCS_IDS": "chroma_add_document_with_id",
    "ADD_DOCS_META": "chroma_add_document_with_metadata",
    "ADD_DOCS_IDS_META": "chroma_add_document_with_id_and_metadata",
    "QUERY_DOCS": "chroma_query_documents",
    "QUERY_DOCS_WHERE": "chroma_query_documents_with_where_filter",
    "QUERY_DOCS_DOC": "chroma_query_documents_with_document_filter",
    "GET_DOCS_IDS": "chroma_get_documents_by_ids",
    "GET_DOCS_WHERE": "chroma_get_documents_with_where_filter",
    "GET_DOCS_DOC": "chroma_get_documents_with_document_filter",
    "GET_DOCS_ALL": "chroma_get_all_documents",
    "GET_DOCS_IDS_EMBEDDINGS": "chroma_get_documents_by_ids_embeddings",
    "GET_DOCS_IDS_ALL": "chroma_get_documents_by_ids_all",
    "DELETE_DOCS": "chroma_delete_document_by_id",
    "SEQ_THINKING": "chroma_sequential_thinking",
    "SEQ_THINKING_CUSTOM": "chroma_sequential_thinking_with_custom_data",
    "FIND_THOUGHTS": "chroma_find_similar_thoughts",
    "GET_SUMMARY": "chroma_get_session_summary",
    "FIND_SESSIONS": "chroma_find_similar_sessions",
    "GET_VERSION": "chroma_get_server_version",
    "UPDATE_DOC_CONTENT": "chroma_update_document_content",
    "UPDATE_DOC_META": "chroma_update_document_metadata",
    "LOG_CHAT": "chroma_log_chat",
}

# Pydantic models mapping
INPUT_MODELS = {
    TOOL_NAMES["CREATE_COLLECTION"]: CreateCollectionInput,
    TOOL_NAMES["CREATE_COLLECTION_WITH_META"]: CreateCollectionWithMetadataInput,
    TOOL_NAMES["LIST_COLLECTIONS"]: ListCollectionsInput,
    TOOL_NAMES["GET_COLLECTION"]: GetCollectionInput,
    TOOL_NAMES["RENAME_COLLECTION"]: RenameCollectionInput,
    TOOL_NAMES["DELETE_COLLECTION"]: DeleteCollectionInput,
    TOOL_NAMES["PEEK_COLLECTION"]: PeekCollectionInput,
    TOOL_NAMES["ADD_DOCS"]: AddDocumentInput,
    TOOL_NAMES["ADD_DOCS_IDS"]: AddDocumentWithIDInput,
    TOOL_NAMES["ADD_DOCS_META"]: AddDocumentWithMetadataInput,
    TOOL_NAMES["ADD_DOCS_IDS_META"]: AddDocumentWithIDAndMetadataInput,
    TOOL_NAMES["QUERY_DOCS"]: QueryDocumentsInput,
    TOOL_NAMES["QUERY_DOCS_WHERE"]: QueryDocumentsWithWhereFilterInput,
    TOOL_NAMES["QUERY_DOCS_DOC"]: QueryDocumentsWithDocumentFilterInput,
    TOOL_NAMES["GET_DOCS_IDS"]: GetDocumentsByIdsInput,
    TOOL_NAMES["GET_DOCS_WHERE"]: GetDocumentsWithWhereFilterInput,
    TOOL_NAMES["GET_DOCS_DOC"]: GetDocumentsWithDocumentFilterInput,
    TOOL_NAMES["GET_DOCS_ALL"]: GetAllDocumentsInput,
    TOOL_NAMES["GET_DOCS_IDS_EMBEDDINGS"]: GetDocumentsByIdsEmbeddingsInput,
    TOOL_NAMES["GET_DOCS_IDS_ALL"]: GetDocumentsByIdsAllInput,
    TOOL_NAMES["DELETE_DOCS"]: DeleteDocumentByIdInput,
    TOOL_NAMES["SEQ_THINKING"]: SequentialThinkingInput,
    TOOL_NAMES["SEQ_THINKING_CUSTOM"]: SequentialThinkingWithCustomDataInput,
    TOOL_NAMES["FIND_THOUGHTS"]: FindSimilarThoughtsInput,
    TOOL_NAMES["GET_SUMMARY"]: GetSessionSummaryInput,
    TOOL_NAMES["FIND_SESSIONS"]: FindSimilarSessionsInput,
    TOOL_NAMES["UPDATE_DOC_CONTENT"]: UpdateDocumentContentInput,
    TOOL_NAMES["UPDATE_DOC_META"]: UpdateDocumentMetadataInput,
    TOOL_NAMES["GET_VERSION"]: None,  # GET_VERSION has no input model
    TOOL_NAMES["LOG_CHAT"]: LogChatInput,
}

# Tool implementation function mapping
IMPL_FUNCTIONS = {
    TOOL_NAMES["CREATE_COLLECTION"]: _create_collection_impl,
    TOOL_NAMES["CREATE_COLLECTION_WITH_META"]: _create_collection_with_metadata_impl,
    TOOL_NAMES["LIST_COLLECTIONS"]: _list_collections_impl,
    TOOL_NAMES["GET_COLLECTION"]: _get_collection_impl,
    TOOL_NAMES["RENAME_COLLECTION"]: _rename_collection_impl,
    TOOL_NAMES["DELETE_COLLECTION"]: _delete_collection_impl,
    TOOL_NAMES["PEEK_COLLECTION"]: _peek_collection_impl,
    TOOL_NAMES["ADD_DOCS"]: _add_document_impl,
    TOOL_NAMES["ADD_DOCS_IDS"]: _add_document_with_id_impl,
    TOOL_NAMES["ADD_DOCS_META"]: _add_document_with_metadata_impl,
    TOOL_NAMES["ADD_DOCS_IDS_META"]: _add_document_with_id_and_metadata_impl,
    TOOL_NAMES["QUERY_DOCS"]: _query_documents_impl,
    TOOL_NAMES["QUERY_DOCS_WHERE"]: _query_documents_with_where_filter_impl,
    TOOL_NAMES["QUERY_DOCS_DOC"]: _query_documents_with_document_filter_impl,
    TOOL_NAMES["GET_DOCS_IDS"]: _get_documents_by_ids_impl,
    TOOL_NAMES["GET_DOCS_WHERE"]: _get_documents_with_where_filter_impl,
    TOOL_NAMES["GET_DOCS_DOC"]: _get_documents_with_document_filter_impl,
    TOOL_NAMES["GET_DOCS_ALL"]: _get_all_documents_impl,
    TOOL_NAMES["GET_DOCS_IDS_EMBEDDINGS"]: _get_documents_by_ids_embeddings_impl,
    TOOL_NAMES["GET_DOCS_IDS_ALL"]: _get_documents_by_ids_all_impl,
    TOOL_NAMES["DELETE_DOCS"]: _delete_document_by_id_impl,
    TOOL_NAMES["SEQ_THINKING"]: _sequential_thinking_impl,
    TOOL_NAMES["SEQ_THINKING_CUSTOM"]: _sequential_thinking_with_custom_data_impl,
    TOOL_NAMES["FIND_THOUGHTS"]: _find_similar_thoughts_impl,
    TOOL_NAMES["GET_SUMMARY"]: _get_session_summary_impl,
    TOOL_NAMES["FIND_SESSIONS"]: _find_similar_sessions_impl,
    TOOL_NAMES["UPDATE_DOC_CONTENT"]: _update_document_content_impl,
    TOOL_NAMES["UPDATE_DOC_META"]: _update_document_metadata_impl,
    TOOL_NAMES["GET_VERSION"]: None,  # GET_VERSION needs a simple handler
    TOOL_NAMES["LOG_CHAT"]: _log_chat_impl,
}


@server.list_tools()
async def list_tools() -> List[types.Tool]:
    """Registers all available tools with the MCP server."""
    # Get logger instance
    logger = get_logger("list_tools")
    tool_definitions = [
        # Collection Tools
        types.Tool(
            name=TOOL_NAMES["CREATE_COLLECTION"],
            description="Create a new ChromaDB collection using server default settings. Requires: `collection_name`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["CREATE_COLLECTION"]].model_json_schema(),
        ),
        types.Tool(
            name=TOOL_NAMES["CREATE_COLLECTION_WITH_META"],
            description="Create a new ChromaDB collection with specific metadata/settings provided. Requires: `collection_name`, `metadata` (JSON string).",
            inputSchema=INPUT_MODELS[TOOL_NAMES["CREATE_COLLECTION_WITH_META"]].model_json_schema(),
        ),
        types.Tool(
            name=TOOL_NAMES["LIST_COLLECTIONS"],
            description="List all collections. Optional: `limit`, `offset`, `name_contains`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["LIST_COLLECTIONS"]].model_json_schema(),
        ),
        types.Tool(
            name=TOOL_NAMES["GET_COLLECTION"],
            description="Get information about a specific collection. Requires: `collection_name`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["GET_COLLECTION"]].model_json_schema(),
        ),
        types.Tool(
            name=TOOL_NAMES["RENAME_COLLECTION"],
            description="Renames an existing collection. Requires: `collection_name`, `new_name`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["RENAME_COLLECTION"]].model_json_schema(),
        ),
        types.Tool(
            name=TOOL_NAMES["DELETE_COLLECTION"],
            description="Delete a collection. Requires: `collection_name`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["DELETE_COLLECTION"]].model_json_schema(),
        ),
        types.Tool(
            name=TOOL_NAMES["PEEK_COLLECTION"],
            description="Get a sample of documents from a collection. Requires: `collection_name`. Optional: `limit`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["PEEK_COLLECTION"]].model_json_schema(),
        ),
        # Document Tools
        types.Tool(
            name=TOOL_NAMES["ADD_DOCS"],
            description="Add a document (auto-generates ID, no metadata). Requires: `collection_name`, `document`. Optional: `increment_index`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["ADD_DOCS"]].model_json_schema(),
        ),
        types.Tool(
            name=TOOL_NAMES["ADD_DOCS_IDS"],
            description="Add a document with a specified ID (no metadata). Requires: `collection_name`, `document`, `id`. Optional: `increment_index`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["ADD_DOCS_IDS"]].model_json_schema(),
        ),
        types.Tool(
            name=TOOL_NAMES["ADD_DOCS_META"],
            description="Add a document with specified metadata (auto-generates ID). Requires: `collection_name`, `document`, `metadata` (JSON string). Optional: `increment_index`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["ADD_DOCS_META"]].model_json_schema(),
        ),
        types.Tool(
            name=TOOL_NAMES["ADD_DOCS_IDS_META"],
            description="Add a document with specified ID and metadata. Requires: `collection_name`, `document`, `id`, `metadata` (JSON string). Optional: `increment_index`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["ADD_DOCS_IDS_META"]].model_json_schema(),
        ),
        types.Tool(
            name=TOOL_NAMES["QUERY_DOCS"],
            description="Query documents using semantic search. Queries the specified 'collection_name' AND the 'derived_learnings_v1' collection. Results are merged, and each item's metadata includes a 'source_collection' field. Returns IDs, documents, metadatas, and distances. Requires: `collection_name`, `query_texts`. Optional: `n_results`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["QUERY_DOCS"]].model_json_schema(),
        ),
        types.Tool(
            name=TOOL_NAMES["QUERY_DOCS_WHERE"],
            description="Query documents using semantic search with a metadata filter. Returns IDs and potentially distances/scores. Use `chroma_get_documents_by_ids` to fetch details. Requires: `collection_name`, `query_texts`, `where`. Optional: `n_results`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["QUERY_DOCS_WHERE"]].model_json_schema(),
        ),
        types.Tool(
            name=TOOL_NAMES["QUERY_DOCS_DOC"],
            description="Query documents using semantic search with a document content filter. Returns IDs and potentially distances/scores. Use `chroma_get_documents_by_ids` to fetch details. Requires: `collection_name`, `query_texts`, `where_document`. Optional: `n_results`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["QUERY_DOCS_DOC"]].model_json_schema(),
        ),
        types.Tool(
            name=TOOL_NAMES["GET_DOCS_IDS"],
            description="Get document content and metadata from a collection using specific IDs (obtained from a query). Requires: `collection_name`, `ids`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["GET_DOCS_IDS"]].model_json_schema(),
        ),
        types.Tool(
            name=TOOL_NAMES["GET_DOCS_WHERE"],
            description="Get documents from a collection using a metadata filter. Requires: `collection_name`, `where`. Optional: `limit`, `offset`, `include`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["GET_DOCS_WHERE"]].model_json_schema(),
        ),
        types.Tool(
            name=TOOL_NAMES["GET_DOCS_DOC"],
            description="Get documents from a collection using a document content filter. Requires: `collection_name`, `where_document`. Optional: `limit`, `offset`, `include`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["GET_DOCS_DOC"]].model_json_schema(),
        ),
        types.Tool(
            name=TOOL_NAMES["GET_DOCS_ALL"],
            description="Get all documents from a collection. Requires: `collection_name`. Optional: `limit`, `offset`, `include`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["GET_DOCS_ALL"]].model_json_schema(),
        ),
        # --- Start: Add New Include Variants ---
        types.Tool(
            name=TOOL_NAMES["GET_DOCS_IDS_EMBEDDINGS"],
            description="Get documents from a collection by specific IDs, including embeddings only. Requires: `collection_name`, `ids`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["GET_DOCS_IDS_EMBEDDINGS"]].model_json_schema(),
        ),
        types.Tool(
            name=TOOL_NAMES["GET_DOCS_IDS_ALL"],
            description="Get documents from a collection by specific IDs, including all available data. Requires: `collection_name`, `ids`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["GET_DOCS_IDS_ALL"]].model_json_schema(),
        ),
        # --- End: Add New Include Variants ---
        types.Tool(
            name=TOOL_NAMES["DELETE_DOCS"],
            description="Delete a document from a collection by its specific ID. Requires: `collection_name`, `id`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["DELETE_DOCS"]].model_json_schema(),
        ),
        # Update Document Variants
        types.Tool(
            name=TOOL_NAMES["UPDATE_DOC_CONTENT"],
            description="Update the content of an existing document by ID. Requires: `collection_name`, `id`, `document`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["UPDATE_DOC_CONTENT"]].model_json_schema(),
        ),
        types.Tool(
            name=TOOL_NAMES["UPDATE_DOC_META"],
            description="Update the metadata of an existing document by ID. Requires: `collection_name`, `id`, `metadata` (dict).",
            inputSchema=INPUT_MODELS[TOOL_NAMES["UPDATE_DOC_META"]].model_json_schema(),
        ),
        # Thinking Tools
        types.Tool(
            name=TOOL_NAMES["SEQ_THINKING"],
            description="Records a single thought. Requires: `thought`, `thought_number`, `total_thoughts`. Optional: `session_id`, `branch_id`, `branch_from_thought`, `next_thought_needed`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["SEQ_THINKING"]].model_json_schema(),
        ),
        types.Tool(
            name=TOOL_NAMES["FIND_THOUGHTS"],
            description="Finds thoughts semantically similar to a query. Requires: `query`. Optional: `session_id`, `n_results`, `threshold`, `include_branches`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["FIND_THOUGHTS"]].model_json_schema(),
        ),
        types.Tool(
            name=TOOL_NAMES["GET_SUMMARY"],
            description="Retrieves all thoughts recorded within a specific thinking session. Requires: `session_id`. Optional: `include_branches`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["GET_SUMMARY"]].model_json_schema(),
        ),
        types.Tool(
            name=TOOL_NAMES["FIND_SESSIONS"],
            description="Finds thinking sessions similar to a query. Requires: `query`. Optional: `n_results`, `threshold`.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["FIND_SESSIONS"]].model_json_schema(),
        ),
        # Utility Tool
        types.Tool(
            name=TOOL_NAMES["GET_VERSION"],
            description="Return the installed version of the chroma-mcp-server package. Takes no parameters.",
            inputSchema={
                "type": "object",
                "properties": {},
                "required": [],
            },
        ),
        types.Tool(
            name=TOOL_NAMES["LOG_CHAT"],
            description="Log chat interaction with enhanced context for future retrieval and bidirectional linking. Requires prompt and response summaries plus optional context.",
            inputSchema=INPUT_MODELS[TOOL_NAMES["LOG_CHAT"]].model_json_schema(),
        ),
    ]
    # Add debug log
    logger.debug(f"Returning {len(tool_definitions)} tool definitions: {[t.name for t in tool_definitions]}")
    # Optionally log the full definitions if needed for deep debugging:
    logger.debug(f"Full tool definitions: {tool_definitions}")
    logger.debug("Finished listing tools.")
    return tool_definitions


# --- Tool Execution (call_tool) ---


@server.call_tool()
async def call_tool(name: str, arguments: Dict[str, Any]) -> List[types.TextContent]:
    """Handles incoming tool calls, validates input, and dispatches to implementation functions."""
    logger = get_logger("call_tool")
    # Add this line to log raw arguments
    logger.debug(f"Raw arguments received for tool '{name}': {arguments}")
    # logger.debug(f"Received tool call: {name} with arguments: {arguments}")

    # REMOVE the outer try...except block. Let Server handle exceptions.
    # try:
    # --- Special case: Get Version (no Pydantic model) ---
    if name == TOOL_NAMES["GET_VERSION"]:
        try:
            version = importlib.metadata.version("chroma-mcp-server")
            result_text = json.dumps({"package": "chroma-mcp-server", "version": version})
            content_list = [types.TextContent(type="text", text=result_text)]
            logger.debug(f"Returning result for {name}: {content_list}")  # Log before return
            return content_list
        except importlib.metadata.PackageNotFoundError as e:
            logger.error(f"Error getting server version: {str(e)}", exc_info=True)
            # Raise exception for Server to handle
            error_data = ErrorData(code=INTERNAL_ERROR, message="Tool Error: chroma-mcp-server package not found.")
            raise McpError(error_data)
        except Exception as e:
            logger.error(f"Error getting server version: {str(e)}", exc_info=True)
            # Raise exception for Server to handle
            error_data = ErrorData(
                code=INTERNAL_ERROR, message=f"Tool Error: Could not get server version. Details: {str(e)}"
            )
            raise McpError(error_data)

    # --- Get Pydantic Model and Implementation Function --- >
    InputModel = INPUT_MODELS.get(name)
    impl_function = IMPL_FUNCTIONS.get(name)

    if not InputModel or not impl_function:
        logger.error(f"Unknown tool name received: {name}")
        # Raise exception for Server to handle, wrapping ErrorData
        error_data = ErrorData(code=INVALID_PARAMS, message=f"Tool Error: Unknown tool name '{name}'")
        raise McpError(error_data)

    # --- Pydantic Validation --- >
    try:
        logger.debug(f"Validating arguments for {name} using {InputModel.__name__}")
        validated_input = InputModel(**arguments)
        logger.debug(f"Validation successful for {name}")
    except ValidationError as e:
        logger.warning(f"Input validation failed for {name}: {e}")
        # Wrap Pydantic error message in McpError with ErrorData
        error_data = ErrorData(code=INVALID_PARAMS, message=f"Input Error: {str(e)}")
        raise McpError(error_data)

    # --- Call Core Logic --- >
    logger.debug(f"Calling implementation function for {name}")
    # Pass the validated Pydantic model instance to the implementation function
    # Assume impl_function now returns List[TextContent] or raises Exception
    content_list: List[types.TextContent] = await impl_function(validated_input)
    logger.debug(f"Implementation function for {name} returned content list.")

    # Add debug log before returning
    logger.debug("Debug log for call_tool result.")
    logger.debug(f"Returning call_tool result for {name}: {content_list}")  # Log before return
    logger.debug("Finished debug log for call_tool result.")
    return content_list


def main() -> None:
    """Main execution function for the Chroma MCP server.

    Assumes that `config_server` has already been called (typically by `cli.py`).
    Retrieves the globally configured logger.
    Logs the server start event, including the package version.
    Initiates the MCP server run loop using the configured stdio transport
    and the shared `server` instance from `app.py`.

    Catches and logs `McpError` exceptions specifically.
    Catches any other exceptions, logs them as critical errors, and wraps them
    in an `McpError` before raising to ensure a consistent exit status via the CLI.
    """
    logger = None  # Initialize logger variable for this scope
    try:
        # Configuration should have been done by cli.py calling config_server
        logger = get_logger()

        if logger:
            try:
                version = importlib.metadata.version("chroma-mcp-server")
            except importlib.metadata.PackageNotFoundError:
                version = "unknown"
            logger.info(f"Chroma MCP server v{version} started. Using stdio transport.")

        # Start server with stdio transport using the IMPORTED shared 'server' instance
        # The run method now needs the read/write streams and options
        # We need asyncio to run the server properly now
        import asyncio

        async def run_server():
            options = server.create_initialization_options()
            print("SERVER: Attempting to enter stdio_server context...", file=sys.stderr)
            async with stdio.stdio_server() as (read_stream, write_stream):
                print("SERVER: Entered stdio_server context. Attempting server.run...", file=sys.stderr)
                try:
                    await server.run(read_stream, write_stream, options, raise_exceptions=True)
                    print("SERVER: server.run completed.", file=sys.stderr)
                except Exception as run_err:
                    print(f"SERVER: ERROR during server.run: {run_err}", file=sys.stderr)
                    raise  # Re-raise after logging
            print("SERVER: Exited stdio_server context.", file=sys.stderr)

        # Run the async server function
        print("SERVER: Calling asyncio.run(run_server())...", file=sys.stderr)
        asyncio.run(run_server())
        print("SERVER: asyncio.run(run_server()) finished.", file=sys.stderr)

    except McpError as e:
        if logger:
            logger.error(f"MCP Error: {str(e)}")
        # Re-raise McpError directly
        raise e
    except Exception as e:
        error_msg = f"Critical error running MCP server: {str(e)}"
        if logger:
            logger.error(error_msg)
        # Use ErrorData
        err_data = ErrorData(code=INTERNAL_ERROR, message=error_msg)
        raise McpError(err_data)


if __name__ == "__main__":
    # In a typical setup, cli.py would call config_server then main.
    # For direct execution (if needed for debugging), configuration might be missing.
    # Consider adding basic argument parsing and config call here if direct execution is intended.
    # For now, assume cli.py is the entry point.
    pass
