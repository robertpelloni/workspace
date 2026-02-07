
import { CDPHandler } from '../services/cdp/cdp-handler';
import { createLogger } from '../utils/logger';
import { config } from '../utils/config';

const log = createLogger('CDPClient');

export class CDPClient {
    private handler: CDPHandler;
    private isPro = true;

    constructor() {
        this.handler = new CDPHandler();
    }

    async connect(): Promise<boolean> {
        return await this.handler.connect(); // Assuming handler has a connect method or similar
    }

    isConnected(): boolean {
        return this.handler.isConnected();
    }

    async injectPrompt(prompt: string): Promise<boolean> {
        // Find active tab and inject prompt
        const instances = await this.handler.scanForInstances();
        for (const instance of instances) {
            for (const page of instance.pages) {
                if (page.url.includes('editor')) { // Simplified check
                    // This is where real injection logic goes, likely using Runtime.evaluate
                    const script = `
                        (function() {
                            const input = document.querySelector('textarea, div[contenteditable="true"]');
                            if (input) {
                                input.innerText = ${JSON.stringify(prompt)};
                                input.dispatchEvent(new Event('input', { bubbles: true }));
                                // Find send button and click
                                const btn = document.querySelector('button[aria-label="Send"], button[class*="send"]');
                                if (btn) btn.click();
                                return true;
                            }
                            return false;
                        })()
                     `;
                    const result = await this.handler.sendCommand(page.id, 'Runtime.evaluate', { expression: script, returnByValue: true });
                    if (result && result.result && result.result.value) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    async waitForResponse(timeoutMs: number): Promise<string> {
        return new Promise(resolve => {
            setTimeout(() => {
                resolve("Mock Response for now - need real event listener");
            }, 2000);
        });
    }

    async evaluate(expression: string): Promise<any> {
        const instances = await this.handler.scanForInstances();
        for (const instance of instances) {
            for (const page of instance.pages) {
                if (page.url.includes('editor') || page.title.includes('Cursor') || page.title.includes('Visual Studio Code')) {
                    const result = await this.handler.sendCommand(page.id, 'Runtime.evaluate', {
                        expression,
                        returnByValue: true,
                        awaitPromise: true
                    });
                    if (result && result.result) {
                        return result.result.value;
                    }
                }
            }
        }
        return null;
    }

    async switchModel(modelId: string): Promise<boolean> {
        log.info(`Switching to model ${modelId}`);
        // Implement model switching logic via DOM
        return true;
    }
}

export const cdpClient = new CDPClient();
