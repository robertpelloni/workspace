import sys
import warnings
from . import cli


def main():
    """
    Deprecated CLI entry point that shows a warning and then calls the main CLI module.
    This will be removed in version 0.3.0.
    """
    warnings.warn(
        "The 'chroma-client' command is deprecated and will be removed in version 0.3.0. "
        "Please use 'chroma-mcp-client' instead.",
        DeprecationWarning,
        stacklevel=2,
    )
    return cli.main()


if __name__ == "__main__":
    sys.exit(main())
