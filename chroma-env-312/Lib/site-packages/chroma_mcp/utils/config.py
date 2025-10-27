"""
Configuration utility module for managing server settings.
"""

import os
import re
from typing import Dict, Any, Optional
from dataclasses import dataclass
from dotenv import load_dotenv

from mcp.shared.exceptions import McpError
from mcp.types import ErrorData, INTERNAL_ERROR, INVALID_PARAMS

from .errors import ValidationError
from . import get_logger


@dataclass
class ServerConfig:
    """Server configuration settings."""

    log_level: str = "INFO"
    max_batch_size: int = 100
    default_collection: Optional[str] = None
    enable_telemetry: bool = False
    log_retention_days: int = 7  # Default to 7 days of log retention


def load_config(env_file: Optional[str] = None) -> ServerConfig:
    """
    Load server configuration from environment variables.

    Args:
        env_file: Optional path to .env file

    Returns:
        ServerConfig instance with loaded settings

    Raises:
        McpError: If configuration loading fails
    """
    logger = get_logger("utils.config")

    try:
        # Load environment variables if env_file is provided
        if env_file:
            logger.debug(f"Loading environment variables from: {env_file}")
            load_dotenv(env_file)

        config = ServerConfig(
            log_level=os.getenv("CHROMA_LOG_LEVEL", "INFO"),
            max_batch_size=int(os.getenv("CHROMA_MAX_BATCH_SIZE", "100")),
            default_collection=os.getenv("CHROMA_DEFAULT_COLLECTION"),
            enable_telemetry=os.getenv("CHROMA_ENABLE_TELEMETRY", "false").lower() in ["true", "1", "yes"],
            log_retention_days=int(os.getenv("LOG_RETENTION_DAYS", "7")),
        )

        logger.debug(f"Loaded configuration: {config}")
        return config

    except ValueError as e:
        logger.error(f"Invalid configuration value: {str(e)}")
        raise McpError(ErrorData(code=INVALID_PARAMS, message=f"Invalid configuration value: {str(e)}"))
    except Exception as e:
        logger.error(f"Failed to load configuration: {str(e)}")
        raise McpError(ErrorData(code=INTERNAL_ERROR, message=f"Failed to load configuration: {str(e)}"))


def get_collection_settings(
    collection_name: Optional[str] = None,
    hnsw_space: Optional[str] = None,
    hnsw_construction_ef: Optional[int] = None,
    **kwargs,
) -> Dict[str, Any]:
    """
    Get settings for a collection.

    Args:
        collection_name: Optional name of the collection for loading environment-specific settings
        hnsw_space: Optional HNSW space type (e.g., 'cosine', 'l2', 'ip')
        hnsw_construction_ef: Optional HNSW construction EF parameter
        **kwargs: Additional settings to override defaults

    Returns:
        Dictionary of collection settings
    """
    logger = get_logger("utils.config")

    # Default HNSW settings
    default_settings = {
        "hnsw:space": "cosine",
        "hnsw:construction_ef": 100,
        "hnsw:search_ef": 10,
        "hnsw:M": 16,
        "hnsw:num_threads": 4,
    }

    # Override with provided parameters
    if hnsw_space:
        default_settings["hnsw:space"] = hnsw_space
    if hnsw_construction_ef:
        default_settings["hnsw:construction_ef"] = hnsw_construction_ef

    # If collection name is provided, try to load collection-specific settings from environment
    if collection_name:
        collection_prefix = f"CHROMA_COLLECTION_{collection_name.upper()}_"
        custom_settings = {}

        for key in default_settings.keys():
            env_key = f"{collection_prefix}{key.replace(':', '_').upper()}"
            if env_value := os.getenv(env_key):
                try:
                    # Convert numeric values
                    if env_value.isdigit():
                        custom_settings[key] = int(env_value)
                    elif env_value.replace(".", "", 1).isdigit():
                        custom_settings[key] = float(env_value)
                    else:
                        custom_settings[key] = env_value
                except ValueError:
                    logger.warning(f"Invalid value for {env_key}: {env_value}")
                    custom_settings[key] = default_settings[key]

        # Merge default and custom settings
        default_settings.update(custom_settings)

    # Override with any additional settings
    default_settings.update(kwargs)

    return default_settings


def validate_collection_name(name: str) -> None:
    """
    Validate a collection name.

    Args:
        name: Collection name to validate

    Raises:
        McpError: If the collection name is invalid
    """
    logger = get_logger("utils.config")

    if not name:
        logger.warning("Empty collection name provided")
        raise McpError(ErrorData(code=INVALID_PARAMS, message="Collection name cannot be empty"))

    # Check length
    if len(name) > 64:
        logger.warning(f"Collection name too long: {name}")
        raise McpError(ErrorData(code=INVALID_PARAMS, message="Collection name cannot be longer than 64 characters"))

    # Check characters
    if not re.match(r"^[a-zA-Z0-9_-]+$", name):
        logger.warning(f"Invalid characters in collection name: {name}")
        raise McpError(
            ErrorData(
                code=INVALID_PARAMS,
                message="Collection name can only contain letters, numbers, underscores, and hyphens",
            )
        )
