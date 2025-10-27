"""
Module for managing derived learnings, including promoting chat entries or manual insights
into the derived_learnings_v1 collection.
"""

import sys
import logging
import uuid
import time
import chromadb
from typing import Optional, Dict, Any, List, Union
import json

logger = logging.getLogger(__name__)


def fetch_source_chat_context(
    client: chromadb.ClientAPI,
    source_chat_id: str,
    chat_history_collection_name: str = "chat_history_v1",
) -> Dict[str, Any]:
    """
    Fetches rich context data from a source chat entry.

    Args:
        client: Initialized ChromaDB client.
        source_chat_id: ID of the source entry in the chat history collection.
        chat_history_collection_name: Name of the chat history collection.

    Returns:
        Dictionary containing rich context data from the source chat entry.
    """
    context_data = {
        "code_context": "",
        "diff_summary": "",
        "tool_sequence": "",
        "confidence_score": 0.0,
        "modification_type": "unknown",
        "related_code_chunks": "",
        "prompt_summary": "",
        "response_summary": "",
    }

    try:
        chat_collection = client.get_collection(name=chat_history_collection_name)
        results = chat_collection.get(ids=[source_chat_id], include=["metadatas", "documents"])

        if not results or not results["ids"] or results["ids"][0] != source_chat_id:
            logger.warning(f"Source chat ID {source_chat_id} not found when fetching context.")
            return context_data

        metadata = results["metadatas"][0] if results.get("metadatas") else {}
        if not metadata:
            logger.warning(f"No metadata found for source chat ID {source_chat_id}.")
            return context_data

        # Extract available context fields
        for field in context_data.keys():
            if field in metadata and metadata[field] is not None:
                context_data[field] = metadata[field]

        # Add prompt and response summaries
        context_data["prompt_summary"] = metadata.get("prompt_summary", "")
        context_data["response_summary"] = metadata.get("response_summary", "")

        logger.info(f"Successfully fetched context data for chat ID {source_chat_id}.")

    except Exception as e:
        logger.error(f"Error fetching context for source chat ID {source_chat_id}: {e}", exc_info=True)

    return context_data


def promote_to_learnings_collection(
    client: chromadb.ClientAPI,
    embedding_function: Optional[chromadb.EmbeddingFunction],
    description: str,
    pattern: str,
    code_ref: str,
    tags: str,
    confidence: float,
    learnings_collection_name: str = "derived_learnings_v1",
    source_chat_id: Optional[str] = None,
    chat_history_collection_name: str = "chat_history_v1",
    include_chat_context: bool = True,
    validation_evidence_id: Optional[str] = None,
    validation_score: Optional[float] = None,
) -> Optional[str]:
    """
    Promote an analyzed chat insight or manual finding to derived learnings.

    Args:
        client: ChromaDB client instance
        embedding_function: EF to use for the derived learning
        description: Natural language description of the learning
        pattern: Core pattern identified (code, regex, etc.)
        code_ref: Code reference (e.g., chunk_id from codebase_v1)
        tags: Comma-separated tags for categorization
        confidence: Confidence score for this learning (0.0 to 1.0)
        learnings_collection_name: Collection to add learning to
        source_chat_id: Optional ID of source entry in chat history
        chat_history_collection_name: Chat collection name
        include_chat_context: Include chat context in learning
        validation_evidence_id: Optional ID of validation evidence
        validation_score: Optional validation score (0.0 to 1.0)

    Returns:
        ID of the promoted learning if successful, else None
    """
    try:
        # Generate a unique ID for this learning
        learning_id = str(uuid.uuid4())

        # Prepare the base metadata
        metadata = {
            "tags": tags,
            "confidence": confidence,
            "code_ref": code_ref,
            "promotion_type": "manual" if not source_chat_id else "from_chat",
        }

        # Check if there's validation evidence to include
        if validation_evidence_id or validation_score is not None:
            metadata["validation"] = {}

            # Add validation score if provided directly
            if validation_score is not None:
                metadata["validation"]["score"] = validation_score

            # Add evidence ID if available
            if validation_evidence_id:
                metadata["validation"]["evidence_id"] = validation_evidence_id

                # Attempt to retrieve validation evidence if ID provided
                try:
                    from chroma_mcp_client.validation.promotion import LearningPromoter

                    promoter = LearningPromoter(client)
                    evidence = promoter.get_validation_evidence(validation_evidence_id)

                    if evidence:
                        # Use the evidence score if direct score not provided
                        if validation_score is None:
                            metadata["validation"]["score"] = evidence.score

                        # Add evidence types
                        metadata["validation"]["evidence_types"] = [et.value for et in evidence.evidence_types]

                        # Set meets_threshold flag
                        metadata["validation"]["meets_threshold"] = evidence.meets_threshold()

                        # Add evidence counts
                        evidence_counts = {}
                        if evidence.test_transitions:
                            evidence_counts["test_transitions"] = len(evidence.test_transitions)
                        if evidence.runtime_errors:
                            evidence_counts["runtime_errors"] = len(evidence.runtime_errors)
                        if evidence.code_quality_improvements:
                            evidence_counts["code_quality"] = len(evidence.code_quality_improvements)
                        metadata["validation"]["evidence_counts"] = evidence_counts
                except Exception as e:
                    logger.warning(f"Failed to retrieve validation evidence {validation_evidence_id}: {str(e)}")

        # Bidirectional linking setup
        if source_chat_id:
            metadata["source_chat_id"] = source_chat_id

            # Attempt to get rich context from the source chat entry
            if include_chat_context:
                try:
                    chat_collection = client.get_collection(name=chat_history_collection_name)
                    result = chat_collection.get(ids=[source_chat_id], include=["metadatas", "documents"])

                    if result and result["metadatas"] and len(result["metadatas"]) > 0:
                        chat_metadata = result["metadatas"][0]

                        # Extract code context if available
                        if "code_context" in chat_metadata:
                            metadata["code_context"] = chat_metadata["code_context"]

                        # Extract confidence score details if available
                        if "confidence_score" in chat_metadata:
                            metadata["source_confidence"] = chat_metadata["confidence_score"]

                        # Extract diff summary if available
                        if "diff_summary" in chat_metadata:
                            metadata["diff_summary"] = chat_metadata["diff_summary"]

                        # Extract code changes if available (simplified version)
                        if "code_changes" in chat_metadata:
                            metadata["code_changes"] = chat_metadata["code_changes"]

                        # Extract modification type if available
                        if "modification_type" in chat_metadata:
                            metadata["modification_type"] = chat_metadata["modification_type"]

                        # Extract tool sequence if available
                        if "tool_sequence" in chat_metadata:
                            metadata["tool_sequence"] = chat_metadata["tool_sequence"]
                except Exception as e:
                    logger.warning(f"Failed to extract context from source chat entry: {e}")

        # Get or create the derived learnings collection
        learnings_collection = client.get_or_create_collection(
            name=learnings_collection_name, embedding_function=embedding_function
        )

        # Add the learning to the collection
        learnings_collection.add(
            ids=[learning_id],
            documents=[description],
            metadatas=[metadata],
        )

        logger.info(f"Added derived learning with ID {learning_id}")

        # Update the source chat entry status if provided
        if source_chat_id:
            try:
                chat_collection = client.get_collection(name=chat_history_collection_name)
                result = chat_collection.get(ids=[source_chat_id], include=["metadatas"])

                if result and result["metadatas"] and len(result["metadatas"]) > 0:
                    chat_metadata = result["metadatas"][0]
                    chat_metadata["status"] = "promoted"
                    chat_metadata["derived_learning_id"] = learning_id

                    # Update the metadata
                    chat_collection.update(ids=[source_chat_id], metadatas=[chat_metadata])

                    logger.info(f"Updated source chat entry {source_chat_id} status to 'promoted'")
                else:
                    logger.warning(f"Source chat entry {source_chat_id} not found")
            except Exception as e:
                logger.warning(f"Failed to update source chat entry status: {e}")

        # Success! Print a nice message
        print(f"Promoted to derived learning with ID: {learning_id}")
        print(f"Description: {description}")
        print(f"Tags: {tags}")
        print(f"Confidence: {confidence}")

        # Print validation info if available
        if validation_evidence_id or validation_score is not None:
            if validation_score is not None:
                print(f"Validation Score: {validation_score:.2f}")
            if validation_evidence_id:
                print(f"Validation Evidence ID: {validation_evidence_id}")

            # Print if it meets threshold
            if "validation" in metadata and "meets_threshold" in metadata["validation"]:
                print(f"Meets Promotion Threshold: {metadata['validation']['meets_threshold']}")

        return learning_id

    except Exception as e:
        logger.error(f"Failed to promote to derived learning: {e}", exc_info=True)
        print(f"Error: Failed to promote to derived learning: {e}")
        return None
