"""
Code quality metrics collection and processing for validation evidence.

This module provides tools to:
1. Parse linter and quality tool outputs
2. Compare before/after quality metrics
3. Generate quality improvement evidence for validation scoring
"""

import os
import re
import uuid
import json
import datetime
import subprocess
from typing import Dict, List, Optional, Any, Tuple

from .schemas import CodeQualityEvidence


def parse_ruff_output(output: str) -> Dict[str, List[Dict[str, Any]]]:
    """
    Parse output from the Ruff linter.

    Args:
        output: Ruff output string

    Returns:
        Dictionary mapping file paths to lists of issues
    """
    issues = {}

    # Regular expression to match ruff output lines
    # Example: file.py:10:5: E123 Error description
    pattern = re.compile(r"^(.+?):(\d+):(\d+): ([A-Z]\d+) (.+)$")

    for line in output.split("\n"):
        match = pattern.match(line.strip())
        if match:
            file_path = match.group(1)
            line_num = int(match.group(2))
            col_num = int(match.group(3))
            code = match.group(4)
            description = match.group(5)

            if file_path not in issues:
                issues[file_path] = []

            issues[file_path].append({"line": line_num, "column": col_num, "code": code, "description": description})

    return issues


def parse_pylint_output(output: str) -> Dict[str, List[Dict[str, Any]]]:
    """
    Parse output from Pylint.

    Args:
        output: Pylint output string

    Returns:
        Dictionary mapping file paths to lists of issues
    """
    issues = {}

    # Regular expression to match pylint output lines
    # Example: file.py:10:5: C0103: Variable name "x" doesn't conform to snake_case naming style (invalid-name)
    pattern = re.compile(r"^(.+?):(\d+):(\d+): ([A-Z]\d+): (.+)$")

    for line in output.split("\n"):
        match = pattern.match(line.strip())
        if match:
            file_path = match.group(1)
            line_num = int(match.group(2))
            col_num = int(match.group(3))
            code = match.group(4)
            description = match.group(5)

            if file_path not in issues:
                issues[file_path] = []

            issues[file_path].append({"line": line_num, "column": col_num, "code": code, "description": description})

    return issues


def parse_flake8_output(output: str) -> Dict[str, List[Dict[str, Any]]]:
    """
    Parse output from Flake8.

    Args:
        output: Flake8 output string

    Returns:
        Dictionary mapping file paths to lists of issues
    """
    issues = {}

    # Regular expression to match flake8 output lines
    # Example: file.py:10:5: E123 Error description
    pattern = re.compile(r"^(.+?):(\d+):(\d+): ([A-Z]\d+) (.+)$")

    for line in output.split("\n"):
        match = pattern.match(line.strip())
        if match:
            file_path = match.group(1)
            line_num = int(match.group(2))
            col_num = int(match.group(3))
            code = match.group(4)
            description = match.group(5)

            if file_path not in issues:
                issues[file_path] = []

            issues[file_path].append({"line": line_num, "column": col_num, "code": code, "description": description})

    return issues


def run_ruff(target_paths: List[str]) -> Tuple[int, Dict[str, List[Dict[str, Any]]]]:
    """
    Run Ruff linter on target paths.

    Args:
        target_paths: List of file or directory paths to analyze

    Returns:
        Tuple of (issues dictionary, total issues count)
    """
    try:
        cmd = ["ruff", "check"] + target_paths
        process = subprocess.run(cmd, capture_output=True, text=True)
        output = process.stdout or process.stderr
        issues = parse_ruff_output(output)

        # Count total issues
        total_issues = sum(len(file_issues) for file_issues in issues.values())

        return issues, total_issues
    except Exception as e:
        print(f"Error running ruff: {str(e)}")
        return {}, 0


def run_pylint(target_paths: List[str]) -> Tuple[int, Dict[str, List[Dict[str, Any]]]]:
    """
    Run Pylint on target paths.

    Args:
        target_paths: List of file or directory paths to analyze

    Returns:
        Tuple of (issues dictionary, total issues count)
    """
    try:
        cmd = ["pylint"] + target_paths
        process = subprocess.run(cmd, capture_output=True, text=True)
        output = process.stdout or process.stderr
        issues = parse_pylint_output(output)

        # Count total issues
        total_issues = sum(len(file_issues) for file_issues in issues.values())

        return issues, total_issues
    except Exception as e:
        print(f"Error running pylint: {str(e)}")
        return {}, 0


def run_flake8(target_paths: List[str]) -> Tuple[int, Dict[str, List[Dict[str, Any]]]]:
    """
    Run Flake8 on target paths.

    Args:
        target_paths: List of file or directory paths to analyze

    Returns:
        Tuple of (issues dictionary, total issues count)
    """
    try:
        cmd = ["flake8"] + target_paths
        process = subprocess.run(cmd, capture_output=True, text=True)
        output = process.stdout or process.stderr
        issues = parse_flake8_output(output)

        # Count total issues
        total_issues = sum(len(file_issues) for file_issues in issues.values())

        return issues, total_issues
    except Exception as e:
        print(f"Error running flake8: {str(e)}")
        return {}, 0


def run_quality_tool(tool: str, target_paths: List[str]) -> Tuple[Dict[str, List[Dict[str, Any]]], int]:
    """
    Run a code quality tool on target paths.

    Args:
        tool: Tool name ('ruff', 'pylint', etc.)
        target_paths: List of file or directory paths to analyze

    Returns:
        Tuple of (issues dictionary, total issues count)
    """
    if tool == "ruff":
        return run_ruff(target_paths)
    elif tool == "pylint":
        return run_pylint(target_paths)
    elif tool == "flake8":
        return run_flake8(target_paths)
    else:
        error_msg = f"Unsupported quality tool: {tool}"
        print(f"Error running {tool}: {error_msg}")
        raise ValueError(error_msg)


def extract_code_with_issues(file_path: str, issues: List[Dict[str, Any]]) -> str:
    """
    Extract code snippets with issues from a file.

    Args:
        file_path: Path to the file
        issues: List of issue dictionaries

    Returns:
        String with code snippets and issues
    """
    try:
        if not os.path.exists(file_path):
            return f"Error extracting code: File not found - {file_path}"

        with open(file_path, "r") as f:
            lines = f.readlines()

        result = []

        for issue in issues:
            line_num = issue.get("line", 0)
            if line_num > 0 and line_num <= len(lines):
                # Get context (line before and after if available)
                start = max(0, line_num - 2)
                end = min(len(lines), line_num + 1)

                context = []
                for i in range(start, end):
                    prefix = ">> " if i == line_num - 1 else "   "
                    context.append(f"{prefix}{i+1}: {lines[i].rstrip()}")

                # Add issue details
                issue_details = (
                    f"Line {line_num}: {issue.get('code', 'N/A')} - {issue.get('description', 'No description')}"
                )

                result.append(issue_details)
                result.extend(context)
                result.append("")  # Empty line for separation

        return "\n".join(result) if result else "No issues found in code"

    except Exception as e:
        return f"Error extracting code: {str(e)}"


def compare_quality_results(
    before_issues: Dict[str, List[Dict[str, Any]]], after_issues: Dict[str, List[Dict[str, Any]]]
) -> Dict[str, Dict[str, Any]]:
    """
    Compare before and after quality analysis results.

    Args:
        before_issues: Issues found before changes
        after_issues: Issues found after changes

    Returns:
        Dictionary of files with improvement metrics
    """
    improvements = {}

    # Combine all file paths from both results
    all_files = set(before_issues.keys()) | set(after_issues.keys())

    for file_path in all_files:
        before_count = len(before_issues.get(file_path, []))
        after_count = len(after_issues.get(file_path, []))

        # Only track files with improvements
        if before_count > after_count:
            improvements[file_path] = {
                "before_count": before_count,
                "after_count": after_count,
                "fixed_count": before_count - after_count,
                "before_details": before_issues.get(file_path, []),
                "after_details": after_issues.get(file_path, []),
            }

    return improvements


def create_code_quality_evidence(
    before_results: Dict[str, List[Dict[str, Any]]],
    after_results: Dict[str, List[Dict[str, Any]]],
    tool_name: str,
    before_code: Optional[Dict[str, str]] = None,
    after_code: Optional[Dict[str, str]] = None,
) -> List[CodeQualityEvidence]:
    """
    Create CodeQualityEvidence objects from before/after quality tool results.

    Args:
        before_results: Quality issues before changes
        after_results: Quality issues after changes
        tool_name: Name of the quality tool used
        before_code: Optional dictionary of code before changes
        after_code: Optional dictionary of code after changes

    Returns:
        List of CodeQualityEvidence objects
    """
    # Compare results to find improvements
    improvements = compare_quality_results(before_results, after_results)

    # Create evidence objects
    evidence_list = []

    for file_path, data in improvements.items():
        # Prepare code changes dictionary
        code_changes = {}

        # If code_before and code_after provided, use them
        if before_code and after_code and file_path in before_code and file_path in after_code:
            code_changes[file_path] = {"before": before_code[file_path], "after": after_code[file_path]}
        # Otherwise extract code from the file directly
        else:
            try:
                with open(file_path, "r") as f:
                    current_code = f.read()

                code_changes[file_path] = {"before": "Code not available", "after": current_code}
            except Exception:
                code_changes[file_path] = {"before": "Code not available", "after": "File not found or cannot be read"}

        # Calculate improvement percentage
        before_count = data["before_count"]
        after_count = data["after_count"]
        improvement_percentage = 0.0
        if before_count > 0:
            improvement_percentage = ((before_count - after_count) / before_count) * 100.0

        # Create the evidence object
        evidence = CodeQualityEvidence(
            metric_type="linting",
            before_value=float(before_count),
            after_value=float(after_count),
            percentage_improvement=improvement_percentage,
            tool=tool_name,
            file_path=file_path,
            measured_at=datetime.datetime.now().isoformat(),
        )

        evidence_list.append(evidence)

    return evidence_list


def run_quality_check(target_paths: List[str], tool: str = "ruff") -> Tuple[Dict[str, List[Dict[str, Any]]], int]:
    """
    Run a quality check on target paths.

    Args:
        target_paths: List of file or directory paths to analyze
        tool: Tool name ('ruff', 'pylint', etc.)

    Returns:
        Tuple of (issues dictionary, total issue count)
    """
    issues, count = run_quality_tool(tool, target_paths)
    return issues, count


def store_quality_results(
    results: Dict[str, List[Dict[str, Any]]],
    total_issues: int,
    tool_name: str,
    collection_name: str = "code_quality_v1",
    chroma_client=None,
) -> str:
    """
    Store code quality results in ChromaDB.

    Args:
        results: Dictionary of quality issues
        total_issues: Total number of issues found
        tool_name: Name of the quality tool used
        collection_name: ChromaDB collection name
        chroma_client: Optional ChromaDB client instance

    Returns:
        ID of the stored results
    """
    # Import here to avoid circular imports
    from chroma_mcp.utils.chroma_client import get_chroma_client

    if chroma_client is None:
        chroma_client = get_chroma_client()

    # Ensure collection exists
    try:
        collection = chroma_client.get_collection(name=collection_name)
    except Exception:
        collection = chroma_client.create_collection(name=collection_name)

    # Generate a results ID
    results_id = str(uuid.uuid4())
    timestamp = datetime.datetime.now().isoformat()

    # Prepare data for storage
    documents = []
    metadatas = []
    ids = []

    # Store a summary document
    summary = {
        "tool": tool_name,
        "total_issues": total_issues,
        "timestamp": timestamp,
        "results_id": results_id,
        "file_count": len(results),
    }

    documents.append(json.dumps(summary))
    metadatas.append(
        {
            "tool": tool_name,
            "timestamp": timestamp,
            "results_id": results_id,
            "total_issues": total_issues,
            "document_type": "summary",
        }
    )
    ids.append(f"{results_id}_summary")

    # Store individual file results
    for file_path, issues in results.items():
        file_doc = {
            "file": file_path,
            "tool": tool_name,
            "issues": issues,
            "issue_count": len(issues),
            "timestamp": timestamp,
            "results_id": results_id,
        }

        documents.append(json.dumps(file_doc))
        metadatas.append(
            {
                "file": file_path,
                "tool": tool_name,
                "timestamp": timestamp,
                "results_id": results_id,
                "issue_count": len(issues),
                "document_type": "file_result",
            }
        )
        ids.append(f"{results_id}_{hash(file_path)}")

    # Store in collection
    collection.add(documents=documents, metadatas=metadatas, ids=ids)

    return results_id
