import { spawnSync } from 'child_process';
import * as fs from 'fs';
import * as path from 'path';

export interface VocalProcessorConfig {
    mode: 'local' | 'api';
    lalalApiKey?: string;
    targetBpm: number;
    targetKey?: string;
}

export class VocalProcessor {
    private config: VocalProcessorConfig;

    constructor(config: VocalProcessorConfig) {
        this.config = config;
    }

    async process(inputPath: string, outputDir: string): Promise<string> {
        console.log(`Starting vocal processing for ${inputPath}...`);

        // 0. Download if it's a URL
        let localInput = inputPath;
        if (inputPath.startsWith('http')) {
            localInput = await this.downloadAudio(inputPath, outputDir);
        }

        // 1. Demixing
        const vocalStem = await this.isolateVocals(localInput, outputDir);

        // 2. Analysis (BPM/Key)
        const analysis = await this.analyzeAudio(vocalStem);
        console.log(`Analysis: BPM=${analysis.bpm}, Key=${analysis.key}`);

        // 3. Time Stretch
        const stretchedPath = this.timeStretch(vocalStem, analysis.bpm, this.config.targetBpm);

        // 4. Pitch Shift (Placeholder for key alignment)
        const finalPath = stretchedPath;

        return finalPath;
    }

    private async downloadAudio(url: string, outputDir: string): Promise<string> {
        console.log(`Downloading audio from ${url}...`);
        const outputPath = path.join(outputDir, 'downloaded_vocal.wav');

        // Use spawnSync for safer command execution with arguments
        const result = spawnSync('python3', [
            '-m', 'yt_dlp',
            '-x', '--audio-format', 'wav',
            '--output', outputPath.replace('.wav', '.%(ext)s'),
            url
        ]);

        if (result.status !== 0) {
            throw new Error(`yt-dlp failed: ${result.stderr.toString()}`);
        }

        return outputPath;
    }

    private async isolateVocals(inputPath: string, outputDir: string): Promise<string> {
        if (this.config.mode === 'local') {
            console.log("Running Demucs locally...");

            const result = spawnSync('python3', [
                '-m', 'demucs.separate',
                '--two-stems=vocals',
                '-o', outputDir,
                inputPath
            ]);

            if (result.status !== 0) {
                throw new Error(`Demucs failed: ${result.stderr.toString()}`);
            }

            const nameNoExt = path.basename(inputPath, path.extname(inputPath));
            return path.join(outputDir, 'htdemucs', nameNoExt, 'vocals.wav');
        } else {
            console.log("LALAL.AI API integration (stub)...");
            throw new Error("LALAL.AI API mode not fully implemented yet.");
        }
    }

    private async analyzeAudio(filePath: string): Promise<{ bpm: number, key: string }> {
        console.log("Analyzing audio via Python helper...");

        const pythonScript = `
import librosa
import sys
import os

filePath = sys.argv[1]
if not os.path.exists(filePath):
    sys.exit(1)

y, sr = librosa.load(filePath)
tempo, _ = librosa.beat.beat_track(y=y, sr=sr)
# Key detection stub
print(f"{float(tempo)},Cmin")
`;
        const result = spawnSync('python3', ['-c', pythonScript, filePath]);

        if (result.status !== 0) {
            throw new Error(`Analysis failed: ${result.stderr.toString()}`);
        }

        const output = result.stdout.toString().trim();
        const [bpm, key] = output.split(',');
        return { bpm: parseFloat(bpm), key };
    }

    private timeStretch(inputPath: string, originalBpm: number, targetBpm: number): string {
        const ratio = targetBpm / originalBpm;
        const outputPath = inputPath.replace(".wav", "_stretched.wav");
        console.log(`Time-stretching: ${originalBpm} -> ${targetBpm} (Ratio: ${ratio.toFixed(3)})`);

        let filter = `atempo=${ratio}`;
        if (ratio > 2.0) filter = `atempo=2.0,atempo=${ratio/2.0}`;
        if (ratio < 0.5) filter = `atempo=0.5,atempo=${ratio/0.5}`;

        const result = spawnSync('ffmpeg', [
            '-y',
            '-i', inputPath,
            '-filter:a', filter,
            outputPath
        ]);

        if (result.status !== 0) {
            throw new Error(`FFmpeg failed: ${result.stderr.toString()}`);
        }

        return outputPath;
    }
}
