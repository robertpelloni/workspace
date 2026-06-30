use crate::arrowvortex::tempo::Tempo;

pub struct Event {
    pub row: i32,
    pub start_time: f64,
    pub hit_time: f64,
    pub end_time: f64,
    pub spr: f64,
}

impl Event {
    pub fn new(row: i32, start_time: f64, hit_time: f64, end_time: f64, spr: f64) -> Self {
        Self {
            row,
            start_time,
            hit_time,
            end_time,
            spr,
        }
    }
}

pub struct Signature {
    pub row: i32,
    pub measure: i32,
    pub rows_per_measure: i32,
}

impl Signature {
    pub fn new(row: i32, measure: i32, rows_per_measure: i32) -> Self {
        Self {
            row,
            measure,
            rows_per_measure,
        }
    }
}

pub struct TimingData {
    pub events: Vec<Event>,
    pub signatures: Vec<Signature>,
}

impl TimingData {
    pub fn new() -> Self {
        Self {
            events: Vec::new(),
            signatures: Vec::new(),
        }
    }

    pub fn update(&mut self, offset: f64, tempo: &Tempo) {
        // Placeholder for C++ update logic
        self.events.clear();
        self.signatures.clear();

        // Push initial event to prevent empty bounds later
        self.events.push(Event::new(0, offset, offset, offset, 1.0));
    }

    pub fn time_to_row(&self, time: f64) -> f64 {
        // Basic placeholder
        if self.events.is_empty() { return 0.0; }
        let ev = &self.events[0];
        (time - ev.start_time) / ev.spr
    }

    pub fn row_to_time(&self, row: f64) -> f64 {
        // Basic placeholder
        if self.events.is_empty() { return 0.0; }
        let ev = &self.events[0];
        ev.start_time + row * ev.spr
    }
}

impl Default for TimingData {
    fn default() -> Self {
        Self::new()
    }
}
