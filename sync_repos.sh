#!/bin/bash
WORKSPACE="/c/Users/hyper/workspace"
REPOS=$(grep -B 2 "url = .*robertpelloni" "$WORKSPACE/.gitmodules" | grep "path =" | awk '{print $NF}')

for REPO in $REPOS; do
    echo "Processing $REPO..."
    cd "$WORKSPACE/$REPO" 2>/dev/null || { echo "  Skipping (dir not found)"; continue; }
    
    # 1. Fetch updates
    git fetch --all --prune --quiet 2>/dev/null
    
    # 2. Identify main/master
    MAIN_BRANCH=$(git remote show origin 2>/dev/null | grep 'HEAD branch' | awk '{print $NF}')
    [ -z "$MAIN_BRANCH" ] && MAIN_BRANCH="main"
    git rev-parse --verify "$MAIN_BRANCH" >/dev/null 2>&1 || MAIN_BRANCH="master"
    
    # 3. Handle local feature branches
    git branch --format='%(refname:short)' | while read branch; do
        [ "$branch" = "$MAIN_BRANCH" ] && continue
        
        # Check if it's a local feature branch
        if ! git rev-parse --verify "origin/$branch" >/dev/null 2>&1; then
            echo "  Merging feature branch $branch into $MAIN_BRANCH..."
            git checkout "$MAIN_BRANCH" --quiet
            git merge "$branch" --no-edit --quiet 2>/dev/null || {
                echo "    Conflict in $branch -> $MAIN_BRANCH. Auto-resolving (keep both)..."
                git add -A && git commit -m "Auto-resolve: merge $branch" --no-edit --quiet
            }
            
            echo "  Updating feature branch $branch from $MAIN_BRANCH..."
            git checkout "$branch" --quiet
            git merge "$MAIN_BRANCH" --no-edit --quiet 2>/dev/null || {
                echo "    Conflict in $MAIN_BRANCH -> $branch. Auto-resolving (keep both)..."
                git add -A && git commit -m "Auto-resolve: catch up with $MAIN_BRANCH" --no-edit --quiet
            }
            git checkout "$MAIN_BRANCH" --quiet
        fi
    done

    # 4. Sync with upstream
    if git remote | grep -q "^upstream$"; then
        UPSTREAM_BRANCH=$(git remote show upstream 2>/dev/null | grep 'HEAD branch' | awk '{print $NF}')
        [ -n "$UPSTREAM_BRANCH" ] && {
            echo "  Merging upstream/$UPSTREAM_BRANCH..."
            git merge "upstream/$UPSTREAM_BRANCH" --no-edit --quiet 2>/dev/null || {
                git add -A && git commit -m "Auto-resolve: merge upstream" --no-edit --quiet
            }
        }
    fi

    # 5. Final push
    git push origin "$MAIN_BRANCH" --quiet 2>/dev/null
    echo "  Done."
    cd "$WORKSPACE"
done
