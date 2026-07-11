# 🤙 BrobocallZ

AI-powered phone system for small businesses. Answer incoming calls with AI, make outbound calls to your customer list, get email transcripts.

## Quick Start

```bash
npm install
cp .env.example .env
# Edit .env with your credentials
npm run dev
```

## Setup Accounts

1. **Twilio** (https://console.twilio.com) - Get Account SID, Auth Token, buy a phone number (~$1/mo)
2. **OpenAI** (https://platform.openai.com/api-keys) - Get API key
3. **SendGrid** (https://sendgrid.com) - Free tier for emails (optional)

## Configure Twilio Webhook

1. Run: `ngrok http 3000`
2. Copy the https URL
3. In Twilio Console → Phone Numbers → Your Number → Voice webhook: `https://xxx.ngrok.io/incoming-call`

## Usage

**Inbound (answering service):**
```bash
npm run dev
# Call your Twilio number - AI answers!
```

**Outbound (call customers):**
```bash
# Edit customers.json with your list
npm run outbound
```

## Costs

| Service | Cost |
|---------|------|
| Twilio number | $1.15/mo |
| Twilio calls | ~$0.02/min |
| OpenAI Realtime | ~$0.30/min |
| **Per 3-min call** | **~$1.00** |

## Selling This Service

Charge $99-199/month per business. Your cost ~$30-50/month. Profit: $50-150/customer/month.

10 customers = $500-1500/month profit.
