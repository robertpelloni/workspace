$results = New-Object System.Collections.Generic.List[PSObject]
$submoduleStatus = git submodule status
foreach ($line in $submoduleStatus) {
    $parts = $line.Trim() -split " "
    if ($parts.Count -ge 2) {
        $path = $parts[1]
        if (Test-Path $path) {
            cd $path
            $url = git remote get-url origin
            $commit = git rev-parse HEAD
            $branch = git rev-parse --abbrev-ref HEAD
            cd ..
            $obj = [PSCustomObject]@{
                Path = $path
                URL = $url
                Commit = $commit
                Branch = $branch
            }
            $results.Add($obj)
        }
    }
}
$results | ConvertTo-Json | Out-File "SUBMODULE_INVENTORY.json"
$results | Format-Table -AutoSize | Out-File "STRUCTURAL_MAP.txt"
Write-Host "Inventory and structural map generated."
