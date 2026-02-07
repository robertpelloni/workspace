# Recursive git update script v2
$ErrorActionPreference = "Continue"

function Update-Repo {
    param (
        [string]$Path
    )

    Write-Host "Processing $Path..." -ForegroundColor Cyan
    if (-not (Test-Path $Path)) {
        Write-Warning "Path not found: $Path"
        return
    }
    
    Push-Location $Path

    try {
        if (-not (Test-Path .git)) {
            Write-Warning "Not a git repository: $Path"
            return
        }

        # Fetch all
        git fetch --all --prune | Out-Null

        # Detect default branch (main or master)
        $defaultBranch = "main"
        if (git show-ref --verify --quiet refs/heads/master) {
            $defaultBranch = "master"
        }
        
        $currentBranch = (git branch --show-current).Trim()
        Write-Host "Current branch: $currentBranch (Default: $defaultBranch)" -ForegroundColor Gray

        # If detached, try to checkout default
        if ([string]::IsNullOrWhiteSpace($currentBranch)) {
            Write-Warning "Detached HEAD. Checking out $defaultBranch..."
            git checkout $defaultBranch 2>&1 | Out-Null
            $currentBranch = $defaultBranch
        }

        # If on a feature branch (not main/master), merge it into default
        if ($currentBranch -ne $defaultBranch) {
            Write-Host "On feature branch '$currentBranch'. Switching to '$defaultBranch' and merging..." -ForegroundColor Yellow
            git checkout $defaultBranch 2>&1 | Out-Null
            git merge $currentBranch 2>&1 | Out-Null
            $currentBranch = $defaultBranch
        }

        # Now on default branch. Merge Upstream and Origin.
        $remotes = git remote

        if ($remotes -contains "upstream") {
            Write-Host "Merging upstream/$defaultBranch..."
            git merge upstream/$defaultBranch | Out-Null
        }

        if ($remotes -contains "origin") {
            Write-Host "Merging origin/$defaultBranch..."
            git merge origin/$defaultBranch | Out-Null
        }

        # Submodules
        git submodule update --init --recursive 2>&1 | Out-Null

        # Commit
        git add . 2>&1 | Out-Null
        if ((git status --porcelain) -ne "") {
            git commit -m "chore: recursive update and merge feature branches" 2>&1 | Out-Null
            Write-Host "Committed changes in $Path" -ForegroundColor Green
        }

        # Push
        if ($remotes -contains "origin") {
            git push origin $defaultBranch 2>&1 | Out-Null
            Write-Host "Pushed $Path" -ForegroundColor Green
        }

    } catch {
        Write-Error "Failed to process $Path : $_"
    } finally {
        Pop-Location
    }
}

# 1. Root Submodules
$submodules = git submodule status | ForEach-Object { $_.Trim().Split(" ")[1] }
foreach ($sub in $submodules) { Update-Repo -Path $sub }

# 2. Nested Submodules (Manual list for priority/safety)
$nested = @(
    "bobmani/bobmania",
    "bobmani/itgmania",
    "bobmani/beatoraja",
    "bobmani/hymnmania",
    "bobmani/ksm-v2",
    "bobmani/linthesia",
    "bobmani/pianogame"
)
foreach ($path in $nested) { Update-Repo -Path $path }
