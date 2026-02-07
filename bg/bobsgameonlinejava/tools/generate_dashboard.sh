#!/bin/bash

echo "# Project Dashboard" > DASHBOARD.md
echo "" >> DASHBOARD.md
echo "This dashboard lists the status of all submodules and the project structure." >> DASHBOARD.md
echo "" >> DASHBOARD.md
echo "## Project Structure" >> DASHBOARD.md
echo "" >> DASHBOARD.md
echo "- **client/**: Contains the main game client source code, assets, and logic. Uses LWJGL 3." >> DASHBOARD.md
echo "- **server/**: Contains the dedicated game server code. Uses Netty 4." >> DASHBOARD.md
echo "- **shared/**: Contains shared data structures, networking packets, and utility classes used by both client and server." >> DASHBOARD.md
echo "- **libs/**: Contains external libraries used by the project. Some are included as Git submodules." >> DASHBOARD.md
echo "- **references/**: Contains Git submodules of external open-source projects (editors, engines) used for feature research and reference." >> DASHBOARD.md
echo "" >> DASHBOARD.md
echo "## Submodule Status" >> DASHBOARD.md
echo "" >> DASHBOARD.md
echo "| Path | Branch | Commit | Date | Version/Build |" >> DASHBOARD.md
echo "| --- | --- | --- | --- | --- |" >> DASHBOARD.md

# Iterate over submodules
git submodule status --recursive | while read -r sha path describe; do
    # Get branch info from .gitmodules
    name=$(git config -f .gitmodules --get-regexp path | grep "$path$" | awk '{print $1}' | sed 's/\.path//')
    branch=$(git config -f .gitmodules --get "submodule.$name.branch")
    if [ -z "$branch" ]; then branch="HEAD"; fi

    # Get submodule info
    cd "$path"
    date=$(git log -1 --format=%cd --date=short)
    # Try to get a tag or describe, else count commits
    version=$(git describe --tags 2>/dev/null)
    if [ -z "$version" ]; then
        count=$(git rev-list --count HEAD)
        version="build-$count"
    fi

    echo "| $path | $branch | ${sha:0:7} | $date | $version |" >> ../../DASHBOARD.md
    cd - > /dev/null
done

echo "" >> DASHBOARD.md
echo "Generated on $(date)" >> DASHBOARD.md
