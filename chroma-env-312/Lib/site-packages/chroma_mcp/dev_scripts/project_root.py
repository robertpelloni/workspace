from pathlib import Path


def get_project_root() -> Path:
    """
    Get the project root directory by searching upward from the current working directory
    for a directory containing 'pyproject.toml'. Falls back to the current working directory.
    """
    cwd = Path.cwd().resolve()
    for parent in (cwd, *cwd.parents):
        if (parent / "pyproject.toml").exists():
            return parent
    return cwd
