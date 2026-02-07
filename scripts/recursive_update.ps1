# Recursive git update script
$ErrorActionPreference = "Continue"

function Update-Repo {
    param (
        [string]$Path
    )

    Write-Host "Processing $Path..." -ForegroundColor Cyan
    Push-Location $Path

    try {
        # Check if it's a git repo
        if (-not (Test-Path .git)) {
            Write-Warning "Not a git repository: $Path"
            return
        }

        # Fetch all remotes
        git fetch --all --prune | Out-Null

        # Get current branch
        $branch = (git branch --show-current).Trim()
        if ([string]::IsNullOrWhiteSpace($branch)) {
            Write-Warning "Detached HEAD at $Path. Checking out main..."
            git checkout main 2>&1 | Out-Null
            if ($LASTEXITCODE -ne 0) { git checkout master 2>&1 | Out-Null }
            $branch = (git branch --show-current).Trim()
        }

        # Merge upstream if exists
        $remotes = git remote
        if ($remotes -contains "upstream") {
            Write-Host "Merging upstream/$branch..."
            git merge upstream/$branch | Out-Null
        }

        # Merge origin (robertpelloni fork)
        if ($remotes -contains "origin") {
            Write-Host "Merging origin/$branch..."
            git merge origin/$branch | Out-Null
        }

        # Recursively update submodules
        # We use --init but NOT --recursive here to control the depth manually if needed, 
        # but --recursive is generally safer for consistency.
        git submodule update --init --recursive 2>&1 | Out-Null

        # Add changes (including submodule updates)
        git add . 2>&1 | Out-Null

        # Commit if there are changes
        if ((git status --porcelain) -ne "") {
            git commit -m "chore: recursive update and merge" 2>&1 | Out-Null
            Write-Host "Committed changes in $Path" -ForegroundColor Green
        }

        # Push to origin
        if ($remotes -contains "origin") {
            git push origin $branch 2>&1 | Out-Null
            Write-Host "Pushed $Path" -ForegroundColor Green
        }

    } catch {
        Write-Error "Failed to process $Path : $_"
    } finally {
        Pop-Location
    }
}

# 1. Update root submodules
$submodules = git submodule status | ForEach-Object { $_.Trim().Split(" ")[1] }

foreach ($sub in $submodules) {
    if (Test-Path $sub) {
        Update-Repo -Path $sub
    }
}

# 2. Handle specific nested cases or top-level dirs that are git repos but maybe not tracked correctly yet
# (Like the ones I just fixed: bobmani/bobmania, etc)
$manualPaths = @(
    "Alti.Code.Studio",
    "Alti.Assistant",
    "bobmani/bobmania",
    "bobmani/itgmania",
    "bobmani/beatoraja",
    "bobmani/hymnmania",
    "bobmani/ksm-v2",
    "bobmani/linthesia",
    "bobmani/pianogame",
    "bobfilez"
)

foreach ($path in $manualPaths) {
    if (Test-Path $path) {
        Update-Repo -Path $path
    }
}
