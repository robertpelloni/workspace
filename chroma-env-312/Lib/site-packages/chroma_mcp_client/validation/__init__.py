"""
Validation package for error-driven learning in the Chroma MCP client.

This package provides tools for:
1. Collecting validation evidence (test transitions, runtime errors, code quality)
2. Scoring potential learnings based on evidence
3. Promoting only high-value, validated learnings to derived_learnings_v1
"""

from .schemas import (
    ValidationEvidenceType,
    TestTransitionEvidence,
    RuntimeErrorEvidence,
    CodeQualityEvidence,
    ValidationEvidence,
    calculate_validation_score,
)

__all__ = [
    "ValidationEvidenceType",
    "TestTransitionEvidence",
    "RuntimeErrorEvidence",
    "CodeQualityEvidence",
    "ValidationEvidence",
    "calculate_validation_score",
]
