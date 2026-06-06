import * as fs from "fs";
import * as path from "path";
import { spawnSync } from "child_process";
import { Midi } from "@tonejs/midi";

export interface RenderOptions {
    soundfontPath?: string;
    sampleRate?: number;
    outputFormat?: "wav" | "flac";
}

export class RenderingModule {
    private fluidsynthBin: string;
    private defaultSoundfont: string;

    constructor() {
        this.fluidsynthBin = process.platform === "win32" ? "fluidsynth.exe" : "fluidsynth";
        // Attempt to find a default soundfont
        const commonPaths = [
            "/usr/share/sounds/sf2/FluidR3_GM.sf2",
            "/usr/share/sounds/sf2/default-GM.sf2",
            path.join(__dirname, "../../hymn_remaker/soundfonts/FluidR3_GM.sf2")
        ];
        this.defaultSoundfont = commonPaths.find(p => fs.existsSync(p)) || "";
    }

    /**
     * Renders a MIDI file to audio using FluidSynth.
     */
    render(midiPath: string, outputPath: string, options: RenderOptions = {}): boolean {
        const sf = options.soundfontPath || this.defaultSoundfont;
        const sr = options.sampleRate || 44100;

        if (!fs.existsSync(sf)) {
            console.error(`Soundfont not found: ${sf}`);
            return false;
        }

        const args = [
            "-ni",
            "-F", outputPath,
            "-r", sr.toString(),
            sf,
            midiPath
        ];

        console.log(`Running: ${this.fluidsynthBin} ${args.join(" ")}`);
        const result = spawnSync(this.fluidsynthBin, args);

        if (result.status !== 0) {
            console.error(`FluidSynth failed with status ${result.status}: ${result.stderr ? result.stderr.toString() : "No stderr"}`);
            return false;
        }

        return fs.existsSync(outputPath);
    }

    /**
     * Renders separate stems from a multi-track MIDI.
     */
    async renderStems(midi: Midi, outputDir: string, options: RenderOptions = {}): Promise<string[]> {
        if (!fs.existsSync(outputDir)) {
            fs.mkdirSync(outputDir, { recursive: true });
        }

        const stemFiles: string[] = [];

        for (const track of midi.tracks) {
            if (track.notes.length === 0) continue;

            const stemMidi = new Midi();
            stemMidi.header.name = track.name;
            const newTrack = stemMidi.addTrack();
            newTrack.name = track.name;
            track.notes.forEach(note => newTrack.addNote(note));

            const stemMidiPath = path.join(outputDir, `${track.name || "track"}.mid`);
            const stemWavPath = path.join(outputDir, `${track.name || "track"}.wav`);

            fs.writeFileSync(stemMidiPath, Buffer.from(stemMidi.toArray()));

            if (this.render(stemMidiPath, stemWavPath, options)) {
                stemFiles.push(stemWavPath);
            }

            // Clean up temporary MIDI
            fs.unlinkSync(stemMidiPath);
        }

        return stemFiles;
    }
}
