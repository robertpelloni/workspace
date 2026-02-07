
/**
 * Yoke AntiGravity - Memory Manager
 * Persistent session memory with context tracking
 * @module core/memory-manager
 */

import * as vscode from 'vscode';
import * as fs from 'fs';
import * as path from 'path';
import { createLogger } from '../utils/logger';

const log = createLogger('MemoryManager');

// ============ Types ============
export interface MemoryEntry {
    id: string;
    type: 'file_edit' | 'conversation' | 'task_complete' | 'error' | 'model_switch' | 'custom';
    timestamp: number;
    content: string;
    metadata?: Record<string, unknown>;
    tags?: string[];
}

export interface SessionMemory {
    sessionId: string;
    startTime: number;
    endTime?: number;
    entries: MemoryEntry[];
    summary?: string;
}

export interface MemorySearchResult {
    entry: MemoryEntry;
    relevance: number;
    sessionId: string;
}

// ============ Memory Manager Class ============
export class MemoryManager {
    private currentSession: SessionMemory | null = null;
    private storagePath: string | null = null;
    private memoryIndex: Map<string, string[]> = new Map(); // keyword -> entryIds

    constructor() {
        this.initializeStorage();
    }

    private initializeStorage(): void {
        const folders = vscode.workspace.workspaceFolders;
        if (folders?.[0]) {
            this.storagePath = path.join(folders[0].uri.fsPath, '.yoke', 'memory');
            this.ensureStorageDir();
            this.loadIndex();
        }
    }

    private ensureStorageDir(): void {
        if (this.storagePath && !fs.existsSync(this.storagePath)) {
            fs.mkdirSync(this.storagePath, { recursive: true });
            log.info(`Created memory storage at ${this.storagePath}`);
        }
    }

    // ============ Session Management ============
    startSession(): string {
        const sessionId = `session_${Date.now()}_${Math.random().toString(36).substring(7)}`;

        this.currentSession = {
            sessionId,
            startTime: Date.now(),
            entries: []
        };

        log.info(`Started new memory session: ${sessionId}`);
        return sessionId;
    }

    endSession(summary?: string): void {
        if (!this.currentSession) return;

        this.currentSession.endTime = Date.now();
        this.currentSession.summary = summary || this.generateSessionSummary();

        this.saveSession(this.currentSession);
        log.info(`Ended session: ${this.currentSession.sessionId}`);

        this.currentSession = null;
    }

    // ============ Memory Operations ============
    remember(entry: Omit<MemoryEntry, 'id' | 'timestamp'>): string {
        if (!this.currentSession) {
            this.startSession();
        }

        const id = `mem_${Date.now()}_${Math.random().toString(36).substring(7)}`;
        const fullEntry: MemoryEntry = {
            ...entry,
            id,
            timestamp: Date.now()
        };

        this.currentSession!.entries.push(fullEntry);
        this.indexEntry(fullEntry);

        // Auto-save periodically
        if (this.currentSession!.entries.length % 10 === 0) {
            this.saveSession(this.currentSession!);
        }

        log.info(`Remembered: ${entry.type}`); // Simplified log
        return id;
    }

    rememberFileEdit(filePath: string, changes: string): string {
        return this.remember({
            type: 'file_edit',
            content: `File: ${filePath}\nChanges: ${changes}`,
            metadata: { filePath },
            tags: this.extractTags(changes)
        });
    }

    rememberConversation(prompt: string, response: string): string {
        return this.remember({
            type: 'conversation',
            content: `Prompt: ${prompt}\nResponse: ${response.substring(0, 500)}...`,
            tags: this.extractTags(prompt)
        });
    }

    rememberTaskComplete(task: string, result: string): string {
        return this.remember({
            type: 'task_complete',
            content: `Task: ${task}\nResult: ${result}`,
            tags: this.extractTags(task)
        });
    }

    rememberError(error: string, context: string): string {
        return this.remember({
            type: 'error',
            content: `Error: ${error}\nContext: ${context}`,
            tags: ['error', ...this.extractTags(error)]
        });
    }

    rememberModelSwitch(fromModel: string, toModel: string, reason: string): string {
        return this.remember({
            type: 'model_switch',
            content: `Switched from ${fromModel} to ${toModel}. Reason: ${reason}`,
            metadata: { fromModel, toModel, reason },
            tags: ['model_switch']
        });
    }

    // ============ Search & Retrieval ============
    search(query: string, limit = 10): MemorySearchResult[] {
        const results: MemorySearchResult[] = [];
        const queryWords = this.tokenize(query.toLowerCase());

        // Search current session
        if (this.currentSession) {
            for (const entry of this.currentSession.entries) {
                const relevance = this.calculateRelevance(entry, queryWords);
                if (relevance > 0) {
                    results.push({
                        entry,
                        relevance,
                        sessionId: this.currentSession.sessionId
                    });
                }
            }
        }

        // Search past sessions
        const pastSessions = this.loadRecentSessions(5);
        for (const session of pastSessions) {
            for (const entry of session.entries) {
                const relevance = this.calculateRelevance(entry, queryWords);
                if (relevance > 0) {
                    results.push({
                        entry,
                        relevance,
                        sessionId: session.sessionId
                    });
                }
            }
        }

        // Sort by relevance and return top results
        return results
            .sort((a, b) => b.relevance - a.relevance)
            .slice(0, limit);
    }

    getRecentMemories(count = 20): MemoryEntry[] {
        const entries: MemoryEntry[] = [];

        if (this.currentSession) {
            entries.push(...this.currentSession.entries.slice(-count));
        }

        if (entries.length < count) {
            const pastSessions = this.loadRecentSessions(3);
            for (const session of pastSessions) {
                entries.push(...session.entries);
                if (entries.length >= count) break;
            }
        }

        return entries
            .sort((a, b) => b.timestamp - a.timestamp)
            .slice(0, count);
    }

    getContextForPrompt(task: string, maxTokens = 2000): string {
        const relevantMemories = this.search(task, 5);
        const recentMemories = this.getRecentMemories(5);

        const contextParts: string[] = [];
        let tokenCount = 0;
        const estimatedTokensPerChar = 0.25;

        // Add relevant memories
        if (relevantMemories.length > 0) {
            contextParts.push('## Relevant Context from Memory:');
            for (const result of relevantMemories) {
                const entry = result.entry;
                const text = `- [${entry.type}] ${entry.content.substring(0, 200)}`;
                const tokens = text.length * estimatedTokensPerChar;

                if (tokenCount + tokens > maxTokens) break;
                contextParts.push(text);
                tokenCount += tokens;
            }
        }

        // Add recent activity
        if (recentMemories.length > 0 && tokenCount < maxTokens * 0.8) {
            contextParts.push('\n## Recent Activity:');
            for (const entry of recentMemories) {
                const text = `- [${this.formatTime(entry.timestamp)}] ${entry.type}: ${entry.content.substring(0, 100)}`;
                const tokens = text.length * estimatedTokensPerChar;

                if (tokenCount + tokens > maxTokens) break;
                contextParts.push(text);
                tokenCount += tokens;
            }
        }

        return contextParts.join('\n');
    }

    // ============ Persistence ============
    private saveSession(session: SessionMemory): void {
        if (!this.storagePath) return;

        try {
            const filePath = path.join(this.storagePath, `${session.sessionId}.json`);
            fs.writeFileSync(filePath, JSON.stringify(session, null, 2));
            this.saveIndex();
        } catch (error) {
            log.error('Failed to save session: ' + (error as Error).message);
        }
    }

    private loadRecentSessions(count: number): SessionMemory[] {
        if (!this.storagePath || !fs.existsSync(this.storagePath)) return [];

        try {
            const files = fs.readdirSync(this.storagePath)
                .filter(f => f.startsWith('session_') && f.endsWith('.json'))
                .sort()
                .reverse()
                .slice(0, count);

            return files.map(f => {
                const content = fs.readFileSync(path.join(this.storagePath!, f), 'utf-8');
                return JSON.parse(content) as SessionMemory;
            });
        } catch (error) {
            log.error('Failed to load sessions: ' + (error as Error).message);
            return [];
        }
    }

    private loadIndex(): void {
        if (!this.storagePath) return;

        const indexPath = path.join(this.storagePath, 'index.json');
        if (fs.existsSync(indexPath)) {
            try {
                const data = JSON.parse(fs.readFileSync(indexPath, 'utf-8'));
                this.memoryIndex = new Map(Object.entries(data));
            } catch (error) {
                log.warn('Failed to load memory index');
            }
        }
    }

    private saveIndex(): void {
        if (!this.storagePath) return;

        try {
            const indexPath = path.join(this.storagePath, 'index.json');
            const data = Object.fromEntries(this.memoryIndex);
            fs.writeFileSync(indexPath, JSON.stringify(data));
        } catch (error) {
            log.warn('Failed to save memory index');
        }
    }

    // ============ Indexing ============
    private indexEntry(entry: MemoryEntry): void {
        const words = this.tokenize(entry.content.toLowerCase());
        const tags = entry.tags || [];

        for (const word of [...words, ...tags]) {
            if (word.length < 3) continue;

            const existing = this.memoryIndex.get(word) || [];
            if (!existing.includes(entry.id)) {
                existing.push(entry.id);
                this.memoryIndex.set(word, existing);
            }
        }
    }

    private calculateRelevance(entry: MemoryEntry, queryWords: string[]): number {
        const entryWords = new Set(this.tokenize(entry.content.toLowerCase()));
        const entryTags = new Set(entry.tags?.map(t => t.toLowerCase()) || []);

        let score = 0;
        for (const word of queryWords) {
            if (entryWords.has(word)) score += 1;
            if (entryTags.has(word)) score += 2; // Tags are more valuable
        }

        // Recency bonus
        const ageHours = (Date.now() - entry.timestamp) / (1000 * 60 * 60);
        const recencyBonus = Math.max(0, 1 - ageHours / 24); // Decay over 24 hours

        return score + recencyBonus;
    }

    // ============ Utilities ============
    private tokenize(text: string): string[] {
        return text
            .replace(/[^\w\s]/g, ' ')
            .split(/\s+/)
            .filter(w => w.length > 2);
    }

    private extractTags(text: string): string[] {
        const tags: string[] = [];

        // Extract file extensions
        const extMatches = text.match(/\.\w{2,4}(?=\s|$)/g);
        if (extMatches) tags.push(...extMatches.map(e => e.substring(1)));

        // Extract common programming terms
        const keywords = ['function', 'class', 'component', 'api', 'test', 'fix', 'bug', 'feature'];
        for (const kw of keywords) {
            if (text.toLowerCase().includes(kw)) tags.push(kw);
        }

        return [...new Set(tags)];
    }

    private generateSessionSummary(): string {
        if (!this.currentSession) return '';

        const entries = this.currentSession.entries;
        const typeCount: Record<string, number> = {};

        for (const entry of entries) {
            typeCount[entry.type] = (typeCount[entry.type] || 0) + 1;
        }

        const parts = Object.entries(typeCount)
            .map(([type, count]) => `${count} ${type.replace('_', ' ')}s`)
            .join(', ');

        return `Session with ${entries.length} entries: ${parts}`;
    }

    private formatTime(timestamp: number): string {
        const date = new Date(timestamp);
        return date.toLocaleTimeString('en-US', { hour: '2-digit', minute: '2-digit' });
    }

    // ============ Cleanup ============
    cleanup(maxAgeDays = 30): void {
        if (!this.storagePath || !fs.existsSync(this.storagePath)) return;

        const maxAge = maxAgeDays * 24 * 60 * 60 * 1000;
        const now = Date.now();

        try {
            const files = fs.readdirSync(this.storagePath)
                .filter(f => f.startsWith('session_') && f.endsWith('.json'));

            for (const file of files) {
                const filePath = path.join(this.storagePath, file);
                const stats = fs.statSync(filePath);

                if (now - stats.mtime.getTime() > maxAge) {
                    fs.unlinkSync(filePath);
                    log.info(`Cleaned up old session: ${file}`);
                }
            }
        } catch (error) {
            log.error('Cleanup failed: ' + (error as Error).message);
        }
    }

    // ============ Stats ============
    getStats(): { currentEntries: number; totalSessions: number; indexedTerms: number } {
        let totalSessions = 0;

        if (this.storagePath && fs.existsSync(this.storagePath)) {
            totalSessions = fs.readdirSync(this.storagePath)
                .filter(f => f.startsWith('session_') && f.endsWith('.json')).length;
        }

        return {
            currentEntries: this.currentSession?.entries.length || 0,
            totalSessions,
            indexedTerms: this.memoryIndex.size
        };
    }
}

// Singleton export
export const memoryManager = new MemoryManager();
