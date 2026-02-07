
export enum CircuitState {
    CLOSED, // Normal operation
    OPEN,   // Failure state, blocking actions
    HALF_OPEN // Testing recovery
}

export class CircuitBreaker {
    private state: CircuitState = CircuitState.CLOSED;
    private failureCount = 0;
    private lastFailureTime = 0;
    private readonly failureThreshold = 5;
    private readonly resetTimeout = 30000; // 30s

    async execute<T>(action: () => Promise<T>): Promise<T | null> {
        if (this.state === CircuitState.OPEN) {
            if (Date.now() - this.lastFailureTime > this.resetTimeout) {
                this.state = CircuitState.HALF_OPEN;
            } else {
                console.warn('[CircuitBreaker] Circuit is OPEN. Action blocked.');
                return null;
            }
        }

        try {
            const result = await action();
            if (this.state === CircuitState.HALF_OPEN) {
                this.reset();
            }
            return result;
        } catch (error) {
            this.recordFailure();
            throw error;
        }
    }

    private recordFailure() {
        this.failureCount++;
        this.lastFailureTime = Date.now();
        if (this.failureCount >= this.failureThreshold) {
            this.trip();
        }
    }

    private trip() {
        this.state = CircuitState.OPEN;
        console.error('[CircuitBreaker] Circuit TRIPPED to OPEN state.');
    }

    private reset() {
        this.state = CircuitState.CLOSED;
        this.failureCount = 0;
        console.log('[CircuitBreaker] Circuit RESET to CLOSED state.');
    }
}
