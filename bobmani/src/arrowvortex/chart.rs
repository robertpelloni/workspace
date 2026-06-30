use crate::arrowvortex::notes::{ExpandedNote, NoteType};
use crate::arrowvortex::note_list::NoteList;
use crate::arrowvortex::tempo::Tempo;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Difficulty {
    Beginner = 0,
    Easy = 1,
    Medium = 2,
    Hard = 3,
    Challenge = 4,
    Edit = 5,
}

impl Difficulty {
    pub fn name(&self) -> &'static str {
        match self {
            Difficulty::Beginner => "Beginner",
            Difficulty::Easy => "Easy",
            Difficulty::Medium => "Medium",
            Difficulty::Hard => "Hard",
            Difficulty::Challenge => "Challenge",
            Difficulty::Edit => "Edit",
        }
    }
}

pub struct Chart {
    pub artist: String,
    pub difficulty: Difficulty,
    pub radar: Vec<f64>,
    pub meter: i32,
    pub notes: NoteList,
    pub has_tempo: bool,
    pub tempo: Option<Tempo>,
}

impl Chart {
    pub fn new() -> Self {
        Self {
            artist: String::new(),
            difficulty: Difficulty::Beginner,
            radar: Vec::new(),
            meter: 1,
            notes: NoteList::new(),
            has_tempo: false,
            tempo: None,
        }
    }

    pub fn description(&self) -> String {
        format!("{} {}", self.difficulty.name(), self.meter)
    }

    pub fn step_count(&self) -> usize {
        // Assume step_count is size() for now until we expand note_list iteration
        self.notes.size()
    }
}

impl Default for Chart {
    fn default() -> Self {
        Self::new()
    }
}
