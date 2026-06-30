use std::fs;
use std::path::{Path, PathBuf};
use rand::seq::SliceRandom;
use rand::{SeedableRng, rngs::StdRng};

/// Creates dataset splits based on a directory of JSON chart data files
pub struct DatasetJsonGenerator {
    pub json_dir: PathBuf,
    pub dataset_dir: Option<PathBuf>,
    pub use_abs_paths: bool,
    pub splits: Vec<f64>,
    pub split_names: Vec<String>,
    pub shuffle: bool,
    pub shuffle_seed: u64,
}

impl DatasetJsonGenerator {
    pub fn new(json_dir: PathBuf) -> Self {
        Self {
            json_dir,
            dataset_dir: None,
            use_abs_paths: true,
            splits: vec![1.0],
            split_names: vec!["".to_string()],
            shuffle: false,
            shuffle_seed: 0,
        }
    }

    pub fn generate(&self) -> Result<(), String> {
        if self.splits.len() != self.split_names.len() {
            return Err("Splits and split_names must have the same length".to_string());
        }

        let out_dir = self.dataset_dir.as_ref().unwrap_or(&self.json_dir);
        if !out_dir.exists() {
            fs::create_dir_all(out_dir).map_err(|e| format!("Failed to create out dir: {}", e))?;
        }

        let pack_name = self.json_dir.file_name()
            .and_then(|n| n.to_str())
            .unwrap_or("dataset");

        let mut sub_fps: Vec<String> = fs::read_dir(&self.json_dir)
            .map_err(|e| e.to_string())?
            .filter_map(|entry| {
                entry.ok().and_then(|e| {
                    let path = e.path();
                    if path.is_file() {
                        if self.use_abs_paths {
                            path.canonicalize().ok().and_then(|p| p.to_str().map(|s| s.to_string()))
                        } else {
                            path.file_name().and_then(|n| n.to_str().map(|s| s.to_string()))
                        }
                    } else {
                        None
                    }
                })
            })
            .collect();

        sub_fps.sort();

        if self.shuffle {
            let mut rng = StdRng::seed_from_u64(self.shuffle_seed);
            sub_fps.shuffle(&mut rng);
        }

        let total_split_sum: f64 = self.splits.iter().sum();
        let normalized_splits: Vec<f64> = if total_split_sum > 0.0 {
            self.splits.iter().map(|s| s / total_split_sum).collect()
        } else {
            vec![1.0]
        };

        let num_files = sub_fps.len();
        let mut split_ints: Vec<usize> = normalized_splits.iter()
            .map(|s| (num_files as f64 * s) as usize)
            .collect();

        // Give the remainder to the first split
        let allocated: usize = split_ints.iter().sum();
        if allocated < num_files && !split_ints.is_empty() {
            split_ints[0] += num_files - allocated;
        }

        let mut current_idx = 0;
        for (i, &count) in split_ints.iter().enumerate() {
            let split_name = &self.split_names[i];
            let chunk = &sub_fps[current_idx..(current_idx + count)];
            current_idx += count;

            let suffix = if split_name.is_empty() { String::new() } else { format!("_{}", split_name) };
            let out_name = format!("{}{}.txt", pack_name, suffix);
            let out_fp = out_dir.join(out_name);

            fs::write(&out_fp, chunk.join("\n"))
                .map_err(|e| format!("Failed to write split {}: {}", out_fp.display(), e))?;
        }

        Ok(())
    }
}
