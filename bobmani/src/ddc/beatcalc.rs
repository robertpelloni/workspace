use std::collections::BTreeMap;
use crate::ffr_diff_model::features::OrderedFloat;

const EPSILON: f64 = 1e-6;

pub struct BeatCalc {
    pub offset: f64,
    pub bpms: Vec<(f64, f64)>,
    pub stops: Vec<(f64, f64)>,
    segment_time: Vec<f64>,
    segment_beat: Vec<f64>,
    segment_bps: Vec<f64>,
    segment_spb: Vec<f64>,
}

impl BeatCalc {
    pub fn new(offset: f64, beat_bpm: Vec<(f64, f64)>, beat_stop: Vec<(f64, f64)>) -> Self {
        assert!(!beat_bpm.is_empty(), "beat_bpm cannot be empty");
        assert!((beat_bpm[0].0 - 0.0).abs() < EPSILON, "First beat marker must be 0.0");

        let mut bpms = Vec::new();
        let mut beat_last = -1.0;

        for (beat, bpm) in &beat_bpm {
            assert!(*beat >= beat_last, "Beats must be strictly increasing");
            if (*beat - beat_last).abs() < EPSILON {
                if let Some(last) = bpms.last_mut() {
                    *last = (*beat, *bpm);
                }
            } else {
                bpms.push((*beat, *bpm));
            }
            beat_last = *beat;
        }

        // Aggregate repeat stops
        let mut stops_map: BTreeMap<OrderedFloat, f64> = BTreeMap::new();
        for (beat, stop) in &beat_stop {
            assert!(*beat >= 0.0, "Stop beat must be >= 0.0");
            let key = OrderedFloat(*beat);
            *stops_map.entry(key).or_insert(0.0) += *stop;
        }

        let mut stops: Vec<(f64, f64)> = stops_map.into_iter()
            .map(|(k, v)| (k.0, v))
            .filter(|&(_, v)| v != 0.0)
            .collect();

        let mut beat_bps: Vec<(f64, f64)> = bpms.iter()
            .map(|(beat, bpm)| (*beat, bpm / 60.0))
            .collect();

        // Insert line segments for stops
        for (beat, stop) in &stops {
            // Find index using a binary search equivalent (`searchsorted` right side in python)
            let seg_idx = match beat_bps.binary_search_by(|(b, _)| {
                b.partial_cmp(beat).unwrap_or(std::cmp::Ordering::Equal)
            }) {
                Ok(idx) => idx + 1, // 'right' side
                Err(idx) => idx,
            };

            let bps = if seg_idx > 0 { beat_bps[seg_idx - 1].1 } else { beat_bps[0].1 };

            beat_bps.insert(seg_idx, (*beat + EPSILON, bps));
            beat_bps.insert(seg_idx, (*beat, EPSILON / stop));
        }

        // Create line segments for tempo changes
        let mut time_cum = -offset;
        let mut times = vec![-offset];

        let mut beat_last = beat_bps[0].0;
        let mut bps_last = beat_bps[0].1;

        for (beat, bps) in beat_bps.iter().skip(1) {
            let dbeat = beat - beat_last;
            let dtime = dbeat / bps_last;
            time_cum += dtime;
            times.push(time_cum);
            beat_last = *beat;
            bps_last = *bps;
        }

        let segment_time = times;
        let segment_beat: Vec<f64> = beat_bps.iter().map(|(b, _)| *b).collect();
        let segment_bps: Vec<f64> = beat_bps.iter().map(|(_, bps)| *bps).collect();
        let segment_spb: Vec<f64> = segment_bps.iter().map(|bps| 1.0 / bps).collect();

        Self {
            offset,
            bpms: beat_bpm,
            stops,
            segment_time,
            segment_beat,
            segment_bps,
            segment_spb,
        }
    }

    fn searchsorted(arr: &[f64], val: f64) -> usize {
        match arr.binary_search_by(|a| a.partial_cmp(&val).unwrap_or(std::cmp::Ordering::Equal)) {
            Ok(idx) => {
                let mut right = idx;
                while right < arr.len() && arr[right] <= val {
                    right += 1;
                }
                right
            }
            Err(idx) => idx,
        }
    }

    pub fn beat_to_time(&self, beat: f64) -> f64 {
        let mut seg_idx = Self::searchsorted(&self.segment_beat, beat);
        if seg_idx > 0 {
            seg_idx -= 1;
        }

        let beat_left = self.segment_beat[seg_idx];
        let time_left = self.segment_time[seg_idx];
        let spb = self.segment_spb[seg_idx];
        time_left + ((beat - beat_left) * spb)
    }

    pub fn time_to_beat(&self, time: f64) -> f64 {
        let mut seg_idx = Self::searchsorted(&self.segment_time, time);
        if seg_idx > 0 {
            seg_idx -= 1;
        }

        let time_left = self.segment_time[seg_idx];
        let beat_left = self.segment_beat[seg_idx];
        let bps = self.segment_bps[seg_idx];
        beat_left + ((time - time_left) * bps)
    }
}
