
import * as vscode from 'vscode';
import { createLogger } from '../utils/logger';
import { config } from '../utils/config';

const log = createLogger('RateLimiter');

interface RateLimitState {
    callsThisHour: number;
    hourStartTime: number;
    isLimited: boolean;
    waitingForReset: boolean;
}

export class RateLimiter {
    private state: RateLimitState = {
        callsThisHour: 0,
        hourStartTime: Date.now(),
        isLimited: false,
        waitingForReset: false,
    };

    private waitTimer: NodeJS.Timeout | null = null;

    canMakeCall(): boolean {
        this.checkHourReset();
        const maxCalls = config.get<number>('maxCallsPerHour') || 100;
        return this.state.callsThisHour < maxCalls && !this.state.waitingForReset;
    }

    recordCall(): void {
        this.checkHourReset();
        this.state.callsThisHour++;
        log.info(`Call recorded (${this.state.callsThisHour}/${config.get('maxCallsPerHour') || 100})`);
    }

    private checkHourReset(): void {
        const now = Date.now();
        const hourMs = 60 * 60 * 1000;

        if (now - this.state.hourStartTime >= hourMs) {
            this.state.callsThisHour = 0;
            this.state.hourStartTime = now;
            this.state.isLimited = false;
            log.info('Hourly rate limit reset');
        }
    }

    getRemainingCalls(): number {
        this.checkHourReset();
        const maxCalls = config.get<number>('maxCallsPerHour') || 100;
        return Math.max(0, maxCalls - this.state.callsThisHour);
    }

    getTimeUntilReset(): number {
        const hourMs = 60 * 60 * 1000;
        const elapsed = Date.now() - this.state.hourStartTime;
        return Math.max(0, hourMs - elapsed);
    }

    async handleRateLimitReached(): Promise<'wait' | 'exit'> {
        this.state.isLimited = true;
        const timeUntilReset = this.getTimeUntilReset();
        const minutesRemaining = Math.ceil(timeUntilReset / 60000);

        log.warn(`Rate limit reached. ${minutesRemaining} minutes until reset.`);

        const choice = await vscode.window.showWarningMessage(
            `⚠️ Rate Limit Reached\n\n` +
            `You've made ${this.state.callsThisHour} calls this hour.\n` +
            `The limit will reset in ${minutesRemaining} minutes.`,
            { modal: true },
            'Wait for Reset',
            'Exit Now'
        );

        if (choice === 'Wait for Reset') {
            return this.waitForReset();
        } else {
            return 'exit';
        }
    }

    private async waitForReset(): Promise<'wait' | 'exit'> {
        this.state.waitingForReset = true;
        const timeUntilReset = this.getTimeUntilReset();

        log.info(`Waiting ${Math.ceil(timeUntilReset / 60000)} minutes for rate limit reset...`);

        return new Promise((resolve) => {
            vscode.window.withProgress(
                {
                    location: vscode.ProgressLocation.Notification,
                    title: 'Yoke AntiGravity: Waiting for rate limit reset',
                    cancellable: true,
                },
                async (progress, token) => {
                    const startTime = Date.now();
                    const totalMs = timeUntilReset;

                    token.onCancellationRequested(() => {
                        this.state.waitingForReset = false;
                        resolve('exit');
                    });

                    while (Date.now() - startTime < totalMs) {
                        if (token.isCancellationRequested) break;

                        const elapsed = Date.now() - startTime;
                        const remaining = totalMs - elapsed;
                        const minutesLeft = Math.ceil(remaining / 60000);
                        const percentage = (elapsed / totalMs) * 100;

                        progress.report({
                            increment: percentage,
                            message: `${minutesLeft} minutes remaining...`,
                        });

                        await new Promise((r) => setTimeout(r, 10000));
                    }

                    this.state.waitingForReset = false;
                    this.state.callsThisHour = 0;
                    this.state.hourStartTime = Date.now();
                    this.state.isLimited = false;

                    log.info('Rate limit reset. Resuming...');
                    resolve('wait');
                }
            );
        });
    }

    reset(): void {
        this.state = {
            callsThisHour: 0,
            hourStartTime: Date.now(),
            isLimited: false,
            waitingForReset: false,
        };
        if (this.waitTimer) {
            clearTimeout(this.waitTimer);
            this.waitTimer = null;
        }
        log.info('Rate limiter reset');
    }
}

export const rateLimiter = new RateLimiter();
