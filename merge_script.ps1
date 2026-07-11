$ErrorActionPreference = "Continue"

function Merge-Repo {
    param ($repo, $branches)
    Write-Host "=== Merging branches in $repo ==="
    cd $repo
    
    $mainBranch = "main"
    $hasMain = git branch | Select-String "\bmain\b"
    if (!$hasMain) {
        $hasMaster = git branch | Select-String "\bmaster\b"
        if ($hasMaster) {
            $mainBranch = "master"
        } else {
            git checkout -b main origin/main
        }
    }
    
    git checkout $mainBranch
    git pull origin $mainBranch

    foreach ($branch in $branches) {
        Write-Host "  Merging $branch into $mainBranch"
        git merge $branch -m "Merge $branch into $mainBranch to consolidate features"
        if ($LASTEXITCODE -ne 0) {
            Write-Host "    Merge conflict! Aborting forward merge and attempting reverse merge."
            git merge --abort
            
            $localBranch = $branch -replace "origin/", ""
            git checkout $localBranch
            if ($LASTEXITCODE -ne 0) {
                git checkout -b $localBranch $branch
            }
            Write-Host "    Reverse merging $mainBranch into $localBranch"
            git merge $mainBranch -m "Reverse merge $mainBranch into $localBranch to prevent drift"
            git checkout $mainBranch
        } else {
            Write-Host "    Merge successful."
        }
    }
    cd ..
}

Merge-Repo "brokeragentworkflow" @("origin/jules-15611515557307440123-585a1605")
Merge-Repo "hymnmania" @("origin/feat/comprehensive-docs-and-tts-params-16556208438382467677", "origin/feat/psy-mono-pipeline-1.27.0-9908176330949525010", "origin/feature/web-ui-and-parallelization-5540056130352860192")
Merge-Repo "hypercode" @("origin/feat/immune-system-dashboard-truth-pass-7249401460413473838")
Merge-Repo "jules-autopilot" @("origin/jules-17764958747146694232-3d7c3856", "origin/hypercode-sync")
Merge-Repo "re-agent-workflow-media-1" @("origin/feature/init-media-pipeline-17967464845567188821")
Merge-Repo "realestateleadcaller" @("origin/jules-ai-real-estate-concierge-mvp-8261096991693832942")
