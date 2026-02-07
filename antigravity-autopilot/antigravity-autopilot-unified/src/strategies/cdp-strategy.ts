import * as vscode from 'vscode';
import { IStrategy } from './interface';
import { CDPHandler } from '../services/cdp/cdp-handler';
// @ts-ignore
import { Relauncher } from '../../main_scripts/relauncher.js'; // Requires JS import in TS if generic
import { config } from '../utils/config';
import * as path from 'path';
import * as fs from 'fs';

export class CDPStrategy implements IStrategy {
    name = 'CDP Strategy';
    isActive = false;
    private cdpHandler: CDPHandler;
    private relauncher: any; // Relauncher is JS class
    private statusBarItem: vscode.StatusBarItem;
    private pollTimer: NodeJS.Timeout | null = null;
    private logger: (msg: string) => void;

    constructor() {
        this.cdpHandler = new CDPHandler();
        // Dynamic import or require for JS module if needed, but standard import should work with allowJs
        const { Relauncher } = require('../../main_scripts/relauncher.js');
        this.relauncher = new Relauncher();

        this.logger = (msg: string) => console.log(`[CDPStrategy] ${msg}`);

        this.statusBarItem = vscode.window.createStatusBarItem(vscode.StatusBarAlignment.Right, 10000);
        this.statusBarItem.command = 'antigravity.toggleAutoAccept';
    }

    async start(): Promise<void> {
        if (this.isActive) return;

        // 1. Check if CDP is available
        const isCdpRunning = await this.relauncher.isCDPRunning();
        if (!isCdpRunning) {
            const result = await this.relauncher.showRelaunchPrompt();
            if (result !== 'relaunched') {
                vscode.window.showWarningMessage('Antigravity: CDP Mode requires a relaunch to function.');
                return;
            }
            // If relaunched, the extension will restart, so we return here.
            return;
        }

        // 2. Start CDP Handler
        this.isActive = true;
        this.updateStatusBar();

        try {
            const ide = vscode.env.appName.toLowerCase().includes('cursor') ? 'cursor' : 'antigravity';
            const scriptPath = path.join(__dirname, '..', '..', 'main_scripts', 'full_cdp_script.js');
            const scriptContent = fs.readFileSync(scriptPath, 'utf8');

            // Initial connection
            await this.connectAndInject(scriptContent, ide);

            // 3. Start Polling Loop to ensure all tabs are injected
            const pollFreq = config.get<number>('pollFrequency') || 2000;
            this.pollTimer = setInterval(async () => {
                await this.connectAndInject(scriptContent, ide);
            }, 5000); // Check for new tabs every 5s

            vscode.window.showInformationMessage('Antigravity: Auto-All ON (CDP Mode) 🚀');

        } catch (e: any) {
            this.isActive = false;
            this.updateStatusBar();
            vscode.window.showErrorMessage(`Antigravity CDP Error: ${e.message}`);
        }
    }

    private async connectAndInject(script: string, ide: string) {
        // Scan and connect to all pages
        const instances = await this.cdpHandler.scanForInstances();
        for (const instance of instances) {
            for (const page of instance.pages) {
                const connected = await this.cdpHandler.connectToPage(page);
                if (connected) {
                    await this.cdpHandler.injectScript(page.id, script);

                    // Send Start Command
                    await this.cdpHandler.sendCommand(page.id, 'Runtime.evaluate', {
                        expression: `(function(){
                            const g = (typeof window !== 'undefined') ? window : self;
                            if(g && g.__autoAllStart){
                                g.__autoAllStart({
                                    ide: '${ide}',
                                    isPro: true,
                                    isBackgroundMode: ${config.get('multiTabEnabled')},
                                    pollInterval: ${config.get('pollFrequency')},
                                    bannedCommands: ${JSON.stringify(config.get('bannedCommands'))},
                                    threadWaitInterval: ${config.get('threadWaitInterval')},
                                    autoApproveDelay: ${config.get('autoApproveDelay')},
                                    bumpMessage: "${config.get('bumpMessage') || 'bump'}"
                                });
                            }
                        })()`
                    });
                }
            }
        }
    }

    async stop(): Promise<void> {
        if (!this.isActive) return;
        this.isActive = false;

        if (this.pollTimer) {
            clearInterval(this.pollTimer);
            this.pollTimer = null;
        }

        // Send Stop Command to all pages
        const instances = await this.cdpHandler.scanForInstances(); // Get current pages
        for (const instance of instances) {
            for (const page of instance.pages) {
                await this.cdpHandler.sendCommand(page.id, 'Runtime.evaluate', {
                    expression: 'if(typeof window !== "undefined" && window.__autoAllStop) window.__autoAllStop()'
                }).catch(() => { });
            }
        }

        this.cdpHandler.disconnectAll();
        this.updateStatusBar();
        vscode.window.showInformationMessage('Antigravity: Auto-All OFF');
    }

    private updateStatusBar() {
        if (this.isActive) {
            this.statusBarItem.text = "$(rocket) Auto-All: ON";
            this.statusBarItem.tooltip = "CDP Backed Auto-Accept Running";
            this.statusBarItem.backgroundColor = undefined;
        } else {
            this.statusBarItem.text = "$(circle-slash) Auto-All: OFF";
            this.statusBarItem.tooltip = "Click to Enable Auto-All";
            this.statusBarItem.backgroundColor = new vscode.ThemeColor('statusBarItem.warningBackground');
        }
        this.statusBarItem.show();
    }

    dispose() {
        this.stop();
        this.statusBarItem.dispose();
    }
}
