import logger from '../utils/logger.js';
import { getAnalytics } from './analytics.js';
import { activeCalls } from '../index.js';

export async function exportAnalyticsToCSV(req, res) {
  try {
    const { days = 30 } = req.query;
    const daysNum = parseInt(days) || 30;
    
    logger.info('Exporting analytics to CSV', { days: daysNum });
    
    const analytics = getAnalytics(daysNum);
    
    if (!analytics.summary.totalCalls) {
      return res.status(400).json({ error: 'No call data available' });
    }

    let csv = 'Call SID,From,To,Direction,Duration,Transcript Length,Status,Start Time,End Time,Customer Name,Equipment\n';
    
    const stats = analytics.summary;
    const recentStats = stats.timing.callsByHour || [];
    
    for (const entry of stats.timing.callsByHour || []) {
      const matchingCall = Array.from(activeCalls.values()).find(c => 
        c.callSid && c.startTime.getTime() >= new Date(analytics.period.start).getTime() &&
        c.startTime.getTime() <= new Date(analytics.period.end).getTime()
      );
      
      if (matchingCall) {
        csv += `${matchingCall.callSid},${matchingCall.from},${matchingCall.to},${matchingCall.direction},${matchingCall.duration},${matchingCall.transcriptLength},${matchingCall.direction === 'completed' ? 'completed' : 'in-progress'},${matchingCall.startTime.toISOString()},${matchingCall.endTime || new Date().toISOString()},"${matchingCall.customerName || ''}","${matchingCall.equipment || ''}"\n`;
      }
    }

    for (let i = 0; i < analytics.summary.totalCalls; i++) {
      const callData = Array.from(activeCalls.values())[i];
      if (!callData) continue;
      
      const status = callData.transcript?.length > 0 ? 'completed' : 'incomplete';
      const duration = callData.endTime ? 
        Math.round((callData.endTime.getTime() - callData.startTime.getTime()) / 1000) : 
        null;
      
      csv += `${callData.callSid},${callData.from},${callData.to},${callData.direction},${duration || 0},${callData.transcript?.length || 0},${status},${callData.startTime.toISOString()},${callData.endTime || new Date().toISOString()},"${callData.customerName || ''}","${callData.equipment || ''}"\n`;
    }

    res.setHeader('Content-Type', 'text/csv');
    res.setHeader('Content-Disposition', `attachment; filename="brobocallz_analytics_${new Date().toISOString().split('T')[0]}.csv"`);
    res.send(csv);
    
    logger.info('Analytics exported to CSV', {
      totalCalls: analytics.summary.totalCalls,
      lines: csv.split('\n').length
    });
  } catch (err) {
    logger.error('Error exporting analytics', { error: err.message });
    res.status(500).json({ error: 'Failed to export analytics' });
  }
}
