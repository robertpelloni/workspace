#![no_main]
sp1_zkvm::entrypoint!(main);

use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize)]
struct GameStats {
    score: u32,
    perfects: u32,
    greats: u32,
    misses: u32,
}

pub fn main() {
    let stats: GameStats = sp1_zkvm::io::read();

    let calculated_score = stats.perfects * 100 + stats.greats * 50;

    if stats.score != calculated_score {
        panic!("Score mismatch! Claimed: {}, Calculated: {}", stats.score, calculated_score);
    }

    if stats.score > 1_000_000 {
        panic!("Score exceeds maximum possible value");
    }

    sp1_zkvm::io::commit(&stats.score);
    sp1_zkvm::io::commit(&true);
}
