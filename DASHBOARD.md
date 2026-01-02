# Workspace Dashboard

## Overview
This repository manages a collection of AI-related submodules, tools, and configurations. The structure has been reorganized to centralize AI operations within the `AIOS` submodule and file organization tools in `FileOrganizer`.

## Submodules

### Core
- **AIOS**: The central AI Operating System hub containing agents, MCP servers, and frameworks.
  - Path: `AIOS`
  - URL: `https://github.com/robertpelloni/AIOS`
- **FileOrganizer**: Tools for organizing local files using AI.
  - Path: `FileOrganizer`
  - URL: `https://github.com/robertpelloni/FileOrganizer`

### Applications & Platforms
- **LibreChat**: Advanced chatbot interface.
  - Path: `LibreChat`
  - URL: `https://github.com/danny-avila/LibreChat`
- **OmniParser**: Parser for various file formats.
  - Path: `OmniParser`
  - URL: `https://github.com/microsoft/OmniParser`
- **Resume-Matcher**: AI tool to match resumes with job descriptions.
  - Path: `Resume-Matcher`
  - URL: `https://github.com/srbhr/Resume-Matcher`
- **web-ui**: Browser automation UI.
  - Path: `web-ui`
  - URL: `https://github.com/browser-use/web-ui`

### Games & Sims
- **ArrowVortex**: Rhythm game engine.
  - Path: `ArrowVortex`
  - URL: `https://github.com/robertpelloni/ArrowVortex`
- **BobsGameOnline**: Online game platform.
  - Path: `BobsGameOnline`
  - URL: `https://github.com/robertpelloni/BobsGameOnline`
- **AirSim**: Open source simulator for autonomous vehicles.
  - Path: `AirSim`
  - URL: `https://github.com/microsoft/AirSim`
- **hellven**: Gaming project.
  - Path: `hellven`
  - URL: `https://gitlab.com/robertpelloni/hellven`
- **JWildfire**: Image processing software.
  - Path: `JWildfire`
  - URL: `https://github.com/robertpelloni/JWildfire`
- **stepmania**: Advanced rhythm game.
  - Path: `stepmania`
  - URL: `https://github.com/robertpelloni/stepmania`
- **itgmania**: Fork of StepMania.
  - Path: `itgmania`
  - URL: `https://github.com/robertpelloni/itgmania`

### Utilities & Tools
- **copyparty**: Portable file server.
  - Path: `copyparty`
  - URL: `https://github.com/9001/copyparty`
- **vcpkg**: C++ library manager.
  - Path: `vcpkg`
  - URL: `https://github.com/microsoft/vcpkg`
- **witsy**: AI tool.
  - Path: `witsy`
  - URL: `https://github.com/nbonamy/witsy`
- **onyx**: Distributed computing platform.
  - Path: `onyx`
  - URL: `https://github.com/onyx-dot-app/onyx`
- **ddc**: Data distribution component.
  - Path: `ddc`
  - URL: `https://github.com/robertpelloni/ddc`
- **kapture**: Screen capture tool.
  - Path: `kapture`
  - URL: `https://github.com/williamkapke/kapture`
- **changesets**: Versioning tool.
  - Path: `changesets`
  - URL: `https://github.com/changesets/changesets`
- **lootbox**: Game asset manager.
  - Path: `lootbox`
  - URL: `https://github.com/jx-codes/lootbox`
- **bobcoin**: Cryptocurrency project.
  - Path: `bobcoin`
  - URL: `https://github.com/robertpelloni/bobcoin`
- **raindropioapp**: Bookmark manager app.
  - Path: `raindropioapp`
  - URL: `https://github.com/robertpelloni/raindropioapp`
- **robertpelloni.com**: Personal website repo.
  - Path: `robertpelloni.com`
  - URL: `https://gitlab.com/robertpelloni/robertpelloni.com`
- **fwber**: Framework/Tool.
  - Path: `fwber`
  - URL: `https://github.com/robertpelloni/fwber`

### AIOS Included Submodules (Located in `AIOS/references/`)
*See `AIOS/README.md` for the full list of internal submodules.*

- **Agents**: `amplifier`, `autogen`, `OpenHands`, `trae-agent`, `claude-squad`, ...
- **MCP Servers**: `chroma-mcp`, `gemini-mcp-tool`, `mcp-manager`, `mcp-server-gemini`, ...
- **Frameworks**: `opencode`, `playwright`, `vibesdk`, `gram`, ...
- **Tools**: `CodeMachine-CLI`, `grok-cli`, `goose`, ...
- **Memory**: `beads`, `mem0`, ...

## Recent Changes
- Moved ~60 AI-related submodules from Root to `AIOS/references/`.
- Created `FileOrganizer` module and moved related tools there.
- Updated all submodules to latest upstream versions.
- Cleaned up root workspace structure.

## Maintenance
To update all submodules:
```bash
git submodule update --init --recursive
git submodule foreach --recursive "git pull origin main || git pull origin master"
```
