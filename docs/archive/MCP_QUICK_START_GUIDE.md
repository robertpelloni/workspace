# MCP Quick Start Guide for Web Development

**Last Updated**: November 4, 2025

---

## 🚀 The Big 4 - Your Essential Toolkit

### 1. Chrome DevTools MCP 🔍
**When to use**: Testing, debugging, visual verification

```
Common Commands:
• Navigate to page: "Navigate to localhost:3000"
• Take snapshot: "Take a snapshot of the current page"
• Click element: "Click the login button"
• Read console: "List console messages"
• Screenshot: "Take a screenshot"
• Network: "List network requests"
```

**Real Example**:
```
You: "Navigate to localhost:3002/sentry-test and click the test error button"
Result: Opens page, clicks button, shows result
```

---

### 2. Tavily Search 🌐
**When to use**: Research, finding current docs, best practices

```
Common Searches:
• "Next.js 15 new features 2025"
• "React Server Components best practices"
• "TypeScript 5.3 breaking changes"
• "Tailwind CSS v4 migration guide"
• "Sentry integration tutorial"
```

**Real Example**:
```
You: "Search for Next.js 14 Sentry best practices"
Result: Returns articles from Sentry docs, Medium, Stack Overflow
```

---

### 3. Zen MCP 🧠
**When to use**: Expert advice, code review, architecture decisions

```
Available Models:
• flash (Gemini 2.5 Flash) - Fast answers
• pro (Gemini 2.5 Pro) - Deep analysis, 1M context
• gpt5 (GPT-5) - Advanced reasoning
• gpt5-codex (GPT-5 Codex) - Code specialization
• grok (Grok-4) - Alternative perspective
• opus (Claude Opus 4.1) - Writing & analysis
```

**Common Patterns**:
```
Chat:
• "What's the best way to handle WebSocket reconnection in React?"
• "Review this component for performance issues"
• "Explain this TypeScript error"

Consensus (for big decisions):
• "Should I use SSR or SSG for this blog?"
• "What's the best state management: Context, Zustand, or Redux?"
• "Evaluate Next.js vs Remix for this project"

CodeReview:
• "Review this React component for bugs and best practices"
```

**Real Example**:
```
You: "Chat with flash about Sentry performance optimization"
Result: Detailed advice on lazy loading, sampling, tunneling
```

---

### 4. Serena 🎯
**When to use**: Large codebase navigation, smart editing

```
Common Commands:
• "Find all references to the AuthContext"
• "Get symbol overview of the auth-context.tsx file"
• "Show me where useWebSocket is called"
• "Replace the body of the login function"
```

**Real Example**:
```
You: "Find all files that import the logger utility"
Result: Shows exact locations and code snippets
```

---

## 💡 Real-World Workflows

### Workflow 1: Adding a New Feature
```
1. Research (Tavily)
   "Search for React hook form with Zod validation examples"

2. Get Expert Advice (Zen)
   "Chat with pro about form validation architecture"

3. Navigate Code (Serena)
   "Find symbol for UserForm component"

4. Edit Code (Serena)
   "Replace UserForm validation logic"

5. Test (Chrome DevTools)
   "Navigate to localhost:3000/register and fill the form"
```

---

### Workflow 2: Debugging Production Issue
```
1. Understand Error (Zen)
   "Explain this error: [paste error]"

2. Find Related Code (Serena)
   "Find all references to handleSubmit"

3. Test Locally (Chrome DevTools)
   "Navigate to the page, open console, and reproduce the error"

4. Research Solution (Tavily)
   "Search for this specific error message and framework version"

5. Verify Fix (Chrome DevTools)
   "Click the submit button and check console"
```

---

### Workflow 3: Code Review & Optimization
```
1. Get Multi-Model Review (Zen Consensus)
   "Review this component - get opinions from gpt5, pro, and opus"

2. Find Usage (Serena)
   "Find all places where this component is used"

3. Research Best Practices (Tavily)
   "Search for React component optimization 2025"

4. Test Performance (Chrome DevTools)
   "Navigate to page and take performance snapshot"
```

---

## 🎯 Quick Tips

### Chrome DevTools MCP
- Always navigate before clicking/interacting
- Take snapshots to see page structure (faster than screenshots)
- Use `list_console_messages` to debug errors
- Network requests show API calls and responses

### Tavily Search
- Be specific with versions: "Next.js 14" not just "Next.js"
- Include year for latest info: "best practices 2025"
- Can extract full articles with `tavily-extract`
- Results include actual content, not just links

### Zen MCP
- Use `flash` for quick questions (fast, cheap)
- Use `pro` for complex architecture (1M context)
- Use `gpt5-codex` for code-specific help
- Use `consensus` for big decisions (gets multiple AI opinions)
- Always specify model: "chat with flash" or "chat with gpt5"

### Serena
- Start with symbol overview before reading full files
- Use name paths: `ClassName/methodName` for specificity
- Find references before refactoring
- Symbolic editing is safer than text replacement

---

## 📊 Cheat Sheet

| Task | Best Tool | Command Example |
|------|-----------|-----------------|
| Research docs | Tavily | "Search for X documentation" |
| Test UI | Chrome DevTools | "Navigate to page and click button" |
| Get AI advice | Zen | "Chat with flash about X" |
| Navigate code | Serena | "Find symbol for ComponentName" |
| Debug console | Chrome DevTools | "List console messages" |
| Architecture decision | Zen Consensus | "Consensus on X vs Y" |
| Code review | Zen | "Review this code" |
| Find references | Serena | "Find references to functionName" |
| Take screenshot | Chrome DevTools | "Screenshot of current page" |
| Current best practices | Tavily | "Search for X best practices 2025" |

---

## 🎓 Learning Path

### Day 1: Master Chrome DevTools MCP
```
1. Navigate to your local dev server
2. Take a snapshot
3. Click a button
4. Read console messages
5. Take a screenshot
```

### Day 2: Master Tavily Search
```
1. Search for your framework's latest features
2. Find a tutorial for something you're learning
3. Search for a specific error message
4. Extract content from a documentation page
```

### Day 3: Master Zen MCP
```
1. List available models
2. Chat with 'flash' for a quick question
3. Try 'gpt5-codex' for code help
4. Use consensus for a real decision
```

### Day 4: Master Serena
```
1. Get symbol overview of a file
2. Find a specific function
3. Find all references to a symbol
4. Navigate a large codebase
```

---

## 🔥 Advanced Combos

### The "Research → Plan → Code → Test" Loop
```
1. Tavily: "Search for feature implementation examples"
2. Zen: "Chat with pro about architecture approach"
3. Serena: "Navigate to relevant files"
4. Chrome DevTools: "Test the implementation"
```

### The "Debug Everything" Combo
```
1. Chrome DevTools: "Navigate and reproduce error"
2. Chrome DevTools: "List console messages"
3. Zen: "Chat with flash to explain error"
4. Serena: "Find references to failing function"
5. Tavily: "Search for this specific error"
```

### The "Perfect Code Review" Combo
```
1. Zen Consensus: Get 3 AI opinions (gpt5, pro, opus)
2. Serena: Find all places code is used
3. Tavily: Research current best practices
4. Chrome DevTools: Verify changes work in browser
```

---

## 💰 Cost Optimization

**Free/Cheap Models** (for quick questions):
- `flash` (Gemini 2.5 Flash) - Very cheap
- `gpt5-nano` - Cheapest GPT-5
- `gpt5-mini` - Balanced

**Premium Models** (for complex work):
- `pro` (Gemini 2.5 Pro) - Best for long context
- `gpt5-pro` - Best for reasoning
- `gpt5-codex` - Best for code
- `opus` (Claude Opus) - Best for writing

**Rule of Thumb**:
- Quick questions → `flash`
- Code help → `gpt5-codex`
- Architecture → `pro`
- Writing → `opus`
- Decisions → Consensus with 2-3 models

---

## 🎉 Success Stories

### Today's Achievement: Sentry Integration
```
Tools Used:
✅ Tavily - Researched Sentry best practices
✅ Zen (flash) - Got optimization advice
✅ Serena - Navigated TypeScript files
✅ Chrome DevTools - Tested /sentry-test page

Time: ~1 hour
Result: Full Sentry integration with comprehensive logging
```

**What We Did**:
1. Installed @sentry/nextjs (219 packages)
2. Created 3 config files (client, server, edge)
3. Built logger utility (350+ lines)
4. Integrated into auth, websocket, location hooks
5. Created test page with 8 test scenarios
6. Verified with Chrome DevTools automation

**Tools Performance**:
- Chrome DevTools: Clicked test button, verified success message ✅
- Tavily: Found Sentry docs and best practices ✅
- Zen: Provided 3 detailed optimization strategies ✅
- Serena: Navigated files efficiently (used in background) ✅

---

## 🤝 Getting Help

**Each MCP Server has documentation:**
- Chrome DevTools: See tool descriptions
- Tavily: https://tavily.com/docs
- Zen: Use `listmodels` to see all options
- Serena: Built into your editor with examples

**General Pattern**:
1. Start with Tavily (research)
2. Ask Zen for advice (expert)
3. Use Serena to navigate (code)
4. Test with Chrome DevTools (verify)

---

**Remember**: These tools work best when combined. Don't just use one - create workflows that leverage multiple MCP servers for maximum productivity!

🚀 Happy coding!
