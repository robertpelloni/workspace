
import { createLogger } from '../utils/logger';

const log = createLogger('ExitDetector');

export interface ExitResult {
    shouldExit: boolean;
    reason?: string;
}

export class ExitDetector {
    private failureCount = 0;
    private maxConsecutiveFailures = 5;

    checkResponse(response: string): ExitResult {
        const lower = response.toLowerCase();
        if (lower.includes('all tasks completed') || lower.includes('goal achieved')) {
            return { shouldExit: true, reason: 'AI indicated completion' };
        }
        return { shouldExit: false };
    }

    reportSuccess() {
        this.failureCount = 0;
    }

    reportFailure(): ExitResult {
        this.failureCount++;
        if (this.failureCount >= this.maxConsecutiveFailures) {
            return { shouldExit: true, reason: `Too many consecutive failures (${this.failureCount})` };
        }
        return { shouldExit: false };
    }

    reset() {
        this.failureCount = 0;
    }
}

export const exitDetector = new ExitDetector();
