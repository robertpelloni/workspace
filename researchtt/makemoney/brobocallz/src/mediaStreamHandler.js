/**
 * Media Stream Handler
 * Bridges Twilio's audio stream with OpenAI's Realtime API
 */

import WebSocket from 'ws';

const OPENAI_API_KEY = process.env.OPENAI_API_KEY;
const OPENAI_REALTIME_URL = 'wss://api.openai.com/v1/realtime?model=gpt-4o-realtime-preview-2024-10-01';

/**
 * Handle incoming media stream from Twilio
 */
export function handleMediaStream(twilioWs, activeCalls) {
  let openaiWs = null;
  let streamSid = null;
  let callSid = null;
  let callerNumber = null;
  
  // Connect to OpenAI Realtime API
  function connectToOpenAI() {
    openaiWs = new WebSocket(OPENAI_REALTIME_URL, {
      headers: {
        'Authorization': `Bearer ${OPENAI_API_KEY}`,
        'OpenAI-Beta': 'realtime=v1'
      }
    });
    
    openaiWs.on('open', () => {
      console.log('🤖 Connected to OpenAI Realtime API');
      
      // Configure the session
      const sessionConfig = {
        type: 'session.update',
        session: {
          turn_detection: { type: 'server_vad' },
          input_audio_format: 'g711_ulaw',
          output_audio_format: 'g711_ulaw',
          voice: 'alloy',
          instructions: getSystemPrompt(),
          modalities: ['text', 'audio'],
          temperature: 0.8
        }
      };
      
      openaiWs.send(JSON.stringify(sessionConfig));
      
      // Send initial greeting
      setTimeout(() => {
        const greeting = {
          type: 'conversation.item.create',
          item: {
            type: 'message',
            role: 'user',
            content: [{
              type: 'input_text',
              text: 'The caller just connected. Greet them warmly and ask how you can help.'
            }]
          }
        };
        openaiWs.send(JSON.stringify(greeting));
        openaiWs.send(JSON.stringify({ type: 'response.create' }));
      }, 500);
    });
    
    openaiWs.on('message', (data) => {
      try {
        const event = JSON.parse(data.toString());
        handleOpenAIEvent(event);
      } catch (err) {
        console.error('Failed to parse OpenAI message:', err);
      }
    });
    
    openaiWs.on('error', (err) => {
      console.error('OpenAI WebSocket error:', err);
    });
    
    openaiWs.on('close', () => {
      console.log('🤖 OpenAI connection closed');
    });
  }
  
  /**
   * Handle events from OpenAI
   */
  function handleOpenAIEvent(event) {
    switch (event.type) {
      case 'response.audio.delta':
        // Send audio back to Twilio
        if (event.delta && streamSid) {
          const audioMessage = {
            event: 'media',
            streamSid: streamSid,
            media: {
              payload: event.delta
            }
          };
          twilioWs.send(JSON.stringify(audioMessage));
        }
        break;
        
      case 'response.audio_transcript.delta':
        // Log assistant's speech
        if (event.delta) {
          process.stdout.write(event.delta);
        }
        break;
        
      case 'response.audio_transcript.done':
        console.log(''); // New line after transcript
        // Store in call transcript
        if (callSid && activeCalls.has(callSid)) {
          const callData = activeCalls.get(callSid);
          callData.transcript.push({
            role: 'assistant',
            content: event.transcript,
            timestamp: new Date()
          });
        }
        break;
        
      case 'conversation.item.input_audio_transcription.completed':
        // Log caller's speech
        console.log(`📞 Caller: ${event.transcript}`);
        // Store in call transcript
        if (callSid && activeCalls.has(callSid)) {
          const callData = activeCalls.get(callSid);
          callData.transcript.push({
            role: 'user',
            content: event.transcript,
            timestamp: new Date()
          });
        }
        break;
        
      case 'error':
        console.error('OpenAI error:', event.error);
        break;
    }
  }
  
  /**
   * Handle messages from Twilio
   */
  twilioWs.on('message', (message) => {
    try {
      const data = JSON.parse(message.toString());
      
      switch (data.event) {
        case 'connected':
          console.log('📡 Twilio media stream connected');
          break;
          
        case 'start':
          streamSid = data.start.streamSid;
          callSid = data.start.customParameters?.callSid;
          callerNumber = data.start.customParameters?.from;
          console.log(`🎙️ Stream started: ${streamSid}, Call: ${callSid}`);
          
          // Now connect to OpenAI
          connectToOpenAI();
          break;
          
        case 'media':
          // Forward audio to OpenAI
          if (openaiWs && openaiWs.readyState === WebSocket.OPEN) {
            const audioAppend = {
              type: 'input_audio_buffer.append',
              audio: data.media.payload
            };
            openaiWs.send(JSON.stringify(audioAppend));
          }
          break;
          
        case 'stop':
          console.log('📴 Stream stopped');
          if (openaiWs) {
            openaiWs.close();
          }
          break;
      }
    } catch (err) {
      console.error('Failed to parse Twilio message:', err);
    }
  });
  
  twilioWs.on('close', () => {
    console.log('📴 Twilio WebSocket closed');
    if (openaiWs) {
      openaiWs.close();
    }
  });
  
  twilioWs.on('error', (err) => {
    console.error('Twilio WebSocket error:', err);
  });
}

/**
 * Generate system prompt for the AI
 */
function getSystemPrompt() {
  const businessName = process.env.BUSINESS_NAME || 'our business';
  const businessContext = process.env.BUSINESS_CONTEXT || 'You are a helpful receptionist.';
  
  return `You are a friendly, professional AI receptionist for ${businessName}.

${businessContext}

IMPORTANT GUIDELINES:
- Be warm, helpful, and conversational - sound human, not robotic
- Keep responses concise (1-2 sentences typically)
- If someone wants to schedule service, collect: their name, phone number, what they need fixed, and when works for them
- If you don't know something, say you'll have the owner call them back
- If someone asks for pricing, give general ranges if known, otherwise say the owner will provide a quote
- Always confirm you've taken their information correctly before ending
- If someone wants to be removed from our call list, acknowledge and confirm removal

NEVER:
- Pretend to be human if directly asked
- Make up specific prices or availability you don't know
- Keep people on the line unnecessarily`;
}
