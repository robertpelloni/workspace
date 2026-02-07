
import * as vscode from 'vscode';
import * as path from 'path';
import { DashboardPanel } from './ui/dashboard';
import { config } from './utils/config';
import { createLogger } from './utils/logger';
import { autonomousLoop } from './core/autonomous-loop';
// import { circuitBreaker } from './core/circuit-breaker'; // Removed unused import
import { progressTracker } from './core/progress-tracker';
import { mcpServer } from './modules/mcp/server';
import { voiceControl } from './modules/voice/control';
import { CDPHandler } from './services/cdp/cdp-handler';
import { StrategyManager } from './strategies/manager';

import { StatusBarManager } from './ui/status-bar';

const log = createLogger('Extension');
let statusBar: StatusBarManager;

export function activate(context: vscode.ExtensionContext) {
    log.info('Antigravity Autopilot (Unified) activating...');

    // Initialize UI
    statusBar = new StatusBarManager(context);

    // Initialize Managers
    const strategyManager = new StrategyManager(context);

    // Wire up Status Bar to Autonomous Loop
    autonomousLoop.setStatusCallback(status => {
        statusBar.update({
            autonomousEnabled: status.running,
            loopCount: status.loopCount,
            autoAllEnabled: config.get('autoAllEnabled'),
            multiTabEnabled: config.get('multiTabEnabled'),
            mode: config.get('strategy')
        });
    });

    // Update Status Bar on Config Change
    vscode.workspace.onDidChangeConfiguration(e => {
        if (e.affectsConfiguration('antigravity')) {
            statusBar.update({
                autonomousEnabled: autonomousLoop.isRunning(),
                loopCount: 0, // We assume loop count preserves or resets? 
                autoAllEnabled: config.get('autoAllEnabled'),
                multiTabEnabled: config.get('multiTabEnabled'),
                mode: config.get('strategy')
            });
        }
    });

    // Initial Status Update
    statusBar.update({
        autonomousEnabled: autonomousLoop.isRunning(),
        loopCount: 0,
        autoAllEnabled: config.get('autoAllEnabled'),
        multiTabEnabled: config.get('multiTabEnabled'),
        mode: config.get('strategy')
    });

    // Register Commands
    context.subscriptions.push(
        vscode.commands.registerCommand('antigravity.toggleExtension', async () => {
            await strategyManager.toggle();
            // Status bar update triggered by config listener or loop callback
        }),
        vscode.commands.registerCommand('antigravity.toggleAutoAccept', async () => {
            await config.update('autoAcceptEnabled', !config.get('autoAcceptEnabled'));
            await strategyManager.start();
        }),
        vscode.commands.registerCommand('antigravity.toggleAutoAll', async () => {
            const current = config.get<boolean>('autoAllEnabled');
            await config.update('autoAllEnabled', !current);
            if (!current) {
                await config.update('strategy', 'cdp');
            }
            await strategyManager.start();
        }),
        vscode.commands.registerCommand('antigravity.toggleAutonomous', async () => {
            const isRunning = autonomousLoop.isRunning();
            if (isRunning) {
                autonomousLoop.stop('User toggled off');
                await config.update('autonomousEnabled', false);
            } else {
                await autonomousLoop.start();
                await config.update('autonomousEnabled', true);
            }
        }),
        vscode.commands.registerCommand('antigravity.openSettings', () => {
            DashboardPanel.createOrShow(context.extensionUri);
        }),
        vscode.commands.registerCommand('antigravity.toggleMcp', async () => {
            const current = config.get<boolean>('mcpEnabled');
            if (current) {
                await mcpServer.stop();
            } else {
                await mcpServer.start();
            }
            await config.update('mcpEnabled', !current);
        }),
        vscode.commands.registerCommand('antigravity.toggleVoice', async () => {
            const current = config.get<boolean>('voiceControlEnabled');
            if (current) {
                await voiceControl.stop();
            } else {
                await voiceControl.start();
            }
            await config.update('voiceControlEnabled', !current);
        })
    );

    // Initialize based on saved config
    // 1. Strategy (Core Driver)
    if (config.get('autoAllEnabled') || config.get('autoAcceptEnabled')) {
        strategyManager.start().catch(e => log.error(`Failed to start strategy: ${e.message}`));
    }

    // 2. Autonomous Loop
    if (config.get('autonomousEnabled')) {
        autonomousLoop.start().catch(e => log.error(`Failed to start autonomous loop: ${e.message}`));
    }

    // 3. Modules
    if (config.get('mcpEnabled')) {
        mcpServer.start().catch(e => log.error(`MCP start failed: ${e.message}`));
    }
    if (config.get('voiceControlEnabled')) {
        voiceControl.start().catch(e => log.error(`Voice start failed: ${e.message}`));
    }

    log.info('Antigravity Autopilot activated!');
}

export function deactivate() {
    autonomousLoop.stop('Deactivating');
    mcpServer.stop();
    voiceControl.stop();
    if (statusBar) statusBar.dispose();
    log.info('Antigravity Autopilot deactivated');
}
