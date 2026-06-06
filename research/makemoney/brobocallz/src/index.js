/**
 * BrobocallZ - AI Call Handler
 * Main server for handling inbound calls via Twilio + OpenAI Realtime API
 */

import 'dotenv/config';
import express from 'express';
import { createServer } from 'http';
import { WebSocketServer } from 'ws';
import Twilio from 'twilio';
import { handleMediaStream } from './mediaStreamHandler.js';
import { sendTranscriptEmail } from './email.js';

const app = express();
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

const server = createServer(app);
const wss = new WebSocketServer({ server });

// Store active calls
const activeCalls = new Map();

// ===========================================
// TWILIO WEBHOOK ENDPOINTS
// ===========================================

/**
 * Handle incoming calls - Twilio hits this endpoint when someone calls
 */
app.post('/incoming-call', (req, res) => {
  const callSid = req.body.CallSid;
  const from = req.body.From;
  const to = req.body.To;
  
  console.log(`📞 Incoming call from ${from} to ${to} (${callSid})`);
  
  // Initialize call data
  activeCalls.set(callSid, {
    from,
    to,
    startTime: new Date(),
    transcript: [],
    audioChunks: []
  });
  
  // Return TwiML to connect the call to our WebSocket
  const twiml = `<?xml version="1.0" encoding="UTF-8"?>
<Response>
  <Connect>
    <Stream url="wss://${req.headers.host}/media-stream">
      <Parameter name="callSid" value="${callSid}" />
      <Parameter name="from" value="${from}" />
    </Stream>
  </Connect>
</Response>`;

  res.type('text/xml');
  res.send(twiml);
});

/**
 * Handle call status updates (completed, failed, etc.)
 */
app.post('/call-status', async (req, res) => {
  const { CallSid, CallStatus, CallDuration } = req.body;
  
  console.log(`📊 Call ${CallSid} status: ${CallStatus}, duration: ${CallDuration}s`);
  
  if (CallStatus === 'completed') {
    const callData = activeCalls.get(CallSid);
    if (callData) {
      // Send transcript email
      try {
        await sendTranscriptEmail(callData);
        console.log(`📧 Transcript sent for call ${CallSid}`);
      } catch (err) {
        console.error(`Failed to send transcript: ${err.message}`);
      }
      activeCalls.delete(CallSid);
    }
  }
  
  res.sendStatus(200);
});

/**
 * Health check endpoint
 */
app.get('/health', (req, res) => {
  res.json({ 
    status: 'ok', 
    service: 'BrobocallZ',
    activeCalls: activeCalls.size 
  });
});

/**
 * Dashboard - simple call log view
 */
app.get('/', (req, res) => {
  res.send(`
    <!DOCTYPE html>
    <html>
    <head>
      <title>BrobocallZ Dashboard</title>
      <style>
        body { font-family: system-ui; max-width: 800px; margin: 50px auto; padding: 20px; }
        h1 { color: #2563eb; }
        .status { padding: 10px; background: #dcfce7; border-radius: 8px; }
        .call { padding: 15px; margin: 10px 0; background: #f1f5f9; border-radius: 8px; }
      </style>
    </head>
    <body>
      <h1>🤙 BrobocallZ Dashboard</h1>
      <div class="status">
        <strong>Status:</strong> Running<br>
        <strong>Active Calls:</strong> ${activeCalls.size}<br>
        <strong>Business:</strong> ${process.env.BUSINESS_NAME || 'Not configured'}
      </div>
      <h2>Recent Calls</h2>
      <p>Call logs will appear here...</p>
    </body>
    </html>
  `);
});

// ===========================================
// WEBSOCKET HANDLER FOR MEDIA STREAMS
// ===========================================

wss.on('connection', (ws, req) => {
  console.log('🔌 WebSocket connection established');
  
  // Handle the media stream from Twilio
  handleMediaStream(ws, activeCalls);
});

// ===========================================
// START SERVER
// ===========================================

const PORT = process.env.PORT || 3000;

server.listen(PORT, () => {
  console.log(`
🤙 BrobocallZ Server Started!
============================
Port: ${PORT}
Business: ${process.env.BUSINESS_NAME || 'Not configured'}

Endpoints:
  POST /incoming-call  - Twilio webhook for incoming calls
  POST /call-status    - Twilio status callback
  GET  /health         - Health check
  GET  /               - Dashboard

Next steps:
  1. Run: ngrok http ${PORT}
  2. Set Twilio webhook to: https://your-ngrok-url/incoming-call
  3. Call your Twilio number!
  `);
});

export { activeCalls };
