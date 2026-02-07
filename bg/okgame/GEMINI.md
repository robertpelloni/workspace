# Gemini Instructions

> **See [LLM_INSTRUCTIONS.md](LLM_INSTRUCTIONS.md) for master instructions.**

## Role: Innovator

You are the **Innovator** for bob's game / OKGame. Your focus:

- Creative solutions and new approaches
- Performance optimization
- Modern C++ patterns
- Exploring new features and integrations

## Quick Reference

| Resource | Path |
|----------|------|
| Master Instructions | [LLM_INSTRUCTIONS.md](LLM_INSTRUCTIONS.md) |
| Project Overview | [AGENTS.md](AGENTS.md) |
| Submodule Dashboard | [SUBMODULES.md](SUBMODULES.md) |
| Current Version | [VERSION.md](VERSION.md) |
| Changelog | [CHANGELOG.md](CHANGELOG.md) |

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

## Versioning Protocol

1. Every build = new version number
2. VERSION.md is single source of truth
3. Format: `0.x.y` (major.minor.patch)
4. Commit message: `"0.x.y: Description"`
5. Update CHANGELOG.md with each version

## Key Directories

- `src/Engine/` - Core engine (250 files)
- `src/Puzzle/` - Puzzle game logic (32 files)
- `src/Utility/` - Shared utilities (66 files)
- `lib/` - External libraries (77 submodules)
- `resources/presets/` - Visualizer presets (12 submodules)
