import logger from './logger.js';
import { activeCalls } from '../index.js';

const CALL_TTL_MS = 60 * 60 * 1000;
const CLEANUP_INTERVAL_MS = 5 * 60 * 1000;
const MAX_ACTIVE_CALLS = 100;

class CallDataCleanup {
  constructor() {
    this.cleanupTimer = null;
  }

  start() {
    logger.info('Starting call data cleanup service');

    this.cleanupTimer = setInterval(() => {
      this.cleanup();
    }, CLEANUP_INTERVAL_MS);
  }

  stop() {
    if (this.cleanupTimer) {
      clearInterval(this.cleanupTimer);
      this.cleanupTimer = null;
      logger.info('Call data cleanup service stopped');
    }
  }

  cleanup() {
    const now = Date.now();
    let cleanedCount = 0;
    let expiredCount = 0;

    for (const [callSid, callData] of activeCalls.entries()) {
      const callAge = now - callData.startTime.getTime();

      if (callAge > CALL_TTL_MS) {
        logger.warn(`Cleaning up expired call data: ${callSid} (age: ${Math.round(callAge / 60000)} minutes)`);
        activeCalls.delete(callSid);
        expiredCount++;
        cleanedCount++;
      }
    }

    if (activeCalls.size > MAX_ACTIVE_CALLS) {
      const entries = Array.from(activeCalls.entries());
      const toRemove = entries
        .sort((a, b) => a[1].startTime - b[1].startTime)
        .slice(0, activeCalls.size - MAX_ACTIVE_CALLS);

      for (const [callSid] of toRemove) {
        logger.warn(`Cleaning up oldest call data (max limit): ${callSid}`);
        activeCalls.delete(callSid);
        cleanedCount++;
      }
    }

    if (cleanedCount > 0) {
      logger.info(`Cleanup complete: removed ${cleanedCount} call entries (${expiredCount} expired, ${activeCalls.size} remaining)`);
    }
  }

  getStats() {
    return {
      activeCalls: activeCalls.size,
      maxCalls: MAX_ACTIVE_CALLS,
      ttlMinutes: CALL_TTL_MS / (60 * 1000),
      cleanupIntervalMinutes: CLEANUP_INTERVAL_MS / (60 * 1000),
    };
  }
}

const cleanupService = new CallDataCleanup();

export default cleanupService;
