import { activeCalls } from '../index.js';
import { sendTranscriptEmail } from './email.js';
import { validateTwilioRequest } from '../utils/validation.js';
import logger from '../utils/logger.js';
import { initializeRecording, updateRecordingDetails, downloadRecording } from './recording.js';

export function handleIncomingCall(req, res) {
  try {
    validateTwilioRequest(req.body, ['CallSid', 'From', 'To']);

    const { CallSid, From, To } = req.body;

    logger.info('Incoming call received', { CallSid, From, To });

    activeCalls.set(CallSid, {
      from: From,
      to: To,
      startTime: new Date(),
      transcript: [],
      direction: 'inbound'
    });

    const wsUrl = `wss://${req.headers.host}/media-stream`;

    const twiml = `<?xml version="1.0" encoding="UTF-8"?>
<Response>
  <Connect>
    <Stream url="${wsUrl}">
      <Parameter name="callSid" value="${CallSid}" />
      <Parameter name="from" value="${From}" />
      <Parameter name="direction" value="inbound" />
    </Stream>
  </Connect>
</Response>`;

    res.type('text/xml').send(twiml);
  } catch (err) {
    logger.error('Error in handleIncomingCall', { error: err.message, CallSid: req.body.CallSid });
    res.status(500).send('Error processing incoming call');
  }
}

export async function handleCallStatus(req, res) {
  try {
    validateTwilioRequest(req.body, ['CallSid', 'CallStatus']);

    const { CallSid, CallStatus, CallDuration, RecordingSid, RecordingUrl } = req.body;

    logger.info('Call status update', { CallSid, CallStatus, CallDuration });

    const callData = activeCalls.get(CallSid);

    if (callData) {
      updateCallStats(CallSid, CallStatus, callData.transcript?.length || 0);

      if (RecordingSid && RecordingUrl) {
        updateRecordingDetails(CallSid, RecordingSid, RecordingUrl);
      }
    }

    if (CallStatus === 'completed' || CallStatus === 'failed' || CallStatus === 'busy' || CallStatus === 'no-answer') {
      if (callData) {
        if (CallStatus === 'completed') {
          try {
            await sendTranscriptEmail(callData);
            logger.info('Transcript email sent', { CallSid });
          } catch (err) {
            logger.error('Email transmission failed', { error: err.message, CallSid });
          }

          try {
            await downloadRecording(CallSid);
          } catch (err) {
            logger.error('Recording download failed', { error: err.message, CallSid });
          }
        }
        activeCalls.delete(CallSid);
        logger.info('Call data cleaned up', { CallSid, CallStatus });
      }
    }

    res.sendStatus(200);
  } catch (err) {
    logger.error('Error in handleCallStatus', { error: err.message });
    res.status(500).send('Error processing call status');
  }
}
