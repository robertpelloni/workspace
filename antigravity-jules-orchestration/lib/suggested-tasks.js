/**
 * Suggested Tasks Module
 * Proactively scans codebases for #TODO, FIXME, HACK comments
 *
 * Features:
 * - Scan directories for actionable comments
 * - Filter by file patterns, priority markers, age
 * - Prioritize by urgency markers and context
 * - Cache results for performance
 *
 * @module lib/suggested-tasks
 */

import fs from 'fs';
import path from 'path';
import { execFileSync } from 'child_process';

// Comment patterns to detect
const COMMENT_PATTERNS = [
  { pattern: /(?:\/\/|#|\/\*|\*)\s*TODO\s*[:\-]?\s*(.+?)(?:\*\/)?$/gim, type: 'todo', priority: 3 },
  { pattern: /(?:\/\/|#|\/\*|\*)\s*FIXME\s*[:\-]?\s*(.+?)(?:\*\/)?$/gim, type: 'fixme', priority: 5 },
  { pattern: /(?:\/\/|#|\/\*|\*)\s*HACK\s*[:\-]?\s*(.+?)(?:\*\/)?$/gim, type: 'hack', priority: 4 },
  { pattern: /(?:\/\/|#|\/\*|\*)\s*BUG\s*[:\-]?\s*(.+?)(?:\*\/)?$/gim, type: 'bug', priority: 5 },
  { pattern: /(?:\/\/|#|\/\*|\*)\s*XXX\s*[:\-]?\s*(.+?)(?:\*\/)?$/gim, type: 'xxx', priority: 4 },
  { pattern: /(?:\/\/|#|\/\*|\*)\s*OPTIMIZE\s*[:\-]?\s*(.+?)(?:\*\/)?$/gim, type: 'optimize', priority: 2 },
  { pattern: /(?:\/\/|#|\/\*|\*)\s*REFACTOR\s*[:\-]?\s*(.+?)(?:\*\/)?$/gim, type: 'refactor', priority: 2 },
  { pattern: /(?:\/\/|#|\/\*|\*)\s*DEPRECATED\s*[:\-]?\s*(.+?)(?:\*\/)?$/gim, type: 'deprecated', priority: 3 }
];

// Priority modifiers in comment text
const PRIORITY_MODIFIERS = [
  { pattern: /\bURGENT\b/i, modifier: 2 },
  { pattern: /\bCRITICAL\b/i, modifier: 3 },
  { pattern: /\bIMPORTANT\b/i, modifier: 1 },
  { pattern: /\bASAP\b/i, modifier: 2 },
  { pattern: /\bP0\b/i, modifier: 3 },
  { pattern: /\bP1\b/i, modifier: 2 },
  { pattern: /\bP2\b/i, modifier: 1 },
  { pattern: /\bBLOCKER\b/i, modifier: 3 }
];

// Default file extensions to scan
const DEFAULT_EXTENSIONS = [
  '.js', '.jsx', '.ts', '.tsx', '.mjs', '.cjs',
  '.py', '.rb', '.go', '.rs', '.java', '.kt',
  '.c', '.cpp', '.h', '.hpp', '.cs',
  '.php', '.swift', '.scala', '.clj',
  '.vue', '.svelte', '.astro',
  '.sh', '.bash', '.zsh',
  '.yaml', '.yml', '.json', '.toml',
  '.md', '.mdx', '.txt'
];

// Directories to skip
const SKIP_DIRS = [
  'node_modules', '.git', '.svn', '.hg',
  'vendor', 'dist', 'build', 'out', 'target',
  '.next', '.nuxt', '.output', '.cache',
  'coverage', '__pycache__', '.pytest_cache',
  '.venv', 'venv', 'env', '.env',
  'bower_components', 'jspm_packages'
];

// Results cache
const scanCache = new Map();
const CACHE_TTL = 5 * 60 * 1000; // 5 minutes

/**
 * Check if file should be scanned
 * @param {string} filePath - File path
 * @param {object} options - Scan options
 */
function shouldScanFile(filePath, options = {}) {
  const ext = path.extname(filePath).toLowerCase();
  const extensions = options.extensions || DEFAULT_EXTENSIONS;

  if (!extensions.includes(ext)) {
    return false;
  }

  // Check if path contains skip directories
  const parts = filePath.split(path.sep);
  for (const part of parts) {
    if (SKIP_DIRS.includes(part)) {
      return false;
    }
  }

  // Check include/exclude patterns
  if (options.include && !options.include.some(p => filePath.includes(p))) {
    return false;
  }
  if (options.exclude && options.exclude.some(p => filePath.includes(p))) {
    return false;
  }

  return true;
}

/**
 * Get file modification date
 * @param {string} filePath - File path
 */
function getFileModDate(filePath) {
  try {
    const stats = fs.statSync(filePath);
    return stats.mtime;
  } catch {
    return null;
  }
}

/**
 * Get git blame info for a line (if available)
 * Uses execFileSync for safety (no shell injection possible)
 * @param {string} filePath - File path
 * @param {number} lineNumber - Line number
 */
function getGitBlame(filePath, lineNumber) {
  try {
    // Use execFileSync to avoid shell injection - arguments are passed as array
    const result = execFileSync('git', [
      'blame',
      '-L', `${lineNumber},${lineNumber}`,
      '--porcelain',
      filePath
    ], {
      encoding: 'utf-8',
      timeout: 5000,
      stdio: ['pipe', 'pipe', 'pipe']
    });

    const lines = result.split('\n');
    const authorLine = lines.find(l => l.startsWith('author '));
    const timeLine = lines.find(l => l.startsWith('author-time '));

    return {
      author: authorLine ? authorLine.replace('author ', '') : 'Unknown',
      timestamp: timeLine ? new Date(parseInt(timeLine.replace('author-time ', '')) * 1000) : null
    };
  } catch {
    return null;
  }
}

/**
 * Calculate task priority
 * @param {string} type - Comment type
 * @param {string} text - Comment text
 * @param {object} context - Additional context
 */
function calculatePriority(type, text, context = {}) {
  // Base priority from type
  const typePattern = COMMENT_PATTERNS.find(p => p.type === type);
  let priority = typePattern ? typePattern.priority : 3;

  // Apply modifiers from text
  for (const mod of PRIORITY_MODIFIERS) {
    if (mod.pattern.test(text)) {
      priority += mod.modifier;
    }
  }

  // Age modifier - older tasks get slight priority boost
  if (context.age) {
    const daysOld = Math.floor(context.age / (24 * 60 * 60 * 1000));
    if (daysOld > 180) priority += 2;
    else if (daysOld > 90) priority += 1;
  }

  return Math.min(10, Math.max(1, priority));
}

/**
 * Parse a file for actionable comments
 * @param {string} filePath - File path
 * @param {object} options - Parse options
 */
function parseFile(filePath, options = {}) {
  const results = [];

  try {
    const content = fs.readFileSync(filePath, 'utf-8');
    const lines = content.split('\n');

    for (let i = 0; i < lines.length; i++) {
      const line = lines[i];
      const lineNumber = i + 1;

      for (const { pattern, type, priority } of COMMENT_PATTERNS) {
        // Reset regex state
        pattern.lastIndex = 0;
        const match = pattern.exec(line);

        if (match) {
          const text = match[1].trim();

          // Skip empty or very short comments
          if (text.length < 3) continue;

          // Get surrounding context
          const contextLines = [];
          for (let j = Math.max(0, i - 2); j <= Math.min(lines.length - 1, i + 2); j++) {
            contextLines.push(lines[j]);
          }

          // Get git info if requested
          let gitInfo = null;
          if (options.includeGitInfo) {
            gitInfo = getGitBlame(filePath, lineNumber);
          }

          const fileModDate = getFileModDate(filePath);
          const age = fileModDate ? Date.now() - fileModDate.getTime() : null;

          results.push({
            type,
            text,
            file: filePath,
            line: lineNumber,
            priority: calculatePriority(type, text, { age }),
            context: contextLines.join('\n'),
            gitInfo,
            fileModified: fileModDate,
            age
          });
        }
      }
    }
  } catch (error) {
    // Skip files that can't be read
    if (options.verbose) {
      console.warn(`[Suggested Tasks] Could not read ${filePath}: ${error.message}`);
    }
  }

  return results;
}

/**
 * Recursively scan a directory for files
 * @param {string} dir - Directory path
 * @param {object} options - Scan options
 */
function* walkDir(dir, options = {}) {
  try {
    const entries = fs.readdirSync(dir, { withFileTypes: true });

    for (const entry of entries) {
      const fullPath = path.join(dir, entry.name);

      if (entry.isDirectory()) {
        if (!SKIP_DIRS.includes(entry.name)) {
          yield* walkDir(fullPath, options);
        }
      } else if (entry.isFile()) {
        if (shouldScanFile(fullPath, options)) {
          yield fullPath;
        }
      }
    }
  } catch (error) {
    if (options.verbose) {
      console.warn(`[Suggested Tasks] Could not read directory ${dir}: ${error.message}`);
    }
  }
}

/**
 * Scan a directory for suggested tasks
 * @param {string} directory - Directory to scan
 * @param {object} options - Scan options
 */
export function scanDirectory(directory, options = {}) {
  const resolvedDir = path.resolve(directory);

  // Check cache
  const cacheKey = `${resolvedDir}:${JSON.stringify(options)}`;
  const cached = scanCache.get(cacheKey);
  if (cached && Date.now() - cached.timestamp < CACHE_TTL) {
    return cached.data;
  }

  const allTasks = [];
  let filesScanned = 0;
  const maxFiles = options.maxFiles || 1000;

  for (const filePath of walkDir(resolvedDir, options)) {
    if (filesScanned >= maxFiles) break;

    const tasks = parseFile(filePath, options);
    allTasks.push(...tasks);
    filesScanned++;
  }

  // Sort by priority (descending), then by age (older first)
  allTasks.sort((a, b) => {
    if (b.priority !== a.priority) {
      return b.priority - a.priority;
    }
    return (b.age || 0) - (a.age || 0);
  });

  const result = {
    tasks: allTasks,
    summary: {
      total: allTasks.length,
      byType: {},
      byPriority: { high: 0, medium: 0, low: 0 },
      filesScanned
    }
  };

  // Calculate summary
  for (const task of allTasks) {
    result.summary.byType[task.type] = (result.summary.byType[task.type] || 0) + 1;

    if (task.priority >= 7) result.summary.byPriority.high++;
    else if (task.priority >= 4) result.summary.byPriority.medium++;
    else result.summary.byPriority.low++;
  }

  // Cache result
  scanCache.set(cacheKey, { data: result, timestamp: Date.now() });

  return result;
}

/**
 * Get suggested tasks filtered and formatted for Jules
 * @param {string} directory - Directory to scan
 * @param {object} options - Filter options
 */
export function getSuggestedTasks(directory, options = {}) {
  const result = scanDirectory(directory, options);

  let tasks = result.tasks;

  // Apply filters
  if (options.types && options.types.length > 0) {
    tasks = tasks.filter(t => options.types.includes(t.type));
  }

  if (options.minPriority) {
    tasks = tasks.filter(t => t.priority >= options.minPriority);
  }

  if (options.maxAge) {
    const cutoff = Date.now() - options.maxAge;
    tasks = tasks.filter(t => !t.fileModified || t.fileModified.getTime() >= cutoff);
  }

  // Limit results
  const limit = options.limit || 20;
  tasks = tasks.slice(0, limit);

  // Format for Jules consumption
  return {
    tasks: tasks.map(t => ({
      type: t.type.toUpperCase(),
      text: t.text,
      location: `${path.relative(directory, t.file)}:${t.line}`,
      priority: t.priority,
      priorityLabel: t.priority >= 7 ? 'HIGH' : t.priority >= 4 ? 'MEDIUM' : 'LOW',
      author: t.gitInfo?.author || null,
      age: t.age ? formatAge(t.age) : null
    })),
    summary: result.summary,
    scannedDirectory: directory
  };
}

/**
 * Format age in human readable form
 * @param {number} ms - Age in milliseconds
 */
function formatAge(ms) {
  const days = Math.floor(ms / (24 * 60 * 60 * 1000));
  if (days > 365) return `${Math.floor(days / 365)} years`;
  if (days > 30) return `${Math.floor(days / 30)} months`;
  if (days > 0) return `${days} days`;
  return 'today';
}

/**
 * Clear the scan cache
 */
export function clearCache() {
  scanCache.clear();
  return { success: true, message: 'Suggested tasks cache cleared' };
}

/**
 * Get cache stats
 */
export function getCacheStats() {
  return {
    entries: scanCache.size,
    maxAge: CACHE_TTL
  };
}

/**
 * Generate a prompt for Jules to fix a task
 * @param {object} task - Task to fix
 * @param {string} directory - Base directory
 */
export function generateFixPrompt(task, directory) {
  const fullPath = path.join(directory, task.location.split(':')[0]);
  const lineNumber = parseInt(task.location.split(':')[1]);

  return `Fix the ${task.type} comment in ${task.location}:

**Issue:** ${task.text}

**Location:** ${fullPath} at line ${lineNumber}

**Priority:** ${task.priorityLabel} (${task.priority}/10)

Please:
1. Read the file and understand the context
2. Implement the fix or improvement suggested by the comment
3. Remove the ${task.type} comment once the issue is resolved
4. Add any necessary tests if applicable`;
}

export default {
  scanDirectory,
  getSuggestedTasks,
  clearCache,
  getCacheStats,
  generateFixPrompt
};
