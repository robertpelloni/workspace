#!/usr/bin/env python3
"""Add giant UNDER CONSTRUCTION banner to README.md in robertpelloni submodules."""

import os
import sys
import io

# Force UTF-8 for Windows console
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding="utf-8", errors="replace")

BANNER = r"""╔══════════════════════════════════════════════════════════════════════════════╗
║                                                                              ║
║                     ██╗   ██╗███╗   ██╗██████╗ ███████╗██████╗              ║
║                     ██║   ██║████╗  ██║██╔══██╗██╔════╝██╔══██╗             ║
║                     ██║   ██║██╔██╗ ██║██║  ██║█████╗  ██████╔╝             ║
║                     ██║   ██║██║╚██╗██║██║  ██║██╔══╝  ██╔══██╗             ║
║                     ╚██████╔╝██║ ╚████║██████╔╝███████╗██║  ██║             ║
║                      ╚═════╝ ╚═╝  ╚═══╝╚═════╝ ╚══════╝╚═╝  ╚═╝             ║
║                                                                              ║
║                     ██████╗ ██████╗ ███╗   ██╗███████╗████████╗██████╗      ║
║                    ██╔════╝██╔═══██╗████╗  ██║██╔════╝╚══██╔══╝██╔══██╗     ║
║                    ██║     ██║   ██║██╔██╗ ██║███████╗   ██║   ██████╔╝     ║
║                    ██║     ██║   ██║██║╚██╗██║╚════██║   ██║   ██╔══██╗     ║
║                    ╚██████╗╚██████╔╝██║ ╚████║███████║   ██║   ██║  ██║     ║
║                     ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝   ╚═╝   ╚═╝  ╚═╝     ║
║                                                                              ║
║                     █████╗ ██╗     ██████╗ ██╗  ██╗ █████╗                  ║
║                    ██╔══██╗██║     ██╔══██╗██║  ██║██╔══██╗                 ║
║                    ███████║██║     ██████╔╝███████║███████║                 ║
║                    ██╔══██║██║     ██╔═══╝ ██╔══██║██╔══██║                 ║
║                    ██║  ██║███████╗██║     ██║  ██║██║  ██║                 ║
║                    ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝                 ║
║                                                                              ║
║                    ╔══════════════════════════════════════╗                  ║
║                    ║     ⚠️  ALPHA SOFTWARE  ⚠️           ║                  ║
║                    ║  EXPECT BREAKING CHANGES & BUGS     ║                  ║
║                    ║  NOT READY FOR PRODUCTION USE       ║                  ║
║                    ╚══════════════════════════════════════╝                  ║
║                                                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝"""

# Get workspace root from script location or cwd
workspace = os.getcwd()

SUBMODULES = [
    "ArrowVortex",
    "Maestro",
    "MilkDrop3",
    "MilkDrop3_fix",
    "agentirc",
    "aimoneymachine_site",
    "auto_dj_script",
    "bcs",
    "bgtk",
    "bobbybookmarks",
    "bobeditpro",
    "bobfilez",
    "bobfilez_fix",
    "bobium",
    "bobsaver",
    "bobsaver_fix",
    "bobsgameonline",
    "bobsgameweb",
    "bobtrader",
    "bobtrax",
    "bobzilla",
    "bobzzite",
    "browser-use",
    "crowdsourced_dance_club",
    "dao",
    "electricsheep",
    "enterprise_sales_bot",
    "f-zerox",
    "freellm",
    "fwber",
    "hermes-agent",
    "hyper",
    "hyperharness",
    "jules-autopilot",
    "mcp-superassistant",
    "multimousergy",
    "native-fy",
    "onetool-mcp",
    "pi-mono",
    "planet_fitness_stepmaniax_agent",
    "private_gemini_storage",
    "projectm",
    "psytrance_night_outreach_agent",
    "realestatecrm",
    "skillzhub",
    "slsk_discography_downloader_script",
    "superdawmcp",
    "supersaber",
    "tabby",
    "tormentnexus",
    "veilid_reddit_facebook",
    "warp",
    "xrnet",
]


def prepend_banner(filepath):
    """Prepend banner to file. Removes existing UNDER CONSTRUCTION line if present."""
    with open(filepath, "r", encoding="utf-8", errors="replace") as f:
        content = f.read()

    # Strip existing single-line banner if present (first line)
    lines = content.split("\n")
    first_line = lines[0].strip() if lines else ""
    if (
        "UNDER CONSTRUCTION" in first_line
        or "ALPHA STATE" in first_line
        or "ALPHA" in first_line
    ):
        lines = lines[1:]
        # Also strip empty lines after the removed banner
        while lines and lines[0].strip() == "":
            lines = lines[1:]
        content = "\n".join(lines)

    new_content = BANNER + "\n\n" + content
    with open(filepath, "w", encoding="utf-8") as f:
        f.write(new_content)


count = 0
for sm in SUBMODULES:
    readme_path = os.path.join(workspace, sm, "README.md")
    if os.path.isfile(readme_path):
        try:
            prepend_banner(readme_path)
            print(f"✅ {sm}")
            count += 1
        except Exception as e:
            print(f"❌ {sm}: {e}")
    else:
        print(f"⚠️  {sm}: no README.md")

print(f"\n=== Done: {count} submodules updated ===")
