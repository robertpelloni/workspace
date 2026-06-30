use crate::arrowvortex::chart::Chart;
use crate::arrowvortex::tempo::Tempo;

/// Formats from which the simfile can be loaded/saved.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum SimFormat {
    None = 0,
    Sm = 1,
    Ssc = 2,
    Osu = 3,
    Osz = 4,
    Dwi = 5,
}

impl SimFormat {
    pub fn abbreviation(&self) -> &'static str {
        match self {
            SimFormat::None => "None",
            SimFormat::Sm => "SM",
            SimFormat::Ssc => "SSC",
            SimFormat::Osu => "OSU",
            SimFormat::Osz => "OSZ",
            SimFormat::Dwi => "DWI",
        }
    }
}

/// Hold data for a foreground/background change.
#[derive(Debug, Clone)]
pub struct BgChange {
    pub effect: String,
    pub file: String,
    pub file2: String,
    pub color: String,
    pub color2: String,
    pub transition: String,
    pub start_beat: f64,
    pub rate: f64,
}

/// Holds the simfile metadata.
pub struct Simfile {
    pub charts: Vec<Chart>,
    pub tempo: Tempo,

    pub dir: String,
    pub file: String,
    pub format: SimFormat,

    pub title: String,
    pub title_tr: String,
    pub subtitle: String,
    pub subtitle_tr: String,
    pub artist: String,
    pub artist_tr: String,
    pub genre: String,
    pub credit: String,

    pub music: String,
    pub banner: String,
    pub background: String,
    pub cd_title: String,
    pub lyrics_path: String,

    pub fg_changes: Vec<BgChange>,
    // C++ has Vector<BgChange> bgChanges[2];
    pub bg_changes: [Vec<BgChange>; 2],

    pub preview_start: f64,
    pub preview_length: f64,

    pub is_selectable: bool,
}

impl Simfile {
    pub fn new() -> Self {
        Self {
            charts: Vec::new(),
            tempo: Tempo::new(),
            dir: String::new(),
            file: String::new(),
            format: SimFormat::None,
            title: String::new(),
            title_tr: String::new(),
            subtitle: String::new(),
            subtitle_tr: String::new(),
            artist: String::new(),
            artist_tr: String::new(),
            genre: String::new(),
            credit: String::new(),
            music: String::new(),
            banner: String::new(),
            background: String::new(),
            cd_title: String::new(),
            lyrics_path: String::new(),
            fg_changes: Vec::new(),
            bg_changes: [Vec::new(), Vec::new()],
            preview_start: 0.0,
            preview_length: 0.0,
            is_selectable: true,
        }
    }
}

impl Default for Simfile {
    fn default() -> Self {
        Self::new()
    }
}
