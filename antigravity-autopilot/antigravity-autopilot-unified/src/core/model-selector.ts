
import { createLogger } from '../utils/logger';
import * as vscode from 'vscode';
import { getAvailableModels } from './model-scraper';
import { ModelId, TaskType } from '../utils/constants';

const log = createLogger('ModelSelector');

export interface ModelSelection {
    modelId: string;
    modelDisplayName: string;
    reasoning: string;
}

export class ModelSelector {

    async selectForTask(task: string): Promise<ModelSelection> {
        const lowerTask = task.toLowerCase();
        let model: string = ModelId.GEMINI_FLASH; // Default fast model
        let reason = 'Default general purpose model';

        // 1. Get Available Models (cached)
        const availableModels = await getAvailableModels();
        const availableValues = availableModels.map(m => m.value);

        // Helper to find best match in available models
        const findBestMatch = (preferred: string[], fallback: string): string => {
            for (const p of preferred) {
                if (availableValues.includes(p)) return p;
            }
            return fallback;
        };

        // 2. Select based on task type
        if (lowerTask.includes('css') || lowerTask.includes('ui') || lowerTask.includes('frontend')) {
            model = findBestMatch([ModelId.GEMINI_FLASH, 'gpt-4o'], ModelId.GEMINI_FLASH);
            reason = 'Fast vision/UI model';
        } else if (lowerTask.includes('refactor') || lowerTask.includes('architecture') || lowerTask.includes('plan')) {
            model = findBestMatch([ModelId.CLAUDE_OPUS_THINKING, ModelId.CLAUDE_SONNET_THINKING, 'gpt-4-turbo'], ModelId.CLAUDE_SONNET);
            reason = 'Strong reasoning for architecture';
        } else if (lowerTask.includes('test') || lowerTask.includes('debug')) {
            model = findBestMatch(['gpt-4o', ModelId.GEMINI_PRO_HIGH], 'gpt-4o');
            reason = 'Reliable for debugging';
        }

        // Find display name
        const modelObj = availableModels.find(m => m.value === model);
        const displayName = modelObj ? modelObj.label : model;

        return {
            modelId: model,
            modelDisplayName: displayName,
            reasoning: reason
        };
    }

    showSwitchNotification(selection: ModelSelection) {
        vscode.window.showInformationMessage(`🧠 Switched to ${selection.modelDisplayName}: ${selection.reasoning}`);
    }
}

export const modelSelector = new ModelSelector();
