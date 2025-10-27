import time
import sys
import hashlib
import subprocess
import logging
from pathlib import Path
from typing import Set, List, Tuple, Optional
import os
import glob
import re
import uuid

# Explicitly configure logger for this module to ensure DEBUG messages are shown when configured
logger = logging.getLogger(__name__)
# Check if handlers are already present to avoid duplicates if run multiple times
if not logger.handlers:
    handler = logging.StreamHandler()  # Or use appropriate handler
    formatter = logging.Formatter("%(asctime)s - %(name)s - %(levelname)s - %(message)s")
    handler.setFormatter(formatter)
    logger.addHandler(handler)

from .connection import get_client_and_ef

# Define supported file types (can be extended)
DEFAULT_SUPPORTED_SUFFIXES: Set[str] = {
    ".py",
    ".ts",
    ".js",
    ".go",
    ".java",
    ".md",
    ".txt",
    ".sh",
    ".yaml",
    ".json",
    ".h",
    ".c",
    ".cpp",
    ".cs",
    ".rb",
    ".php",
    ".toml",
    ".ini",
    ".cfg",
    ".sql",
    ".dockerfile",
    "Dockerfile",
    ".env",
}

# Default collection name (consider making this configurable)
DEFAULT_COLLECTION_NAME = "codebase_v1"


def get_current_commit_sha(repo_root: Path) -> Optional[str]:
    """Gets the current commit SHA of the Git repository."""
    try:
        # Ensure repo_root is a string for the command
        cmd = ["git", "-C", str(repo_root), "rev-parse", "HEAD"]
        result = subprocess.run(cmd, capture_output=True, text=True, check=True, encoding="utf-8")
        return result.stdout.strip()
    except FileNotFoundError:
        logger.error(f"'git' command not found. Ensure Git is installed and in PATH for repo {repo_root}.")
    except subprocess.CalledProcessError as e:
        logger.error(f"Error getting commit SHA for {repo_root}: {e.stderr.strip() if e.stderr else e.stdout.strip()}")
    except Exception as e:
        logger.error(f"Unexpected error getting commit SHA for {repo_root}: {e}", exc_info=True)
    return None


def chunk_file_content(content: str, lines_per_chunk: int = 40, line_overlap: int = 5) -> List[Tuple[str, int, int]]:
    """
    Chunks content by lines.
    Returns a list of tuples: (chunk_text, start_line_idx (0-based), end_line_idx (0-based, inclusive)).
    """
    lines = content.splitlines()
    if not lines:
        return []

    chunks_with_pos = []
    current_line_idx = 0

    while current_line_idx < len(lines):
        start_idx = current_line_idx
        # Exclusive end index for slicing, so + lines_per_chunk
        end_idx_slice = min(current_line_idx + lines_per_chunk, len(lines))
        chunk_lines = lines[start_idx:end_idx_slice]

        if chunk_lines:  # Only add if there are lines in the chunk
            # Inclusive end index for metadata, so end_idx_slice - 1
            chunks_with_pos.append(("\n".join(chunk_lines), start_idx, end_idx_slice - 1))

        if end_idx_slice == len(lines):  # Reached the end of the file
            break

        advance = lines_per_chunk - line_overlap
        # Prevent infinite loop if overlap is too large or lines_per_chunk is too small
        if advance <= 0:
            logger.warning(
                f"Chunking advance is {advance} (<=0) due to overlap ({line_overlap}) "
                f"and lines_per_chunk ({lines_per_chunk}). Advancing by 1 to prevent infinite loop."
            )
            advance = 1
        current_line_idx += advance

    # Filter out chunks that might be empty after join if they only contained empty lines
    return [c for c in chunks_with_pos if c[0].strip()]


def chunk_file_content_semantic(
    content: str, file_path: Path, lines_per_chunk: int = 40, line_overlap: int = 5
) -> List[Tuple[str, int, int]]:
    """
    Chunks content using semantic boundaries when possible.

    For code files, tries to chunk along class and function boundaries.
    Falls back to line-based chunking when semantic chunking is not suitable.

    Args:
        content: File content to chunk
        file_path: Path to the file (used to determine file type)
        lines_per_chunk: Max lines per chunk for fallback chunking
        line_overlap: Line overlap for fallback chunking

    Returns:
        List of tuples: (chunk_text, start_line_idx (0-based), end_line_idx (0-based, inclusive))
    """
    lines = content.splitlines()
    if not lines:
        return []

    suffix = file_path.suffix.lower()

    # Check if we should use semantic chunking based on file type
    if suffix in (".py", ".js", ".ts", ".java", ".c", ".cpp", ".cs", ".go", ".php", ".rb"):
        # Try semantic chunking for code files
        chunks = _chunk_code_semantic(lines, suffix)

        # If semantic chunking produced meaningful chunks, use those
        if chunks and len(chunks) > 1:  # More than one chunk indicates successful semantic splitting
            logger.debug(f"Using semantic chunking for {file_path}")
            return chunks
        else:
            logger.debug(f"Semantic chunking not effective for {file_path}, falling back to line-based chunking")

    # Fall back to standard line-based chunking
    return chunk_file_content(content, lines_per_chunk, line_overlap)


def _chunk_code_semantic(lines: List[str], file_type: str) -> List[Tuple[str, int, int]]:
    """
    Chunk code files based on semantic structure.

    Args:
        lines: List of code lines
        file_type: File extension to determine language

    Returns:
        List of tuples: (chunk_text, start_line_idx, end_line_idx)
    """
    chunks = []

    # Basic patterns for common code constructs
    class_pattern = re.compile(r"^\s*(class|interface|struct)\s+\w+")
    function_pattern = re.compile(
        r"^\s*(def|function|func|public|private|protected|static|void|int|float|double|String)\s+\w+\s*\("
    )

    # Python-specific function pattern
    py_function_pattern = re.compile(r"^\s*(?:async\s+)?def\s+\w+\s*\(")

    # JavaScript/TypeScript patterns
    js_function_pattern = re.compile(
        r"^\s*(?:async\s+)?(?:function\s+\w+|\w+\s*=\s*(?:async\s+)?function|\w+\s*=\s*\(.*\)\s*=>|(?:async\s+)?\(.*\)\s*=>)"
    )
    js_class_method_pattern = re.compile(r"^\s*(?:async\s+)?\w+\s*\(.*\)")

    # Find semantic boundaries
    boundaries = []
    in_docstring = False

    for i, line in enumerate(lines):
        # Skip doc comments
        if file_type == ".py":
            if line.strip().startswith('"""') or line.strip().startswith("'''"):
                in_docstring = not in_docstring
                continue
            if in_docstring:
                continue

        # Check for class/module-level constructs
        if class_pattern.match(line):
            boundaries.append(i)

        # Check for function definitions based on language
        if file_type == ".py" and py_function_pattern.match(line):
            boundaries.append(i)
        elif file_type in (".js", ".ts") and (js_function_pattern.match(line) or js_class_method_pattern.match(line)):
            boundaries.append(i)
        elif function_pattern.match(line):
            boundaries.append(i)

    if not boundaries:
        return []

    # Add start and end boundaries
    boundaries = [0] + boundaries + [len(lines)]
    boundaries = sorted(set(boundaries))  # Remove duplicates and sort

    # Create chunks from boundaries
    for i in range(len(boundaries) - 1):
        start_line = boundaries[i]
        end_line = boundaries[i + 1] - 1  # -1 because end is inclusive

        # If chunk is empty or too small, skip
        if end_line < start_line:
            continue

        chunk_text = "\n".join(lines[start_line : end_line + 1])
        if not chunk_text.strip():
            continue

        chunks.append((chunk_text, start_line, end_line))

    # If we have only one very large chunk, split it further using line-based chunking
    MAX_LINES_PER_SEMANTIC_CHUNK = 100
    result_chunks = []

    for chunk_text, start_line, end_line in chunks:
        chunk_lines = chunk_text.splitlines()

        # If chunk is too big, split it
        if len(chunk_lines) > MAX_LINES_PER_SEMANTIC_CHUNK:
            sub_chunks = chunk_file_content(chunk_text, MAX_LINES_PER_SEMANTIC_CHUNK, 5)
            # Adjust line numbers to be relative to the whole file
            for sub_text, sub_start, sub_end in sub_chunks:
                result_chunks.append((sub_text, start_line + sub_start, start_line + sub_end))
        else:
            result_chunks.append((chunk_text, start_line, end_line))

    return result_chunks


def index_file(
    file_path: Path,
    repo_root: Path,
    collection_name: str = DEFAULT_COLLECTION_NAME,
    supported_suffixes: Set[str] = DEFAULT_SUPPORTED_SUFFIXES,
    # Allow commit SHA to be passed in, e.g., from git hook
    commit_sha_override: Optional[str] = None,
) -> bool:
    """Reads, chunks, embeds, and upserts a single file into the specified ChromaDB collection.

    Args:
        file_path: Absolute path to the file.
        repo_root: Absolute path to the repository root (for relative path metadata).
        collection_name: Name of the ChromaDB collection.
        supported_suffixes: Set of file extensions to index.
        commit_sha_override: Optional specific commit SHA to associate with this file version.
                             If None, attempts to get current HEAD commit.

    Returns:
        True if the file was processed and chunks were upserted, False otherwise.
    """
    if not file_path.is_absolute():
        logger.debug(
            f"[index_file] Received relative path '{file_path}'. Assuming relative to repo_root '{repo_root}'."
        )
        file_path = (repo_root / file_path).resolve()
        logger.debug(f"[index_file] Resolved to absolute path: '{file_path}'")

    client, embedding_func = get_client_and_ef()

    if not file_path.exists() or file_path.is_dir():
        logger.debug(f"Skipping non-existent or directory: {file_path}")
        return False

    if file_path.suffix.lower() not in supported_suffixes:
        logger.debug(f"Skipping unsupported file type: {file_path.suffix}")
        return False

    try:
        content = file_path.read_text(encoding="utf-8", errors="ignore")
        if not content.strip():
            logger.info(f"Skipping empty file: {file_path}")
            return False

        # Determine commit SHA
        if commit_sha_override:
            commit_sha = commit_sha_override
            logger.debug(f"Using provided commit SHA: {commit_sha} for {file_path.name}")
        else:
            logger.debug(f"Attempting to get current HEAD commit SHA for {file_path.name}")
            commit_sha = get_current_commit_sha(repo_root)
            if not commit_sha:
                logger.error(f"Could not determine commit SHA for {file_path.name}. Skipping indexing.")
                return False
            logger.debug(f"Using current HEAD commit SHA: {commit_sha} for {file_path.name}")

        relative_path = str(file_path.relative_to(repo_root))

        # Get or create the collection (only need to do this once per file)
        try:
            # Explicitly pass embedding_function to trigger early mismatch error
            collection = client.get_collection(name=collection_name, embedding_function=embedding_func)
            logger.debug(f"Using existing collection: {collection_name} with configured embedding function.")
        except ValueError as e:
            error_str = str(e).lower()
            # Check for specific ChromaDB error messages related to EF mismatch
            ef_mismatch_error = (
                "embedding function name mismatch" in error_str
                or "an embedding function must be specified" in error_str
            )  # if collection expects EF but none/wrong one given

            if ef_mismatch_error:
                client_ef_name_str = type(embedding_func).__name__ if embedding_func else "None"
                collection_ef_name_str = "unknown (from collection)"  # Default if parsing fails

                # Map of known EF class names to their likely representation in ChromaDB error messages
                # (typically lowercase with underscores)
                ef_class_to_error_name_map = {
                    "SentenceTransformerEmbeddingFunction": "sentence_transformer",
                    "ONNXMiniLM_L6_V2": "onnx_mini_lm_l6_v2",
                    "OpenAIEmbeddingFunction": "openai",  # Guessing pattern
                    "CohereEmbeddingFunction": "cohere",  # Guessing pattern
                    # Add others as encountered or confirmed
                }

                # Get the expected error string name for the client's current EF
                client_ef_error_name_lower = ef_class_to_error_name_map.get(
                    client_ef_name_str, client_ef_name_str.lower()
                )

                if "embedding function name mismatch" in error_str:
                    try:
                        mismatch_details = str(e).split("Embedding function name mismatch: ")[1]
                        parts = mismatch_details.split(" != ")
                        if len(parts) == 2:
                            part0_lower = parts[0].strip().lower()
                            part1_lower = parts[1].strip().lower()

                            # Check if the client's EF (in its error string form) matches one of the parts
                            if client_ef_error_name_lower == part0_lower:
                                collection_ef_name_str = parts[1].strip()  # The other part is the collection's EF
                            elif client_ef_error_name_lower == part1_lower:
                                collection_ef_name_str = parts[0].strip()  # The other part is the collection's EF
                            else:
                                # Client's EF error name didn't match either part directly.
                                # This could happen if map is incomplete or error format is very unexpected.
                                logger.debug(
                                    f"Client EF error name '{client_ef_error_name_lower}' (from class '{client_ef_name_str}') "
                                    f"did not match parts '{part0_lower}' or '{part1_lower}' from error: {str(e)}. "
                                    f"Falling back to OR display."
                                )
                                collection_ef_name_str = (
                                    f"{parts[0].strip()} OR {parts[1].strip()} (client used {client_ef_name_str})"
                                )
                        else:  # Mismatch string present, but " != " format not as expected
                            logger.debug(
                                f"EF mismatch error string '{str(e)}' did not contain ' != ' separator or produce 2 parts as expected."
                            )
                            collection_ef_name_str = "different from client's configuration (malformed error details)"

                    except (IndexError, ValueError) as parse_error:  # Errors from split() or list indexing
                        logger.debug(
                            f"Could not parse EF mismatch details from error string '{str(e)}': {parse_error}",
                            exc_info=True,
                        )
                        collection_ef_name_str = "different from client's configuration (parsing failed)"
                elif "an embedding function must be specified" in error_str:
                    logger.debug(
                        f"EF mismatch: collection requires an EF, but client's attempt was problematic. Error: {str(e)}"
                    )
                    collection_ef_name_str = "required by collection (mismatch with client's attempt)"
                else:  # ef_mismatch_error is True, but the specific known strings weren't matched
                    logger.debug(f"Unhandled ef_mismatch_error string: {str(e)}")
                    collection_ef_name_str = "different from client's configuration (unrecognized error format)"

                env_ef_setting = os.getenv("CHROMA_EMBEDDING_FUNCTION", "default")
                error_message = (
                    f"Failed to get collection '{collection_name}' for indexing. Mismatch: "
                    f"Client is configured to use an embedding function derived from '{env_ef_setting}' (resolves to {client_ef_name_str}), "
                    f"but the collection appears to use an EF like '{collection_ef_name_str}'. "
                    f"Ensure CHROMA_EMBEDDING_FUNCTION is consistent or re-index collection '{collection_name}' with the correct embedding function."
                )
                logger.error(error_message)
                print(f"ERROR: {error_message}", file=sys.stderr)
                return False  # Critical error, cannot proceed

            # Preserved logic: Check if the error message indicates the collection doesn't exist
            not_found = False
            if (
                f"collection {collection_name} does not exist" in error_str
                or f"collection named {collection_name} does not exist" in error_str
            ):
                not_found = True

            if not_found:
                logger.info(f"Collection '{collection_name}' not found, creating...")
                try:
                    collection = client.create_collection(
                        name=collection_name,
                        embedding_function=embedding_func,
                        get_or_create=False,
                    )
                    logger.info(f"Successfully created collection: {collection_name}")
                except Exception as create_e:
                    logger.error(f"Failed to create collection '{collection_name}': {create_e}", exc_info=True)
                    return False
            else:
                logger.error(f"Error getting collection '{collection_name}': {e}", exc_info=True)
                return False
        except Exception as get_e:
            logger.error(f"Unexpected error getting collection '{collection_name}': {get_e}", exc_info=True)
            return False

        # Now chunk the file content using semantic boundaries when possible
        chunks_with_pos = chunk_file_content_semantic(content, file_path)
        if not chunks_with_pos:
            logger.info(f"No meaningful chunks extracted from {file_path}")
            return False

        # Log info about chunking
        logger.debug(f"Split {file_path} into {len(chunks_with_pos)} chunks")

        ids_list = []
        metadatas_list = []
        documents_list = []
        chunk_count = 0

        for chunk_index, (chunk_text, start_line, end_line) in enumerate(chunks_with_pos):
            # Generate chunk_id: relative_path:commit_sha:chunk_index
            chunk_id = f"{relative_path}:{commit_sha}:{chunk_index}"

            chunk_metadata = {
                "file_path": relative_path,
                "commit_sha": commit_sha,
                "chunk_index": chunk_index,
                "start_line": start_line + 1,  # User-facing lines are 1-based
                "end_line": end_line + 1,  # User-facing lines are 1-based
                "filename": file_path.name,
                "last_indexed_utc": time.time(),
                "chunk_id": chunk_id,  # Also store chunk_id in metadata for easier retrieval if needed
            }

            ids_list.append(chunk_id)
            metadatas_list.append(chunk_metadata)
            documents_list.append(chunk_text)
            chunk_count += 1

        if not ids_list:
            logger.warning(f"No chunks generated to index for {relative_path} at commit {commit_sha}")
            return False

        # Upsert all chunks for this file at once
        collection.upsert(ids=ids_list, metadatas=metadatas_list, documents=documents_list)
        logger.info(f"Indexed {chunk_count} chunks for: {relative_path} at commit {commit_sha[:7]}")
        return True

    except Exception as e:
        logger.error(f"Error indexing {file_path}: {e}", exc_info=True)
        return False


def index_git_files(
    repo_root: Path,
    collection_name: str = DEFAULT_COLLECTION_NAME,
    supported_suffixes: Set[str] = DEFAULT_SUPPORTED_SUFFIXES,
) -> int:
    """Indexes all files tracked by Git within the repository root.

    Args:
        repo_root: Absolute path to the repository root.
        collection_name: Name of the ChromaDB collection.
        supported_suffixes: Set of file extensions to index.

    Returns:
        The number of files successfully indexed.
    """
    logger.info(f"Indexing all tracked git files in {repo_root}...")
    indexed_count = 0
    try:
        # Use 'git ls-files -z' for safer handling of filenames with spaces/special chars
        cmd = ["git", "-C", str(repo_root), "ls-files", "-z"]
        result = subprocess.run(cmd, capture_output=True, check=True, encoding="utf-8")

        # Split by null character
        files_to_index = [repo_root / f for f in result.stdout.strip("\0").split("\0") if f]
        logger.info(f"Found {len(files_to_index)} files tracked by git.")

        # Consider getting the collection once before the loop for efficiency
        # client, _ = get_client_and_ef()
        # collection = client.get_or_create_collection(name=collection_name, ...)

        for file_path in files_to_index:
            if index_file(file_path, repo_root, collection_name, supported_suffixes):
                indexed_count += 1

        logger.info(f"Successfully indexed {indexed_count} out of {len(files_to_index)} tracked files.")
        return indexed_count

    except FileNotFoundError:
        logger.error(f"'git' command not found. Ensure Git is installed and in PATH.")
        return 0
    except subprocess.CalledProcessError as e:
        logger.error(f"Error running 'git ls-files' in {repo_root}: {e}")
        logger.error(f"Git stderr: {e.stderr}")
        return 0
    except Exception as e:
        logger.error(f"An unexpected error occurred during git file indexing: {e}", exc_info=True)
        return 0


def index_paths(
    paths: Set[str],
    repo_root: Path,
    collection_name: str = DEFAULT_COLLECTION_NAME,
    supported_suffixes: Set[str] = DEFAULT_SUPPORTED_SUFFIXES,
) -> int:
    """Indexes multiple files and directories specified by paths.

    Args:
        paths: Set of file paths to index.
        repo_root: Absolute path to the repository root.
        collection_name: Name of the ChromaDB collection.
        supported_suffixes: Set of file extensions to index.

    Returns:
        The number of files successfully indexed.
    """
    logger.info(f"Processing {len(paths)} specified file/directory paths...")
    indexed_count = 0
    try:
        for p in paths:
            path_obj = Path(p)
            try:
                if path_obj.is_dir():
                    # Recursively process directory
                    logger.debug(f"Indexing directory: {p}")
                    for root, _, files in os.walk(path_obj):
                        for file in files:
                            file_path_abs = (Path(root) / file).resolve()  # Resolve for symlinks etc.
                            if index_file(file_path_abs, repo_root, collection_name, supported_suffixes):
                                indexed_count += 1
                elif path_obj.is_file():
                    logger.debug(f"Indexing file: {p}")
                    # Construct absolute path from repo_root and the relative path_obj
                    absolute_file_path = (repo_root / path_obj).resolve()
                    # --- DEBUGGING START (index_paths) ---
                    logger.debug(
                        f"[index_paths] Calling index_file with: absolute_file_path='{absolute_file_path}', repo_root='{repo_root}'"
                    )
                    # --- DEBUGGING END (index_paths) ---
                    if index_file(absolute_file_path, repo_root, collection_name, supported_suffixes):
                        indexed_count += 1
                else:
                    logger.warning(f"Skipping path (not a file or directory): {p}")
            except Exception as e:
                logger.error(f"Error processing path {p}: {e}", exc_info=True)

        logger.info(f"Successfully indexed {indexed_count} out of {len(paths)} specified files and directories.")
        return indexed_count

    except Exception as e:
        logger.error(f"An unexpected error occurred during path indexing: {e}", exc_info=True)
        return 0
