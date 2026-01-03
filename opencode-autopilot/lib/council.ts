import type { CouncilConfig, DevelopmentContext, Guidance, ISupervisor, Message } from './types';

export class Council {
  private supervisors: ISupervisor[] = [];
  private config: CouncilConfig;
  private history: Message[] = [];

  constructor(config: CouncilConfig) {
    this.config = config;
  }

  public registerSupervisor(supervisor: ISupervisor): void {
    this.supervisors.push(supervisor);
  }

  public async init(): Promise<void> {
    const initPromises = this.supervisors.map(s => s.init());
    await Promise.all(initPromises);
  }

  public async discuss(context: DevelopmentContext): Promise<Guidance> {
    // 1. Initial Review Round
    // If smart pilot is disabled in config, skip discussion and return a dummy guidance
    if (this.config.smartPilot === false) {
       console.log("Smart Pilot disabled. Skipping detailed discussion.");
       return {
         approved: false, // Default to false so fallback logic can take over
         feedback: "Smart Pilot is disabled.",
         suggestedNextSteps: []
       };
    }

    console.log("Starting Council Discussion...");
    
    // In a real implementation, we might want supervisors to see each other's messages.
    // For now, we'll implement a simple round-robin or parallel review.
    
    const discussionLog: Message[] = [];

    for (let round = 0; round < this.config.debateRounds; round++) {
      console.log(`--- Debate Round ${round + 1} ---`);
      
      // Parallel input from all supervisors
      const roundPromises = this.supervisors.map(async (supervisor) => {
        const response = await supervisor.chat([...this.history, ...discussionLog, {
          role: 'system',
          content: `Round ${round + 1}: Analyze the current project state and provide your perspective. Context: ${JSON.stringify(context)}`
        }]);
        
        return {
          role: 'assistant' as const,
          content: `[${supervisor.name}]: ${response}`
        };
      });

      const roundResults = await Promise.all(roundPromises);
      discussionLog.push(...roundResults);
      
      // Log for the main history
      this.history.push(...roundResults);
    }

    // 2. Consensus / Final Guidance
    if (this.supervisors.length === 0) {
      throw new Error("No supervisors registered in the council.");
    }

    // Safe access because we checked length > 0
    const leadSupervisor = this.supervisors[0];
    // Double check to satisfy TS if needed, though length check handles it.
    if (!leadSupervisor) {
        throw new Error("Unexpected undefined supervisor");
    }

    const finalGuidance = await leadSupervisor.review(context, discussionLog);
    
    return finalGuidance;
  }
}
