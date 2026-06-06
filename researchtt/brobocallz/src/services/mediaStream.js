import WebSocket from 'ws';
import logger from '../utils/logger.js';
import * as rag from './rag.js';

const OPENAI_API_KEY = process.env.OPENAI_API_KEY;
const BASE_SYSTEM_PROMPT = `${process.env.BUSINESS_CONTEXT || 'You are a helpful AI receptionist.'}

Key behaviors:
- Be warm, friendly, and professional
- Keep responses concise (1-2 sentences max for phone conversation)
- If someone wants to schedule service, get their name, phone number, and brief description of the issue
- If you don't know something specific, offer to take a message for the owner
- Always end by confirming you'll pass along the message`;

function getSystemPrompt() {
  return BASE_SYSTEM_PROMPT;
}

export async function handleMediaStream(ws, activeCalls) {
  const { OpenAIWebSocketClient } = await import('../utils/openaiClient.js');

  let openaiClient = null;
  let streamSid = null;
  let callSid = null;
  let callData = null;
  let ragEnabled = rag.getRAGStats().enabled;
  let conversationHistory = [];
  let lastContextUpdate = 0;

  ws.on('message', async (message) => {
    try {
      const msg = JSON.parse(message);

      switch (msg.event) {
        case 'connected':
          logger.info('Twilio media stream connected', { streamSid });
          break;

        case 'start':
          streamSid = msg.start.streamSid;
          callSid = msg.start.customParameters?.callSid;
          callData = activeCalls.get(callSid);

          if (!callData) {
            logger.error('Call data not found for stream start', { callSid, streamSid });
            return;
          }

          logger.info('Media stream started', { streamSid, callSid });
          
          openaiClient = new OpenAIWebSocketClient.default(
            'wss://api.openai.com/v1/realtime?model=gpt-4o-realtime-preview-2024-10-01',
            callSid,
            streamSid
          );

          try {
            await openaiClient.connect();
            
            const sessionConfig = {
              type: 'session.update',
              session: {
                turn_detection: { type: 'server_vad' },
                input_audio_format: 'g711_ulaw',
                output_audio_format: 'g711_ulaw',
                voice: 'alloy',
                instructions: SYSTEM_PROMPT,
                modalities: ['text', 'audio'],
                temperature: 0.8
              }
            };
            openaiClient.send(JSON.stringify(sessionConfig));

            const greeting = process.env.BUSINESS_GREETING || "Hi, how can I help you today?";
            const initialMessage = {
              type: 'conversation.item.create',
              item: {
                type: 'message',
                role: 'assistant',
                content: [{ type: 'input_text', text: greeting }]
              }
            };
            openaiClient.send(JSON.stringify(initialMessage));
            openaiClient.send(JSON.stringify({ type: 'response.create' }));
          } catch (err) {
            logger.error('Failed to initialize OpenAI connection', { 
              error: err.message, 
              callSid 
            });
          }
          break;

        case 'media':
          if (openaiClient?.getReadyState() === WebSocket.OPEN) {
            const audioAppend = {
              type: 'input_audio_buffer.append',
              audio: msg.media.payload
            };
            openaiClient.send(JSON.stringify(audioAppend));
          }
          break;

        case 'stop':
          logger.info('Media stream stopped', { streamSid, callSid });
          if (openaiClient) {
            openaiClient.close();
          }
          break;
      }
    } catch (err) {
      logger.error('Media stream message parsing error', { error: err.message });
    }
  });

  ws.on('close', () => {
    logger.info('Twilio WebSocket closed', { streamSid, callSid });
    if (openaiClient) {
      openaiClient.close();
    }
  });

  if (openaiClient) {
    openaiClient.ws.on('message', async (data) => {
      try {
        const response = JSON.parse(data);

        switch (response.type) {
          case 'response.audio.delta':
            if (response.delta) {
              const audioMessage = {
                event: 'media',
                streamSid: streamSid,
                media: { payload: response.delta }
              };
              ws.send(JSON.stringify(audioMessage));
            }
            break;

          case 'response.audio_transcript.done':
            if (callData && response.transcript) {
              callData.transcript.push({
                role: 'assistant',
                content: response.transcript,
                timestamp: new Date().toISOString()
              });
            }
            logger.debug('AI response transcript', { transcript: response.transcript, callSid });
            break;

          case 'conversation.item.input_audio_transcription.completed':
            if (callData && response.transcript) {
              const transcript = response.transcript;

              callData.transcript.push({
                role: 'user',
                content: transcript,
                timestamp: new Date().toISOString()
              });

              conversationHistory.push({ role: 'user', content: transcript });

              if (ragEnabled && openaiClient?.getReadyState() === WebSocket.OPEN) {
                const now = Date.now();
                if (now - lastContextUpdate > 5000) {
                  try {
                    const ragResult = await rag.getContextForQuery(transcript, { topK: 3 });

                    if (ragResult.success && ragResult.context.length > 0) {
                      const augmentedPrompt = rag.augmentSystemPrompt(getSystemPrompt(), ragResult.context);

                      const sessionUpdate = {
                        type: 'session.update',
                        session: {
                          instructions: augmentedPrompt
                        }
                      };

                      openaiClient.send(JSON.stringify(sessionUpdate));
                      lastContextUpdate = now;

                      logger.info('RAG context injected', {
                        callSid,
                        contextLength: ragResult.context.length,
                        results: ragResult.results?.length
                      });

                      callData.ragContext = ragResult.context;
                    }
                  } catch (err) {
                    logger.error('Failed to inject RAG context', {
                      callSid,
                      error: err.message
                    });
                  }
                }
              }
            }
            logger.debug('User transcription completed', { transcript: response.transcript, callSid });
            break;

          case 'error':
            logger.error('OpenAI API error', { error: response.error, callSid });
            break;
        }
      } catch (err) {
        logger.error('OpenAI message parsing error', { error: err.message, callSid });
      }
    });

    openaiClient.ws.on('close', () => {
      logger.info('OpenAI connection closed', { callSid });
    });

    openaiClient.ws.on('error', (err) => {
      logger.error('OpenAI WebSocket error', { error: err.message, callSid });
    });
  }
}

async function connectToOpenAI(twilioWs, streamSid, callData) {
  return new Promise((resolve, reject) => {
    const url = 'wss://api.openai.com/v1/realtime?model=gpt-4o-realtime-preview-2024-10-01';
    
    const openaiWs = new WebSocket(url, {
      headers: {
        'Authorization': `Bearer ${OPENAI_API_KEY}`,
        'OpenAI-Beta': 'realtime=v1'
      }
    });

    const connectionTimeout = setTimeout(() => {
      openaiWs.close();
      reject(new Error('Connection timeout'));
    }, 10000);

    openaiWs.on('open', () => {
      clearTimeout(connectionTimeout);
      
      const sessionConfig = {
        type: 'session.update',
        session: {
          turn_detection: { type: 'server_vad' },
          input_audio_format: 'g711_ulaw',
          output_audio_format: 'g711_ulaw',
          voice: 'alloy',
          instructions: SYSTEM_PROMPT,
          modalities: ['text', 'audio'],
          temperature: 0.8
        }
      };
      openaiWs.send(JSON.stringify(sessionConfig));

      const greeting = process.env.BUSINESS_GREETING || "Hi, how can I help you today?";
      const initialMessage = {
        type: 'conversation.item.create',
        item: {
          type: 'message',
          role: 'assistant',
          content: [{ type: 'input_text', text: greeting }]
        }
      };
      openaiWs.send(JSON.stringify(initialMessage));
      openaiWs.send(JSON.stringify({ type: 'response.create' }));

      resolve(openaiWs);
    });

    openaiWs.on('message', (data) => {
      try {
        const response = JSON.parse(data);

        switch (response.type) {
          case 'response.audio.delta':
            if (response.delta) {
              const audioMessage = {
                event: 'media',
                streamSid: streamSid,
                media: { payload: response.delta }
              };
              twilioWs.send(JSON.stringify(audioMessage));
            }
            break;

          case 'response.audio_transcript.done':
            if (callData && response.transcript) {
              callData.transcript.push({
                role: 'assistant',
                content: response.transcript,
                timestamp: new Date().toISOString()
              });
            }
            logger.debug('AI response transcript', { transcript: response.transcript, callSid });
            break;

          case 'conversation.item.input_audio_transcription.completed':
            if (callData && response.transcript) {
              callData.transcript.push({
                role: 'user',
                content: response.transcript,
                timestamp: new Date().toISOString()
              });
            }
            logger.debug('User transcription completed', { transcript: response.transcript, callSid });
            break;

          case 'error':
            logger.error('OpenAI API error', { error: response.error, callSid });
            break;
        }
      } catch (err) {
        logger.error('OpenAI message parsing error', { error: err.message, callSid });
      }
    });

    openaiWs.on('close', () => {
      logger.info('OpenAI connection closed', { callSid });
    });

    openaiWs.on('error', (err) => {
      logger.error('OpenAI WebSocket error', { error: err.message, callSid });
    });
  });
}
