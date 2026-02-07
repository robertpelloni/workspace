
import { createLogger } from '../utils/logger';
import * as vscode from 'vscode';

const log = createLogger('ModelSelector');

export interface ModelSelection {
    modelId: string;
    modelDisplayName: string;
    reasoning: string;
}

export class ModelSelector {
    selectForTask(task: string): ModelSelection {
        // Simple keyword-based selection logic for now
        const lowerTask = task.toLowerCase();

        let model = 'gemini-2.0-flash-thinking-exp-1219'; // Default sane choice
        let reason = 'Default general purpose model';

        if (lowerTask.includes('css') || lowerTask.includes('ui') || lowerTask.includes('frontend')) {
            model = 'gemini-3-flash';
            reason = 'Fast vision model for UI';
        } else if (lowerTask.includes('refactor') || lowerTask.includes('architecture') || lowerTask.includes('plan')) {
            model = 'claude-3-5-sonnet-20240620';
            reason = 'Strong reasoning for architecture';
        } else if (lowerTask.includes('test') || lowerTask.includes('debug')) {
            model = 'gpt-4o';
            reason = 'Reliable for debugging';
        }

        return {
            modelId: model,
            modelDisplayName: model,
            reasoning: reason
        };
    }

    showSwitchNotification(selection: ModelSelection) {
        vscode.window.showInformationMessage(`🧠 Switched to ${selection.modelDisplayName}: ${selection.reasoning}`);
    }
}

export const modelSelector = new ModelSelector();
