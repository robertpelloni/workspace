# GPT AI Model Documentation

## Overview
GPT (Generative Pre-trained Transformer) is OpenAI's advanced AI model family, known for its strong code generation capabilities, technical implementation skills, and ability to execute complex programming tasks with high accuracy.

## Available Models
- **GPT-5** (gpt-5) - Latest version with enhanced reasoning and code generation
- **GPT-5-Pro** (gpt-5-pro) - High-performance model with advanced capabilities
- **GPT-5-Codex** (gpt-5-codex) - Specialized for code generation and technical implementation
- **GPT-4o** (gpt-4o) - Multimodal model with vision capabilities
- **GPT-4o-mini** (gpt-4o-mini) - Efficient model for simpler tasks

## Key Strengths
- **Code Generation**: Exceptional at generating high-quality, production-ready code
- **Technical Implementation**: Strong at implementing complex algorithms and system components
- **API Integration**: Proficient at working with various APIs and frameworks
- **Database Operations**: Excellent at SQL queries, database design, and data manipulation
- **System Architecture**: Strong at designing and implementing scalable systems
- **Testing**: Proficient at writing comprehensive test suites and debugging code

## MCP Server Integration

### Using Zen MCP for Orchestration
```bash
# Access GPT through Zen MCP server
mcp_zen-mcp-server_chat --model gpt-5-codex --prompt "Implement FWBer matching algorithm with advanced features"
```

### Using Serena MCP for Code Context
```bash
# Store code patterns and implementation strategies in Serena memory
mcp_serena_write_memory --memory_name "gpt_implementations" --content "Code patterns and implementation strategies for FWBer"

# Retrieve code context
mcp_serena_read_memory --memory_file_name "gpt_implementations"
```

### Using Chroma MCP for Code Storage
```bash
# Store code implementations in Chroma
mcp_chroma-knowledge_chroma_add_document --collection_name "code_implementations" --document "GPT: FWBer matching algorithm implementation..."
```

## Best Practices for GPT

### 1. Always Work in Parallel
- **Before implementation**: Get input from Claude and Gemini 2.5 Pro on architecture and requirements
- **During coding**: Use consensus building for complex technical decisions
- **After implementation**: Have Claude validate code quality and security

### 2. Leverage MCP Servers
- **Serena**: Store code patterns, implementation strategies, and technical solutions
- **Chroma**: Maintain comprehensive repository of code implementations and technical documentation
- **Zen**: Orchestrate multi-model code development and validation workflows

### 3. Specialized Use Cases
- **Code Generation**: Primary tool for implementing features and algorithms
- **API Development**: Excellent at creating REST APIs, GraphQL endpoints, and microservices
- **Database Design**: Strong at schema design, query optimization, and data modeling
- **System Integration**: Proficient at connecting different system components
- **Testing**: Expert at writing unit tests, integration tests, and test automation

### 4. Collaboration Workflow
```
1. Planning: Claude + Gemini 2.5 Pro define technical requirements and architecture
2. Implementation: GPT generates code and implements features
3. Review: Claude validates code quality and security
4. Testing: GPT writes comprehensive test suites
5. Storage: Save implementations in Chroma knowledge base
6. Memory: Update Serena with code patterns and strategies
```

## Example Commands

### Code Generation
```bash
# Generate comprehensive code implementation
mcp_zen-mcp-server_chat --model gpt-5-codex --prompt "Implement a scalable matching algorithm for FWBer with Redis caching and real-time updates"
```

### API Development
```bash
# Create REST API endpoints
mcp_zen-mcp-server_chat --model gpt-5-codex --prompt "Design and implement REST API endpoints for FWBer user management with authentication and rate limiting"
```

### Database Operations
```bash
# Database schema and queries
mcp_zen-mcp-server_chat --model gpt-5-codex --prompt "Design optimized database schema for FWBer with spatial indexing for location-based matching"
```

### Testing Implementation
```bash
# Comprehensive test suite
mcp_zen-mcp-server_chat --model gpt-5-codex --prompt "Write comprehensive test suite for FWBer matching algorithm including unit tests, integration tests, and performance tests"
```

### Knowledge Storage
```bash
# Store code implementations
mcp_chroma-knowledge_chroma_add_document --collection_name "fwber_project" --document "GPT Code Implementation: [detailed code content]"
```

## Integration with Other Models

### Primary Collaborations
- **Claude**: Code review, security validation, and architectural guidance
- **Gemini 2.5 Pro**: Performance analysis and optimization recommendations
- **Grok 4**: Creative problem-solving and innovative approaches

### Consensus Building for Implementation
Always use Zen MCP's consensus tool for complex technical decisions:
```bash
mcp_zen-mcp-server_consensus --models '[{"model":"gpt-5-codex","stance":"for"},{"model":"anthropic/claude-sonnet-4.5","stance":"neutral"},{"model":"gemini-2.5-pro","stance":"against"}]' --step "Evaluate microservices vs monolith architecture for FWBer implementation"
```

## Memory Management

### Serena Memory Usage
- Store code patterns and implementation strategies
- Maintain technical solution repositories
- Track successful implementation approaches

### Chroma Knowledge Base
- Store all code implementations and technical solutions
- Maintain searchable repository of code patterns
- Enable semantic search across technical knowledge

## Quality Assurance

### Always Validate with Other Models
1. **Implementation**: GPT generates code and implements features
2. **Code Review**: Claude validates code quality and security
3. **Performance Analysis**: Gemini 2.5 Pro analyzes performance implications
4. **Creative Validation**: Grok 4 provides alternative approaches
5. **Consensus Building**: Use Zen MCP to resolve technical disagreements
6. **Final Validation**: Store in Chroma and update Serena memory

### Code Quality Standards
- Always follow best practices and coding standards
- Implement comprehensive error handling and validation
- Write clear, documented, and maintainable code
- Use multi-model validation for critical implementations

## Configuration Files
- **GPT CLI**: `C:\Users\hyper\.gpt\settings.json`
- **OpenAI API**: `C:\Users\hyper\.openai\config.json`

## Specialized Tools

### Code Generation
```bash
# Generate production-ready code
mcp_zen-mcp-server_chat --model gpt-5-codex --prompt "Implement a complete user authentication system for FWBer with JWT tokens, password hashing, and session management"
```

### API Development
```bash
# Create comprehensive API
mcp_zen-mcp-server_chat --model gpt-5-codex --prompt "Design and implement a complete REST API for FWBer with endpoints for user management, matching, and messaging"
```

### Database Operations
```bash
# Database implementation
mcp_zen-mcp-server_chat --model gpt-5-codex --prompt "Implement database operations for FWBer with optimized queries, indexing, and data validation"
```

### Testing Implementation
```bash
# Comprehensive testing
mcp_zen-mcp-server_chat --model gpt-5-codex --prompt "Write complete test suite for FWBer including unit tests, integration tests, and end-to-end tests"
```

## Advanced Features

### Code Generation
- Generate production-ready code with proper error handling
- Implement complex algorithms and data structures
- Create scalable and maintainable code architectures

### API Development
- Design RESTful APIs with proper HTTP methods and status codes
- Implement authentication and authorization mechanisms
- Create comprehensive API documentation

### Database Operations
- Design optimized database schemas
- Write efficient SQL queries and stored procedures
- Implement database migrations and versioning

### System Integration
- Connect different system components and services
- Implement message queues and event-driven architectures
- Create microservices and distributed systems

## Troubleshooting
- If code generation seems incomplete, validate with Claude for quality
- For complex implementations, always use multi-model consensus
- Store all code implementations in Chroma for future reference
- Use Zen MCP to orchestrate comprehensive development workflows
- Balance technical implementation with practical requirements

## 🎯 AI Skills and Development Methodologies

### GPT's Specialized Skills

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

### GPT's AI Orchestration Role

#### Primary Role: Code Implementation/Technical Executor
- **Code Generation**: Primary tool for implementing features and algorithms
- **API Development**: Excellent at creating REST APIs, GraphQL endpoints, and microservices
- **Database Design**: Strong at schema design, query optimization, and data modeling
- **System Integration**: Proficient at connecting different system components
- **Testing**: Expert at writing unit tests, integration tests, and test automation

#### Multi-Model Collaboration Patterns
- **Consensus Building**: Build agreement across multiple AI models with structured debate and evidence-based reasoning
- **Task Delegation**: Assign specific tasks to specialized AI models with clear instructions and progress monitoring
- **Parallel Processing**: Execute multiple independent tasks simultaneously (3x faster completion, better resource utilization)

#### Communication Patterns
- **Structured Questioning**: Gather information systematically with one question at a time
- **Incremental Validation**: Validate work in small, manageable chunks with continuous feedback
- **Documentation Standards**: Maintain consistent, high-quality documentation with clear structure

### GPT's MCP Stack Integration

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

### GPT's Skill Effectiveness Metrics

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

### GPT's Implementation Guidelines

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

### GPT's Future Enhancements

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
