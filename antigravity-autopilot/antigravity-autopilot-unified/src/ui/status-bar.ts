import * as vscode from 'vscode';
import { createLogger } from '../utils/logger';

const log = createLogger('StatusBar');

export interface StatusBarState {
    autoAllEnabled: boolean;
    multiTabEnabled: boolean;
    autonomousEnabled: boolean;
    loopCount: number;
    mode: string;
}

export class StatusBarManager {
    private statusMain: vscode.StatusBarItem;
    private statusSettings: vscode.StatusBarItem;
    private disposed = false;

    constructor(context: vscode.ExtensionContext) {
        // Main Toggle
        this.statusMain = vscode.window.createStatusBarItem(
            vscode.StatusBarAlignment.Right,
            100
        );
        this.statusMain.command = 'antigravity.toggleExtension';
        context.subscriptions.push(this.statusMain);

        // Settings Gear
        this.statusSettings = vscode.window.createStatusBarItem(
            vscode.StatusBarAlignment.Right,
            99
        );
        this.statusSettings.command = 'antigravity.openSettings';
        this.statusSettings.text = '$(gear)';
        this.statusSettings.tooltip = 'Open Antigravity Dashboard';
        context.subscriptions.push(this.statusSettings);

        this.statusMain.show();
        this.statusSettings.show();
        log.info('Status bar initialized');
    }

    update(state: StatusBarState): void {
        if (this.disposed) return;

        if (state.autonomousEnabled) {
            this.statusMain.text = `$(sync~spin) Yoke: ${state.loopCount}`;
            this.statusMain.tooltip = 'Autonomous Mode Running';
            this.statusMain.backgroundColor = new vscode.ThemeColor('statusBarItem.prominentBackground');
        } else if (state.autoAllEnabled) {
            this.statusMain.text = `$(rocket) Yoke: CDP`;
            this.statusMain.tooltip = 'CDP Auto-All Enabled';
            this.statusMain.backgroundColor = undefined;
        } else {
            this.statusMain.text = `$(circle-slash) Yoke: OFF`;
            this.statusMain.tooltip = 'Click to enable';
            this.statusMain.backgroundColor = undefined; // new vscode.ThemeColor('statusBarItem.warningBackground');
        }
    }

    dispose(): void {
        this.disposed = true;
        this.statusMain.dispose();
        this.statusSettings.dispose();
    }
}
