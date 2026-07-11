import WebSocket from 'ws';
import logger from '../utils/logger.js';

const CONNECTION_TIMEOUT_MS = 10000;
const MAX_RETRIES = 3;
const INITIAL_RETRY_DELAY_MS = 1000;
const KEEPALIVE_INTERVAL_MS = 30000;

class OpenAIWebSocketClient {
  constructor(url, callSid, streamSid) {
    this.url = url;
    this.callSid = callSid;
    this.streamSid = streamSid;
    this.ws = null;
    this.retries = 0;
    this.isClosing = false;
    this.keepaliveTimer = null;
  }

  async connect() {
    return new Promise((resolve, reject) => {
      if (this.retries >= MAX_RETRIES) {
        logger.error('Max retries reached for OpenAI connection', { callSid: this.callSid });
        reject(new Error('Max retries exceeded'));
        return;
      }

      const retryDelay = Math.min(
        INITIAL_RETRY_DELAY_MS * Math.pow(2, this.retries),
        10000
      );

      if (this.retries > 0) {
        logger.info(`Retrying OpenAI connection`, { 
          attempt: this.retries + 1,
          delay: retryDelay,
          callSid: this.callSid 
        });
        await new Promise(r => setTimeout(r, retryDelay));
      }

      this.ws = new WebSocket(this.url, {
        headers: {
          'Authorization': `Bearer ${process.env.OPENAI_API_KEY}`,
          'OpenAI-Beta': 'realtime=v1'
        }
      });

      const connectionTimer = setTimeout(() => {
        if (this.ws && this.ws.readyState === WebSocket.CONNECTING) {
          logger.error('OpenAI connection timeout', { callSid: this.callSid, timeout: CONNECTION_TIMEOUT_MS });
          this.ws.close();
          reject(new Error('Connection timeout'));
        }
      }, CONNECTION_TIMEOUT_MS);

      this.ws.on('open', () => {
        clearTimeout(connectionTimer);
        this.retries = 0;
        logger.info('OpenAI WebSocket connected', { callSid: this.callSid, streamSid: this.streamSid });
        this.startKeepalive();
        resolve(this.ws);
      });

      this.ws.on('error', (err) => {
        clearTimeout(connectionTimer);
        this.retries++;
        logger.error('OpenAI WebSocket error', { 
          error: err.message, 
          attempt: this.retries,
          callSid: this.callSid 
        });
        reject(err);
      });

      this.ws.on('close', (code, reason) => {
        clearTimeout(connectionTimer);
        this.stopKeepalive();

        if (!this.isClosing && code !== 1000) {
          logger.warn('OpenAI WebSocket unexpectedly closed', { 
            code, 
            reason, 
            callSid: this.callSid 
          });
        }
      });
    });
  }

  send(message) {
    if (this.ws && this.ws.readyState === WebSocket.OPEN) {
      try {
        this.ws.send(message);
      } catch (err) {
        logger.error('Failed to send message to OpenAI', { 
          error: err.message, 
          callSid: this.callSid 
        });
      }
    } else {
      logger.warn('Cannot send message - WebSocket not connected', { callSid: this.callSid });
    }
  }

  startKeepalive() {
    this.stopKeepalive();
    
    this.keepaliveTimer = setInterval(() => {
      if (this.ws && this.ws.readyState === WebSocket.OPEN) {
        this.send(JSON.stringify({ type: 'ping' }));
        logger.debug('OpenAI keepalive ping sent', { callSid: this.callSid });
      }
    }, KEEPALIVE_INTERVAL_MS);

    this.ws.on('message', (data) => {
      try {
        const event = JSON.parse(data.toString());
        if (event.type === 'pong') {
          logger.debug('OpenAI keepalive pong received', { callSid: this.callSid });
        }
      } catch (err) {
        logger.debug('Failed to parse keepalive pong', { error: err.message });
      }
    });
  }

  stopKeepalive() {
    if (this.keepaliveTimer) {
      clearInterval(this.keepaliveTimer);
      this.keepaliveTimer = null;
    }
  }

  close() {
    this.isClosing = true;
    this.stopKeepalive();
    
    if (this.ws) {
      this.ws.close(1000, 'Normal closure');
      logger.info('OpenAI WebSocket closed', { callSid: this.callSid });
    }
  }

  getReadyState() {
    return this.ws ? this.ws.readyState : WebSocket.CLOSED;
  }
}

export default OpenAIWebSocketClient;
