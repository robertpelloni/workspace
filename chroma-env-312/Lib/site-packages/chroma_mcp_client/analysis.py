import subprocess
import json
import logging
from datetime import datetime, timedelta, timezone
from pathlib import Path
import numpy as np  # Added for cosine similarity
from chromadb.utils.embedding_functions import DefaultEmbeddingFunction  # Added
import chromadb

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

# Placeholder for ChromaDB client interaction (assuming a client object is passed)
# You'll need to integrate this with your existing connection logic (e.g., from connection.py)

# Define a threshold for embedding similarity
SIMILARITY_THRESHOLD = 0.6


def fetch_recent_chat_entries(
    collection: chromadb.Collection, status_filter: str = "captured", days_limit: int = 7, fetch_limit: int = 200
):
    """Fetches recent chat entries based on status and timestamp using a Collection object."""
    collection_name = collection.name  # Get name for logging
    logger.info(f"Fetching up to {fetch_limit} entries from '{collection_name}' with status '{status_filter}'.")

    filtered_entries = []
    try:
        # 1. Collection object is already provided
        # logger.debug(f"Getting collection: {collection_name}")
        # collection = client.get_collection(name=collection_name) # No longer needed

        # 2. Construct the where filter for status
        where_filter = {"status": status_filter}
        logger.debug(f"Fetching documents with where filter: {where_filter}")
        results = collection.get(where=where_filter, include=["metadatas"])  # Only need metadata for filtering
        logger.info(f"Initial fetch returned {len(results.get('ids', []))} entries with status '{status_filter}'.")

        # 3. Check results
        if not results or not results.get("ids"):
            logger.info("No documents found matching the status filter.")
            return []

        ids = results.get("ids", [])
        metadatas = results.get("metadatas", [])
        # documents = results.get("documents", [None] * len(ids)) # If needed

        # Sort by timestamp descending to process most recent first (optional)
        # This requires parsing all timestamps first
        logger.debug("Sorting fetched entries by timestamp...")
        entry_tuples = []
        for i, entry_id in enumerate(ids):
            metadata = metadatas[i] if i < len(metadatas) else {}
            timestamp_str = metadata.get("timestamp")
            if timestamp_str:
                try:
                    # Handle 'Z' for UTC explicitly by replacing it for fromisoformat
                    # and ensure it becomes an offset-aware datetime.
                    # For other ISO formats, parse directly.
                    if timestamp_str.endswith("Z"):
                        # Replace Z with +00:00 which fromisoformat understands
                        dt_obj = datetime.fromisoformat(timestamp_str[:-1] + "+00:00")
                    else:
                        dt_obj = datetime.fromisoformat(timestamp_str)

                    # Standardize to UTC:
                    # If naive after parsing, assume it represents UTC and make it aware.
                    if dt_obj.tzinfo is None or dt_obj.tzinfo.utcoffset(dt_obj) is None:
                        dt_obj = dt_obj.replace(tzinfo=timezone.utc)
                    # If already aware, convert to UTC to ensure all are in the same timezone for comparison.
                    else:
                        dt_obj = dt_obj.astimezone(timezone.utc)

                    entry_tuples.append((dt_obj, entry_id, metadata))
                except ValueError:
                    logger.warning(f"Could not parse timestamp '{timestamp_str}' for entry {entry_id} during sorting.")
            else:
                logger.warning(f"Missing timestamp for entry {entry_id} during sorting.")

        entry_tuples.sort(key=lambda x: x[0], reverse=True)
        logger.debug(f"Sorted {len(entry_tuples)} entries.")

        # 4. Filter locally by timestamp and limit
        # Only apply time limit if days_limit > 0
        time_limit = None
        if days_limit > 0:
            time_limit = datetime.now(timezone.utc) - timedelta(days=days_limit)
            logger.info(f"Filtering entries older than {time_limit.isoformat()} ({days_limit} days ago)...")
        else:
            logger.info("Not applying time limit (days_limit=0).")

        # Iterate through sorted tuples
        processed_count = 0
        for entry_timestamp, entry_id, metadata in entry_tuples:
            if processed_count >= fetch_limit:  # Apply the overall limit
                logger.info(f"Reached processing limit ({fetch_limit}).")
                break

            entry_status = metadata.get("status")  # Should match filter, but check anyway?

            # Check status *before* timestamp
            if entry_status != status_filter:
                logger.debug(
                    f"Skipping entry {entry_id}: Status '{entry_status}' does not match filter '{status_filter}'."
                )
                continue

            # Timestamp check (only if time_limit is set)
            if time_limit and entry_timestamp < time_limit:
                logger.debug(
                    f"Entry {entry_id}: Timestamp {entry_timestamp.isoformat()} is older than limit {time_limit.isoformat()}"
                )
                continue  # Skip this entry if it's too old

            # If we pass the time check (or if there's no time limit), add the entry
            filtered_entries.append(
                {
                    "id": entry_id,
                    "metadata": metadata,
                    # "document": documents[i] # Add if document included and needed
                }
            )
            processed_count += 1

        logger.info(
            f"Found {len(filtered_entries)} entries matching status {('and time limit ' + str(days_limit) + ' days') if days_limit > 0 else ''} (within overall limit {fetch_limit})."
        )

    except Exception as e:
        # Log the specific exception that occurred
        logger.error(f"Error fetching chat entries from '{collection_name}': {e}", exc_info=True)
        # Depending on policy, maybe return empty list or re-raise
        return []  # Return empty list on error

    return filtered_entries


def get_git_diff_after_timestamp(repo_path, file_path, timestamp_str):
    """Gets the git diff for a file after a specific timestamp."""
    try:
        timestamp = datetime.fromisoformat(timestamp_str.replace("Z", "+00:00"))
        # Format timestamp for git log --since
        since_timestamp = timestamp.strftime("%Y-%m-%d %H:%M:%S %z")

        # Find commits affecting the file since the timestamp
        # Using --follow helps track renames, but might be complex
        # Using --first-parent might simplify history if branches are noisy
        # Need to handle file_path relative to repo_path
        relative_file_path = Path(file_path).relative_to(repo_path)

        # Get commits affecting the file since the timestamp
        commits_cmd = [
            "git",
            "-C",
            str(repo_path),
            "log",
            "--format=%H",
            "--since",
            since_timestamp,
            "--",
            str(relative_file_path),
        ]
        logger.debug(f"Running git commits command: {' '.join(commits_cmd)}")
        commits_result = subprocess.run(commits_cmd, capture_output=True, text=True, check=False)

        if commits_result.returncode != 0:
            logger.error(f"Git log command failed: {commits_result.stderr}")
            return None

        commit_hashes = commits_result.stdout.strip().split("\n")
        if not commit_hashes or not commit_hashes[0]:
            logger.info(f"No commits found for {relative_file_path} since {timestamp_str}")
            return None

        # Get the diff from the *first* commit *before* the timestamp up to HEAD
        # Find the commit right before the first relevant commit
        # This is complex. Simpler approach: Show diff of the *first* commit *after* the timestamp?
        # Let's try showing the diff of the earliest commit found *after* the timestamp for simplicity first.
        earliest_commit = commit_hashes[-1]  # Last in the list is the oldest commit *after* the timestamp
        diff_cmd = [
            "git",
            "-C",
            str(repo_path),
            "show",
            "--format=",
            "--patch",
            earliest_commit,
            "--",
            str(relative_file_path),
        ]
        logger.debug(f"Running git diff command: {' '.join(diff_cmd)}")
        diff_result = subprocess.run(diff_cmd, capture_output=True, text=True, check=False)

        if diff_result.returncode != 0:
            logger.error(f"Git show command failed for commit {earliest_commit}: {diff_result.stderr}")
            return None

        logger.info(f"Found diff for {relative_file_path} in commit {earliest_commit}")
        return diff_result.stdout.strip()

    except Exception as e:
        logger.error(f"Error getting git diff for {file_path}: {e}")
        return None


def correlate_summary_with_diff(summary: str, diff: str, embedding_function) -> bool:
    """Checks for semantic correlation between a summary and a git diff using embeddings."""
    logger.debug(f"Running correlation check. Summary length: {len(summary)}, Diff length: {len(diff)}")

    if not summary or not diff or not embedding_function:
        logger.warning("Correlation check skipped: Empty summary, diff, or no embedding function provided.")
        return False

    try:
        logger.debug("Generating embeddings for summary and diff...")
        # Ensure inputs are non-empty lists of strings for the embedding function
        summary_embedding = embedding_function([summary])[0]
        diff_embedding = embedding_function([diff])[0]

        # Calculate cosine similarity
        # Convert to numpy arrays if they aren't already
        summary_vec = np.array(summary_embedding)
        diff_vec = np.array(diff_embedding)

        # Normalize vectors to unit length
        summary_vec_norm = summary_vec / np.linalg.norm(summary_vec)
        diff_vec_norm = diff_vec / np.linalg.norm(diff_vec)

        # Calculate cosine similarity (dot product of normalized vectors)
        similarity = np.dot(summary_vec_norm, diff_vec_norm)

        # Ensure similarity is a scalar float before formatting/comparison
        if isinstance(similarity, np.ndarray):
            similarity = similarity.item()

        correlation = similarity >= SIMILARITY_THRESHOLD
        # Use a safer format string for logging, explicitly converting to float
        logger.info(
            f"Correlation check result: Similarity = {float(similarity):.4f}, Threshold = {SIMILARITY_THRESHOLD}, Correlated = {correlation}"
        )
        return correlation

    except Exception as e:
        logger.error(f"Error during embedding generation or similarity calculation: {e}", exc_info=True)
        return False


def update_entry_status(client, collection_name, entry_id, new_status="analyzed"):
    """Updates the status metadata of a specific entry using the chromadb client."""
    logger.info(f"Attempting to update status for entry {entry_id} in '{collection_name}' to '{new_status}'.")
    try:
        # 1. Get the collection object
        logger.debug(f"Getting collection '{collection_name}' for update.")
        collection = client.get_collection(name=collection_name)

        # 2. Call the update method
        # Note: ChromaDB's update merges metadata by default.
        # We are only updating the 'status' field.
        logger.debug(f"Calling collection.update for id={entry_id} with metadata={{'status': '{new_status}'}}")
        collection.update(
            ids=[entry_id],  # Pass ID as a list
            metadatas=[{"status": new_status}],  # Pass metadata update as a list of dicts
        )
        logger.info(f"Successfully updated status for entry {entry_id}.")
        return True

    except Exception as e:
        # Log the specific exception that occurred
        logger.error(f"Failed to update status for entry {entry_id} in '{collection_name}': {e}", exc_info=True)
        return False


def analyze_chat_history(  # pylint: disable=too-many-locals,too-many-statements
    client: chromadb.Client,
    embedding_function: chromadb.EmbeddingFunction,
    repo_path: str,
    collection_name: str = "chat_history_v1",
    days_limit: int = 7,
    limit: int = 200,
    status_filter: str = "captured",
    new_status: str = "analyzed",
    prioritize_by_confidence: bool = True,
):
    """
    Analyzes chat history entries, compares summaries with git diffs of mentioned files,
    and updates the status of analyzed entries.

    Args:
        client: The ChromaDB client instance.
        embedding_function: The embedding function instance to use for correlations.
        repo_path: The absolute path to the root of the git repository.
        collection_name: Name of the ChromaDB collection for chat history.
        days_limit: How many days back to look for entries.
        limit: Maximum number of entries to fetch initially.
        status_filter: The status to filter entries by (e.g., "captured").
        new_status: The status to set after successful analysis.
        prioritize_by_confidence: Whether to prioritize entries by confidence score.

    Returns:
        Tuple[int, int]: Number of entries processed, number of correlations found.
    """
    logger.info("Starting chat history analysis for collection '%s'...", collection_name)

    processed_count = 0
    correlated_count = 0
    updated_entries_info = []

    try:
        # Get the collection *without* explicitly passing the EF.
        # Rely on the EF stored in the collection's metadata.
        collection = client.get_collection(name=collection_name)
        # Log the EF associated with the *retrieved* collection object for debugging
        retrieved_ef_name = (
            collection.metadata.get("hnsw:embedding_function", "Not Set") if collection.metadata else "Metadata Missing"
        )
        logger.debug(f"Retrieved collection '{collection_name}'. Metadata EF: {retrieved_ef_name}")

    except ValueError as e:
        # This specific EF mismatch error *shouldn't* happen here anymore,
        # but catch other potential ValueErrors during get_collection.
        logger.error(f"Error getting collection '{collection_name}': {e}", exc_info=True)
        return 0, 0  # Cannot proceed
    except Exception as e:
        # Catch other unexpected errors during collection retrieval
        logger.error(f"Unexpected error getting collection '{collection_name}': {e}", exc_info=True)
        return 0, 0  # Cannot proceed

    # Proceed with analysis using the provided embedding_function for calculations
    # and the retrieved collection object for DB operations.

    # Fetch entries using the retrieved collection object
    entries = fetch_recent_chat_entries(collection, status_filter, days_limit, limit)

    if not entries:
        logger.info("No matching entries found to analyze.")
        return 0, 0

    # Sort entries by confidence score if enabled
    if prioritize_by_confidence:
        # Sort entries by confidence_score in descending order (highest first)
        entries.sort(key=lambda entry: float(entry.get("metadata", {}).get("confidence_score", 0.0)), reverse=True)
        logger.info("Entries sorted by confidence score (highest first).")

    # 2. Process each entry
    for entry in entries:
        entry_id = entry.get("id")
        metadata = entry.get("metadata", {})
        timestamp_str = metadata.get("timestamp")
        involved_entities_str = metadata.get("involved_entities", "")
        response_summary = metadata.get("response_summary", "")
        prompt_summary = metadata.get("prompt_summary", "")  # Get prompt summary too

        # Get enhanced context fields if available
        code_context = metadata.get("code_context", "")
        diff_summary = metadata.get("diff_summary", "")
        tool_sequence = metadata.get("tool_sequence", "")
        confidence_score = metadata.get("confidence_score", 0.0)
        modification_type = metadata.get("modification_type", "unknown")
        related_code_chunks = metadata.get("related_code_chunks", "")

        if not all([entry_id, timestamp_str, involved_entities_str, response_summary]):
            logger.warning(f"Skipping entry {entry_id}: Missing required metadata.")
            continue

        logger.info(f"--- Processing Entry: {entry_id} ({timestamp_str}) ---")
        logger.info(f"  Confidence Score: {confidence_score}, Modification Type: {modification_type}")
        if tool_sequence:
            logger.info(f"  Tool Sequence: {tool_sequence}")

        correlated_this_entry = False  # Flag for correlation within this specific entry

        # Check if we have related code chunks via bidirectional links
        if related_code_chunks:
            code_chunk_ids = [chunk_id.strip() for chunk_id in related_code_chunks.split(",") if chunk_id.strip()]
            if code_chunk_ids:
                logger.info(f"  Found {len(code_chunk_ids)} related code chunks from bidirectional links")
                correlated_this_entry = True

        # Check if we already have code context and diff summary
        if code_context and diff_summary:
            logger.info("  Using existing code context and diff summary from enhanced context")
            # Directly use the captured diff summary for correlation
            summary = prompt_summary + " " + response_summary
            correlated_this_entry = True
        elif not correlated_this_entry:
            # Fall back to git diff analysis if no enhanced context available
            entities = [e.strip() for e in involved_entities_str.split(",")]

            # 3. Get Git diff for involved files
            resolved_repo_path = Path(repo_path).resolve()
            for entity_path in entities:
                if not entity_path:  # Skip empty strings resulting from split
                    continue

                # Construct absolute path RELATIVE TO REPO PATH
                try:
                    # Assume entity_path is relative to repo_root
                    file_path_abs = (resolved_repo_path / entity_path).resolve()
                except Exception as e:
                    logger.warning(f"Skipping entity '{entity_path}': Error constructing path: {e}")
                    continue

                # is_file check (using the constructed absolute path)
                if not file_path_abs.is_file():
                    # Log the entity path AND the absolute path for debugging
                    logger.debug(
                        f"Skipping entity '{entity_path}': Resolved path '{file_path_abs}' is not a valid file."
                    )
                    continue

                # If all checks pass, proceed to get diff
                logger.info(f"Checking Git history for file: {file_path_abs}")  # Log absolute path
                # Pass the resolved repo_path and the absolute file path string
                diff = get_git_diff_after_timestamp(resolved_repo_path, str(file_path_abs), timestamp_str)

                if diff:
                    logger.debug(f"Diff found for {entity_path}:\n{diff[:500]}...")  # Log snippet
                    # Use combined summary for correlation check
                    summary = prompt_summary + " " + response_summary
                    # 4. Correlate summary and diff
                    if embedding_function and correlate_summary_with_diff(summary, diff, embedding_function):
                        correlated_this_entry = True
                        logger.info(f"Correlation found for entity: {entity_path}")
                else:
                    logger.debug(f"No relevant diff found for {entity_path} after {timestamp_str}")

        # Analyze tool sequence patterns if available
        if tool_sequence and not correlated_this_entry:
            # If we have tool sequences that typically modify code, assume correlation
            if any(pattern in tool_sequence for pattern in ["edit_file", "reapply", "run_terminal_cmd", "delete_file"]):
                logger.info(f"Tool sequence indicates code modification: {tool_sequence}")
                correlated_this_entry = True

        # Increment total correlation count if this entry was correlated
        if correlated_this_entry:
            correlated_count += 1

        # 5. Update status (if processing was successful, regardless of correlation)
        if update_entry_status(client, collection_name, entry_id, new_status):
            processed_count += 1
            # Store info for printing later
            confidence_str = f" (confidence: {confidence_score})" if confidence_score else ""
            updated_entries_info.append((entry_id, metadata.get("prompt_summary", ""), confidence_score))
        else:
            logger.error(f"Failed to update status for {entry_id}. It might be reprocessed next time.")

        logger.info(f"--- Finished Processing Entry: {entry_id} ---")

    logger.info(
        f"Analysis complete. Processed {processed_count} entries. Found potential correlation in {correlated_count} entries."
    )

    # Print details of entries whose status was updated to 'analyzed'
    if updated_entries_info:
        logger.info("\n--- Entries updated to 'analyzed' ---")
        # Sort output by confidence score
        updated_entries_info.sort(key=lambda x: float(x[2]) if x[2] else 0.0, reverse=True)
        for entry_id, summary, confidence in updated_entries_info:
            confidence_str = f" (confidence: {confidence})" if confidence else ""
            logger.info(f"  ID: {entry_id}, Summary: {summary}{confidence_str}")
    else:
        logger.info("No entries were updated to 'analyzed' in this run.")

    return processed_count, correlated_count


# Example usage (if run directly, needs a mock client)
# if __name__ == "__main__":
#     class MockChromaClient: # Replace with actual client setup
#         def get(self, collection_name, where, include): # Simplified mock
#              print(f"Mock Get from {collection_name} with filter {where}")
#              return [] # Simulate no entries for direct run
#         def update(self, ids, metadatas): # Simplified mock
#              print(f"Mock Update IDs {ids} with metadatas {metadatas}")
#              return True

#     mock_client = MockChromaClient()
#     analyze_chat_history(mock_client)
