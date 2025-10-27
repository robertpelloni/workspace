"""
Evidence-based learning promotion module.

This module provides utilities to:
1. Evaluate validation evidence to determine promotion eligibility
2. Format and prepare validated code changes for promotion
3. Promote high-quality validated code changes to derived_learnings_v1
"""

import json
import uuid
import datetime
from typing import Dict, List, Optional, Any, Union

from .schemas import ValidationEvidence


class LearningPromoter:
    """
    Class for promoting validated code changes to derived learnings.
    """

    def __init__(self, chroma_client=None):
        """
        Initialize the learning promoter.

        Args:
            chroma_client: Optional ChromaDB client
        """
        self.chroma_client = chroma_client

    def get_validation_evidence(
        self, evidence_id: str, collection_name: str = "validation_evidence_v1"
    ) -> Optional[ValidationEvidence]:
        """
        Get validation evidence by ID.

        Args:
            evidence_id: ID of the validation evidence
            collection_name: Name of the validation evidence collection

        Returns:
            ValidationEvidence object or None if not found
        """
        # Import here to avoid circular imports
        from chroma_mcp.utils.chroma_client import get_chroma_client

        if self.chroma_client is None:
            self.chroma_client = get_chroma_client()

        try:
            collection = self.chroma_client.get_collection(name=collection_name)
            result = collection.get(ids=[evidence_id])

            if result and result["documents"]:
                # Parse JSON document into ValidationEvidence
                doc = result["documents"][0]
                return ValidationEvidence.model_validate_json(doc)

            return None
        except Exception as e:
            print(f"Error retrieving validation evidence: {str(e)}")
            return None

    def format_learning(
        self, evidence: ValidationEvidence, chat_id: Optional[str] = None, metadata: Optional[Dict[str, Any]] = None
    ) -> Dict[str, Any]:
        """
        Format validation evidence into a derived learning entry.

        Args:
            evidence: ValidationEvidence object
            chat_id: Optional chat ID related to the changes
            metadata: Optional additional metadata

        Returns:
            Dictionary with formatted learning data
        """
        # Prepare title based on evidence types
        evidence_types = [str(t).replace("ValidationEvidenceType.", "") for t in evidence.evidence_types]

        if "TEST_TRANSITION" in evidence_types:
            # Use the first test transition for the title
            test = evidence.test_transitions[0]
            title = f"Fixed failing test: {test.test_name}"
            description = (
                f"Fixed a failing test by addressing the issue: {test.error_message_before or 'Unknown error'}"
            )

            # Get the code changes
            file_changes = {}
            for test_evidence in evidence.test_transitions:
                file_changes.update(test_evidence.code_changes)

        elif "RUNTIME_ERROR_RESOLUTION" in evidence_types:
            # Use the first runtime error for the title
            error = evidence.runtime_errors[0]
            title = f"Fixed runtime error: {error.error_type}"
            description = f"Resolved runtime error: {error.error_message}"

            # Get the code changes
            file_changes = {}
            for error_evidence in evidence.runtime_errors:
                file_changes.update(error_evidence.code_changes)

        elif "CODE_QUALITY_IMPROVEMENT" in evidence_types:
            # Use the first code quality improvement for the title
            quality = evidence.code_quality_improvements[0]
            title = f"Code quality improvement: {quality.tool}"
            description = f"Improved code quality by fixing {quality.before_issues - quality.after_issues} issues"

            # Get the code changes
            file_changes = {}
            for quality_evidence in evidence.code_quality_improvements:
                file_changes.update(quality_evidence.code_changes)

        else:
            title = "Validated code change"
            description = "Code change validated through evidence"
            file_changes = {}

        # Format file changes for derived learning
        code_snippets = []
        for file_path, changes in file_changes.items():
            snippet = {
                "file": file_path,
                "code_before": changes.get("before", ""),
                "code_after": changes.get("after", ""),
                "language": file_path.split(".")[-1] if "." in file_path else "text",
            }
            code_snippets.append(snippet)

        # Prepare base learning data
        learning = {
            "title": title,
            "description": description,
            "code_snippets": code_snippets,
            "validation_score": evidence.score,
            "validation_evidence": evidence.model_dump(),
            "timestamp": datetime.datetime.now().isoformat(),
        }

        # Add chat ID if provided
        if chat_id:
            learning["chat_id"] = chat_id

        # Add additional metadata if provided
        if metadata:
            learning.update(metadata)

        return learning

    def promote_learning(
        self,
        evidence: ValidationEvidence,
        chat_id: Optional[str] = None,
        collection_name: str = "derived_learnings_v1",
        metadata: Optional[Dict[str, Any]] = None,
    ) -> Optional[str]:
        """
        Promote validated evidence to derived learnings.

        Args:
            evidence: ValidationEvidence object
            chat_id: Optional chat ID related to the changes
            collection_name: Name of the derived learnings collection
            metadata: Optional additional metadata

        Returns:
            ID of the promoted learning or None if promotion failed
        """
        # Check if evidence meets threshold
        if not evidence.meets_threshold():
            print(f"Validation evidence does not meet threshold (score: {evidence.score})")
            return None

        # Import here to avoid circular imports
        from chroma_mcp.utils.chroma_client import get_chroma_client

        if self.chroma_client is None:
            self.chroma_client = get_chroma_client()

        # Format learning
        learning = self.format_learning(evidence, chat_id, metadata)

        try:
            # Ensure collection exists
            try:
                collection = self.chroma_client.get_collection(name=collection_name)
            except Exception:
                collection = self.chroma_client.create_collection(name=collection_name)

            # Generate learning ID
            learning_id = str(uuid.uuid4())

            # Prepare document and metadata
            document = json.dumps(learning)

            # Prepare metadata for search and filtering
            meta = {
                "learning_id": learning_id,
                "title": learning["title"],
                "timestamp": learning["timestamp"],
                "validation_score": learning["validation_score"],
                "evidence_types": [str(t) for t in evidence.evidence_types],
            }

            # Add additional metadata fields
            if chat_id:
                meta["chat_id"] = chat_id

            if "code_snippets" in learning and learning["code_snippets"]:
                files = [snippet["file"] for snippet in learning["code_snippets"]]
                meta["files"] = files

            # Store in collection
            collection.add(documents=[document], metadatas=[meta], ids=[learning_id])

            return learning_id

        except Exception as e:
            print(f"Error promoting learning: {str(e)}")
            return None

    def promote_by_evidence_id(
        self,
        evidence_id: str,
        chat_id: Optional[str] = None,
        evidence_collection: str = "validation_evidence_v1",
        learning_collection: str = "derived_learnings_v1",
        metadata: Optional[Dict[str, Any]] = None,
    ) -> Optional[str]:
        """
        Promote a learning by validation evidence ID.

        Args:
            evidence_id: ID of the validation evidence
            chat_id: Optional chat ID related to the changes
            evidence_collection: Name of the validation evidence collection
            learning_collection: Name of the derived learnings collection
            metadata: Optional additional metadata

        Returns:
            ID of the promoted learning or None if promotion failed
        """
        # Get validation evidence
        evidence = self.get_validation_evidence(evidence_id, evidence_collection)

        if not evidence:
            print(f"Validation evidence not found: {evidence_id}")
            return None

        # Promote learning
        return self.promote_learning(evidence, chat_id, learning_collection, metadata)


def promote_validated_learning(
    evidence_id: str,
    chat_id: Optional[str] = None,
    evidence_collection: str = "validation_evidence_v1",
    learning_collection: str = "derived_learnings_v1",
    metadata: Optional[Dict[str, Any]] = None,
    chroma_client=None,
) -> Optional[str]:
    """
    Convenience function to promote a validated learning by evidence ID.

    Args:
        evidence_id: ID of the validation evidence
        chat_id: Optional chat ID related to the changes
        evidence_collection: Name of the validation evidence collection
        learning_collection: Name of the derived learnings collection
        metadata: Optional additional metadata
        chroma_client: Optional ChromaDB client

    Returns:
        ID of the promoted learning or None if promotion failed
    """
    promoter = LearningPromoter(chroma_client)
    return promoter.promote_by_evidence_id(evidence_id, chat_id, evidence_collection, learning_collection, metadata)
