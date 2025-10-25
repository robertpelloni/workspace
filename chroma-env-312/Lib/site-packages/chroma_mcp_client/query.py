"""
Provides query functionality for the ChromaDB client.
"""

import sys
import logging
import chromadb
from typing import Optional, List, Dict, Any

logger = logging.getLogger(__name__)

DEFAULT_CODEBASE_COLLECTION = "codebase_v1"
DEFAULT_QUERY_N_RESULTS = 5


def query_codebase(
    client: chromadb.ClientAPI,
    embedding_function: Optional[chromadb.EmbeddingFunction],
    query_texts: List[str],
    collection_name: str = DEFAULT_CODEBASE_COLLECTION,
    n_results: int = DEFAULT_QUERY_N_RESULTS,
) -> Optional[Dict[str, Any]]:
    """
    Performs a query against the specified codebase collection.

    Args:
        client: Initialized ChromaDB client.
        embedding_function: Embedding function used by the collection.
        query_texts: List of strings to query for.
        collection_name: Name of the codebase collection.
        n_results: Number of results to return per query text.

    Returns:
        The query results dictionary from ChromaDB, or None if an error occurs.
    """
    logger.info(
        f"Querying collection '{collection_name}' with {len(query_texts)} query texts (n_results={n_results})..."
    )
    try:
        collection = client.get_collection(name=collection_name, embedding_function=embedding_function)
        results = collection.query(
            query_texts=query_texts,
            n_results=n_results,
            include=["metadatas", "documents", "distances"],  # Include necessary fields
        )
        logger.debug(f"Query successful. Found results: {results is not None}")
        return results
    except ValueError as ve:
        if "Embedding function name mismatch" in str(ve):
            try:
                # Attempt to parse out the client and collection EF names from the error
                # Format: "Embedding function name mismatch: <client_ef_name> != <collection_ef_name>"
                mismatch_details = str(ve).split("Embedding function name mismatch: ")[1]
                client_ef_name, collection_ef_name = mismatch_details.split(" != ")

                error_message = (
                    f"Failed to query collection '{collection_name}'. Mismatch: Client is configured to use "
                    f"'{client_ef_name}' embedding function, but the collection was created with "
                    f"'{collection_ef_name}'. The collection may need to be re-indexed using the "
                    f"'{client_ef_name}' embedding model (often aliased as 'accurate')."
                )
                logger.error(error_message)
                # Provide a clear message to stdout/stderr as well, as this is a common operational issue
                print(f"ERROR: {error_message}", file=sys.stderr)

            except (IndexError, ValueError) as parse_error:  # Fallback if parsing the error string fails
                logger.error(
                    f"Failed to query collection '{collection_name}' due to an embedding function mismatch: {ve}. "
                    f"The collection may need to be re-indexed with the client's configured embedding model.",
                    exc_info=True,
                )
                print(
                    f"ERROR: Collection '{collection_name}' uses an incompatible embedding model. "
                    f"Please ensure it is indexed with the same embedding model the client is configured to use (e.g., 'accurate').",
                    file=sys.stderr,
                )
        else:
            # Handle other ValueErrors that are not EF mismatches
            logger.error(f"ValueError while querying collection '{collection_name}': {ve}", exc_info=True)
            print(
                f"Error: A configuration or data issue occurred while querying '{collection_name}'. Check logs for details.",
                file=sys.stderr,
            )
        return None
    except Exception as e:
        logger.error(f"Failed to query collection '{collection_name}': {e}", exc_info=True)
        # Keep the original print for other generic errors, but improve clarity
        print(
            f"Error querying collection '{collection_name}'. It might not exist or there's a server-side issue. Check logs.",
            file=sys.stderr,
        )
        return None
