# Deployment: FreeLLM (Go)

## Prerequisites
- Windows 10/11
- Go 1.21+ (for building from source)

## Building from Source
1. Clone the repository and submodules.
2. Initialize Go modules:
   ```bash
   go mod tidy
   ```
3. Build the application:
   ```bash
   go build -o FreeLLMControlPanel.exe .
   ```

## Development
- Run `go run .` to start the tray application in development mode.
- The app uses `provider_metrics.db` (SQLite) for data persistence.

## Packaging
To create a production build with no console window:
```bash
go build -ldflags -H=windowsgui -o FreeLLMControlPanel.exe .
```

## Startup Integration
Configurable via the system tray menu; adds a registry key to `HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run`.
