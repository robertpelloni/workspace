mod ffr_diff_model;

fn main() {
    println!("Universal Rhythm Engine (Rust Monolith)");
    let predictor = ffr_diff_model::predictor::DifficultyPredictor::new();
    println!("Difficulty Predictor initialized. Parsing test simfile...");

    let results = predictor.predict("ffr-difficulty-model/test.sm");

    for (i, result) in results.iter().enumerate() {
        println!("Chart {} Extracted Features:", i + 1);
        for (feature, value) in result {
            println!("  {}: {:.4}", feature, value);
        }
    }
}
