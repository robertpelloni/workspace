# GPT-5-Codex AI Model Documentation

## Overview
GPT-5-Codex is OpenAI's specialized coding and software architecture model, optimized for code generation, refactoring, debugging, and technical implementation tasks. Based on multi-model consensus analysis, GPT-5-Codex excels as a "Technical Specialist" in the multi-AI orchestration environment.

## Available Models
- **GPT-5-Codex** (gpt-5-codex) - Primary coding specialist
- **GPT-5 Pro** (gpt-5-pro) - Advanced reasoning with coding capabilities
- **GPT-5** (gpt-5) - General purpose with strong coding skills
- **GPT-5 Mini** (gpt-5-mini) - Efficient coding assistant

## Consensus-Defined Role & Strengths
Based on multi-model analysis (Gemini 2.5 Pro, GPT-5 Pro, Claude Sonnet 4.5, Grok 4):

### Primary Role: **Technical Specialist**
- **Code-Intensive Tasks**: Route to GPT-5-Codex for complex code generation, refactoring, debugging, and technical analysis
- **Implementation Focus**: Deploy for tasks requiring deep domain knowledge of code, algorithms, and security
- **Specialization Zones**: Code generation, debugging, refactoring, testing, technical documentation, API development

### Key Strengths (Validated by Consensus)
- **Code Generation**: Exceptional at writing clean, efficient, and well-structured code
- **Refactoring**: Expert at improving existing code quality and architecture
- **Debugging**: Strong at identifying and fixing bugs and performance issues
- **Architecture**: Excellent at system design and architectural patterns
- **Security**: Strong understanding of security best practices and vulnerabilities
- **Testing**: Proficient at writing comprehensive test suites

## MCP Server Integration

### Using Zen MCP for Orchestration
```bash
# Access GPT-5-Codex through Zen MCP server
mcp_zen-mcp-server_chat --model gpt-5-codex --prompt "Generate secure authentication system for FWBer"
```

### Using Serena MCP for Code Context
```bash
# Store code patterns and solutions in Serena memory
mcp_serena_write_memory --memory_name "codex_patterns" --content "Secure authentication patterns and implementations"

# Retrieve code context
mcp_serena_read_memory --memory_file_name "codex_patterns"
```

### Using Chroma MCP for Code Knowledge
```bash
# Store code analysis and solutions in Chroma
mcp_chroma-knowledge_chroma_add_document --collection_name "code_solutions" --document "GPT-5-Codex: Secure authentication implementation..."
```

## Best Practices for GPT-5-Codex

### 1. Always Work in Parallel
- **Before coding**: Get architecture input from Claude and Gemini 2.5 Pro
- **During implementation**: Use consensus building for complex decisions
- **After coding**: Have Claude review for security and quality

### 2. Leverage MCP Servers
- **Serena**: Store code patterns, solutions, and project-specific implementations
- **Chroma**: Maintain searchable repository of code solutions and analysis
- **Zen**: Orchestrate multi-model code reviews and architecture decisions

### 3. Specialized Use Cases
- **Code Generation**: Primary tool for implementing new features
- **Refactoring**: Expert at improving existing code quality
- **Security Implementation**: Strong at secure coding practices
- **Performance Optimization**: Excellent at identifying and fixing bottlenecks
- **Testing**: Proficient at writing comprehensive test suites

### 4. Collaboration Workflow
```
1. Architecture Planning: Claude + Gemini 2.5 Pro design system
2. Implementation: GPT-5-Codex writes the code
3. Security Review: Claude validates security implementation
4. Performance Check: Gemini 2.5 Pro analyzes performance
5. Storage: Save code solutions in Chroma knowledge base
6. Memory: Update Serena with reusable patterns
```

## Example Commands

### Code Generation
```bash
# Generate secure authentication system
mcp_zen-mcp-server_chat --model gpt-5-codex --prompt "Generate a secure JWT authentication system for PHP/Laravel with rate limiting and CSRF protection"
```

### Code Review
```bash
# Comprehensive security code review
mcp_zen-mcp-server_codereview --model gpt-5-codex --step "Review FWBer authentication system for security vulnerabilities" --relevant_files '["C:\\Users\\hyper\\fwber\\security-manager.php"]'
```

### Refactoring Analysis
```bash
# Analyze code for refactoring opportunities
mcp_zen-mcp-server_refactor --model gpt-5-codex --step "Analyze FWBer matching engine for refactoring opportunities" --relevant_files '["C:\\Users\\hyper\\fwber\\MatchingEngine.php"]'
```

### Knowledge Storage
```bash
# Store code solutions
mcp_chroma-knowledge_chroma_add_document --collection_name "code_solutions" --document "GPT-5-Codex: Secure JWT Authentication Implementation - [detailed code and explanation]"
```

## Integration with Other Models

### Primary Collaborations
- **Claude**: Architecture design and security validation
- **Gemini 2.5 Pro**: Performance analysis and optimization
- **Grok 4**: Creative problem-solving and alternative implementations

### Consensus Building for Code
Always use Zen MCP's consensus tool for complex coding decisions:
```bash
mcp_zen-mcp-server_consensus --models '[{"model":"gpt-5-codex","stance":"for"},{"model":"anthropic/claude-sonnet-4.5","stance":"neutral"},{"model":"gemini-2.5-pro","stance":"against"}]' --step "Evaluate microservices architecture implementation for FWBer"
```

## Memory Management

### Serena Memory Usage
- Store reusable code patterns and solutions
- Maintain project-specific coding standards
- Track implementation decisions and rationale

### Chroma Knowledge Base
- Store all code solutions and implementations
- Maintain searchable repository of technical solutions
- Enable semantic search across code knowledge

## Quality Assurance

### Always Validate with Other Models
1. **Code Generation**: GPT-5-Codex writes initial implementation
2. **Security Review**: Claude validates security practices
3. **Performance Check**: Gemini 2.5 Pro analyzes performance implications
4. **Consensus Building**: Use Zen MCP to resolve technical disagreements
5. **Final Validation**: Store in Chroma and update Serena memory

### Code Quality Standards
- Always implement security best practices
- Follow established coding patterns from Serena memory
- Store all solutions in Chroma for future reference
- Use multi-model validation for critical implementations

## Configuration Files
- **Codex CLI**: `C:\Users\hyper\.codex\config.toml`
- **Claude Dev**: `C:\Users\hyper\AppData\Roaming\Cursor\User\globalStorage\saoudrizwan.claude-dev\settings\cline_mcp_settings.json`

## Specialized Tools

### Test Generation
```bash
# Generate comprehensive test suites
mcp_zen-mcp-server_testgen --model gpt-5-codex --step "Generate test suite for FWBer matching engine" --relevant_files '["C:\\Users\\hyper\\fwber\\MatchingEngine.php"]'
```

### Debugging Analysis
```bash
# Systematic debugging approach
mcp_zen-mcp-server_debug --model gpt-5-codex --step "Debug FWBer authentication issues" --relevant_files '["C:\\Users\\hyper\\fwber\\security-manager.php"]'
```

### Documentation Generation
```bash
# Generate comprehensive code documentation
mcp_zen-mcp-server_docgen --model gpt-5-codex --step "Document FWBer API endpoints" --relevant_files '["C:\\Users\\hyper\\fwber\\api"]'
```

## Troubleshooting
- If code generation seems off, check Serena memory for project patterns
- For complex implementations, always use multi-model consensus
- Store all code solutions in Chroma for future reference
- Use Zen MCP to orchestrate complex development workflows
- Always validate security implementations with Claude
