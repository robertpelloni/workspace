
import * as vscode from 'vscode';
import * as fs from 'fs';
import * as path from 'path';
import { CircuitBreaker, CircuitState } from '../core/circuit-breaker';
import { progressTracker } from './progress-tracker';
import { rateLimiter } from './rate-limiter';
import { taskAnalyzer } from './task-analyzer';
import { modelSelector } from './model-selector';
import { exitDetector } from './exit-detector';
import { cdpClient } from '../providers/cdp-client';
import { config } from '../utils/config';
import { createLogger } from '../utils/logger';

const log = createLogger('AutonomousLoop');
const circuitBreaker = new CircuitBreaker(); // Use local instance for now or singleton if preferred

export interface LoopConfig {
    goal?: string;
    maxLoops: number;
    loopIntervalSeconds: number;
    autoSwitchModels: boolean;
}

export interface LoopStatus {
    running: boolean;
    loopCount: number;
    currentTask: string | null;
    currentModel: string;
    circuitState: CircuitState;
    message: string;
}

export class AutonomousLoop {
    private running = false;
    private loopCount = 0;
    private currentTask: string | null = null;
    private timer: NodeJS.Timeout | null = null;
    private workspaceRoot: string | null = null;
    private goal: string = '';
    private onStatusChange: ((status: LoopStatus) => void) | null = null;
    private previousModel: string | null = null;

    constructor() {
        const folders = vscode.workspace.workspaceFolders;
        if (folders && folders.length > 0) {
            this.workspaceRoot = folders[0].uri.fsPath;
        }
    }

    setStatusCallback(callback: (status: LoopStatus) => void): void {
        this.onStatusChange = callback;
    }

    async start(loopConfig: Partial<LoopConfig> = {}): Promise<void> {
        if (this.running) {
            log.warn('Loop already running');
            return;
        }

        this.running = true;
        this.loopCount = 0;
        this.goal = loopConfig.goal || '';
        progressTracker.startSession();
        rateLimiter.reset();
        exitDetector.reset(); // Added reset
        this.previousModel = null;

        log.info('🚀 Autonomous loop starting');
        vscode.window.showInformationMessage('🚀 Yoke AntiGravity Autonomous Mode: STARTING');

        await this.runLoop(loopConfig);
    }

    stop(reason = 'User stopped'): void {
        if (!this.running) return;

        this.running = false;
        if (this.timer) {
            clearTimeout(this.timer);
            this.timer = null;
        }

        log.info(`Loop stopped: ${reason}`);
        this.showSummary(reason);
        this.updateStatus();
    }

    private async runLoop(loopConfig: Partial<LoopConfig>): Promise<void> {
        const maxLoops = loopConfig.maxLoops || config.get('maxLoopsPerSession');
        const intervalSeconds = loopConfig.loopIntervalSeconds || config.get('loopInterval');

        while (this.running) {
            this.loopCount++;
            log.info(`=== Loop #${this.loopCount} ===`);
            this.updateStatus();

            // Circuit Breaker check
            const circuitState = await circuitBreaker.execute(async () => true);
            if (!circuitState) {
                log.warn('Circuit Breaker is OPEN. Skipping loop.');
                this.updateStatus();
                await this.wait(10000);
                continue;
            }

            if (!rateLimiter.canMakeCall()) {
                log.warn('Hourly rate limit reached');
                const decision = await rateLimiter.handleRateLimitReached();
                if (decision === 'exit') {
                    this.stop('Rate limit reached - user chose to exit');
                    return;
                }
            }

            if (this.loopCount > maxLoops) {
                this.stop(`Max loops reached (${maxLoops})`);
                return;
            }

            this.currentTask = await this.getCurrentTask();
            if (!this.currentTask) {
                this.stop('All tasks completed! 🎉');
                return;
            }

            if (config.get('autoSwitchModels')) {
                const selection = await modelSelector.selectForTask(this.currentTask);
                // logic to set model on rateLimitHandler or similar
                log.info(`Model: ${selection.modelDisplayName} (${selection.reasoning})`);
                if (this.previousModel !== selection.modelId) {
                    modelSelector.showSwitchNotification(selection);
                    progressTracker.recordModelSwitch();
                    this.previousModel = selection.modelId;
                }
            }

            const success = await this.executeTask();

            await progressTracker.recordLoop({
                modelUsed: this.previousModel || 'unknown',
                hasErrors: !success,
            });

            // Git Commit logic
            if (config.get('autoGitCommit') && this.loopCount % 10 === 0) {
                await this.gitCommit();
            }

            const waitTime = (intervalSeconds || 30) * 1000;
            await this.wait(waitTime);
        }
    }

    private async gitCommit(): Promise<void> {
        if (!this.workspaceRoot) return;

        try {
            log.info('Auto-committing progress...');
            const cp = require('child_process');
            const exec = (cmd: string) => new Promise((res, rej) => {
                cp.exec(cmd, { cwd: this.workspaceRoot }, (err: any, stdout: string) => {
                    if (err) rej(err);
                    else res(stdout);
                });
            });

            await exec('git add .');
            await exec(`git commit -m "antigravity: auto-save loop #${this.loopCount}"`);
            log.info('Auto-commit successful');
        } catch (e: any) {
            log.error(`Auto-commit failed: ${e.message}`);
        }
    }

    private async getCurrentTask(): Promise<string | null> {
        if (this.goal && this.loopCount === 1) {
            return this.goal;
        }

        if (this.workspaceRoot) {
            const fixPlanPath = path.join(this.workspaceRoot, '@fix_plan.md');
            if (fs.existsSync(fixPlanPath)) {
                try {
                    const content = fs.readFileSync(fixPlanPath, 'utf-8');
                    const task = taskAnalyzer.extractCurrentTask(content);
                    if (task) return task;
                    log.info('All tasks in @fix_plan.md are complete');
                    return null;
                } catch (err) {
                    log.warn('Could not read @fix_plan.md');
                }
            }
        }

        if (this.goal) return this.goal;
        return null;
    }

    private async executeTask(): Promise<boolean> {
        if (!cdpClient.isConnected()) {
            const connected = await cdpClient.connect();
            if (!connected) {
                log.warn('CDP not available, waiting...');
                return true;
            }
        }

        try {
            const prompt = this.buildPrompt();
            progressTracker.recordPromptSent();

            log.info('Injecting prompt...');
            const injected = await cdpClient.injectPrompt(prompt);
            if (!injected) {
                log.error('Failed to inject prompt');
                return false;
            }

            rateLimiter.recordCall();

            log.info('Waiting for response...');
            const timeoutMs = (config.get<number>('executionTimeout') || 15) * 60 * 1000;
            const response = await cdpClient.waitForResponse(timeoutMs);

            const exitCheck = exitDetector.checkResponse(response);
            if (exitCheck.shouldExit) {
                this.stop(exitCheck.reason || 'Task completed');
                return true;
            }

            exitDetector.reportSuccess();
            return true;
        } catch (err: any) {
            log.error(`Execution error: ${err.message}`);
            // Report to circuit breaker
            // Circuit breaker wrapper around executeTask is better, but here we just report

            const failCheck = exitDetector.reportFailure();
            if (failCheck.shouldExit) {
                this.stop(failCheck.reason);
            }
            return false;
        }
    }

    private buildPrompt(): string {
        if (!this.currentTask) return '';
        return `${this.currentTask}\n\n[Note: Running in autonomous mode.]`;
    }

    private wait(ms: number): Promise<void> {
        return new Promise((resolve) => {
            this.timer = setTimeout(resolve, ms);
        });
    }

    private showSummary(reason: string): void {
        const summary = progressTracker.getSummary();
        vscode.window.showInformationMessage(
            `Yoke: ${reason}\n${summary}`,
            'Open Dashboard'
        ).then((action) => {
            if (action === 'Open Dashboard') {
                vscode.commands.executeCommand('antigravity.openSettings');
            }
        });
    }

    private updateStatus(): void {
        if (this.onStatusChange) {
            this.onStatusChange(this.getStatus());
        }
    }

    getStatus(): LoopStatus {
        return {
            running: this.running,
            loopCount: this.loopCount,
            currentTask: this.currentTask,
            currentModel: this.previousModel || 'default',
            circuitState: CircuitState.CLOSED, // Placeholder
            message: 'Running',
        };
    }

    isRunning(): boolean {
        return this.running;
    }
}

export const autonomousLoop = new AutonomousLoop();
