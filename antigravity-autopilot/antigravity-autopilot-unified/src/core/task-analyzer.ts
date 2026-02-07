
import { createLogger } from '../utils/logger';

const log = createLogger('TaskAnalyzer');

export class TaskAnalyzer {
    extractCurrentTask(content: string): string | null {
        if (!content) return null;

        const lines = content.split('\n');
        for (const line of lines) {
            const trimmed = line.trim();
            // Match [ ] or [ ] with widely varying checks
            if (trimmed.match(/^- \[[ ]\]/)) {
                // Ignore if it looks like a header or crossed out
                if (trimmed.includes('~~')) continue;

                const task = trimmed.replace(/^- \[[ ]\]/, '').trim();
                // Filter out empty tasks
                if (task.length < 3) continue;

                log.info(`Found next task: ${task}`);
                return task;
            }
        }
        return null;
    }
}

export const taskAnalyzer = new TaskAnalyzer();
