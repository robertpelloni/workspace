"""
Utility functions for working with thinking sessions.
"""

from typing import Dict, List, Optional, Any

from chroma_mcp_client import ChromaMcpClient
from .thinking_session import ThinkingSession


def record_thought_chain(
    thoughts: List[str],
    session_id: Optional[str] = None,
    metadata: Optional[Dict[str, Any]] = None,
    client: Optional[ChromaMcpClient] = None,
) -> Dict[str, Any]:
    """
    Records a complete chain of thoughts in a single function call.

    Args:
        thoughts: List of thought strings to record in sequence
        session_id: Optional session ID. If not provided, a new session will be created
        metadata: Optional metadata dictionary to associate with the session
        client: Optional ChromaMcpClient instance. If not provided, a new one will be created

    Returns:
        Dictionary containing session information and summary
    """
    session = ThinkingSession(client=client, session_id=session_id)
    total_thoughts = len(thoughts)

    for idx, thought in enumerate(thoughts, 1):
        next_thought_needed = idx < total_thoughts
        session.record_thought(
            thought=thought, thought_number=idx, total_thoughts=total_thoughts, next_thought_needed=next_thought_needed
        )

    return {
        "session_id": session.session_id,
        "total_thoughts": total_thoughts,
        "metadata": metadata,
        "summary": session.get_session_summary(),
    }


def find_thoughts_across_sessions(
    query: str,
    n_results: int = 10,
    threshold: float = -1.0,
    include_branches: bool = True,
    session_id: Optional[str] = None,
    client: Optional[ChromaMcpClient] = None,
) -> List[Dict[str, Any]]:
    """
    Find thoughts similar to a query text across all thinking sessions.

    Args:
        query: Text to search for similar thoughts
        n_results: Maximum number of similar thoughts to return
        threshold: Similarity score threshold (0.0 to 1.0). Lower distance is more similar.
                  -1.0 to use default.
        include_branches: Whether to include thoughts from branches in the search
        session_id: Optional session ID to limit search to a specific session
        client: Optional ChromaMcpClient instance. If not provided, a new one will be created

    Returns:
        List of similar thoughts with metadata, across all sessions
    """
    client = client or ChromaMcpClient()
    response = client.mcp_chroma_dev_chroma_find_similar_thoughts(
        query=query, n_results=n_results, threshold=threshold, include_branches=include_branches, session_id=session_id
    )

    return response.get("similar_thoughts", [])


def create_thought_branch(
    parent_session_id: str,
    parent_thought_number: int,
    branch_thoughts: List[str],
    branch_id: Optional[str] = None,
    client: Optional[ChromaMcpClient] = None,
) -> Dict[str, Any]:
    """
    Creates a branch from an existing thought in a parent session.

    Args:
        parent_session_id: Session ID of the parent thought
        parent_thought_number: Thought number to branch from
        branch_thoughts: List of thought strings for the branch
        branch_id: Optional branch identifier. If not provided, a random ID will be used
        client: Optional ChromaMcpClient instance. If not provided, a new one will be created

    Returns:
        Dictionary containing session and branch information
    """
    if parent_thought_number < 1:
        raise ValueError("Parent thought number must be at least 1")

    session = ThinkingSession(client=client, session_id=parent_session_id)
    total_thoughts = len(branch_thoughts)

    for idx, thought in enumerate(branch_thoughts, 1):
        next_thought_needed = idx < total_thoughts
        branch_from = parent_thought_number if idx == 1 else 0

        session.record_thought(
            thought=thought,
            thought_number=idx,
            total_thoughts=total_thoughts,
            branch_id=branch_id or "",
            branch_from_thought=branch_from,
            next_thought_needed=next_thought_needed,
        )

    return {
        "session_id": session.session_id,
        "branch_id": branch_id,
        "parent_thought": parent_thought_number,
        "total_branch_thoughts": total_thoughts,
        "summary": session.get_session_summary(include_branches=True),
    }
