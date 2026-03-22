$processes = @(
    "node",
    "pnpm",
    "OpenConsole",
    "cmdhost",
    "conhost",
    "cmd",
    "bun",
    "uv",
    "pwsh",
    "WindowsTerminal"
)

foreach ($proc in $processes) {
    Write-Host "Attempting to kill $proc..." -ForegroundColor Yellow
    Get-Process -Name $proc -ErrorAction SilentlyContinue | Stop-Process -Force -ErrorAction SilentlyContinue
}

Write-Host "Workspace reset complete." -ForegroundColor Green
