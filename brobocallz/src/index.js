import 'dotenv/config';
import './utils/startup-validation.js';
import express from 'express';
import { createServer } from 'http';
import { WebSocketServer } from 'ws';
import { handleIncomingCall, handleCallStatus } from './services/twilio.js';
import { handleMediaStream } from './services/mediaStream.js';
import logger from './utils/logger.js';
import cleanupService from './utils/callCleanup.js';
import { realtimeMiddleware } from './routes/api.js';
import { getAnalytics, updateCallStats, getRealtimeStats } from './services/analytics.js';
import { getMonthlyCost } from './services/costTracking.js';

const app = express();
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

app.use((err, req, res, next) => {
  logger.error('Express error middleware', { error: err.message, stack: err.stack });
  res.status(500).json({ error: 'Internal server error' });
});

const server = createServer(app);
const wss = new WebSocketServer({ server });

export const activeCalls = new Map();

app.use(express.static('public'));

server.listen(PORT, () => {
  logger.info('BrobocallZ server started', {
    port: PORT,
    business: process.env.BUSINESS_NAME || 'Not configured',
    environment: process.env.NODE_ENV || 'development',
    version: '1.2.0',
    endpoints: [
      'GET /api/calls - Real-time call data',
      'GET /api/analytics - Call analytics',
      'GET /api/costs - Cost tracking',
      'GET /dashboard.html - Web dashboard',
      'POST /incoming-call - Twilio webhook',
      'POST /outbound-answer - Outbound call handler',
      'POST /call-status - Call status callback',
      'WSS /media-stream - Real-time audio',
      'GET /cleanup-stats - Cleanup statistics'
    ]
  });
});
