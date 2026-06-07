import { MidiParser } from "./analysis/midi_parser";
import { PsyGenerator, PsyConfig, DEFAULT_PSY_CONFIG } from "./sequencer/psy_generator";
import { RenderingModule } from "./rendering/renderer";
import { AIBridge } from "./integrators/ai_bridge";
import * as fs from "fs";
import * as path from "path";

export interface PipelineOptions {
    inputMidi: string;
    outputDir: string;
    psyConfig?: PsyConfig;
    aiPrompt?: string;
    renderStems?: boolean;
}

export class PsyMonoPipeline {
    private renderer: RenderingModule;
    private ai: AIBridge;

    constructor() {
        this.renderer = new RenderingModule();
        this.ai = new AIBridge();
    }

    async run(options: PipelineOptions) {
        const { inputMidi, outputDir, psyConfig = DEFAULT_PSY_CONFIG, aiPrompt, renderStems = false } = options;

        if (!fs.existsSync(outputDir)) {
            fs.mkdirSync(outputDir, { recursive: true });
        }

        console.log(`--- [Psy-Mono Pipeline] Starting ---`);

        // 1. Analysis
        console.log(`Step 1: Extracting DNA from ${path.basename(inputMidi)}...`);
        const dna = MidiParser.parse(inputMidi);

        // 2. Algorithmic Sequencing
        console.log(`Step 2: Generating procedural 145 BPM patterns...`);
        const psyMidi = PsyGenerator.generate(dna, psyConfig);
        const finalMidiPath = path.join(outputDir, "psy_structure.mid");
        PsyGenerator.saveMidi(psyMidi, finalMidiPath);

        // 3. Optional Stem Rendering & AI Overhaul
        if (renderStems) {
            console.log(`Step 3: Rendering dry stems for Neural Texture Mapping...`);
            const stems = await this.renderer.renderStems(psyMidi, path.join(outputDir, "stems"));

            if (aiPrompt) {
                console.log(`Step 4: Orchestrating AI Sound Design Overhaul...`);
                // We typically focus the AI on the Lead Arp or the full mix
                const leadStem = stems.find(s => s.includes("Lead"));
                if (leadStem) {
                    const aiResultUrl = await this.ai.remakeWithMusicGen(leadStem, aiPrompt);
                    console.log(`AI Remake URL: ${aiResultUrl}`);
                }
            }
        } else {
            console.log(`Step 3: Rendering full structural preview...`);
            const previewWav = path.join(outputDir, "psy_preview.wav");
            this.renderer.render(finalMidiPath, previewWav);
        }

        console.log(`--- [Psy-Mono Pipeline] Finished ---`);
    }
}

// CLI Entry point
if (require.main === module) {
    const args = process.argv.slice(2);
    if (args.length < 2) {
        console.log("Usage: ts-node src/pipeline.ts <input_midi> <output_dir> [config_json]");
        process.exit(1);
    }

    const pipeline = new PsyMonoPipeline();
    const config = args[2] ? JSON.parse(args[2]) : undefined;

    pipeline.run({
        inputMidi: args[0],
        outputDir: args[1],
        psyConfig: config,
        renderStems: true,
        aiPrompt: "Modern Full-On Psytrance, 145 BPM, driving, psychedelic sound design, festival grade master"
    }).catch(console.error);
}
