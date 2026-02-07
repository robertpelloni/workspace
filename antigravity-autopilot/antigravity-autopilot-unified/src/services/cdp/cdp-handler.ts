import WebSocket from 'ws';
import * as http from 'http';
import * as fs from 'fs';
import * as path from 'path';
import { EventEmitter } from 'events';

export class CDPHandler extends EventEmitter {
    private startPort: number;
    private endPort: number;
    private connections: Map<string, any>;
    private messageId: number;
    private pendingMessages: Map<number, { resolve: Function, reject: Function }>;

    constructor(startPort = 9000, endPort = 9030) {
        super();
        this.startPort = startPort;
        this.endPort = endPort;
        this.connections = new Map();
        this.messageId = 1;
        this.pendingMessages = new Map();
    }

    async scanForInstances(): Promise<{ port: number, pages: any[] }[]> {
        const instances = [];
        for (let port = this.startPort; port <= this.endPort; port++) {
            try {
                const pages = await this.getPages(port);
                if (pages.length > 0) instances.push({ port, pages });
            } catch (e) { }
        }
        return instances;
    }

    getPages(port: number): Promise<any[]> {
        return new Promise((resolve, reject) => {
            const req = http.get({ hostname: '127.0.0.1', port, path: '/json/list', timeout: 500 }, (res) => {
                let data = '';
                res.on('data', chunk => data += chunk);
                res.on('end', () => {
                    try { resolve(JSON.parse(data).filter((p: any) => p.webSocketDebuggerUrl)); }
                    catch (e) { reject(e); }
                });
            });
            req.on('error', reject);
            req.on('timeout', () => { req.destroy(); reject(new Error('timeout')); });
        });
    }

    async connectToPage(page: any): Promise<boolean> {
        return new Promise((resolve) => {
            const ws = new WebSocket(page.webSocketDebuggerUrl);
            ws.on('open', () => {
                this.connections.set(page.id, { ws, injected: false });
                resolve(true);
            });
            ws.on('message', (data: any) => {
                try {
                    const msg = JSON.parse(data.toString());
                    if (msg.id && this.pendingMessages.has(msg.id)) {
                        const { resolve: res, reject: rej } = this.pendingMessages.get(msg.id)!;
                        this.pendingMessages.delete(msg.id);
                        msg.error ? rej(new Error(msg.error.message)) : res(msg.result);
                    }
                } catch (e) { }
            });
            ws.on('error', (err: Error) => {
                console.log(`WS Error on ${page.id}: ${err.message}`);
                this.connections.delete(page.id);
                resolve(false);
            });
            ws.on('close', () => {
                this.connections.delete(page.id);
            });
        });
    }

    async sendCommand(pageId: string, method: string, params: any = {}): Promise<any> {
        const conn = this.connections.get(pageId);
        if (!conn || conn.ws.readyState !== WebSocket.OPEN) return Promise.reject(new Error('dead'));
        const id = this.messageId++;
        return new Promise((resolve, reject) => {
            this.pendingMessages.set(id, { resolve, reject });
            conn.ws.send(JSON.stringify({ id, method, params }));
            setTimeout(() => {
                if (this.pendingMessages.has(id)) {
                    this.pendingMessages.delete(id);
                    reject(new Error('timeout'));
                }
            }, 2000);
        });
    }

    async injectScript(pageId: string, scriptContent: string): Promise<void> {
        const conn = this.connections.get(pageId);
        if (!conn) return;

        if (!conn.injected) {
            try {
                await this.sendCommand(pageId, 'Runtime.evaluate', {
                    expression: scriptContent,
                    userGesture: true,
                    awaitPromise: true
                });
                conn.injected = true;
            } catch (e) {
                console.error(`Injection failed on ${pageId}`, e);
            }
        }
    }

    disconnectAll() {
        for (const [, conn] of this.connections) {
            try { conn.ws.close(); } catch (e) { }
        }
        this.connections.clear();
    }
    isConnected(): boolean {
        return this.connections.size > 0;
    }

    async connect(): Promise<boolean> {
        const instances = await this.scanForInstances();
        return instances.length > 0;
    }
}
