#!/bin/bash
WORKSPACE="/c/Users/hyper/workspace"

# Function to fix a specific repo/submodule
fix_repo() {
    local repo_path=$1
    cd "$repo_path" || return
    echo "Fixing $repo_path..."

    # 1. Handle "bad revision HEAD" (empty repos or detached)
    if ! git rev-parse HEAD &>/dev/null; then
        echo "Empty/Broken HEAD in $repo_path. Attempting checkout master/main."
        git checkout master &>/dev/null || git checkout main &>/dev/null
    fi

    # 2. Break embedded git repos (usually build artifacts)
    # If a .git directory exists inside a directory that is NOT a submodule, it causes issues.
    # We find .git dirs that are NOT at the top level of this repo.
    find . -mindepth 2 -name ".git" -type d | while read -r subgit; do
        if [ ! -f ".gitmodules" ] || ! grep -q "$(dirname "$subgit")" .gitmodules; then
            echo "Removing embedded build-generated .git: $subgit"
            rm -rf "$subgit"
        fi
    done

    # 3. Clean index and resolve
    rm -f .git/index.lock
    git add . 2>/dev/null
}

# Find all git repos again
find "$WORKSPACE" -name ".git" | while read -r gitdir; do
    repo_path=$(dirname "$gitdir")
    fix_repo "$repo_path"
done

# Resume Sync Protocol
cd "$WORKSPACE"
./recursive_sync_protocol.sh
