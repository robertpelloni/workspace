export function createMockTwilioEvent(eventType, overrides = {}) {
  const baseEvent = {
    event: eventType,
    timestamp: new Date().toISOString(),
  };

  return { ...baseEvent, ...overrides };
}

export function createMockIncomingCall(overrides = {}) {
  return {
    CallSid: 'CA' + generateRandomSid(),
    From: '+15551234567',
    To: '+15559876543',
    CallerName: 'Test Caller',
    ...overrides
  };
}

export function createMockCallStatus(status, overrides = {}) {
  return {
    CallSid: 'CA' + generateRandomSid(),
    CallStatus: status,
    CallDuration: Math.floor(Math.random() * 300) + 60,
    ...overrides
  };
}

export function createMockMediaStreamEvent(eventType, overrides = {}) {
  return {
    event: eventType,
    timestamp: new Date().toISOString(),
    ...overrides
  };
}

export function createMockStreamStart(overrides = {}) {
  return createMockMediaStreamEvent('start', {
    start: {
      streamSid: 'MZ' + generateRandomSid(),
      customParameters: {
        callSid: 'CA' + generateRandomSid(),
        from: '+15551234567',
        direction: 'inbound'
      }
    },
    ...overrides
  });
}

export function createMockMediaEvent(payload) {
  return createMockMediaStreamEvent('media', {
    media: {
      payload: payload,
      track: 'inbound'
    }
  });
}

export function createMockOpenAIEvent(eventType, data = {}) {
  return {
    type: eventType,
    ...data
  };
}

export function createMockSessionUpdate() {
  return {
    type: 'session.update',
    session: {
      turn_detection: { type: 'server_vad' },
      input_audio_format: 'g711_ulaw',
      output_audio_format: 'g711_ulaw',
      voice: 'alloy',
      instructions: 'Test instructions',
      modalities: ['text', 'audio'],
      temperature: 0.8
    }
  };
}

export function createMockResponseCreate() {
  return {
    type: 'response.create'
  };
}

export function createMockConversationItem(role, content) {
  return {
    type: 'conversation.item.create',
    item: {
      type: 'message',
      role: role,
      content: [
        { type: 'input_text', text: content }
      ]
    }
  };
}

export function createMockAudioDelta(delta) {
  return {
    type: 'response.audio.delta',
    delta: delta
  };
}

export function createMockTranscript(transcript, role = 'assistant') {
  return {
    type: role === 'assistant' ? 'response.audio_transcript.done' : 'conversation.item.input_audio_transcription.completed',
    transcript: transcript
  };
}

export function createMockError(error) {
  return {
    type: 'error',
    error: {
      message: error,
      type: 'invalid_request_error'
    }
  };
}

export function createMockPing() {
  return { type: 'ping' };
}

export function createMockPong() {
  return { type: 'pong' };
}

function generateRandomSid() {
  return Math.random().toString(36).substring(2, 34).toUpperCase();
}

export function createMockOutboundCall(customer, overrides = {}) {
  return {
    CallSid: 'CA' + generateRandomSid(),
    From: process.env.TWILIO_PHONE_NUMBER || '+15559876543',
    To: customer.phone,
    customerName: customer.name,
    equipment: customer.equipment || '',
    ...overrides
  };
}

export function createMockTwilioRequestBody(type, overrides = {}) {
  const baseBody = {
    CallSid: 'CA' + generateRandomSid(),
    AccountSid: 'AC' + generateRandomSid(),
    From: '+15551234567',
    To: process.env.TWILIO_PHONE_NUMBER || '+15559876543',
    CallStatus: type,
    Direction: 'inbound',
    ...overrides
  };

  return baseBody;
}
