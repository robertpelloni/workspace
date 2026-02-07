/**
 * Antigravity Autopilot - Model Scraper
 * Dynamically detects available models from Antigravity's UI
 * @module core/model-scraper
 */

import { cdpClient } from '../providers/cdp-client';
import { createLogger } from '../utils/logger';
import { MODEL_LABELS } from '../utils/constants';

const log = createLogger('ModelScraper');

// Cache for scraped models
let cachedModels: { value: string; label: string }[] = [];
let lastScrapeTime = 0;
const CACHE_DURATION_MS = 60000; // 1 minute cache

/**
 * Get available models from Antigravity's model selector
 * Falls back to hardcoded list if scraping fails
 */
export async function getAvailableModels(): Promise<{ value: string; label: string }[]> {
    // Return cached if fresh
    if (cachedModels.length > 0 && Date.now() - lastScrapeTime < CACHE_DURATION_MS) {
        return cachedModels;
    }

    // Try to scrape from Antigravity
    try {
        const scraped = await scrapeModelsFromUI();
        if (scraped.length > 0) {
            cachedModels = scraped;
            lastScrapeTime = Date.now();
            log.info(`Scraped ${scraped.length} models from Antigravity`);
            return cachedModels;
        }
    } catch (err) {
        log.warn(`Failed to scrape models: ${(err as Error).message}`);
    }

    // Fallback to hardcoded models
    return getHardcodedModels();
}

/**
 * Scrape models from Antigravity's model selector dropdown via CDP
 */
async function scrapeModelsFromUI(): Promise<{ value: string; label: string }[]> {
    if (!cdpClient.isConnected()) {
        const connected = await cdpClient.connect();
        if (!connected) return [];
    }

    // JavaScript to extract model options from Antigravity's UI
    const result = await cdpClient.evaluate(`
        (function() {
            const models = [];
            
            // Try to find model selector dropdown options
            // Method 1: Look for the model dropdown button and its options
            const modelBtn = document.querySelector('[data-testid="model-selector"], .model-dropdown, button[aria-label*="model"], button[class*="model"]');
            if (modelBtn) {
                // Click to open dropdown
                modelBtn.click();
                
                // Wait a bit and collect options
                setTimeout(() => {
                    const options = document.querySelectorAll('[role="option"], [role="menuitem"], .model-option, li[data-value], div[data-value]');
                    options.forEach(opt => {
                        const value = opt.getAttribute('data-value') || opt.getAttribute('data-model') || opt.textContent?.trim().toLowerCase().replace(/\\s+/g, '-');
                        const label = opt.textContent?.trim();
                        if (value && label) {
                            models.push({ value, label });
                        }
                    });
                    // Close dropdown
                    document.body.click();
                }, 300);
            }
            
            // Method 2: Look for existing model name in the UI
            const currentModel = document.querySelector('.model-name, .current-model, [data-testid="current-model"]');
            if (currentModel) {
                const label = currentModel.textContent?.trim();
                if (label) {
                    models.push({ value: label.toLowerCase().replace(/\\s+/g, '-'), label });
                }
            }
            
            return models;
        })()
    `) as { value: string; label: string }[];

    return result || [];
}

/**
 * Get hardcoded fallback models
 */
function getHardcodedModels(): { value: string; label: string }[] {
    return Object.entries(MODEL_LABELS).map(([value, label]) => ({
        value,
        label: label as string
    }));
}

/**
 * Force refresh the model cache
 */
export function refreshModelCache(): void {
    cachedModels = [];
    lastScrapeTime = 0;
}
