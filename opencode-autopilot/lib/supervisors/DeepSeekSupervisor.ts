import OpenAI from 'openai';
import { BaseSupervisor } from './BaseSupervisor';
import type { Message, SupervisorConfig } from '../types';

export class DeepSeekSupervisor extends BaseSupervisor {
  private client: OpenAI;

  constructor(config: SupervisorConfig) {
    super(config);
    this.client = new OpenAI({
      apiKey: config.apiKey || process.env.DEEPSEEK_API_KEY,
      baseURL: 'https://api.deepseek.com'
    });
  }

  public async chat(messages: Message[]): Promise<string> {
    try {
      const completion = await this.client.chat.completions.create({
        messages: messages.map(m => ({ role: m.role, content: m.content })),
        model: this.config.modelName || 'deepseek-chat',
        temperature: this.config.temperature || 0.7,
      });

      return completion.choices[0]?.message?.content || "No response generated.";
    } catch (error: any) {
      console.error(`[${this.name}] DeepSeek API Error:`, error.message);
      return `[Error] Failed to generate response: ${error.message}`;
    }
  }
}
