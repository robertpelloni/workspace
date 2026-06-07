# MCP Server Audit & Configuration Plan

## Quick Reference

**Priority**: Complete this efficiently so you can focus on fwber monetization

## Phase 1: Edge Tabs Extraction (15-30 min)

### Steps:
1. **Extract all tabs**: Export Edge tabs to a list/txt file
2. **Filter MCP servers**: Identify which tabs contain MCP server info
3. **Categorize**: Group by type (AI models, tools, CLIs, utilities)
4. **Prioritize**: Mark which ones are most useful for your workflow

### Categories to Look For:
- **AI Model Servers**: Claude, GPT, Gemini, etc.
- **Development Tools**: Code editors, debuggers, formatters
- **Database Tools**: Postgres, MongoDB, etc.
- **File System Tools**: File management, search
- **Communication Tools**: Email, messaging integrations
- **Web Scraping**: Data extraction tools
- **Knowledge Bases**: Vector DBs, document stores

## Phase 2: Notepad++ Configuration (30-45 min)

### Current Tools Structure:
Based on your setup, you likely have:
- Codex config
- Cursor MCP config
- Other CLI configs

### What to Add:
1. **Create MCP server registry** in Notepad++
2. **Document each server**: Purpose, command, config location
3. **Test basic connectivity**: Can it start? Does it handshake?
4. **Document issues**: Timeouts, auth failures, etc.

### Config Locations to Check:
- `C:\Users\hyper\.cursor\mcp.json`
- `C:\Users\hyper\workspace\.kilocode\mcp.json`
- Notepad++ config files
- Codex config files

## Phase 3: Testing & Validation (45-60 min)

### Test Checklist per Server:
- [ ] Server starts without errors
- [ ] Handshake successful
- [ ] Tools are listed correctly
- [ ] Basic tool call works
- [ ] Resources accessible (if applicable)
- [ ] No timeout issues
- [ ] Authentication works (if required)

### Current Issues to Fix First:
1. **tavily-mcp**: Handshake failure - check command path
2. **filesystem**: 120s timeout - increase timeout in config

## Phase 4: Integration (30 min)

### Sync Across Tools:
- Codex
- Cursor
- Notepad++
- Gemini CLI (if applicable)
- Any other CLIs

### Create Master Config:
- Single source of truth for MCP servers
- Easy to sync across tools
- Version controlled

## Quick Wins While Waiting for ChatGPT Plus

1. **Fix existing issues first**: tavily-mcp, filesystem timeout
2. **Document working servers**: You have 3 working (chroma, serena, zen)
3. **Create template**: For adding new servers quickly
4. **Test current stack**: Make sure what works continues to work

## fwber Priority Checklist (When You Return)

Since you mentioned fwber needs finishing:
- [ ] Review current production readiness
- [ ] Identify monetization features needed
- [ ] Test deployment pipeline
- [ ] Security audit (you fixed critical issues already)
- [ ] User onboarding flow
- [ ] Payment integration (if needed)
- [ ] Marketing/promotion strategy

## Time Allocation Suggestion

**Total MCP Audit**: 2-3 hours max
- Edge tabs: 30 min
- Notepad++ config: 45 min  
- Testing: 60 min
- Documentation: 30 min

**Then focus on fwber monetization** - that's where the real value is.

## Notes

- ChatGPT Plus might help, but manual review ensures you understand what you're adding
- gemini-computer-use could automate, but manual gives you better control
- Consider batch processing: test 5-10 servers at a time rather than all at once

---

**Remember**: The goal is to improve your development workflow, not to create a perfect MCP setup. Good enough and back to fwber is better than perfect MCP setup and delayed monetization.

