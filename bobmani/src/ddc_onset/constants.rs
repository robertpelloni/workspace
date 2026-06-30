pub const SAMPLE_RATE: usize = 44100;
pub const FRAME_RATE: usize = 100;

#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum Difficulty {
    Beginner = 0,
    Easy = 1,
    Medium = 2,
    Hard = 3,
    Challenge = 4,
}

impl Difficulty {
    pub fn threshold(&self) -> f32 {
        match self {
            Difficulty::Beginner => 0.15325437,
            Difficulty::Easy => 0.23268291,
            Difficulty::Medium => 0.29456162,
            Difficulty::Hard => 0.29084727,
            Difficulty::Challenge => 0.28875697,
        }
    }
}
