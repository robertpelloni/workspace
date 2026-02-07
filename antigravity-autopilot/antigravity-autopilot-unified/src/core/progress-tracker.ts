
import { createLogger } from '../utils/logger';

const log = createLogger('ProgressTracker');

export interface LoopStats {
    totalLoops: number;
    successfulLoops: number;
    failedLoops: number;
    modelSwitches: number;
    startTime: number;
    filesChanged: number;
    promptsSent: number;
}

export class ProgressTracker {
    private stats: LoopStats = {
        totalLoops: 0,
        successfulLoops: 0,
        failedLoops: 0,
        modelSwitches: 0,
        startTime: Date.now(),
        filesChanged: 0,
        promptsSent: 0
    };

    startSession() {
        this.stats = {
            totalLoops: 0,
            successfulLoops: 0,
            failedLoops: 0,
            modelSwitches: 0,
            startTime: Date.now(),
            filesChanged: 0,
            promptsSent: 0
        };
        log.info('Session progress tracking started');
    }

    async recordLoop(result: { modelUsed: string; hasErrors: boolean }): Promise<{ filesChanged: number; hasErrors: boolean; responseLength: number; responseHash: string }> {
        this.stats.totalLoops++;
        if (result.hasErrors) {
            this.stats.failedLoops++;
        } else {
            this.stats.successfulLoops++;
        }

        // Placeholder values - real implementation would analyze diffs or response
        const filesChanged = result.hasErrors ? 0 : 1;
        this.stats.filesChanged += filesChanged;

        return {
            filesChanged,
            hasErrors: result.hasErrors,
            responseLength: 100, // Placeholder
            responseHash: 'dummy-hash' // Placeholder
        };
    }

    recordModelSwitch() {
        this.stats.modelSwitches++;
    }

    recordPromptSent() {
        this.stats.promptsSent++;
    }

    getSummary(): string {
        const duration = (Date.now() - this.stats.startTime) / 1000 / 60;
        return `
Session Duration: ${duration.toFixed(1)} mins
Total Loops: ${this.stats.totalLoops}
Success Rate: ${((this.stats.successfulLoops / this.stats.totalLoops) * 100).toFixed(1)}%
Model Switches: ${this.stats.modelSwitches}
Prompts Sent: ${this.stats.promptsSent}
        `.trim();
    }

    getStats(): LoopStats {
        return { ...this.stats };
    }

    getDurationMinutes(): number {
        return (Date.now() - this.stats.startTime) / 1000 / 60;
    }
}

export const progressTracker = new ProgressTracker();
