import logger from '../utils/logger.js';
import { getAnalytics, updateCallStats, getRealtimeStats, clearOldStats } from '../services/analytics.js';
import { activeCalls } from '../index.js';

const costs = {
  twilio: {
    numberPerMonth: 1.15,
    perMinute: 0.02
  },
  openai: {
    perMinute: 0.30,
    realtimeModel: 'gpt-4o-realtime-preview'
  },
  sendgrid: {
    emailsPerMonth: 100,
    costPer100Email: 1
  }
};

export function calculateCallCost(duration, model = 'realtime') {
  const durationMinutes = duration / 60;
  
  const twilioCost = durationMinutes * costs.twilio.perMinute;
  const openaiCost = durationMinutes * costs.openai.perMinute;
  
  const total = twilioCost + openaiCost;
  
  logger.debug('Call cost calculated', { 
    durationMinutes, 
    twilioCost: twilioCost.toFixed(4),
    openaiCost: openaiCost.toFixed(4),
    total: total.toFixed(4)
  });
  
  return {
    durationMinutes,
    twilioCost,
    openaiCost,
    total
  };
}

export function getMonthlyCost(days = 30) {
  const analytics = getAnalytics(days);
  
  const totalMinutes = analytics.summary.totalDuration;
  const twilioCost = totalMinutes * costs.twilio.perMinute;
  const openaiCost = totalMinutes * costs.openai.perMinute;
  const totalCost = twilioCost + openaiCost;
  
  const emailCosts = Math.ceil(analytics.summary.totalCalls / costs.sendgrid.emailsPerMonth) * costs.sendgrid.costPer100Email;
  const monthlyTwilioCost = costs.twilio.numberPerMonth;
  const totalMonthlyCost = totalCost + monthlyTwilioCost + emailCosts;
  
  return {
    period: {
      days,
      start: analytics.period.start,
      end: analytics.period.end
    },
    usage: {
      totalCalls: analytics.summary.totalCalls,
      totalDuration: Math.round(totalMinutes),
      avgDuration: analytics.summary.avgDuration
    },
    costs: {
      twilio: twilioCost.toFixed(2),
      openai: openaiCost.toFixed(2),
      emails: emailCosts.toFixed(2),
      monthlyTwilio: monthlyTwilioCost.toFixed(2),
      totalVoice: totalCost.toFixed(2),
      total: totalMonthlyCost.toFixed(2)
    },
    pricing: {
      twilioPerMinute: costs.twilio.perMinute,
      openaiPerMinute: costs.openai.perMinute,
      sendgridPer100Email: costs.sendgrid.costPer100Email
    }
  };
}

export function getCostBreakdown(callData) {
  if (!callData || !callData.endTime) {
    return null;
  }

  const duration = (callData.endTime.getTime() - callData.startTime.getTime()) / 1000;
  const costInfo = calculateCallCost(duration);
  
  logger.info('Cost breakdown calculated', {
    callSid: callData.callSid,
    duration,
    totalCost: costInfo.total
  });
  
  return costInfo;
}
