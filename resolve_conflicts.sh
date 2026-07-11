#!/bin/bash
WORKSPACE="/c/Users/hyper/workspace"
REPOS=$(grep -B 2 "url = .*robertpelloni" "$WORKSPACE/.gitmodules" | grep "path =" | awk '{print $NF}')

for REPO in $REPOS; do
    cd "$WORKSPACE/$REPO" 2>/dev/null || continue
    if git status | grep -q "Unmerged paths:"; then
        echo "Resolving conflicts in $REPO..."
        git add -A
        git commit -m "Auto-resolve: keep both changes" --no-edit --quiet 2>/dev/null
    fi
    cd "$WORKSPACE"
done
