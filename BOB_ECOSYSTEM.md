# Bob Ecosystem Roadmap

The complete software ecosystem by Robert "bob's game" Pelloni.

## Vision

All bobproducts will dominate their respective categories. Eventually all software will be written in a boblang to run on a bobos.

## Current State

| Project | Exists As | Location | Tech Stack | Status |
|---------|-----------|----------|------------|--------|
| **bobcoin** | bobcoin | `bobcoin/` | Solana, Node.js | Active - proof-of-play research |
| **bobsgame** | bobsgameonlinejava | `bobsgameonlinejava/` | Java/Gradle, Lua | Has SQL schema, client code |
| **supertorrent** | supertorrent | `bobcoin/supertorrent/` | Node.js | Blockchain-integrated torrent |
| **bobfilez** | bobfilez | `bobfilez/` | Qt/C++ | File organizer - **REBRANDED** |
| **FWBer** | fwber | `fwber/` | Laravel 12, API-first | Dating platform - **REBRANDED** |
| **bobzzite** | bobzzite | `bobzzite/` | Bazzite/Fedora Atomic | Gaming OS - **INITIALIZED** |
| **bobzilla** | bobzilla | `bobzilla/` | Firefox/Gecko | Browser fork - **INITIALIZED** |
| **bobium** | bobium | `bobium/` | Chromium/Blink | Browser fork - **INITIALIZED** |
| **bob++** | - | - | - | Planned (C++ inspired language) |
| **boblang** | - | - | - | Planned (Programming language) |
| **bobvm** | - | - | - | Planned (Virtual machine) |
| **bobuntu** | - | - | - | Planned (Linux distribution) |

## Implementation Phases

### Phase 1: Rebrand Existing Projects (Quick Wins)

These already exist and just need renaming/branding:

1. **filez → bobfilez** ✅ DONE
   - Qt/C++ file organizer
   - Updated: CMakeLists.txt, vcxproj, sln, source files, README, AGENTS.md, WiX installer
   - Location: `bobfilez/` (GitHub repo renamed)

2. **supertorrent** (keeping current name)
   - Already in bobcoin ecosystem
   - Blockchain-integrated P2P
   - Location: `bobcoin/supertorrent/`

3. **fwber → FWBer** ✅ DONE
   - User-visible branding updated to "FWBer"
   - Internal code stays lowercase "fwber"
   - Location: `fwber/`

4. **BobsGameOnline → bobsgame**
   - Already correctly named
   - Java game client with Lua scripting
   - Location: `bobsgameonlinejava/`

### Phase 2: Fork & Customize (Medium Effort)

Fork existing open source projects and customize:

4. **bobzzite** (Gaming OS) ✅ INITIALIZED
   - Base: Bazzite (Fedora Atomic + gaming stack)
   - Location: `bobzzite/`
   - Key features: Immutable OS, pre-installed bob ecosystem, gaming-first
   - Ships with: bobzilla, bobfilez, Godot, bob's game
   - Future: Multiplayer computing, bobcoin integration

5. **bobzilla** (Browser) ✅ INITIALIZED
   - Base: Firefox / LibreWolf
   - Location: `bobzilla/`
   - Key features: Privacy by default, DRM support, Manifest V2 forever
   - Strips: Mozilla telemetry, Pocket, sponsored content
   - Preserves: webRequest API for ad blocking

6. **bobium** (Browser - Chromium-based) ✅ INITIALIZED
   - Base: Chromium / Ungoogled-Chromium
   - Location: `bobium/`
   - Key features: De-Googled, Manifest V2 preserved, portable USB mode
   - Fixes: Edge's 400+ tab performance issues
   - Preserves: webRequest API, YouTube ad blocking capability

### Phase 3: Build from Scratch (Heavy Lift)

New projects requiring significant development:

7. **boblang** (High-level language)
   - Purpose: General-purpose programming language
   - Target: bobvm bytecode
   - Style: TBD

8. **bob++** (Systems language)
   - Purpose: C++ alternative for systems programming
   - Could be: C++ dialect, transpiler, or new language
   - Use case: bobvm, performance-critical bob apps

9. **bobvm** (Virtual Machine)
   - Runtime for boblang
   - Could target: Custom bytecode, WASM, or LLVM

10. **bobuntu** (Linux Distribution)
    - Base: Ubuntu / Debian
    - Ships with: Full bob ecosystem pre-installed
    - Desktop: Custom bob-themed DE or modified KDE/GNOME

## Ecosystem Integration

All bobproducts interoperate:

```
┌─────────────────────────────────────────────────────────────┐
│                        bobuntu                               │
│  ┌─────────────────────────────────────────────────────┐    │
│  │                    bobzzite                          │    │
│  │  ┌──────────┐  ┌──────────┐  ┌──────────────────┐   │    │
│  │  │ bobzilla │  │  bobium  │  │    bobsgame      │   │    │
│  │  │ browser  │  │  browser │  │    (games)       │   │    │
│  │  └────┬─────┘  └────┬─────┘  └────────┬─────────┘   │    │
│  │       │              │                 │             │    │
│  │       └──────────────┼─────────────────┘             │    │
│  │                      │                               │    │
│  │              ┌───────▼───────┐                       │    │
│  │              ┌───────▼───────┐                       │    │
│  │              │    bobcoin    │ (payments/rewards)    │    │
│  │              └───────┬───────┘                       │    │
│  │                      │                               │    │
│  │       ┌──────────────┼──────────────┐               │    │
│  │       │              │              │               │    │
│  │  ┌────▼─────┐  ┌─────▼────┐  ┌─────▼─────┐         │    │
│  │  │bobtorrent│  │ bobfilez │  │   fwber   │         │    │
│  │  │   (P2P)  │  │ (files)  │  │ (dating)  │         │    │
│  │  └──────────┘  └──────────┘  └───────────┘         │    │
│  └─────────────────────────────────────────────────────┘    │
│                                                              │
│  ┌─────────────────────────────────────────────────────┐    │
│  │                   Development                        │    │
│  │  ┌──────────┐  ┌──────────┐  ┌──────────────────┐   │    │
│  │  │ boblang  │──│  bobvm   │  │      bob++       │   │    │
│  │  │ (lang)   │  │  (vm)    │  │ (systems lang)   │   │    │
│  │  └──────────┘  └──────────┘  └──────────────────┘   │    │
│  └─────────────────────────────────────────────────────┘    │
└─────────────────────────────────────────────────────────────┘
```

## Related Projects (Not Rebranded)

These stay as-is but integrate with bob ecosystem:

- **ArrowVortex** - Stepmania simfile editor
- **itgmania** - Rhythm game (StepMania fork)
- **aios** - AI Operating System / orchestrator

## Notes

- All bob products should have consistent branding
- bobcoin is the payment/reward layer across all products
- Proof-of-play from bobsgame earns bobcoin
- bobtorrent uses bobcoin for incentivized seeding
- bobfilez integrates with bobtorrent for distributed storage