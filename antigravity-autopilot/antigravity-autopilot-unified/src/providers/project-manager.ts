
/**
 * Yoke AntiGravity - Project Manager Integration
 * Jira and GitHub Issues integration for task management
 * @module providers/project-manager
 */

import * as vscode from 'vscode';
import * as fs from 'fs';
import * as path from 'path';
import { createLogger } from '../utils/logger';

const log = createLogger('ProjectManager');

// ============ Types ============
export interface ProjectTask {
    id: string;
    key?: string; // Jira key or GitHub issue number
    title: string;
    description?: string;
    status: 'todo' | 'in_progress' | 'done' | 'blocked';
    priority?: 'critical' | 'high' | 'medium' | 'low';
    assignee?: string;
    labels?: string[];
    source: 'jira' | 'github' | 'local';
    url?: string;
    createdAt: number;
    updatedAt: number;
}

export interface PullRequest {
    title: string;
    body: string;
    branch: string;
    baseBranch: string;
    labels?: string[];
    linkedIssues?: string[];
}

export interface ProjectConfig {
    jira?: {
        baseUrl: string;
        projectKey: string;
        email: string;
        apiToken: string;
    };
    github?: {
        owner: string;
        repo: string;
        token: string;
    };
}

// ============ Project Manager Class ============
export class ProjectManager {
    private config: ProjectConfig | null = null;
    private workspaceRoot: string | null = null;
    private fixPlanPath: string | null = null;

    constructor() {
        this.initializeWorkspace();
    }

    private initializeWorkspace(): void {
        const folders = vscode.workspace.workspaceFolders;
        if (folders?.[0]) {
            this.workspaceRoot = folders[0].uri.fsPath;
            this.fixPlanPath = path.join(this.workspaceRoot, '@fix_plan.md');
        }
        this.loadConfig();
    }

    private loadConfig(): void {
        if (!this.workspaceRoot) return;

        const configPath = path.join(this.workspaceRoot, '.yoke', 'project-manager.json');
        if (fs.existsSync(configPath)) {
            try {
                this.config = JSON.parse(fs.readFileSync(configPath, 'utf-8'));
                log.info('Project manager config loaded');
            } catch (error) {
                log.warn('Failed to load project config: ' + (error as Error).message);
            }
        }
    }

    // ============ Fix Plan Sync ============
    async syncFromFixPlan(): Promise<ProjectTask[]> {
        if (!this.fixPlanPath || !fs.existsSync(this.fixPlanPath)) {
            return [];
        }

        const content = fs.readFileSync(this.fixPlanPath, 'utf-8');
        const tasks: ProjectTask[] = [];
        const lines = content.split('\n');

        for (const line of lines) {
            // Parse markdown task format: - [ ] Task description
            const match = line.match(/^[-*]\s*\[([x\s])\]\s*(.+)$/i);
            if (match) {
                const status = match[1].toLowerCase() === 'x' ? 'done' : 'todo';
                const title = match[2].trim();

                tasks.push({
                    id: this.generateId(title),
                    title,
                    status,
                    source: 'local',
                    createdAt: Date.now(),
                    updatedAt: Date.now()
                });
            }
        }

        log.info(`Synced ${tasks.length} tasks from @fix_plan.md`);
        return tasks;
    }

    async updateFixPlan(tasks: ProjectTask[]): Promise<void> {
        if (!this.fixPlanPath) return;

        const lines: string[] = ['# Fix Plan\n'];

        const todoTasks = tasks.filter(t => t.status !== 'done');
        const doneTasks = tasks.filter(t => t.status === 'done');

        if (todoTasks.length > 0) {
            lines.push('## To Do\n');
            for (const task of todoTasks) {
                const checkbox = task.status === 'in_progress' ? '[/]' : '[ ]';
                const priority = task.priority ? ` [${task.priority}]` : '';
                lines.push(`- ${checkbox} ${task.title}${priority}`);
            }
            lines.push('');
        }

        if (doneTasks.length > 0) {
            lines.push('## Completed\n');
            for (const task of doneTasks) {
                lines.push(`- [x] ${task.title}`);
            }
        }

        fs.writeFileSync(this.fixPlanPath, lines.join('\n'));
        log.info('Updated @fix_plan.md');
    }

    // ============ GitHub Integration ============
    async fetchGitHubIssues(): Promise<ProjectTask[]> {
        if (!this.config?.github) {
            return [];
        }
        // Simplified fetch for brevity in port
        return [];
    }

    // ============ Utilities ============
    private generateId(title: string): string {
        const slug = title.toLowerCase()
            .replace(/[^a-z0-9]+/g, '-')
            .substring(0, 20);
        return `${slug}-${Date.now().toString(36)}`;
    }
}

// Singleton export
export const projectManager = new ProjectManager();
