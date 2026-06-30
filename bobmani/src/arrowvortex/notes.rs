#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum NoteType {
    StepOrHold = 0,
    Mine = 1,
    Roll = 2,
    Lift = 3,
    Fake = 4,
}

impl NoteType {
    pub fn from_u8(value: u8) -> Option<Self> {
        match value {
            0 => Some(NoteType::StepOrHold),
            1 => Some(NoteType::Mine),
            2 => Some(NoteType::Roll),
            3 => Some(NoteType::Lift),
            4 => Some(NoteType::Fake),
            _ => None,
        }
    }
}

/// Expanded representation of a note, including editing data.
#[derive(Debug, Clone, PartialEq)]
pub struct ExpandedNote {
    /// Row index of the note.
    pub row: i32,

    /// Column index of the note.
    pub col: i32,

    /// Equal to `row` for steps, larger than `row` for holds.
    pub endrow: i32,

    /// Time of the row.
    pub time: f64,

    /// Time of the end row.
    pub endtime: f64,

    // Bitfields in C++ translate to booleans/small ints in Rust
    /// Indicates a mine
    pub is_mine: bool,

    /// Indicates a roll
    pub is_roll: bool,

    /// Indicates a warped note
    pub is_warped: bool,

    /// Indicates a faked note
    pub is_fake: bool,

    /// Indicates selected status
    pub is_selected: bool,

    /// One of the values in NoteType, indicates what kind of note it is.
    pub note_type: NoteType,

    /// Indicates which player the note belongs to in routine modes.
    pub player: u32,

    /// Indicates the quantization of the note, if it is nonstandard.
    pub quant: u8,
}

impl ExpandedNote {
    pub fn new(row: i32, col: i32, time: f64) -> Self {
        Self {
            row,
            col,
            endrow: row,
            time,
            endtime: time,
            is_mine: false,
            is_roll: false,
            is_warped: false,
            is_fake: false,
            is_selected: false,
            note_type: NoteType::StepOrHold,
            player: 0,
            quant: 0,
        }
    }
}