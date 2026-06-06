/**
 * Unit Tests for Render Integration
 *
 * Tests cover:
 * - Encryption module (encrypt/decrypt, credentials storage)
 * - Render client (API validation, service listing)
 * - Auto-fix module (webhook verification, branch detection, error analysis)
 *
 * @module tests/unit/render-integration.test
 */

import { describe, it, beforeEach, afterEach, after } from 'node:test';
import assert from 'node:assert';
import crypto from 'crypto';
import fs from 'fs';
import path from 'path';
import os from 'os';

// =============================================================================
// Mock Setup
// =============================================================================

// Create temp credentials directory
const tempCredentialsDir = path.join(os.tmpdir(), 'test-credentials-' + Date.now());

// Store original cwd
const originalCwd = process.cwd();

function setupTempDir() {
  if (!fs.existsSync(tempCredentialsDir)) {
    fs.mkdirSync(tempCredentialsDir, { recursive: true });
  }
  process.chdir(tempCredentialsDir);
}

function cleanupTempDir() {
  process.chdir(originalCwd);
  if (fs.existsSync(tempCredentialsDir)) {
    fs.rmSync(tempCredentialsDir, { recursive: true, force: true });
  }
}

// =============================================================================
// Import modules dynamically to allow temp dir setup
// =============================================================================

let encryption;
let renderClient;
let renderAutofix;

async function loadModules() {
  const timestamp = Date.now();
  encryption = await import(`../../lib/encryption.js?t=${timestamp}`);
  renderClient = await import(`../../lib/render-client.js?t=${timestamp}`);
  renderAutofix = await import(`../../lib/render-autofix.js?t=${timestamp}`);
}

// =============================================================================
// Encryption Module Tests
// =============================================================================

describe('Encryption Module', () => {
  beforeEach(async () => {
    setupTempDir();
    await loadModules();
  });

  afterEach(() => {
    cleanupTempDir();
  });

  it('should encrypt and decrypt text correctly', () => {
    const plaintext = 'my-secret-api-key-12345';
    const encrypted = encryption.encrypt(plaintext);
    const decrypted = encryption.decrypt(encrypted);

    assert.strictEqual(decrypted, plaintext, 'Decrypted text should match original');
    assert.notStrictEqual(encrypted, plaintext, 'Encrypted text should not match original');
  });

  it('should produce different ciphertexts for same plaintext (random IV)', () => {
    const plaintext = 'test-value';
    const encrypted1 = encryption.encrypt(plaintext);
    const encrypted2 = encryption.encrypt(plaintext);

    assert.notStrictEqual(encrypted1, encrypted2, 'Same plaintext should produce different ciphertexts');
  });

  it('should store encrypted ciphertext in correct format', () => {
    const plaintext = 'test';
    const encrypted = encryption.encrypt(plaintext);
    const parts = encrypted.split(':');

    assert.strictEqual(parts.length, 3, 'Format should be iv:authTag:ciphertext');
    assert.ok(/^[a-f0-9]+$/.test(parts[0]), 'IV should be hex');
    assert.ok(/^[a-f0-9]+$/.test(parts[1]), 'Auth tag should be hex');
    assert.ok(/^[a-f0-9]+$/.test(parts[2]), 'Ciphertext should be hex');
  });

  it('should throw on invalid ciphertext format', () => {
    assert.throws(
      () => encryption.decrypt('invalid'),
      /Invalid ciphertext format/,
      'Should reject invalid format'
    );

    assert.throws(
      () => encryption.decrypt('a:b'),
      /Invalid ciphertext format/,
      'Should reject format with only 2 parts'
    );
  });

  it('should throw on tampered ciphertext', () => {
    const encrypted = encryption.encrypt('original');
    const [iv, authTag, ciphertext] = encrypted.split(':');

    // Tamper with the ciphertext
    const tampered = `${iv}:${authTag}:${'0'.repeat(ciphertext.length)}`;

    assert.throws(
      () => encryption.decrypt(tampered),
      /unable to authenticate|authentication tag/i,
      'Should detect tampering via auth tag'
    );
  });
});

// =============================================================================
// Credential Storage Tests
// =============================================================================

describe('Credential Storage', () => {
  beforeEach(async () => {
    setupTempDir();
    await loadModules();
  });

  afterEach(() => {
    cleanupTempDir();
  });

  it('should store and retrieve credentials', () => {
    const result = encryption.storeCredential('test-key', 'secret-value');
    assert.ok(result.success, 'Store should succeed');

    const retrieved = encryption.getCredential('test-key');
    assert.strictEqual(retrieved, 'secret-value', 'Should retrieve stored value');
  });

  it('should return null for non-existent credentials', () => {
    const value = encryption.getCredential('nonexistent');
    assert.strictEqual(value, null, 'Should return null for missing credential');
  });

  it('should delete credentials', () => {
    encryption.storeCredential('to-delete', 'value');
    assert.ok(encryption.hasCredential('to-delete'), 'Should exist before delete');

    encryption.deleteCredential('to-delete');
    assert.ok(!encryption.hasCredential('to-delete'), 'Should not exist after delete');
  });

  it('should validate credential names', () => {
    assert.throws(
      () => encryption.storeCredential('Invalid Name', 'value'),
      /Invalid credential name/,
      'Should reject names with spaces'
    );

    assert.throws(
      () => encryption.storeCredential('../traversal', 'value'),
      /Invalid credential name/,
      'Should reject path traversal attempts'
    );

    assert.throws(
      () => encryption.storeCredential('UPPERCASE', 'value'),
      /Invalid credential name/,
      'Should reject uppercase names'
    );
  });

  it('should list stored credentials', () => {
    encryption.storeCredential('key-one', 'value1');
    encryption.storeCredential('key-two', 'value2');

    const list = encryption.listCredentials();
    assert.ok(list.credentials.includes('key-one'), 'Should list key-one');
    assert.ok(list.credentials.includes('key-two'), 'Should list key-two');
  });

  it('should check credential existence', () => {
    encryption.storeCredential('exists', 'value');

    assert.ok(encryption.hasCredential('exists'), 'Should return true for existing');
    assert.ok(!encryption.hasCredential('not-exists'), 'Should return false for missing');
  });
});

// =============================================================================
// Render Client Tests
// =============================================================================

describe('Render Client', () => {
  beforeEach(async () => {
    setupTempDir();
    await loadModules();
  });

  afterEach(() => {
    renderClient.disconnect();
    cleanupTempDir();
  });

  it('should validate API key format', () => {
    assert.throws(
      () => renderClient.connect('rnd_short'),
      /Invalid API key/,
      'Should reject keys that are too short'
    );

    // Key is long enough but wrong prefix
    assert.throws(
      () => renderClient.connect('xxx_' + 'a'.repeat(20)),
      /must start with rnd_/,
      'Should reject keys not starting with rnd_'
    );
  });

  it('should connect with valid API key', () => {
    const result = renderClient.connect('rnd_' + 'a'.repeat(20));
    assert.ok(result.success, 'Should connect successfully');
    assert.ok(result.connected, 'Should indicate connected state');
  });

  it('should store webhook secret if provided', () => {
    renderClient.connect('rnd_' + 'a'.repeat(20), 'my-webhook-secret');
    const secret = renderClient.getWebhookSecret();
    assert.strictEqual(secret, 'my-webhook-secret', 'Should store webhook secret');
  });

  it('should disconnect and clear credentials', () => {
    renderClient.connect('rnd_' + 'a'.repeat(20), 'secret');
    assert.ok(renderClient.isConfigured(), 'Should be configured after connect');

    renderClient.disconnect();
    assert.ok(!renderClient.isConfigured(), 'Should not be configured after disconnect');
  });

  it('should detect Jules branches correctly', () => {
    assert.ok(renderClient.isJulesBranch('jules/fix-123'), 'jules/ prefix');
    assert.ok(renderClient.isJulesBranch('jules-feature'), 'jules- prefix');
    assert.ok(renderClient.isJulesBranch('feature/jules-fix'), 'contains /jules-');
    assert.ok(renderClient.isJulesBranch('my-jules-feature-branch'), 'contains jules-feature');
    assert.ok(!renderClient.isJulesBranch('main'), 'main is not Jules');
    assert.ok(!renderClient.isJulesBranch('feature/add-login'), 'regular feature is not Jules');
    assert.ok(!renderClient.isJulesBranch(null), 'null is not Jules');
  });
});

// =============================================================================
// Error Analysis Tests
// =============================================================================

describe('Error Analysis', () => {
  beforeEach(async () => {
    setupTempDir();
    await loadModules();
  });

  afterEach(() => {
    cleanupTempDir();
  });

  it('should detect no actionable errors in clean logs', () => {
    const logs = {
      hasErrors: false,
      errors: [],
    };

    const analysis = renderClient.analyzeErrors(logs);
    assert.ok(!analysis.hasActionableErrors, 'Should have no actionable errors');
  });

  it('should detect npm errors', () => {
    const logs = {
      hasErrors: true,
      errors: [
        { message: 'npm ERR! code ERESOLVE', level: 'error' },
      ],
    };

    const analysis = renderClient.analyzeErrors(logs);
    assert.ok(analysis.hasActionableErrors, 'Should have actionable errors');
    assert.strictEqual(analysis.errors[0].type, 'npm_error');
  });

  it('should detect TypeScript errors', () => {
    const logs = {
      hasErrors: true,
      errors: [
        { message: 'error TS2339: Property does not exist', level: 'error' },
      ],
    };

    const analysis = renderClient.analyzeErrors(logs);
    assert.strictEqual(analysis.errors[0].type, 'typescript_error');
  });

  it('should detect module not found errors', () => {
    const logs = {
      hasErrors: true,
      errors: [
        { message: "Module not found: Can't resolve '@mylib/core'", level: 'error' },
      ],
    };

    const analysis = renderClient.analyzeErrors(logs);
    assert.strictEqual(analysis.errors[0].type, 'import_error');
  });

  it('should generate fix prompt context', () => {
    const logs = {
      hasErrors: true,
      errors: [
        { message: 'npm ERR! missing dependency', level: 'error' },
      ],
    };

    const analysis = renderClient.analyzeErrors(logs);
    assert.ok(analysis.promptContext, 'Should generate prompt context');
    assert.ok(analysis.promptContext.includes('Build Failure Analysis'), 'Should have analysis header');
    assert.ok(analysis.promptContext.includes('NPM ERROR'), 'Should include error type');
  });
});

// =============================================================================
// Auto-Fix Module Tests
// =============================================================================

describe('Auto-Fix Module', () => {
  beforeEach(async () => {
    setupTempDir();
    await loadModules();
  });

  afterEach(() => {
    cleanupTempDir();
  });

  it('should verify webhook signature correctly', () => {
    // No secret configured - should skip verification
    const result1 = renderAutofix.verifyWebhookSignature('payload', null);
    assert.ok(result1, 'Should pass without secret');
  });

  it('should parse deploy webhook events', () => {
    const webhookBody = {
      type: 'deploy',
      data: {
        id: 'dep-123',
        serviceId: 'srv-456',
        status: 'build_failed',
        commit: {
          branch: 'jules/fix-issue-789',
        },
      },
    };

    const parsed = renderAutofix.parseWebhookEvent(webhookBody);
    assert.ok(parsed.isRelevant, 'Should be relevant');
    assert.strictEqual(parsed.event.type, 'build_failure');
    assert.strictEqual(parsed.event.branch, 'jules/fix-issue-789');
  });

  it('should reject non-deploy events', () => {
    const webhookBody = {
      type: 'service_created',
      data: {},
    };

    const parsed = renderAutofix.parseWebhookEvent(webhookBody);
    assert.ok(!parsed.isRelevant, 'Should not be relevant');
    assert.strictEqual(parsed.reason, 'Not a deploy event');
  });

  it('should reject successful deploys', () => {
    const webhookBody = {
      type: 'deploy',
      data: {
        status: 'live',
        commit: { branch: 'main' },
      },
    };

    const parsed = renderAutofix.parseWebhookEvent(webhookBody);
    assert.ok(!parsed.isRelevant, 'Successful deploy should not be relevant');
  });

  it('should reject non-Jules branches', () => {
    const webhookBody = {
      type: 'deploy',
      data: {
        status: 'build_failed',
        commit: { branch: 'feature/add-login' },
      },
    };

    const parsed = renderAutofix.parseWebhookEvent(webhookBody);
    assert.ok(!parsed.isRelevant, 'Non-Jules branch should not be relevant');
    assert.ok(parsed.reason.includes('not a Jules PR branch'));
  });

  it('should check auto-fix conditions', () => {
    // Not configured - should not auto-fix
    const check1 = renderAutofix.shouldAutoFix({ serviceId: 'srv-123' });
    assert.ok(!check1.shouldFix, 'Should not fix when not configured');

    // Enable and configure
    renderClient.connect('rnd_' + 'a'.repeat(20));
    renderAutofix.setAutoFixEnabled(true);

    const check2 = renderAutofix.shouldAutoFix({ serviceId: 'srv-123', deployId: 'dep-456' });
    assert.ok(check2.shouldFix, 'Should fix when properly configured');
  });

  it('should enable/disable auto-fix', () => {
    let status = renderAutofix.getAutoFixStatus();
    assert.ok(status.enabled, 'Should be enabled by default');

    renderAutofix.setAutoFixEnabled(false);
    status = renderAutofix.getAutoFixStatus();
    assert.ok(!status.enabled, 'Should be disabled after setting');

    renderAutofix.setAutoFixEnabled(true);
    status = renderAutofix.getAutoFixStatus();
    assert.ok(status.enabled, 'Should be re-enabled');
  });

  it('should manage monitored services', () => {
    const result1 = renderAutofix.addMonitoredService('srv-123');
    assert.ok(result1.success);
    assert.ok(result1.monitoredServices.includes('srv-123'));

    const result2 = renderAutofix.addMonitoredService('srv-456');
    assert.strictEqual(result2.monitoredServices.length, 2);

    const result3 = renderAutofix.removeMonitoredService('srv-123');
    assert.strictEqual(result3.monitoredServices.length, 1);
    assert.ok(!result3.monitoredServices.includes('srv-123'));
  });

  it('should validate service ID format', () => {
    assert.throws(
      () => renderAutofix.addMonitoredService('invalid-id'),
      /Invalid service ID format/
    );

    assert.throws(
      () => renderAutofix.addMonitoredService(null),
      /Invalid service ID format/
    );
  });
});

// =============================================================================
// Webhook Signature Verification Tests
// =============================================================================

describe('Webhook Signature Verification', () => {
  beforeEach(async () => {
    setupTempDir();
    await loadModules();
  });

  afterEach(() => {
    renderClient.disconnect();
    cleanupTempDir();
  });

  it('should verify valid signature', () => {
    const secret = 'test-webhook-secret';
    const payload = '{"type":"deploy","data":{}}';

    // Connect with webhook secret
    renderClient.connect('rnd_' + 'a'.repeat(20), secret);

    // Generate valid signature
    const expectedSignature = crypto
      .createHmac('sha256', secret)
      .update(payload)
      .digest('hex');

    const result = renderAutofix.verifyWebhookSignature(payload, `sha256=${expectedSignature}`);
    assert.ok(result, 'Should accept valid signature');
  });

  it('should reject invalid signature', () => {
    const secret = 'test-webhook-secret';
    const payload = '{"type":"deploy","data":{}}';

    renderClient.connect('rnd_' + 'a'.repeat(20), secret);

    const result = renderAutofix.verifyWebhookSignature(payload, 'sha256=invalid');
    assert.ok(!result, 'Should reject invalid signature');
  });

  it('should reject missing signature when secret is configured', () => {
    renderClient.connect('rnd_' + 'a'.repeat(20), 'secret');

    const result = renderAutofix.verifyWebhookSignature('payload', null);
    assert.ok(!result, 'Should reject missing signature');
  });
});

// =============================================================================
// Branch Filtering Edge Cases
// =============================================================================

describe('Branch Filtering Edge Cases', () => {
  beforeEach(async () => {
    setupTempDir();
    await loadModules();
  });

  afterEach(() => {
    cleanupTempDir();
  });

  it('should match jules-fix-v2 style branches', () => {
    assert.ok(renderClient.isJulesBranch('jules-fix-v2-issue-123'), 'jules-fix-v2 style');
    assert.ok(renderClient.isJulesBranch('jules-fix-owner-repo'), 'jules-fix-owner-repo');
  });

  it('should match nested jules branches', () => {
    assert.ok(renderClient.isJulesBranch('feature/jules-fix-123'), 'nested jules-fix');
    assert.ok(renderClient.isJulesBranch('bugfix/jules-feature-456'), 'nested jules-feature');
  });

  it('should NOT match partial matches', () => {
    assert.ok(!renderClient.isJulesBranch('myjules-branch'), 'no prefix match');
    assert.ok(!renderClient.isJulesBranch('julesman/feature'), 'julesman is not jules');
    assert.ok(!renderClient.isJulesBranch('pre-jules'), 'pre-jules is not jules');
  });

  it('should NOT match production branches', () => {
    assert.ok(!renderClient.isJulesBranch('main'), 'main');
    assert.ok(!renderClient.isJulesBranch('master'), 'master');
    assert.ok(!renderClient.isJulesBranch('develop'), 'develop');
    assert.ok(!renderClient.isJulesBranch('staging'), 'staging');
    assert.ok(!renderClient.isJulesBranch('production'), 'production');
  });

  it('should handle edge cases', () => {
    assert.ok(!renderClient.isJulesBranch(''), 'empty string');
    assert.ok(!renderClient.isJulesBranch(undefined), 'undefined');
    assert.ok(!renderClient.isJulesBranch(null), 'null');
    assert.ok(!renderClient.isJulesBranch(123), 'number');
  });
});

// =============================================================================
// Webhook Replay Prevention Tests
// =============================================================================

describe('Webhook Security', () => {
  beforeEach(async () => {
    setupTempDir();
    await loadModules();
  });

  afterEach(() => {
    renderClient.disconnect();
    cleanupTempDir();
  });

  it('should reject webhooks with stale timestamps', async () => {
    const staleTimestamp = new Date(Date.now() - 10 * 60 * 1000).toISOString(); // 10 min ago

    const webhookBody = {
      type: 'deploy',
      data: {
        id: 'dep-stale',
        serviceId: 'srv-123',
        status: 'build_failed',
        createdAt: staleTimestamp,
        commit: { branch: 'jules/fix-test' },
      },
    };

    renderClient.connect('rnd_' + 'a'.repeat(20));
    renderAutofix.setAutoFixEnabled(true);

    const mockReq = {
      body: webhookBody,
      headers: {},
      rawBody: JSON.stringify(webhookBody),
    };

    const result = await renderAutofix.handleWebhook(mockReq, async () => ({}), async () => ({}));

    assert.strictEqual(result.status, 400, 'Should reject stale webhook');
    assert.ok(result.error?.includes('timestamp'), 'Error should mention timestamp');
  });

  it('should reject duplicate webhooks (replay prevention)', async () => {
    const webhookBody = {
      type: 'deploy',
      data: {
        id: 'dep-duplicate-test',
        serviceId: 'srv-123',
        status: 'build_failed',
        createdAt: new Date().toISOString(),
        commit: { branch: 'jules/fix-test' },
      },
    };

    renderClient.connect('rnd_' + 'a'.repeat(20));
    renderAutofix.setAutoFixEnabled(true);

    const mockReq = {
      body: webhookBody,
      headers: {},
      rawBody: JSON.stringify(webhookBody),
    };

    // First call should succeed (or at least not be rejected as duplicate)
    const result1 = await renderAutofix.handleWebhook(
      mockReq,
      async () => ({ name: 'session-1' }),
      async () => ({})
    );

    // Second call with same deployId should be rejected as duplicate
    const result2 = await renderAutofix.handleWebhook(mockReq, async () => ({}), async () => ({}));

    assert.strictEqual(result2.message, 'Webhook already processed', 'Should detect duplicate');
  });

  it('should sanitize branch names with special characters', () => {
    const parsed = renderAutofix.parseWebhookEvent({
      type: 'deploy',
      data: {
        id: 'dep-test',
        serviceId: 'srv-123',
        status: 'build_failed',
        commit: { branch: 'jules/fix-<script>alert(1)</script>' },
      },
    });

    // Branch should match Jules pattern before sanitization
    assert.ok(parsed.isRelevant, 'Should be relevant');
    // The actual sanitization happens in handleWebhook, not parseWebhookEvent
    // This test verifies the parsing doesn't break on special chars
  });
});

// =============================================================================
// Error Analysis Edge Cases
// =============================================================================

describe('Error Analysis Edge Cases', () => {
  beforeEach(async () => {
    setupTempDir();
    await loadModules();
  });

  afterEach(() => {
    cleanupTempDir();
  });

  it('should handle logs with mixed error types', () => {
    const logs = {
      hasErrors: true,
      errors: [
        { message: 'npm ERR! code ERESOLVE', level: 'error' },
        { message: 'error TS2339: Property does not exist', level: 'error' },
        { message: "Module not found: Can't resolve '@lib/utils'", level: 'error' },
      ],
    };

    const analysis = renderClient.analyzeErrors(logs);
    assert.strictEqual(analysis.errors.length, 3, 'Should detect all 3 errors');
    assert.strictEqual(analysis.errors[0].type, 'npm_error');
    assert.strictEqual(analysis.errors[1].type, 'typescript_error');
    assert.strictEqual(analysis.errors[2].type, 'import_error');
  });

  it('should handle unknown error patterns', () => {
    const logs = {
      hasErrors: true,
      errors: [
        { message: 'Some weird error nobody has seen before', level: 'error' },
      ],
    };

    const analysis = renderClient.analyzeErrors(logs);
    assert.ok(analysis.hasActionableErrors, 'Should still have actionable errors');
    assert.strictEqual(analysis.errors[0].type, 'unknown');
  });

  it('should limit unknown errors to 5', () => {
    const logs = {
      hasErrors: true,
      errors: Array(10).fill(null).map((_, i) => ({
        message: `Unknown error ${i + 1}`,
        level: 'error',
      })),
    };

    const analysis = renderClient.analyzeErrors(logs);
    assert.ok(analysis.errors.length <= 5, 'Should limit to 5 unknown errors');
  });
});

console.log('Running render-integration tests...');

// Global cleanup to stop any running intervals
after(async () => {
  // Dynamically import to ensure module is loaded
  try {
    const autofix = await import('../../lib/render-autofix.js');
    if (autofix.stopCleanupInterval) {
      autofix.stopCleanupInterval();
    }
  } catch {
    // Ignore if module not loaded
  }
  cleanupTempDir();
});
