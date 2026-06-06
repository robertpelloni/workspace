#!/bin/bash
WORKSPACE="/c/Users/hyper/workspace"
REPOS=$(grep -B 2 "url = .*robertpelloni" "$WORKSPACE/.gitmodules" | grep "path =" | awk '{print $NF}')

for REPO in $REPOS; do
    cd "$WORKSPACE/$REPO" 2>/dev/null || continue
    # Recursive update
    git submodule update --init --recursive --quiet 2>/dev/null
    
    # If still dirty, check for conflicts
    if git status | grep -q "Unmerged paths:"; then
        echo "Fixing unresolved merge in $REPO..."
        # Special case for directory/file conflicts (ksm-v2)
        git add . 2>/dev/null
        git commit -m "Auto-resolve conflicts" --no-edit --quiet 2>/dev/null
    fi
    
    # Add, commit, push submodule
    git add -A 2>/dev/null
    if ! git diff-index --quiet HEAD --; then
        git commit -m "Auto-sync: update files and submodules" --no-edit --quiet 2>/dev/null
        git push origin $(git rev-parse --abbrev-ref HEAD) --quiet 2>/dev/null
    fi
    cd "$WORKSPACE"
done
