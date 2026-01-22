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
import {
  listRecordings,
  getRecording,
  deleteRecording,
  getRecordingStats,
  cleanupOldRecordings,
  isRecordingEnabled
} from './services/recording.js';
import * as knowledgeBase from './services/knowledgeBase.js';
import { setupKnowledgeBaseRoutes } from './routes/knowledgeBase.js';
import fs from 'fs';
import path from 'path';

const PORT = process.env.PORT || 3000;
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
app.set('activeCalls', activeCalls);

app.use(express.static('public'));

setupKnowledgeBaseRoutes(app);

app.post('/incoming-call', handleIncomingCall);
app.post('/outbound-answer', handleMediaStream);
app.post('/call-status', handleCallStatus);

app.get('/api/calls', realtimeMiddleware);

app.get('/api/analytics', (req, res) => {
  const days = parseInt(req.query.days || '7', 10);
  try {
    const analytics = getAnalytics(days);
    res.json({ success: true, data: analytics });
  } catch (err) {
    logger.error('Failed to get analytics', { error: err.message });
    res.status(500).json({ success: false, error: err.message });
  }
});

app.get('/api/costs', (req, res) => {
  try {
    const costs = getMonthlyCost();
    res.json({ success: true, data: costs });
  } catch (err) {
    logger.error('Failed to get costs', { error: err.message });
    res.status(500).json({ success: false, error: err.message });
  }
});

app.get('/api/recordings', (req, res) => {
  try {
    const recordings = listRecordings();
    res.json({ success: true, data: recordings });
  } catch (err) {
    logger.error('Failed to list recordings', { error: err.message });
    res.status(500).json({ success: false, error: err.message });
  }
});

app.get('/api/recordings/:callSid', (req, res) => {
  const { callSid } = req.params;
  try {
    const recording = getRecording(callSid);
    if (!recording) {
      return res.status(404).json({ success: false, error: 'Recording not found' });
    }
    res.json({ success: true, data: recording });
  } catch (err) {
    logger.error('Failed to get recording', { callSid, error: err.message });
    res.status(500).json({ success: false, error: err.message });
  }
});

app.get('/api/recordings/:callSid/download', (req, res) => {
  const { callSid } = req.params;
  try {
    const recording = getRecording(callSid);
    if (!recording || !recording.localPath) {
      return res.status(404).json({ success: false, error: 'Recording file not found' });
    }

    if (!fs.existsSync(recording.localPath)) {
      logger.error('Recording file missing from filesystem', { callSid, localPath: recording.localPath });
      return res.status(404).json({ success: false, error: 'Recording file not found on disk' });
    }

    const filename = path.basename(recording.localPath);
    res.download(recording.localPath, filename, (err) => {
      if (err) {
        logger.error('Failed to download recording file', { callSid, error: err.message });
        if (!res.headersSent) {
          res.status(500).json({ success: false, error: 'Download failed' });
        }
      } else {
        logger.info('Recording file downloaded', { callSid, filename });
      }
    });
  } catch (err) {
    logger.error('Error in recording download', { callSid, error: err.message });
    if (!res.headersSent) {
      res.status(500).json({ success: false, error: err.message });
    }
  }
});

app.delete('/api/recordings/:callSid', (req, res) => {
  const { callSid } = req.params;
  try {
    const result = deleteRecording(callSid);
    res.json({ success: result.success, message: result.message });
  } catch (err) {
    logger.error('Failed to delete recording', { callSid, error: err.message });
    res.status(500).json({ success: false, error: err.message });
  }
});

app.get('/api/recordings-stats', (req, res) => {
  try {
    const stats = getRecordingStats();
    res.json({ success: true, data: stats });
  } catch (err) {
    logger.error('Failed to get recording stats', { error: err.message });
    res.status(500).json({ success: false, error: err.message });
  }
});

app.post('/api/recordings/cleanup', (req, res) => {
  try {
    const result = cleanupOldRecordings();
    res.json({ success: true, data: result });
  } catch (err) {
    logger.error('Failed to cleanup recordings', { error: err.message });
    res.status(500).json({ success: false, error: err.message });
  }
});

async function initializeServices() {
  if (knowledgeBase.isKnowledgeBaseEnabled()) {
    logger.info('Initializing knowledge base service...');
    const initialized = await knowledgeBase.initialize();
    if (initialized) {
      logger.info('Knowledge base service initialized successfully');
    } else {
      logger.warn('Knowledge base service initialization failed, continuing without it');
    }
  } else {
    logger.info('Knowledge base is disabled in configuration');
  }
}

initializeServices().then(() => {
  server.listen(PORT, () => {
    logger.info('BrobocallZ server started', {
      port: PORT,
      business: process.env.BUSINESS_NAME || 'Not configured',
      environment: process.env.NODE_ENV || 'development',
      version: '1.4.0',
      recordingEnabled: isRecordingEnabled(),
      knowledgeBaseEnabled: knowledgeBase.isKnowledgeBaseEnabled(),
      endpoints: [
        'GET /api/calls - Real-time call data',
        'GET /api/analytics - Call analytics',
        'GET /api/costs - Cost tracking',
        'GET /api/recordings - List all recordings',
        'GET /api/recordings/:callSid - Get recording details',
        'GET /api/recordings/:callSid/download - Download recording file',
        'DELETE /api/recordings/:callSid - Delete recording',
        'GET /api/recordings-stats - Recording statistics',
        'POST /api/recordings/cleanup - Clean up old recordings',
        'POST /api/knowledge-base/upload - Upload document (PDF, DOCX, TXT)',
        'POST /api/knowledge-base/text - Ingest text content',
        'GET /api/knowledge-base/documents - List all documents',
        'GET /api/knowledge-base/documents/:docId - Get document details',
        'DELETE /api/knowledge-base/documents/:docId - Delete document',
        'POST /api/knowledge-base/search - Search knowledge base',
        'GET /api/knowledge-base/stats - Get RAG statistics',
        'GET /api/knowledge-base/ingestion-info - Get ingestion configuration',
        'POST /api/knowledge-base/cache/clear - Clear RAG context cache',
        'GET /dashboard.html - Web dashboard',
        'POST /incoming-call - Twilio webhook',
        'POST /outbound-answer - Outbound call handler',
        'POST /call-status - Call status callback',
        'WSS /media-stream - Real-time audio'
      ]
    });
  });
}).catch(err => {
  logger.error('Failed to initialize services', { error: err.message });
  process.exit(1);
});
