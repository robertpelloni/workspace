import { Midi } from "@tonejs/midi";
import * as fs from "fs";

export interface HymnDNA {
    title: string;
    bpm: number;
    key: string;
    melody: {
        time: number;
        duration: number;
        note: number;
        velocity: number;
    }[];
    harmony: {
        time: number;
        duration: number;
        note: number;
        velocity: number;
    }[];
}

export class MidiParser {
    static parse(filePath: string): HymnDNA {
        const midiData = fs.readFileSync(filePath);
        const midi = new Midi(midiData);

        const dna: HymnDNA = {
            title: midi.name || "Untitled",
            bpm: midi.header.tempos[0]?.bpm || 120,
            key: midi.header.keySignatures[0]?.key || "C",
            melody: [],
            harmony: []
        };

        const tracksWithNotes = midi.tracks.filter(t => t.notes.length > 0);

        if (tracksWithNotes.length > 0) {
            const sortedTracks = [...tracksWithNotes].sort((a, b) => {
                const avgA = a.notes.reduce((sum, n) => sum + n.midi, 0) / a.notes.length;
                const avgB = b.notes.reduce((sum, n) => sum + n.midi, 0) / b.notes.length;
                return avgB - avgA;
            });

            const melodyTrack = sortedTracks[0];
            dna.melody = melodyTrack.notes.map(n => ({
                time: n.time,
                duration: n.duration,
                note: n.midi,
                velocity: n.velocity
            }));

            const harmonyTrack = sortedTracks[sortedTracks.length - 1];
            dna.harmony = harmonyTrack.notes.map(n => ({
                time: n.time,
                duration: n.duration,
                note: n.midi,
                velocity: n.velocity
            }));
        }

        return dna;
    }
}
