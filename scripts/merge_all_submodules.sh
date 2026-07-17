#!/bin/bash
# Comprehensive submodule merge script
# Fetches all remotes and merges feature branches into main/master

set -e

WORKSPACE="/c/Users/hyper/workspace"
cd "$WORKSPACE"

echo "=== Phase 1: Fetching all submodule remotes ==="
git submodule foreach --recursive '
  echo "Fetching: $name"
  git fetch --all --tags 2>/dev/null || true
' 2>/dev/null || true

echo ""
echo "=== Phase 2: Processing feature branches ==="

# Get list of submodules on feature branches
git submodule status 2>/dev/null | while read line; do
	path=$(echo "$line" | awk '{print $2}')
	branch_info=$(echo "$line" | grep -oP '\([^)]+\)' | tr -d '()')

	# Skip if no branch info or on main/master
	if [ -z "$branch_info" ]; then
		continue
	fi

	branch=$(echo "$branch_info" | sed 's/heads\///')

	# Skip main/master and version tags
	if [[ "$branch" == "main" || "$branch" == "master" || "$branch" =~ ^v[0-9] || "$branch" =~ ^[0-9]+\.[0-9]+ ]]; then
		continue
	fi

	# Skip upstream-specific branches
	if [[ "$branch" =~ ^(topaz|cvs|develop) ]]; then
		continue
	fi

	echo ""
	echo "--- Processing: $path (branch: $branch) ---"

	cd "$WORKSPACE/$path" 2>/dev/null || continue

	# Determine default branch
	default_branch="main"
	if git show-ref --verify --quiet refs/remotes/origin/master 2>/dev/null; then
		default_branch="master"
	fi

	# Check if branch has unique commits
	feature_commits=$(git log --oneline origin/$default_branch..HEAD 2>/dev/null | wc -l)
	main_commits=$(git log --oneline HEAD..origin/$default_branch 2>/dev/null | wc -l)

	echo "  Feature commits ahead: $feature_commits"
	echo "  Main commits behind: $main_commits"

	if [ "$feature_commits" -gt 0 ]; then
		echo "  -> Branch has unique work, attempting merge to $default_branch"

		# Save current branch
		current_branch=$(git branch --show-current)

		# Checkout default branch
		git checkout $default_branch 2>/dev/null || git checkout -b $default_branch origin/$default_branch 2>/dev/null || true

		# Try to merge feature branch
		if git merge --no-edit "$current_branch" 2>/dev/null; then
			echo "  -> Successfully merged $current_branch into $default_branch"
		else
			echo "  -> Merge conflict detected, attempting cherry-pick"
			git merge --abort 2>/dev/null || true

			# Cherry-pick individual commits
			for commit in $(git log --oneline --reverse $default_branch..$current_branch | awk '{print $1}'); do
				if git cherry-pick $commit 2>/dev/null; then
					echo "  -> Cherry-picked $commit"
				else
					echo "  -> Conflict on $commit, skipping"
					git cherry-pick --abort 2>/dev/null || true
				fi
			done
		fi

		# Return to original branch
		git checkout "$current_branch" 2>/dev/null || true
	else
		echo "  -> No unique commits, skipping"
	fi

	cd "$WORKSPACE"
done

echo ""
echo "=== Phase 3: Syncing main branches with remotes ==="

git submodule foreach --recursive '
  default_branch="main"
  if git show-ref --verify --quiet refs/remotes/origin/master 2>/dev/null; then
    default_branch="master"
  fi
  
  current=$(git branch --show-current)
  if [ "$current" = "$default_branch" ]; then
    git merge --no-edit origin/$default_branch 2>/dev/null || true
  fi
' 2>/dev/null || true

echo ""
echo "=== Merge complete ==="
