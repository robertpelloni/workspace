import sgMail from '@sendgrid/mail';

if (process.env.SENDGRID_API_KEY) {
  sgMail.setApiKey(process.env.SENDGRID_API_KEY);
}

export async function sendTranscriptEmail(callData) {
  if (!process.env.SENDGRID_API_KEY || !process.env.NOTIFICATION_EMAIL) {
    console.log('📧 Email not configured, logging transcript instead:');
    console.log(formatTranscript(callData));
    return;
  }

  const duration = Math.round((new Date() - callData.startTime) / 1000);
  const transcriptText = formatTranscript(callData);
  
  const msg = {
    to: process.env.NOTIFICATION_EMAIL,
    from: process.env.FROM_EMAIL || 'noreply@brobocallz.com',
    subject: `📞 ${callData.direction === 'outbound' ? 'Outbound' : 'Incoming'} Call from ${callData.from}`,
    text: transcriptText,
    html: `
      <div style="font-family: system-ui; max-width: 600px; margin: 0 auto;">
        <h2 style="color: #2563eb;">📞 Call Summary</h2>
        <table style="width: 100%; border-collapse: collapse;">
          <tr><td style="padding: 8px; border-bottom: 1px solid #e2e8f0;"><strong>From:</strong></td><td style="padding: 8px; border-bottom: 1px solid #e2e8f0;">${callData.from}</td></tr>
          <tr><td style="padding: 8px; border-bottom: 1px solid #e2e8f0;"><strong>To:</strong></td><td style="padding: 8px; border-bottom: 1px solid #e2e8f0;">${callData.to}</td></tr>
          <tr><td style="padding: 8px; border-bottom: 1px solid #e2e8f0;"><strong>Duration:</strong></td><td style="padding: 8px; border-bottom: 1px solid #e2e8f0;">${duration} seconds</td></tr>
          <tr><td style="padding: 8px; border-bottom: 1px solid #e2e8f0;"><strong>Time:</strong></td><td style="padding: 8px; border-bottom: 1px solid #e2e8f0;">${callData.startTime.toLocaleString()}</td></tr>
        </table>
        
        <h3 style="color: #334155; margin-top: 24px;">Transcript</h3>
        <div style="background: #f8fafc; padding: 16px; border-radius: 8px;">
          ${callData.transcript.map(t => `
            <p style="margin: 8px 0;">
              <strong style="color: ${t.role === 'assistant' ? '#2563eb' : '#059669'}">
                ${t.role === 'assistant' ? '🤖 Assistant' : '👤 Caller'}:
              </strong>
              ${t.content}
            </p>
          `).join('')}
        </div>
        
        <p style="color: #64748b; font-size: 12px; margin-top: 24px;">
          Sent by BrobocallZ - AI Call Handler
        </p>
      </div>
    `
  };

  await sgMail.send(msg);
}

function formatTranscript(callData) {
  const duration = Math.round((new Date() - callData.startTime) / 1000);
  
  let text = `
CALL SUMMARY
============
From: ${callData.from}
To: ${callData.to}
Duration: ${duration} seconds
Time: ${callData.startTime.toLocaleString()}
Direction: ${callData.direction || 'inbound'}

TRANSCRIPT
==========
`;

  for (const entry of callData.transcript) {
    const role = entry.role === 'assistant' ? 'Assistant' : 'Caller';
    text += `${role}: ${entry.content}\n\n`;
  }

  return text;
}
