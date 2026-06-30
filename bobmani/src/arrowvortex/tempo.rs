// Row/beat conversion constants.
pub const ROWS_PER_BEAT: f64 = 48.0;
pub const BEATS_PER_ROW: f64 = 1.0 / 48.0;

// Converts a BPM value to seconds per row.
pub fn sec_per_row(beats_per_min: f64) -> f64 {
    60.0 / (beats_per_min * ROWS_PER_BEAT)
}

// Converts seconds per row to a BPM value.
pub fn beats_per_min(sec_per_row: f64) -> f64 {
    60.0 / (sec_per_row * ROWS_PER_BEAT)
}

/// Different ways to display the song BPM.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum DisplayBpmType {
    Actual = 0,
    Random = 1,
    Custom = 2,
}

/// Unit used for attack timing.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum AttackUnit {
    Length = 0,
    End = 1,
}

/// Represents an attack (SM5).
#[derive(Debug, Clone)]
pub struct Attack {
    pub time: f64,
    pub duration: f64,
    pub mods: String,
    pub unit: AttackUnit,
}

/// Represents a BPM range.
#[derive(Debug, Clone, Copy)]
pub struct BpmRange {
    pub min: f64,
    pub max: f64,
}

/// Represents a generic tag/value property.
#[derive(Debug, Clone)]
pub struct Property {
    pub tag: String,
    pub val: String,
}

/// Holds data that determines the tempo of a song or chart (and a few other things).
#[derive(Debug, Clone)]
pub struct Tempo {
    pub offset: f64,
    pub attacks: Vec<Attack>,
    pub keysounds: Vec<String>,
    pub misc: Vec<Property>,

    pub display_bpm_type: DisplayBpmType,
    pub display_bpm_range: BpmRange,

    pub segments: crate::arrowvortex::segments::SegmentGroup,
}

impl Tempo {
    pub fn new() -> Self {
        Self {
            offset: 0.0,
            attacks: Vec::new(),
            keysounds: Vec::new(),
            misc: Vec::new(),
            display_bpm_type: DisplayBpmType::Actual,
            display_bpm_range: BpmRange { min: 0.0, max: 0.0 },
            segments: crate::arrowvortex::segments::SegmentGroup::new(),
        }
    }

    /// Copies the data of another tempo.
    pub fn copy_from(&mut self, other: &Tempo) {
        self.offset = other.offset;
        self.attacks = other.attacks.clone();
        self.keysounds = other.keysounds.clone();
        self.misc = other.misc.clone();

        self.display_bpm_type = other.display_bpm_type;
        self.display_bpm_range = other.display_bpm_range;
        self.segments = other.segments.clone();
    }

    /// Returns true if the tempo contains one or more segments, false otherwise.
    pub fn has_segments(&self) -> bool {
        !self.segments.is_empty()
    }
}

impl Default for Tempo {
    fn default() -> Self {
        Self::new()
    }
}
