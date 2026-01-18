# 🤙 BrobocallZ

AI-powered phone call handler for small businesses. Handle inbound calls with an AI receptionist, make outbound calls to opted-in customers, and get email transcripts of every conversation.

## Features

- **Inbound Call Handling**: AI answers calls, takes messages, handles FAQs
- **Outbound Calling**: Call your opted-in customer list with AI voice
- **Real-time Voice**: Uses OpenAI's Realtime API for natural conversation
- **Email Transcripts**: Get summaries of every call sent to your inbox
- **Multi-Business**: Configure for different businesses/clients

## Quick Start

### 1. Install Dependencies

```bash
npm install
```

### 2. Set Up Accounts

You'll need:
- **Twilio Account**: https://console.twilio.com (free trial available)
- **OpenAI API Key**: https://platform.openai.com/api-keys
- **SendGrid** (optional): https://sendgrid.com (free tier available)

### 3. Configure Environment

```bash
cp .env.example .env
# Edit .env with your credentials
```

### 4. Expose Local Server (for development)

```bash
# Install ngrok if you don't have it
npm install -g ngrok

# In one terminal, start the server
npm run dev

# In another terminal, expose it
ngrok http 3000
```

### 5. Configure Twilio

1. Go to your Twilio Console
2. Navigate to Phone Numbers → Manage → Active Numbers
3. Click your phone number
4. Under "Voice & Fax", set:
   - **A Call Comes In**: Webhook → `https://your-ngrok-url/incoming-call`
   - **Call Status Changes**: `https://your-ngrok-url/call-status`

### 6. Test It!

Call your Twilio phone number. The AI should answer!

## Outbound Calling

### Set Up Customer List

Create `customers.json`:

```json
[
  {
    "name": "John Smith",
    "phone": "+11234567890",
    "lastService": "2024-06-01",
    "equipment": "Riding mower"
  }
]
```

### Run Campaign

```bash
npm run outbound
```

**Important**: Only call customers who have given you permission!

## Configuration

### Business Customization

Edit `.env` to customize the AI's behavior:

```env
BUSINESS_NAME=Cliff's Small Engine Repair
BUSINESS_GREETING=Hi, thanks for calling Cliff's Small Engine Repair!
BUSINESS_CONTEXT=You are a helpful receptionist for a small engine repair shop...
```

### Calling Hours

The outbound system only calls between 9 AM - 8 PM local time. Edit `src/outbound.js` to change:

```javascript
allowedHours: { start: 9, end: 20 }
```

## Costs

| Service | Cost |
|---------|------|
| Twilio Phone Number | $1.15/month |
| Twilio Inbound Calls | $0.0085/min |
| Twilio Outbound Calls | $0.014/min |
| OpenAI Realtime API | ~$0.30/min |
| SendGrid | Free (100 emails/day) |

**Estimated cost per 3-minute call**: ~$0.95

## Selling This Service

Charge businesses $99-199/month for:
- Dedicated phone number
- 24/7 AI answering
- Email transcripts
- Call summaries

Your cost per customer: ~$30-50/month
Your profit: $50-150/month per customer

## Project Structure

```
brobocallz/
├── src/
│   ├── index.js           # Main server
│   ├── mediaStreamHandler.js  # Twilio ↔ OpenAI bridge
│   ├── outbound.js        # Outbound calling system
│   └── email.js           # Transcript emails
├── customers.json         # Your customer list
├── do-not-call.json      # DNC list (auto-managed)
├── .env                   # Your config (don't commit!)
└── .env.example          # Example config
```

## License

MIT - Built with ❤️ by the BrobocallZ team
