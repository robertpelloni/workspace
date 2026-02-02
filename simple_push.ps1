# simple_push.ps1
$remote = git remote get-url origin 2>$null
if (!$remote) { exit 0 }

Write-Host "`n>>> Submodule: $pwd"
if ($(git status --porcelain)) {
    Write-Host "Changes found. Committing..."
    git add .
    git commit -m "chore: automated update"
}

if ($remote -match "robertpelloni") {
    $branches = git branch -r
    $defaultBranch = "main"
    if ($branches -match "origin/master") { $defaultBranch = "master" }
    Write-Host "Pushing to origin $defaultBranch..."
    git push origin $defaultBranch
}
