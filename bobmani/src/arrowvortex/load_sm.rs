use std::fs;
use crate::arrowvortex::simfile::{Simfile, SimFormat};
use crate::arrowvortex::chart::{Chart, Difficulty};
use crate::arrowvortex::notes::{ExpandedNote, NoteType};

/// Basic representation of ParseData from LoadSm.cpp
pub struct ParseData {
    pub is_sm5: bool,
    pub sim: Simfile,
    pub current_chart: Option<Chart>,
}

impl ParseData {
    pub fn new() -> Self {
        Self {
            is_sm5: false,
            sim: Simfile::new(),
            current_chart: None,
        }
    }
}

pub fn load_sm_file(filepath: &str) -> Result<Simfile, String> {
    let content = fs::read_to_string(filepath)
        .map_err(|e| format!("Failed to read file: {}", e))?;

    let mut data = ParseData::new();
    data.sim.format = SimFormat::Sm;

    // Naive split by '#' tags, mimicking the map[] parser in C++
    let tags: Vec<&str> = content.split('#').skip(1).collect();

    for block in tags {
        let colon_idx = match block.find(':') {
            Some(idx) => idx,
            None => continue,
        };

        let tag = block[..colon_idx].trim().to_uppercase();
        let value = block[colon_idx + 1..].trim_end_matches(';').trim();

        match tag.as_str() {
            "TITLE" => data.sim.title = value.to_string(),
            "ARTIST" => data.sim.artist = value.to_string(),
            "OFFSET" => {
                if let Ok(offset) = value.parse::<f64>() {
                    data.sim.tempo.offset = offset;
                }
            }
            "BPMS" => {
                parse_bpms(&mut data, value);
            }
            "STOPS" => {
                parse_stops(&mut data, value);
            }
            "NOTES" | "NOTES2" => {
                parse_notes(&mut data, value);
            }
            _ => {
                // Ignore unimplemented tags for the skeleton
            }
        }
    }

    Ok(data.sim)
}

use crate::arrowvortex::segments::{BpmChange, Stop};

fn parse_bpms(data: &mut ParseData, value_str: &str) {
    let pairs: Vec<&str> = value_str.split(',').collect();
    for pair in pairs {
        let kv: Vec<&str> = pair.split('=').collect();
        if kv.len() == 2 {
            if let (Ok(beat), Ok(bpm)) = (kv[0].trim().parse::<f64>(), kv[1].trim().parse::<f64>()) {
                let row = (beat * crate::arrowvortex::tempo::ROWS_PER_BEAT) as i32;
                data.sim.tempo.segments.bpm_changes.push(BpmChange { row, bpm });
            }
        }
    }
}

fn parse_stops(data: &mut ParseData, value_str: &str) {
    let pairs: Vec<&str> = value_str.split(',').collect();
    for pair in pairs {
        let kv: Vec<&str> = pair.split('=').collect();
        if kv.len() == 2 {
            if let (Ok(beat), Ok(seconds)) = (kv[0].trim().parse::<f64>(), kv[1].trim().parse::<f64>()) {
                let row = (beat * crate::arrowvortex::tempo::ROWS_PER_BEAT) as i32;
                data.sim.tempo.segments.stops.push(Stop { row, seconds });
            }
        }
    }
}

fn parse_notes(data: &mut ParseData, value_str: &str) {
    let mut chart = Chart::new();

    // Split chart info "a:b:c:d:..." into parameters.
    let mut params: Vec<&str> = value_str.split(':').map(|s| s.trim()).collect();

    if params.len() >= 6 {
        chart.difficulty = match params[1].to_uppercase().as_str() {
            "BEGINNER" => Difficulty::Beginner,
            "EASY" => Difficulty::Easy,
            "MEDIUM" => Difficulty::Medium,
            "HARD" => Difficulty::Hard,
            "CHALLENGE" => Difficulty::Challenge,
            "EDIT" => Difficulty::Edit,
            _ => Difficulty::Beginner,
        };

        chart.meter = params[2].parse().unwrap_or(1);

        let note_data = params[5];
        let measures: Vec<&str> = note_data.split(',').collect();
        let mut current_row = 0;

        for measure in measures {
            let lines: Vec<&str> = measure.lines().map(|l| l.trim()).filter(|l| !l.is_empty()).collect();
            let rows_in_measure = lines.len() as i32;

            if rows_in_measure == 0 {
                continue;
            }

            for line in lines {
                for (col, ch) in line.chars().enumerate() {
                    let mut note = ExpandedNote::new(current_row, col as i32, 0.0);
                    match ch {
                        '1' => {
                            note.note_type = NoteType::StepOrHold;
                            chart.notes.append(note);
                        }
                        '2' => {
                            // Hold head
                            note.note_type = NoteType::StepOrHold;
                            chart.notes.append(note);
                        }
                        'M' => {
                            note.is_mine = true;
                            note.note_type = NoteType::Mine;
                            chart.notes.append(note);
                        }
                        _ => {} // 0 or empty
                    }
                }
                current_row += 1;
            }
        }
    }

    data.sim.charts.push(chart);
}
