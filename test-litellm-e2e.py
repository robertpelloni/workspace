import json, urllib.request, time

PROXY = "http://localhost:4000/v1"

def chat(model, msg, timeout=20):
    req = urllib.request.Request(
        PROXY + "/chat/completions",
        data=json.dumps({"model": model, "messages": [{"role": "user", "content": msg}], "max_tokens": 20}).encode(),
        headers={"Content-Type": "application/json"})
    start = time.time()
    with urllib.request.urlopen(req, timeout=timeout) as r:
        d = json.loads(r.read())
        elapsed = time.time() - start
        model_used = d.get("model", "?")
        content = d.get("choices", [{}])[0].get("message", {}).get("content", "?")
        return elapsed, model_used, content

print("=" * 60)
print("LiteLLM Proxy v6 - Comprehensive End-to-End Test")
print("=" * 60)
print()

# Test 1: Basic routing
print("1. Basic Routing Tests:")
for group in ["free-llm", "free-llm-or", "free-llm-thinking"]:
    t, m, c = chat(group, "respond with just: ok")
    c_short = c.strip()[:20] if c else "(empty/thinking)"
    print("   %-20s -> %.1fs  model=%-40s  content=%s" % (group, t, m[:40], c_short))

# Test 2: Code generation
print()
print("2. Code Generation (free-llm):")
t, m, c = chat("free-llm", "Write a Python one-liner to reverse a string. Just the code.", timeout=30)
print("   %.1fs  model=%s" % (t, m[:40]))
print("   content=%s" % c.strip()[:60])

# Test 3: Multi-turn conversation
print()
print("3. Multi-turn Conversation (free-llm-or):")
msgs = [
    {"role": "user", "content": "My name is Alice."},
    {"role": "assistant", "content": "Hi Alice! How can I help you?"},
    {"role": "user", "content": "What is my name? Answer briefly."}
]
req = urllib.request.Request(
    PROXY + "/chat/completions",
    data=json.dumps({"model": "free-llm-or", "messages": msgs, "max_tokens": 20}).encode(),
    headers={"Content-Type": "application/json"})
start = time.time()
with urllib.request.urlopen(req, timeout=20) as r:
    d = json.loads(r.read())
    elapsed = time.time() - start
    content = d.get("choices", [{}])[0].get("message", {}).get("content", "?")
    print("   %.1fs  content=%s" % (elapsed, content.strip()[:40]))

# Test 4: Tool calling
print()
print("4. Tool Calling (free-llm-or):")
req = urllib.request.Request(
    PROXY + "/chat/completions",
    data=json.dumps({
        "model": "free-llm-or",
        "messages": [
            {"role": "system", "content": "You are a helpful assistant. Always use tools when available."},
            {"role": "user", "content": "What is the weather in Paris?"}
        ],
        "max_tokens": 50,
        "tools": [{"type": "function", "function": {
            "name": "get_weather",
            "description": "Get current weather for a city",
            "parameters": {"type": "object", "properties": {"city": {"type": "string"}}, "required": ["city"]}
        }}]
    }).encode(),
    headers={"Content-Type": "application/json"})
start = time.time()
with urllib.request.urlopen(req, timeout=20) as r:
    d = json.loads(r.read())
    elapsed = time.time() - start
    msg = d.get("choices", [{}])[0].get("message", {})
    tcs = msg.get("tool_calls", [])
    if tcs:
        fn_name = tcs[0].get("function", {}).get("name", "?")
        fn_args = tcs[0].get("function", {}).get("arguments", "?")
        print("   %.1fs  tool_call=%s(%s)" % (elapsed, fn_name, fn_args))
    else:
        content_str = msg.get("content", "?") or ""
        print("   %.1fs  content=%s (no tool_call)" % (elapsed, content_str[:40]))

# Test 5: Thinking model
print()
print("5. Reasoning Model (free-llm-thinking):")
req = urllib.request.Request(
    PROXY + "/chat/completions",
    data=json.dumps({
        "model": "free-llm-thinking",
        "messages": [{"role": "user", "content": "If a bat and ball cost $1.10 total, and the bat costs $1 more than the ball, how much does the ball cost?"}],
        "max_tokens": 200
    }).encode(),
    headers={"Content-Type": "application/json"})
start = time.time()
with urllib.request.urlopen(req, timeout=45) as r:
    d = json.loads(r.read())
    elapsed = time.time() - start
    msg = d.get("choices", [{}])[0].get("message", {})
    reasoning = msg.get("reasoning_content", None)
    content = msg.get("content", None)
    print("   %.1fs  model=%s" % (elapsed, d.get("model", "?")[:40]))
    if reasoning:
        print("   reasoning=%s..." % reasoning[:60])
    if content:
        print("   content=%s" % content.strip()[:60])
    else:
        print("   content=(in reasoning, increase max_tokens)")

# Test 6: Rapid sequential
print()
print("6. Rapid Sequential (5 requests, free-llm):")
total_time = 0
for i in range(1, 6):
    t, m, c = chat("free-llm", "say request %d ok" % i, timeout=15)
    total_time += t
    print("   [%d] %.1fs  model=%s" % (i, t, m[:30]))
print("   Total: %.1fs, Avg: %.1fs" % (total_time, total_time/5))

print()
print("=" * 60)
print("ALL END-TO-END TESTS COMPLETE")
print("=" * 60)
