import * as vscode from 'vscode';
import { IStrategy } from './interface';
import { config } from '../utils/config';

export class SimpleStrategy implements IStrategy {
    name = 'Simple Strategy';
    isActive = false;
    private intervalParams: NodeJS.Timeout | null = null;
    private statusBarItem: vscode.StatusBarItem;

    constructor() {
        this.statusBarItem = vscode.window.createStatusBarItem(vscode.StatusBarAlignment.Right, 10000);
        this.statusBarItem.command = 'antigravity.toggleAutoAccept';
    }

    async start(): Promise<void> {
        if (this.isActive) return;
        this.isActive = true;
        this.updateStatusBar();

        const frequency = config.get<number>('pollFrequency') || 1000;
        console.log(`[SimpleStrategy] Starting with frequency: ${frequency}ms`);

        this.intervalParams = setInterval(async () => {
            if (!this.isActive) return;
            try {
                // Try executing the standard Antigravity accept command
                await vscode.commands.executeCommand('antigravity.agent.acceptAgentStep');
            } catch (e) {
                // Command might not be available if valid editor is not focused, ignore
            }
            try {
                // Also try accepting terminal commands if any
                await vscode.commands.executeCommand('antigravity.terminal.accept');
            } catch (e) { }
        }, frequency);

        vscode.window.showInformationMessage('Antigravity: Auto-Accept ON (Simple Mode)');
    }

    async stop(): Promise<void> {
        if (!this.isActive) return;
        this.isActive = false;
        if (this.intervalParams) {
            clearInterval(this.intervalParams);
            this.intervalParams = null;
        }
        this.updateStatusBar();
        vscode.window.showInformationMessage('Antigravity: Auto-Accept OFF');
    }

    private updateStatusBar() {
        if (this.isActive) {
            this.statusBarItem.text = "$(check) Auto-Accept: ON";
            this.statusBarItem.tooltip = "Click to Pause Auto-Accept";
            this.statusBarItem.backgroundColor = undefined;
        } else {
            this.statusBarItem.text = "$(circle-slash) Auto-Accept: OFF";
            this.statusBarItem.tooltip = "Click to Enable Auto-Accept";
            this.statusBarItem.backgroundColor = new vscode.ThemeColor('statusBarItem.warningBackground');
        }
        this.statusBarItem.show();
    }

    dispose() {
        this.stop();
        this.statusBarItem.dispose();
    }
}
