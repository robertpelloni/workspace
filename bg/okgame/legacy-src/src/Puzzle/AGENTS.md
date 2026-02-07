# Puzzle Subsystem - AGENTS.md

> Part of [bob's game / OKGame](../../AGENTS.md)

## Overview

The Puzzle subsystem (32 files) implements the core puzzle game logic - the "every puzzle game in one" feature that allows customizable rulesets combining elements from Tetris, Puyo Puyo, Dr. Mario, and more.

## Directory Structure

```
Puzzle/
├── BobsGame.h/cpp           # Main puzzle game class
├── BobsGameMenus.cpp        # Menu system (212KB - large file)
├── OKGame.h/cpp             # Alternative puzzle implementation
├── Block.h/cpp              # Individual puzzle blocks
├── Piece.h/cpp              # Tetromino-style pieces
├── Grid.h/cpp               # Game grid management
├── GameLogic.h/cpp          # Core game rules (163KB - large file)
├── GameType.h/cpp           # Game mode definitions
├── GameSequence.h/cpp       # Sequence of game types
├── GameSequenceEditor.h/cpp # Sequence editing
├── CustomGameEditor.h/cpp   # Rule editor (220KB - large file)
├── GameTestMenu.h/cpp       # Testing interface
├── PuzzlePlayer.h/cpp       # Player state in puzzle mode
├── Room.h/cpp               # Multiplayer room management
├── GlobalSettings.h/cpp     # Puzzle game settings
└── Stats/                   # Statistics tracking
```

## Core Classes

### BobsGame (BobsGame.h)
Main puzzle game state. Extends Engine and BobState.

```cpp
class BobsGame : public Engine, public BobState {
    // Players
    vector<shared_ptr<PuzzlePlayer>> players;
    
    // Game state
    shared_ptr<GameType> currentGameType;
    shared_ptr<GameSequence> gameSequence;
    
    // Methods
    void update() override;
    void render() override;
    void startGame();
    void endGame();
};
```

### Block (Block.h)
Individual puzzle block with color, type, and state.

```cpp
class Block {
    int color;
    int type;           // Normal, garbage, special
    bool falling;
    bool locked;
    bool clearing;
    int clearTimer;
};
```

### Piece (Piece.h)
Tetromino-style piece composed of multiple blocks.

```cpp
class Piece {
    vector<Block> blocks;
    int rotation;
    int x, y;
    
    void rotateClockwise();
    void rotateCounterClockwise();
    bool canMoveDown(Grid& grid);
};
```

### Grid (Grid.h)
Game grid containing blocks.

```cpp
class Grid {
    int width, height;
    vector<vector<Block>> cells;
    
    void addPiece(Piece& piece);
    int clearLines();
    bool isGameOver();
};
```

### GameLogic (GameLogic.h)
Core game rules engine. **Large file (163KB)** - handles all puzzle mechanics.

Key features:
- Line clearing (match-3, match-4, etc.)
- Chain reactions
- Garbage sending/receiving
- Combo multipliers
- Special block effects

### GameType (GameType.h)
Defines a puzzle game ruleset.

```cpp
class GameType {
    string name;
    int gridWidth, gridHeight;
    int pieceTypes;          // Available piece shapes
    int colorsCount;         // Block colors
    int clearType;           // Line, match, etc.
    int clearCount;          // Minimum to clear
    bool gravity;            // Blocks fall after clear
    float fallSpeed;
    // ... many more parameters
};
```

### CustomGameEditor (CustomGameEditor.h)
UI for creating custom game rules. **Large file (220KB)**.

Allows editing:
- Grid dimensions
- Piece shapes
- Clear conditions
- Gravity behavior
- Speed curves
- Special blocks
- Garbage rules

### GameSequence (GameSequence.h)
A sequence of GameTypes played in order (e.g., "play Tetris, then Puyo Puyo").

## Key Features

### Rule Customization
Any combination of puzzle game rules:
- Tetris-style line clearing
- Puyo Puyo-style color matching
- Dr. Mario-style virus clearing
- Custom match patterns

### Multiplayer
- Local split-screen
- Online via BobNet
- Spectator mode
- Tournament brackets

### Visualizer Integration
- projectM renders in background
- Audio-reactive effects
- Preset transitions on combos

## Large Files (Technical Debt)

| File | Size | Recommendation |
|------|------|----------------|
| `BobsGameMenus.cpp` | 212KB | Split into separate menu classes |
| `CustomGameEditor.cpp` | 220KB | Extract sub-editors |
| `GameLogic.cpp` | 163KB | Extract rule modules |

## Key Patterns

### Player Management
```cpp
vector<shared_ptr<PuzzlePlayer>> players;
for (auto& player : players) {
    player->update();
}
```

### Game Type Loading
```cpp
shared_ptr<GameType> loadGameType(string name);
void applyGameType(shared_ptr<GameType> type);
```

### Event Callbacks
```cpp
void onLineClear(int lines, int chain);
void onGarbageReceived(int amount);
void onGameOver();
```

## Dependencies

- Engine subsystem (base classes)
- Utility subsystem (rendering, input)
- BobNet (multiplayer)
- projectM (visualizer)

## Related Documentation

- [Root AGENTS.md](../../AGENTS.md)
- [Engine AGENTS.md](../Engine/AGENTS.md)
- [Utility AGENTS.md](../Utility/AGENTS.md)
