"""Central configuration defining all genres, speeds, and pitch factor parameters for the HymnMania pipeline."""

GENRES = {
    "gabba": "gabba hardcore",
    "psytrance": "full-on psytrance",
    "chiptune": "chiptune",
    "synthwave": "synthwave",
    "japanese_hardcore_techno": "japanese hardcore techno",
    "hardstyle_trance": "hardstyle trance",
    "deep_house": "deep house",
    "drum_and_bass": "drum and bass",
    "dubstep": "brostep dubstep",
    "detroit_techno": "detroit techno",
    "detroit_house": "detroit house"
}

SPEEDS = [0.5, 1.0, 1.5, 2.0, 3.0]

SPEED_LABEL_MAP = {
    0.5: "05x",
    1.0: "10x",
    1.5: "15x",
    2.0: "20x",
    3.0: "30x"
}

# Pitch shifts used by FFMPEG to defeat copyright checks
PITCH_SHIFT_FACTORS = {
    0.5: {"rate": 0.8909, "tempo": 1.1225},   # Shift down 2 semitones
    1.0: {"rate": 1.0595, "tempo": 0.9439},   # Shift up 1 semitone
    1.5: {"rate": 0.9439, "tempo": 1.0595},   # Shift down 1 semitone
    2.0: {"rate": 1.1225, "tempo": 0.8909},   # Shift up 2 semitones
    3.0: {"rate": 1.1892, "tempo": 0.8409}    # Shift up 3 semitones
}
