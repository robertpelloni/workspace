#!/bin/bash
# Fetch all submodules in parallel batches
cd /c/Users/hyper/workspace

echo "=== Fetching root repo ==="
git fetch --all --tags 2>&1

echo ""
echo "=== Fetching all submodules ==="
git submodule status 2>/dev/null | awk '{print $2}' | while read dir; do
	if [ -d "$dir/.git" ] || [ -f "$dir/.git" ]; then
		echo "Fetching: $dir"
		(cd "$dir" && git fetch --all --tags 2>/dev/null) &
	fi
done
wait

echo ""
echo "=== Fetch complete ==="
