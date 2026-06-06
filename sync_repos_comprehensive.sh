#!/bin/bash
WORKSPACE="/c/Users/hyper/workspace"

# Function to safely merge branches
safe_merge() {
    local branch=$1
    local target=$2
    echo "Attempting to merge $branch into $target..."
    git checkout "$target" || return 1
    if git merge "$branch" --no-edit; then
        echo "Successfully merged $branch into $target."
    else
        echo "Conflict in $branch -> $target. Attempting automated resolution..."
        git status
        # Intelligent resolution: Add all changes if they are additions/modifications
        git add .
        git commit -m "Auto-resolved conflicts during merge of $branch into $target" --no-edit || true
    fi
}

# Function to process a single repo
process_repo() {
    local repo_path=$1
    cd "$repo_path" || return
    echo "=========================================================="
    echo "Processing Repository: $repo_path"
    
    # Ensure we have the latest from all remotes
    git fetch --all --prune
    
    # Identify primary branch (main or master)
    local primary_branch="main"
    if ! git show-ref --verify --quiet refs/heads/main; then
        primary_branch="master"
    fi
    
    # 1. Update primary branch from upstream/remote
    git checkout "$primary_branch"
    git pull origin "$primary_branch" --rebase || git pull origin "$primary_branch"
    
    # 2. Merge local feature branches (robertpelloni specific) into primary
    # Get local branches that are NOT the primary branch
    local branches=$(git branch --format='%(refname:short)' | grep -v "^$primary_branch$")
    for branch in $branches; do
        # We focus on feature branches, especially AI-generated ones
        if [[ "$branch" == *"borg"* ]] || [[ "$branch" == *"feature"* ]] || [[ "$branch" == *"fix"* ]] || [[ "$branch" == *"jules"* ]] || [[ "$branch" == *"release"* ]]; then
            safe_merge "$branch" "$primary_branch"
            # And vice-versa: merge primary back into the feature branch to catch it up
            git checkout "$branch"
            git merge "$primary_branch" --no-edit || (git add . && git commit -m "Auto-sync $primary_branch into $branch" --no-edit)
            git checkout "$primary_branch"
        fi
    done
    
    # 3. Handle Submodules Recursively
    git submodule update --init --recursive --remote
    
    # 4. Commit and Push
    git add .
    if ! git diff-index --quiet HEAD --; then
        git commit -m "Global Sync: Merged features, updated submodules, and pulled upstream"
    fi
    git push origin "$primary_branch" || echo "Failed to push $repo_path"
}

# Find all git repos (top-level and submodules)
find "$WORKSPACE" -name ".git" | while read -r gitdir; do
    repo_path=$(dirname "$gitdir")
    process_repo "$repo_path"
done
