Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

function Get-LogDirectory {
  param(
    [Parameter(Mandatory = $true)]
    [string]$StartDirectory
  )

  $currentDir = $StartDirectory
  while ($currentDir -and -not (Test-Path -LiteralPath (Join-Path -Path $currentDir -ChildPath "AI_COORDINATION"))) {
    $parentDir = Split-Path -Parent $currentDir
    if (-not $parentDir -or $parentDir -eq $currentDir) {
      break
    }
    $currentDir = $parentDir
  }

  if ($currentDir -and (Test-Path -LiteralPath (Join-Path -Path $currentDir -ChildPath "AI_COORDINATION"))) {
    $logDir = Join-Path -Path $currentDir -ChildPath "AI_COORDINATION\logs"
  } else {
    $logDir = Join-Path -Path $StartDirectory -ChildPath "logs"
  }

  if (-not (Test-Path -LiteralPath $logDir)) {
    New-Item -Path $logDir -ItemType Directory -Force | Out-Null
  }

  return $logDir
}

function Invoke-ProcessTest {
  param(
    [Parameter(Mandatory = $true)]
    [hashtable]$Test
  )

  if (-not $Test.ContainsKey('Name') -or [string]::IsNullOrWhiteSpace([string]$Test['Name'])) {
    throw "Test definition is missing the 'Name' property."
  }

  if (-not $Test.ContainsKey('FilePath') -or [string]::IsNullOrWhiteSpace([string]$Test['FilePath'])) {
    throw "Test '$($Test['Name'])' is missing the 'FilePath' property."
  }

  $name = [string]$Test['Name']
  $filePath = [string]$Test['FilePath']
  $argumentList = [System.Collections.Generic.List[string]]::new()
  if ($Test.ContainsKey('Arguments') -and $Test['Arguments']) {
    foreach ($argument in @($Test['Arguments'])) {
      $null = $argumentList.Add([string]$argument)
    }
  }
  [string[]]$arguments = $argumentList.ToArray()
  $timeout = if ($Test.ContainsKey('TimeoutSeconds') -and $Test['TimeoutSeconds']) { [int]$Test['TimeoutSeconds'] } else { 120 }
  $workingDirectory = if ($Test.ContainsKey('WorkingDirectory')) { [string]$Test['WorkingDirectory'] } else { $null }
  $skipIfMissing = if ($Test.ContainsKey('SkipIfMissing')) { [bool]$Test['SkipIfMissing'] } else { $false }

  $startTime = Get-Date
  $resolvedFilePath = $null
  $notFoundMessage = $null

  if ([System.IO.Path]::IsPathRooted($filePath)) {
    if (Test-Path -LiteralPath $filePath) {
      $resolvedFilePath = $filePath
    } else {
      $notFoundMessage = "File not found at path '$filePath'."
    }
  } else {
    try {
      $commandInfo = Get-Command -Name $filePath -ErrorAction Stop
      if ($commandInfo.Source) {
        $resolvedFilePath = $commandInfo.Source
      } elseif ($commandInfo.Definition) {
        $resolvedFilePath = $commandInfo.Definition
      } else {
        $resolvedFilePath = $commandInfo.Name
      }
    } catch {
      $notFoundMessage = $_.Exception.Message
    }
  }

  if (-not $resolvedFilePath) {
    $endTime = Get-Date
    return [pscustomobject][ordered]@{
      Name = $name
      Command = $filePath
      ResolvedCommand = $null
      Arguments = @($arguments)
      StartTimestamp = $startTime.ToString("o")
      EndTimestamp = $endTime.ToString("o")
      DurationSeconds = [math]::Round(($endTime - $startTime).TotalSeconds, 3)
      ExitCode = $null
      StdOut = ""
      StdErr = $notFoundMessage
      Status = "NotFound"
      SkipIfMissing = $skipIfMissing
    }
  }

  $stdoutFile = [System.IO.Path]::GetTempFileName()
  $stderrFile = [System.IO.Path]::GetTempFileName()
  $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
  $timedOut = $false
  $exitCode = $null
  $stdOut = ""
  $stdErr = ""
  $errorMessage = $null

  try {
    $startParams = @{
      FilePath = $resolvedFilePath
      ArgumentList = $arguments
      RedirectStandardOutput = $stdoutFile
      RedirectStandardError = $stderrFile
      PassThru = $true
      NoNewWindow = $true
    }
    if ($workingDirectory) {
      $startParams['WorkingDirectory'] = $workingDirectory
    }

    $process = Start-Process @startParams

    if (-not $process.WaitForExit($timeout * 1000)) {
      $timedOut = $true
      try {
        $process.Kill()
      } catch {
      }
      $process.WaitForExit()
    }

    if (-not $timedOut) {
      $exitCode = $process.ExitCode
    }

    if (Test-Path -LiteralPath $stdoutFile) {
      $stdOut = Get-Content -Path $stdoutFile -Raw -ErrorAction SilentlyContinue
    }

    if (Test-Path -LiteralPath $stderrFile) {
      $stdErr = Get-Content -Path $stderrFile -Raw -ErrorAction SilentlyContinue
    }
  } catch {
    $errorMessage = $_.Exception.Message
    if (Test-Path -LiteralPath $stdoutFile) {
      $stdOut = Get-Content -Path $stdoutFile -Raw -ErrorAction SilentlyContinue
    }
    if (Test-Path -LiteralPath $stderrFile) {
      $stdErr = Get-Content -Path $stderrFile -Raw -ErrorAction SilentlyContinue
    }
    if ([string]::IsNullOrWhiteSpace($stdErr)) {
      $stdErr = $errorMessage
    } else {
      $stdErr = ($stdErr + "`n" + $errorMessage).Trim()
    }
  } finally {
    $stopwatch.Stop()
    Remove-Item -Path $stdoutFile, $stderrFile -ErrorAction SilentlyContinue
  }

  $endTime = Get-Date
  $duration = [math]::Round($stopwatch.Elapsed.TotalSeconds, 3)
  $status = if ($timedOut) {
    "Timeout"
  } elseif ($errorMessage) {
    "Failed"
  } elseif ($exitCode -eq 0) {
    "Success"
  } else {
    "Failed"
  }

  return [pscustomobject][ordered]@{
    Name = $name
    Command = $filePath
    ResolvedCommand = $resolvedFilePath
    Arguments = @($arguments)
    StartTimestamp = $startTime.ToString("o")
    EndTimestamp = $endTime.ToString("o")
    DurationSeconds = $duration
    ExitCode = $exitCode
    StdOut = $stdOut
    StdErr = $stdErr
    Status = $status
    SkipIfMissing = $skipIfMissing
  }
}

$scriptDirectory = Split-Path -Parent $MyInvocation.MyCommand.Path
if (-not $scriptDirectory) {
  $scriptDirectory = (Get-Location).ProviderPath
}
$logDirectory = Get-LogDirectory -StartDirectory $scriptDirectory
$scriptLabel = [System.IO.Path]::GetFileNameWithoutExtension($MyInvocation.MyCommand.Name)
$timestamp = Get-Date -Format "yyyyMMdd_HHmmss"
$transcriptPath = Join-Path -Path $logDirectory -ChildPath ("mcp_diagnostic_{0}_{1}.log" -f $scriptLabel, $timestamp)
$transcriptStarted = $false

try {
  Start-Transcript -Path $transcriptPath -Append | Out-Null
  $transcriptStarted = $true

  Write-Host "$(Get-Date -Format o) :: Starting diagnostics for $scriptLabel" -ForegroundColor Cyan

  $results = [System.Collections.Generic.List[pscustomobject]]::new()
  $defaultTimeout = 120

  $tests = @(
    @{ Name = "UV Version"; FilePath = "C:\Users\hyper\.local\bin\uv.exe"; Arguments = @("--version"); TimeoutSeconds = 60 },
    @{ Name = "Python Version"; FilePath = "python"; Arguments = @("--version"); TimeoutSeconds = 60 },
    @{ Name = "Node Version"; FilePath = "node"; Arguments = @("--version"); TimeoutSeconds = 60 },
    @{ Name = "npm Version"; FilePath = "npm"; Arguments = @("--version"); TimeoutSeconds = 60 },
    @{ Name = "npx Version"; FilePath = "npx"; Arguments = @("--version"); TimeoutSeconds = 60 },
    @{ Name = "Filesystem MCP via npx"; FilePath = "cmd.exe"; Arguments = @("/c","npx.cmd","-y","@modelcontextprotocol/server-filesystem","--help") },
    @{ Name = "Sequential Thinking MCP via npx"; FilePath = "cmd.exe"; Arguments = @("/c","npx.cmd","-y","@modelcontextprotocol/server-sequential-thinking","--help") },
    @{ Name = "Memory MCP via npx"; FilePath = "cmd.exe"; Arguments = @("/c","npx.cmd","-y","@modelcontextprotocol/server-memory","--help") },
    @{ Name = "Everything MCP via npx"; FilePath = "cmd.exe"; Arguments = @("/c","npx.cmd","-y","@modelcontextprotocol/server-everything","--help") },
    @{ Name = "Puppeteer MCP via npx"; FilePath = "cmd.exe"; Arguments = @("/c","npx.cmd","-y","puppeteer-mcp-server","--help") },
    @{ Name = "Smart Crawler MCP via npx"; FilePath = "cmd.exe"; Arguments = @("/c","npx.cmd","-y","mcp-smart-crawler","--help") },
    @{ Name = "Playwright MCP via npx"; FilePath = "cmd.exe"; Arguments = @("/c","npx.cmd","-y","@playwright/mcp","--help") },
    @{ Name = "Chrome DevTools MCP via npx"; FilePath = "cmd.exe"; Arguments = @("/c","npx.cmd","-y","chrome-devtools-mcp","--help") },
    @{ Name = "Terry MCP via npx"; FilePath = "cmd.exe"; Arguments = @("/c","npx.cmd","-y","terry-mcp","--help") },
    @{ Name = "Codex MCP via npx"; FilePath = "cmd.exe"; Arguments = @("/c","npx.cmd","-y","codex-mcp-server","--help") },
    @{ Name = "Gemini MCP via npx"; FilePath = "cmd.exe"; Arguments = @("/c","npx.cmd","-y","gemini-mcp-tool","--help") },
    @{ Name = "codex --version"; FilePath = "codex"; Arguments = @("--version"); TimeoutSeconds = 45; SkipIfMissing = $true },
    @{ Name = "copilot --version"; FilePath = "copilot"; Arguments = @("--version"); TimeoutSeconds = 45; SkipIfMissing = $true },
    @{ Name = "gemini --version"; FilePath = "gemini"; Arguments = @("--version"); TimeoutSeconds = 45; SkipIfMissing = $true },
    @{ Name = "grok --version"; FilePath = "grok"; Arguments = @("--version"); TimeoutSeconds = 45; SkipIfMissing = $true },
    @{ Name = "qwen --version"; FilePath = "qwen"; Arguments = @("--version"); TimeoutSeconds = 45; SkipIfMissing = $true },
    @{ Name = "cursor-agent --version"; FilePath = "cursor-agent"; Arguments = @("--version"); TimeoutSeconds = 45; SkipIfMissing = $true }
  )

  foreach ($test in $tests) {
    if (-not $test.ContainsKey('Arguments') -or -not $test['Arguments']) {
      $test['Arguments'] = @()
    }
    if (-not $test.ContainsKey('TimeoutSeconds') -or -not $test['TimeoutSeconds']) {
      $test['TimeoutSeconds'] = $defaultTimeout
    }

    Write-Host "$(Get-Date -Format o) :: Running test '$($test['Name'])'" -ForegroundColor Yellow
    $result = Invoke-ProcessTest -Test $test
    $results.Add($result)
    $statusColor = switch ($result.Status) {
      "Success" { "Green" }
      "Timeout" { "Yellow" }
      "NotFound" { "DarkYellow" }
      default { "Red" }
    }
    Write-Host "$(Get-Date -Format o) :: Completed '$($result.Name)' with status $($result.Status)" -ForegroundColor $statusColor
    if ($result.Status -eq "NotFound" -and $test.ContainsKey('SkipIfMissing') -and $test['SkipIfMissing']) {
      Write-Host "  Optional dependency missing for '$($result.Name)'; continuing." -ForegroundColor DarkYellow
    } elseif ($result.Status -eq "Failed") {
      Write-Host "  stderr: $($result.StdErr)" -ForegroundColor Red
    } elseif ($result.Status -eq "Timeout") {
      Write-Host "  Command exceeded timeout of $($test['TimeoutSeconds']) seconds." -ForegroundColor Yellow
    }
  }

  Write-Host ""
  Write-Host "=== Test Summary ===" -ForegroundColor Cyan
  $summaryTable = $results.ToArray() | Select-Object Name, Status, ExitCode, DurationSeconds | Format-Table -AutoSize | Out-String
  Write-Host $summaryTable

  $statusGroups = $results.ToArray() | Group-Object -Property Status
  foreach ($group in $statusGroups) {
    Write-Host ("{0}: {1}" -f $group.Name, $group.Count) -ForegroundColor White
  }

  $resultsArray = $results.ToArray()
  $summary = [pscustomobject]@{
    Script = $scriptLabel
    GeneratedAt = (Get-Date).ToString("o")
    Results = $resultsArray
  }
  $jsonPath = Join-Path -Path $logDirectory -ChildPath ("mcp_diagnostic_{0}_{1}.json" -f $scriptLabel, $timestamp)
  $summary | ConvertTo-Json -Depth 6 | Out-File -FilePath $jsonPath -Encoding UTF8
  Write-Host "Summary JSON saved to: $jsonPath" -ForegroundColor Green
  Write-Host "Transcript saved to: $transcriptPath" -ForegroundColor Gray
} finally {
  if ($transcriptStarted) {
    try {
      Stop-Transcript | Out-Null
    } catch {
    }
  }
}
