// src/metrics.js
import client from 'prom-client';

const register = new client.Registry();

// Default metrics
client.collectDefaultMetrics({ register });

// Custom metrics
export const workflowCounter = new client.Counter({
  name: 'workflow_total',
  help: 'Total number of workflows executed',
  labelNames: ['template', 'status'],
  registers: [register]
});

export const workflowDuration = new client.Histogram({
  name: 'workflow_duration_seconds',
  help: 'Workflow execution duration',
  labelNames: ['template', 'status'],
  buckets: [5, 10, 30, 60, 300, 600, 1800, 3600],
  registers: [register]
});

export const julesTaskCounter = new client.Counter({
  name: 'jules_tasks_total',
  help: 'Total Jules tasks created',
  labelNames: ['status'],
  registers: [register]
});

export const actionCounter = new client.Counter({
  name: 'workflow_actions_total',
  help: 'Total workflow actions executed',
  labelNames: ['action_type', 'success'],
  registers: [register]
});

export const webhookCounter = new client.Counter({
  name: 'webhook_events_total',
  help: 'Total webhook events received',
  labelNames: ['source', 'event_type'],
  registers: [register]
});

export const activeWorkflows = new client.Gauge({
  name: 'workflow_active',
  help: 'Number of currently active workflows',
  registers: [register]
});

export async function getMetrics() {
  return register.metrics();
}

export const registerContentType = register.contentType;
