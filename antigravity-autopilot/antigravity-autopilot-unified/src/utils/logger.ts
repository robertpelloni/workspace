import * as vscode from 'vscode';

export class Logger {
    private outputChannel: vscode.OutputChannel;
    private context: string;

    constructor(context: string) {
        this.context = context;
        this.outputChannel = vscode.window.createOutputChannel(`Antigravity: ${context}`);
    }

    info(message: string) {
        this.log('INFO', message);
    }

    warn(message: string) {
        this.log('WARN', message);
    }

    error(message: string) {
        this.log('ERROR', message);
    }

    private log(level: string, message: string) {
        const timestamp = new Date().toISOString();
        const formatted = `[${timestamp}] [${level}] ${message}`;
        console.log(`[${this.context}] ${formatted}`);
        this.outputChannel.appendLine(formatted);
    }
}

export function createLogger(context: string): Logger {
    return new Logger(context);
}
