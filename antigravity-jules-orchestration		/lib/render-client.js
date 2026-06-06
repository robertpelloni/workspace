/**
 * Render API Client
 * Integrates with Render.com for deployment monitoring and auto-fix capabilities
 *
 * Features:
 * - Secure API key storage (encrypted at rest)
 * - Service and deploy listing
 * - Build log retrieval
 * - Auto-fix for Jules PRs
 */

import https from 'https';
import { getCredential, storeCredential, deleteCredential, hasCredential } from './encryption.js';

const RENDER_API_HOST = 'api.render.com';
const RENDER_API_VERSION = 'v1';
const CREDENTIAL_NAME = 'render-api-key';
const WEBHOOK_SECRET_NAME = 'render-webhook-secret';

// Connection pooling for performance
const renderAgent = new https.Agent({
  keepAlive: true,
  keepAliveMsecs: 30000,
  maxSockets: 5,
  maxFreeSockets: 2
});

/**
 * Check if Render is configured
 */
export function isConfigured() {
  return hasCredential(CREDENTIAL_NAME);
}

/**
 * Connect Render integration by storing API key
 * @param {string} apiKey - Render API key
 * @param {string} webhookSecret - Optional webhook secret for signature verification
 */
export function connect(apiKey, webhookSecret = null) {
  if (!apiKey || typeof apiKey !== 'string' || apiKey.length < 20) {
    throw new Error('Invalid API key format');
  }

  // Validate API key format (Render keys start with 'rnd_')
  if (!apiKey.startsWith('rnd_')) {
    throw new Error('Invalid Render API key: must start with rnd_');
  }

  storeCredential(CREDENTIAL_NAME, apiKey);

  if (webhookSecret) {
    storeCredential(WEBHOOK_SECRET_NAME, webhookSecret);
  }

  return { success: true, connected: true, message: 'Render integration connected' };
}

/**
 * Disconnect Render integration
 */
export function disconnect() {
  deleteCredential(CREDENTIAL_NAME);
  deleteCredential(WEBHOOK_SECRET_NAME);
  return { success: true, disconnected: true, message: 'Render integration disconnected' };
}

/**
 * Get webhook secret for signature verification
 */
export function getWebhookSecret() {
  return getCredential(WEBHOOK_SECRET_NAME);
}

/**
 * Make authenticated request to Render API
 * @param {string} method - HTTP method
 * @param {string} path - API path (without version prefix)
 * @param {object} body - Request body for POST/PUT
 */
function renderRequest(method, path, body = null) {
  const apiKey = getCredential(CREDENTIAL_NAME);

  if (!apiKey) {
    return Promise.reject(new Error('Render not configured. Use render_connect to add API key.'));
  }

  return new Promise((resolve, reject) => {
    const options = {
      hostname: RENDER_API_HOST,
      port: 443,
      path: `/${RENDER_API_VERSION}${path}`,
      method: method,
      agent: renderAgent,
      headers: {
        'Authorization': `Bearer ${apiKey}`,
        'Accept': 'application/json',
        'Content-Type': 'application/json'
      }
    };

    console.log(`[Render API] ${method} ${path}`);

    const req = https.request(options, (response) => {
      let data = '';
      const MAX_RESPONSE_SIZE = 5 * 1024 * 1024; // 5MB limit

      response.on('data', chunk => {
        data += chunk;
        if (data.length > MAX_RESPONSE_SIZE) {
          response.destroy();
          reject(new Error('Response too large'));
        }
      });

      response.on('end', () => {
        // Handle rate limiting
        if (response.statusCode === 429) {
          const retryAfter = response.headers['retry-after'] || 60;
          reject(new Error(`Rate limited. Retry after ${retryAfter} seconds`));
          return;
        }

        if (response.statusCode >= 200 && response.statusCode < 300) {
          try {
            resolve(JSON.parse(data));
          } catch {
            resolve(data);
          }
        } else if (response.statusCode === 401) {
          reject(new Error('Invalid Render API key'));
        } else if (response.statusCode === 403) {
          reject(new Error('Render API access denied - check key permissions'));
        } else if (response.statusCode === 404) {
          reject(new Error('Resource not found'));
        } else {
          reject(new Error(`Render API error: ${response.statusCode} - ${data}`));
        }
      });
    });

    req.setTimeout(30000, () => {
      req.destroy();
      reject(new Error('Request timeout'));
    });

    req.on('error', (err) => {
      reject(new Error(`Render API request failed: ${err.message}`));
    });

    if (body) {
      const jsonBody = JSON.stringify(body);
      req.setHeader('Content-Length', Buffer.byteLength(jsonBody));
      req.write(jsonBody);
    }

    req.end();
  });
}

/**
 * List all services
 */
export async function listServices() {
  const response = await renderRequest('GET', '/services');
  return response.map(service => ({
    id: service.service.id,
    name: service.service.name,
    type: service.service.type,
    slug: service.service.slug,
    branch: service.service.branch,
    repo: service.service.repo,
    autoDeploy: service.service.autoDeploy,
    suspended: service.service.suspended,
    createdAt: service.service.createdAt,
    updatedAt: service.service.updatedAt
  }));
}

/**
 * Get service details
 * @param {string} serviceId - Service ID (srv-xxx)
 */
export async function getService(serviceId) {
  if (!serviceId || !serviceId.startsWith('srv-')) {
    throw new Error('Invalid service ID format');
  }

  const service = await renderRequest('GET', `/services/${serviceId}`);
  return {
    id: service.id,
    name: service.name,
    type: service.type,
    slug: service.slug,
    branch: service.branch,
    repo: service.repo,
    autoDeploy: service.autoDeploy,
    suspended: service.suspended,
    dashboardUrl: `https://dashboard.render.com/web/${serviceId}`,
    createdAt: service.createdAt,
    updatedAt: service.updatedAt
  };
}

/**
 * List deploys for a service
 * @param {string} serviceId - Service ID
 * @param {number} limit - Max number of deploys to return
 */
export async function listDeploys(serviceId, limit = 10) {
  if (!serviceId || !serviceId.startsWith('srv-')) {
    throw new Error('Invalid service ID format');
  }

  const deploys = await renderRequest('GET', `/services/${serviceId}/deploys?limit=${limit}`);
  return deploys.map(deploy => ({
    id: deploy.deploy.id,
    status: deploy.deploy.status,
    trigger: deploy.deploy.trigger,
    commit: deploy.deploy.commit,
    branch: deploy.deploy.branch || deploy.deploy.commit?.branch,
    createdAt: deploy.deploy.createdAt,
    updatedAt: deploy.deploy.updatedAt,
    finishedAt: deploy.deploy.finishedAt
  }));
}

/**
 * Get deploy details
 * @param {string} serviceId - Service ID
 * @param {string} deployId - Deploy ID
 */
export async function getDeploy(serviceId, deployId) {
  if (!serviceId || !serviceId.startsWith('srv-')) {
    throw new Error('Invalid service ID format');
  }
  if (!deployId || !deployId.startsWith('dep-')) {
    throw new Error('Invalid deploy ID format');
  }

  return await renderRequest('GET', `/services/${serviceId}/deploys/${deployId}`);
}

/**
 * Get build logs for a deploy
 * @param {string} serviceId - Service ID
 * @param {string} deployId - Deploy ID
 */
export async function getBuildLogs(serviceId, deployId) {
  if (!serviceId || !serviceId.startsWith('srv-')) {
    throw new Error('Invalid service ID format');
  }
  if (!deployId || !deployId.startsWith('dep-')) {
    throw new Error('Invalid deploy ID format');
  }

  // Render returns logs as array of log entries
  const logs = await renderRequest('GET', `/services/${serviceId}/deploys/${deployId}/logs`);

  // Format logs for easier reading
  const formattedLogs = logs.map(entry => ({
    timestamp: entry.timestamp,
    message: entry.message,
    level: entry.level || 'info'
  }));

  // Extract error messages
  const errors = formattedLogs.filter(l =>
    l.level === 'error' ||
    l.message?.toLowerCase().includes('error') ||
    l.message?.toLowerCase().includes('failed') ||
    l.message?.toLowerCase().includes('exception')
  );

  return {
    serviceId,
    deployId,
    totalLines: formattedLogs.length,
    logs: formattedLogs,
    errors: errors,
    hasErrors: errors.length > 0,
    summary: errors.length > 0
      ? `Build failed with ${errors.length} error(s)`
      : 'Build completed successfully'
  };
}

/**
 * Get the most recent failed deploy for a service
 * @param {string} serviceId - Service ID
 */
export async function getLatestFailedDeploy(serviceId) {
  const deploys = await listDeploys(serviceId, 10);
  const failed = deploys.find(d => d.status === 'build_failed' || d.status === 'deploy_failed');

  if (!failed) {
    return { found: false, message: 'No recent failed deploys' };
  }

  const logs = await getBuildLogs(serviceId, failed.id);

  return {
    found: true,
    deploy: failed,
    logs: logs,
    branch: failed.branch,
    commit: failed.commit
  };
}

/**
 * Check if a branch is a Jules PR branch
 * @param {string} branch - Branch name
 */
export function isJulesBranch(branch) {
  if (!branch || typeof branch !== 'string') return false;
  return branch.startsWith('jules/') ||
         branch.startsWith('jules-') ||
         branch.includes('/jules-') ||
         branch.includes('jules-fix') ||
         branch.includes('jules-feature');
}

/**
 * Analyze build logs and extract actionable errors
 * @param {object} logs - Logs from getBuildLogs
 */
export function analyzeErrors(logs) {
  if (!logs.hasErrors) {
    return { hasActionableErrors: false, errors: [] };
  }

  const errorPatterns = [
    { pattern: /npm ERR! (.*)/i, type: 'npm_error', fix: 'Check package.json and dependencies' },
    { pattern: /error TS(\d+): (.*)/i, type: 'typescript_error', fix: 'Fix TypeScript type errors' },
    { pattern: /SyntaxError: (.*)/i, type: 'syntax_error', fix: 'Fix syntax error in code' },
    { pattern: /Module not found: (.*)/i, type: 'import_error', fix: 'Fix import path or install missing package' },
    { pattern: /ESLint: (.*)/i, type: 'lint_error', fix: 'Fix linting errors' },
    { pattern: /ENOENT: no such file or directory, open '(.*)'/i, type: 'missing_file', fix: 'Create missing file' },
    { pattern: /Error: Cannot find module '(.*)'/i, type: 'missing_module', fix: 'Install missing module' },
    { pattern: /Build failed/i, type: 'build_failed', fix: 'Review build configuration' },
    { pattern: /test(s)? failed/i, type: 'test_failed', fix: 'Fix failing tests' }
  ];

  const analyzedErrors = [];

  for (const logEntry of logs.errors) {
    for (const { pattern, type, fix } of errorPatterns) {
      const match = logEntry.message?.match(pattern);
      if (match) {
        analyzedErrors.push({
          type,
          message: logEntry.message,
          extracted: match[1] || match[0],
          suggestedFix: fix,
          timestamp: logEntry.timestamp
        });
        break;
      }
    }
  }

  // If no specific patterns matched, include raw errors
  if (analyzedErrors.length === 0 && logs.errors.length > 0) {
    analyzedErrors.push(...logs.errors.slice(0, 5).map(e => ({
      type: 'unknown',
      message: e.message,
      suggestedFix: 'Review error message and fix'
    })));
  }

  return {
    hasActionableErrors: analyzedErrors.length > 0,
    errors: analyzedErrors,
    summary: `Found ${analyzedErrors.length} actionable error(s)`,
    promptContext: generateFixPrompt(analyzedErrors, logs)
  };
}

/**
 * Generate a prompt for Jules to fix the errors
 */
function generateFixPrompt(errors, logs) {
  let prompt = `## Build Failure Analysis\n\n`;
  prompt += `The Render build failed with the following errors:\n\n`;

  for (const error of errors) {
    prompt += `### ${error.type.replace(/_/g, ' ').toUpperCase()}\n`;
    prompt += `- **Error**: ${error.message}\n`;
    if (error.extracted) {
      prompt += `- **Details**: ${error.extracted}\n`;
    }
    prompt += `- **Suggested Fix**: ${error.suggestedFix}\n\n`;
  }

  prompt += `## Instructions\n`;
  prompt += `1. Analyze the build errors above\n`;
  prompt += `2. Identify the root cause in the code\n`;
  prompt += `3. Implement fixes for each error\n`;
  prompt += `4. Ensure the build will pass after fixes\n`;
  prompt += `5. Push the fix to the same branch\n`;

  return prompt;
}

export default {
  isConfigured,
  connect,
  disconnect,
  listServices,
  getService,
  listDeploys,
  getDeploy,
  getBuildLogs,
  getLatestFailedDeploy,
  isJulesBranch,
  analyzeErrors,
  getWebhookSecret
};
