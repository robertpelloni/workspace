import 'dotenv/config';
import Twilio from 'twilio';
import fs from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';
import logger from './utils/logger.js';
import { validateCustomer, validateCallingHours } from './utils/validation.js';

const __dirname = path.dirname(fileURLToPath(import.meta.url));
const client = Twilio(process.env.TWILIO_ACCOUNT_SID, process.env.TWILIO_AUTH_TOKEN);

const CALLING_HOURS = { start: 9, end: 20 };
const DELAY_BETWEEN_CALLS = 5000;

validateCallingHours(CALLING_HOURS.start, CALLING_HOURS.end);
logger.info('Outbound campaign initialized', { callingHours: CALLING_HOURS });

function loadCustomers() {
  const filePath = path.join(__dirname, '..', 'customers.json');

  if (!fs.existsSync(filePath)) {
    const example = [
      { name: "John Smith", phone: "+1234567890", equipment: "Riding mower", lastService: "2024-06-01" },
      { name: "Jane Doe", phone: "+1234567891", equipment: "Chainsaw", lastService: "2024-05-15" }
    ];
    fs.writeFileSync(filePath, JSON.stringify(example, null, 2));
    logger.info('Created customers.json example file');
    return [];
  }

  try {
    const data = fs.readFileSync(filePath, 'utf-8');
    const customers = JSON.parse(data);
    
    const validCustomers = [];
    for (const customer of customers) {
      const validation = validateCustomer(customer);
      if (validation.isValid) {
        validCustomers.push(customer);
      } else {
        logger.warn('Skipping invalid customer', { customer, errors: validation.errors });
      }
    }
    
    return validCustomers;
  } catch (err) {
    logger.error('Failed to load customers.json', { error: err.message });
    return [];
  }
}

function loadDNC() {
  const filePath = path.join(__dirname, '..', 'do-not-call.json');
  if (!fs.existsSync(filePath)) {
    fs.writeFileSync(filePath, '[]');
    logger.info('Created empty do-not-call.json');
    return new Set();
  }
  
  try {
    const data = fs.readFileSync(filePath, 'utf-8');
    return new Set(JSON.parse(data));
  } catch (err) {
    logger.error('Failed to load do-not-call.json', { error: err.message });
    return new Set();
  }
}

function isCallingHours() {
  const hour = new Date().getHours();
  return hour >= CALLING_HOURS.start && hour < CALLING_HOURS.end;
}

async function makeCall(customer) {
  logger.info('Initiating outbound call', { name: customer.name, phone: customer.phone });

  try {
    const call = await client.calls.create({
      to: customer.phone,
      from: process.env.TWILIO_PHONE_NUMBER,
      url: `${process.env.BASE_URL}/outbound-answer?name=${encodeURIComponent(customer.name)}&equipment=${encodeURIComponent(customer.equipment || '')}`,
      statusCallback: `${process.env.BASE_URL}/call-status`,
      statusCallbackEvent: ['completed', 'failed', 'busy', 'no-answer']
    });
    
    logger.info('Call initiated successfully', { sid: call.sid, phone: customer.phone });
    return call;
  } catch (err) {
    logger.error('Call initiation failed', { name: customer.name, phone: customer.phone, error: err.message });
    return null;
  }
}

async function runCampaign() {
  logger.info('Starting outbound campaign', {
    business: process.env.BUSINESS_NAME,
    from: process.env.TWILIO_PHONE_NUMBER
  });

  if (!isCallingHours()) {
    logger.warn('Outside calling hours, exiting campaign', {
      hours: `${CALLING_HOURS.start}:00 - ${CALLING_HOURS.end}:00`
    });
    process.exit(0);
  }

  const customers = loadCustomers();
  const dnc = loadDNC();
  const toCall = customers.filter(c => !dnc.has(c.phone));

  logger.info('Campaign customers loaded', {
    total: customers.length,
    toCall: toCall.length,
    dnc: dnc.size
  });

  if (toCall.length === 0) {
    logger.warn('No customers to call, exiting campaign');
    process.exit(0);
  }

  toCall.forEach((c, i) => logger.info(`Customer ${i + 1}`, { name: c.name, phone: c.phone, equipment: c.equipment || 'N/A' }));
  logger.info('Starting campaign in 5 seconds...');
  await new Promise(r => setTimeout(r, 5000));

  for (const customer of toCall) {
    if (!isCallingHours()) {
      logger.warn('End of calling hours, stopping campaign');
      break;
    }

    await makeCall(customer);

    if (toCall.indexOf(customer) < toCall.length - 1) {
      logger.info(`Waiting ${DELAY_BETWEEN_CALLS / 1000}s before next call`);
      await new Promise(r => setTimeout(r, DELAY_BETWEEN_CALLS));
    }
  }

  logger.info('Campaign completed');
}

runCampaign().catch(console.error);
