
/**
 * Yoke AntiGravity - Test Generator
 * Autonomous test generation and execution pipeline
 * @module core/test-generator
 */

import * as vscode from 'vscode';
import * as fs from 'fs';
import * as path from 'path';
import { createLogger } from '../utils/logger';

const log = createLogger('TestGenerator');

// ============ Types ============
export interface TestCase {
    id: string;
    name: string;
    description: string;
    type: 'unit' | 'integration' | 'e2e';
    sourceFile: string;
    testFile: string;
    code: string;
    status: 'generated' | 'pending' | 'passed' | 'failed' | 'skipped';
    result?: TestResult;
}

export interface TestResult {
    passed: boolean;
    duration: number;
    error?: string;
    coverage?: number;
}

export interface TestSuite {
    id: string;
    name: string;
    tests: TestCase[];
    framework: 'vitest' | 'jest' | 'mocha' | 'playwright';
    createdAt: number;
    lastRunAt?: number;
    coverage?: CoverageReport;
}

export interface CoverageReport {
    lines: number;
    branches: number;
    functions: number;
    statements: number;
}

export interface TestGeneratorConfig {
    framework: 'vitest' | 'jest' | 'mocha';
    testDirectory: string;
    coverageThreshold: number;
    generateMocks: boolean;
    includeEdgeCases: boolean;
}

// ============ Test Templates ============
const TEST_TEMPLATES = {
    vitest: {
        import: `import { describe, it, expect, vi, beforeEach, afterEach } from 'vitest';`,
        describe: (name: string, tests: string) => `describe('${name}', () => {\n${tests}\n});`,
        it: (name: string, code: string) => `  it('${name}', () => {\n${code}\n  });`,
        itAsync: (name: string, code: string) => `  it('${name}', async () => {\n${code}\n  });`,
        mock: (name: string) => `vi.mock('${name}');`,
        beforeEach: (code: string) => `  beforeEach(() => {\n${code}\n  });`,
        afterEach: (code: string) => `  afterEach(() => {\n${code}\n  });`
    },
    jest: {
        import: ``,
        describe: (name: string, tests: string) => `describe('${name}', () => {\n${tests}\n});`,
        it: (name: string, code: string) => `  it('${name}', () => {\n${code}\n  });`,
        itAsync: (name: string, code: string) => `  it('${name}', async () => {\n${code}\n  });`,
        mock: (name: string) => `jest.mock('${name}');`,
        beforeEach: (code: string) => `  beforeEach(() => {\n${code}\n  });`,
        afterEach: (code: string) => `  afterEach(() => {\n${code}\n  });`
    },
    mocha: {
        import: `import { expect } from 'chai';`,
        describe: (name: string, tests: string) => `describe('${name}', () => {\n${tests}\n});`,
        it: (name: string, code: string) => `  it('${name}', () => {\n${code}\n  });`,
        itAsync: (name: string, code: string) => `  it('${name}', async () => {\n${code}\n  });`,
        mock: (name: string) => `// Mock ${name}`,
        beforeEach: (code: string) => `  beforeEach(() => {\n${code}\n  });`,
        afterEach: (code: string) => `  afterEach(() => {\n${code}\n  });`
    }
};

// ============ Test Generator Class ============
export class TestGenerator {
    private config: TestGeneratorConfig = {
        framework: 'vitest',
        testDirectory: 'tests',
        coverageThreshold: 80,
        generateMocks: true,
        includeEdgeCases: true
    };
    private workspaceRoot: string | null = null;
    private suites: Map<string, TestSuite> = new Map();

    constructor() {
        this.initializeWorkspace();
    }

    private initializeWorkspace(): void {
        const folders = vscode.workspace.workspaceFolders;
        if (folders?.[0]) {
            this.workspaceRoot = folders[0].uri.fsPath;
            this.detectTestFramework();
        }
    }

    private detectTestFramework(): void {
        if (!this.workspaceRoot) return;

        const packageJsonPath = path.join(this.workspaceRoot, 'package.json');
        if (fs.existsSync(packageJsonPath)) {
            try {
                const pkg = JSON.parse(fs.readFileSync(packageJsonPath, 'utf-8'));
                const deps = { ...pkg.dependencies, ...pkg.devDependencies };

                if (deps['vitest']) this.config.framework = 'vitest';
                else if (deps['jest']) this.config.framework = 'jest';
                else if (deps['mocha']) this.config.framework = 'mocha';

                log.info(`Detected test framework: ${this.config.framework}`);
            } catch (error) {
                log.warn('Could not parse package.json');
            }
        }
    }

    // ============ Test Generation ============
    async generateTestsForFile(filePath: string): Promise<TestSuite> {
        const absolutePath = this.resolvePath(filePath);
        const content = fs.readFileSync(absolutePath, 'utf-8');

        const suiteId = this.generateId();
        const suiteName = path.basename(filePath, path.extname(filePath));

        log.info(`Generating tests for: ${filePath}`);

        // Extract functions and classes from file
        const functions = this.extractFunctions(content);
        const classes = this.extractClasses(content);

        const tests: TestCase[] = [];

        // Generate tests for each function
        for (const func of functions) {
            const testCases = this.generateFunctionTests(func, filePath);
            tests.push(...testCases);
        }

        // Generate tests for each class
        for (const cls of classes) {
            const testCases = this.generateClassTests(cls, filePath);
            tests.push(...testCases);
        }

        const suite: TestSuite = {
            id: suiteId,
            name: suiteName,
            tests,
            framework: this.config.framework,
            createdAt: Date.now()
        };

        this.suites.set(suiteId, suite);

        // Write test file
        await this.writeTestFile(suite, filePath);

        log.info(`Generated ${tests.length} tests for ${suiteName}`);
        return suite;
    }

    private extractFunctions(content: string): Array<{ name: string; params: string[]; async: boolean; body: string }> {
        const functions: Array<{ name: string; params: string[]; async: boolean; body: string }> = [];

        // Match function declarations and arrow functions
        const patterns = [
            /(?:export\s+)?(?:async\s+)?function\s+(\w+)\s*\(([^)]*)\)\s*(?::\s*[^{]+)?\s*\{([^}]*(?:\{[^}]*\}[^}]*)*)\}/g,
            /(?:export\s+)?const\s+(\w+)\s*=\s*(?:async\s+)?\(([^)]*)\)\s*(?::\s*[^=]+)?=>\s*\{([^}]*(?:\{[^}]*\}[^}]*)*)\}/g
        ];

        for (const pattern of patterns) {
            let match;
            while ((match = pattern.exec(content)) !== null) {
                const [full, name, params, body] = match;
                if (name && !name.startsWith('_')) {
                    functions.push({
                        name,
                        params: params.split(',').map(p => p.trim().split(':')[0].trim()).filter(Boolean),
                        async: full.includes('async'),
                        body: body || ''
                    });
                }
            }
        }

        return functions;
    }

    private extractClasses(content: string): Array<{ name: string; methods: string[] }> {
        const classes: Array<{ name: string; methods: string[] }> = [];

        const classPattern = /(?:export\s+)?class\s+(\w+)(?:\s+extends\s+\w+)?\s*\{([^]*?)\n\}/g;
        const methodPattern = /(?:async\s+)?(\w+)\s*\([^)]*\)\s*(?::\s*[^{]+)?\s*\{/g;

        let classMatch;
        while ((classMatch = classPattern.exec(content)) !== null) {
            const [, className, classBody] = classMatch;
            const methods: string[] = [];

            let methodMatch;
            while ((methodMatch = methodPattern.exec(classBody)) !== null) {
                const methodName = methodMatch[1];
                if (methodName !== 'constructor' && !methodName.startsWith('_')) {
                    methods.push(methodName);
                }
            }

            if (className) {
                classes.push({ name: className, methods });
            }
        }

        return classes;
    }

    private generateFunctionTests(
        func: { name: string; params: string[]; async: boolean; body: string },
        sourceFile: string
    ): TestCase[] {
        const tests: TestCase[] = [];
        const template = TEST_TEMPLATES[this.config.framework];

        // Basic functionality test
        tests.push({
            id: this.generateId(),
            name: `${func.name} - should execute without errors`,
            description: `Basic execution test for ${func.name}`,
            type: 'unit',
            sourceFile,
            testFile: this.getTestFilePath(sourceFile),
            code: this.generateBasicTest(func, template),
            status: 'generated'
        });

        // Edge case tests
        if (this.config.includeEdgeCases) {
            // Empty/null input test
            if (func.params.length > 0) {
                tests.push({
                    id: this.generateId(),
                    name: `${func.name} - should handle empty input`,
                    description: `Edge case test with empty/null inputs`,
                    type: 'unit',
                    sourceFile,
                    testFile: this.getTestFilePath(sourceFile),
                    code: this.generateEdgeCaseTest(func, template, 'empty'),
                    status: 'generated'
                });
            }

            // Error handling test
            tests.push({
                id: this.generateId(),
                name: `${func.name} - should handle errors gracefully`,
                description: `Error handling test`,
                type: 'unit',
                sourceFile,
                testFile: this.getTestFilePath(sourceFile),
                code: this.generateEdgeCaseTest(func, template, 'error'),
                status: 'generated'
            });
        }

        return tests;
    }

    private generateClassTests(
        cls: { name: string; methods: string[] },
        sourceFile: string
    ): TestCase[] {
        const tests: TestCase[] = [];
        const template = TEST_TEMPLATES[this.config.framework];

        // Instantiation test
        tests.push({
            id: this.generateId(),
            name: `${cls.name} - should instantiate correctly`,
            description: `Constructor test for ${cls.name}`,
            type: 'unit',
            sourceFile,
            testFile: this.getTestFilePath(sourceFile),
            code: `    const instance = new ${cls.name}();\n    expect(instance).toBeDefined();`,
            status: 'generated'
        });

        // Method tests
        for (const method of cls.methods) {
            tests.push({
                id: this.generateId(),
                name: `${cls.name}.${method} - should work correctly`,
                description: `Method test for ${method}`,
                type: 'unit',
                sourceFile,
                testFile: this.getTestFilePath(sourceFile),
                code: `    const instance = new ${cls.name}();\n    expect(instance.${method}).toBeDefined();`,
                status: 'generated'
            });
        }

        return tests;
    }

    private generateBasicTest(
        func: { name: string; params: string[]; async: boolean },
        template: typeof TEST_TEMPLATES.vitest
    ): string {
        const params = func.params.map(() => 'undefined').join(', ');
        const call = func.async
            ? `await ${func.name}(${params})`
            : `${func.name}(${params})`;

        return `    const result = ${call};\n    expect(result).toBeDefined();`;
    }

    private generateEdgeCaseTest(
        func: { name: string; params: string[] },
        template: typeof TEST_TEMPLATES.vitest,
        type: 'empty' | 'error'
    ): string {
        if (type === 'empty') {
            const nullParams = func.params.map(() => 'null').join(', ');
            return `    expect(() => ${func.name}(${nullParams})).not.toThrow();`;
        } else {
            return `    // Error handling test\n    expect(true).toBe(true); // Placeholder`;
        }
    }

    // ============ Test File Operations ============
    private async writeTestFile(suite: TestSuite, sourceFile: string): Promise<string> {
        const testFilePath = this.getTestFilePath(sourceFile);
        const absoluteTestPath = this.resolvePath(testFilePath);
        const template = TEST_TEMPLATES[this.config.framework];

        const imports = [
            template.import,
            `import { /* imports */ } from '${this.getRelativeImportPath(testFilePath, sourceFile)}';`
        ].filter(Boolean).join('\n');

        const testCode = suite.tests.map(test =>
            test.code.includes('async') || test.code.includes('await')
                ? template.itAsync(test.name, test.code)
                : template.it(test.name, test.code)
        ).join('\n\n');

        const content = `${imports}\n\n${template.describe(suite.name, testCode)}\n`;

        // Ensure directory exists
        const dir = path.dirname(absoluteTestPath);
        if (!fs.existsSync(dir)) {
            fs.mkdirSync(dir, { recursive: true });
        }

        fs.writeFileSync(absoluteTestPath, content);
        log.info(`Wrote test file: ${testFilePath}`);

        return testFilePath;
    }

    private getTestFilePath(sourceFile: string): string {
        const basename = path.basename(sourceFile, path.extname(sourceFile));
        const ext = path.extname(sourceFile);
        return path.join(this.config.testDirectory, `${basename}.test${ext}`);
    }

    private getRelativeImportPath(from: string, to: string): string {
        const fromDir = path.dirname(this.resolvePath(from));
        const toPath = this.resolvePath(to);
        let relative = path.relative(fromDir, toPath);

        if (!relative.startsWith('.')) {
            relative = './' + relative;
        }

        return relative.replace(/\\/g, '/').replace(/\.[jt]sx?$/, '');
    }

    // ============ Test Execution ============
    async runTests(suiteId?: string): Promise<TestResult[]> {
        const { exec } = require('child_process');

        return new Promise((resolve) => {
            const command = this.getTestCommand(suiteId);

            log.info(`Running tests: ${command}`);

            exec(command, { cwd: this.workspaceRoot }, (error: Error | null, stdout: string, stderr: string) => {
                const results: TestResult[] = [];

                if (error) {
                    log.warn('Test run had failures');
                    results.push({
                        passed: false,
                        duration: 0,
                        error: stderr || stdout
                    });
                } else {
                    log.info('Tests passed');
                    results.push({
                        passed: true,
                        duration: this.parseTestDuration(stdout)
                    });
                }

                resolve(results);
            });
        });
    }

    private getTestCommand(suiteId?: string): string {
        const base = {
            vitest: 'npx vitest run',
            jest: 'npx jest',
            mocha: 'npx mocha'
        }[this.config.framework];

        if (suiteId) {
            const suite = this.suites.get(suiteId);
            if (suite?.tests[0]) {
                return `${base} ${suite.tests[0].testFile}`;
            }
        }

        return base;
    }

    private parseTestDuration(output: string): number {
        const match = output.match(/(\d+(?:\.\d+)?)\s*(?:ms|s)/);
        if (match) {
            const value = parseFloat(match[1]);
            return match[0].includes('s') && !match[0].includes('ms') ? value * 1000 : value;
        }
        return 0;
    }

    // ============ Coverage ============
    async getCoverage(): Promise<CoverageReport | null> {
        const coveragePath = path.join(this.workspaceRoot || '', 'coverage', 'coverage-summary.json');

        if (!fs.existsSync(coveragePath)) {
            log.info('No coverage report found');
            return null;
        }

        try {
            const data = JSON.parse(fs.readFileSync(coveragePath, 'utf-8'));
            const total = data.total;

            return {
                lines: total.lines.pct,
                branches: total.branches.pct,
                functions: total.functions.pct,
                statements: total.statements.pct
            };
        } catch (error) {
            log.error('Failed to parse coverage: ' + (error as Error).message);
            return null;
        }
    }

    // ============ Utilities ============
    private resolvePath(relativePath: string): string {
        if (path.isAbsolute(relativePath)) return relativePath;
        return path.join(this.workspaceRoot || '', relativePath);
    }

    private generateId(): string {
        return `test_${Date.now()}_${Math.random().toString(36).substring(7)}`;
    }

    // ============ Configuration ============
    setConfig(config: Partial<TestGeneratorConfig>): void {
        this.config = { ...this.config, ...config };
        log.info('Test generator config updated');
    }

    getConfig(): TestGeneratorConfig {
        return { ...this.config };
    }

    getSuites(): TestSuite[] {
        return Array.from(this.suites.values());
    }
}

// Singleton export
export const testGenerator = new TestGenerator();
