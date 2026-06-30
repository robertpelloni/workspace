use std::string::String;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum ClearType {
    Failed,
    AssistEasy,
    LightAssistEasy,
    Easy,
    Normal,
    Hard,
    ExHard,
    FullCombo,
    Perfect,
    Max,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum SongTrophy {
    Easy,
    Groove,
    Hard,
    ExHard,
    Normal,
    Mirror,
    Random,
    RRandom,
    SRandom,
    HRandom,
    Spiral,
    AllScr,
    ExRandom,
    ExSRandom,
    Battle,
    BattleAssist,
}

#[derive(Debug, Default, Clone)]
pub struct ScoreData {
    pub clear: i32,
    pub epg: i32,
    pub lpg: i32,
    pub egr: i32,
    pub lgr: i32,
    pub egd: i32,
    pub lgd: i32,
    pub ebd: i32,
    pub lbd: i32,
    pub epr: i32,
    pub lpr: i32,
    pub ems: i32,
    pub lms: i32,

    pub fast_notes: i32,
    pub slow_notes: i32,
    pub fast_scratch: i32,
    pub slow_scratch: i32,

    pub maxcombo: i32,
    pub mode: i32,
    pub notes: i32,
    pub clearcount: i32,
    pub playcount: i32,
    pub minbp: i32,
    pub avgjudge: i64,
    pub total_duration: i64,

    pub trophy: String,
    pub option: i32,
    pub state: i32,
    pub sha256: String,
    pub id: String,
    pub player: String,
    pub random: i32,
    pub seed: i64,
    pub scorehash: String,
    pub assist: i32,
    pub gauge: i32,
    pub ghost: String,
    pub passnotes: i32,
}

impl ScoreData {
    pub fn new() -> Self {
        Self::default()
    }

    pub fn get_exscore(&self) -> i32 {
        (self.epg + self.lpg) * 2 + self.egr + self.lgr
    }

    pub fn validate(&self) -> bool {
        self.mode >= 0 && self.clear >= 0 && self.clear <= 10 && // Assume Max.id is 10 based on enums
        self.epg >= 0 && self.lpg >= 0 && self.egr >= 0 && self.lgr >= 0 && self.egd >= 0 && self.lgd >= 0 &&
        self.ebd >= 0 && self.lbd >= 0 && self.epr >= 0 && self.lpr >= 0 && self.ems >= 0 && self.lms >= 0 &&
        self.clearcount >= 0 && self.playcount >= self.clearcount && self.maxcombo >= 0 && self.notes > 0 &&
        self.passnotes >= 0 && self.passnotes <= self.notes && self.minbp >= 0 &&
        self.avgjudge >= 0 && self.random >= 0 && self.option >= 0 && self.assist >= 0 && self.gauge >= 0
    }
}
