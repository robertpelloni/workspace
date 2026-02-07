export interface IStrategy {
    name: string;
    isActive: boolean;
    start(): Promise<void>;
    stop(): Promise<void>;
    dispose(): void;
}
