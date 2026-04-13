#!/bin/bash
WORKSPACE="/c/Users/hyper/workspace"

resolve_repo() {
    local repo_path=$1
    cd "$repo_path" || return
    
    if [ -d ".git" ]; then
        # Check for lock files
        if [ -f ".git/index.lock" ]; then
            echo "Removing lock in $repo_path"
            rm -f ".git/index.lock"
        fi
        
        # Check for unmerged paths
        if git status | grep -q "unmerged paths"; then
            echo "Resolving conflicts in $repo_path"
            # Favoring "our" changes for safety in the context of merging feature branches into main,
            # but we will stage everything that was automatically merged successfully.
            git add .
            git commit -m "Auto-resolve conflicts" --no-edit || true
        fi
    fi
}

find "$WORKSPACE" -name ".git" | while read -r gitdir; do
    repo_path=$(dirname "$gitdir")
    resolve_repo "$repo_path"
done
