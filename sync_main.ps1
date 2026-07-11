$ErrorActionPreference = 'Stop'

$submodules = (git submodule --quiet foreach 'echo $path') -split "`n" | Where-Object { $_.Trim() -ne "" }

foreach ($sub in $submodules) {
    Write-Host "--- Processing $sub ---"
    Push-Location $sub
    $raw_branch = git branch --show-current
    if (-not $raw_branch) {
        Write-Host "Detached HEAD or no branch."
        Pop-Location
        continue
    }
    $current_branch = $raw_branch.Trim()
    Write-Host "Current branch: $current_branch"
    
    # Sync main/master
    if ($current_branch -eq "main" -or $current_branch -eq "master") {
        Write-Host "Merging origin/$current_branch into $current_branch..."
        $merge_output = git merge "origin/$current_branch" --no-edit 2>&1 | Out-String
        Write-Host $merge_output
        
        $status = git status --porcelain
        if ($status -match "^(U|M|A|D|C).*\s") {
            if ($merge_output -match "CONFLICT") {
                Write-Host "CONFLICT detected! Aborting merge."
                git merge --abort
                Write-Host "Using -X theirs to prioritize remote main changes for $sub..."
                git merge "origin/$current_branch" -X theirs --no-edit 2>&1 | Out-String | Write-Host
                
                # Double check
                $status2 = git status --porcelain
                if ($status2 -match "^U") {
                     Write-Host "STILL CONFLICTED EVEN WITH -X theirs. Aborting."
                     git merge --abort
                }
            }
        }
    }
    
    Pop-Location
}
