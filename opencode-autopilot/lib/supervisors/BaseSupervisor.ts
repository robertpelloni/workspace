import type { DevelopmentContext, Guidance, ISupervisor, Message, SupervisorConfig } from '../types';

export abstract class BaseSupervisor implements ISupervisor {
  public name: string;
  protected config: SupervisorConfig;

  constructor(config: SupervisorConfig) {
    this.name = config.name;
    this.config = config;
  }

  public async init(): Promise<void> {
    console.log(`[${this.name}] Initialized.`);
  }

  public abstract chat(messages: Message[]): Promise<string>;

  public async review(context: DevelopmentContext, history: Message[]): Promise<Guidance> {
    // Default implementation for review - can be overridden by specific supervisors
    // asking them to structure their response as JSON.
    
    const prompt: Message[] = [
      ...history,
      {
        role: 'system',
        content: `Based on the discussion above and the current project context: ${JSON.stringify(context)}, provide final guidance. 
        Return ONLY a JSON object with the following structure:
        {
          "approved": boolean,
          "feedback": "string summary",
          "suggestedNextSteps": ["step 1", "step 2"]
        }`
      }
    ];

    const response = await this.chat(prompt);
    
    try {
      // Basic JSON cleanup if the model returns markdown code blocks
      const cleanResponse = response.replace(/```json/g, '').replace(/```/g, '').trim();
      const guidance = JSON.parse(cleanResponse) as Guidance;
      return guidance;
    } catch (error) {
      console.error(`[${this.name}] Failed to parse guidance JSON:`, error);
      return {
        approved: false,
        feedback: "Failed to parse supervisor response.",
        suggestedNextSteps: ["Retry review"]
      };
    }
  }
}
