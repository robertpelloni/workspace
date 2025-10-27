"""
Module for interactively reviewing and promoting chat history entries to derived learnings.
"""

import logging
import sys
import os
from typing import Optional, List, Dict, Any, Tuple
from pathlib import Path
from enum import Enum

# Add project root for imports
project_root = Path(__file__).resolve().parent.parent.parent
sys.path.insert(0, str(project_root))

# Assuming connection and analysis functions are importable
from chroma_mcp_client.connection import (
    get_client_and_ef,
    get_chroma_client,
    get_embedding_function,
)
from chroma_mcp_client.analysis import fetch_recent_chat_entries, update_entry_status

# Import the refactored promotion function
from chroma_mcp_client.learnings import promote_to_learnings_collection

# Import the new query function
from chroma_mcp_client.query import query_codebase, DEFAULT_CODEBASE_COLLECTION

logger = logging.getLogger(__name__)


class ModificationTypeFilter(Enum):
    """Enum for filtering entries by modification type"""

    ALL = "all"
    REFACTOR = "refactor"
    BUGFIX = "bugfix"
    FEATURE = "feature"
    DOCUMENTATION = "documentation"
    OPTIMIZATION = "optimization"
    TEST = "test"
    CONFIG = "config"
    STYLE = "style"
    UNKNOWN = "unknown"


def display_code_results(results: Dict[str, Any]):
    """Helper function to display codebase query results."""
    if not results or not results.get("ids") or not results["ids"][0]:
        print("No relevant code snippets found.")
        return []

    ids = results["ids"][0]
    documents = results["documents"][0]
    metadatas = results["metadatas"][0]
    distances = results["distances"][0]

    print("\nSuggested Code References:")
    valid_choices = []
    for i, doc_id in enumerate(ids):
        metadata = metadatas[i] if metadatas else {}
        file_path = metadata.get("relative_file_path", "N/A")
        document = documents[i] if documents else ""
        distance = distances[i] if distances else float("inf")
        snippet = document.splitlines()[0] if document else "(No snippet)"  # Just first line
        print(f"  {i+1}. ID: {doc_id}")
        print(f"     File: {file_path}")
        print(f"     Dist: {distance:.4f}")
        print(f"     Snippet: {snippet[:100]}{'...' if len(snippet)>100 else ''}")
        valid_choices.append(doc_id)
    print("  N. None of the above / Not applicable")
    return valid_choices


def display_rich_context(metadata: Dict[str, Any]) -> None:
    """
    Display rich context information from metadata in a user-friendly format.

    Args:
        metadata: Metadata dictionary from chat entry
    """
    print("\n--- Rich Context Information ---")

    # Display confidence score with color if available
    confidence_score = metadata.get("confidence_score")
    if confidence_score is not None:
        try:
            score = float(confidence_score)
            # Color codes for terminal
            GREEN = "\033[92m" if os.isatty(sys.stdout.fileno()) else ""
            YELLOW = "\033[93m" if os.isatty(sys.stdout.fileno()) else ""
            RED = "\033[91m" if os.isatty(sys.stdout.fileno()) else ""
            RESET = "\033[0m" if os.isatty(sys.stdout.fileno()) else ""

            if score >= 0.8:
                color = GREEN
            elif score >= 0.5:
                color = YELLOW
            else:
                color = RED

            print(f"Confidence Score: {color}{score}{RESET}")
        except (ValueError, TypeError):
            print(f"Confidence Score: {confidence_score}")

    # Display modification type
    modification_type = metadata.get("modification_type")
    if modification_type:
        print(f"Modification Type: {modification_type}")

    # Display tool sequence with pattern highlighting
    tool_sequence = metadata.get("tool_sequence")
    if tool_sequence:
        print(f"Tool Sequence: {tool_sequence}")

        # Highlight common patterns
        if "edit_file→reapply" in tool_sequence:
            print("  - Pattern: Iterative refinement (multiple edit attempts)")
        if "read_file→read_file→read_file" in tool_sequence:
            print("  - Pattern: Deep research (multiple files read)")
        if "codebase_search→read_file→edit_file" in tool_sequence:
            print("  - Pattern: Search and modify")

    # Display linked code chunks
    related_code_chunks = metadata.get("related_code_chunks")
    if related_code_chunks:
        chunks = [c.strip() for c in related_code_chunks.split(",") if c.strip()]
        if chunks:
            print(f"Related Code Chunks: {len(chunks)}")
            for i, chunk_id in enumerate(chunks[:3]):  # Show max 3 chunks
                print(f"  {i+1}. {chunk_id}")
            if len(chunks) > 3:
                print(f"  ... and {len(chunks) - 3} more")

    # Display diff summary in a compact form
    diff_summary = metadata.get("diff_summary")
    if diff_summary:
        print("\nDiff Summary:")
        # Split by lines and show first few lines
        lines = diff_summary.split("\n")
        for line in lines[:5]:  # Show max 5 lines of diff summary
            print(f"  {line}")
        if len(lines) > 5:
            print(f"  ... and {len(lines) - 5} more lines")

    # Show a snippet of code context if available
    code_context = metadata.get("code_context")
    if code_context:
        print("\nCode Context Available: Yes (use 'v' to view full context)")

    print("----------------------------")


def view_full_code_context(metadata: Dict[str, Any]) -> None:
    """
    Display the full code context from metadata.

    Args:
        metadata: Metadata dictionary from chat entry
    """
    code_context = metadata.get("code_context")
    if not code_context:
        print("No detailed code context available.")
        return

    print("\n" + "=" * 60)
    print("FULL CODE CONTEXT")
    print("=" * 60)
    print(code_context)
    print("=" * 60)
    input("Press Enter to continue...")  # Pause to let user read


def calculate_context_richness(metadata: Dict[str, Any]) -> float:
    """
    Calculate a 'richness' score for the entry's context.

    Args:
        metadata: Metadata dictionary from chat entry

    Returns:
        Float indicating the richness (0.0 to 1.0)
    """
    # Start with base score
    richness = 0.0

    # Check for key context fields
    context_fields = [
        "code_context",
        "diff_summary",
        "tool_sequence",
        "related_code_chunks",
        "confidence_score",
        "modification_type",
    ]

    # Award points for each available field
    for field in context_fields:
        if field in metadata and metadata[field]:
            richness += 1 / len(context_fields)

    return min(richness, 1.0)  # Cap at 1.0


def run_interactive_promotion(
    days_limit: int = 7,
    fetch_limit: int = 50,
    chat_collection_name: str = "chat_history_v1",
    learnings_collection_name: str = "derived_learnings_v1",
    modification_type_filter: str = ModificationTypeFilter.ALL.value,
    min_confidence: float = 0.0,
    sort_by_confidence: bool = True,
):
    """
    Runs the interactive workflow to review and promote chat entries.

    Args:
        days_limit: How many days back to look for entries
        fetch_limit: Maximum number of entries to fetch
        chat_collection_name: Name of chat history collection
        learnings_collection_name: Name of derived learnings collection
        modification_type_filter: Filter by modification type (refactor, bugfix, etc.)
        min_confidence: Minimum confidence score to include (0.0-1.0)
        sort_by_confidence: Whether to sort entries by confidence score
    """
    logger.info("Starting interactive promotion workflow...")

    try:
        # Initialize client and EF
        logger.debug("Initializing Chroma connection for interactive promoter...")
        client, ef = get_client_and_ef()
        if not client or not ef:
            logger.error("Failed to initialize Chroma connection.")
            return

        chat_collection = client.get_collection(name=chat_collection_name)

        # 1. Fetch entries with status 'analyzed'
        logger.info(
            f"Fetching entries with status 'analyzed' from '{chat_collection_name}' (last {days_limit} days)..."
        )
        analyzed_entries: List[Dict[str, Any]] = fetch_recent_chat_entries(
            collection=chat_collection, status_filter="analyzed", days_limit=days_limit, fetch_limit=fetch_limit
        )

        if not analyzed_entries:
            print("No entries with status 'analyzed' found within the specified time limit.")
            logger.info("No analyzed entries found.")
            return

        # Filter and sort entries
        filtered_entries = []

        for entry in analyzed_entries:
            metadata = entry.get("metadata", {})
            entry_modification_type = metadata.get("modification_type", ModificationTypeFilter.UNKNOWN.value)
            entry_confidence = 0.0

            try:
                confidence_str = metadata.get("confidence_score", "0.0")
                entry_confidence = float(confidence_str) if confidence_str else 0.0
            except (ValueError, TypeError):
                entry_confidence = 0.0

            # Apply filters
            if (
                modification_type_filter == ModificationTypeFilter.ALL.value
                or entry_modification_type == modification_type_filter
            ):
                if entry_confidence >= min_confidence:
                    # Calculate context richness score
                    context_richness = calculate_context_richness(metadata)
                    entry["_context_richness"] = context_richness  # Store for sorting
                    entry["_confidence_score"] = entry_confidence  # Store for sorting
                    filtered_entries.append(entry)

        # Sort entries
        if sort_by_confidence:
            filtered_entries.sort(key=lambda e: (e["_confidence_score"], e["_context_richness"]), reverse=True)
            logger.info("Entries sorted by confidence score (highest first).")

        print(f"Found {len(filtered_entries)} entries to review after filtering.")
        if len(filtered_entries) == 0:
            return

        # Ask if user wants to enable auto-promote mode for high confidence entries
        auto_promote_high_confidence = False
        auto_promote_threshold = 0.8
        auto_promote_response = input("\nEnable auto-promote mode for high confidence entries (≥0.8)? (y/N): ").lower()
        if auto_promote_response == "y":
            auto_promote_high_confidence = True
            print(f"Auto-promote mode enabled for entries with confidence ≥{auto_promote_threshold}")
            # Allow customizing the threshold
            threshold_input = input(f"Change auto-promote threshold (default: {auto_promote_threshold}): ")
            if threshold_input:
                try:
                    custom_threshold = float(threshold_input)
                    if 0.0 <= custom_threshold <= 1.0:
                        auto_promote_threshold = custom_threshold
                        print(f"Auto-promote threshold set to {auto_promote_threshold}")
                    else:
                        print(f"Invalid threshold value. Using default: {auto_promote_threshold}")
                except ValueError:
                    print(f"Invalid threshold value. Using default: {auto_promote_threshold}")

        # 2. Loop through entries
        promoted_count = 0
        ignored_count = 0
        skipped_count = 0
        auto_promoted_count = 0

        for i, entry in enumerate(filtered_entries):
            entry_id = entry.get("id")
            metadata = entry.get("metadata", {})
            timestamp = metadata.get("timestamp", "N/A")
            prompt_summary = metadata.get("prompt_summary", "N/A")
            response_summary = metadata.get("response_summary", "N/A")
            involved_entities = metadata.get("involved_entities", "N/A")
            confidence_score = metadata.get("confidence_score", "N/A")
            modification_type = metadata.get("modification_type", "unknown")

            # Calculate richness score
            richness = entry.get("_context_richness", 0.0)
            richness_indicator = "*" * int(richness * 5)  # Visual indicator (0-5 stars)

            print("\n" + "=" * 50)
            print(f"Reviewing Entry {i+1}/{len(filtered_entries)} | Context Richness: {richness_indicator}")
            print(f"  ID: {entry_id}")
            print(f"  Timestamp: {timestamp}")
            print(f"  Confidence: {confidence_score}, Type: {modification_type}")
            print(f"  Prompt Summary: {prompt_summary}")
            print(f"  Response Summary: {response_summary}")
            print(f"  Involved Entities: {involved_entities}")
            print("=" * 50)

            # Show rich context information if available
            display_rich_context(metadata)

            # Check if auto-promote should be applied for this entry
            entry_confidence = entry.get("_confidence_score", 0.0)
            if auto_promote_high_confidence and entry_confidence >= auto_promote_threshold:
                print(f"\n🔄 Auto-promoting entry with confidence score {entry_confidence} ≥ {auto_promote_threshold}")
                action = "auto-p"  # Special action code for auto-promotion
            else:
                # Command loop
                while True:
                    action = input("\nAction (p=promote, i=ignore, s=skip, v=view context, q=quit): ").lower()
                    if action == "v":
                        view_full_code_context(metadata)
                        continue
                    if action in ["p", "i", "s", "q"]:
                        break
                    print("Invalid action. Please enter p, i, s, v, or q.")

            if action == "q":
                print("Quitting review process.")
                break
            elif action == "s":
                print(f"Skipping entry {entry_id}.")
                skipped_count += 1
                continue
            elif action == "i":
                print(f"Marking entry {entry_id} as ignored...")
                # Update status to 'ignored' (or similar)
                if update_entry_status(client, chat_collection_name, entry_id, new_status="ignored"):
                    print("Status updated to 'ignored'.")
                    ignored_count += 1
                else:
                    print(f"Warning: Failed to update status for {entry_id}.")
                continue  # Move to next entry
            elif action in ["p", "auto-p"]:
                if action == "auto-p":
                    print(f"Auto-promoting entry {entry_id}...")
                else:
                    print(f"Starting promotion process for entry {entry_id}...")

                # --- Gather Promotion Details ---
                if action != "auto-p":
                    print("\nPlease provide the following details for the new learning entry:")

                # Generate better defaults based on context
                confidence_float = 0.8
                try:
                    confidence_float = float(metadata.get("confidence_score", "0.8"))
                except (ValueError, TypeError):
                    pass

                # Add a warning for low confidence scores
                if confidence_float < 0.5 and action != "auto-p":
                    print("\n⚠️  LOW CONFIDENCE SCORE DETECTED ⚠️")
                    print("This entry has a low confidence score. Consider reviewing it carefully before promoting.")
                    print("Press Enter to use the suggested defaults, or provide your own values.")

                # Default description with improved context
                if metadata.get("diff_summary"):
                    default_description = f"{prompt_summary}\n{response_summary}\n\nKey changes: {metadata.get('diff_summary', '')[:200]}..."
                else:
                    default_description = f"Prompt: {prompt_summary}\nResponse: {response_summary}"

                if action == "auto-p":
                    description = default_description
                else:
                    description = input(f"Description (default: use auto-generated): ")
                    if not description:
                        description = default_description
                        print("Using auto-generated description.")

                # Generate smart pattern default based on modification type and content
                default_pattern = ""
                if modification_type == "feature":
                    default_pattern = f"Implementation pattern for {prompt_summary.split()[0:5]}"
                elif modification_type == "bugfix":
                    default_pattern = f"Bug fix pattern for {prompt_summary.split()[0:5]}"
                elif modification_type == "refactor":
                    default_pattern = f"Refactoring pattern for {prompt_summary.split()[0:5]}"
                elif modification_type == "documentation":
                    default_pattern = f"Documentation pattern for {prompt_summary.split()[0:5]}"
                else:
                    # Extract key terms from prompt/response for a generic pattern
                    content_terms = set(prompt_summary.split() + response_summary.split())
                    # Filter for longer, more meaningful terms (likely not stopwords)
                    meaningful_terms = [term for term in content_terms if len(term) > 5 and "." not in term][:3]
                    if meaningful_terms:
                        default_pattern = f"Pattern for {' '.join(meaningful_terms)}"
                    else:
                        default_pattern = "General implementation pattern"

                # Truncate default pattern if too long
                if len(default_pattern) > 80:
                    default_pattern = default_pattern[:77] + "..."

                if action == "auto-p":
                    pattern = default_pattern
                    print(f"Auto-using pattern: {pattern}")
                else:
                    pattern = input(f"Pattern (default: {default_pattern}): ")
                    if not pattern:
                        pattern = default_pattern
                        print(f"Using default pattern: {default_pattern}")

                # Get code_ref from user selection or manual input
                default_code_ref = ""
                default_code_ref_index = 0

                # First try to use related code chunks
                related_code_chunks = metadata.get("related_code_chunks", "")
                code_chunks = [c.strip() for c in related_code_chunks.split(",") if c.strip()]
                suggested_ids = []

                if code_chunks:
                    if action != "auto-p":
                        print(f"\nUsing {len(code_chunks)} related code chunks from bidirectional links:")
                        for i, chunk_id in enumerate(code_chunks):
                            print(f"  {i+1}. {chunk_id}")
                    suggested_ids = code_chunks
                    default_code_ref = code_chunks[0] if code_chunks else ""
                    if action != "auto-p":
                        print(f"Default selection: 1. {default_code_ref}")
                else:
                    # --- Suggest Code Refs ---
                    if action != "auto-p":
                        print("\nSearching codebase for relevant snippets...")
                    query_text = f"{prompt_summary}\n{response_summary}"
                    code_results = query_codebase(
                        client=client,
                        embedding_function=ef,
                        query_texts=[query_text],
                        collection_name=DEFAULT_CODEBASE_COLLECTION,
                        n_results=5,
                    )

                    if action != "auto-p":
                        suggested_ids = display_code_results(code_results)
                    elif code_results and code_results.get("ids") and code_results["ids"][0]:
                        suggested_ids = code_results["ids"][0]

                    # Select the best match by closest distance
                    if code_results and code_results.get("ids") and code_results["ids"][0]:
                        default_code_ref = code_results["ids"][0][0]
                        # Find its index in the display list (1-based)
                        default_code_ref_index = 1
                        if action != "auto-p":
                            print(f"Default selection: {default_code_ref_index}. {default_code_ref}")

                if action == "auto-p":
                    code_ref = default_code_ref if default_code_ref else "N/A"
                    print(f"Auto-selecting code reference: {code_ref}")
                else:
                    code_ref_display = (
                        f"Code Reference (default: {default_code_ref_index if default_code_ref_index else 'N/A'}, "
                    )
                    code_ref_display += f"select 1-{len(suggested_ids)}, manual, or 'n' for N/A): "

                    code_ref_input = input(code_ref_display).lower()
                    if not code_ref_input:
                        if default_code_ref:
                            code_ref = default_code_ref
                            print(f"Using default: {code_ref}")
                        else:
                            code_ref = "N/A"
                            print("No default available, using 'N/A'.")
                    elif code_ref_input == "n":
                        code_ref = "N/A"
                    else:
                        try:
                            choice_index = int(code_ref_input) - 1
                            if 0 <= choice_index < len(suggested_ids):
                                code_ref = suggested_ids[choice_index]
                                print(f"Selected: {code_ref}")
                            else:
                                print(f"Invalid selection. Using default.")
                                code_ref = default_code_ref if default_code_ref else "N/A"
                        except ValueError:
                            # Assume manual input if not 'n' and not a valid number
                            code_ref = code_ref_input
                            print(f"Using manual input: {code_ref}")

                # Suggest tags based on modification type and entities
                suggested_tags = []
                if modification_type and modification_type != "unknown":
                    suggested_tags.append(modification_type)
                if involved_entities:
                    entities = involved_entities.split(",")
                    for entity in entities:
                        entity = entity.strip()
                        if entity and "." in entity:
                            extension = entity.split(".")[-1]
                            if extension in ["py", "js", "ts", "rs", "go", "java", "c", "cpp", "html", "css"]:
                                suggested_tags.append(extension)

                # Deduplicate tags
                suggested_tags = list(dict.fromkeys(suggested_tags))
                default_tags = ",".join(suggested_tags) if suggested_tags else "general"

                if action == "auto-p":
                    tags = default_tags
                    print(f"Auto-using tags: {tags}")
                else:
                    tags_input = input(f"Tags (default: {default_tags}): ")
                    tags = tags_input if tags_input else default_tags

                # Use source confidence as default if available
                default_confidence = metadata.get("confidence_score", "0.8")
                try:
                    default_conf_float = float(default_confidence)
                    if not (0.0 <= default_conf_float <= 1.0):
                        default_confidence = "0.8"  # Fallback to 0.8 if out of range
                except (ValueError, TypeError):
                    default_confidence = "0.8"  # Fallback to 0.8 if not a valid float

                if action == "auto-p":
                    confidence_str = default_confidence
                    confidence = float(confidence_str)
                    print(f"Auto-using confidence: {confidence_str}")
                else:
                    confidence_str = input(f"Confidence (default: {default_confidence}): ")
                    if not confidence_str:
                        confidence_str = default_confidence
                        print(f"Using default confidence: {default_confidence}")

                    try:
                        confidence = float(confidence_str)
                        if not (0.0 <= confidence <= 1.0):
                            print(f"Warning: Confidence {confidence} is outside the range 0.0-1.0. Proceeding anyway.")
                    except ValueError:
                        print(f"Invalid confidence value. Using default: {default_confidence}")
                        confidence = float(default_confidence)

                # For auto-promote, always include rich context
                if action == "auto-p":
                    include_context = True
                    print("Auto-including rich context from source chat.")
                else:
                    # Ask if the user wants to include rich context (default yes)
                    context_prompt = (
                        "Include rich context from source chat? (Y/n): "
                        if confidence_float >= 0.5
                        else "Include rich context from source chat? (recommended for low confidence) (Y/n): "
                    )
                    include_context = input(context_prompt).lower() != "n"

                # Call the refactored promotion function
                new_learning_id = promote_to_learnings_collection(
                    client=client,
                    embedding_function=ef,
                    description=description,
                    pattern=pattern,
                    code_ref=code_ref,
                    tags=tags,
                    confidence=confidence,
                    learnings_collection_name=learnings_collection_name,
                    source_chat_id=entry_id,
                    chat_history_collection_name=chat_collection_name,
                    include_chat_context=include_context,
                )

                if new_learning_id:
                    if action == "auto-p":
                        print(f"Successfully auto-promoted entry {entry_id} to learning {new_learning_id}.")
                        auto_promoted_count += 1
                    else:
                        print(f"Successfully promoted entry {entry_id} to learning {new_learning_id}.")
                        promoted_count += 1
                else:
                    print(f"Failed to promote entry {entry_id}. Please check logs.")
                    skipped_count += 1

        # 3. Summary
        print("\n" + "=" * 50)
        print("Review Complete")
        print(f"  Entries Reviewed: {len(filtered_entries)}")
        print(f"  Promoted: {promoted_count}")
        if auto_promoted_count > 0:
            print(f"  Auto-Promoted: {auto_promoted_count}")
        print(f"  Ignored: {ignored_count}")
        print(f"  Skipped: {skipped_count}")
        print("=" * 50)

    except Exception as e:
        logger.error(f"Interactive promotion workflow failed: {e}", exc_info=True)
        print(f"An error occurred: {e}")
    finally:
        logger.info("Interactive promotion workflow finished.")


# Example placeholder for how it might be called (not used directly by CLI)
# if __name__ == '__main__':
#     run_interactive_promotion()
