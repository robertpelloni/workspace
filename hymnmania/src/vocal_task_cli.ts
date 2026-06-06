import { VocalProcessor } from './integrators/vocal_processor';

async function main() {
    const args = process.argv.slice(2);
    if (args.length < 3) {
        console.error("Usage: ts-node vocal_task_cli.ts <input_path_or_url> <output_dir> <target_bpm>");
        process.exit(1);
    }

    const input = args[0];
    const outputDir = args[1];
    const targetBpm = parseFloat(args[2]);

    const vp = new VocalProcessor({ mode: 'local', targetBpm });
    try {
        const result = await vp.process(input, outputDir);
        console.log("RESULT_PATH:" + result);
    } catch (err) {
        console.error("Vocal processing failed:", err);
        process.exit(1);
    }
}

main();
