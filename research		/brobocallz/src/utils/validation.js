import 'dotenv/config';
import crypto from 'crypto';

/**
 * Validate required environment variables on startup
 * @throws {Error} If required variables are missing
 */
export function validateEnv() {
  const required = [
    'TWILIO_ACCOUNT_SID',
    'TWILIO_AUTH_TOKEN',
    'TWILIO_PHONE_NUMBER',
    'OPENAI_API_KEY',
    'PORT'
  ];

  const missing = required.filter(key => !process.env[key]);

  if (missing.length > 0) {
    throw new Error(`Missing required environment variables: ${missing.join(', ')}`);
  }

  // Validate format
  if (!process.env.TWILIO_ACCOUNT_SID.startsWith('AC')) {
    throw new Error('TWILIO_ACCOUNT_SID must start with "AC"');
  }

  if (!process.env.OPENAI_API_KEY.startsWith('sk-')) {
    throw new Error('OPENAI_API_KEY must start with "sk-"');
  }

  if (!process.env.PORT || isNaN(parseInt(process.env.PORT))) {
    throw new Error('PORT must be a valid number');
  }
}

/**
 * Validate Twilio webhook request body
 * @param {object} body - Request body from Twilio
 * @param {string[]} requiredFields - Array of required field names
 * @throws {Error} If required fields are missing
 */
export function validateTwilioRequest(body, requiredFields = ['CallSid', 'From', 'To']) {
  if (!body || typeof body !== 'object') {
    throw new Error('Invalid Twilio webhook: body must be an object');
  }

  const missing = requiredFields.filter(field => !body[field]);

  if (missing.length > 0) {
    throw new Error(`Invalid Twilio webhook: missing required fields: ${missing.join(', ')}`);
  }

  // Validate CallSid format
  if (body.CallSid && !body.CallSid.startsWith('CA')) {
    throw new Error('Invalid CallSid format');
  }

  // Validate phone number format (basic check)
  if (body.From && !body.From.match(/^\+?\d{10,15}$/)) {
    throw new Error('Invalid From phone number format');
  }

  if (body.To && !body.To.match(/^\+?\d{10,15}$/)) {
    throw new Error('Invalid To phone number format');
  }
}

/**
 * Validate phone number format
 * @param {string} phone - Phone number to validate
 * @returns {boolean} True if valid
 */
export function isValidPhoneNumber(phone) {
  return typeof phone === 'string' && phone.match(/^\+?\d{10,15}$/);
}

/**
 * Validate calling hours configuration
 * @param {number} startHour - Start hour (0-23)
 * @param {number} endHour - End hour (0-23)
 * @throws {Error} If hours are invalid
 */
export function validateCallingHours(startHour, endHour) {
  if (typeof startHour !== 'number' || startHour < 0 || startHour > 23) {
    throw new Error('Start hour must be between 0 and 23');
  }

  if (typeof endHour !== 'number' || endHour < 0 || endHour > 23) {
    throw new Error('End hour must be between 0 and 23');
  }

  if (startHour >= endHour) {
    throw new Error('Start hour must be less than end hour');
  }
}

/**
 * Validate email address format
 * @param {string} email - Email to validate
 * @returns {boolean} True if valid
 */
export function isValidEmail(email) {
  const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
  return typeof email === 'string' && emailRegex.test(email);
}

/**
 * Validate Twilio request signature (optional security enhancement)
 * @param {string} url - Full URL of the request
 * @param {string} signature - X-Twilio-Signature header
 * @param {string} body - Raw request body
 * @param {string} authToken - Twilio Auth Token
 * @returns {boolean} True if signature is valid
 */
export function validateTwilioSignature(url, signature, body, authToken) {
  if (!signature || !authToken) {
    // Signature validation is optional, allow if not configured
    return true;
  }

  const expectedSignature = crypto
    .createHmac('sha1', authToken)
    .update(url + body)
    .digest('base64');

  return crypto.timingSafeEqual(
    Buffer.from(signature),
    Buffer.from(expectedSignature)
  );
}

/**
 * Validate customer data object
 * @param {object} customer - Customer object to validate
 * @returns {object} Validation result with isValid and errors
 */
export function validateCustomer(customer) {
  const errors = [];

  if (!customer.name || typeof customer.name !== 'string' || customer.name.trim().length === 0) {
    errors.push('Customer name is required and must be a non-empty string');
  }

  if (!customer.phone || !isValidPhoneNumber(customer.phone)) {
    errors.push('Customer phone is required and must be a valid phone number');
  }

  if (customer.equipment && typeof customer.equipment !== 'string') {
    errors.push('Customer equipment must be a string if provided');
  }

  if (customer.lastService) {
    const date = new Date(customer.lastService);
    if (isNaN(date.getTime())) {
      errors.push('Customer lastService must be a valid date');
    }
  }

  return {
    isValid: errors.length === 0,
    errors
  };
}

/**
 * Validate outbound campaign configuration
 * @param {object} config - Campaign configuration
 * @returns {object} Validation result
 */
export function validateCampaignConfig(config) {
  const errors = [];

  if (config.delayBetweenCalls && (typeof config.delayBetweenCalls !== 'number' || config.delayBetweenCalls < 1000)) {
    errors.push('delayBetweenCalls must be at least 1000ms');
  }

  if (config.maxConcurrentCalls && (typeof config.maxConcurrentCalls !== 'number' || config.maxConcurrentCalls < 1)) {
    errors.push('maxConcurrentCalls must be at least 1');
  }

  if (config.maxCalls && (typeof config.maxCalls !== 'number' || config.maxCalls < 1)) {
    errors.push('maxCalls must be at least 1');
  }

  if (config.callingHours) {
    try {
      validateCallingHours(config.callingHours.start, config.callingHours.end);
    } catch (err) {
      errors.push(`Invalid calling hours: ${err.message}`);
    }
  }

  return {
    isValid: errors.length === 0,
    errors
  };
}
