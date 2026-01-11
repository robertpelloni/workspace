#!/usr/bin/env node
/**
 * Consensus Gate - Multi-Model Agreement Checker for CI/CD
 * 
 * This script validates that code changes have been reviewed/approved by
 * multiple AI models before merging, implementing the "Multi-Model Consensus"
 * principle from the AIOS architecture.
 * 
 * Environment Variables:
 *   MIN_MODELS       - Minimum number of models required (default: 2)
 *   ALLOW_STALE_DAYS - How old a review can be before considered stale (default: 365)
 *   SOFT_FAIL        - If "true", log warning but exit 0 (default: true)
 *   STATE_PATH       - Path to orchestrator state JSON (default: AI_COORDINATION/orchestrator_state.json)
 */

const fs = require('fs');
const path = require('path');

// Configuration from environment
const MIN_MODELS = parseInt(process.env.MIN_MODELS || '2', 10);
const ALLOW_STALE_DAYS = parseInt(process.env.ALLOW_STALE_DAYS || '365', 10);
const SOFT_FAIL = process.env.SOFT_FAIL !== 'false';
const STATE_PATH = process.env.STATE_PATH || 'AI_COORDINATION/orchestrator_state.json';

// Result structure
const result = {
  timestamp: new Date().toISOString(),
  policy: {
    minModels: MIN_MODELS,
    allowStaleDays: ALLOW_STALE_DAYS,
    softFail: SOFT_FAIL
  },
  state: null,
  validation: {
    passed: false,
    modelCount: 0,
    models: [],
    errors: [],
    warnings: []
  }
};

/**
 * Load orchestrator state from JSON file
 */
function loadState() {
  const statePath = path.resolve(process.cwd(), STATE_PATH);
  
  if (!fs.existsSync(statePath)) {
    result.validation.warnings.push(`State file not found: ${STATE_PATH}`);
    return null;
  }
  
  try {
    const content = fs.readFileSync(statePath, 'utf-8');
    return JSON.parse(content);
  } catch (err) {
    result.validation.errors.push(`Failed to parse state file: ${err.message}`);
    return null;
  }
}

/**
 * Validate consensus requirements
 */
function validateConsensus(state) {
  if (!state) {
    // No state file - check if this is expected (new repo, no AI coordination yet)
    result.validation.warnings.push('No orchestrator state available - consensus validation skipped');
    
    // In soft-fail mode with no state, we pass but warn
    if (SOFT_FAIL) {
      result.validation.passed = true;
      result.validation.warnings.push('SOFT_FAIL enabled: Passing despite missing state');
    }
    return;
  }
  
  result.state = state;
  
  // Extract model reviews from state
  const reviews = state.reviews || state.model_reviews || state.consensus || [];
  const models = new Set();
  const now = new Date();
  const staleThreshold = new Date(now.getTime() - (ALLOW_STALE_DAYS * 24 * 60 * 60 * 1000));
  
  for (const review of reviews) {
    const reviewDate = new Date(review.timestamp || review.date || review.created_at);
    
    if (reviewDate < staleThreshold) {
      result.validation.warnings.push(`Stale review from ${review.model}: ${reviewDate.toISOString()}`);
      continue;
    }
    
    if (review.approved || review.status === 'approved' || review.consensus === true) {
      models.add(review.model || review.model_name || review.provider);
    }
  }
  
  result.validation.models = Array.from(models);
  result.validation.modelCount = models.size;
  
  if (models.size >= MIN_MODELS) {
    result.validation.passed = true;
  } else {
    result.validation.errors.push(
      `Insufficient model consensus: ${models.size}/${MIN_MODELS} required`
    );
    
    if (SOFT_FAIL) {
      result.validation.passed = true;
      result.validation.warnings.push('SOFT_FAIL enabled: Passing despite insufficient consensus');
    }
  }
}

/**
 * Main execution
 */
function main() {
  console.log('=== Consensus Gate ===\n');
  
  const state = loadState();
  validateConsensus(state);
  
  // Output result as JSON
  console.log(JSON.stringify(result, null, 2));
  
  // Exit with appropriate code
  if (!result.validation.passed) {
    console.error('\n❌ Consensus gate FAILED');
    process.exit(1);
  } else if (result.validation.warnings.length > 0) {
    console.log('\n⚠️  Consensus gate PASSED with warnings');
    process.exit(0);
  } else {
    console.log('\n✅ Consensus gate PASSED');
    process.exit(0);
  }
}

main();
