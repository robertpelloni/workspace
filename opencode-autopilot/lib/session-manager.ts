// @ts-nocheck
import { Council } from './council';
import { OpenAISupervisor } from './supervisors/OpenAISupervisor';
import { AnthropicSupervisor } from './supervisors/AnthropicSupervisor';
import { GoogleSupervisor } from './supervisors/GoogleSupervisor';
import { DeepSeekSupervisor } from './supervisors/DeepSeekSupervisor';
import { MockSupervisor } from './supervisors/MockSupervisor';
import type { CouncilConfig, SupervisorConfig } from './types';

// Simplified for Vercel Serverless environment
// We cannot spawn child processes or maintain persistent state easily here
// So we strip out the child_process and net logic
// This effectively makes it a stateless session manager wrapper around the Council logic

interface Session {
    id: string;
    messages: { role: string, content: string }[];
    council: Council | null;
}

export class SessionManager {
    private sessions: Map<string, Session> = new Map();

    constructor() {
        // No auto-start or persistent storage in this serverless demo version
    }

    public createSession(config: any) {
        const id = Math.random().toString(36).substring(7);
        const session: Session = {
            id,
            messages: [],
            council: null
        };
        
        // Initialize council immediately
        this.initializeCouncil(session, config);
        
        this.sessions.set(id, session);
        return session;
    }

    public getSession(id: string) {
        // Return a wrapper that has the chat method
        const session = this.sessions.get(id);
        if (!session) return undefined;

        return {
            ...session,
            chat: async (message: string) => this.handleChat(session, message)
        };
    }

    private async handleChat(session: Session, message: string) {
        session.messages.push({ role: 'user', content: message });
        
        if (!session.council) {
            return { error: "Council not initialized" };
        }

        // Simulate context gathering
        const context = {
            currentGoal: message,
            recentChanges: [],
            fileContext: {},
            projectState: "Active Development"
        };

        const guidance = await session.council.discuss(context);
        
        // Format response
        const responseText = `
**Council Decision:** ${guidance.approved ? '✅ Approved' : '❌ Rejected'}

**Feedback:**
${guidance.feedback}

**Suggested Next Steps:**
${guidance.suggestedNextSteps.map((s: string) => `- ${s}`).join('\n')}
        `.trim();

        session.messages.push({ role: 'assistant', content: responseText });
        return { response: responseText, guidance };
    }

    private initializeCouncil(session: Session, userSettings?: any) {
        const supervisors: SupervisorConfig[] = [];
        
        if (userSettings && userSettings.smartPilot) {
             supervisors.push({
                 name: "Primary-Supervisor",
                 provider: userSettings.provider,
                 apiKey: userSettings.apiKey,
                 modelName: userSettings.model
             });
        } else {
            // Fallback to env vars
            if (process.env.OPENAI_API_KEY) supervisors.push({ name: "GPT-Architect", provider: "openai", modelName: "gpt-4o" });
            if (process.env.ANTHROPIC_API_KEY) supervisors.push({ name: "Claude-Reviewer", provider: "anthropic", modelName: "claude-3-5-sonnet-20241022" });
            if (process.env.GOOGLE_API_KEY) supervisors.push({ name: "Gemini-Strategist", provider: "google", modelName: "gemini-pro" });
            if (process.env.DEEPSEEK_API_KEY) supervisors.push({ name: "DeepSeek-Analyst", provider: "deepseek", modelName: "deepseek-chat" });
        }
        
        if (supervisors.length === 0) {
            supervisors.push({ name: "Mock-Critic", provider: "custom", modelName: "mock-v1" });
        }

        const config: CouncilConfig = {
            supervisors,
            debateRounds: userSettings?.debate ? 2 : 0,
            autoContinue: false,
            enabled: userSettings?.enabled ?? true,
            smartPilot: userSettings?.smartPilot ?? false,
            fallbackMessages: userSettings?.messages ? userSettings.messages.split('\n') : []
        };

        const council = new Council(config);
        
        config.supervisors.forEach(conf => {
            switch (conf.provider) {
            case 'openai': council.registerSupervisor(new OpenAISupervisor(conf)); break;
            case 'anthropic': council.registerSupervisor(new AnthropicSupervisor(conf)); break;
            case 'google': council.registerSupervisor(new GoogleSupervisor(conf)); break;
            case 'deepseek': council.registerSupervisor(new DeepSeekSupervisor(conf)); break;
            default: council.registerSupervisor(new MockSupervisor(conf)); break;
            }
        });

        // Async init - we just fire and forget here for simplicity, 
        // real app should await this during creation
        council.init().catch(console.error);
        session.council = council;
    }
}
