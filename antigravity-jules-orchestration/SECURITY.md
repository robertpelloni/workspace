# Security Documentation

**Version: 2.6.0** | antigravity-jules-orchestration

## Overview

This document describes the security measures implemented for credential storage and API integrations in the Jules Orchestration MCP server.

## Credential Storage (lib/encryption.js)

### Encryption Algorithm
- **Algorithm**: AES-256-GCM (Authenticated Encryption)
- **Key Length**: 256 bits (32 bytes)
- **IV Length**: 128 bits (16 bytes)
- **Authentication**: Built-in AEAD prevents tampering

### Key Derivation
The encryption key is derived using `crypto.scryptSync` with machine-specific identifiers:
- Hostname
- Platform (OS)
- Architecture
- Username

This ensures credentials are machine-bound and cannot be copied to another system.

**Known Limitation**: The key derivation uses predictable machine identifiers. Anyone with access to the machine and source code can derive the encryption key. This provides protection against:
- Copying encrypted files to another machine
- Offline attacks without machine access

This does NOT protect against:
- Privileged users on the same machine
- Attackers with code execution on the server

For production deployments with higher security requirements, consider using:
- Hardware Security Modules (HSMs)
- Cloud KMS (AWS KMS, GCP KMS, Azure Key Vault)
- Environment-based secrets management (HashiCorp Vault)

### Storage Format
Encrypted credentials are stored in `.credentials/*.enc` files with:
- **File permissions**: `0o600` (owner read/write only)
- **Directory permissions**: `0o700` (owner access only)
- **Format**: `iv:authTag:ciphertext` (hex-encoded)

### Secure Deletion
When credentials are deleted:
1. File is overwritten with random data
2. File is then unlinked (deleted)

### Path Traversal Prevention
Credential names are validated against `/^[a-z0-9-]+$/` to prevent directory traversal attacks.

## Render API Integration (lib/render-client.js)

### API Key Validation
- Keys must start with `rnd_` prefix
- Minimum length of 20 characters
- Stored encrypted (never in plaintext)

### Webhook Security
- HMAC-SHA256 signature verification
- Timing-safe comparison to prevent timing attacks
- Configurable webhook secret

### Request Security
- **Connection pooling**: Prevents socket exhaustion
- **Response size limit**: 5MB maximum
- **Request timeout**: 30 seconds
- **Rate limit handling**: Respects `retry-after` headers

### Error Handling
- 401: Invalid API key
- 403: Insufficient permissions
- 429: Rate limited (with retry guidance)
- 4xx/5xx: Sanitized error messages

## Auto-Fix Security (lib/render-autofix.js)

### Webhook Security
- **Signature Verification**: HMAC-SHA256 with timing-safe comparison
- **Replay Prevention**: Webhook IDs are tracked for 10 minutes
- **Timestamp Validation**: Webhooks older than 5 minutes are rejected
- **Raw Body Preservation**: Express middleware preserves raw body for accurate signature verification
- **Branch Sanitization**: Branch names are sanitized before use in prompts (alphanumeric, hyphens, underscores, slashes only)

### Branch Filtering
Only monitors branches matching Jules patterns:
- `jules/` prefix
- `jules-` prefix
- Contains `/jules-` or `jules-fix` or `jules-feature`

### Operation Limits
- **Max concurrent auto-fixes**: 10
- **Auto-fix timeout**: 5 minutes
- **Service allow-list**: Optional whitelist of monitored services
- **Webhook dedup window**: 10 minutes

### Duplicate Prevention
Active auto-fixes are tracked by `serviceId:deployId` to prevent duplicate operations.

## General Security Practices

### Input Validation
All user inputs are validated before processing:
- Service IDs must match `srv-*` format
- Deploy IDs must match `dep-*` format
- Credential names restricted to lowercase alphanumeric with hyphens

### No Credential Exposure
- API keys are NEVER logged
- API keys are NEVER returned in responses
- Credentials are only accessible via secure helper functions

### Circuit Breaker
The circuit breaker pattern prevents cascade failures:
- Trips after 5 consecutive failures
- 60-second cooldown before retry
- Protects downstream services

### Rate Limiting
- 100 requests per minute per IP on MCP endpoints
- Proper rate limit headers returned

## Environment Variables

| Variable | Purpose | Security Notes |
|----------|---------|----------------|
| `JULES_API_KEY` | Jules API authentication | Required, never log |
| `RENDER_API_KEY` | Render API (via encryption) | Use `render_connect` tool |
| `RENDER_WEBHOOK_SECRET` | Webhook verification | Use `render_connect` tool |

## Recommendations

### Production Deployment
1. Use HTTPS exclusively
2. Configure webhook secrets
3. Enable only required services via allow-list
4. Monitor auto-fix logs for anomalies
5. Rotate API keys periodically

### Local Development
1. Use `.env` files (never commit)
2. Test with non-production Render accounts
3. Verify webhook signatures even in development

## Reporting Security Issues

If you discover a security vulnerability, please report it responsibly via GitHub Security Advisories or by contacting the maintainers directly.
