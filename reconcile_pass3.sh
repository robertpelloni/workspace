#!/bin/bash
# Reconciliation Pass 3 — Fetch all, merge remaining feature branches
# v5.249.0 → v5.250.0

WORKSPACE="/c/Users/hyper/workspace"
LOG="$WORKSPACE/merge_pass3.log"
>"$LOG"

echo "=== RECONCILIATION PASS 3 — $(date) ===" | tee -a "$LOG"

# List of submodules to process (all .gitmodules entries)
SUBMODULES=$(cd "$WORKSPACE" && git config --file .gitmodules --get-regexp path | awk '{print $2}')

# Track results
declare -A MERGE_RESULTS
TOTAL_MERGES=0
TOTAL_PUSHES=0

process_submodule() {
	local sub_path="$1"
	local full_path="$WORKSPACE/$sub_path"

	if [ ! -d "$full_path/.git" ] && [ ! -f "$full_path/.git" ]; then
		echo "SKIP: $sub_path — not initialized" | tee -a "$LOG"
		return
	fi

	cd "$full_path" || return

	# Determine default branch
	local default_branch="main"
	if git rev-parse --verify master >/dev/null 2>&1; then
		local main_exists=$(git rev-parse --verify main 2>/dev/null)
		if [ -z "$main_exists" ]; then
			default_branch="master"
		fi
	fi

	# Fetch all
	git fetch --all --prune 2>/dev/null

	# Get current branch
	local current_branch=$(git rev-parse --abbrev-ref HEAD 2>/dev/null)

	# If detached HEAD, checkout default branch
	if [ "$current_branch" = "HEAD" ]; then
		git checkout "$default_branch" 2>/dev/null
	fi

	# Get list of remote branches (excluding HEAD, default, upstream)
	local branches=$(git branch -r 2>/dev/null | grep -v "HEAD" | grep -v "origin/$default_branch" | grep -v "upstream/" | sed 's/origin\///' | sed 's/^[[:space:]]*//' | sort -u)

	if [ -z "$branches" ]; then
		echo "OK: $sub_path — no feature branches" | tee -a "$LOG"
		return
	fi

	echo "--- $sub_path ($default_branch) ---" | tee -a "$LOG"
	echo "  Feature branches: $(echo "$branches" | wc -l)" | tee -a "$LOG"

	local merged_here=0

	for branch in $branches; do
		# Skip if branch doesn't exist remotely
		if ! git rev-parse --verify "origin/$branch" >/dev/null 2>&1; then
			continue
		fi

		# Check if branch has unique commits vs default
		local unique=$(git log "$default_branch..origin/$branch" --oneline 2>/dev/null | wc -l)

		if [ "$unique" -eq 0 ]; then
			echo "  SKIP: $branch — already merged (0 unique commits)" | tee -a "$LOG"
			continue
		fi

		echo "  MERGE: $branch ($unique unique commits)" | tee -a "$LOG"

		# Try merge
		cd "$full_path"
		git checkout "$default_branch" 2>/dev/null

		if git merge "origin/$branch" --no-edit -m "merge: $branch into $default_branch (pass 3)" 2>>"$LOG"; then
			echo "    ✓ Merged successfully" | tee -a "$LOG"
			merged_here=$((merged_here + 1))
			TOTAL_MERGES=$((TOTAL_MERGES + 1))
		else
			# Conflict — try to resolve or abort
			echo "    ✗ Conflict detected, attempting resolution..." | tee -a "$LOG"

			# Try theirs strategy for non-critical files
			git merge --abort 2>/dev/null

			# Try cherry-pick of individual commits
			local commits=$(git log "$default_branch..origin/$branch" --format="%H" 2>/dev/null)
			local cherry_picked=0
			for commit in $commits; do
				if git cherry-pick "$commit" --no-edit 2>>"$LOG"; then
					cherry_picked=$((cherry_picked + 1))
				else
					git cherry-pick --abort 2>/dev/null
				fi
			done

			if [ "$cherry_picked" -gt 0 ]; then
				echo "    ✓ Cherry-picked $cherry_picked commits" | tee -a "$LOG"
				merged_here=$((merged_here + 1))
				TOTAL_MERGES=$((TOTAL_MERGES + 1))
			else
				echo "    ✗ Could not merge or cherry-pick" | tee -a "$LOG"
			fi
		fi
	done

	if [ "$merged_here" -gt 0 ]; then
		echo "  PUSH: $sub_path ($merged_here merges)" | tee -a "$LOG"
		if git push origin "$default_branch" 2>>"$LOG"; then
			echo "    ✓ Pushed" | tee -a "$LOG"
			TOTAL_PUSHES=$((TOTAL_PUSHES + 1))
		else
			echo "    ✗ Push failed" | tee -a "$LOG"
		fi
	fi

	echo "" | tee -a "$LOG"
}

# Process all submodules
for sub in $SUBMODULES; do
	process_submodule "$sub"
done

echo "=== SUMMARY ===" | tee -a "$LOG"
echo "Total merges: $TOTAL_MERGES" | tee -a "$LOG"
echo "Total pushes: $TOTAL_PUSHES" | tee -a "$LOG"
echo "Log: $LOG"
