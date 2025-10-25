# Master Skill Index

A comprehensive reference for all 41 skills in the consolidated library.

## How to Use This Index

Each skill entry includes:
- **Name** - The skill file name
- **Category** - Which category it belongs to
- **Description** - What the skill does
- **When to Use** - Triggering conditions
- **Key Concepts** - Main ideas or frameworks

---

## Development Process Skills

### brainstorming.skill
**When to Use:** Before writing code or creating implementation plans  
**Description:** Transform rough ideas into fully-formed designs through structured Socratic questioning and alternative exploration  
**Key Concepts:**
- 6-phase process: Understanding → Exploration → Design → Documentation → Setup → Planning
- Ask one question at a time
- Present 2-3 alternative approaches
- Incremental validation
- YAGNI ruthlessly

### writing-plans.skill  
**When to Use:** When creating detailed implementation plans  
**Description:** Break down designs into concrete, actionable task lists with clear dependencies and verification criteria  
**Key Concepts:**
- Task hierarchy and dependencies
- Clear acceptance criteria
- Risk identification
- Resource estimation

### executing-plans.skill
**When to Use:** During implementation phase  
**Description:** Systematically execute implementation plans while tracking progress and adapting to discoveries  
**Key Concepts:**
- Follow plan structure
- Document deviations
- Track completion
- Continuous verification

### verification-before-completion.skill
**When to Use:** Before marking any work complete  
**Description:** Comprehensive checklist to verify work meets all requirements before considering it done  
**Key Concepts:**
- Requirements verification
- Test coverage
- Documentation completeness
- Integration checks

---

## Testing Skills

### test-driven-development.skill
**When to Use:** When implementing new features or fixing bugs  
**Description:** Write tests before implementation to drive design and ensure correctness  
**Key Concepts:**
- Red-Green-Refactor cycle
- Test first, always
- Minimal implementation
- Continuous refactoring
- Test as specification

### testing-skills-with-subagents.skill
**When to Use:** Testing complex multi-agent or skill-based systems  
**Description:** Strategies for testing systems that use sub-agents or composed skills  
**Key Concepts:**
- Agent isolation
- Skill mocking
- Integration testing
- State verification
- Parallel test execution

### testing-anti-patterns.skill
**When to Use:** When reviewing tests or experiencing testing problems  
**Description:** Common testing mistakes and how to avoid them  
**Key Concepts:**
- Fragile tests
- Test interdependence
- Over-mocking
- Poor assertions
- Slow test suites

### condition-based-waiting.skill
**When to Use:** Replacing sleep/timeout calls in tests  
**Description:** Wait for actual conditions instead of arbitrary time periods  
**Key Concepts:**
- Poll for conditions
- Exponential backoff
- Clear timeout messages
- Deterministic tests

### test-pressure-1.skill
**When to Use:** Under time pressure to deliver  
**Description:** Testing strategies when time is limited (Part 1)  
**Key Concepts:**
- Risk-based testing
- Critical path focus
- Smoke tests
- Fast feedback

### test-pressure-2.skill
**When to Use:** Continued time pressure scenarios  
**Description:** Additional testing strategies for pressure situations (Part 2)  
**Key Concepts:**
- Parallel testing
- Test prioritization
- Incremental coverage

### test-pressure-3.skill
**When to Use:** Extreme pressure situations  
**Description:** Minimal viable testing approach (Part 3)  
**Key Concepts:**
- Core functionality focus
- Manual verification
- Post-release testing

---

## Debugging Skills

### systematic-debugging.skill
**When to Use:** Encountering any bug, test failure, or unexpected behavior  
**Description:** Four-phase debugging framework ensuring root cause investigation before fixes  
**Key Concepts:**
- NO FIXES WITHOUT ROOT CAUSE FIRST
- Phase 1: Root cause investigation
- Phase 2: Pattern analysis
- Phase 3: Hypothesis and testing
- Phase 4: Implementation
- After 3 failed fixes → question architecture

### root-cause-tracing.skill
**When to Use:** Error deep in call stack or unclear origin  
**Description:** Backward tracing technique to find where problems originate  
**Key Concepts:**
- Trace data flow backwards
- Find source, not symptom
- Document the path
- Fix at origin

### when-stuck.skill
**When to Use:** When progress stops or you're spinning  
**Description:** Strategies to identify why you're stuck and get unstuck  
**Key Concepts:**
- Recognize stuck patterns
- Question assumptions
- Change approach
- Ask for help
- Take breaks

---

## Code Review Skills

### code-reviewer.skill
**When to Use:** When reviewing someone else's code  
**Description:** How to provide valuable, constructive code reviews  
**Key Concepts:**
- Review for correctness first
- Security concerns
- Performance implications
- Maintainability
- Constructive feedback
- Balance praise and critique

### requesting-code-review.skill
**When to Use:** Before submitting code for review  
**Description:** Prepare code reviews that reviewers can act on quickly  
**Key Concepts:**
- Self-review first
- Clear description
- Test evidence
- Small, focused changes
- Context provision

### receiving-code-review.skill
**When to Use:** When receiving feedback on your code  
**Description:** Respond to code review feedback constructively and professionally  
**Key Concepts:**
- Assume good intent
- Ask clarifying questions
- Defend when needed, but objectively
- Learn from feedback
- Thank reviewers

---

## Git & Workflow Skills

### using-git-worktrees.skill
**When to Use:** Working on multiple branches simultaneously  
**Description:** Use git worktrees to manage parallel development safely  
**Key Concepts:**
- Separate working directories per branch
- No branch switching overhead
- Parallel testing
- Safety checks before creation

### finishing-a-development-branch.skill
**When to Use:** Completing work on a feature branch  
**Description:** Proper cleanup and merge process for development branches  
**Key Concepts:**
- Final verification
- Rebase vs merge
- Clean commit history
- Branch deletion
- Tag creation

---

## Writing & Documentation Skills

### writing-skills.skill
**When to Use:** Creating any written documentation or content  
**Description:** Comprehensive guide to technical and documentation writing  
**Key Concepts:**
- Audience awareness
- Structure and organization
- Clarity and precision
- Examples and diagrams
- Iterative improvement

### writing-clearly-and-concisely.skill
**When to Use:** When any human will read your writing  
**Description:** Apply Strunk's timeless rules for clear, strong, professional writing  
**Key Concepts:**
- Active voice
- Eliminate needless words
- Parallel construction
- Omit redundant content
- Specific over general

### elements-of-style.skill
**When to Use:** Reference for style questions  
**Description:** Classical writing principles from "The Elements of Style"  
**Key Concepts:**
- Elementary rules of usage
- Elementary principles of composition
- Matters of form
- Words and expressions commonly misused
- An approach to style

---

## Architecture & Design Skills

### defense-in-depth.skill
**When to Use:** Designing systems with reliability and security needs  
**Description:** Implement multiple layers of validation and protection  
**Key Concepts:**
- Multiple validation layers
- Fail-safe defaults
- Explicit assumptions
- Input validation
- Error handling

### subagent-driven-development.skill
**When to Use:** Complex projects that can be parallelized  
**Description:** Coordinate development using autonomous sub-agents  
**Key Concepts:**
- Agent decomposition
- Clear interfaces
- Independent operation
- Coordination protocols
- Failure handling

### dispatching-parallel-agents.skill
**When to Use:** Coordinating multiple concurrent tasks  
**Description:** Launch and manage parallel agents effectively  
**Key Concepts:**
- Work distribution
- Load balancing
- Progress tracking
- Result aggregation
- Error isolation

### collision-zone-thinking.skill
**When to Use:** Identifying system risks and conflicts  
**Description:** Identify where different parts of system might conflict  
**Key Concepts:**
- Shared state analysis
- Concurrency risks
- Resource contention
- Interface boundaries
- Conflict resolution

### preserving-productive-tensions.skill
**When to Use:** Balancing competing design forces  
**Description:** Maintain healthy tension between competing concerns  
**Key Concepts:**
- Speed vs quality
- Flexibility vs simplicity
- Abstraction vs concreteness
- Perfect vs good enough
- Innovation vs stability

### simplification-cascades.skill
**When to Use:** Systems becoming too complex  
**Description:** Progressively simplify systems through cascading improvements  
**Key Concepts:**
- Identify complexity sources
- Simplify one layer
- Observe cascade effects
- Iterate downward
- Stop when stable

---

## Meta-Skills

### using-skills.skill
**When to Use:** When applying any skill  
**Description:** How to effectively use and apply skills in your workflow  
**Key Concepts:**
- When to invoke skills
- How to announce usage
- Combining skills
- Skill selection
- Adapting skills

### using-superpowers.skill
**When to Use:** Advanced skill application  
**Description:** Advanced techniques for skill composition and mastery  
**Key Concepts:**
- Skill chaining
- Custom skill creation
- Context switching
- Performance optimization

### sharing-skills.skill
**When to Use:** Contributing skills to others  
**Description:** How to package and share skills with your team or community  
**Key Concepts:**
- Skill documentation
- Example provision
- Version control
- Distribution methods
- Maintenance

### gardening-skills-wiki.skill
**When to Use:** Maintaining skill library  
**Description:** Curate, update, and improve the skill collection  
**Key Concepts:**
- Regular review
- Deprecation
- Consolidation
- Quality standards
- Community input

### pulling-updates-from-skill-repository.skill
**When to Use:** Syncing with skill updates  
**Description:** Keep local skills synchronized with central repository  
**Key Concepts:**
- Update checking
- Conflict resolution
- Version management
- Selective updates

---

## Thinking & Analysis Skills

### meta-pattern-recognition.skill
**When to Use:** Identifying patterns across domains  
**Description:** Recognize and apply patterns that transcend specific contexts  
**Key Concepts:**
- Cross-domain mapping
- Pattern abstraction
- Analogy formation
- Transfer learning
- Pattern catalog

### inversion-exercise.skill
**When to Use:** Stuck on forward thinking  
**Description:** Think backwards from desired outcome to find solution path  
**Key Concepts:**
- Start with end state
- Work backwards
- Identify prerequisites
- Remove obstacles
- Reverse constraints

### tracing-knowledge-lineages.skill
**When to Use:** Understanding knowledge evolution  
**Description:** Track how ideas and knowledge evolve over time  
**Key Concepts:**
- Source identification
- Transformation tracking
- Influence mapping
- Citation chains
- Knowledge provenance

### search-agent.skill
**When to Use:** Need to find information effectively  
**Description:** Systematic approach to searching and information gathering  
**Key Concepts:**
- Query formulation
- Source evaluation
- Result synthesis
- Iterative refinement
- Knowledge gaps

### remembering-conversations.skill
**When to Use:** Maintaining context across conversations  
**Description:** Techniques for retaining and referencing past conversations  
**Key Concepts:**
- Context markers
- Summary creation
- Key point extraction
- Reference systems
- Memory aids

---

## Communication Skills

### persuasion-principles.skill
**When to Use:** Need to influence or convince  
**Description:** Evidence-based principles for persuasive communication  
**Key Concepts:**
- Reciprocity
- Commitment/consistency
- Social proof
- Authority
- Liking
- Scarcity
- Unity

### scale-game.skill
**When to Use:** Communication at scale  
**Description:** Strategies for effective communication in large groups or organizations  
**Key Concepts:**
- Message amplification
- Feedback loops
- Signal vs noise
- Cascade effects
- Broadcast strategies

---

## Statistics

- **Total Skills:** 41
- **Development Process:** 4
- **Testing:** 7
- **Debugging:** 3
- **Code Review:** 3
- **Git & Workflow:** 2
- **Writing & Documentation:** 3
- **Architecture & Design:** 6
- **Meta-Skills:** 5
- **Thinking & Analysis:** 5
- **Communication:** 2

---

**Version:** 1.0  
**Last Updated:** October 24, 2025
