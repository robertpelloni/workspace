import * as vscode from 'vscode';
import { config } from '../utils/config';

export class DashboardPanel {
    public static currentPanel: DashboardPanel | undefined;
    private readonly _panel: vscode.WebviewPanel;
    private readonly _extensionUri: vscode.Uri;
    private _disposables: vscode.Disposable[] = [];

    private constructor(panel: vscode.WebviewPanel, extensionUri: vscode.Uri) {
        this._panel = panel;
        this._extensionUri = extensionUri;

        this._update();
        this._panel.onDidDispose(() => this.dispose(), null, this._disposables);
    }

    public static createOrShow(extensionUri: vscode.Uri) {
        const column = vscode.window.activeTextEditor
            ? vscode.window.activeTextEditor.viewColumn
            : undefined;

        if (DashboardPanel.currentPanel) {
            DashboardPanel.currentPanel._panel.reveal(column);
            return;
        }

        const panel = vscode.window.createWebviewPanel(
            'antigravityDashboard',
            'Antigravity Dashboard',
            column || vscode.ViewColumn.One,
            {
                enableScripts: true,
                localResourceRoots: [vscode.Uri.joinPath(extensionUri, 'media')]
            }
        );

        DashboardPanel.currentPanel = new DashboardPanel(panel, extensionUri);
    }

    public dispose() {
        DashboardPanel.currentPanel = undefined;
        this._panel.dispose();
        while (this._disposables.length) {
            const x = this._disposables.pop();
            if (x) {
                x.dispose();
            }
        }
    }

    private _update() {
        const webview = this._panel.webview;
        this._panel.title = 'Antigravity Settings';
        this._panel.webview.html = this._getHtmlForWebview(webview);
    }

    private _getHtmlForWebview(webview: vscode.Webview) {
        const settings = config.getAll(); // Ensure config.getAll() is public

        // Simple HTML for now
        return `<!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>Antigravity Dashboard</title>
            <style>
                body { font-family: sans-serif; padding: 20px; }
                h1 { color: var(--vscode-editor-foreground); }
                .card { background: var(--vscode-editor-background); border: 1px solid var(--vscode-widget-border); padding: 15px; margin-bottom: 10px; border-radius: 5px; }
                .setting { margin-bottom: 10px; display: flex; justify-content: space-between; align-items: center; }
                label { font-weight: bold; }
            </style>
        </head>
        <body>
            <h1>Antigravity Autopilot</h1>
            <div class="card">
                <h2>Strategies</h2>
                <div class="setting">
                    <label>Current Strategy:</label>
                    <span>${settings.strategy.toUpperCase()}</span>
                </div>
                <div class="setting">
                    <label>Auto-Accept:</label>
                    <span>${settings.autoAcceptEnabled ? 'ON' : 'OFF'}</span>
                </div>
                <div class="setting">
                    <label>Auto-All (CDP):</label>
                    <span>${settings.autoAllEnabled ? 'ON' : 'OFF'}</span>
                </div>
            </div>
             <div class="card">
                <h2>Modules</h2>
                <div class="setting">
                    <label>Autonomous Mode:</label>
                    <span>${settings.autonomousEnabled ? 'ON' : 'OFF'}</span>
                </div>
                 <div class="setting">
                    <label>MCP Server:</label>
                    <span>${settings.mcpEnabled ? 'ON' : 'OFF'}</span>
                </div>
                 <div class="setting">
                    <label>Voice Control:</label>
                    <span>${settings.voiceControlEnabled ? 'ON' : 'OFF'}</span>
                </div>
            </div>
            <p>Use VS Code Settings (Ctrl+,) to configure advanced options.</p>
        </body>
        </html>`;
    }
}
