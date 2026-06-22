use std::collections::BTreeMap;
use std::fs;
use regex::Regex;
use crate::ffr_diff_model::features::OrderedFloat;

#[derive(Debug)]
pub struct PreprocessedChart {
    pub name: String,
    pub mode: String,
    pub difficulty: String,
    pub meter: f64,
    pub chart: BTreeMap<OrderedFloat, String>,
}

pub struct SMChartPreprocessor {
    pub decimals: u32,
}

impl SMChartPreprocessor {
    pub fn new(decimals: u32) -> Self {
        Self { decimals }
    }

    pub fn preprocess(&self, sm_file_path: &str) -> Vec<PreprocessedChart> {
        let mut preprocessed_charts = Vec::new();

        let contents = match fs::read_to_string(sm_file_path) {
            Ok(c) => c,
            Err(e) => {
                eprintln!("Failed to read file {}: {}", sm_file_path, e);
                return preprocessed_charts;
            }
        };

        // Extract Title
        let title_re = Regex::new(r"#TITLE:(.*?);").unwrap();
        let name = title_re
            .captures(&contents)
            .map(|cap| cap[1].to_string())
            .unwrap_or_else(|| "Unknown".to_string());

        // Extract BPM (only handling the initial basic BPM for this stub)
        let bpm_re = Regex::new(r"#BPMS:.*?0=([0-9.]+).*?;").unwrap();
        let base_bpm: f64 = bpm_re
            .captures(&contents)
            .and_then(|cap| cap[1].parse().ok())
            .unwrap_or(120.0);

        // A beat in stepmania is a quarter note.
        let seconds_per_beat = 60.0 / base_bpm;

        // Split into chunks by `#NOTES:`
        let notes_blocks: Vec<&str> = contents.split("#NOTES:").skip(1).collect();

        for block in notes_blocks {
            let mut chart_dict = BTreeMap::new();

            // The block is split into meta lines and then the actual notes
            let mut parts: Vec<&str> = block.split(':').map(|s| s.trim()).collect();
            if parts.len() < 6 {
                continue;
            }

            let mode = parts[0].to_string();
            let difficulty = parts[1].to_string();
            let meter: f64 = parts[2].parse().unwrap_or(0.0);

            let note_data = parts[5].trim_end_matches(';').trim();

            let mut current_beat = 0.0;

            let measures: Vec<&str> = note_data.split(',').collect();
            for measure in measures {
                let lines: Vec<&str> = measure.lines().map(|l| l.trim()).filter(|l| !l.is_empty()).collect();
                let rows_in_measure = lines.len();
                if rows_in_measure == 0 {
                    continue;
                }

                // 4 beats per measure in StepMania default (4/4 time)
                let beats_per_row = 4.0 / (rows_in_measure as f64);

                for line in lines {
                    if line.contains('1') || line.contains('2') || line.contains('4') {
                        let time = current_beat * seconds_per_beat;
                        // Convert stepmania notes (1=tap, 2=hold head, etc) into binary layout for the features
                        let binary_line: String = line.chars()
                            .map(|c| if c == '1' || c == '2' || c == '4' { '1' } else { '0' })
                            .collect();

                        // Round to requested decimals
                        let factor = 10_f64.powi(self.decimals as i32);
                        let rounded_time = (time * factor).round() / factor;

                        chart_dict.insert(OrderedFloat(rounded_time), binary_line);
                    }
                    current_beat += beats_per_row;
                }
            }

            preprocessed_charts.push(PreprocessedChart {
                name: name.clone(),
                mode,
                difficulty,
                meter,
                chart: chart_dict,
            });
        }

        preprocessed_charts
    }
}
