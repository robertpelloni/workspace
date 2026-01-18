import logger from '../utils/logger.js';
import { getCallStats } from '../routes/api.js';
import { activeCalls } from '../index.js';
import { getRecordingStats as getRecordingStatsFromService } from './recording.js';

const statsHistory = [];
const STATS_HISTORY_SIZE = 100;

export function updateCallStats(callSid, status) {
  const callData = activeCalls.get(callSid);
  if (!callData) return;

  if (status === 'completed') {
    callData.endTime = new Date();
  }

  statsHistory.push({
    callSid,
    from: callData.from,
    to: callData.to,
    direction: callData.direction,
    status,
    startTime: callData.startTime,
    endTime: callData.endTime || new Date(),
    transcriptLength: callData.transcript?.length || 0,
    timestamp: Date.now()
  });

  if (statsHistory.length > STATS_HISTORY_SIZE) {
    statsHistory.shift();
    logger.info('Stats history trimmed to size', { maxSize: STATS_HISTORY_SIZE });
  }
}

export function getAnalytics(days = 7) {
  const cutoffDate = new Date(Date.now() - days * 24 * 60 * 60 * 1000);

  const recentStats = statsHistory.filter(s => s.timestamp >= cutoffDate.getTime());

  const totalCalls = recentStats.length;
  const completedCalls = recentStats.filter(s => s.status === 'completed');
  const inboundCalls = recentStats.filter(s => s.direction === 'inbound').length;
  const outboundCalls = recentStats.filter(s => s.direction === 'outbound').length;

  let totalDuration = 0;
  for (const stat of completedCalls) {
    const duration = (stat.endTime?.getTime() || stat.startTime.getTime()) - stat.startTime.getTime();
    totalDuration += duration;
  }

  const avgDuration = completedCalls.length > 0 ? totalDuration / completedCalls.length : 0;

  const hourBuckets = Array(24).fill(0);
  for (const stat of completedCalls) {
    const hour = stat.startTime.getHours();
    hourBuckets[hour]++;
  }

  const peakHour = hourBuckets.indexOf(Math.max(...hourBuckets));
  const peakCalls = Math.max(...hourBuckets);

  return {
    period: {
      start: new Date(cutoffDate).toISOString(),
      end: new Date().toISOString()
    },
    summary: {
      totalCalls,
      completedCalls: completedCalls.length,
      failedCalls: totalCalls - completedCalls.length,
      successRate: totalCalls > 0 ? (completedCalls.length / totalCalls * 100).toFixed(2) : '0',
      avgDuration: Math.round(avgDuration / 1000),
      totalDuration: Math.round(totalDuration / 1000),
      inboundCalls,
      outboundCalls
    },
    timing: {
      peakHour,
      peakCalls,
      callsByHour: hourBuckets.map((count, hour) => ({ hour, count }))
    },
    recordings: getRecordingStatsFromService()
  };
}

export function getRealtimeStats() {
  const stats = getCallStats(activeCalls);
  return {
    ...stats,
    timestamp: Date.now()
  };
}

export function clearOldStats(days = 30) {
  const cutoffDate = Date.now() - days * 24 * 60 * 60 * 1000;
  const beforeCount = statsHistory.length;

  statsHistory = statsHistory.filter(s => s.timestamp >= cutoffDate);

  const removedCount = beforeCount - statsHistory.length;
  logger.info('Cleared old analytics data', {
    days,
    removedCount,
    remainingCount: statsHistory.length
  });

  return removedCount;
}
