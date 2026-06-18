# Load Session Handoff Command

You are beginning a new session and need to fully reconstruct the context of previous work from the handoff document. This command performs deep analysis of the HANDOFF.md file to rebuild the complete mental state, understanding, and momentum of the previous session, enabling you to continue work seamlessly as if no context was lost.

## Auto-Loaded Context:
@docs/ai-context/HANDOFF.md (REQUIRED - must be attached)
@/CLAUDE.md (project guidelines)

## Philosophy of Perfect Context Loading

The goal is not just to read what was done, but to **reconstruct the complete cognitive state** of the previous session. You should emerge from this process with:

- **Full situational awareness** of where the project stands
- **Deep understanding** of decisions made and why
- **Clear mental model** of the system architecture
- **Awareness of pitfalls** to avoid repeating mistakes
- **Immediate actionability** knowing exactly what to do next
- **Confidence in direction** understanding the strategy being pursued

## Step 1: Validate Handoff Document

First, ensure you have the necessary context loaded:

### 1.1 Check for HANDOFF.md
Verify that `docs/ai-context/HANDOFF.md` has been attached to this conversation. If not present:
```
❌ ERROR: HANDOFF.md not found or not attached.

Please attach the handoff document before continuing:
- Expected location: docs/ai-context/HANDOFF.md
- This file is critical for context reconstruction
- Cannot proceed without it
```

### 1.2 Validate Document Structure
Quickly scan the document to ensure it contains the expected sections:
- Task sections with status indicators
- Accomplishments and current status
- Next steps and action items
- Key files and context

If the document appears incomplete or corrupted, note this and proceed with caution, requesting clarification from the user about missing context.

## Step 2: Perform Multi-Pass Analysis

Read through the HANDOFF.md document using a systematic multi-pass approach, with each pass extracting different layers of information:

### Pass 1: High-Level Situation Assessment (Breadth Pass)

Skim through the entire document to build a bird's-eye view:

**Identify Active Work Streams:**
- How many distinct tasks or areas of work are in progress?
- What are their current statuses (IN_PROGRESS, BLOCKED, TESTING, etc.)?
- Which ones are high priority vs. future considerations?

**Assess Overall Project Health:**
- Is work progressing smoothly or are there significant blockers?
- What's the general momentum (high/medium/low)?
- Are there any critical issues that need immediate attention?

**Map the Territory:**
- What parts of the codebase are being actively modified?
- What external dependencies or systems are involved?
- What's the testing coverage situation?

Generate a mental summary:
```
Project Situation Summary:
- Active work streams: [number] tasks in progress
- Primary focus: [main area of development]
- Overall health: [healthy/moderate concerns/critical issues]
- Immediate blockers: [yes/no - description if yes]
- Momentum: [HIGH/MEDIUM/LOW]
```

### Pass 2: Deep Dive on Priority Work (Depth Pass)

For each IN_PROGRESS or high-priority task, perform detailed analysis:

**2.1 Reconstruct the Problem Space**
- **Original Goal**: What is this task trying to achieve?
- **Current Understanding**: What's been learned about the problem?
- **Constraints**: What limitations or requirements exist?
- **Success Criteria**: How will we know when this is complete?

**2.2 Absorb All Accomplishments**
Read through everything that was accomplished. For each item:
- What was the specific change made?
- Which files were affected and how?
- What technical approach was taken?
- Why was this particular solution chosen?

Create a mental map:
```
For [Task Name]:
  ✅ Completed: [list of achievements]
  📁 Modified files: [files with role of each]
  🎯 Remaining: [what's left to do]
```

**2.3 Internalize Key Insights and Decisions**
This is crucial. For each documented decision or insight:
- **Understand the reasoning**: Why was this approach chosen?
- **Know the alternatives**: What else was considered and why rejected?
- **Recognize trade-offs**: What was sacrificed or deferred?
- **See implications**: How does this affect future work?

You must be able to explain these decisions as if you made them yourself.

**2.4 Learn from Failed Approaches**
Study every documented failure carefully:
- **What was tried**: Understand the exact approach
- **Why it seemed reasonable**: The logic that motivated it
- **How it failed**: The specific error or problem
- **Root cause**: Why it fundamentally couldn't work
- **Key lesson**: What this teaches about the system

Commit these to memory to avoid repetition. Think: "If I'm tempted to try [X], I should remember that [failure lesson]."

**2.5 Understand Current Blockers**
If there are blockers or current issues:
- **Nature of blocker**: Technical issue, missing information, external dependency?
- **What's been tried**: Previous debugging or resolution attempts
- **Current theory**: What do we think is causing this?
- **Next diagnostic steps**: What should be investigated next?

**2.6 Absorb Testing State**
Know exactly what's tested and what isn't:
- **Passing tests**: What functionality is verified working
- **Failing tests**: What's broken and specific error messages
- **Untested areas**: What needs test coverage
- **Manual testing**: What scenarios have been checked

This tells you what's safe to build on vs. what's risky.

### Pass 3: Pattern Recognition (Architecture Pass)

Extract the mental model of how the system works:

**3.1 Code Patterns and Conventions**
Internalize the project's coding style:
- How are things named? (functions, variables, files)
- What architectural patterns are used? (MVC, services, repositories)
- How is error handling done?
- Where do tests go and how are they structured?
- How are dependencies organized?

You need to write code that fits naturally into this project.

**3.2 File Relationships and Dependencies**
Build a mental graph of the codebase:
- Which files import which other files?
- What are the key execution flows?
- How does data move through the system?
- What are the critical configuration files?

Example mental model:
```
Component Architecture:
  src/
    ├─ core/ (business logic, no external deps)
    ├─ services/ (uses core, talks to external APIs)
    ├─ api/ (HTTP layer, uses services)
    └─ config/ (loaded by everything)
  
  Flow: api → services → core
  Tests: mirror src structure, use mocks for services
```

**3.3 Technology Stack Understanding**
Know what technologies are in play:
- Primary language and version
- Key frameworks and libraries
- Database or data storage approach
- Testing frameworks
- Build and deployment tools

**3.4 Gotchas and Pitfalls Awareness**
Memorize the documented pitfalls:
- What are the known traps in this codebase?
- What surprising behaviors have been discovered?
- What configuration details are easy to miss?
- What anti-patterns should be avoided?

Keep these at top of mind to avoid stumbling into them.

### Pass 4: Action Planning (Execution Pass)

Transform documented next steps into immediate execution readiness:

**4.1 Parse Next Steps Hierarchy**
Organize the documented next steps by:
- **Immediate priority**: Must be done first
- **Sequential order**: What depends on what
- **Parallel opportunities**: What can be done simultaneously
- **Future considerations**: What comes later

**4.2 Understand Each Action in Detail**
For the immediate next actions:
- **Exact objective**: What needs to be accomplished
- **Specific procedure**: Step-by-step how to do it
- **File locations**: Exact paths and line numbers if provided
- **Commands to run**: Copy-paste ready commands
- **Verification method**: How to confirm it worked
- **Expected outcome**: What success looks like

You should be able to start executing immediately without additional research.

**4.3 Identify Prerequisites**
Before starting, ensure you have:
- Access to all necessary files
- Understanding of all context needed
- Any tools or dependencies available
- Clear success criteria

**4.4 Plan Validation Strategy**
Know how you'll verify your work:
- What tests to run after changes
- What manual checks to perform
- What output or behavior to observe
- When to consider the step complete

## Step 3: Synthesize Mental Model

After the multi-pass analysis, construct a complete mental model:

### 3.1 System Architecture Understanding
You should be able to explain:
- How the system is structured overall
- What the major components are and their roles
- How data flows through the system
- Where different types of logic live (business rules, data access, presentation)

### 3.2 Current Work Strategy
Understand the approach being taken:
- What's the overall strategy for solving the problem?
- Why is this strategy appropriate?
- What are the key milestones in this strategy?
- Where are we currently in executing this strategy?

### 3.3 Decision Context
For any decisions you might need to make, know:
- What principles guide technical decisions in this project?
- What constraints must be respected?
- What trade-offs are acceptable?
- What patterns should be followed?

### 3.4 Risk Awareness
Understand what could go wrong:
- What are the known fragile areas of the code?
- What dependencies have had issues?
- What assumptions need validation?
- What testing gaps exist?

## Step 4: Activate Working Memory

Bring the most critical information into immediate awareness:

### 4.1 Load Priority Task Context
For the highest-priority task that you'll likely work on first:

**Keep at front of mind:**
- The exact current status (what was just completed, what's next)
- The immediate next action (specific file, function, change needed)
- Why this approach was chosen (the reasoning)
- How to verify success (the test or check)

**Be aware of:**
- What was already tried and failed (to avoid repetition)
- What pitfalls to watch for (documented gotchas)
- What patterns to follow (code conventions)

### 4.2 Prepare File Context
Identify the key files you'll need to look at:
- Which files are most relevant to the immediate work?
- What role does each file play?
- Are there specific sections or functions to focus on?

You might want to actually view these files to fully load their context.

### 4.3 Command Readiness
Have ready the commands you're likely to need:
- Test commands to verify changes
- Build commands if compilation is needed
- Database commands if schema is involved
- Debugging commands for investigation

## Step 5: Verify Context Completeness

Before proceeding with work, validate that you have sufficient context:

### 5.1 Self-Assessment Checklist
Ask yourself these questions:

**Understanding:**
- [ ] Do I understand what we're trying to achieve overall?
- [ ] Do I know why the current approach was chosen?
- [ ] Do I understand how the system is architected?
- [ ] Do I know what was already tried and why it failed?

**Readiness:**
- [ ] Do I know exactly what to do next?
- [ ] Do I know which files to modify and how?
- [ ] Do I know how to verify my changes work?
- [ ] Do I know what pitfalls to avoid?

**Awareness:**
- [ ] Do I know what's tested and what's not?
- [ ] Do I know what code patterns to follow?
- [ ] Do I know what current blockers exist?
- [ ] Do I understand the dependencies between tasks?

### 5.2 Identify Information Gaps
If any checklist item is unchecked, identify what information is missing:
- Can it be found by examining specific files?
- Should the user be asked for clarification?
- Is it documented elsewhere in the project?

Address critical gaps before proceeding with work.

### 5.3 Confidence Assessment
Evaluate your readiness level:

**HIGH CONFIDENCE**: 
- Clear understanding of system and task
- Know exactly what to do next and why
- Aware of pitfalls and patterns
- Ready to execute immediately

**MEDIUM CONFIDENCE**:
- General understanding of the situation
- Some uncertainty about specifics
- May need to examine files for clarity
- Can proceed with some investigation

**LOW CONFIDENCE**:
- Significant gaps in understanding
- Unclear about approach or decisions
- Need substantial clarification
- Should ask user for context before proceeding

Be honest about your confidence level and communicate it.

## Step 6: Generate Context Summary

Produce a concise summary demonstrating your loaded context:

```markdown
# 🧠 Session Context Loaded Successfully

## Situation Awareness

**Project**: [Project name and purpose]
**Current Focus**: [Main area of development]
**Session Continuity**: Resuming from [brief description of where we left off]

---

## What I Understand

### Primary Task: [Task Name]
**Goal**: [What we're trying to achieve]
**Status**: [Current state and completion %]
**Approach**: [The strategy being used and why]

**Recent Progress**:
- [Key accomplishment 1]
- [Key accomplishment 2]
- [Key accomplishment 3]

**Current Blocker** (if any):
[Description of any blocking issue and current understanding of it]

### System Understanding
- **Architecture**: [Brief description of how system is structured]
- **Key Components**: [Main files/modules and their roles]
- **Tech Stack**: [Primary technologies in use]

### Critical Insights
- [Key insight 1 that shapes approach]
- [Key insight 2 about how system works]
- [Key insight 3 from previous debugging]

### Known Pitfalls
- ⚠️ [Pitfall 1 to avoid]
- ⚠️ [Pitfall 2 to watch for]

---

## What I Remember NOT to Do

**Failed Approaches** (will not retry):
1. [Approach that failed] - because [reason it didn't work]
2. [Another failed attempt] - due to [root cause]

---

## Immediate Action Plan

**Next Step** (Priority #1):
[Specific action to take next with clear objective]

**How**:
1. [Precise step 1]
2. [Precise step 2]
3. [Precise step 3]

**Files Involved**:
- `[exact/path/to/file.ext]` - [what I'll modify]

**Verification**:
[How I'll confirm it works]

**Then**: [What comes after this immediate step]

---

## Questions/Uncertainties

[Any gaps in understanding or areas needing clarification - or "None, ready to proceed" if fully clear]

---

## Confidence Level

[HIGH/MEDIUM/LOW] - [Brief explanation of confidence and readiness]

**Ready to Continue**: [YES/NO with brief reasoning]

---
```

## Step 7: Offer Proactive Assistance

Based on the loaded context, immediately offer value:

### 7.1 For Clearly Defined Next Steps
If the next action is well-documented and you have high confidence:
```
I'm ready to continue with [specific next task]. 

I'll [describe what you'll do in one sentence]. This will [describe expected outcome].

Shall I proceed?
```

### 7.2 For Blocked or Unclear Situations
If there's a blocker or uncertainty:
```
I see we're currently blocked on [issue description].

Based on the previous attempts, I have some ideas:
1. [Potential approach 1]
2. [Potential approach 2]

Would you like me to investigate [most promising option], or do you have guidance on direction?
```

### 7.3 For Multiple Priority Items
If there are several high-priority tasks:
```
I see there are [N] priority items:
1. [Task 1 brief description]
2. [Task 2 brief description]
3. [Task 3 brief description]

Based on the dependencies, I recommend starting with [Task X] because [reasoning].

Does this align with your priorities, or should I focus elsewhere?
```

### 7.4 For Review or Validation Needs
If previous work needs validation:
```
Before continuing, I notice that [recent change] should be verified.

I can:
1. Run the test suite to confirm everything passes
2. Review the implementation against requirements
3. Check for any edge cases that might have been missed

Should I do a validation pass first, or proceed with new work?
```

## Step 8: Activate Task-Specific Context

If the user responds confirming direction, dive deeper into that specific task:

### 8.1 Load Specific File Context
If you haven't already, view the key files for the task:
```bash
view path/to/primary/file.ext
```

### 8.2 Review Related Context
Examine any related files, tests, or configuration that will inform your work.

### 8.3 Refresh on Patterns
Review the code style in the files you'll be modifying to ensure your changes will be consistent.

### 8.4 Prepare Work Environment
If needed, run any preparatory commands:
- Pull latest code (if in a repo)
- Install dependencies (if changed)
- Start development server (if needed)
- Run tests to establish baseline (if appropriate)

## Step 9: Continuous Context Awareness

As you work, maintain awareness of the handoff context:

### 9.1 Stay Aligned with Strategy
Ensure your actions align with the documented approach and reasoning.

### 9.2 Apply Learned Lessons
Remember the failed approaches and avoid similar paths.

### 9.3 Follow Established Patterns
Write code that fits the project's conventions and architecture.

### 9.4 Track New Learnings
As you discover new information, remember it will need to be added to the handoff when you conclude work.

## Step 10: Context Loading Anti-Patterns to Avoid

**Don't:**
- ❌ Skim the handoff superficially and claim to understand
- ❌ Start working immediately without validating your understanding
- ❌ Ignore documented failed approaches and retry them
- ❌ Make assumptions that contradict documented insights
- ❌ Violate established code patterns without good reason
- ❌ Skip verification steps that were documented
- ❌ Proceed with low confidence without asking for clarification

**Do:**
- ✅ Read thoroughly and build a complete mental model
- ✅ Validate your understanding before taking action
- ✅ Respect the lessons from previous failures
- ✅ Build on documented insights and decisions
- ✅ Follow established patterns and conventions
- ✅ Execute the validation strategy as documented
- ✅ Ask for clarification when uncertain

---

## Quality Standards for Context Loading

A successful context load means:
- You can explain the system architecture clearly
- You know exactly what to do next and why
- You understand why previous decisions were made
- You're aware of what didn't work before
- You can start work immediately without additional research
- You feel confident in the direction
- You know how to verify your work

---

## Emergency: Incomplete or Missing Context

If the HANDOFF.md is missing critical information:

1. **Be transparent**: Explain what context is missing
2. **Don't guess**: Clearly state what you don't know
3. **Ask specifically**: Request the exact information needed
4. **Proceed cautiously**: Only move forward on what you clearly understand
5. **Document the gap**: Note what context should be added for next time

Example:
```
⚠️ Context Gap Identified

I've loaded the available handoff context, but I'm missing critical information about:
- [Specific missing context 1]
- [Specific missing context 2]

Without this, I cannot confidently proceed with [task] because [reasoning].

Can you provide:
1. [Specific question 1]
2. [Specific question 2]

Alternatively, I could investigate by [alternative approach], but this might duplicate previous work.
```

---

Now execute this context loading process with the attached HANDOFF.md document and prepare to continue the work seamlessly.