param(
  [Parameter(Mandatory = $true, Position = 0)]
  [string] $Package,
  [Parameter(ValueFromRemainingArguments = $true, Position = 1)]
  [string[]] $ExtraArgs
)

# IMPORTANT: Do not emit any output before the MCP server starts its JSON-RPC handshake.
# This wrapper reliably launches npx.cmd on Windows under CreateProcess, inheriting stdio.

$ErrorActionPreference = 'Stop'
try {
  # Prefer an absolute path; fall back to env/where if needed
  $npx = 'C:\Program Files\nodejs\npx.cmd'
  if ($env:NPX_CMD -and (Test-Path -LiteralPath $env:NPX_CMD)) {
    $npx = $env:NPX_CMD
  } elseif (-not (Test-Path -LiteralPath $npx)) {
    $found = (Get-Command npx -ErrorAction SilentlyContinue)
    if ($found) {
      $npx = $found.Source
    }
  }
  if (-not (Test-Path -LiteralPath $npx)) {
    # Emit only a minimal error if we truly cannot launch
    [Console]::Error.WriteLine('npx not found. Set NPX_CMD or install Node.js.')
    exit 127
  }

  # PowerShell 7+: ensure native arg passing (ignored on WindowsPowerShell)
  try { $PSNativeCommandArgumentPassing = 'Standard' } catch {}

  # Launch npx.cmd with inherited stdio; do not prepend any extra output
  & $npx -y $Package @ExtraArgs
  exit $LASTEXITCODE
}
catch {
  # Emit only the message to stderr and exit non-zero
  [Console]::Error.WriteLine($_.Exception.Message)
  exit 1
}