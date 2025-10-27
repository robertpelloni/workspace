"""Pytest hooks for chroma-mcp-client users."""

import os
import subprocess
import json
from datetime import datetime
import glob
import pathlib  # Import pathlib


def pytest_addoption(parser):
    """Add the --auto-capture-workflow option to pytest."""
    parser.addoption(
        "--auto-capture-workflow",
        action="store_true",
        dest="auto_capture_workflow",
        help="Enable automated test workflow capturing (failures and transitions).",
    )


def pytest_sessionfinish(session, exitstatus):
    """
    After the test session finishes, if auto-capture-workflow was requested,
    log test results, generate workflow JSON (failed or transitioned),
    and call the CLI with appropriate flags.
    """
    config = session.config
    if not config.getoption("auto_capture_workflow"):
        return

    # Use pathlib for more robust path handling, relative to user's project root
    project_root = pathlib.Path(session.config.rootdir)
    xml_path = project_root / "logs" / "tests" / "junit" / "test-results.xml"

    if not xml_path.exists():
        # Consider logging a warning if the XML file isn't found
        print(f"pytest-sessionfinish: JUnit XML file not found at {xml_path}. Skipping workflow capture.")
        return

    # Prepare base CLI command
    # Ensure chroma-mcp-client is in PATH, which it should be if package is installed
    base_cmd = ["chroma-mcp-client", "log-test-results", str(xml_path)]

    # Get current commit hash
    try:
        # Run git command from the project root
        commit_hash = subprocess.check_output(["git", "rev-parse", "HEAD"], cwd=str(project_root)).decode().strip()
    except Exception:
        commit_hash = "unknown"

    # Ensure workflow directory exists
    workflow_dir = project_root / "logs" / "tests" / "workflows"
    workflow_dir.mkdir(parents=True, exist_ok=True)

    # Timestamp for filenames
    ts = datetime.now().strftime("%Y%m%d_%H%M%S")

    if exitstatus != 0:
        # Test failures: log results and capture failure JSON
        subprocess.run(base_cmd, check=False, cwd=str(project_root))
        failure_file = workflow_dir / f"test_workflow_{ts}.json"
        failure_data = {"status": "failed", "timestamp": ts, "xml_path": str(xml_path), "commit": commit_hash}
        with open(failure_file, "w") as f:
            json.dump(failure_data, f)
    else:
        # Test success: find most recent failure JSON
        pattern = str(workflow_dir / "test_workflow_*.json")
        # Exclude completed workflow files when determining previous failures
        all_files = glob.glob(pattern)
        files = [f for f in all_files if "test_workflow_complete_" not in os.path.basename(f)]

        if files:
            files.sort(key=os.path.getmtime)
            latest_failure_json_path = files[-1]
            with open(latest_failure_json_path) as f:
                prev = json.load(f)
            # Support both initial failure keys and completed workflow keys
            before_xml_str = prev.get("xml_path") or prev.get("before_xml")
            before_commit = prev.get("commit") or prev.get("before_commit")

            if not before_xml_str:
                print(
                    f"pytest-sessionfinish: 'xml_path' or 'before_xml' not found in {latest_failure_json_path}. Cannot determine previous XML."
                )
                subprocess.run(base_cmd, check=False, cwd=str(project_root))  # Log current results anyway
                return

            cmd = base_cmd + [
                "--before-xml",
                before_xml_str,  # Ensure this is a string path
                "--commit-before",
                before_commit,
                "--commit-after",
                commit_hash,
            ]
            subprocess.run(cmd, check=False, cwd=str(project_root))
            # Write completed workflow JSON
            completed_file = workflow_dir / f"test_workflow_complete_{ts}.json"
            completed_data = {
                "status": "transitioned",
                "timestamp": ts,
                "before_xml": before_xml_str,
                "after_xml": str(xml_path),
                "before_commit": before_commit,
                "after_commit": commit_hash,
            }
            with open(completed_file, "w") as f:
                json.dump(completed_data, f)
        else:
            # No failure history: just log results
            subprocess.run(base_cmd, check=False, cwd=str(project_root))
