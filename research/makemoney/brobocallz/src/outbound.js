/**
 * BrobocallZ - Outbound Calling System
 * Call a list of opted-in customers with AI voice
 */

import 'dotenv/config';
import Twilio from 'twilio';
import fs from 'fs';
import path from 'path';

const client = Twilio(process.env.TWILIO_ACCOUNT_SID, process.env.TWILIO_AUTH_TOKEN);

// ===========================================
// CONFIGURATION
// ===========================================

const CONFIG = {
  // Your Twilio phone number
  fromNumber: process.env.TWILIO_PHONE_NUMBER,
  
  // Your server URL (ngrok or production)
  baseUrl: process.env.BASE_URL,
  
  // Delay between calls (ms) - be nice to the phone system
  delayBetweenCalls: 5000,
  
  // Only call between these hours (local time)
  allowedHours: { start: 9, end: 20 }, // 9 AM to 8 PM
  
  // Max concurrent calls
  maxConcurrent: 1
};

// ===========================================
// CUSTOMER LIST
// ===========================================

/**
 * Load customer list from JSON file
 * Format: [{ name: "John", phone: "+1234567890", lastService: "2024-06-01" }, ...]
 */
function loadCustomerList() {
  const listPath = path.join(process.cwd(), 'customers.json');
  
  if (!fs.existsSync(listPath)) {
    console.log('📝 No customers.json found. Creating example file...');
    const example = [
      { 
        name: "John Smith", 
        phone: "+1234567890", 
        lastService: "2024-06-01",
        equipment: "Riding mower"
      },
      { 
        name: "Jane Doe", 
        phone: "+1234567891", 
        lastService: "2024-05-15",
        equipment: "Chainsaw"
      }
    ];
    fs.writeFileSync(listPath, JSON.stringify(example, null, 2));
    console.log('✅ Created customers.json - edit it with your real customer list!');
    return [];
  }
  
  return JSON.parse(fs.readFileSync(listPath, 'utf-8'));
}

/**
 * Load do-not-call list
 */
function loadDoNotCallList() {
  const dncPath = path.join(process.cwd(), 'do-not-call.json');
  
  if (!fs.existsSync(dncPath)) {
    fs.writeFileSync(dncPath, JSON.stringify([], null, 2));
    return new Set();
  }
  
  return new Set(JSON.parse(fs.readFileSync(dncPath, 'utf-8')));
}

/**
 * Add number to do-not-call list
 */
function addToDoNotCall(phone) {
  const dncPath = path.join(process.cwd(), 'do-not-call.json');
  const dnc = loadDoNotCallList();
  dnc.add(phone);
  fs.writeFileSync(dncPath, JSON.stringify([...dnc], null, 2));
  console.log(`🚫 Added ${phone} to do-not-call list`);
}

// ===========================================
// OUTBOUND CALLING
// ===========================================

/**
 * Check if we're within allowed calling hours
 */
function isWithinCallingHours() {
  const hour = new Date().getHours();
  return hour >= CONFIG.allowedHours.start && hour < CONFIG.allowedHours.end;
}

/**
 * Make an outbound call to a customer
 */
async function callCustomer(customer) {
  console.log(`📞 Calling ${customer.name} at ${customer.phone}...`);
  
  try {
    const call = await client.calls.create({
      to: customer.phone,
      from: CONFIG.fromNumber,
      url: `${CONFIG.baseUrl}/outbound-connect?name=${encodeURIComponent(customer.name)}&equipment=${encodeURIComponent(customer.equipment || '')}`,
      statusCallback: `${CONFIG.baseUrl}/call-status`,
      statusCallbackEvent: ['completed', 'failed', 'busy', 'no-answer']
    });
    
    console.log(`✅ Call initiated: ${call.sid}`);
    return call;
  } catch (err) {
    console.error(`❌ Failed to call ${customer.phone}: ${err.message}`);
    return null;
  }
}

/**
 * Run the outbound calling campaign
 */
async function runCampaign() {
  console.log(`
🤙 BrobocallZ Outbound Campaign
================================
Business: ${process.env.BUSINESS_NAME}
From: ${CONFIG.fromNumber}
Base URL: ${CONFIG.baseUrl}
  `);
  
  // Check calling hours
  if (!isWithinCallingHours()) {
    console.log(`⏰ Outside calling hours (${CONFIG.allowedHours.start}:00 - ${CONFIG.allowedHours.end}:00)`);
    console.log('Exiting. Run again during allowed hours.');
    process.exit(0);
  }
  
  // Load lists
  const customers = loadCustomerList();
  const doNotCall = loadDoNotCallList();
  
  // Filter out DNC numbers
  const toCall = customers.filter(c => !doNotCall.has(c.phone));
  
  console.log(`📋 ${toCall.length} customers to call (${doNotCall.size} on DNC list)`);
  
  if (toCall.length === 0) {
    console.log('No customers to call. Add customers to customers.json');
    process.exit(0);
  }
  
  // Confirm before starting
  console.log('\nCustomers to call:');
  toCall.forEach((c, i) => console.log(`  ${i + 1}. ${c.name} - ${c.phone}`));
  console.log('\nStarting in 5 seconds... (Ctrl+C to cancel)\n');
  
  await new Promise(r => setTimeout(r, 5000));
  
  // Make calls with delay
  for (const customer of toCall) {
    // Recheck calling hours
    if (!isWithinCallingHours()) {
      console.log('⏰ Reached end of calling hours. Stopping campaign.');
      break;
    }
    
    await callCustomer(customer);
    
    // Wait between calls
    console.log(`⏳ Waiting ${CONFIG.delayBetweenCalls / 1000}s before next call...`);
    await new Promise(r => setTimeout(r, CONFIG.delayBetweenCalls));
  }
  
  console.log('\n✅ Campaign complete!');
}

// ===========================================
// OUTBOUND WEBHOOK (add to index.js)
// ===========================================

/**
 * TwiML for outbound calls - customize the AI's opening
 * Add this route to your main server
 */
export function getOutboundTwiML(customerName, equipment) {
  const businessName = process.env.BUSINESS_NAME || 'our service';
  
  // This tells Twilio to connect to our WebSocket with custom context
  return `<?xml version="1.0" encoding="UTF-8"?>
<Response>
  <Connect>
    <Stream url="wss://${process.env.BASE_URL?.replace('https://', '')}/media-stream">
      <Parameter name="direction" value="outbound" />
      <Parameter name="customerName" value="${customerName}" />
      <Parameter name="equipment" value="${equipment}" />
    </Stream>
  </Connect>
</Response>`;
}

// Run campaign if called directly
runCampaign().catch(console.error);
