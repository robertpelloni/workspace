
/**
 * Yoke AntiGravity - AI Code Reviewer
 * Automated security and quality review for AI-generated code
 * @module core/code-reviewer
 */

import * as vscode from 'vscode';
import { createLogger } from '../utils/logger';

const log = createLogger('CodeReviewer');

// ============ Types ============
export interface ReviewIssue {
    type: 'security' | 'quality' | 'performance' | 'style' | 'bug';
    severity: 'critical' | 'high' | 'medium' | 'low' | 'info';
    line?: number;
    message: string;
    suggestion?: string;
    rule: string;
}

export interface ReviewResult {
    passed: boolean;
    issues: ReviewIssue[];
    score: number; // 0-100
    summary: string;
    reviewedAt: number;
}

// ============ Security Patterns ============
const SECURITY_PATTERNS: Array<{
    pattern: RegExp;
    type: ReviewIssue['type'];
    severity: ReviewIssue['severity'];
    message: string;
    rule: string;
}> = [
        // SQL Injection
        {
            pattern: /(['"`])\s*\+\s*\w+\s*\+\s*\1.*(?:SELECT|INSERT|UPDATE|DELETE|FROM|WHERE)/i,
            type: 'security',
            severity: 'critical',
            message: 'Potential SQL injection vulnerability - use parameterized queries',
            rule: 'sql-injection'
        },
        // Command Injection
        {
            pattern: /exec\s*\(\s*[`'"].*\$\{/,
            type: 'security',
            severity: 'critical',
            message: 'Potential command injection - avoid string interpolation in shell commands',
            rule: 'command-injection'
        },
        // Hardcoded Secrets
        {
            pattern: /(?:password|secret|api[_-]?key|token|auth)\s*[=:]\s*['"`][^'"` ]{8,}/i,
            type: 'security',
            severity: 'high',
            message: 'Possible hardcoded secret detected - use environment variables',
            rule: 'hardcoded-secret'
        },
        // Eval Usage
        {
            pattern: /\beval\s*\(/,
            type: 'security',
            severity: 'high',
            message: 'Avoid using eval() - it can execute arbitrary code',
            rule: 'no-eval'
        },
        // innerHTML XSS
        {
            pattern: /\.innerHTML\s*=(?!.*sanitize)/i,
            type: 'security',
            severity: 'high',
            message: 'innerHTML assignment may lead to XSS - sanitize input or use textContent',
            rule: 'xss-innerhtml'
        },
        // Insecure HTTP
        {
            pattern: /http:\/\/(?!localhost|127\.0\.0\.1)/,
            type: 'security',
            severity: 'medium',
            message: 'Insecure HTTP URL detected - use HTTPS',
            rule: 'insecure-http'
        },
        // Weak Crypto
        {
            pattern: /(?:md5|sha1)\s*\(/i,
            type: 'security',
            severity: 'medium',
            message: 'Weak hash algorithm detected - use SHA-256 or better',
            rule: 'weak-crypto'
        }
    ];

// ============ Quality Patterns ============
const QUALITY_PATTERNS: Array<{
    pattern: RegExp;
    type: ReviewIssue['type'];
    severity: ReviewIssue['severity'];
    message: string;
    suggestion?: string;
    rule: string;
}> = [
        // Console.log in production
        {
            pattern: /console\.(log|debug|info)\(/,
            type: 'quality',
            severity: 'low',
            message: 'Console statement found - remove before production',
            rule: 'no-console'
        },
        // TODO/FIXME comments
        {
            pattern: /\/\/\s*(TODO|FIXME|HACK|XXX):/i,
            type: 'quality',
            severity: 'info',
            message: 'Unresolved TODO/FIXME comment',
            rule: 'no-todo'
        },
        // Magic numbers
        {
            pattern: /(?<!\w)(?!0|1|2|-1)\d{2,}(?!\w)/,
            type: 'quality',
            severity: 'low',
            message: 'Magic number detected - consider using a named constant',
            rule: 'no-magic-numbers'
        },
        // Empty catch blocks
        {
            pattern: /catch\s*\([^)]*\)\s*\{\s*\}/,
            type: 'quality',
            severity: 'medium',
            message: 'Empty catch block - errors should be handled or logged',
            rule: 'no-empty-catch'
        },
        // Very long lines
        {
            pattern: /.{200,}/,
            type: 'style',
            severity: 'low',
            message: 'Line exceeds 200 characters - consider breaking up',
            rule: 'max-line-length'
        },
        // Nested callbacks (callback hell)
        {
            pattern: /\)\s*=>\s*\{[^}]*\)\s*=>\s*\{[^}]*\)\s*=>\s*\{/,
            type: 'quality',
            severity: 'medium',
            message: 'Deeply nested callbacks - consider async/await or Promise chains',
            rule: 'no-callback-hell'
        },
        // == instead of ===
        {
            pattern: /[^=!]==[^=]/,
            type: 'quality',
            severity: 'low',
            message: 'Use strict equality (===) instead of loose equality (==)',
            rule: 'eqeqeq'
        }
    ];

// ============ Performance Patterns ============
const PERFORMANCE_PATTERNS: Array<{
    pattern: RegExp;
    type: ReviewIssue['type'];
    severity: ReviewIssue['severity'];
    message: string;
    rule: string;
}> = [
        // Sync file operations in async context
        {
            pattern: /(?:readFileSync|writeFileSync|existsSync|mkdirSync)\s*\(/,
            type: 'performance',
            severity: 'medium',
            message: 'Synchronous file operation - consider using async version',
            rule: 'no-sync-io'
        },
        // N+1 query pattern
        {
            pattern: /for\s*\([^)]+\)\s*\{[^}]*(?:SELECT|findOne|findById|query)/i,
            type: 'performance',
            severity: 'high',
            message: 'Possible N+1 query pattern - batch database operations',
            rule: 'n-plus-one'
        },
        // Inefficient regex
        {
            pattern: /new\s+RegExp\s*\([^)]+\)/,
            type: 'performance',
            severity: 'low',
            message: 'Consider using regex literal instead of RegExp constructor if pattern is static',
            rule: 'prefer-regex-literal'
        }
    ];

// ============ Bug Patterns ============
const BUG_PATTERNS: Array<{
    pattern: RegExp;
    type: ReviewIssue['type'];
    severity: ReviewIssue['severity'];
    message: string;
    rule: string;
}> = [
        // Assignment in condition
        {
            pattern: /if\s*\([^=]*[^=!<>]=[^=][^)]*\)/,
            type: 'bug',
            severity: 'high',
            message: 'Assignment in conditional - did you mean to use == or ===?',
            rule: 'no-cond-assign'
        },
        // Unreachable code after return
        {
            pattern: /return\s+[^;]+;\s*\n\s*[a-zA-Z]/,
            type: 'bug',
            severity: 'medium',
            message: 'Possible unreachable code after return statement',
            rule: 'no-unreachable'
        },
        // Duplicate keys
        {
            pattern: /(['"`])(\w+)\1\s*:[^,}]+,\s*\1\2\1\s*:/,
            type: 'bug',
            severity: 'high',
            message: 'Duplicate object key detected',
            rule: 'no-dupe-keys'
        }
    ];

// ============ Code Reviewer Class ============
export class CodeReviewer {
    private allPatterns = [
        ...SECURITY_PATTERNS,
        ...QUALITY_PATTERNS,
        ...PERFORMANCE_PATTERNS,
        ...BUG_PATTERNS
    ];

    private enabledRules: Set<string> = new Set();
    private disabledRules: Set<string> = new Set();
    private minSeverityToBlock: ReviewIssue['severity'] = 'high';

    constructor() {
        // Enable all rules by default
        this.enabledRules = new Set(this.allPatterns.map(p => p.rule));
    }

    // ============ Configuration ============
    setMinBlockSeverity(severity: ReviewIssue['severity']): void {
        this.minSeverityToBlock = severity;
    }

    enableRule(rule: string): void {
        this.enabledRules.add(rule);
        this.disabledRules.delete(rule);
    }

    disableRule(rule: string): void {
        this.disabledRules.add(rule);
        this.enabledRules.delete(rule);
    }

    // ============ Main Review Function ============
    review(code: string, filename?: string): ReviewResult {
        const issues: ReviewIssue[] = [];
        const lines = code.split('\n');

        log.info(`Reviewing code: ${lines.length} lines`); // Changed debug to info for visibility

        // Check each pattern against each line
        for (let i = 0; i < lines.length; i++) {
            const line = lines[i];

            for (const pattern of this.allPatterns) {
                if (this.disabledRules.has(pattern.rule)) continue;
                if (!this.enabledRules.has(pattern.rule)) continue;

                if (pattern.pattern.test(line)) {
                    issues.push({
                        type: pattern.type,
                        severity: pattern.severity,
                        line: i + 1,
                        message: pattern.message,
                        rule: pattern.rule
                    });
                }
            }
        }

        // Also check full code for multi-line patterns
        for (const pattern of this.allPatterns) {
            if (this.disabledRules.has(pattern.rule)) continue;

            // Skip if already found by line-by-line check
            if (issues.some(i => i.rule === pattern.rule)) continue;

            if (pattern.pattern.test(code)) {
                issues.push({
                    type: pattern.type,
                    severity: pattern.severity,
                    message: pattern.message,
                    rule: pattern.rule
                });
            }
        }

        // Calculate score
        const score = this.calculateScore(issues);

        // Determine if review passes
        const sevOrder: ReviewIssue['severity'][] = ['critical', 'high', 'medium', 'low', 'info'];
        const blockThreshold = sevOrder.indexOf(this.minSeverityToBlock);
        const hasBlockingIssue = issues.some(i => sevOrder.indexOf(i.severity) <= blockThreshold);

        const passed = !hasBlockingIssue;

        // Generate summary
        const summary = this.generateSummary(issues, score, passed);

        log.info(`Review complete: ${passed ? 'PASSED' : 'FAILED'} (score: ${score})`);

        return {
            passed,
            issues,
            score,
            summary,
            reviewedAt: Date.now()
        };
    }

    // ============ Review Specific File Diff ============
    reviewDiff(oldCode: string, newCode: string): ReviewResult {
        // Only review the new code (what was added/changed)
        return this.review(newCode);
    }

    // ============ Quick Security Scan ============
    quickSecurityScan(code: string): { safe: boolean; criticalIssues: ReviewIssue[] } {
        const issues: ReviewIssue[] = [];

        for (const pattern of SECURITY_PATTERNS) {
            if (pattern.pattern.test(code)) {
                if (pattern.severity === 'critical' || pattern.severity === 'high') {
                    issues.push({
                        type: pattern.type,
                        severity: pattern.severity,
                        message: pattern.message,
                        rule: pattern.rule
                    });
                }
            }
        }

        return {
            safe: issues.length === 0,
            criticalIssues: issues
        };
    }

    // ============ Scoring ============
    private calculateScore(issues: ReviewIssue[]): number {
        let score = 100;

        const deductions: Record<ReviewIssue['severity'], number> = {
            critical: 30,
            high: 15,
            medium: 8,
            low: 3,
            info: 1
        };

        for (const issue of issues) {
            score -= deductions[issue.severity];
        }

        return Math.max(0, score);
    }

    // ============ Summary Generation ============
    private generateSummary(issues: ReviewIssue[], score: number, passed: boolean): string {
        if (issues.length === 0) {
            return '✅ No issues found. Code looks clean!';
        }

        const byType: Record<string, number> = {};
        const bySeverity: Record<string, number> = {};

        for (const issue of issues) {
            byType[issue.type] = (byType[issue.type] || 0) + 1;
            bySeverity[issue.severity] = (bySeverity[issue.severity] || 0) + 1;
        }

        const typeSummary = Object.entries(byType)
            .map(([t, c]) => `${c} ${t}`)
            .join(', ');

        const emoji = passed ? '✅' : '❌';
        const status = passed ? 'Passed' : 'Needs attention';

        return `${emoji} ${status} (Score: ${score}/100)\nIssues: ${typeSummary}`;
    }

    // ============ VS Code Integration ============
    showDiagnostics(document: vscode.TextDocument, issues: ReviewIssue[]): vscode.Diagnostic[] {
        const diagnostics: vscode.Diagnostic[] = [];

        const severityMap: Record<ReviewIssue['severity'], vscode.DiagnosticSeverity> = {
            critical: vscode.DiagnosticSeverity.Error,
            high: vscode.DiagnosticSeverity.Error,
            medium: vscode.DiagnosticSeverity.Warning,
            low: vscode.DiagnosticSeverity.Information,
            info: vscode.DiagnosticSeverity.Hint
        };

        for (const issue of issues) {
            const line = (issue.line || 1) - 1;
            const range = new vscode.Range(line, 0, line, 1000);

            const diagnostic = new vscode.Diagnostic(
                range,
                `[Yoke] ${issue.message}`,
                severityMap[issue.severity]
            );
            diagnostic.source = 'Yoke CodeReviewer';
            diagnostic.code = issue.rule;

            diagnostics.push(diagnostic);
        }

        return diagnostics;
    }

    // ============ Banned Commands Check ============
    checkBannedCommands(command: string, bannedList: string[]): { blocked: boolean; reason?: string } {
        const normalizedCommand = command.toLowerCase().trim();

        for (const banned of bannedList) {
            if (normalizedCommand.includes(banned.toLowerCase())) {
                return {
                    blocked: true,
                    reason: `Command contains banned pattern: ${banned}`
                };
            }
        }

        // Additional safety checks
        const dangerousPatterns = [
            /rm\s+-rf?\s+[\/~]/,
            /format\s+[a-z]:/i,
            /del\s+\/[sfq]/i,
            />\s*\/dev\/sd[a-z]/,
            /dd\s+if=.*of=\/dev/
        ];

        for (const pattern of dangerousPatterns) {
            if (pattern.test(normalizedCommand)) {
                return {
                    blocked: true,
                    reason: 'Potentially destructive command detected'
                };
            }
        }

        return { blocked: false };
    }
}

// Singleton export
export const codeReviewer = new CodeReviewer();
