import Anthropic from '@anthropic-ai/sdk';
import { BaseSupervisor } from './BaseSupervisor';
import type { Message, SupervisorConfig } from '../types';

export class AnthropicSupervisor extends BaseSupervisor {
  private client: Anthropic;

  constructor(config: SupervisorConfig) {
    super(config);
    this.client = new Anthropic({
      apiKey: config.apiKey || process.env.ANTHROPIC_API_KEY,
    });
  }

  public async chat(messages: Message[]): Promise<string> {
    try {
      // Anthropic API requires 'system' messages to be top-level parameters, not in the messages array
      // So we need to extract them.
      const systemMessage = messages.find(m => m.role === 'system');
      const chatMessages = messages.filter(m => m.role !== 'system');

      const params: Anthropic.MessageCreateParamsNonStreaming = {
        model: this.config.modelName || 'claude-3-5-sonnet-20241022',
        max_tokens: 1024,
        temperature: this.config.temperature || 0.7,
        messages: chatMessages.map(m => ({
          role: m.role === 'assistant' ? 'assistant' : 'user',
          content: m.content
        })),
      };

      if (systemMessage && systemMessage.content) {
        params.system = systemMessage.content;
      }

      const completion = await this.client.messages.create(params);

      // Handle the content block response
      const content = completion.content[0];
      
      if (!content) {
          return "No content generated.";
      }

      if (content.type === 'text') {
          return content.text;
      }
      return "No text response generated (received non-text block).";

    } catch (error: any) {
      console.error(`[${this.name}] Anthropic API Error:`, error.message);
      return `[Error] Failed to generate response: ${error.message}`;
    }
  }
}
