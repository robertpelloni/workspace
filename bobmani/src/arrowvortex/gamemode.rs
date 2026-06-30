#[derive(Debug, Clone)]
pub struct GameMode {
    pub id: String,
    pub game: String,
    pub mode: String,
    pub index: u32,
    pub num_cols: i32,
    pub num_players: i32,

    // Arrays translated to Rust Vecs
    pub color_table: Vec<i32>,
    pub mirror_table_h: Vec<i32>,
    pub mirror_table_v: Vec<i32>,

    pub pad_width: i32,
    pub pad_height: i32,

    // Using tuples (f32, f32) instead of Vec2 struct for simplicity
    pub pad_col_positions: Vec<(f32, f32)>,
    pub pad_initial_feet_cols: Vec<(f32, f32)>,
}

impl GameMode {
    pub fn new(id: String, num_cols: i32, num_players: i32) -> Self {
        let (game, mode) = Self::split_id(&id);

        Self {
            id,
            game,
            mode,
            index: 0, // Assigned later by a manager
            num_cols,
            num_players,
            color_table: Vec::with_capacity(num_cols as usize),
            mirror_table_h: Vec::with_capacity(num_cols as usize),
            mirror_table_v: Vec::with_capacity(num_cols as usize),
            pad_width: 0,
            pad_height: 0,
            pad_col_positions: Vec::with_capacity(num_cols as usize),
            pad_initial_feet_cols: Vec::with_capacity(num_players as usize),
        }
    }

    /// Translates the C++ `SplitId` function to parse the game and mode name
    fn split_id(id: &str) -> (String, String) {
        let mut out_game = String::new();
        let mut out_mode = String::new();
        let mut prefix = true;
        let mut prev = ' ';

        for mut c in id.chars() {
            if prev == ' ' && c.is_ascii_lowercase() {
                c = c.to_ascii_uppercase();
            }

            if prefix {
                if c == '-' {
                    prefix = false;
                } else {
                    out_game.push(c);
                }
            } else {
                if c == '-' {
                    out_mode.push(' ');
                } else {
                    out_mode.push(c);
                }
            }
            prev = c;
        }

        (out_game, out_mode)
    }

    pub fn make_game_index(generated: bool, mode: i32) -> u32 {
        let gen_bit = if generated { 1 } else { 0 };
        (gen_bit << 31) | (mode as u32 & 0x7FFFFFFF)
    }

    pub fn split_game_index(index: u32) -> (bool, i32) {
        let generated = ((index >> 31) & 1) != 0;
        let mode = (index & 0x7FFFFFFF) as i32;
        (generated, mode)
    }
}
