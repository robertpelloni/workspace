# Contributing to Robert Pelloni's Workspace

Thank you for your interest in contributing! This workspace contains multiple projects and AI orchestration tools. Here's how you can contribute effectively.

## Table of Contents
- [Getting Started](#getting-started)
- [Development Process](#development-process)
- [Code Standards](#code-standards)
- [Submitting Changes](#submitting-changes)
- [AI Orchestration Guidelines](#ai-orchestration-guidelines)

## Getting Started

### Prerequisites
- Git installed and configured
- Familiarity with the specific project you want to contribute to
- For AI orchestration work: Access to relevant MCP servers and AI models

### Setting Up Your Environment

1. Fork the repository
2. Clone your fork:
   ```bash
   git clone https://github.com/YOUR-USERNAME/workspace.git
   cd workspace
   ```
3. Create a feature branch:
   ```bash
   git checkout -b feature/your-feature-name
   ```

## Development Process

### Before Starting Work
1. Check existing issues and pull requests to avoid duplication
2. For major changes, open an issue first to discuss the approach
3. Review the project-specific documentation in each subdirectory

### Code Quality
- Write clear, maintainable code
- Follow the existing code style in each project
- Add tests for new features when applicable
- Update documentation to reflect your changes

### Testing
- Run existing tests before submitting changes
- Add tests for new functionality
- Ensure all tests pass before creating a pull request

## Code Standards

### General Guidelines
- Use meaningful variable and function names
- Keep functions small and focused
- Comment complex logic
- Remove commented-out code and debug statements

### Project-Specific Standards
Different projects in this workspace use different languages and frameworks:
- **PHP projects**: Follow PSR-12 coding standards
- **JavaScript/TypeScript**: Use consistent formatting (Prettier recommended)
- **Python**: Follow PEP 8 style guide
- **C++**: Follow project-specific conventions

### Commit Messages
Follow the [Conventional Commits](https://www.conventionalcommits.org/) specification:

```
type(scope): subject

body

footer
```

Types:
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation changes
- `style`: Formatting, missing semicolons, etc.
- `refactor`: Code restructuring
- `test`: Adding tests
- `chore`: Maintenance tasks

Example:
```
feat(auth): add two-factor authentication support

Implements TOTP-based 2FA for enhanced security.
Uses standard TOTP libraries and follows best practices.

Closes #123
```

## Submitting Changes

### Pull Request Process

1. **Update Your Branch**
   ```bash
   git fetch origin
   git rebase origin/main
   ```

2. **Push Your Changes**
   ```bash
   git push origin feature/your-feature-name
   ```

3. **Create Pull Request**
   - Use the pull request template
   - Provide a clear description of changes
   - Link related issues
   - Add screenshots for UI changes
   - Request review from maintainers

4. **Address Review Feedback**
   - Respond to all review comments
   - Make requested changes
   - Push updates to the same branch

5. **Merge**
   - Maintainers will merge once approved
   - Delete your feature branch after merge

### Pull Request Checklist
- [ ] Code follows project style guidelines
- [ ] Self-review of code completed
- [ ] Comments added for complex logic
- [ ] Documentation updated
- [ ] No new warnings generated
- [ ] Tests added/updated and passing
- [ ] Changes work locally
- [ ] Dependent changes merged

## AI Orchestration Guidelines

This workspace extensively uses AI orchestration with multiple models. When contributing to AI-related components:

### AI Model Integration
- Document which AI models are used and why
- Include fallback strategies for API failures
- Respect rate limits and quotas
- Never commit API keys or secrets

### MCP Server Development
- Follow MCP protocol specifications
- Add comprehensive error handling
- Document all available tools and methods
- Include usage examples

### Skills and Methodologies
- Document new skills in the consolidated-skills directory
- Follow the existing skill structure
- Include effectiveness metrics when available
- Test skills with multiple AI models

### Consensus Building
- Use multi-model consensus for critical decisions
- Document the models used and their responses
- Include confidence scores when available
- Store results in appropriate Chroma collections

## Questions or Need Help?

- Open an issue for bugs or feature requests
- Check existing documentation in the repository
- Review the AI coordination guides for orchestration questions

## Code of Conduct

Please note that this project follows a Code of Conduct. By participating, you agree to uphold this code. Please report unacceptable behavior to the project maintainers.

## Recognition

Contributors will be recognized in the project documentation. Thank you for helping make this workspace better!
