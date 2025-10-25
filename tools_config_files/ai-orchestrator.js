#!/usr/bin/env node

/**
 * AI Orchestrator for Parallel Model Collaboration
 * Location: tools_config_files/ai-orchestrator.js
 * Purpose: Coordinates multiple AI models for parallel processing with security, logging, retries, backoff, and consensus
 * Note: This orchestrator is available but disabled by default in MCP settings. Prefer stable MCP servers first.
 */

'use strict';

const fs = require('fs');
const path = require('path');
const os = require('os');
const crypto = require('crypto');

class AIOrchestrator {
  constructor() {
    // Environment-driven configuration with safe Windows defaults (no tildes)
    this.projectRoot = process.env.PROJECT_ROOT || 'C:\\Users\\hyper\\fwber';
    this.coordinationDir = process.env.AI_COORDINATION_DIR || path.join(this.projectRoot, 'AI_COORDINATION');
    this.mcpConfigPath =
      process.env.MCP_CONFIG_PATH ||
      path.join(this.projectRoot, 'tools_config_files', 'enhanced_mcp_settings.json');

    // Numeric knobs with sane defaults
    this.maxConcurrency = parseIntSafe(process.env.AI_MAX_CONCURRENCY, 4);
    this.taskTimeoutMs = parseIntSafe(process.env.AI_TASK_TIMEOUT_MS, 300000); // 5 min
    this.modelTimeoutMs = parseIntSafe(process.env.AI_MODEL_TIMEOUT_MS, 30000); // 30s
    this.maxRetries = parseIntSafe(process.env.AI_MAX_RETRIES, 2);
    this.backoffBaseMs = parseIntSafe(process.env.AI_BACKOFF_BASE_MS, 500);
    this.backoffFactor = parseFloatSafe(process.env.AI_BACKOFF_FACTOR, 2.0);
    this.backoffMaxMs = parseIntSafe(process.env.AI_BACKOFF_MAX_MS, 15000);
    this.circuitFails = parseIntSafe(process.env.AI_CIRCUIT_FAILS, 3);
    this.circuitWindowMs = parseIntSafe(process.env.AI_CIRCUIT_WINDOW_MS, 120000); // 2 min
    this.circuitCooldownMs = parseIntSafe(process.env.AI_CIRCUIT_COOLDOWN_MS, 300000); // 5 min

    // Logging and redaction
    this.logJsonl = (process.env.AI_LOG_JSONL || '1') === '1';
    this.redactLogs = (process.env.AI_LOG_REDACT || '1') === '1';
    this.logDir = process.env.AI_LOG_DIR || path.join(this.coordinationDir, 'logs');
    this.logFile = path.join(this.logDir, 'orchestrator.jsonl');
    this.logMaxBytes = 10 * 1024 * 1024; // 10MB
    this.logMaxLines = 10000;
    this.logRotationKeep = 5;
    this.logLineCounter = 0;

    // State
    this.sessions = new Map();
    this.tasks = new Map();
    this.modelCapabilities = new Map();
    this.circuit = new Map(); // model -> {state, failures, lastFailureTs, openedTs}
    this.modelHealth = new Map(); // model -> {lastOkTs, failures}

    // Derived directories
    this.sessionsDir = path.join(this.coordinationDir, 'sessions');
    this.tasksDir = path.join(this.coordinationDir, 'tasks');
    this.decisionsDir = path.join(this.coordinationDir, 'decisions');
    this.communicationDir = path.join(this.coordinationDir, 'communication');

    try {
      // Validate projectRoot exists
      if (!fs.existsSync(this.projectRoot)) {
        throw new Error(`Project root not found at ${this.projectRoot}. Set PROJECT_ROOT to a valid absolute Windows path.`);
      }

      this.initializeDirectories();
      this.loadModelCapabilities();
    } catch (err) {
      safeConsoleError('[AI-Orchestrator] Initialization error:', err);
      throw err;
    }
  }

  initializeDirectories() {
    const dirs = [
      this.coordinationDir,
      this.sessionsDir,
      this.tasksDir,
      this.decisionsDir,
      this.communicationDir,
      this.logDir
    ];

    dirs.forEach((dir) => {
      try {
        if (!fs.existsSync(dir)) {
          fs.mkdirSync(dir, { recursive: true });
        }
        // Write permission check (atomic temp file)
        const tmp = path.join(dir, `.permcheck_${Date.now()}_${Math.random().toString(36).slice(2)}.tmp`);
        fs.writeFileSync(tmp, 'ok');
        fs.unlinkSync(tmp);
      } catch (e) {
        throw new Error(`Directory init/permission failed for ${dir}: ${e.message}`);
      }
    });

    // Ensure baseline files exist
    ensureFileExists(path.join(this.coordinationDir, 'orchestrator_state.json'), JSON.stringify({
      sessions: [],
      tasks: [],
      lastUpdated: new Date().toISOString(),
      schemaVersion: '1.1.0'
    }, null, 2));

    if (this.logJsonl) {
      ensureFileExists(this.logFile, '');
    }
  }

  loadModelCapabilities() {
    // Define model strengths, reliability, and freshness half-life for weighting
    this.modelCapabilities.set('claude-4.5', {
      tier: 1,
      strengths: ['complex-reasoning', 'architecture', 'orchestration', 'code-analysis'],
      weaknesses: ['speed', 'creative-ideation'],
      contextWindow: 200000,
      reliability: 0.97,
      freshnessHalfLifeMin: 120
    });

    this.modelCapabilities.set('gpt-5-codex-high', {
      tier: 2,
      strengths: ['code-generation', 'implementation', 'refactoring', 'testing'],
      weaknesses: ['architectural-reasoning', 'creative-problem-solving'],
      contextWindow: 128000,
      reliability: 0.95,
      freshnessHalfLifeMin: 120
    });

    this.modelCapabilities.set('cheetah', {
      tier: 3,
      strengths: ['performance-optimization', 'speed', 'efficiency', 'real-time-analysis'],
      weaknesses: ['complex-reasoning', 'creative-tasks'],
      contextWindow: 32000,
      reliability: 0.90,
      freshnessHalfLifeMin: 60
    });

    this.modelCapabilities.set('code-supernova-1-million', {
      tier: 4,
      strengths: ['project-context', 'continuity', 'memory', 'integration'],
      weaknesses: ['raw-power', 'speed'],
      contextWindow: 1000000,
      reliability: 0.92,
      freshnessHalfLifeMin: 240
    });

    this.modelCapabilities.set('gemini-2.5-flash', {
      tier: 5,
      strengths: ['rapid-prototyping', 'iteration', 'quick-analysis', 'creativity'],
      weaknesses: ['deep-reasoning', 'complex-architecture'],
      contextWindow: 32000,
      reliability: 0.93,
      freshnessHalfLifeMin: 90
    });
  }

  async orchestrateTask(taskDescription, priority = 'normal', options = {}) {
    const startTs = Date.now();
    // Input validation
    if (typeof taskDescription !== 'string' || taskDescription.trim().length === 0) {
      throw new Error('Invalid taskDescription: must be a non-empty string.');
    }
    if (!['low', 'normal', 'high'].includes(priority)) {
      throw new Error('Invalid priority: must be one of low|normal|high.');
    }

    const taskId = this.generateTaskId();
    const task = {
      id: taskId,
      description: taskDescription,
      priority,
      status: 'pending',
      created: new Date().toISOString(),
      models: [],
      results: [],
      consensus: null
    };
    this.tasks.set(taskId, task);
    this.saveTaskState();

    // Determine models using policy-driven routing
    const assignments = this.analyzeTaskAndAssign(taskDescription, priority);
    task.models = assignments.map((a) => a.model);
    this.saveTaskState();

    // Concurrency control: batch up to maxConcurrency
    const batches = chunk(assignments, Math.max(1, this.maxConcurrency));

    const runWithTaskTimeout = withTimeout(async () => {
      const allResults = [];
      for (const batch of batches) {
        const promises = batch.map((assignment) =>
          this.executeWithPolicies(assignment.model, assignment.task, taskId)
        );
        const settled = await Promise.allSettled(promises);
        settled.forEach((s) => allResults.push(s));
      }

      const consensus = this.buildConsensus(allResults, taskId);
      task.status = 'completed';
      task.consensus = consensus;
      task.completed = new Date().toISOString();
      task.results = allResults.map((r) => (r.status === 'fulfilled' ? r.value : { error: r.reason?.message || 'error' }));
      this.tasks.set(taskId, task);
      this.saveTaskState();

      this.log('info', 'consensus_finalized', { taskId, consensus, durationMs: Date.now() - startTs });
      this.log('info', 'task_completed', { taskId });

      return { taskId, consensus, results: allResults.length };
    }, this.taskTimeoutMs, `Task timeout after ${this.taskTimeoutMs}ms`); // task-level timeout

    this.log('info', 'task_started', { taskId, priority, description: elide(taskDescription, 1024) });

    try {
      return await runWithTaskTimeout();
    } catch (error) {
      task.status = 'failed';
      task.error = error.message;
      this.tasks.set(taskId, task);
      this.saveTaskState();
      this.log('error', 'task_failed', { taskId, error: error.message });
      throw error;
    }
  }

  analyzeTaskAndAssign(taskDescription, priority = 'normal') {
    // Load routing policy from MCP settings
    const routing = this.loadRoutingFromConfig();
    const tags = deriveTags(taskDescription);
    const seen = new Set();
    const assignments = [];

    const addModelsForTag = (tag, prio) => {
      const list = routing.modelRouting[tag] || [];
      list.forEach((model) => {
        if (!seen.has(model) && !this.isCircuitOpen(model)) {
          seen.add(model);
          assignments.push({
            model,
            task: `${capitalize(tag)}: ${taskDescription}`,
            priority: prio
          });
        }
      });
    };

    // Primary mapping from tags
    tags.forEach((t) => addModelsForTag(t, priority));
    // Fallbacks if none selected
    if (assignments.length === 0) {
      const fallbacks = routing.fallbackMapping || {};
      const fbTags = ['reasoning', 'analysis', 'implementation'];
      for (const t of fbTags) {
        const list = fallbacks[t] || [];
        for (const model of list) {
          if (!seen.has(model) && !this.isCircuitOpen(model)) {
            seen.add(model);
            assignments.push({
              model,
              task: `Fallback ${capitalize(t)}: ${taskDescription}`,
              priority: priority
            });
          }
        }
        if (assignments.length > 0) break;
      }
    }

    // If still none, include an alternative perspective with gemini-2.5-flash if available
    if (assignments.length < 1 && !this.isCircuitOpen('gemini-2.5-flash')) {
      assignments.push({
        model: 'gemini-2.5-flash',
        task: `Alternative Analysis: ${taskDescription}`,
        priority: 'low'
      });
    }

    // Cap by a soft max (4)
    return assignments.slice(0, 4);
  }

  async executeWithPolicies(modelName, subTask, taskId) {
    // Circuit breaker skip
    if (this.isCircuitOpen(modelName)) {
      this.log('warn', 'model_skipped_circuit_open', { model: modelName, taskId });
      return Promise.reject(new Error(`Circuit open for ${modelName}`));
    }

    // Per-model execution with timeout and retries
    let attempt = 0;
    let lastError = null;
    const start = Date.now();

    while (attempt <= this.maxRetries) {
      try {
        this.log('info', 'model_consult_started', { model: modelName, taskId, attempt });

        const exec = withTimeout(async () => {
          const res = await this.consultModel(modelName, subTask, taskId, attempt);
          return res;
        }, this.modelTimeoutMs, `Model ${modelName} timeout after ${this.modelTimeoutMs}ms`);

        const result = await exec();
        // success -> reset circuit stats
        this.noteModelSuccess(modelName);
        this.log('info', 'model_consult_finished', {
          model: modelName,
          taskId,
          attempt,
          durationMs: Date.now() - start
        });
        return result;
      } catch (err) {
        lastError = err;
        this.noteModelFailure(modelName);
        this.log('warn', 'model_consult_failed', {
          model: modelName,
          taskId,
          attempt,
          error: err.message
        });
        if (attempt === this.maxRetries) break;

        const backoff = computeBackoff(this.backoffBaseMs, this.backoffFactor, attempt, this.backoffMaxMs, true);
        await sleep(backoff);
        attempt += 1;
      }
    }

    // Trip circuit if necessary
    this.maybeOpenCircuit(modelName);
    throw lastError || new Error(`Unknown failure consulting model ${modelName}`);
  }

  async consultModel(modelName, task, taskId, attempt = 0) {
    // NOTE: Placeholder for real MCP integrations. For now, simulate model response.
    // Sanitize payload and limit input size
    const sanitizedTask = elide(String(task), 65536); // 64KB cap
    const capabilities = this.modelCapabilities.get(modelName) || { tier: 5, reliability: 0.9, freshnessHalfLifeMin: 120 };

    // Simulate response
    const mockResponse = {
      model: modelName,
      taskId,
      response: `Mock response from ${modelName} for: ${sanitizedTask}`,
      confidence: Math.min(1, 0.7 + Math.random() * 0.3),
      timestamp: new Date().toISOString(),
      capabilities
    };

    // Persist session file atomically
    const sessionFile = path.join(this.sessionsDir, `${safeFile(modelName)}_${taskId}.json`);
    writeFileAtomic(sessionFile, JSON.stringify(mockResponse, null, 2));

    return mockResponse;
  }

  buildConsensus(results, taskId) {
    const successful = results.filter((r) => r.status === 'fulfilled').map((r) => r.value);
    const failed = results.filter((r) => r.status === 'rejected');

    if (failed.length > 0) {
      this.log('warn', 'some_models_failed', { taskId, failedCount: failed.length });
    }

    if (successful.length === 0) {
      return {
        overallConfidence: 0,
        modelCount: 0,
        failedModels: failed.length,
        consensusMethod: 'none',
        recommendation: 'review_required',
        timestamp: new Date().toISOString()
      };
    }

    if (successful.length === 1) {
      const s = successful[0];
      const overallConfidence = clamp01(s.confidence || 0.8);
      return {
        overallConfidence,
        modelCount: 1,
        failedModels: failed.length,
        consensusMethod: 'single_model',
        recommendation: overallConfidence > 0.7 ? 'proceed' : 'review_required',
        timestamp: new Date().toISOString(),
        primaryRecommendation: { model: s.model, response: s.response }
      };
    }

    // Weighted consensus: confidence * weight, weight from reliability and freshness
    const now = Date.now();
    const scores = successful.map((s) => {
      const reliability = (s.capabilities && s.capabilities.reliability) || 0.9;
      const halfLifeMin = (s.capabilities && s.capabilities.freshnessHalfLifeMin) || 120;
      const ts = Date.parse(s.timestamp) || now;
      const deltaMs = Math.max(0, now - ts);
      const freshness = Math.exp(-deltaMs / (halfLifeMin * 60 * 1000));
      const weight = 0.6 * reliability + 0.4 * freshness;
      const score = (s.confidence || 0.8) * weight;
      return { s, weight, score };
    });

    // Outlier dampening by median absolute deviation
    const confs = successful.map((s) => s.confidence || 0.8);
    const med = median(confs);
    const mad = median(confs.map((c) => Math.abs(c - med))) || 0;
    const dampened = scores.map((x) => {
      const dev = Math.abs((x.s.confidence || 0.8) - med);
      if (mad > 0 && dev > 2 * mad) {
        return { ...x, weight: x.weight * 0.5, score: (x.s.confidence || 0.8) * (x.weight * 0.5) };
      }
      return x;
    });

    const totalWeight = dampened.reduce((sum, x) => sum + x.weight, 0) || 1;
    const overallConfidence = clamp01(dampened.reduce((sum, x) => sum + x.s.confidence * x.weight, 0) / totalWeight);

    dampened.sort((a, b) => {
      if (b.score !== a.score) return b.score - a.score;
      const ta = Date.parse(a.s.timestamp) || 0;
      const tb = Date.parse(b.s.timestamp) || 0;
      if (ta !== tb) return ta - tb;
      return String(a.s.model).localeCompare(String(b.s.model));
    });

    const consensus = {
      overallConfidence,
      modelCount: successful.length,
      failedModels: failed.length,
      consensusMethod: 'weighted_reliability_freshness',
      recommendation: overallConfidence > this.getConsensusThreshold() ? 'proceed' : 'review_required',
      timestamp: new Date().toISOString(),
      primaryRecommendation: {
        model: dampened[0].s.model,
        response: dampened[0].s.response
      }
    };

    return consensus;
  }

  generateTaskId() {
    if (crypto.randomUUID) {
      return `task_${crypto.randomUUID()}`;
    }
    return `task_${Date.now()}_${Math.random().toString(36).substr(2, 9)}`;
  }

  saveTaskState() {
    const state = {
      sessions: Array.from(this.sessions.entries()),
      tasks: Array.from(this.tasks.entries()),
      lastUpdated: new Date().toISOString(),
      schemaVersion: '1.1.0'
    };

    const stateFile = path.join(this.coordinationDir, 'orchestrator_state.json');
    const content = JSON.stringify(state, null, 2);

    // Rotate by size (>5MB) or too many tasks (>2000)
    try {
      let rotate = false;
      if (fs.existsSync(stateFile)) {
        const stats = fs.statSync(stateFile);
        if (stats.size > 5 * 1024 * 1024) rotate = true;
      }
      if (state.tasks.length > 2000) rotate = true;

      if (rotate) {
        rotateFile(stateFile, 3);
      }
    } catch (_) {
      // ignore rotation errors
    }

    writeFileAtomic(stateFile, content);
  }

  getActiveSessions() {
    return Array.from(this.tasks.values()).filter((task) => task.status === 'in_progress');
  }

  getTaskStatus(taskId) {
    return this.tasks.get(taskId) || null;
  }

  // ----------------- helpers: routing, circuit, logging -----------------

  loadRoutingFromConfig() {
    try {
      const raw = fs.readFileSync(this.mcpConfigPath, 'utf8');
      const json = JSON.parse(raw);
      const orch = json.orchestration || {};
      const modelRouting = orch.modelRouting || {};
      const fallbackMapping = orch.fallbackMapping || {};
      return {
        modelRouting,
        fallbackMapping,
        consensusThreshold: typeof orch.consensusThreshold === 'number' ? orch.consensusThreshold : 0.7
      };
    } catch (e) {
      // Fallback routing
      return {
        modelRouting: {
          implementation: ['gpt-5-codex-high', 'grok-4-code'],
          architecture: ['claude-4.5', 'gemini-2.5-pro'],
          analysis: ['claude-4.5', 'gemini-2.5-pro'],
          creative: ['gemini-2.5-flash', 'claude-4.5'],
          fast: ['gemini-2.5-flash', 'grok-code-fast-1'],
          reasoning: ['claude-4.5', 'gemini-2.5-pro'],
          performance: ['cheetah', 'gpt-5-codex-high'],
          context: ['code-supernova-1-million', 'claude-4.5']
        },
        fallbackMapping: {
          implementation: ['gpt-5-codex-medium', 'claude-4.5'],
          architecture: ['claude-4.5'],
          analysis: ['gemini-2.5-pro']
        },
        consensusThreshold: 0.7
      };
    }
  }

  getConsensusThreshold() {
    const conf = this.loadRoutingFromConfig();
    return conf.consensusThreshold || 0.7;
  }

  isCircuitOpen(model) {
    const st = this.circuit.get(model);
    if (!st) return false;
    if (st.state !== 'open') return false;
    const now = Date.now();
    if (now - st.openedTs >= this.circuitCooldownMs) {
      // Half-open
      this.circuit.set(model, { state: 'half-open', failures: 0, lastFailureTs: now, openedTs: st.openedTs });
      return false;
    }
    return true;
    }

  maybeOpenCircuit(model) {
    const now = Date.now();
    const mh = this.modelHealth.get(model) || { lastOkTs: 0, failures: [] };
    // drop failures older than window
    mh.failures = mh.failures.filter((t) => now - t <= this.circuitWindowMs);
    if (mh.failures.length >= this.circuitFails) {
      this.circuit.set(model, { state: 'open', failures: mh.failures.length, lastFailureTs: now, openedTs: now });
      this.log('warn', 'circuit_opened', { model, failures: mh.failures.length });
    }
    this.modelHealth.set(model, mh);
  }

  noteModelFailure(model) {
    const now = Date.now();
    const mh = this.modelHealth.get(model) || { lastOkTs: 0, failures: [] };
    mh.failures.push(now);
    this.modelHealth.set(model, mh);
  }

  noteModelSuccess(model) {
    const mh = this.modelHealth.get(model) || { lastOkTs: 0, failures: [] };
    mh.lastOkTs = Date.now();
    mh.failures = [];
    if (this.circuit.get(model)?.state) {
      this.circuit.delete(model);
      this.log('info', 'circuit_closed', { model });
    }
    this.modelHealth.set(model, mh);
  }

  log(level, event, obj = {}) {
    if (!this.logJsonl) return;
    try {
      const line = JSON.stringify(redact({
        ts: new Date().toISOString(),
        level,
        event,
        ...obj
      }, this.redactLogs)) + os.EOL;

      rotateLogIfNeeded(this.logFile, this.logMaxBytes, this.logRotationKeep);
      fs.appendFileSync(this.logFile, line);
      this.logLineCounter += 1;
      if (this.logLineCounter >= this.logMaxLines) {
        rotateLogIfNeeded(this.logFile, this.logMaxBytes, this.logRotationKeep);
        this.logLineCounter = 0;
      }
    } catch {
      // best-effort
    }
  }
}

// ----------------- Utilities -----------------

function parseIntSafe(v, def) {
  const n = parseInt(v, 10);
  return Number.isFinite(n) ? n : def;
}
function parseFloatSafe(v, def) {
  const n = parseFloat(v);
  return Number.isFinite(n) ? n : def;
}
function clamp01(n) {
  return Math.max(0, Math.min(1, n));
}
function capitalize(s) {
  return String(s || '').charAt(0).toUpperCase() + String(s || '').slice(1);
}
function elide(s, max) {
  const str = String(s || '');
  if (str.length <= max) return str;
  return str.slice(0, Math.max(0, max - 3)) + '...';
}
function chunk(arr, size) {
  const res = [];
  for (let i = 0; i < arr.length; i += size) res.push(arr.slice(i, i + size));
  return res;
}
function sleep(ms) {
  return new Promise((r) => setTimeout(r, ms));
}
function computeBackoff(baseMs, factor, attempt, maxMs, jitter) {
  let ms = Math.min(maxMs, baseMs * Math.pow(factor, Math.max(0, attempt)));
  if (jitter) {
    ms += Math.floor(Math.random() * 250);
  }
  return ms;
}
function withTimeout(fn, timeoutMs, message) {
  return async function wrapped() {
    let timeout;
    try {
      return await Promise.race([
        fn(),
        new Promise((_, rej) => {
          timeout = setTimeout(() => rej(new Error(message || `Timeout after ${timeoutMs}ms`)), timeoutMs);
        })
      ]);
    } finally {
      if (timeout) clearTimeout(timeout);
    }
  };
}
function median(arr) {
  if (!arr || arr.length === 0) return 0;
  const a = [...arr].sort((x, y) => x - y);
  const mid = Math.floor(a.length / 2);
  if (a.length % 2 === 0) return (a[mid - 1] + a[mid]) / 2;
  return a[mid];
}
function ensureFileExists(file, content) {
  try {
    if (!fs.existsSync(file)) {
      writeFileAtomic(file, content || '');
    }
  } catch {
    // ignore
  }
}
function writeFileAtomic(target, content) {
  const dir = path.dirname(target);
  const tmp = path.join(dir, `.${path.basename(target)}.tmp_${Date.now()}_${Math.random().toString(36).slice(2)}`);
  fs.writeFileSync(tmp, content);
  fs.renameSync(tmp, target);
}
function rotateFile(filePath, keep = 3) {
  if (!fs.existsSync(filePath)) return;
  // Shift existing rotations
  for (let i = keep; i >= 1; i--) {
    const from = `${filePath}.${i}`;
    const to = `${filePath}.${i + 1}`;
    if (fs.existsSync(from)) {
      try { fs.renameSync(from, to); } catch { /* ignore */ }
    }
  }
  // Move current to .1
  try { fs.renameSync(filePath, `${filePath}.1`); } catch { /* ignore */ }
}
function rotateLogIfNeeded(filePath, maxBytes, keep) {
  try {
    if (!fs.existsSync(filePath)) return;
    const st = fs.statSync(filePath);
    if (st.size >= maxBytes) {
      rotateFile(filePath, keep);
      // ensure new log file exists
      ensureFileExists(filePath, '');
    }
  } catch {
    // ignore
  }
}
function redact(obj, enabled) {
  if (!enabled) return obj;
  const sensitiveKeys = [
    'OPENAI_API_KEY', 'ANTHROPIC_API_KEY', 'GEMINI_API_KEY', 'XAI_API_KEY', 'OPENROUTER_API_KEY',
    'API_KEY', 'TOKEN', 'SECRET', 'PASSWORD'
  ];
  const re = new RegExp(sensitiveKeys.join('|'), 'i');

  const replacer = (val) => {
    if (typeof val === 'string') {
      if (re.test(val) || val.length > 0 && /api[_-]?key|token|secret|password/i.test(val)) return '***REDACTED***';
      return val;
    }
    return val;
  };

  const walk = (input) => {
    if (Array.isArray(input)) return input.map((v) => walk(v));
    if (input && typeof input === 'object') {
      const out = {};
      for (const k of Object.keys(input)) {
        out[k] = walk(input[k]);
      }
      return out;
    }
    return replacer(input);
  };

  return walk(obj);
}
function safeFile(name) {
  return String(name || '').replace(/[^a-zA-Z0-9._-]/g, '_');
}
function safeConsoleError(...args) {
  try {
    console.error(...args);
  } catch {
    // ignore
  }
}
function deriveTags(text) {
  const t = String(text || '').toLowerCase();
  const tags = new Set();
  if (/\b(implement|code|develop|build)\b/.test(t)) tags.add('implementation');
  if (/\b(architect|design|plan)\b/.test(t)) tags.add('architecture');
  if (/\b(analysis|analyze|investigate|review)\b/.test(t)) tags.add('analysis');
  if (/\b(creative|brainstorm|idea|ideation)\b/.test(t)) tags.add('creative');
  if (/\b(fast|quick|rapid)\b/.test(t)) tags.add('fast');
  if (/\b(reason|logic|explain|derive)\b/.test(t)) tags.add('reasoning');
  if (/\b(optimize|performance|speed)\b/.test(t)) tags.add('performance');
  if (/\b(context|memory|integrate|integration)\b/.test(t)) tags.add('context');
  if (tags.size === 0) tags.add('analysis');
  return Array.from(tags);
}

// ----------------- main (MCP stdio style) -----------------

if (require.main === module) {
  const orchestrator = new AIOrchestrator();

  // Buffer stdin data (one JSON object per line or whole payload)
  let buffer = '';
  process.stdin.on('data', async (data) => {
    buffer += data.toString();
    // Try parse per line first
    const parts = buffer.split(/\r?\n/);
    buffer = parts.pop() || '';
    for (const part of parts) {
      await handleRequest(orchestrator, part);
    }
  });

  process.stdin.on('end', async () => {
    if (buffer.trim().length > 0) {
      await handleRequest(orchestrator, buffer);
      buffer = '';
    }
  });
}

async function handleRequest(orchestrator, raw) {
  try {
    const request = JSON.parse(raw);
    const task = request.task || request.description || '';
    const priority = request.priority || 'normal';
    const result = await orchestrator.orchestrateTask(task, priority, request.options || {});
    process.stdout.write(JSON.stringify(result) + os.EOL);
  } catch (error) {
    process.stderr.write(JSON.stringify({ error: error.message }) + os.EOL);
  }
}

module.exports = AIOrchestrator;
