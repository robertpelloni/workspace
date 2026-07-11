import { Midi } from "@tonejs/midi";
import { HymnDNA } from "../analysis/midi_parser";
import * as fs from "fs";

export interface PsyConfig {
    targetBpm: number;
    euclideanDensity: number; // 1 to 8
    octaveJumpBarFrequency: number; // 0 (none) to 4 (every bar)
    bassVelocity: number;
    leadVelocity: number;
    kickVelocity: number;
    gallopVariant: "classic" | "triplet" | "rolling";
}

export const DEFAULT_PSY_CONFIG: PsyConfig = {
    targetBpm: 145,
    euclideanDensity: 5,
    octaveJumpBarFrequency: 2,
    bassVelocity: 0.7,
    leadVelocity: 0.8,
    kickVelocity: 0.9,
    gallopVariant: "classic"
};

export class PsyGenerator {
    static generate(dna: HymnDNA, config: PsyConfig = DEFAULT_PSY_CONFIG): Midi {
        const { targetBpm, euclideanDensity, octaveJumpBarFrequency, bassVelocity, leadVelocity, kickVelocity, gallopVariant } = config;

        const midi = new Midi();
        midi.header.setTempo(targetBpm);
        midi.header.name = dna.title + " (Psytrance Remix)";

        const kickTrack = midi.addTrack();
        kickTrack.name = "Kick";
        kickTrack.channel = 0;

        const bassTrack = midi.addTrack();
        bassTrack.name = "Bass";
        bassTrack.channel = 1;

        const leadTrack = midi.addTrack();
        leadTrack.name = "Lead Arp";
        leadTrack.channel = 2;

        const duration = dna.melody.length > 0 ? dna.melody[dna.melody.length - 1].time + 2 : 60;

        // Generate Kick
        for (let t = 0; t < duration; t += 60 / targetBpm) {
            kickTrack.addNote({
                midi: 36,
                time: t,
                duration: 0.1,
                velocity: kickVelocity
            });
        }

        const sixteenth = 60 / targetBpm / 4;

        // Generate Bass
        for (let i = 0; i < duration / sixteenth; i++) {
            const time = i * sixteenth;
            const barIndex = Math.floor(i / 16);
            const slotInBeat = i % 4; // 0, 1, 2, 3

            let shouldPlayBass = false;
            if (gallopVariant === "classic") {
                shouldPlayBass = slotInBeat !== 0; // K-B-B-B
            } else if (gallopVariant === "triplet") {
                shouldPlayBass = slotInBeat === 2 || slotInBeat === 3; // K-X-B-B
            } else if (gallopVariant === "rolling") {
                shouldPlayBass = slotInBeat === 1 || slotInBeat === 3; // K-B-X-B
            }

            if (shouldPlayBass) {
                const activeHarmony = dna.harmony.find(h => h.time <= dna.melody[0]?.time + time * (dna.bpm / targetBpm)) || dna.harmony[0];
                let rootNote = activeHarmony ? (activeHarmony.note % 12) + 36 : 36;

                // Octave jumps
                if (slotInBeat === 3 && octaveJumpBarFrequency > 0) {
                    if (barIndex % (5 - octaveJumpBarFrequency) === 0) {
                        rootNote += 12;
                    }
                }

                bassTrack.addNote({
                    midi: rootNote,
                    time: time,
                    duration: sixteenth * 0.8,
                    velocity: bassVelocity
                });
            }
        }

        // Euclidean Arp Generation
        const getEuclideanPattern = (pulses: number, steps: number) => {
            let pattern = new Array(steps).fill(0);
            let count = 0;
            for (let i = 0; i < steps; i++) {
                count += pulses;
                if (count >= steps) {
                    pattern[i] = 1;
                    count -= steps;
                }
            }
            return pattern;
        };

        const euclideanPattern = getEuclideanPattern(euclideanDensity, 16);

        for (let i = 0; i < duration / sixteenth; i++) {
            const time = i * sixteenth;
            if (euclideanPattern[i % euclideanPattern.length] === 1) {
                const scaledTime = time * (dna.bpm / targetBpm);
                const activeMelody = dna.melody.find(m => m.time <= scaledTime && m.time + m.duration >= scaledTime) || dna.melody.find(m => m.time > scaledTime);

                if (activeMelody) {
                    leadTrack.addNote({
                        midi: activeMelody.note,
                        time: time,
                        duration: sixteenth * 0.5,
                        velocity: leadVelocity
                    });
                }
            }
        }

        return midi;
    }

    static saveMidi(midi: Midi, outputPath: string) {
        fs.writeFileSync(outputPath, Buffer.from(midi.toArray()));
    }
}
