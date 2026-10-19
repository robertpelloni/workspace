"""Central browser config — point all scripts to the DEDICATED browser.
Change CDP_PORT here if needed.
"""
import os

CDP_PORT = 9333  # dedicated browser (isolated from other bot on 9222)
CDP_URL = f"http://127.0.0.1:{CDP_PORT}"
