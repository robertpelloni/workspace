# Super Monkey Ball Feature Parity Roadmap

## Executive Summary
This document outlines a definitive roadmap to bring the *Neverball* project to feature parity with the *Super Monkey Ball (SMB)* series. The goal is to evolve the Neverball engine to support the beloved gameplay modes, physics nuances, and extensive party game library of the SMB franchise, while preserving Neverball's open-source legacy.

The roadmap is divided into four phases, prioritizing the "Golden Era" (SMB 1 & 2) features first, followed by the vast content of the "Party Game" era, and finally the "Modern" mechanics (Jump, Stats, Online).

## Feature Gap Analysis

| Feature Category | Super Monkey Ball Series (Target) | Current Neverball (Status) |
| :--- | :--- | :--- |
| **Physics** | "Snappy", high-friction, instant acceleration. | "Heavy", momentum-based, inertial. |
| **Camera** | Auto-follow, fixed angle options, "snap" behind. | Loose follow, manual rotation focus. |
| **Main Game** | Timer-based, Bananas = Lives, Bonus Stages. | Timer-based, Coins = Score/Life, no Bonus Stages. |
| **Story Mode** | Cutscenes, World Map, Hub Worlds (SMB2). | Linear level progression only. |
| **Characters** | Distinct Stats (Speed, Weight, Accel, Jump). | Uniform physics (cosmetic differences only). |
| **Mechanics** | Tilt (Classic), Jump (Blitz/Mania), Spin Dash (Rumble). | Tilt only. |
| **Party Games** | 50+ Minigames (Race, Fight, Target, Bowling, Golf, etc.). | Basic Race Mode (In Progress). |
| **Multiplayer** | 4-Player Split-Screen, Online (Modern). | 4-Player Split-Screen (Basic). |
| **Unlockables** | Shop, Characters, Costumes, Modes, Art. | Level unlocking only. |

## Phased Roadmap

### Phase 1: The "Classic" Foundation (SMB 1 Parity)
*Goal: Replicate the feel and core loop of the original arcade/GameCube classic.*

1.  **Physics & Control Overhaul**
    *   Implement an "Arcade Physics" toggle (higher friction, faster acceleration).
    *   Refine Camera logic: Implement "Snap-to-Back" and tighter auto-follow.
    *   **Deliverable:** `MODE_ARCADE` in `game_server.c`.

2.  **Core Game Loop Enhancements**
    *   **Lives System:** Refactor Coin logic to grant Extra Lives (100 Bananas = 1 Life).
    *   **Bonus Stages:** Support for "Collect All" levels with no exit (timer end = success).
    *   **UI/UX:** Implement "Ready? GO!" and "Fall Out" announcer-style transitions.

3.  **The "Holy Trinity" Party Games**
    *   **Monkey Race:**
        *   Power-ups (Speed, Missiles, Peels).
        *   Lap counter and Waypoint system.
    *   **Monkey Target:**
        *   Flight Physics (Gliding state, wind resistance).
        *   Wheel of Danger / Landing Zones.
    *   **Monkey Fight:**
        *   Punch mechanic (Spring attached to ball).
        *   Knockback physics calculation.
        *   Power-ups (Big Punch, Speed, etc.).

### Phase 2: The "Deluxe" Expansion (SMB 2 Features)
*Goal: Add depth, story, and the extended suite of beloved minigames.*

1.  **Campaign Engine**
    *   Support for "Worlds" (groups of levels).
    *   Cutscene playback integration (Video or In-Engine).
    *   World Map / Hub UI.

2.  **Advanced Party Games (Physics Heavy)**
    *   **Monkey Bowling:**
        *   Pin physics simulation.
        *   Spin control UI.
    *   **Monkey Golf / Mini-Golf:**
        *   Stroke power meter.
        *   Club selection.
    *   **Monkey Billiards:**
        *   Cue ball physics, spin, banking.
        *   Rulesets (9-ball, 8-ball).

3.  **Dynamic Level Elements**
    *   Moving/Morphing Stages (e.g., Arthropod level).
    *   Switches that alter geometry in real-time.
    *   Warp Gates.

### Phase 3: The "Modern" Mechanics (Banana Blitz/Mania)
*Goal: Modernize the engine with features from the Wii/Switch eras.*

1.  **Character Class System**
    *   Implement `struct character_stats` (Weight, Speed, Acceleration, Jump, Size).
    *   Character Selection Screen with stats visualization.

2.  **New Mechanics**
    *   **Jump:** Active ability to hop (toggleable per mode/level).
    *   **Spin Dash:** Chargeable speed boost (Sonic-style).

3.  **Unlock & Economy System**
    *   "Bananas" as persistent currency (Play Points).
    *   In-game Shop UI to unlock Characters, Costumes, and Modes.

4.  **Minigame Explosion (Prioritized List)**
    *   *Tier 1:* Monkey Boat, Monkey Shot, Monkey Soccer.
    *   *Tier 2:* Monkey Tennis, Monkey Baseball.
    *   *Tier 3:* Whack-a-Mole, Hurdle Race, Hammer Throw.

### Phase 4: Future Tech (Rumble & Online)
*Goal: Bring Neverball into the next generation.*

1.  **Online Multiplayer**
    *   Networked Physics (Prediction/Rollback or Lockstep).
    *   Lobby System.
2.  **Level Editor Integration**
    *   In-game level builder (User Generated Content).
3.  **Ghost Data Sharing**
    *   Global Leaderboards with replay downloads.

## Immediate Action Plan
To begin this journey, the team should focus on **Phase 1, Item 3: Monkey Target**.
*   **Reasoning:** It requires "Flight Physics" which is distinct from rolling, pushing the engine's capabilities. It is also the most requested party game.
*   **Prerequisite:** The shared-world architecture (recently implemented) is ready for this.
