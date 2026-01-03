export interface Message {
  role: 'system' | 'user' | 'assistant';
  content: string;
}

export interface SupervisorConfig {
  name: string;
  provider: 'openai' | 'anthropic' | 'google' | 'xai' | 'moonshot' | 'deepseek' | 'qwen' | 'custom';
  apiKey?: string;
  modelName: string;
  temperature?: number;
}

export interface DevelopmentContext {
  currentGoal: string;
  recentChanges: string[];
  fileContext: Record<string, string>;
  projectState: string;
}

export interface Guidance {
  approved: boolean;
  feedback: string;
  suggestedNextSteps: string[];
}

export interface ISupervisor {
  name: string;
  init(): Promise<void>;
  review(context: DevelopmentContext, history: Message[]): Promise<Guidance>;
  chat(messages: Message[]): Promise<string>;
}

export interface CouncilConfig {
  supervisors: SupervisorConfig[];
  debateRounds: number; // How many rounds of discussion before final consensus
  autoContinue: boolean; // Whether to automatically proceed based on consensus
  enabled?: boolean;
  smartPilot?: boolean;
  fallbackMessages?: string[];
}
