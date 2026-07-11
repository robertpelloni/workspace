/**
 * Email Service
 * Send call transcripts to business owners
 */

import sgMail from '@sendgrid/mail';

// Initialize SendGrid
if (process.env.SENDGRID_API_KEY) {
  sgMail.setApiKey(process.env.SENDGRID_API_KEY);
}

/**
 * Format transcript for email
 */
function formatTranscript(transcript) {
  if (!transcript || transcript.length === 0) {
    return 'No transcript available for this call.';
  }
  
  return transcript.map(entry => {
    const time = new Date(entry.timestamp).toLocaleTimeString();
    const role = entry.role === 'user' ? '📞 Caller' : '🤖 AI';
    return `[${time}] ${role}: ${entry.content}`;
  }).join('\n\n');
}

/**
 * Generate call summary using simple heuristics
 * (Could be enhanced with GPT summarization)
 */
function generateSummary(callData) {
  const { from, transcript, startTime } = callData;
  const duration = Math.round((new Date() - new Date(startTime)) / 1000);
  
  // Extract key info from transcript
  let callerName = 'Unknown';
  let purpose = 'General inquiry';
  let callbackRequested = false;
  
  const fullText = transcript.map(t => t.content).join(' ').toLowerCase();
  
  // Simple keyword detection
  if (fullText.includes('repair') || fullText.includes('fix')) {
    purpose = 'Repair request';
  } else if (fullText.includes('price') || fullText.includes('cost') || fullText.includes('quote')) {
    purpose = 'Pricing inquiry';
  } else if (fullText.includes('schedule') || fullText.includes('appointment')) {
    purpose = 'Scheduling';
  }
  
  if (fullText.includes('call me back') || fullText.includes('callback')) {
    callbackRequested = true;
  }
  
  // Try to find name
  const nameMatch = fullText.match(/(?:my name is|this is|i'm) (\w+)/i);
  if (nameMatch) {
    callerName = nameMatch[1].charAt(0).toUpperCase() + nameMatch[1].slice(1);
  }
  
  return {
    callerName,
    purpose,
    callbackRequested,
    duration,
    urgency: callbackRequested ? 'HIGH' : 'Normal'
  };
}

/**
 * Send transcript email to business owner
 */
export async function sendTranscriptEmail(callData) {
  if (!process.env.SENDGRID_API_KEY || !process.env.NOTIFICATION_EMAIL) {
    console.log('📧 Email not configured - skipping transcript send');
    console.log('Transcript:', formatTranscript(callData.transcript));
    return;
  }
  
  const summary = generateSummary(callData);
  const formattedTranscript = formatTranscript(callData.transcript);
  
  const urgencyEmoji = summary.urgency === 'HIGH' ? '🔴' : '🟢';
  
  const html = `
<!DOCTYPE html>
<html>
<head>
  <style>
    body { font-family: system-ui, -apple-system, sans-serif; max-width: 600px; margin: 0 auto; }
    .header { background: #2563eb; color: white; padding: 20px; border-radius: 8px 8px 0 0; }
    .content { padding: 20px; background: #f8fafc; }
    .summary { background: white; padding: 15px; border-radius: 8px; margin-bottom: 20px; }
    .summary-row { display: flex; justify-content: space-between; padding: 8px 0; border-bottom: 1px solid #e2e8f0; }
    .transcript { background: white; padding: 15px; border-radius: 8px; white-space: pre-wrap; font-size: 14px; }
    .urgent { background: #fef2f2; border-left: 4px solid #ef4444; }
    .footer { padding: 15px; text-align: center; color: #64748b; font-size: 12px; }
  </style>
</head>
<body>
  <div class="header">
    <h1 style="margin:0;">📞 New Call Received</h1>
    <p style="margin:5px 0 0 0;">${process.env.BUSINESS_NAME || 'BrobocallZ'}</p>
  </div>
  
  <div class="content">
    <div class="summary ${summary.urgency === 'HIGH' ? 'urgent' : ''}">
      <h2 style="margin-top:0;">${urgencyEmoji} Call Summary</h2>
      <div class="summary-row">
        <strong>From:</strong> <span>${callData.from}</span>
      </div>
      <div class="summary-row">
        <strong>Caller Name:</strong> <span>${summary.callerName}</span>
      </div>
      <div class="summary-row">
        <strong>Purpose:</strong> <span>${summary.purpose}</span>
      </div>
      <div class="summary-row">
        <strong>Duration:</strong> <span>${summary.duration} seconds</span>
      </div>
      <div class="summary-row">
        <strong>Callback Requested:</strong> <span>${summary.callbackRequested ? '✅ YES' : 'No'}</span>
      </div>
      <div class="summary-row">
        <strong>Time:</strong> <span>${new Date(callData.startTime).toLocaleString()}</span>
      </div>
    </div>
    
    <h3>📝 Full Transcript</h3>
    <div class="transcript">${formattedTranscript}</div>
  </div>
  
  <div class="footer">
    Powered by BrobocallZ AI Call Handler
  </div>
</body>
</html>
  `;
  
  const msg = {
    to: process.env.NOTIFICATION_EMAIL,
    from: process.env.SENDGRID_FROM_EMAIL || process.env.NOTIFICATION_EMAIL,
    subject: `${urgencyEmoji} Call from ${callData.from} - ${summary.purpose}`,
    text: `New call from ${callData.from}\n\nSummary:\n- Caller: ${summary.callerName}\n- Purpose: ${summary.purpose}\n- Duration: ${summary.duration}s\n- Callback: ${summary.callbackRequested ? 'YES' : 'No'}\n\nTranscript:\n${formattedTranscript}`,
    html
  };
  
  await sgMail.send(msg);
  console.log(`📧 Transcript emailed to ${process.env.NOTIFICATION_EMAIL}`);
}
