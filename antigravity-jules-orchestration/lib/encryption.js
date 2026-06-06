/**
 * Encryption Module for Secure Credential Storage
 * Uses AES-256-GCM for authenticated encryption
 *
 * Security Features:
 * - Machine-specific key derivation
 * - Authenticated encryption (prevents tampering)
 * - Random IV for each encryption
 * - No plaintext stored on disk
 */

import crypto from 'crypto';
import fs from 'fs';
import path from 'path';
import os from 'os';

const ALGORITHM = 'aes-256-gcm';
const KEY_LENGTH = 32; // 256 bits
const IV_LENGTH = 16;
const SALT = 'jules-render-integration-salt-v1';
const CREDENTIALS_DIR = '.credentials';

/**
 * Derive encryption key from machine-specific data
 * This ensures credentials are bound to this machine
 */
function deriveKey() {
  // Combine multiple machine identifiers for key derivation
  const machineId = [
    os.hostname(),
    os.platform(),
    os.arch(),
    process.env.USER || process.env.USERNAME || 'default'
  ].join(':');

  return crypto.scryptSync(machineId, SALT, KEY_LENGTH);
}

/**
 * Encrypt plaintext using AES-256-GCM
 * @param {string} plaintext - Text to encrypt
 * @returns {string} - Encrypted string in format: iv:authTag:ciphertext
 */
export function encrypt(plaintext) {
  const key = deriveKey();
  const iv = crypto.randomBytes(IV_LENGTH);
  const cipher = crypto.createCipheriv(ALGORITHM, key, iv);

  let encrypted = cipher.update(plaintext, 'utf8', 'hex');
  encrypted += cipher.final('hex');

  const authTag = cipher.getAuthTag();

  // Format: iv:authTag:encrypted
  return `${iv.toString('hex')}:${authTag.toString('hex')}:${encrypted}`;
}

/**
 * Decrypt ciphertext using AES-256-GCM
 * @param {string} ciphertext - Encrypted string in format: iv:authTag:ciphertext
 * @returns {string} - Decrypted plaintext
 */
export function decrypt(ciphertext) {
  const parts = ciphertext.split(':');
  if (parts.length !== 3) {
    throw new Error('Invalid ciphertext format');
  }

  const [ivHex, authTagHex, encrypted] = parts;
  const key = deriveKey();
  const iv = Buffer.from(ivHex, 'hex');
  const authTag = Buffer.from(authTagHex, 'hex');

  const decipher = crypto.createDecipheriv(ALGORITHM, key, iv);
  decipher.setAuthTag(authTag);

  let decrypted = decipher.update(encrypted, 'hex', 'utf8');
  decrypted += decipher.final('utf8');

  return decrypted;
}

/**
 * Get credentials directory path
 */
function getCredentialsDir() {
  const dir = path.join(process.cwd(), CREDENTIALS_DIR);
  if (!fs.existsSync(dir)) {
    fs.mkdirSync(dir, { mode: 0o700 }); // Only owner can access
  }
  return dir;
}

/**
 * Store encrypted credential
 * @param {string} name - Credential name (e.g., 'render-api-key')
 * @param {string} value - Credential value
 */
export function storeCredential(name, value) {
  // Validate name to prevent path traversal
  if (!name || !/^[a-z0-9-]+$/.test(name)) {
    throw new Error('Invalid credential name: must be lowercase alphanumeric with hyphens');
  }

  const encrypted = encrypt(value);
  const filePath = path.join(getCredentialsDir(), `${name}.enc`);

  fs.writeFileSync(filePath, encrypted, { mode: 0o600 }); // Only owner can read/write

  return { success: true, name, stored: true };
}

/**
 * Retrieve encrypted credential
 * @param {string} name - Credential name
 * @returns {string|null} - Decrypted value or null if not found
 */
export function getCredential(name) {
  // Validate name to prevent path traversal
  if (!name || !/^[a-z0-9-]+$/.test(name)) {
    throw new Error('Invalid credential name');
  }

  const filePath = path.join(getCredentialsDir(), `${name}.enc`);

  if (!fs.existsSync(filePath)) {
    return null;
  }

  const encrypted = fs.readFileSync(filePath, 'utf8');
  return decrypt(encrypted);
}

/**
 * Delete stored credential
 * @param {string} name - Credential name
 */
export function deleteCredential(name) {
  // Validate name to prevent path traversal
  if (!name || !/^[a-z0-9-]+$/.test(name)) {
    throw new Error('Invalid credential name');
  }

  const filePath = path.join(getCredentialsDir(), `${name}.enc`);

  if (fs.existsSync(filePath)) {
    // Overwrite with random data before deletion (secure delete)
    const fileSize = fs.statSync(filePath).size;
    fs.writeFileSync(filePath, crypto.randomBytes(fileSize));
    fs.unlinkSync(filePath);
    return { success: true, deleted: true };
  }

  return { success: true, deleted: false, message: 'Credential not found' };
}

/**
 * List all stored credentials (names only, not values)
 */
export function listCredentials() {
  const dir = getCredentialsDir();

  if (!fs.existsSync(dir)) {
    return { credentials: [] };
  }

  const files = fs.readdirSync(dir)
    .filter(f => f.endsWith('.enc'))
    .map(f => f.replace('.enc', ''));

  return { credentials: files };
}

/**
 * Check if a credential exists
 * @param {string} name - Credential name
 */
export function hasCredential(name) {
  if (!name || !/^[a-z0-9-]+$/.test(name)) {
    return false;
  }

  const filePath = path.join(getCredentialsDir(), `${name}.enc`);
  return fs.existsSync(filePath);
}

export default {
  encrypt,
  decrypt,
  storeCredential,
  getCredential,
  deleteCredential,
  listCredentials,
  hasCredential
};
