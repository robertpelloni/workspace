<#
.SYNOPSIS
    Omni-Workspace Control Center — Native Windows System Tray Controller (v2.0.0 / v5.293.0)
.DESCRIPTION
    Provides a native Windows System.Windows.Forms.NotifyIcon tray application for
    monitoring and controlling the Omni-Workspace Control Center (:2999), HyperNexus (:7779),
    Jules Autopilot (:3006), and the 10 Go binary daemons at BelowNormal CPU priority.
    Supports --status for non-interactive CLI health checks.
#>

param(
    [switch]$StatusOnly
)

$ErrorActionPreference = "SilentlyContinue"
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
$WorkspaceRoot = Resolve-Path (Join-Path $ScriptDir "..\..") | Select-Object -ExpandProperty Path
$ControlUrl = "http://127.0.0.1:2999"

function Get-ControlCenterOverview {
    try {
        $wc = New-Object System.Net.WebClient
        $wc.Encoding = [System.Text.Encoding]::UTF8
        $raw = $wc.DownloadString("$ControlUrl/api/overview")
        return ($raw | ConvertFrom-Json)
    } catch {
        return $null
    }
}

function Start-ControlCenterBackend {
    $ov = Get-ControlCenterOverview
    if ($null -ne $ov) { return $true }
    $proc = Start-Process -FilePath "node" -ArgumentList "server/index.js" -WorkingDirectory $ScriptDir -WindowStyle Hidden -PassThru
    if ($proc -and $proc.Id) {
        try {
            $p = Get-Process -Id $proc.Id -ErrorAction SilentlyContinue
            if ($p) { $p.PriorityClass = "BelowNormal" }
        } catch {}
    }
    Start-Sleep -Milliseconds 1200
    return ($null -ne (Get-ControlCenterOverview))
}

function Stop-ControlCenterBackend {
    try {
        Invoke-RestMethod -Uri "$ControlUrl/api/shutdown" -Method Post -TimeoutSec 2 | Out-Null
    } catch {}
}

if ($StatusOnly -or ($args -contains "--status")) {
    $ov = Get-ControlCenterOverview
    if ($null -eq $ov) {
        Write-Output "Control Center (:2999): OFFLINE"
        exit 1
    } else {
        $portsOnline = @($ov.ports | Where-Object { $_.online }).Count
        $portsTotal = @($ov.ports).Count
        Write-Output ("Omni-Workspace {0} | Ports: {1}/{2} | Go Daemons: {3}/{4} running ({5} built) | Submodules: {6}/{7}" -f `
            $ov.version, $portsOnline, $portsTotal, $ov.goServicesRunning, $ov.goServicesTotal, $ov.goServicesBuilt, $ov.submodulesInitialized, $ov.submodulesTotal)
        exit 0
    }
}

Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing

# Lower our own tray PowerShell process priority to BelowNormal
try {
    (Get-Process -Id $PID).PriorityClass = "BelowNormal"
} catch {}

# Prevent duplicate tray instances using a named mutex
$createdNew = $false
$mutex = New-Object System.Threading.Mutex($true, "Global\OmniWorkspaceControlTrayMutex", [ref]$createdNew)
if (-not $createdNew) {
    exit 0
}

function New-TrayIcon {
    param([bool]$Online = $true)
    $bmp = New-Object System.Drawing.Bitmap(32, 32)
    $g = [System.Drawing.Graphics]::FromImage($bmp)
    $g.SmoothingMode = [System.Drawing.Drawing2D.SmoothingMode]::AntiAlias
    $bgBrush = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::FromArgb(255, 13, 19, 33))
    $g.FillEllipse($bgBrush, 1, 1, 30, 30)

    $ringColor = if ($Online) { [System.Drawing.Color]::FromArgb(255, 56, 189, 248) } else { [System.Drawing.Color]::FromArgb(255, 244, 63, 94) }
    $ringPen = New-Object System.Drawing.Pen($ringColor, 2.5)
    $g.DrawEllipse($ringPen, 2, 2, 28, 28)

    $dotColor = if ($Online) { [System.Drawing.Color]::FromArgb(255, 16, 185, 129) } else { [System.Drawing.Color]::FromArgb(255, 245, 158, 11) }
    $dotBrush = New-Object System.Drawing.SolidBrush($dotColor)
    $g.FillEllipse($dotBrush, 10, 10, 12, 12)

    $g.Dispose()
    $bgBrush.Dispose()
    $ringPen.Dispose()
    $dotBrush.Dispose()
    return [System.Drawing.Icon]::FromHandle($bmp.GetHicon())
}

$notifyIcon = New-Object System.Windows.Forms.NotifyIcon
$notifyIcon.Icon = New-TrayIcon -Online $true
$notifyIcon.Text = "Omni-Workspace Control Center (:2999)"
$notifyIcon.Visible = $true

$contextMenu = New-Object System.Windows.Forms.ContextMenuStrip

$headerItem = New-Object System.Windows.Forms.ToolStripMenuItem("Omni-Workspace Control Center")
$headerItem.Enabled = $false
$statusItem = New-Object System.Windows.Forms.ToolStripMenuItem("Checking status...")
$statusItem.Enabled = $false

$openControlItem = New-Object System.Windows.Forms.ToolStripMenuItem("Open Control Center (:2999)")
$openControlItem.Add_Click({
    Start-ControlCenterBackend | Out-Null
    Start-Process "$ControlUrl"
})

$openHyperNexusItem = New-Object System.Windows.Forms.ToolStripMenuItem("Open HyperNexus Web UI (:7779)")
$openHyperNexusItem.Add_Click({ Start-Process "http://localhost:7779" })

$openJulesItem = New-Object System.Windows.Forms.ToolStripMenuItem("Open Jules Autopilot (:3006)")
$openJulesItem.Add_Click({ Start-Process "http://localhost:3006" })

$startBackendItem = New-Object System.Windows.Forms.ToolStripMenuItem("Start / Restart Backend (:2999, BelowNormal)")
$startBackendItem.Add_Click({
    Stop-ControlCenterBackend
    Start-Sleep -Milliseconds 500
    Start-ControlCenterBackend | Out-Null
})

$startGoAllItem = New-Object System.Windows.Forms.ToolStripMenuItem("Start All 10 Go Services (BelowNormal)")
$startGoAllItem.Add_Click({
    Start-ControlCenterBackend | Out-Null
    try {
        Invoke-RestMethod -Uri "$ControlUrl/api/go-services/start" -Method Post -ContentType "application/json" -Body '{"id":"all"}' -TimeoutSec 5 | Out-Null
    } catch {}
})

$stopGoAllItem = New-Object System.Windows.Forms.ToolStripMenuItem("Stop All 10 Go Services")
$stopGoAllItem.Add_Click({
    try {
        Invoke-RestMethod -Uri "$ControlUrl/api/go-services/stop" -Method Post -ContentType "application/json" -Body '{"id":"all"}' -TimeoutSec 5 | Out-Null
    } catch {
        Start-Process -FilePath (Join-Path $WorkspaceRoot "start.bat") -ArgumentList "stop" -WindowStyle Hidden
    }
})

$stopBackendItem = New-Object System.Windows.Forms.ToolStripMenuItem("Stop Backend (:2999)")
$stopBackendItem.Add_Click({ Stop-ControlCenterBackend })

$quitAllItem = New-Object System.Windows.Forms.ToolStripMenuItem("Quit System Tray & Shutdown Backend")
$quitAllItem.Add_Click({
    $timer.Stop()
    Stop-ControlCenterBackend
    $notifyIcon.Visible = $false
    $notifyIcon.Dispose()
    $mutex.ReleaseMutex()
    [System.Windows.Forms.Application]::Exit()
})

$exitTrayOnlyItem = New-Object System.Windows.Forms.ToolStripMenuItem("Close Tray Icon Only (Keep Backend Running)")
$exitTrayOnlyItem.Add_Click({
    $timer.Stop()
    $notifyIcon.Visible = $false
    $notifyIcon.Dispose()
    $mutex.ReleaseMutex()
    [System.Windows.Forms.Application]::Exit()
})

[void]$contextMenu.Items.Add($headerItem)
[void]$contextMenu.Items.Add($statusItem)
[void]$contextMenu.Items.Add((New-Object System.Windows.Forms.ToolStripSeparator))
[void]$contextMenu.Items.Add($openControlItem)
[void]$contextMenu.Items.Add($openHyperNexusItem)
[void]$contextMenu.Items.Add($openJulesItem)
[void]$contextMenu.Items.Add((New-Object System.Windows.Forms.ToolStripSeparator))
[void]$contextMenu.Items.Add($startBackendItem)
[void]$contextMenu.Items.Add($startGoAllItem)
[void]$contextMenu.Items.Add($stopGoAllItem)
[void]$contextMenu.Items.Add($stopBackendItem)
[void]$contextMenu.Items.Add((New-Object System.Windows.Forms.ToolStripSeparator))
[void]$contextMenu.Items.Add($exitTrayOnlyItem)
[void]$contextMenu.Items.Add($quitAllItem)

$notifyIcon.ContextMenuStrip = $contextMenu
$notifyIcon.Add_DoubleClick({
    Start-ControlCenterBackend | Out-Null
    Start-Process "$ControlUrl"
})

function Update-TrayTelemetry {
    $ov = Get-ControlCenterOverview
    if ($null -ne $ov) {
        $portsOnline = @($ov.ports | Where-Object { $_.online }).Count
        $portsTotal = @($ov.ports).Count
        $tip = ("Omni {0} | Ports:{1}/{2} | Go:{3}/{4}" -f $ov.version, $portsOnline, $portsTotal, $ov.goServicesRunning, $ov.goServicesTotal)
        if ($tip.Length -gt 63) { $tip = $tip.Substring(0, 63) }
        $notifyIcon.Text = $tip
        $statusItem.Text = ("ONLINE — {0} | Ports {1}/{2} | Go {3}/{4}" -f $ov.version, $portsOnline, $portsTotal, $ov.goServicesRunning, $ov.goServicesTotal)
        $notifyIcon.Icon = New-TrayIcon -Online $true
    } else {
        $notifyIcon.Text = "Omni-Workspace (:2999 Offline)"
        $statusItem.Text = "OFFLINE — Click 'Start / Restart Backend'"
        $notifyIcon.Icon = New-TrayIcon -Online $false
    }
}

# Ensure backend is online at tray startup
Start-ControlCenterBackend | Out-Null
Update-TrayTelemetry

$timer = New-Object System.Windows.Forms.Timer
$timer.Interval = 10000
$timer.Add_Tick({ Update-TrayTelemetry })
$timer.Start()

[System.Windows.Forms.Application]::Run()
