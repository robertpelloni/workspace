# recursive_fix.ps1
$ErrorActionPreference = "Continue"

function Get-DefaultBranch {
    $branches = git branch -r
    if ($branches -match "origin/main") { return "main" }
    if ($branches -match "origin/master") { return "master" }
    $head = git symbolic-ref --short refs/remotes/origin/HEAD 2>$null
    if ($head) { return $head -replace "origin/", "" }
    return (git rev-parse --abbrev-ref HEAD)
}

$remote = git remote get-url origin 2>$null
if (!$remote) { exit 0 }

Write-Host "`n>>> Processing: $pwd"
Write-Host "Remote: $remote"

# 1. Fetch
git fetch --all --prune

# 2. Status check
$status = git status --porcelain
$submoduleChanges = git status | Select-String "modified content"

if ($remote -match "robertpelloni") {
    $defaultBranch = Get-DefaultBranch
    Write-Host "Default branch: $defaultBranch"

    # Ensure we are on the default branch
    git checkout $defaultBranch 2>$null
    git pull origin $defaultBranch 2>$null

    # 3. Merge feature branches
    $localBranches = git branch --format="%(refname:short)" | Where-Object { $_ -ne $defaultBranch -and $_ -ne "HEAD" }
    foreach ($branch in $localBranches) {
        Write-Host "Merging branch: $branch"
        git merge $branch --no-edit -X theirs
        if ($LASTEXITCODE -ne 0) {
            Write-Warning "Conflict merging $branch. Aborting."
            git merge --abort
        }
    }

    # 4. Commit changes if any (including pointer updates)
    if ($(git status --porcelain)) {
        Write-Host "Committing changes..."
        git add .
        # Avoid committing workflows if it caused failures before
        git reset .github/workflows 2>$null 
        git commit -m "chore: automated recursive update and merge"
    }

    # 5. Push
    Write-Host "Pushing..."
    git push origin $defaultBranch
} else {
    # External repo: just update pointers if nested submodules changed
    if ($(git status --porcelain)) {
        Write-Host "External repo changed (likely nested submodules), committing pointers..."
        git add .
        git commit -m "chore: update nested submodule pointers"
    }
}
