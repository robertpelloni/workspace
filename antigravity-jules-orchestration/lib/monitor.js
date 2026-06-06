/**
 * Session Monitor Module
 * Real-time tracking and statistics for Jules sessions
 */

/**
 * Session monitor for tracking all active sessions
 */
export class SessionMonitor {
    constructor(julesRequest) {
        this.julesRequest = julesRequest;
        this.cachedSessions = null;
        this.lastFetch = null;
        this.cacheTimeout = 10000; // 10 seconds
    }

    /**
     * Get all sessions with optional filtering
     */
    async getAllSessions(forceRefresh = false) {
        const now = Date.now();

        // Use cache if available and not expired
        if (!forceRefresh && this.cachedSessions && this.lastFetch &&
            (now - this.lastFetch) < this.cacheTimeout) {
            return this.cachedSessions;
        }

        try {
            const result = await this.julesRequest('GET', '/sessions');
            this.cachedSessions = result.sessions || [];
            this.lastFetch = now;
            return this.cachedSessions;
        } catch (error) {
            console.error('[Monitor] Failed to fetch sessions:', error.message);
            return this.cachedSessions || [];
        }
    }

    /**
     * Get only active (non-completed) sessions
     */
    async getActiveSessions() {
        const sessions = await this.getAllSessions();
        return sessions.filter(s =>
            s.state !== 'COMPLETED' &&
            s.state !== 'FAILED' &&
            s.state !== 'CANCELLED'
        );
    }

    /**
     * Get aggregated statistics for all sessions
     */
    async getStats() {
        const sessions = await this.getAllSessions(true);

        const stats = {
            total: sessions.length,
            byState: {},
            recent24h: 0,
            recent7d: 0,
            avgCompletionTime: null
        };

        const now = Date.now();
        const day = 24 * 60 * 60 * 1000;
        const week = 7 * day;

        sessions.forEach(session => {
            // Count by state
            const state = session.state || 'UNKNOWN';
            stats.byState[state] = (stats.byState[state] || 0) + 1;

            // Count recent sessions
            const created = new Date(session.createTime).getTime();
            if (now - created < day) stats.recent24h++;
            if (now - created < week) stats.recent7d++;
        });

        // Calculate completion rate
        const completed = stats.byState['COMPLETED'] || 0;
        const failed = stats.byState['FAILED'] || 0;
        stats.completionRate = stats.total > 0
            ? ((completed / (completed + failed)) * 100).toFixed(1) + '%'
            : 'N/A';

        return stats;
    }

    /**
     * Get detailed timeline for a session
     */
    async getSessionTimeline(sessionId) {
        try {
            const [session, activities] = await Promise.all([
                this.julesRequest('GET', `/sessions/${sessionId}`),
                this.julesRequest('GET', `/sessions/${sessionId}/activities`)
            ]);

            const timeline = (activities.activities || []).map(activity => ({
                id: activity.id,
                type: this.getActivityType(activity),
                timestamp: activity.createTime,
                originator: activity.originator,
                summary: this.summarizeActivity(activity)
            }));

            return {
                session: {
                    id: sessionId,
                    title: session.title,
                    state: session.state,
                    url: session.url,
                    createdAt: session.createTime,
                    updatedAt: session.updateTime
                },
                timeline,
                duration: this.calculateDuration(session.createTime, session.updateTime)
            };
        } catch (error) {
            throw new Error(`Failed to get timeline for session ${sessionId}: ${error.message}`);
        }
    }

    /**
     * Determine activity type from activity object
     */
    getActivityType(activity) {
        if (activity.planGenerated) return 'PLAN_GENERATED';
        if (activity.planApproved) return 'PLAN_APPROVED';
        if (activity.stepStarted) return 'STEP_STARTED';
        if (activity.stepCompleted) return 'STEP_COMPLETED';
        if (activity.prCreated) return 'PR_CREATED';
        if (activity.message) return 'MESSAGE';
        return 'UNKNOWN';
    }

    /**
     * Create human-readable summary of activity
     */
    summarizeActivity(activity) {
        if (activity.planGenerated) {
            const steps = activity.planGenerated.steps?.length || 0;
            return `Plan generated with ${steps} steps`;
        }
        if (activity.planApproved) {
            return 'Plan approved by user';
        }
        if (activity.stepStarted) {
            return `Started: ${activity.stepStarted.title || 'Step'}`;
        }
        if (activity.stepCompleted) {
            return `Completed: ${activity.stepCompleted.title || 'Step'}`;
        }
        if (activity.prCreated) {
            return `PR created: ${activity.prCreated.url || 'Link available'}`;
        }
        if (activity.message) {
            return `Message: ${activity.message.content?.substring(0, 50) || '...'}`;
        }
        return 'Activity recorded';
    }

    /**
     * Calculate human-readable duration
     */
    calculateDuration(start, end) {
        const startTime = new Date(start).getTime();
        const endTime = new Date(end).getTime();
        const durationMs = endTime - startTime;

        if (durationMs < 60000) {
            return `${Math.round(durationMs / 1000)} seconds`;
        } else if (durationMs < 3600000) {
            return `${Math.round(durationMs / 60000)} minutes`;
        } else {
            return `${(durationMs / 3600000).toFixed(1)} hours`;
        }
    }

    /**
     * Monitor all active sessions and return summary
     */
    async monitorAll() {
        const active = await this.getActiveSessions();
        const stats = await this.getStats();

        // Get detailed status for each active session
        const detailed = await Promise.all(
            active.slice(0, 20).map(async (session) => {
                const id = session.name?.split('/').pop() || session.id;
                try {
                    const details = await this.julesRequest('GET', `/sessions/${id}`);
                    return {
                        id,
                        title: details.title,
                        state: details.state,
                        url: details.url,
                        createdAt: details.createTime,
                        updatedAt: details.updateTime
                    };
                } catch {
                    return {
                        id,
                        title: session.title,
                        state: session.state || 'UNKNOWN',
                        error: 'Could not fetch details'
                    };
                }
            })
        );

        return {
            timestamp: new Date().toISOString(),
            stats,
            activeSessions: detailed,
            activeCount: active.length
        };
    }
}

export default SessionMonitor;
