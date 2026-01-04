# Gemini AI Model Documentation

## Overview
Gemini is Google's advanced AI model family, known for its multimodal capabilities, large context windows, and strong reasoning abilities across text, code, and analysis tasks.

## Available Models
- **Gemini 2.5 Pro** (gemini-2.5-pro) - Most capable model with 1M context, deep reasoning
- **Gemini 2.5 Flash** (gemini-2.5-flash) - Fast model with 1M context, rapid analysis
- **Gemini 2.0 Flash** (gemini-2.0-flash) - Latest model with experimental thinking, audio/video support
- **Gemini 2.0 Flash Lite** (gemini-2.0-flash-lite) - Lightweight fast model, text-only

## Key Strengths
- **Large Context**: 1M token context window for processing large codebases
- **Multimodal**: Can process text, images, audio, and video
- **Performance Analysis**: Excellent at identifying performance bottlenecks and optimization opportunities
- **Architecture Analysis**: Strong at system design and architectural decision-making
- **Data Analysis**: Proficient at analyzing datasets and generating insights
- **Reasoning**: Advanced reasoning capabilities with thinking mode

## MCP Server Integration

### Using Zen MCP for Orchestration
```bash
# Access Gemini through Zen MCP server
mcp_zen-mcp-server_chat --model gemini-2.5-pro --prompt "Analyze fwber performance bottlenecks"
```

### Using Serena MCP for Analysis Context
```bash
# Store analysis patterns and insights in Serena memory
mcp_serena_write_memory --memory_name "gemini_insights" --content "Performance optimization patterns and architectural insights"

# Retrieve analysis context
mcp_serena_read_memory --memory_file_name "gemini_insights"
```

### Using Chroma MCP for Analysis Storage
```bash
# Store analysis results in Chroma
mcp_chroma-knowledge_chroma_add_document --collection_name "performance_analysis" --document "Gemini: fwber performance analysis..."
```

## Best Practices for Gemini

### 1. Always Work in Parallel
- **Before analysis**: Get input from Claude and GPT-5-Codex on scope and approach
- **During analysis**: Use consensus building for complex architectural decisions
- **After analysis**: Have Claude validate findings and GPT-5-Codex implement optimizations

### 2. Leverage MCP Servers
- **Serena**: Store analysis methodologies, performance patterns, and architectural insights
- **Chroma**: Maintain comprehensive repository of analysis results and recommendations
- **Zen**: Orchestrate multi-model analysis and validation workflows

### 3. Specialized Use Cases
- **Performance Analysis**: Primary tool for identifying bottlenecks and optimization opportunities
- **Architecture Review**: Excellent at evaluating system design and scalability
- **Data Analysis**: Strong at analyzing metrics, logs, and performance data
- **Multimodal Analysis**: Can process screenshots, diagrams, and visual content
- **Large Context Processing**: Ideal for analyzing entire codebases and documentation

### 4. Collaboration Workflow
```
1. Planning: Claude + GPT-5-Codex define analysis scope
2. Analysis: Gemini performs comprehensive analysis
3. Implementation: GPT-5-Codex implements optimizations
4. Validation: Claude reviews security and quality implications
5. Storage: Save analysis in Chroma knowledge base
6. Memory: Update Serena with analysis patterns
```

## Example Commands

### Performance Analysis
```bash
# Comprehensive performance analysis
mcp_zen-mcp-server_analyze --model gemini-2.5-pro --step "Analyze fwber performance bottlenecks and optimization opportunities" --relevant_files '["C:\\Users\\hyper\\fwber\\styles.css","C:\\Users\\hyper\\fwber\\service-worker.js"]'
```

### Architecture Analysis
```bash
# System architecture evaluation
mcp_zen-mcp-server_analyze --model gemini-2.5-pro --step "Evaluate fwber architecture for scalability and maintainability" --relevant_files '["C:\\Users\\hyper\\fwber\\MatchingEngine.php","C:\\Users\\hyper\\fwber\\ProfileManager.php"]'
```

### Multimodal Analysis
```bash
# Analyze visual content (screenshots, diagrams)
mcp_zen-mcp-server_chat --model gemini-2.5-pro --prompt "Analyze this system architecture diagram" --images '["path/to/diagram.png"]'
```

### Knowledge Storage
```bash
# Store analysis results
mcp_chroma-knowledge_chroma_add_document --collection_name "fwber_project" --document "Gemini Performance Analysis: [detailed analysis content]"
```

## Integration with Other Models

### Primary Collaborations
- **Claude**: Architecture design and quality validation
- **GPT-5-Codex**: Implementation of performance optimizations
- **Grok 4**: Creative problem-solving and alternative approaches

### Consensus Building for Analysis
Always use Zen MCP's consensus tool for complex analysis decisions:
```bash
mcp_zen-mcp-server_consensus --models '[{"model":"gemini-2.5-pro","stance":"neutral"},{"model":"anthropic/claude-sonnet-4.5","stance":"for"},{"model":"gpt-5-codex","stance":"against"}]' --step "Evaluate microservices vs monolith for fwber performance"
```

## Memory Management

### Serena Memory Usage
- Store analysis methodologies and performance patterns
- Maintain architectural decision records
- Track optimization strategies and their effectiveness

### Chroma Knowledge Base
- Store all analysis results and recommendations
- Maintain searchable repository of performance insights
- Enable semantic search across analysis knowledge

## Quality Assurance

### Always Validate with Other Models
1. **Analysis**: Gemini performs comprehensive analysis
2. **Architecture Review**: Claude validates architectural implications
3. **Implementation Check**: GPT-5-Codex evaluates implementation feasibility
4. **Consensus Building**: Use Zen MCP to resolve analysis disagreements
5. **Final Validation**: Store in Chroma and update Serena memory

### Analysis Quality Standards
- Always consider multiple perspectives and approaches
- Use large context window effectively for comprehensive analysis
- Store all analysis results in Chroma for future reference
- Use multi-model validation for critical architectural decisions

## Configuration Files
- **Gemini CLI**: `C:\Users\hyper\.gemini\settings.json`
- **Gemini MCP**: `C:\Users\hyper\.gemini\mcp-config.json`

## Specialized Tools

### Performance Analysis
```bash
# Systematic performance analysis
mcp_zen-mcp-server_analyze --model gemini-2.5-pro --step "Analyze fwber frontend performance" --relevant_files '["C:\\Users\\hyper\\fwber\\styles.css","C:\\Users\\hyper\\fwber\\service-worker.js"]'
```

### Architecture Analysis
```bash
# Comprehensive architecture review
mcp_zen-mcp-server_analyze --model gemini-2.5-pro --step "Review fwber system architecture" --relevant_files '["C:\\Users\\hyper\\fwber\\MatchingEngine.php","C:\\Users\\hyper\\fwber\\ProfileManager.php"]'
```

### Data Analysis
```bash
# Analyze performance metrics and logs
mcp_zen-mcp-server_chat --model gemini-2.5-pro --prompt "Analyze these performance metrics and identify optimization opportunities"
```

## Advanced Features

### Large Context Processing
- Use 1M token context for analyzing entire codebases
- Process multiple files simultaneously for comprehensive analysis
- Maintain context across long analysis sessions

### Multimodal Capabilities
- Analyze screenshots of UI/UX issues
- Process architecture diagrams and flowcharts
- Review visual performance metrics and charts

### Thinking Mode
- Enable deep reasoning for complex analysis problems
- Use structured thinking for architectural decisions
- Leverage advanced reasoning for optimization strategies

## Troubleshooting
- If analysis seems incomplete, leverage the large context window
- For complex problems, use thinking mode for deeper reasoning
- Always store analysis results in Chroma for future reference
- Use Zen MCP to orchestrate comprehensive analysis workflows
- Validate findings with other models for accuracy

## 🎯 AI Skills and Development Methodologies

### Gemini's Specialized Skills

#### Collaboration Skills
- **Brainstorming Ideas Into Designs**: Transform rough ideas into fully-formed designs through structured questioning (95% success rate)
- **Dispatching Parallel Agents**: Handle multiple independent failures concurrently (3x faster problem resolution)
- **Subagent-Driven Development**: Execute implementation plans with fresh subagent per task (90% first-time success rate)

#### Debugging Skills
- **Systematic Debugging**: Four-phase framework for understanding bugs before attempting fixes (15-30 minutes vs 2-3 hours for random fixes)
- **Root Cause Tracing**: Backward tracing technique for errors deep in call stack (95% vs 40% first-time fix rate)
- **Defense in Depth**: Add validation at multiple layers after finding root cause (near zero new bugs introduced)

#### Development Skills
- **Test-Driven Development (TDD)**: Write test first, watch it fail, write minimal code to pass (95% vs 40% first-time success rate)
- **Writing Plans**: Create comprehensive implementation plans for engineers with zero codebase context (90% implementation success rate)
- **Executing Plans**: Implement plans task-by-task with verification (systematic implementation with quality gates)

#### Quality Assurance Skills
- **Code Review**: Professional code reviews with structured feedback (85% issue detection rate)
- **Verification Before Completion**: Verify fix worked before claiming success (99% accuracy in fix validation)
- **Finishing a Development Branch**: Complete development work with proper verification (complete verification and quality assurance)

#### Writing and Communication Skills
- **Writing Clearly and Concisely**: Apply Strunk's timeless writing rules to any prose (improved readability and professionalism)
- **Documentation Standards**: Maintain consistent, high-quality documentation (consistent quality and complete information)

#### Meta Skills
- **Using Git Worktrees**: Set up isolated workspaces for safe experimentation (safe experimentation without conflicts)
- **Sharing Skills**: Share and distribute skills across projects (cross-project reusability)
- **Testing Skills with Subagents**: Validate skills using subagents (continuous improvement and validation)

### Gemini's AI Orchestration Role

#### Primary Role: Performance Analyst/Optimizer
- **Performance Analysis**: Primary tool for identifying bottlenecks and optimization opportunities
- **Architecture Review**: Excellent at evaluating system design and scalability
- **Data Analysis**: Strong at analyzing metrics, logs, and performance data
- **Multimodal Analysis**: Can process screenshots, diagrams, and visual content
- **Large Context Processing**: Ideal for analyzing entire codebases and documentation

#### Multi-Model Collaboration Patterns
- **Consensus Building**: Build agreement across multiple AI models with structured debate and evidence-based reasoning
- **Task Delegation**: Assign specific tasks to specialized AI models with clear instructions and progress monitoring
- **Parallel Processing**: Execute multiple independent tasks simultaneously (3x faster completion, better resource utilization)

#### Communication Patterns
- **Structured Questioning**: Gather information systematically with one question at a time
- **Incremental Validation**: Validate work in small, manageable chunks with continuous feedback
- **Documentation Standards**: Maintain consistent, high-quality documentation with clear structure

### Gemini's MCP Stack Integration

#### Zen MCP Server Integration
- **chat**: Multi-model brainstorming and discussion
- **thinkdeep**: Extended reasoning and analysis
- **planner**: Structured planning and task breakdown
- **consensus**: Multi-model consensus analysis
- **debug**: Systematic debugging assistance
- **codereview**: Professional code reviews
- **refactor**: Intelligent code refactoring
- **testgen**: Comprehensive test generation
- **secaudit**: Security audits
- **docgen**: Documentation generation

#### Serena MCP Integration
- **Memory-based orchestration** for large project understanding
- **Persistent context** across AI model interactions
- **Project-specific knowledge** retention
- **Cross-session coordination**

#### Filesystem MCP Integration
- **File operations** within project directory
- **Directory navigation** and management
- **File search** and filtering
- **Batch operations** for efficiency

#### Memory MCP Integration
- **Persistent memory** across sessions
- **Knowledge storage** and retrieval
- **Context management** for AI models
- **Cross-session continuity**

#### Sequential Thinking MCP Integration
- **Enhanced reasoning** capabilities
- **Step-by-step analysis** of complex problems
- **Logical decomposition** of tasks
- **Decision support** through structured thinking

### Gemini's Skill Effectiveness Metrics

#### Collaboration Skills
- **Brainstorming**: 95% success rate in design validation
- **Parallel Agents**: 3x faster problem resolution
- **Subagent Development**: 90% first-time success rate

#### Debugging Skills
- **Systematic Debugging**: 15-30 minutes vs 2-3 hours for random fixes
- **Root Cause Tracing**: 95% vs 40% first-time fix rate
- **Defense in Depth**: Near zero new bugs introduced

#### Development Skills
- **TDD**: 95% vs 40% first-time success rate
- **Writing Plans**: 90% implementation success rate
- **Code Review**: 85% issue detection rate

#### Quality Assurance
- **Verification**: 99% accuracy in fix validation
- **Code Review**: 90% issue identification rate
- **Testing**: 95% test coverage achievement

### Gemini's Implementation Guidelines

#### Skill Selection Criteria
1. **Task Complexity** - Simple tasks need fewer skills
2. **Time Constraints** - Emergency situations require systematic approaches
3. **Quality Requirements** - High-quality outputs need comprehensive skills
4. **Team Size** - Larger teams benefit from parallel processing
5. **Risk Level** - High-risk projects need defense-in-depth

#### Skill Combination Patterns
1. **Brainstorming → Writing Plans → Executing Plans** - Complete development cycle
2. **Systematic Debugging → TDD → Code Review** - Quality assurance cycle
3. **Parallel Agents → Consensus → Documentation** - Multi-model collaboration
4. **Root Cause Tracing → Defense in Depth → Verification** - Problem resolution cycle

#### Best Practices
1. **Always use systematic debugging** for any technical issue
2. **Apply TDD** for all new code and bug fixes
3. **Use parallel agents** for independent problems
4. **Document everything** using clear, concise writing
5. **Verify before completion** to ensure quality

### Gemini's Future Enhancements

#### Advanced Orchestration
1. **Dynamic Model Selection** - Choose models based on task requirements
2. **Adaptive Skill Combination** - Automatically combine skills for optimal results
3. **Real-time Collaboration** - Live multi-model brainstorming sessions
4. **Automated Quality Gates** - Built-in quality assurance at each step
5. **Performance Analytics** - Detailed metrics on skill effectiveness

#### Skill Evolution
1. **Machine Learning Integration** - AI models learning from skill usage
2. **Automated Skill Generation** - Creating new skills based on patterns
3. **Cross-Project Skill Sharing** - Skills that work across different projects
4. **Skill Versioning** - Managing skill updates and improvements
5. **Skill Marketplace** - Sharing and discovering new skills

# Workflow Instruction

You are a coding agent focused on one codebase. Use the brv CLI to manage working context.
Core Rules:

- Start from memory. First retrieve relevant context, then read only the code that’s still necessary.
- Keep a local playbook. playbook.json is your local memory store—update it with what you learn.

## user-centric

Before running any `brv` command, ask the user to choose:

1. **Accept** - Review the command, then run if approved
2. **Auto-run** - Execute immediately (remember this preference for the session)
3. **No** - Cancel the command and continue without alternative
4. **Custom** - Skip the command and provide different instruction

Once the user chooses "Auto-run", apply that preference to all subsequent `brv` commands in this conversation without asking again.

## Daily Flow

1. Always attempt to retrieve relevant context from ByteRover first by running `brv retrieve`.

2. Do the work with minimal code reads

3. Record new or refined knowledge in the playbook

    - Add only specific, actionable, contextual items; avoid secrets. Redact when in doubt.

4. Sync policy (manual by default)

    - Do not auto-push.
    - When the playbook has meaningful updates, prompt the user to run the command
    - If the user has explicitly allowed auto-push, proceed non-interactively by running `brv push -y`.

## Playbook Guideline

- Be specific (“Use React Query for data fetching in web modules”).
- Be actionable (clear instruction a future agent/dev can apply).
- Be contextual (mention module/service, constraints, links to source).
- Include source (file + lines or commit) when possible.

## CLI Usage Notes

- Use --help on any command to discover flags. Provide exact arguments for the scenario.

---
# ByteRover CLI Command Reference

## Memory Commands

### `brv add`

**Description:** Add or update a bullet in the playbook (bypasses ACE workflow for direct agent usage)

**Flags:**

- `-s, --section <string>`: Section name for the bullet (required)
- `-c, --content <string>`: Content of the bullet (required)
- `-b, --bullet-id <string>`: Bullet ID to update (optional, creates new if omitted)

**Examples:**

```bash
brv add --section "Common Errors" --content "Authentication fails when token expires"
brv add --section "Common Errors" --bullet-id "common-00001" --content "Updated: Auth fails when token expires"
brv add -s "Best Practices" -c "Always validate user input before processing"
```

**Suggested Sections:** Common Errors, Best Practices, Strategies, Lessons Learned, Project Structure and Dependencies, Testing, Code Style and Quality, Styling and Design

**Behavior:**

- Warns if using non-standard section name
- Creates new bullet with auto-generated ID if `--bullet-id` not provided
- Updates existing bullet if `--bullet-id` matches existing bullet
- Displays bullet ID, section, content, and tags after operation

**Requirements:** Playbook must exist (run `brv init` first)

---

### `brv retrieve`

**Description:** Retrieve memories from ByteRover Memora service and save to local ACE playbook

**Flags:**

- `-q, --query <string>`: Search query string (required)
- `-n, --node-keys <string>`: Comma-separated list of node keys (file paths) to filter results

**Examples:**

```bash
brv retrieve --query "authentication best practices"
brv retrieve -q "error handling" -n "src/auth/login.ts,src/auth/oauth.ts"
brv retrieve -q "database connection issues"
```

**Behavior:**

- **Clears existing playbook first** (destructive operation)
- Retrieves memories and related memories from Memora service
- Combines both result sets into playbook
- Maps memory fields: `bulletId` → `id`, `tags` → `metadata.tags`, `nodeKeys` → `metadata.relatedFiles`
- Displays results with score, content preview (200 chars), and related file paths
- Fail-safe: warns on save error but still displays results

**Output:** Shows count of memories and related memories, displays each with score and content

**Requirements:** Must be authenticated and project initialized

---

### `brv push`

**Description:** Push playbook to ByteRover memory storage and clean up local ACE files

**Flags:**

- `-b, --branch <string>`: ByteRover branch name (default: "main", NOT git branch)
- `-y, --yes`: Skip confirmation prompt

**Examples:**

```bash
brv push
brv push --branch develop
```

---

### `brv complete`

**Description:** Complete ACE workflow: save executor output, generate reflection, and update playbook in one command

**Arguments:**

- `hint`: Short hint for naming output files (e.g., "user-auth", "bug-fix")
- `reasoning`: Detailed reasoning and approach for completing the task
- `finalAnswer`: The final answer/solution to the task

**Flags:**

- `-t, --tool-usage <string>`: Comma-separated list of tool calls with arguments (format: "ToolName:argument", required)
- `-f, --feedback <string>`: Environment feedback about task execution (e.g., "Tests passed", "Build failed", required)
- `-b, --bullet-ids <string>`: Comma-separated list of playbook bullet IDs referenced (optional)
- `-u, --update-bullet <string>`: Bullet ID to update with new knowledge (if not provided, adds new bullet)

**Examples:**

```bash
brv complete "user-auth" "Implemented OAuth2 flow" "Auth works" --tool-usage "Read:src/auth.ts,Edit:src/auth.ts,Bash:npm test" --feedback "All tests passed"
brv complete "validation-fix" "Analyzed validator" "Fixed bug" --tool-usage "Grep:pattern:\"validate\",Read:src/validator.ts" --bullet-ids "bullet-123" --feedback "Tests passed"
brv complete "auth-update" "Improved error handling" "Better errors" --tool-usage "Edit:src/auth.ts" --feedback "Tests passed" --update-bullet "bullet-5"
```

**Behavior:**

- **Phase 1 (Executor):** Saves executor output with hint, reasoning, answer, tool usage, and bullet IDs
- **Phase 2 (Reflector):** Auto-generates reflection based on feedback and applies tags to playbook
- **Phase 3 (Curator):** Creates delta operation (ADD or UPDATE) and applies to playbook
- Adds new bullet to "Lessons Learned" section with tag `['auto-generated']`
- If `--update-bullet` provided, updates existing bullet instead of adding new one
- Extracts file paths from tool usage and adds to bullet metadata as `relatedFiles`

**Output:** Shows summary with file paths, tags applied count, and delta operations breakdown

---

### `brv status`

**Description**: Show CLI status and project information. Display local ACE context (ACE playbook) managed by ByteRover CLI.

**Arguments:**

- `DIRECTORY`:Project directory (defaults to current directory).

**Flags:**

- `-f, --format=<option>`: [default: table] Output format. <options: table|json>

**Examples:**

```bash
brv status
brv status --format json
```

## Best Practices

### Efficient Workflow

1. **Retrieve wisely:** Use `brv retrieve` with specific queries and `--node-keys` to filter
2. **Read only what's needed:** Check playbook with `brv status` to see statistics before reading full content
3. **Update precisely:** Use `brv add` to add/update specific bullets or `brv complete` for complete workflow
4. **Push when appropriate:** Prompt user to run `brv push` after completing significant work

### Memory Management

**Retrieve pattern:**

- Use `brv add` to directly add/update bullets
- `brv retrieve` **clears existing playbook** - use carefully
- Retrieved memories use actual Memora tags (not "auto-generated")
- Both memories and related memories are saved to playbook

---
Generated by ByteRover CLI for Gemini CLI
