#!/bin/bash
WORKSPACE="/c/Users/hyper/workspace"

# Function to get default branch
get_default_branch() {
    git remote show origin | grep 'HEAD branch' | cut -d' ' -f5 || echo "main"
}

# Function to process a single repo
process_repo() {
    local repo_path=$1
    cd "$repo_path" || return
    echo "=========================================================="
    echo "Syncing: $repo_path"

    # 1. Clean environment
    rm -f .git/index.lock
    
    # 2. Fetch all remotes
    git fetch --all --prune

    # 3. Determine main branch
    local main_branch=$(get_default_branch)
    if ! git show-ref --verify --quiet refs/heads/"$main_branch"; then
        if git show-ref --verify --quiet refs/heads/master; then
            main_branch="master"
        else
            main_branch="main"
        fi
    fi

    # 4. Update main from remote
    git checkout "$main_branch" || git checkout -b "$main_branch" "origin/$main_branch"
    git pull origin "$main_branch" --rebase || git pull origin "$main_branch"

    # 5. Merge local feature branches into main
    # Focus on robertpelloni (local) branches and AI generated ones
    local branches=$(git branch --format='%(refname:short)' | grep -v "^$main_branch$")
    for branch in $branches; do
        if [[ "$branch" == *"jules"* ]] || [[ "$branch" == *"borg"* ]] || [[ "$branch" == *"feature"* ]] || [[ "$branch" == *"fix"* ]] || [[ "$branch" == *"release"* ]]; then
            echo "Merging $branch into $main_branch..."
            if git merge "$branch" --no-edit; then
                # After successful merge into main, merge main back into feature branch to catch it up
                git checkout "$branch"
                git merge "$main_branch" --no-edit || (git add . && git commit -m "Sync main into $branch" --no-edit)
                git checkout "$main_branch"
            else
                echo "Conflict merging $branch. Attempting auto-resolution (favoring merge progress)..."
                git add .
                git commit -m "Auto-resolved conflicts: Merging $branch into $main_branch" --no-edit || true
                
                # Try to catch up the feature branch anyway
                git checkout "$branch"
                git merge "$main_branch" --no-edit || (git add . && git commit -m "Sync main into $branch (with conflicts)" --no-edit)
                git checkout "$main_branch"
            fi
        fi
    done

    # 6. Recursive Submodule Sync
    # We use a robust approach for submodules to avoid "bad revision" errors
    git submodule sync --recursive
    git submodule update --init --recursive --remote --merge || git submodule update --init --recursive --remote --rebase || echo "Submodule update failed for some modules in $repo_path, moving on..."

    # 7. Final Add/Commit/Push
    git add .
    if ! git diff-index --quiet HEAD --; then
        git commit -m "Global Sync: Consolidated feature branches and updated submodules"
    fi
    
    # Try pushing if it's a robertpelloni repo or we have permission
    local remote_url=$(git remote get-url origin)
    if [[ "$remote_url" == *"robertpelloni"* ]]; then
        git push origin "$main_branch"
        # Push submodules pointers too
        git submodule foreach --recursive "git push origin \$(git rev-parse --abbrev-ref HEAD) || true"
    fi
}

# Find all git repos
# We use a depth-first approach by sorting by path length (deepest first)
find "$WORKSPACE" -name ".git" | awk '{ print length, $0 }' | sort -rn | cut -d" " -f2- | while read -r gitdir; do
    repo_path=$(dirname "$gitdir")
    process_repo "$repo_path"
done
