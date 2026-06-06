import logger from '../logger.js';
import { activeCalls } from '../index.js';

export function handleVoicemail(req, res) {
  const { CallSid, From } = req.body;

  if (!CallSid) {
    return res.status(400).json({ error: 'Missing CallSid' });
  }

  logger.info('Voicemail request received', { CallSid, From });

  const callData = activeCalls.get(CallSid);
  if (!callData) {
    return res.status(400).json({ error: 'Call not found' });
  }

  if (callData.direction !== 'inbound') {
    logger.warn('Voicemail only available for inbound calls', { CallSid });
    return res.status(400).json({ error: 'Voicemail only for inbound calls' });
  }

  const voicemailMessage = `
    ${process.env.VOICEMAIL_GREETING || 'Thank you for calling! We could't reach you right now. Please leave a message with your name, phone number, and brief description of what you need, and we'll get back to you as soon as possible.'}
    
    ${process.env.VOICEMAIL_MESSAGE || 'To leave a message, press 1. For general inquiries, press 2. For service requests, press 3. If you prefer to be added to our do-not-call list to receive no more calls, press 4. To speak with a representative, press 5. At any time, you can leave a message and hang up.'}
  `;

  const twiml = `<?xml version="1.0" encoding="UTF-8"?>
<Response>
  <Gather inputAction="1">
    <Say voice="alice">${voicemailMessage}</Say>
    <Redirect action="gatherUrl"/>
  </Gather>
  <Gather inputAction="2">
    <Say voice="alice">You have no messages.</Say>
  </Gather>
  <Gather inputAction="3">
    <Say voice="alice">You have no messages.</Say>
  </Gather>
  <Gather inputAction="4">
    <Say voice="alice">You have no messages.</Say>
    <Pause length="2"/>
  </Gather>
  <Gather inputAction="5">
    <Say voice="alice">Thank you for calling ${process.env.BUSINESS_NAME || 'us'}.</Say>
  </Gather>
  <Hangup/>
</Response>`;

  logger.info('Sending voicemail TwiML', { CallSid, messageLength: voicemailMessage.length });

  res.type('text/xml').send(twiml);
}
