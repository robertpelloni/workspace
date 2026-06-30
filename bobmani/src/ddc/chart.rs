use std::collections::{HashMap, HashSet};
use crate::ddc::beatcalc::BeatCalc;

pub struct SongMetadata {
    pub offset: f64,
    pub bpms: Vec<(f64, f64)>,
    pub stops: Vec<(f64, f64)>,
}

#[derive(Clone)]
pub struct ChartMetadata {
    pub coarse_difficulty: String,
    pub foot_difficulty: u32,
    pub chart_type: String,
    pub freetext: String,
}

#[derive(Clone)]
pub struct Annotation {
    pub pulse: (i32, i32, i32), // (wrap, num, den) roughly matching DDC
    pub beat: f64,
    pub time: f64,
    pub label: String,
}

pub struct Chart {
    pub song_metadata: SongMetadata,
    pub metadata: ChartMetadata,
    pub annotations: Vec<Annotation>,
    pub beat_calc: BeatCalc,
    pub first_annotation_time: f64,
    pub last_annotation_time: f64,
    pub time_annotated: f64,
    pub annotations_per_second: f64,
}

impl Chart {
    pub fn new(
        song_metadata: SongMetadata,
        metadata: ChartMetadata,
        annotations: Vec<Annotation>,
    ) -> Self {
        assert!(annotations.len() >= 2, "Need at least 2 annotations");

        let first_annotation_time = annotations[0].time;
        let last_annotation_time = annotations.last().unwrap().time;

        assert!(last_annotation_time - first_annotation_time > 0.0);

        let time_annotated = last_annotation_time - first_annotation_time;
        let annotations_per_second = annotations.len() as f64 / time_annotated;

        let beat_calc = BeatCalc::new(
            song_metadata.offset,
            song_metadata.bpms.clone(),
            song_metadata.stops.clone(),
        );

        Self {
            song_metadata,
            metadata,
            annotations,
            beat_calc,
            first_annotation_time,
            last_annotation_time,
            time_annotated,
            annotations_per_second,
        }
    }
}

pub struct OnsetChart {
    pub base: Chart,
    pub nframes: usize,
    pub dt: f64,
    pub onsets: HashSet<usize>,
    pub first_onset: usize,
    pub last_onset: usize,
    pub nframes_annotated: usize,
    pub blanks: HashSet<usize>,
}

impl OnsetChart {
    pub fn new(
        song_metadata: SongMetadata,
        song_features_frames: usize, // length of audio frames
        frame_rate: f64,
        metadata: ChartMetadata,
        annotations: Vec<Annotation>,
    ) -> Self {
        let base = Chart::new(song_metadata, metadata, annotations);

        let nframes = song_features_frames;
        let dt = 1.0 / frame_rate;

        let mut onsets = HashSet::new();
        for ann in &base.annotations {
            let frame = (ann.time / dt).round() as isize;
            if frame >= 0 && (frame as usize) < nframes {
                onsets.insert(frame as usize);
            }
        }

        let first_onset = *onsets.iter().min().unwrap_or(&0);
        let last_onset = *onsets.iter().max().unwrap_or(&0);
        let nframes_annotated = if onsets.is_empty() { 0 } else { (last_onset - first_onset) + 1 };

        let mut blanks = HashSet::new();
        for i in 0..nframes {
            if !onsets.contains(&i) {
                blanks.insert(i);
            }
        }

        Self {
            base,
            nframes,
            dt,
            onsets,
            first_onset,
            last_onset,
            nframes_annotated,
            blanks,
        }
    }
}

pub struct SymbolicChart {
    pub base: Chart,
    pub sequence: Vec<String>,
    pub seq_beat_phase: Vec<f64>,
    pub seq_beat_diff: Vec<f64>,
    pub seq_beat_abs: Vec<f64>,
    pub seq_time_diff: Vec<f64>,
    pub seq_time_abs: Vec<f64>,
    pub seq_prog_diff: Vec<f64>,
    pub seq_prog_abs: Vec<f64>,
    pub seq_meas_phase: Vec<f64>,
    pub seq_meas_wraps: Vec<i32>,
    pub seq_beat_wraps: Vec<i32>,
    pub seq_frame_idxs: Vec<usize>,
}

impl SymbolicChart {
    pub fn new(
        song_metadata: SongMetadata,
        frame_rate: f64,
        metadata: ChartMetadata,
        annotations: Vec<Annotation>,
        pre: usize,
    ) -> Self {
        let mut base = Chart::new(song_metadata, metadata, annotations);
        let dt = 1.0 / frame_rate;

        // Prepend logic
        let mut prepend_annotations = Vec::new();
        for i in (0..pre).rev() {
            let mut ann = base.annotations[0].clone();
            ann.label = format!("<-{}>", i + 1);
            prepend_annotations.push(ann);
        }

        let mut all_annotations = prepend_annotations;
        all_annotations.append(&mut base.annotations.clone());
        base.annotations = all_annotations.clone();

        let mut sequence = Vec::new();
        let mut seq_beat_phase = Vec::new();
        let mut seq_beat_diff = Vec::new();
        let mut seq_beat_abs = Vec::new();
        let mut seq_time_diff = Vec::new();
        let mut seq_time_abs = Vec::new();
        let mut seq_prog_diff = Vec::new();
        let mut seq_prog_abs = Vec::new();
        let mut seq_meas_phase = Vec::new();
        let mut seq_meas_wraps = Vec::new();
        let mut seq_beat_wraps = Vec::new();
        let mut seq_frame_idxs = Vec::new();

        let mut prog_last = 0.0;

        for i in 0..(all_annotations.len().saturating_sub(1)) {
            let last = &all_annotations[i];
            let current = &all_annotations[i + 1];

            let prog = (current.time - base.first_annotation_time) / base.time_annotated;

            sequence.push(last.label.clone());
            seq_beat_phase.push(current.beat - current.beat.floor());
            seq_beat_diff.push(current.beat - last.beat);
            seq_beat_abs.push(current.beat);
            seq_time_diff.push(current.time - last.time);
            seq_time_abs.push(current.time);
            seq_prog_abs.push(prog);
            seq_prog_diff.push(prog - prog_last);

            let phase = if current.pulse.1 != 0 { current.pulse.2 as f64 / current.pulse.1 as f64 } else { 0.0 };
            seq_meas_phase.push(phase);
            seq_meas_wraps.push(current.pulse.0 - last.pulse.0);
            seq_beat_wraps.push(current.beat as i32 - last.beat as i32);
            seq_frame_idxs.push((current.time / dt).round() as usize);

            prog_last = prog;
        }

        if let Some(last) = all_annotations.last() {
            sequence.push(last.label.clone());
        }

        Self {
            base,
            sequence,
            seq_beat_phase,
            seq_beat_diff,
            seq_beat_abs,
            seq_time_diff,
            seq_time_abs,
            seq_prog_diff,
            seq_prog_abs,
            seq_meas_phase,
            seq_meas_wraps,
            seq_beat_wraps,
            seq_frame_idxs,
        }
    }
}
