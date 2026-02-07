# Engine Subsystem - AGENTS.md

> Part of [bob's game / OKGame](../../AGENTS.md)

## Overview

The Engine subsystem (250 files) provides the core game engine infrastructure including rendering, entity management, map systems, networking, and RPG mechanics.

## Directory Structure

```
Engine/
├── Engine.h/cpp           # Base engine class
├── EnginePart.h/cpp       # Component base class
├── MiniGameEngine.h/cpp   # Lightweight engine variant
├── stdafx.h/cpp           # Precompiled headers
├── cinematics/            # Cutscene system (6 files)
├── entity/                # Characters, NPCs, pathfinding (22 files)
├── map/                   # Tile-based map system (26 files)
├── nd/                    # nD puzzle game system (42 files)
├── network/               # Networking layer (12 files)
├── rpg/                   # RPG game logic (102 files)
├── stadium/               # Tournament/arena system (6 files)
├── state/                 # Game state management (22 files)
└── text/                  # Text/dialogue rendering (4 files)
```

## Core Classes

### Engine (Engine.h)
Base class for all game engines. Contains shared_ptr managers:

```cpp
class Engine {
    shared_ptr<AudioManager> audioManager;
    shared_ptr<Cameraman> cameraman;
    shared_ptr<SpriteManager> spriteManager;
    shared_ptr<ActionManager> actionManager;
    shared_ptr<MapManager> mapManager;
    shared_ptr<CinematicsManager> cinematicsManager;
    shared_ptr<CaptionManager> captionManager;
    shared_ptr<TextManager> textManager;
    shared_ptr<EventManager> eventManager;
    
    virtual void update();
    virtual void render();
    virtual void cleanup();
    virtual void updateControls();
    virtual void serverMessageReceived();
    virtual void udpPeerMessageReceived();
};
```

### EnginePart (EnginePart.h)
Base class for engine components. Provides back-reference to parent engine.

### MiniGameEngine (MiniGameEngine.h)
Lightweight engine variant for mini-games and embedded games.

## Subsystems

### cinematics/ - Cutscene System
- `Cinematic.h/cpp` - Cutscene playback
- `CinematicsManager.h/cpp` - Manages cutscene queue
- Supports scripted camera movements, dialogue, animations

### entity/ - Entity System
- `Entity.h/cpp` - Base entity class
- `Character.h/cpp` - Player/NPC characters
- `RandomCharacter.h/cpp` - Procedural NPCs
- `MicroPather` integration for A* pathfinding
- Appearance system (hair, clothes, accessories)

### map/ - Map System
- `Map.h/cpp` - Tile-based map container
- `MapManager.h/cpp` - Map loading, caching
- `Chunk.h/cpp` - Map chunk streaming
- `Layer.h/cpp` - Render layers (ground, objects, overhead)
- `Door.h/cpp`, `Warp.h/cpp` - Map transitions
- Threading support for background loading

### nd/ - nD Puzzle System
- `NDGameEngine.h/cpp` - N-dimensional puzzle engine
- Supports arbitrary puzzle dimensions
- Grid-based puzzle mechanics

### network/ - Networking
- `BobNet.h/cpp` - Main network coordinator
- `TCPServerConnection.h/cpp` - Server communication
- `UDPPeerConnection.h/cpp` - P2P gameplay
- STUN server integration for NAT traversal

### rpg/ - RPG System (largest: 102 files)
- `event/` - Event scripting system (30 files)
- `dialogue/` - Dialogue trees, text display
- `inventory/` - Items, equipment
- `battle/` - Combat system
- `quest/` - Quest tracking

### stadium/ - Tournament System
- `Stadium.h/cpp` - Arena management
- Tournament brackets, rankings
- Multiplayer matchmaking

### state/ - State Management
- `BobState.h/cpp` - Base state class
- `BobStateManager.h/cpp` - Stack-based state machine
- `LoginState`, `TitleScreenState`, etc.

### text/ - Text Rendering
- `TextManager.h/cpp` - Text display coordination
- Font rendering integration

## Key Patterns

### Manager Pattern
All subsystems use manager classes with shared_ptr:
```cpp
shared_ptr<MapManager> mapManager = ms<MapManager>();
```

### Network Message Pattern
```cpp
// Sending
void sendMapDataRequestByID(int mapID);

// Receiving
void incomingMapData(MapData& data);
```

### Thread Safety
Methods with `_S` suffix are thread-safe:
```cpp
int getUserID_S();  // Thread-safe accessor
mutex data_Mutex;   // Associated mutex
```

## Dependencies

- SDL2 (windowing, input)
- OpenGL (rendering)
- Boost.Serialization (save/load)
- MicroPather (pathfinding)
- SDL_net (networking)

## Related Documentation

- [Root AGENTS.md](../../AGENTS.md)
- [Puzzle AGENTS.md](../Puzzle/AGENTS.md)
- [Utility AGENTS.md](../Utility/AGENTS.md)
