import { validateEnv } from './validation.js';

/**
 * Validate environment on startup
 */
try {
  validateEnv();
  console.log('✅ Environment validation passed');
} catch (error) {
  console.error('❌ Environment validation failed:');
  console.error(`   ${error.message}`);
  console.error('\nPlease check your .env file and ensure all required variables are set.');
  console.error('See .env.example for the required variables.\n');
  process.exit(1);
}
