# Changelog

All notable changes to BrobocallZ will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Planned
- Comprehensive test suite
- Web dashboard for monitoring active calls
- Call recording and playback
- Analytics and reporting
- CRM integration
- Multi-language support
- Sentiment analysis
- Call transfer to human agents
- Voicemail system
- IVR navigation

## [1.2.0] - 2025-01-18

### Added
- Startup validation with environment variable checks
- Structured logging with Winston (console + file + rotation)
- Request validation for all API endpoints
- Call data cleanup with TTL (1 hour) to prevent memory leaks
- Graceful shutdown handlers (SIGTERM, SIGINT, uncaught exceptions)
- Unhandled rejection tracking
- Connection timeout and retry logic for OpenAI WebSocket
- Automatic reconnection with exponential backoff
- Keepalive ping/pong mechanism (30 second intervals)
- OpenAIWebSocketClient class for robust connection management
- Test utilities and mock Twilio/OpenAI event generators
- Comprehensive test-call.js script with interactive menu
- Customer data validation in outbound campaigns
- Cleanup statistics endpoint (/cleanup-stats)

### Changed
- Migrated all console.log to structured logger
- Enhanced error handling with try-catch blocks
- Improved WebSocket connection resilience
- Added max call limit enforcement (100 concurrent calls)

### Fixed
- Memory leak from failed call cleanup
- Missing error handling in webhook endpoints
- Undefined callSid access without null checks
- Empty customer list file handling
- Invalid JSON in customers.json crash

### Security
- Added request validation for all endpoints
- Implemented Twilio webhook signature verification (optional)
- Protected against invalid phone numbers
- Protected against malformed Twilio requests

## [1.0.0] - 2025-01-11

### Added
- Inbound call handling with AI receptionist
- Outbound call campaign system
- OpenAI Realtime API integration for voice AI
- Twilio Programmable Voice integration
- Real-time audio streaming via WebSockets
- Email transcript delivery via SendGrid
- Do Not Call (DNC) list support
- Business hours enforcement
- Customer management via JSON
- Health check endpoint
- Basic web dashboard
- Call status tracking

### Features
- AI-powered inbound answering service
- Automated outbound calling campaigns
- Real-time conversation transcripts
- Email notifications for completed calls
- Configurable business context and greetings
- Multi-customer outbound campaigns
- Calling hours restrictions (9 AM - 8 PM)
- Delay between calls (5 seconds)

### Configuration
- Twilio integration (Account SID, Auth Token, Phone Number)
- OpenAI API key for Realtime API
- SendGrid for email notifications
- Business name, greeting, and context customization
- Server port and base URL configuration
