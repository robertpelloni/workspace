use crate::arrowvortex::notes::{ExpandedNote, NoteType};

/// Holds a list of ExpandedNotes
#[derive(Debug, Clone, Default)]
pub struct NoteList {
    notes: Vec<ExpandedNote>,
}

impl NoteList {
    pub fn new() -> Self {
        Self { notes: Vec::new() }
    }

    pub fn clear(&mut self) {
        self.notes.clear();
    }

    pub fn cleanup(&mut self) {
        // Remove notes with negative rows
        self.notes.retain(|note| note.row >= 0);
    }

    pub fn append(&mut self, note: ExpandedNote) {
        self.notes.push(note);
    }

    pub fn size(&self) -> usize {
        self.notes.len()
    }

    pub fn is_empty(&self) -> bool {
        self.notes.is_empty()
    }
}
