import { GoogleGenerativeAI } from '@google/generative-ai';
import type { Part, ModelParams } from '@google/generative-ai';
import { BaseSupervisor } from './BaseSupervisor';
import type { Message, SupervisorConfig } from '../types';

export class GoogleSupervisor extends BaseSupervisor {
  private client: GoogleGenerativeAI;

  constructor(config: SupervisorConfig) {
    super(config);
    const apiKey = config.apiKey || process.env.GOOGLE_API_KEY;
    if (!apiKey) {
      throw new Error(`[${this.name}] Google API Key is required.`);
    }
    this.client = new GoogleGenerativeAI(apiKey);
  }

  public async chat(messages: Message[]): Promise<string> {
    try {
      // 1. Extract the last message to use as the prompt
      const lastMsg = messages[messages.length - 1];
      if (!lastMsg) return "No messages provided.";

      // 2. Extract system instruction (if any, excluding the last message if it's system)
      // In Council, the last message IS the system prompt/instruction for the round.
      // We should treat the last message as the USER prompt for Gemini, 
      // and any previous system messages as system instructions.
      
      const previousMessages = messages.slice(0, -1);
      const systemInstructionMsg = previousMessages.find(m => m.role === 'system');
      
      const modelParams: ModelParams = { 
        model: this.config.modelName || 'gemini-1.5-pro'
      };

      if (systemInstructionMsg) {
        modelParams.systemInstruction = systemInstructionMsg.content;
      }

      const model = this.client.getGenerativeModel(modelParams);

      // 3. Build History
      // Filter out system messages from history
      let history = previousMessages
        .filter(m => m.role !== 'system')
        .map(m => ({
          role: m.role === 'assistant' ? 'model' : 'user',
          parts: [{ text: m.content } as Part],
        }));

      // Gemini Requirement: History must start with 'user'.
      // If history is not empty and starts with 'model', prepend a dummy user message.
      const firstMsg = history[0];
      if (firstMsg && firstMsg.role === 'model') {
        history = [
          { role: 'user', parts: [{ text: 'Discussion started.' }] },
          ...history
        ];
      }

      // 4. Start Chat
      const chatSession = model.startChat({
        history: history,
        generationConfig: {
            temperature: this.config.temperature || 0.7,
        }
      });

      // 5. Send the last message (converted to text)
      const result = await chatSession.sendMessage(lastMsg.content);
      const response = result.response;
      return response.text();

    } catch (error: any) {
      console.error(`[${this.name}] Google API Error:`, error.message);
      return `[Error] Failed to generate response: ${error.message}`;
    }
  }
}
