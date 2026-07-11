# Universal LLM Instructions

## Core Principles
1. **Extensive Documentation**: Always document input information in comprehensive, thorough, FULL extreme detail. Maintain and update `VISION.md`, `ROADMAP.md`, `CHANGELOG.md`, `TODO.md`, `DEPLOY.md`, and `MEMORY.md`.
2. **Global Version Tracking**: There is a single global version number (e.g., in `VERSION` and `docs/VERSION.md`). Every build must have a new version number. Updates to the version number must be referenced in the commit message. All internal version numbers should reference this global text file instead of being hardcoded.
3. **Deep Analysis & Planning**: Before making any code changes, enter a deep planning mode. Reanalyze the project state and conversation history to identify uncompleted features, incomplete backend/frontend representations, or robustness issues.
4. **Code Quality & Commenting**: Comment code in depth (what, why, how, optimizations, bugs). Leave self-explanatory code bare. Double and triple-check functions for bugs, unpolished areas, and elegance.
5. **Continuous Execution**: Proceed autonomously, implementing features fully. Git pull, commit, and push regularly between implementing each major feature.
6. **Submodule Management**: Track and document all submodules, their project URLs, descriptions, versions, dates, and build numbers. Document library usage and locations in the directory structure.

## Agent Hand-offs
* Detail exact steps taken and the resulting analysis in `HANDOFF.md` to ensure seamless transitions between Claude, Gemini, GPT, and other models.
