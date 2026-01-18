import logger from '../utils/logger.js';

export async function realtimeMiddleware(req, res, next) {
  const path = req.path;
  
  if (path.startsWith('/api/calls')) {
    const { limit = 50 } = req.query;
    
    const calls = Array.from(req.app.get('activeCalls').values()).slice(0, limit);
    
    const callsData = calls.map(call => ({
      callSid: call.get('callSid') || 'unknown',
      from: call.get('from') || 'unknown',
      to: call.get('to') || 'unknown',
      direction: call.get('direction') || 'unknown',
      startTime: call.get('startTime'),
      transcriptLength: call.get('transcript')?.length || 0,
      duration: Math.round((Date.now() - call.get('startTime').getTime() / 1000),
      customerName: call.get('customerName') || null,
      equipment: call.get('equipment') || null
    }));

    logger.debug('Real-time calls API requested', { callCount: callsData.length });

    res.json({ 
      success: true, 
      data: callsData 
    });
  } else {
    next();
  }
}
}

export function getCallStats(activeCalls) {
  const calls = Array.from(activeCalls.values());
  const now = Date.now();
  
  if (calls.length === 0) {
    return {
      totalCalls: 0,
      activeCalls: 0,
      avgDuration: 0,
      totalDuration: 0
    };
  }

  let totalDuration = 0;
  const completedCalls = calls.filter(call => call.transcript.length > 0);
  
  for (const call of completedCalls) {
    const duration = (call.endTime || now) - call.startTime.getTime();
    totalDuration += duration;
  }

  const avgDuration = totalDuration / completedCalls.length;
  
  return {
    totalCalls: calls.length,
    activeCalls: calls.length,
    completedCalls: completedCalls.length,
    avgDuration: Math.round(avgDuration / 1000),
    totalDuration: Math.round(totalDuration / 1000),
    callsByDirection: {
      inbound: calls.filter(c => c.direction === 'inbound').length,
      outbound: calls.filter(c => c.direction === 'outbound').length
    }
  };
}

export function getDailyStats() {
  const stats = {
    date: new Date().toISOString().split('T')[0],
    totalCalls: 0,
    totalDuration: 0,
    avgDuration: 0
  };

  return stats;
}
