use crate::arrowvortex::notes::ExpandedNote;

/// Contains lists of notes for one or more columns
#[derive(Debug, Clone, Default)]
pub struct NoteSet {
    columns: Vec<Vec<ExpandedNote>>,
}

impl NoteSet {
    pub fn new(num_columns: usize) -> Self {
        Self {
            columns: vec![Vec::new(); num_columns],
        }
    }

    pub fn clear(&mut self) {
        for col in &mut self.columns {
            col.clear();
        }
    }

    pub fn remove_marked_notes(&mut self) {
        // Removes notes with negative rows.
        for col in &mut self.columns {
            col.retain(|note| note.row >= 0);
        }
    }

    pub fn num_notes(&self) -> usize {
        self.columns.iter().map(|col| col.len()).sum()
    }

    pub fn num_columns(&self) -> usize {
        self.columns.len()
    }

    pub fn end_row(&self) -> i32 {
        self.columns
            .iter()
            .flat_map(|col| col.iter().map(|note| note.endrow))
            .max()
            .unwrap_or(0)
    }
}
