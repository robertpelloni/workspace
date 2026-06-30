use std::fs;
use std::path::{Path, PathBuf};
use rand::seq::SliceRandom;
use rand::rngs::StdRng; use rand::SeedableRng;

pub struct DatasetSplitter {
    pub train_split: f64,
    pub valid_split: f64,
}

impl DatasetSplitter {
    pub fn new(train_split: f64, valid_split: f64) -> Self {
        Self {
            train_split,
            valid_split,
        }
    }

    pub fn create_dataset_splits(&self, data_dir: &Path, output_dir: &Path) -> Result<(), String> {
        if !output_dir.exists() {
            fs::create_dir_all(output_dir)
                .map_err(|e| format!("Failed to create output dir: {}", e))?;
        }

        let mut all_files: Vec<PathBuf> = fs::read_dir(data_dir)
            .map_err(|e| format!("Failed to read data dir: {}", e))?
            .filter_map(|entry| {
                entry.ok().and_then(|e| {
                    let path = e.path();
                    if path.is_file() && path.extension().and_then(|s| s.to_str()) == Some("json") {
                        Some(path)
                    } else {
                        None
                    }
                })
            })
            .collect();

        // Sort to ensure deterministic behavior before shuffle if seeded
        all_files.sort();

        let mut rng = StdRng::seed_from_u64(0);
        all_files.shuffle(&mut rng);

        let total_files = all_files.len();
        println!("Found {} JSON files in {}", total_files, data_dir.display());

        let train_end = (total_files as f64 * self.train_split) as usize;
        let valid_end = (total_files as f64 * (self.train_split + self.valid_split)) as usize;

        let train_files = &all_files[..train_end];
        let valid_files = &all_files[train_end..valid_end];
        let test_files = &all_files[valid_end..];

        let dataset_name = data_dir.file_name()
            .and_then(|n| n.to_str())
            .unwrap_or("dataset");

        let train_out = output_dir.join(format!("{}_train.txt", dataset_name));
        let valid_out = output_dir.join(format!("{}_valid.txt", dataset_name));
        let test_out = output_dir.join(format!("{}_test.txt", dataset_name));

        self.write_split_file(&train_out, train_files)?;
        self.write_split_file(&valid_out, valid_files)?;
        self.write_split_file(&test_out, test_files)?;

        println!("Created splits in {}:", output_dir.display());
        println!("  Train: {} ({})", train_files.len(), train_out.display());
        println!("  Valid: {} ({})", valid_files.len(), valid_out.display());
        println!("  Test:  {}  ({})", test_files.len(), test_out.display());

        Ok(())
    }

    fn write_split_file(&self, out_path: &Path, files: &[PathBuf]) -> Result<(), String> {
        let lines: Vec<String> = files.iter()
            .filter_map(|p| p.canonicalize().ok().and_then(|abs| abs.to_str().map(|s| s.to_string())))
            .collect();
        fs::write(out_path, lines.join("\n"))
            .map_err(|e| format!("Failed to write split file {}: {}", out_path.display(), e))
    }
}
