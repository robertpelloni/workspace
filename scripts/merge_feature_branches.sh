#!/bin/bash
# Merge feature branches into main/master for all submodules
WORKSPACE="C:/Users/hyper/workspace"

process_submodule() {
	local dir="$1"
	local path="$WORKSPACE/$dir"

	if [ ! -d "$path/.git" ] && [ ! -f "$path/.git" ]; then
		echo "SKIP: $dir (not a git repo)"
		return
	fi

	cd "$path" || return

	echo ""
	echo "=== Processing: $dir ==="

	# Fetch all
	git fetch --all --tags 2>/dev/null || true

	# Determine default branch
	local default_branch="main"
	if git show-ref --verify --quiet refs/remotes/origin/master 2>/dev/null; then
		default_branch="master"
	fi

	# Get current branch
	local current_branch=$(git branch --show-current 2>/dev/null)
	local detached=false
	if [ -z "$current_branch" ]; then
		detached=true
		current_branch=$(git rev-parse --short HEAD)
		echo "  DETACHED at $current_branch"
	fi

	# List all local branches
	echo "  Local branches:"
	git branch 2>/dev/null | sed 's/^/    /'

	# List all remote branches
	echo "  Remote branches:"
	git branch -r 2>/dev/null | grep -v HEAD | sed 's/^/    /'

	# Check if current branch is a feature branch
	if [ "$current_branch" != "$default_branch" ] && [ "$detached" = false ]; then
		echo "  On feature branch: $current_branch"

		# Check for unique commits
		local feature_commits=$(git log --oneline origin/$default_branch..HEAD 2>/dev/null | wc -l)
		local main_commits=$(git log --oneline HEAD..origin/$default_branch 2>/dev/null | wc -l)

		echo "  Feature ahead: $feature_commits, Main behind: $main_commits"

		if [ "$feature_commits" -gt 0 ]; then
			echo "  -> Merging feature into $default_branch"
			git checkout $default_branch 2>/dev/null || git checkout -b $default_branch origin/$default_branch 2>/dev/null

			if git merge --no-edit "$current_branch" 2>/dev/null; then
				echo "  -> SUCCESS: Merged $current_branch into $default_branch"
			else
				echo "  -> CONFLICT: Attempting cherry-pick"
				git merge --abort 2>/dev/null || true

				local success=0
				local failed=0
				for commit in $(git log --oneline --reverse $default_branch..$current_branch | awk '{print $1}'); do
					if git cherry-pick $commit 2>/dev/null; then
						((success++))
					else
						((failed++))
						git cherry-pick --abort 2>/dev/null || true
					fi
				done
				echo "  -> Cherry-picked: $success success, $failed conflicts"
			fi
		fi
	fi

	# For detached HEAD, check if there are remote feature branches to merge
	if [ "$detached" = true ]; then
		echo "  Checking remote feature branches..."
		git branch -r 2>/dev/null | grep -v HEAD | grep -v "$default_branch" | while read remote_branch; do
			local branch_name=$(echo "$remote_branch" | sed 's/origin\///' | xargs)
			echo "  -> Remote feature: $branch_name"
		done
	fi

	# Ensure we're on default branch
	git checkout $default_branch 2>/dev/null || true

	# Pull latest
	git pull origin $default_branch 2>/dev/null || true

	cd "$WORKSPACE"
}

# Process all submodules with feature branches
echo "=========================================="
echo "Processing submodules with feature branches"
echo "=========================================="

# Known feature branches from earlier analysis
FEATURE_BRANCHES=(
	"TurntUpToddler"
	"aimoneymachine_site"
	"bobcoin"
	"bobsgameonlinejava"
	"bobzilla"
	"dao"
	"fcdm"
	"native-fy"
	"planet_fitness_stepmaniax_agent"
	"superdawmcp"
)

for dir in "${FEATURE_BRANCHES[@]}"; do
	process_submodule "$dir"
done

echo ""
echo "=========================================="
echo "Processing modified submodules (+ prefix)"
echo "=========================================="

MODIFIED_SUBMODULES=(
	"bgtk"
	"bobmani"
	"bobsaver_fix"
	"bobsgameonline"
	"bobsgameonlinejava_fix"
	"bobsgameweb"
	"bobtorrent"
	"bobzzite"
	"browser-use"
	"electricsheep"
	"geiss"
	"jules-autopilot"
	"marketing_agent"
	"mcp-superassistant"
	"onetool-mcp"
	"openclaw-config"
	"openclaw-dashboard"
	"private_gemini_storage"
	"projectM-upstream"
	"psytrance_night_outreach_agent"
	"slsk_discography_downloader_script"
	"sm64coopdx"
	"timidity"
	"tormentnexus"
	"vst_monster"
)

for dir in "${MODIFIED_SUBMODULES[@]}"; do
	process_submodule "$dir"
done

echo ""
echo "=========================================="
echo "Processing remaining submodules"
echo "=========================================="

# Get all submodule paths
git submodule status 2>/dev/null | awk '{print $2}' | while read dir; do
	# Skip already processed
	case "$dir" in
	TurntUpToddler | aimoneymachine_site | bobcoin | bobsgameonlinejava | bobzilla | dao | fcdm | native-fy | planet_fitness_stepmaniax_agent | superdawmcp | bgtk | bobmani | bobsaver_fix | bobsgameonline | bobsgameonlinejava_fix | bobsgameweb | bobtorrent | bobzzite | browser-use | electricsheep | geiss | jules-autopilot | marketing_agent | mcp-superassistant | onetool-mcp | openclaw-config | openclaw-dashboard | private_gemini_storage | projectM-upstream | psytrance_night_outreach_agent | slsk_discography_downloader_script | sm64coopdx | timidity | tormentnexus | vst_monster)
		continue
		;;
	esac

	process_submodule "$dir"
done

echo ""
echo "=========================================="
echo "MERGE COMPLETE"
echo "=========================================="
