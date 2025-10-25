# Consolidated Skill Library

This library contains 41 consolidated and organized skill files, organized into 10 thematic categories.

## Overview

These skills were consolidated from 69 source files, with duplicates merged, typos fixed, and stub files integrated into their full versions.

## Organization

### 📁 Categories

1. **Development Process** (4 skills) - Planning, execution, and verification workflows
2. **Testing** (7 skills) - Test-driven development, anti-patterns, and testing strategies  
3. **Debugging** (3 skills) - Systematic debugging, root cause analysis, and problem-solving
4. **Code Review** (3 skills) - Requesting, performing, and receiving code reviews
5. **Git & Workflow** (2 skills) - Git worktrees and branch management
6. **Writing & Documentation** (3 skills) - Clear writing, documentation, and style guides
7. **Architecture & Design** (6 skills) - System design patterns and architectural principles
8. **Meta-Skills** (5 skills) - Skills about managing and using skills
9. **Thinking & Analysis** (5 skills) - Analytical frameworks and thinking tools
10. **Communication** (2 skills) - Persuasion and communication strategies

## Quick Index

### Development Process
- `brainstorming.skill` - Transform rough ideas into designs through structured questioning
- `writing-plans.skill` - Create detailed implementation plans
- `executing-plans.skill` - Execute plans systematically
- `verification-before-completion.skill` - Verify work before marking complete

### Testing
- `test-driven-development.skill` - Write tests before implementation
- `testing-skills-with-subagents.skill` - Test complex multi-agent systems
- `testing-anti-patterns.skill` - Common testing mistakes to avoid
- `condition-based-waiting.skill` - Replace timeouts with condition checks
- `test-pressure-1.skill` - Testing under pressure (part 1)
- `test-pressure-2.skill` - Testing under pressure (part 2)
- `test-pressure-3.skill` - Testing under pressure (part 3)

### Debugging
- `systematic-debugging.skill` - Four-phase debugging framework
- `root-cause-tracing.skill` - Trace issues to their source
- `when-stuck.skill` - Strategies for getting unstuck

### Code Review
- `code-reviewer.skill` - How to review code effectively
- `requesting-code-review.skill` - Request reviews that get results
- `receiving-code-review.skill` - Respond to feedback constructively

### Git & Workflow
- `using-git-worktrees.skill` - Manage multiple branches simultaneously
- `finishing-a-development-branch.skill` - Complete and merge branches properly

### Writing & Documentation
- `writing-skills.skill` - Comprehensive writing guide
- `writing-clearly-and-concisely.skill` - Clear, concise communication
- `elements-of-style.skill` - Timeless writing principles

### Architecture & Design
- `defense-in-depth.skill` - Layered security and validation
- `subagent-driven-development.skill` - Develop using autonomous sub-agents
- `dispatching-parallel-agents.skill` - Coordinate parallel work
- `collision-zone-thinking.skill` - Identify areas of conflict
- `preserving-productive-tensions.skill` - Balance competing forces
- `simplification-cascades.skill` - Simplify systems progressively

### Meta-Skills
- `using-skills.skill` - How to use skills effectively
- `using-superpowers.skill` - Advanced skill usage
- `sharing-skills.skill` - Share skills with others
- `gardening-skills-wiki.skill` - Maintain and grow the skill library
- `pulling-updates-from-skill-repository.skill` - Sync with skill repositories

### Thinking & Analysis
- `meta-pattern-recognition.skill` - Recognize patterns across domains
- `inversion-exercise.skill` - Think backwards to solve problems
- `tracing-knowledge-lineages.skill` - Track how knowledge evolves
- `search-agent.skill` - Effective search strategies
- `remembering-conversations.skill` - Retain context across conversations

### Communication
- `persuasion-principles.skill` - Principles of effective persuasion
- `scale-game.skill` - Communication strategies at scale

## Consolidation Notes

### Merged Files
The following stub files were merged into their full versions:
- `brainstorm` → `brainstorming`
- `execute-plan` → `executing-plans`
- `write-plan` → `writing-plans`

### Fixed Typos
- `testing-anti-patters` / `testing-anti-pattners` → `testing-anti-patterns`
- `writing-clearly-and-consisely` → `writing-clearly-and-concisely`
- `simplification_cascades` → `simplification-cascades`
- `scale_game` → `scale-game`

### Duplicate Handling
When multiple versions existed (e.g., `__2_`, `__3_` suffixes), the most complete version (typically the largest file) was selected.

## Usage

To use a skill, reference it in your workflow:

```markdown
**REQUIRED SUB-SKILL:** Use category:skill-name
```

Example:
```markdown
**REQUIRED SUB-SKILL:** Use debugging:systematic-debugging
```

## Statistics

- **Total source files:** 69
- **Consolidated skills:** 41
- **Categories:** 10
- **Stubs merged:** 3
- **Typos fixed:** 4
- **Duplicates resolved:** 23

## Directory Structure

```
outputs/
├── README.md (this file)
├── MASTER-INDEX.md
├── development-process/
│   ├── brainstorming.skill
│   ├── writing-plans.skill
│   ├── executing-plans.skill
│   └── verification-before-completion.skill
├── testing/
│   ├── test-driven-development.skill
│   ├── testing-skills-with-subagents.skill
│   ├── testing-anti-patterns.skill
│   ├── condition-based-waiting.skill
│   ├── test-pressure-1.skill
│   ├── test-pressure-2.skill
│   └── test-pressure-3.skill
├── debugging/
│   ├── systematic-debugging.skill
│   ├── root-cause-tracing.skill
│   └── when-stuck.skill
├── code-review/
│   ├── code-reviewer.skill
│   ├── requesting-code-review.skill
│   └── receiving-code-review.skill
├── git-and-workflow/
│   ├── using-git-worktrees.skill
│   └── finishing-a-development-branch.skill
├── writing-and-documentation/
│   ├── writing-skills.skill
│   ├── writing-clearly-and-concisely.skill
│   └── elements-of-style.skill
├── architecture-and-design/
│   ├── defense-in-depth.skill
│   ├── subagent-driven-development.skill
│   ├── dispatching-parallel-agents.skill
│   ├── collision-zone-thinking.skill
│   ├── preserving-productive-tensions.skill
│   └── simplification-cascades.skill
├── meta-skills/
│   ├── using-skills.skill
│   ├── using-superpowers.skill
│   ├── sharing-skills.skill
│   ├── gardening-skills-wiki.skill
│   └── pulling-updates-from-skill-repository.skill
├── thinking-and-analysis/
│   ├── meta-pattern-recognition.skill
│   ├── inversion-exercise.skill
│   ├── tracing-knowledge-lineages.skill
│   ├── search-agent.skill
│   └── remembering-conversations.skill
└── communication/
    ├── persuasion-principles.skill
    └── scale-game.skill
```

---

**Version:** 1.0  
**Last Updated:** October 24, 2025  
**Consolidated by:** Claude (Sonnet 4.5)
