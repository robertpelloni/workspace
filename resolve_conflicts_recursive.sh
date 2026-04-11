#!/bin/bash
WORKSPACE="/c/Users/hyper/workspace"

# Function to resolve git locks and submodule unmerged paths
resolve_repo_issues() {
    local repo_path=$1
    cd "$repo_path" || return
    
    # 1. Clean up index.lock if it exists
    if [ -f ".git/index.lock" ]; then
        rm ".git/index.lock"
    fi
    if [ -f ".git/modules/*/index.lock" ]; then
        rm .git/modules/*/index.lock 2>/dev/null
    fi

    # 2. Resolve Unmerged Paths
    if git status | grep -q "Unmerged paths:"; then
        echo "Resolving conflicts in $repo_path"
        git add .
        git commit -m "Auto-resolve: merge conflict resolution" --no-edit 2>/dev/null
    fi

    # 3. Recursive submodule fix
    git submodule status | while read -r status path commit; do
        if [[ $status == "U"* ]]; then
             # Unmerged submodule
             echo "Submodule conflict: $path. Attempting to accept current state."
             git add "$path"
        fi
    done
}

# Run through all submodules
git submodule foreach --recursive '
    if [ -f ".git/index.lock" ]; then rm ".git/index.lock"; fi
    git add . 2>/dev/null
    if ! git diff-index --quiet HEAD --; then
        git commit -m "Auto-sync submodule state" --no-edit 2>/dev/null
    fi
    git push origin HEAD --quiet 2>/dev/null || true
'

# Final root cleanup
cd "$WORKSPACE"
git add .
git commit -m "Finalizing workspace state after comprehensive sync" --no-edit 2>/dev/null
git push origin main --quiet 2>/dev/null
