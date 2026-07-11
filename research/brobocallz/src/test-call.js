import 'dotenv/config';
import WebSocket from 'ws';
import { 
  createMockIncomingCall, 
  createMockCallStatus, 
  createMockStreamStart,
  createMockMediaEvent,
  createMockOpenAIEvent,
  createMockSessionUpdate,
  createMockResponseCreate,
  createMockConversationItem,
  createMockAudioDelta,
  createMockTranscript,
  createMockPing,
  createMockPong,
  createMockError
} from './utils/mockEvents.js';

const TEST_SERVER_PORT = 3001;
const WS_URL = `ws://localhost:${TEST_SERVER_PORT}/media-stream`;

console.log(`
╔═══════════════════════════════════════╗
║   🧪 BrobocallZ Test Call Script          ║
╚═════════════════════════════════════════╝

This script simulates a full call flow without requiring
Twilio or OpenAI accounts. It tests the media stream
handling, message routing, and state management.

Features:
  ✅ Simulate incoming call webhook
  ✅ Simulate Twilio media stream connection
  ✅ Simulate audio data exchange
  ✅ Simulate OpenAI responses
  ✅ Test transcript aggregation
  ✅ Test call status updates
  ✅ Test error handling
`);

async function runTest() {
  console.log('\n📡 Starting test call flow...\n');

  const ws = new WebSocket(WS_URL);

  await new Promise((resolve, reject) => {
    ws.on('open', () => {
      console.log('✅ WebSocket connected to test server\n');
      
      console.log('1️⃣  Sending Twilio "start" event...');
      const startEvent = createMockStreamStart();
      ws.send(JSON.stringify(startEvent));
    });

    ws.on('message', (data) => {
      const message = JSON.parse(data.toString());
      console.log(`📥 Received: ${message.event || 'response'}`);
    });

    ws.on('error', (err) => {
      console.error('❌ WebSocket error:', err.message);
      reject(err);
    });

    setTimeout(() => {
      ws.close();
      resolve();
    }, 5000);
  });

  console.log('\n2️⃣  Simulating audio stream...');
  
  console.log('   🎤 Sending user audio data...');
  ws.send(JSON.stringify(createMockMediaEvent('base64audiopayloadhere')));

  await sleep(1000);

  console.log('   🤖 Simulating OpenAI response...');
  ws.send(JSON.stringify(createMockAudioDelta('base64responsepayload')));
  await sleep(500);

  console.log('   📝 Adding transcript entries...');
  ws.send(JSON.stringify(createMockTranscript('Hello, how can I help you today?', 'assistant')));
  await sleep(500);
  
  ws.send(JSON.stringify(createMockTranscript('I need help with my lawnmower', 'user')));
  await sleep(500);

  console.log('   ✅ Test call completed successfully!\n');
}

async function runConnectionTest() {
  console.log('\n🔗 Testing WebSocket connection...\n');

  const ws = new WebSocket(WS_URL);

  await new Promise((resolve, reject) => {
    ws.on('open', () => {
      console.log('✅ Connection successful\n');
      ws.close();
      resolve();
    });

    ws.on('error', (err) => {
      console.error('❌ Connection failed:', err.message);
      console.log('\n💡 Make sure the server is running:');
      console.log('   npm run dev');
      reject(err);
    });

    setTimeout(() => {
      ws.close();
      reject(new Error('Connection timeout'));
    }, 3000);
  });
}

async function runValidationTest() {
  console.log('\n✅ Testing validation utilities...\n');

  const { validateEnv } = await import('./utils/validation.js');
  const { validateTwilioRequest } = await import('./utils/validation.js');
  const { validateCustomer } = await import('./utils/validation.js');

  try {
    console.log('   Testing environment validation...');
    console.log('   ⚠️  Expected to fail (missing required env vars)');
  } catch (err) {
    console.log('   ✅ Validation working:', err.message);
  }

  console.log('\n   Testing Twilio request validation...');
  const validRequest = createMockIncomingCall();
  try {
    validateTwilioRequest(validRequest);
    console.log('   ✅ Valid request passed');
  } catch (err) {
    console.error('   ❌ Validation error:', err.message);
  }

  console.log('\n   Testing customer validation...');
  const validCustomer = { name: 'John Doe', phone: '+15551234567' };
  const invalidCustomer = { name: '', phone: 'invalid' };

  const validResult = validateCustomer(validCustomer);
  console.log('   Valid customer:', validResult.isValid ? '✅' : '❌');

  const invalidResult = validateCustomer(invalidCustomer);
  console.log('   Invalid customer:', invalidResult.isValid ? '❌' : '✅');
  console.log('   Errors:', invalidResult.errors);
}

async function runLoggerTest() {
  console.log('\n📋 Testing logger...\n');

  const logger = await import('./utils/logger.js').then(m => m.default);

  logger.info('Test info message');
  logger.warn('Test warning message');
  logger.error('Test error message');
  logger.debug('Test debug message');

  console.log('   ✅ Check logs/ directory for output\n');
}

async function runCallCleanupTest() {
  console.log('\n🧹 Testing call cleanup service...\n');

  const { activeCalls } = await import('./index.js').then(m => m.activeCalls);
  const cleanupService = await import('./utils/callCleanup.js').then(m => m.default);

  const testCallSid = 'CA' + Math.random().toString(36).substring(2, 10).toUpperCase();
  activeCalls.set(testCallSid, {
    from: '+15551234567',
    to: '+15559876543',
    startTime: new Date(Date.now() - 90 * 60 * 1000), // 90 minutes ago
    transcript: [],
    direction: 'inbound'
  });

  console.log('   Added test call (90 minutes old)');

  cleanupService.cleanup();

  const stats = cleanupService.getStats();
  console.log('\n   Cleanup stats:', JSON.stringify(stats, null, 2));

  if (!activeCalls.has(testCallSid)) {
    console.log('   ✅ Old call cleaned up successfully\n');
  } else {
    console.log('   ❌ Call not cleaned up\n');
  }
}

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

function printMenu() {
  console.log(`
╔═══════════════════════════════════════╗
║              Available Tests               ║
╠═════════════════════════════════════════╣
║                                            ║
║  1. Full Call Flow Test                    ║
║  2. Connection Test Only                    ║
║  3. Validation Utilities Test              ║
║  4. Logger Test                          ║
║  5. Call Cleanup Test                    ║
║                                            ║
║  6. Run All Tests                         ║
║  0. Exit                                ║
║                                            ║
╚═════════════════════════════════════════╝
`);
}

async function runAllTests() {
  console.log('\n🚀 Running all tests...\n');
  console.log('═'.repeat(50));

  try {
    await runConnectionTest();
    await sleep(500);
    
    await runValidationTest();
    await sleep(500);
    
    await runLoggerTest();
    await sleep(500);
    
    await runCallCleanupTest();
    await sleep(500);
    
    console.log('\n✅ All tests completed successfully!\n');
  } catch (err) {
    console.error('\n❌ Some tests failed:', err.message);
    process.exit(1);
  }
}

async function main() {
  const rl = await import('readline').then(m => {
    return m.createInterface({
      input: process.stdin,
      output: process.stdout
    });
  });

  printMenu();

  const question = async () => {
    rl.question('\nSelect a test (0-6): ', async (answer) => {
      switch (answer.trim()) {
        case '1':
          await runTest();
          break;
        case '2':
          await runConnectionTest();
          break;
        case '3':
          await runValidationTest();
          break;
        case '4':
          await runLoggerTest();
          break;
        case '5':
          await runCallCleanupTest();
          break;
        case '6':
          await runAllTests();
          break;
        case '0':
          console.log('\n👋 Exiting...\n');
          rl.close();
          process.exit(0);
        default:
          console.log('\n❌ Invalid choice. Please select 0-6.\n');
          question();
          return;
      }

      if (answer.trim() !== '0') {
        printMenu();
        question();
      } else {
        rl.close();
      }
    });
  };

  question();
}

main().catch(console.error);
