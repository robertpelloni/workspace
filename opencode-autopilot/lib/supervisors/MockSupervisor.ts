import { BaseSupervisor } from './BaseSupervisor';
import type { Message, Guidance } from '../types';

export class MockSupervisor extends BaseSupervisor {
  public async chat(messages: Message[]): Promise<string> {
    const lastMessage = messages[messages.length - 1];
    
    // Check if the prompt is asking for JSON (the review step)
    if (lastMessage?.content?.includes('Return ONLY a JSON object')) {
        const mockGuidance: Guidance = {
            approved: true,
            feedback: "Mock supervisor approves of these changes. The structure looks solid.",
            suggestedNextSteps: ["Proceed to implementation", "Add real LLM providers"]
        };
        return JSON.stringify(mockGuidance);
    }

    return `[Mock Response] I received: "${lastMessage?.content?.substring(0, 50)}...". Everything looks nominal from my simulation.`;
  }
}
