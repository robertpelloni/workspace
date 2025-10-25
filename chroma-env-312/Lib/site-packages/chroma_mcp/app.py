"""
Application setup for the Chroma MCP Server.

This module initializes the shared FastMCP instance (`mcp`) used throughout the
application. It also registers a basic server utility tool (`chroma_get_server_version`)
directly via the decorator.

Crucially, it imports the tool modules (`.tools.collection_tools`, etc.) AFTER
the `mcp` instance is created. This allows the `@mcp.tool` decorators within
those modules to automatically register themselves with the shared `mcp` instance.
"""

import importlib.metadata
from typing import Dict
import sys
import logging
import os
import time
import tempfile  # Add tempfile import
import glob
import datetime

from mcp.server import Server
from mcp.server.lowlevel.server import NotificationOptions
from mcp.server.stdio import stdio_server

# Configure logging at module import time - CRITICAL FOR STDIO MODE
# In stdio mode, we must ensure NO logs go to stdout or stderr to avoid corrupting JSON

# 1. Create log directory if it doesn't exist
# Use a temporary directory that's guaranteed to be writable
log_dir = os.getenv("CHROMA_LOG_DIR")
try:
    if not log_dir:
        # If not set, first try a relative path in current directory
        log_dir = os.path.join(os.getcwd(), "logs")

    # Try to create the directory, catch permission errors
    try:
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

# 2. Configure a file handler for all logs (with timestamp in filename to avoid conflicts)
timestamp = int(time.time())
log_file = os.path.join(log_dir, f"chroma_mcp_stdio_{timestamp}.log")

# 3. Configure the root logger with a file handler
root_logger = logging.getLogger()
log_level_str = os.getenv("MCP_SERVER_LOG_LEVEL", "INFO")
log_level = getattr(logging, log_level_str.upper(), logging.INFO)
root_logger.setLevel(log_level)  # Use environment variable for log level

# 4. Remove any existing handlers that might log to stdout/stderr
for handler in root_logger.handlers[:]:
    root_logger.removeHandler(handler)

# 5. Add file handler
file_handler = logging.FileHandler(log_file)
formatter = logging.Formatter("%(asctime)s - %(name)s - %(levelname)s - %(message)s")
file_handler.setFormatter(formatter)
root_logger.addHandler(file_handler)

# 6. Add null handler to prevent uncaught logs going to default stderr
null_handler = logging.NullHandler()
root_logger.addHandler(null_handler)

# 7. Log that we've configured logging
logging.info(f"STDIO MODE: Logging configured - all logs redirected to {log_file}")

# 8. Cleanup old log files
try:
    # Import config utility and load server configuration
    from chroma_mcp.utils.config import load_config

    # Get the retention period from server configuration (default to 7 days)
    config = load_config()
    log_retention_days = config.log_retention_days
    logging.info(f"Log retention policy set to {log_retention_days} days")

    # Calculate the cutoff date
    cutoff_date = datetime.datetime.now() - datetime.timedelta(days=log_retention_days)
    cutoff_timestamp = cutoff_date.timestamp()

    # Find and delete old log files
    log_pattern = os.path.join(log_dir, "chroma_mcp_stdio_*.log")
    log_files = glob.glob(log_pattern)
    deleted_count = 0

    for log_file_path in log_files:
        try:
            # Extract timestamp from filename or use file modification time as fallback
            file_name = os.path.basename(log_file_path)
            try:
                # Try to extract timestamp from filename (chroma_mcp_stdio_TIMESTAMP.log)
                timestamp_str = file_name.split("_")[3].split(".")[0]
                file_timestamp = float(timestamp_str)
            except (IndexError, ValueError):
                # If extraction fails, use file modification time
                file_timestamp = os.path.getmtime(log_file_path)

            # Delete if older than retention period
            if file_timestamp < cutoff_timestamp:
                os.remove(log_file_path)
                deleted_count += 1
        except Exception as e:
            logging.warning(f"Failed to process log file {log_file_path}: {e}")

    if deleted_count > 0:
        logging.info(f"Cleaned up {deleted_count} log files older than {log_retention_days} days")
except Exception as e:
    logging.warning(f"Failed to cleanup old log files: {e}")

# 9. Monkey patch logging.getLogger to ensure any future loggers get our configuration
original_getLogger = logging.getLogger


def patched_getLogger(name=None):
    logger = original_getLogger(name)

    # If this is a new logger with no handlers, ensure it gets our configuration
    if not logger.handlers:
        # Remove propagation to prevent double logging
        logger.propagate = False

        # Add our file handler
        handler = logging.FileHandler(log_file)
        handler.setFormatter(formatter)
        logger.addHandler(handler)

        # Add null handler to avoid default stderr output
        logger.addHandler(logging.NullHandler())

    return logger


logging.getLogger = patched_getLogger
logging.info("Monkey patched logging.getLogger to ensure all future loggers use file output only")

# Create the single, shared standard Server instance
# Using 'server' instead of 'mcp' to avoid confusion with the protocol name
server = Server(name="chroma-mcp-server")

# logger.info("Shared standard MCP Server instance created.")

# Register server utility tools directly here if they are simple
# REMOVE: We will define this in list_tools and handle in call_tool now
# @mcp.tool(name="chroma_get_server_version", description="Return the installed version of the chroma-mcp-server package.")
# def get_version_tool() -> Dict[str, str]:
#      """Return the installed version of the chroma-mcp-server package.
#
#      This tool takes no arguments.
#
#      Returns:
#          A dictionary containing the package name ('chroma-mcp-server') and its
#          installed version string. Returns 'unknown (not installed)' or 'error (...)'
#          if the version cannot be determined.
#      """
#      try:
#          version = importlib.metadata.version('chroma-mcp-server')
#          return {"package": "chroma-mcp-server", "version": version}
#      except importlib.metadata.PackageNotFoundError:
#          return {"package": "chroma-mcp-server", "version": "unknown (not installed)"}
#      except Exception as e:
#         # TODO: Add logging here if possible/needed
#         # logger.error(f"Error getting server version: {str(e)}")
#          return {"package": "chroma-mcp-server", "version": f"error ({str(e)})"}

# Tool modules will be imported after server is defined to allow registration.


async def main_stdio():
    """Run the server using stdio transport."""
    # Logging is already configured at module import time
    logging.info("Entering stdio mode - all logs are going to file only")

    # logger.info("Entering stdio_server context manager...")
    async with stdio_server() as (read_stream, write_stream):
        # logger.info("Stdio streams acquired. Triggering tool handler registration...")
        # Import tool modules HERE to trigger registration
        try:
            from chroma_mcp.tools import collection_tools
            from chroma_mcp.tools import document_tools
            from chroma_mcp.tools import thinking_tools

            logging.info("Successfully imported tool modules inside main_stdio.")
            # Explicitly import server module AFTER tools to ensure decorators run
            import chroma_mcp.server

            logging.info("Explicitly imported chroma_mcp.server.")
        except ImportError as e:
            # logger.error(f"Failed to import tool modules/server inside main_stdio: {e}", exc_info=True)
            print(f"Failed to import tool modules/server inside main_stdio: {e}", file=sys.stderr)
            raise

        logging.info("Creating initialization options...")
        init_options = server.create_initialization_options(
            notification_options=NotificationOptions(
                # Configure notifications if needed
            )
        )
        logging.info("Initialization options created. Calling server.run...")
        try:
            await server.run(
                read_stream,
                write_stream,
                init_options,
                raise_exceptions=True,
            )
            logging.info("server.run completed successfully.")
        except Exception as e:
            logging.error(f"Error during server.run: {e}", exc_info=True)
            print(f"Error during server.run: {e}", file=sys.stderr)
            raise


# REMOVE the _register_tool_handlers function
# def _register_tool_handlers():
#    ...

# Note: We could also place the imports directly at the top level here,
# but putting them in a function called from main_stdio ensures they run
# only when the stdio server is starting and makes the dependency clearer.
