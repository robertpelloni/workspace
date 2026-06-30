// Base segment representations corresponding to AV::Segment types

#[derive(Debug, Clone, PartialEq)]
pub struct BpmChange {
    pub row: i32,
    pub bpm: f64,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Stop {
    pub row: i32,
    pub seconds: f64,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Delay {
    pub row: i32,
    pub seconds: f64,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Warp {
    pub row: i32,
    pub num_rows: i32,
}

#[derive(Debug, Clone, PartialEq)]
pub struct TimeSignature {
    pub row: i32,
    pub rows_per_measure: i32,
    pub beat_note: i32,
}

#[derive(Debug, Clone, PartialEq)]
pub struct TickCount {
    pub row: i32,
    pub ticks: i32,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Combo {
    pub row: i32,
    pub hit_combo: i32,
    pub miss_combo: i32,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Speed {
    pub row: i32,
    pub ratio: f64,
    pub delay: f64,
    pub unit: i32,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Scroll {
    pub row: i32,
    pub ratio: f64,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Fake {
    pub row: i32,
    pub num_rows: i32,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Label {
    pub row: i32,
    pub str_label: String,
}

/// Represents the AV::SegmentGroup which holds typed arrays of segments
#[derive(Debug, Clone)]
pub struct SegmentGroup {
    pub bpm_changes: Vec<BpmChange>,
    pub stops: Vec<Stop>,
    pub delays: Vec<Delay>,
    pub warps: Vec<Warp>,
    pub time_signatures: Vec<TimeSignature>,
    pub tick_counts: Vec<TickCount>,
    pub combos: Vec<Combo>,
    pub speeds: Vec<Speed>,
    pub scrolls: Vec<Scroll>,
    pub fakes: Vec<Fake>,
    pub labels: Vec<Label>,
}

impl SegmentGroup {
    pub fn new() -> Self {
        Self {
            bpm_changes: Vec::new(),
            stops: Vec::new(),
            delays: Vec::new(),
            warps: Vec::new(),
            time_signatures: Vec::new(),
            tick_counts: Vec::new(),
            combos: Vec::new(),
            speeds: Vec::new(),
            scrolls: Vec::new(),
            fakes: Vec::new(),
            labels: Vec::new(),
        }
    }

    pub fn is_empty(&self) -> bool {
        self.bpm_changes.is_empty()
            && self.stops.is_empty()
            && self.delays.is_empty()
            && self.warps.is_empty()
            && self.time_signatures.is_empty()
            && self.tick_counts.is_empty()
            && self.combos.is_empty()
            && self.speeds.is_empty()
            && self.scrolls.is_empty()
            && self.fakes.is_empty()
            && self.labels.is_empty()
    }
}

impl Default for SegmentGroup {
    fn default() -> Self {
        Self::new()
    }
}
