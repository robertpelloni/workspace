use std::collections::{HashMap, BTreeMap};
use core::cmp::Ordering;

// A wrapper to allow f64 to be used as BTreeMap keys (unsafe comparison)
#[derive(Debug, Clone, Copy, PartialEq, PartialOrd)]
pub struct OrderedFloat(pub f64);

impl Eq for OrderedFloat {}

impl Ord for OrderedFloat {
    fn cmp(&self, other: &Self) -> Ordering {
        self.partial_cmp(other).unwrap_or(Ordering::Equal)
    }
}

pub struct HorizontalDensity {
    pub alpha: f64,
    pub window_size: f64,
}

impl HorizontalDensity {
    pub fn new(alpha: f64) -> Self {
        Self {
            alpha,
            window_size: 1.0,
        }
    }

    pub fn compute(&self, chart: &BTreeMap<OrderedFloat, String>) -> HashMap<String, f64> {
        let mut horizontal_density = HashMap::new();

        if chart.is_empty() {
            horizontal_density.insert("nps".to_string(), 0.0);
            horizontal_density.insert("length".to_string(), 0.0);
            return horizontal_density;
        }

        let mut preprocessed = BTreeMap::new();
        let mut max_length = 0.0_f64;

        for (k, v) in chart {
            let sum_notes: u32 = v.chars().filter_map(|c| c.to_digit(10)).sum();
            preprocessed.insert(*k, sum_notes as f64);
            if k.0 > max_length {
                max_length = k.0;
            }
        }

        let mut grouped: BTreeMap<i64, f64> = BTreeMap::new();
        for (k, v) in &preprocessed {
            let window_key = (k.0 / self.window_size).floor() as i64;
            *grouped.entry(window_key).or_insert(0.0) += *v;
        }

        let nps_values: Vec<f64> = grouped.values().cloned().collect();
        if nps_values.is_empty() {
            horizontal_density.insert("nps".to_string(), 0.0);
            horizontal_density.insert("length".to_string(), if max_length > 0.0 { max_length.ln() } else { 0.0 });
            return horizontal_density;
        }

        let squared_nps: Vec<f64> = nps_values.iter().map(|&x| x * x).collect();
        let weighted_avg = self.weighted_average(&squared_nps);

        horizontal_density.insert("nps".to_string(), weighted_avg.sqrt());
        horizontal_density.insert("length".to_string(), if max_length > 0.0 { max_length.ln() } else { 0.0 });

        horizontal_density
    }

    fn weighted_average(&self, values: &[f64]) -> f64 {
        if values.is_empty() {
            return 0.0;
        }

        let mut sorted_values = values.to_vec();
        sorted_values.sort_by(|a, b| a.partial_cmp(b).unwrap());

        let mut numerator = 0.0;
        let mut denominator = 0.0;

        for (i, &val) in sorted_values.iter().enumerate() {
            let weight = (i as f64).powf(self.alpha);
            numerator += weight * val;
            denominator += weight;
        }

        if denominator > 0.0 {
            numerator / denominator
        } else {
            0.0
        }
    }
}

pub struct VerticalDensity {
    pub alpha: f64,
}

impl VerticalDensity {
    pub fn new(alpha: f64) -> Self {
        Self { alpha }
    }

    pub fn compute(&self, chart: &BTreeMap<OrderedFloat, String>) -> HashMap<String, f64> {
        let mut vertical_density = HashMap::new();

        if chart.is_empty() {
            return vertical_density;
        }

        let first_val = chart.values().next().unwrap();
        let num_panels = first_val.len();

        if num_panels == 0 {
            return vertical_density;
        }

        // col_i
        for i in 0..num_panels {
            let key = format!("col_{}", i);
            let mut timestamps = Vec::new();
            for (k, v) in chart {
                if let Some(c) = v.chars().nth(i) {
                    if c == '1' {
                        timestamps.push(k.0);
                    }
                }
            }
            vertical_density.insert(key, self.process_timestamps(&timestamps));
        }

        // halfs
        if num_panels > 1 {
            let mut left_timestamps = Vec::new();
            let mut right_timestamps = Vec::new();

            let half = num_panels / 2;

            for (k, v) in chart {
                let chars: Vec<char> = v.chars().collect();
                let left_has_note = chars.iter().take(half).any(|&c| c == '1');
                let right_has_note = chars.iter().skip(half).any(|&c| c == '1');

                if left_has_note { left_timestamps.push(k.0); }
                if right_has_note { right_timestamps.push(k.0); }
            }

            vertical_density.insert("left".to_string(), self.process_timestamps(&left_timestamps));
            vertical_density.insert("right".to_string(), self.process_timestamps(&right_timestamps));
        }

        // all
        let mut all_timestamps = Vec::new();
        for (k, v) in chart {
            if v.contains('1') {
                all_timestamps.push(k.0);
            }
        }
        vertical_density.insert("all".to_string(), self.process_timestamps(&all_timestamps));

        vertical_density
    }

    fn process_timestamps(&self, timestamps: &[f64]) -> f64 {
        if timestamps.len() < 2 {
            return 0.0;
        }

        let mut timedeltas = Vec::with_capacity(timestamps.len() - 1);
        for i in 1..timestamps.len() {
            timedeltas.push(timestamps[i] - timestamps[i - 1]);
        }

        self.weighted_harmonic_average(&timedeltas)
    }

    fn weighted_harmonic_average(&self, values: &[f64]) -> f64 {
        let filtered: Vec<f64> = values.iter().copied().filter(|&x| x > 1e-6).collect();
        if filtered.is_empty() {
            return 0.0;
        }

        let mut sorted = filtered;
        sorted.sort_by(|a, b| a.partial_cmp(b).unwrap());

        let mut numerator = 0.0;
        let mut denominator = 0.0;

        for (i, &val) in sorted.iter().enumerate() {
            let weight = (i as f64).powf(self.alpha);
            numerator += weight;
            denominator += weight * (1.0 / val);
        }

        if denominator > 0.0 && numerator > 0.0 {
            numerator / denominator
        } else {
            0.0
        }
    }
}

pub struct StreamDetector {
    pub stream_threshold: f64,
}

impl StreamDetector {
    pub fn new(stream_threshold: f64) -> Self {
        Self { stream_threshold }
    }

    pub fn compute(&self, chart: &BTreeMap<OrderedFloat, String>) -> HashMap<String, f64> {
        let mut stream_features = HashMap::new();

        let timestamps: Vec<f64> = chart.keys().map(|k| k.0).collect();
        if timestamps.len() < 2 {
            stream_features.insert("stream_percentage".to_string(), 0.0);
            stream_features.insert("max_stream_length".to_string(), 0.0);
            return stream_features;
        }

        let mut stream_notes = 0;
        let mut max_stream_length = 0;
        let mut current_stream_length = 0;

        for i in 1..timestamps.len() {
            let time_diff = timestamps[i] - timestamps[i - 1];
            if time_diff <= self.stream_threshold {
                if current_stream_length == 0 {
                    current_stream_length = 2;
                } else {
                    current_stream_length += 1;
                }
            } else {
                if current_stream_length > 0 {
                    stream_notes += current_stream_length;
                }
                if current_stream_length > max_stream_length {
                    max_stream_length = current_stream_length;
                }
                current_stream_length = 0;
            }
        }

        if current_stream_length > 0 {
            stream_notes += current_stream_length;
        }
        if current_stream_length > max_stream_length {
            max_stream_length = current_stream_length;
        }

        let total_notes = timestamps.len() as f64;
        let stream_percentage = if total_notes > 0.0 {
            (stream_notes as f64 / total_notes) * 100.0
        } else {
            0.0
        };

        stream_features.insert("stream_percentage".to_string(), stream_percentage);
        stream_features.insert("max_stream_length".to_string(), max_stream_length as f64);

        stream_features
    }
}

pub struct PatternDetector {
    pub jack_threshold: f64,
}

impl PatternDetector {
    pub fn new(jack_threshold: f64) -> Self {
        Self { jack_threshold }
    }

    pub fn compute(&self, chart: &BTreeMap<OrderedFloat, String>) -> HashMap<String, f64> {
        let mut pattern_features = HashMap::new();

        let timestamps: Vec<f64> = chart.keys().map(|k| k.0).collect();
        if timestamps.len() < 2 {
            pattern_features.insert("jack_percentage".to_string(), 0.0);
            pattern_features.insert("crossover_percentage".to_string(), 0.0);
            return pattern_features;
        }

        let first_val = chart.values().next().unwrap();
        let num_panels = first_val.len();

        if num_panels == 0 {
            pattern_features.insert("jack_percentage".to_string(), 0.0);
            pattern_features.insert("crossover_percentage".to_string(), 0.0);
            return pattern_features;
        }

        let mut jacks = 0;
        let mut crossovers = 0;
        let mut last_note_com = 0.0;

        for i in 1..timestamps.len() {
            let time_diff = timestamps[i] - timestamps[i - 1];
            let note = chart.get(&OrderedFloat(timestamps[i])).unwrap();
            let prev_note = chart.get(&OrderedFloat(timestamps[i - 1])).unwrap();

            let note_chars: Vec<char> = note.chars().collect();
            let prev_note_chars: Vec<char> = prev_note.chars().collect();

            // Jack detection
            if time_diff <= self.jack_threshold {
                for j in 0..num_panels {
                    if note_chars[j] == '1' && prev_note_chars[j] == '1' {
                        jacks += 1;
                    }
                }
            }

            // Crossover detection
            let mut current_note_panels = Vec::new();
            for (j, &val) in note_chars.iter().enumerate() {
                if val == '1' {
                    current_note_panels.push(j as f64);
                }
            }

            let current_note_com = if current_note_panels.is_empty() {
                last_note_com
            } else {
                let sum: f64 = current_note_panels.iter().sum();
                sum / current_note_panels.len() as f64
            };

            let midline = (num_panels as f64 - 1.0) / 2.0;

            if (last_note_com > midline && current_note_com < midline) ||
               (last_note_com < midline && current_note_com > midline) {
                crossovers += 1;
            }

            last_note_com = current_note_com;
        }

        let total_notes = timestamps.len() as f64;
        let jack_percentage = if total_notes > 0.0 {
            (jacks as f64 / total_notes) * 100.0
        } else {
            0.0
        };
        let crossover_percentage = if total_notes > 0.0 {
            (crossovers as f64 / total_notes) * 100.0
        } else {
            0.0
        };

        pattern_features.insert("jack_percentage".to_string(), jack_percentage);
        pattern_features.insert("crossover_percentage".to_string(), crossover_percentage);

        pattern_features
    }
}
