param(
  [Parameter(Mandatory = $true, Position = 0)]
  [string] $Exe,
  [Parameter(ValueFromRemainingArguments = $true, Position = 1)]
  [string[]] $Args
)

# Quiet stdio proxy for Windows:
# - Starts the target EXE with args
# - For stdout: suppresses any preamble until it detects the start of the MCP handshake
#   (first occurrence of 'Content-Length:' or 'Content-Type:' or the first '{'),
#   then streams all subsequent bytes verbatim to our own stdout.
# - For stdin: forwards raw bytes from our stdin to the child stdin.
# - For stderr: writes child stderr through unchanged (safe for logs).
# IMPORTANT: Do not write anything to stdout before handshake detection, or Codex will time out.

$ErrorActionPreference = 'Stop'

# Logging to TEMP by default (no stdout noise)
$global:MCP_CMD_QUIET_LOG = $env:MCP_PS_LOG
if ([string]::IsNullOrWhiteSpace($global:MCP_CMD_QUIET_LOG)) {
  try { $global:MCP_CMD_QUIET_LOG = Join-Path $env:TEMP 'mcp_cmd_quiet.log' } catch { $global:MCP_CMD_QUIET_LOG = $null }
}
function Write-Log([string]$msg) {
  if (-not $global:MCP_CMD_QUIET_LOG) { return }
  try {
    $ts = (Get-Date).ToString('s')
    Add-Content -Path $global:MCP_CMD_QUIET_LOG -Value "$ts $msg"
  } catch { }
}
Write-Log "START exe='$Exe' args='$([string]::Join(' ', $Args))'"

# Build ProcessStartInfo
$psi = New-Object System.Diagnostics.ProcessStartInfo
$psi.FileName = $Exe
$psi.Arguments = [string]::Join(' ', $Args)
$psi.UseShellExecute = $false
$psi.RedirectStandardInput = $true
$psi.RedirectStandardOutput = $true
$psi.RedirectStandardError = $true
$psi.CreateNoWindow = $true

$proc = New-Object System.Diagnostics.Process
$proc.StartInfo = $psi

# Start child
[void]$proc.Start()
Write-Log ("PROCESS STARTED pid=" + $proc.Id)
Write-Log ("PROCESS STARTED pid=" + $proc.Id)
Write-Log ("PROCESS STARTED pid=" + $proc.Id)

# Async: forward stderr directly
$stderrReader = New-Object System.IO.StreamReader($proc.StandardError.BaseStream, [System.Text.Encoding]::UTF8, $true, 4096, $false)
$null = [System.Threading.Tasks.Task]::Run([System.Action]{
  try {
    while (-not $stderrReader.EndOfStream) {
      $line = $stderrReader.ReadLine()
      if ($null -ne $line) {
        Write-Log ("STDERR " + $line)
        [Console]::Error.WriteLine($line)
      }
    }
  } catch { }
})

# Async: forward stdin raw bytes to child stdin
$stdinStream = [Console]::OpenStandardInput()
$childStdin = $proc.StandardInput.BaseStream
$null = [System.Threading.Tasks.Task]::Run([System.Action]{
  $buf = New-Object byte[] 8192
  try {
    while ($true) {
      $read = $stdinStream.Read($buf, 0, $buf.Length)
      if ($read -le 0) { break }
      Write-Log ("STDIN bytes=" + $read)
      $childStdin.Write($buf, 0, $read)
      $childStdin.Flush()
    }
  } catch { } finally {
    try { $childStdin.Flush() } catch {}
    try { $childStdin.Dispose() } catch {}
  }
})

# Main thread: read stdout and gate until handshake
$childStdout = $proc.StandardOutput.BaseStream
$parentStdout = [Console]::OpenStandardOutput()
$buffer = New-Object System.IO.MemoryStream
$gateOpened = $false
function Detect-HeadersStart {
  param([byte[]] $bytes)
  # Use ISO-8859-1 for header scan (ASCII superset)
  $enc = [System.Text.Encoding]::GetEncoding(28591)
  $txt = $enc.GetString($bytes)
  $low = $txt.ToLowerInvariant()
  $cl = $low.IndexOf('content-length:')
  $ct = $low.IndexOf('content-type:')
  $idx = -1
  if ($cl -ge 0 -and $ct -ge 0) {
    $idx = [Math]::Min($cl, $ct)
  } elseif ($cl -ge 0) {
    $idx = $cl
  } elseif ($ct -ge 0) {
    $idx = $ct
  }
  if ($idx -ge 0) { return $idx }
  # If JSON starts right away
  $brace = $txt.IndexOf('{')
  if ($brace -ge 0) { return $brace }
  # Detect header terminator CRLFCRLF
  $sep = $low.IndexOf("`r`n`r`n")
  if ($sep -ge 0) {
    for ($i = 0; $i -lt $low.Length; $i++) {
      $c = $low[$i]
      if ($c -ne "`r"[0] -and $c -ne "`n"[0] -and $c -ne ' '[0] -and $c -ne "`t"[0]) { return $i }
    }
  }
  return -1
}

$readBuf = New-Object byte[] 8192
try {
  while ($true) {
    $n = $childStdout.Read($readBuf, 0, $readBuf.Length)
    if ($n -le 0) { break }
    Write-Log ("STDOUT bytes=" + $n + " gateOpened=" + $gateOpened)
    if ($gateOpened) {
      $parentStdout.Write($readBuf, 0, $n)
      $parentStdout.Flush()
    } else {
      $buffer.Write($readBuf, 0, $n) | Out-Null
      $bytes = $buffer.ToArray()
      $idx = Detect-HeadersStart $bytes
      if ($idx -ge 0) {
        $gateOpened = $true
        $parentStdout.Write($bytes, $idx, $bytes.Length - $idx)
        $parentStdout.Flush()
        Write-Log ("HANDSHAKE OPEN idx=" + $idx + " emitted=" + ($bytes.Length - $idx))
        $buffer.SetLength(0)
      } elseif ($buffer.Length -gt 65536) {
        # avoid unbounded growth
        $tail = $buffer.ToArray()
        $buffer.SetLength(0)
        $keep = [Math]::Min(16384, $tail.Length)
        $buffer.Write($tail, $tail.Length - $keep, $keep) | Out-Null
      }
    }
  }
} catch { }

# Wait for process to exit and propagate exit code
$proc.WaitForExit()
$exit = $proc.ExitCode
Write-Log ("EXIT code=" + $exit)
exit ($exit)