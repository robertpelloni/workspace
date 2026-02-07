$submodules = git submodule status --recursive
$output = "# Submodule Dashboard`n`nThis project uses a large number of git submodules located in the lib/ directory.`n`n## Project Structure`n*   src/: Main source code.`n*   lib/: External libraries and submodules.`n*   data/: Runtime assets.`n*   cmake/: CMake configuration.`n`n## Submodules List`n`n| Path | URL | Version | Date |`n|---|---|---|---|"

foreach ($line in $submodules) {
    if ($line -match "^\s*[-+]?([0-9a-f]+)\s+(.*?)(\s+\(.*\))?$") {
        $commit = $matches[1]
        $path = $matches[2]
        # Get URL from .gitmodules or git config
        $url = git config --file .gitmodules --get submodule.$path.url
        if (-not $url) {
            $url = git -C $path remote get-url origin
        }
        
        # Get date
        if (Test-Path $path) {
            $date = git -C $path show -s --format=%cd --date=short $commit
            $output += "`n| $path | $url | $commit | $date |"
        }
    }
}

$output | Out-File SUBMODULES.md -Encoding utf8
Write-Host "SUBMODULES.md updated."
