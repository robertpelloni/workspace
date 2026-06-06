import { MidiParser } from "./analysis/midi_parser";
import { PsyGenerator } from "./sequencer/psy_generator";

async function main() {
    const args = process.argv.slice(2);
    if (args.length < 2) {
        console.error("Usage: ts-node main.ts <input_midi> <output_midi>");
        process.exit(1);
    }

    const inputPath = args[0];
    const outputPath = args[1];

    const dna = MidiParser.parse(inputPath);

    const config = args[2] ? JSON.parse(args[2]) : undefined;

    const psyMidi = PsyGenerator.generate(dna, config);
    PsyGenerator.saveMidi(psyMidi, outputPath);
    console.log("Success");
}

main().catch(err => {
    console.error(err);
    process.exit(1);
});
