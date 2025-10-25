# Build script for native handshake proxy (Windows)
# Purpose: compile tools_config_files/handshake_proxy.cs into a single-file EXE
# that immediately emits a minimal MCP header, then execs the real server and bridges stdio.
# This helps diagnose/mitigate Codex Windows stdio startup timeouts.

param(
  [string] $ProjectRoot = "$(Split-Path -Parent $PSCommandPath)"
)

$ErrorActionPreference = 'Stop'

function Assert-Cmd($name) {
  try {
    $v = & $name --version 2>$null
  } catch {
    Write-Host "ERROR: '$name' not found on PATH. Install .NET SDK (dotnet) and retry." -ForegroundColor Red
    exit 1
  }
}

# 1) Check dotnet availability
Assert-Cmd dotnet

# 2) Prepare project directories
$ws = (Resolve-Path "$ProjectRoot\..").Path   # workspace root: C:\Users\hyper\fwber
$srcFile = Join-Path $ws "tools_config_files\handshake_proxy.cs"
if (-not (Test-Path -LiteralPath $srcFile)) {
  Write-Host "ERROR: Missing source file: $srcFile" -ForegroundColor Red
  exit 1
}

$projDir = Join-Path $ws "tools_config_files\handshake_proxy"
$outDir  = Join-Path $projDir "out"
if (-not (Test-Path -LiteralPath $projDir)) { New-Item -ItemType Directory -Path $projDir | Out-Null }
if (-not (Test-Path -LiteralPath $outDir))  { New-Item -ItemType Directory -Path $outDir  | Out-Null }

# 3) Create csproj
$csproj = @"
<Project Sdk="Microsoft.NET.Sdk">
  <PropertyGroup>
    <OutputType>Exe</OutputType>
    <TargetFramework>net8.0</TargetFramework>
    <ImplicitUsings>enable</ImplicitUsings>
    <Nullable>disable</Nullable>
    <AssemblyName>handshake_proxy</AssemblyName>
  </PropertyGroup>
</Project>
"@
$csprojPath = Join-Path $projDir "handshake_proxy.csproj"
Set-Content -LiteralPath $csprojPath -Encoding UTF8 -Value $csproj

# 4) Copy source to Program.cs
$programCs = Join-Path $projDir "Program.cs"
Copy-Item -LiteralPath $srcFile -Destination $programCs -Force

# 5) Build (publish single-file, self-contained)
Push-Location $projDir
try {
  & dotnet publish `
    -c Release `
    -r win-x64 `
    --self-contained true `
    -p:PublishSingleFile=true `
    -p:IncludeNativeLibrariesForSelfExtract=true `
    -o $outDir | Out-Null
} finally {
  Pop-Location
}

$exe = Join-Path $outDir "handshake_proxy.exe"
if (-not (Test-Path -LiteralPath $exe)) {
  Write-Host "ERROR: Build finished but no EXE found at: $exe" -ForegroundColor Red
  exit 1
}

Write-Host "SUCCESS: Built $exe" -ForegroundColor Green
Write-Host ""
Write-Host "Next steps:" -ForegroundColor Yellow
Write-Host "1) Canary test outside Codex (Ctrl+C to stop):" -ForegroundColor Yellow
Write-Host "   & `"$exe`" C:\Progra~1\nodejs\mcp-server-stdio-test.cmd stdio"
Write-Host "2) Update C:\Users\hyper\.codex\config.toml using stanzas in:" -ForegroundColor Yellow
Write-Host "   tools_config_files\codex_handshake_proxy_stanzas.toml" -ForegroundColor Yellow
Write-Host "3) Verify:" -ForegroundColor Yellow
Write-Host "   codex mcp list" -ForegroundColor Yellow
Write-Host "   codex mcp get stdio-test" -ForegroundColor Yellow