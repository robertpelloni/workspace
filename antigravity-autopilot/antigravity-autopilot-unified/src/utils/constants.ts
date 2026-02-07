/**
 * Antigravity Autopilot - Constants and Type Definitions
 * @module constants
 */

// ============ Extension Metadata ============
export const EXTENSION_NAME = 'antigravity-autopilot-unified';
export const EXTENSION_DISPLAY_NAME = 'Antigravity Autopilot';
export const VERSION = '4.0.0';

// ============ CDP Ports ============
export const CDP_PORT_MIN = 9000;
export const CDP_PORT_MAX = 9030;
export const CDP_POLL_INTERVAL = 5000;

// ============ Loop Configuration ============
export const DEFAULT_LOOP_INTERVAL_SECONDS = 30;
export const DEFAULT_MAX_LOOPS = 100;
export const DEFAULT_POLL_FREQUENCY_MS = 1000;

// ============ Model Identifiers ============
// Exact models from Antigravity's model selector (as of Dec 2024)
export const ModelId = {
    // Gemini Models
    GEMINI_PRO_HIGH: 'gemini-3-pro-high',
    GEMINI_PRO_LOW: 'gemini-3-pro-low',
    GEMINI_FLASH: 'gemini-3-flash',
    // Claude Models
    CLAUDE_SONNET: 'claude-sonnet-4-5',
    CLAUDE_SONNET_THINKING: 'claude-sonnet-4-5-thinking',
    CLAUDE_OPUS_THINKING: 'claude-opus-4-5-thinking',
    // GPT Models
    GPT_OSS: 'gpt-oss-120b-medium',
} as const;

// Model display names matching Antigravity's UI exactly
export const MODEL_LABELS: Record<string, string> = {
    [ModelId.GEMINI_PRO_HIGH]: 'Gemini 3 Pro (High)',
    [ModelId.GEMINI_PRO_LOW]: 'Gemini 3 Pro (Low)',
    [ModelId.GEMINI_FLASH]: 'Gemini 3 Flash',
    [ModelId.CLAUDE_SONNET]: 'Claude Sonnet 4.5',
    [ModelId.CLAUDE_SONNET_THINKING]: 'Claude Sonnet 4.5 (Thinking)',
    [ModelId.CLAUDE_OPUS_THINKING]: 'Claude Opus 4.5 (Thinking)',
    [ModelId.GPT_OSS]: 'GPT-OSS 120B (Medium)',
};

export type ModelIdType = typeof ModelId[keyof typeof ModelId];

// ============ Task Types ============
export const TaskType = {
    REASONING: 'reasoning',
    FRONTEND: 'frontend',
    QUICK: 'quick',
    GENERAL: 'general',
} as const;

export type TaskTypeValue = typeof TaskType[keyof typeof TaskType];

// ============ Exit Patterns ============
export const EXIT_PATTERNS = [
    /all\s+tasks?\s+(are\s+)?completed?/i,
    /implementation\s+is\s+complete/i,
    /everything\s+is\s+working/i,
    /no\s+more\s+(tasks?|work)\s+to\s+do/i,
    /successfully\s+completed\s+all/i,
    /\[x\]\s+all\s+items\s+done/i,
    /nothing\s+(left|remaining)\s+to/i,
    /project\s+is\s+ready/i,
] as const;

// ============ Task Keywords ============
export const TASK_KEYWORDS = {
    reasoning: [
        'debug', 'fix', 'error', 'bug', 'issue', 'problem', 'investigate',
        'analyze', 'optimize', 'refactor', 'architecture', 'design', 'complex',
        'algorithm', 'performance', 'memory', 'race condition', 'deadlock',
    ],
    frontend: [
        'ui', 'ux', 'css', 'style', 'layout', 'component', 'react', 'vue',
        'angular', 'html', 'responsive', 'animation', 'theme', 'design',
        'button', 'form', 'modal', 'dashboard', 'page', 'screen',
    ],
    quick: [
        'rename', 'typo', 'comment', 'format', 'lint', 'import', 'export',
        'simple', 'quick', 'minor', 'small', 'cleanup', 'remove', 'delete',
    ],
} as const;
