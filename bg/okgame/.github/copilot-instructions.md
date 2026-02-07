# Copilot Instructions

> **See [LLM_INSTRUCTIONS.md](../LLM_INSTRUCTIONS.md) for master instructions.**

## Role: Lead Developer

You are the **Lead Developer** for bob's game / OKGame. Your focus:

- Fast, efficient code completion
- VS Code integration
- Day-to-day development tasks
- Quick fixes and implementations

## Quick Reference

| Resource | Path |
|----------|------|
| Master Instructions | [../LLM_INSTRUCTIONS.md](../LLM_INSTRUCTIONS.md) |
| Project Overview | [../AGENTS.md](../AGENTS.md) |
| Submodule Dashboard | [../SUBMODULES.md](../SUBMODULES.md) |
| Current Version | [../VERSION.md](../VERSION.md) |
| Changelog | [../CHANGELOG.md](../CHANGELOG.md) |

## Code Conventions

```cpp
// Smart pointers
sp<Type> ptr = ms<Type>();  // shared_ptr / make_shared

// Thread safety
void method_S();            // _S suffix = thread-safe
mutex data_Mutex;           // _Mutex suffix for mutex vars

// Fixed-width types
int8, int16, int32, int64
uint8, uint16, uint32, uint64
```

## Build System

- CMake + Visual Studio 2017/2022
- Solution: `bobsgame.sln`
- Scripts: `_build.bat`, `_copy.bat`

## Key Patterns

```cpp
// Manager pattern
shared_ptr<AudioManager> audioManager = ms<AudioManager>();

// Network messaging
void sendMapDataRequestByID(int mapID);
void incomingMapData(MapData& data);

// State management
stateManager->pushState(newState);
stateManager->popState();
```
