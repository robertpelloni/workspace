#!/usr/bin/env python3
"""
A2A Swarm Harness — Giant swarms of LLM-powered subagents via FreeLLM/LiteLLM.

Architecture:
  - Coordinator dispatches tasks to N subagents
  - Each subagent calls LLM through FreeLLM proxy (localhost:4000)
  - A2A broker routes inter-agent messages (Query/Command/Response/Event)
  - Results aggregate back to coordinator for synthesis
  - Supports parallel, chain, debate, and map-reduce patterns

Usage:
  python a2a_swarm.py --task "Analyze all repos for security issues" --agents 20 --model free-llm
  python a2a_swarm.py --task "Review code quality" --agents 10 --pattern debate
  python a2a_swarm.py --task "Generate tests" --agents 5 --pattern chain
  python a2a_swarm.py --config swarm_config.json
"""

import argparse
import asyncio
import json
import os
import sys
import time
import uuid
import httpx
from dataclasses import dataclass, field
from enum import Enum
from typing import Dict, List, Optional


# ─── A2A Protocol ───────────────────────────────────────────────────────────────


class MessageType(str, Enum):
    QUERY = "Query"
    COMMAND = "Command"
    RESPONSE = "Response"
    EVENT = "Event"


@dataclass
class A2AMessage:
    id: str = field(default_factory=lambda: str(uuid.uuid4())[:8])
    source: str = ""
    target: str = ""
    type: MessageType = MessageType.EVENT
    payload: str = ""
    topic: str = ""
    timestamp: float = field(default_factory=time.time)

    def to_dict(self) -> dict:
        return {
            "id": self.id,
            "source": self.source,
            "target": self.target,
            "type": self.type.value,
            "payload": self.payload,
            "topic": self.topic,
            "timestamp": self.timestamp,
        }


class A2ABroker:
    """In-process A2A message broker with pub/sub, routing, and broadcast."""

    def __init__(self):
        self.subscriptions: Dict[str, list] = {}
        self.topics: Dict[str, list] = {}
        self.peers: Dict[str, str] = {}
        self.message_log: List[A2AMessage] = []

    def subscribe(self, agent_id: str) -> asyncio.Queue:
        q = asyncio.Queue(maxsize=200)
        if agent_id not in self.subscriptions:
            self.subscriptions[agent_id] = []
        self.subscriptions[agent_id].append(q)
        return q

    def subscribe_topic(self, topic: str) -> asyncio.Queue:
        q = asyncio.Queue(maxsize=200)
        if topic not in self.topics:
            self.topics[topic] = []
        self.topics[topic].append(q)
        return q

    def route(self, msg: A2AMessage):
        self.message_log.append(msg)
        if msg.target in self.subscriptions:
            for q in self.subscriptions[msg.target]:
                try:
                    q.put_nowait(msg)
                except asyncio.QueueFull:
                    pass

    def publish(self, msg: A2AMessage):
        self.message_log.append(msg)
        if msg.topic and msg.topic in self.topics:
            for q in self.topics[msg.topic]:
                try:
                    q.put_nowait(msg)
                except asyncio.QueueFull:
                    pass

    def broadcast(self, msg: A2AMessage):
        self.message_log.append(msg)
        for aid, queues in self.subscriptions.items():
            if aid == msg.source:
                continue
            for q in queues:
                try:
                    q.put_nowait(msg)
                except asyncio.QueueFull:
                    pass


# ─── LLM Interface ──────────────────────────────────────────────────────────────

FREE_LLM_URL = os.environ.get("FREELLM_URL", "http://localhost:4000")

# Concurrency limiter: max 3 simultaneous LLM calls to avoid proxy overload
_LLM_SEMAPHORE = asyncio.Semaphore(3)

# Model fallback chain for when primary model fails
MODEL_FALLBACKS = [
    "z-ai/glm-5.1",
    "deepseek-ai/deepseek-v4-flash",
    "openai/gpt-4.1-mini",
    "minimaxai/minimax-m2.7",
    "qwen/qwen3.5-397b-a17b",
]


async def call_freellm(
    prompt: str,
    model: str = "free-llm",
    system: str = "",
    max_tokens: int = 2048,
    temperature: float = 0.7,
    timeout: float = 90.0,
    max_retries: int = 2,
) -> str:
    """Make an async LLM call through FreeLLM/LiteLLM proxy with retries and fallback."""
    messages = []
    if system:
        messages.append({"role": "system", "content": system})
    messages.append({"role": "user", "content": prompt})

    # Build model try-list: primary model + fallbacks
    models_to_try = [model]
    for fb in MODEL_FALLBACKS:
        if fb not in models_to_try:
            models_to_try.append(fb)

    async with _LLM_SEMAPHORE:
        for current_model in models_to_try:
            payload = {
                "model": current_model,
                "messages": messages,
                "max_tokens": max_tokens,
                "temperature": temperature,
            }
            for attempt in range(max_retries + 1):
                try:
                    async with httpx.AsyncClient(
                        timeout=httpx.Timeout(timeout, connect=15.0)
                    ) as client:
                        resp = await client.post(
                            f"{FREE_LLM_URL}/v1/chat/completions",
                            json=payload,
                            headers={"Content-Type": "application/json"},
                        )
                        if resp.status_code == 429 or resp.status_code >= 500:
                            if attempt < max_retries:
                                await asyncio.sleep(2 ** attempt)
                                continue
                            break  # Try next model
                        resp.raise_for_status()
                        data = resp.json()
                        msg = data["choices"][0]["message"]
                        if "content" in msg and msg["content"]:
                            return msg["content"]
                        elif "tool_calls" in msg:
                            return json.dumps(msg["tool_calls"])
                        else:
                            return json.dumps(msg)
                except httpx.TimeoutException:
                    if attempt < max_retries:
                        await asyncio.sleep(1)
                        continue
                    break  # Try next model
                except httpx.HTTPStatusError as e:
                    if e.response.status_code >= 500 and attempt < max_retries:
                        await asyncio.sleep(2 ** attempt)
                        continue
                    return f"[HTTP {e.response.status_code}: {e.response.text[:200]}]"
                except Exception as e:
                    if attempt < max_retries:
                        await asyncio.sleep(1)
                        continue
                    return f"[ERROR: {str(e)[:200]}]"
    return f"[ALL MODELS FAILED: tried {', '.join(models_to_try[:3])}]"


# ─── Subagent Types ─────────────────────────────────────────────────────────────


class SubagentType(str, Enum):
    CODE = "code"
    RESEARCH = "research"
    REVIEW = "review"
    PLAN = "plan"
    DOC = "doc"
    BUILD = "build"
    TEST = "test"
    DEBUG = "debug"
    SECURITY = "security"
    DEVOPS = "devops"
    COORDINATOR = "coordinator"
    SYNTHESIZER = "synthesizer"
    CRITIC = "critic"


SYSTEM_PROMPTS = {
    SubagentType.CODE: "You are a code generation agent. Write clean, efficient code. Follow project conventions.",
    SubagentType.RESEARCH: "You are a research agent. Find relevant information, analyze patterns, and provide thorough findings.",
    SubagentType.REVIEW: "You are a code review agent. Analyze code for correctness, security, performance, and maintainability.",
    SubagentType.PLAN: "You are a planning agent. Break down complex tasks into concrete, verifiable steps.",
    SubagentType.DOC: "You are a documentation agent. Write clear, comprehensive documentation.",
    SubagentType.BUILD: "You are a build agent. Diagnose build failures and fix configuration issues.",
    SubagentType.TEST: "You are a testing agent. Write thorough unit and integration tests.",
    SubagentType.DEBUG: "You are a debugging agent. Systematically trace issues to root causes.",
    SubagentType.SECURITY: "You are a security agent. Identify vulnerabilities, injection risks, and compliance issues.",
    SubagentType.DEVOPS: "You are a DevOps agent. Handle CI/CD, deployment, and infrastructure automation.",
    SubagentType.COORDINATOR: "You are a coordinator agent. Decompose tasks, delegate to specialists, and synthesize results.",
    SubagentType.SYNTHESIZER: "You are a synthesis agent. Combine multiple agent outputs into a coherent, unified result.",
    SubagentType.CRITIC: "You are a critic agent. Challenge assumptions, find weaknesses, and propose improvements.",
}


# ─── Subagent ───────────────────────────────────────────────────────────────────


class Subagent:
    """A single LLM-powered agent in the swarm."""

    def __init__(
        self,
        agent_id: str,
        agent_type: SubagentType,
        broker: A2ABroker,
        model: str = "free-llm",
        max_tokens: int = 2048,
        temperature: float = 0.7,
    ):
        self.id = agent_id
        self.type = agent_type
        self.broker = broker
        self.model = model
        self.max_tokens = max_tokens
        self.temperature = temperature
        self.system_prompt = SYSTEM_PROMPTS.get(
            agent_type, "You are a helpful AI agent."
        )
        self.queue = broker.subscribe(agent_id)
        self.results: List[dict] = []
        self.status = "idle"

    async def execute(self, task: str, context: str = "") -> dict:
        """Execute a task via LLM call."""
        self.status = "running"
        prompt = f"## Task\n{task}\n\n## Context\n{context}\n\n## Instructions\nComplete the task. Be thorough and specific."

        result_text = await call_freellm(
            prompt=prompt,
            model=self.model,
            system=self.system_prompt,
            max_tokens=self.max_tokens,
            temperature=self.temperature,
        )

        self.status = "done"
        entry = {
            "agent_id": self.id,
            "agent_type": self.type.value,
            "task": task,
            "result": result_text,
            "timestamp": time.time(),
        }
        self.results.append(entry)

        # Broadcast completion
        self.broker.broadcast(
            A2AMessage(
                source=self.id,
                type=MessageType.EVENT,
                topic="swarm_results",
                payload=json.dumps(entry),
            )
        )

        return entry

    async def listen_and_respond(self, iterations: int = 1):
        """Listen for A2A messages and respond."""
        for _ in range(iterations):
            try:
                msg = await asyncio.wait_for(self.queue.get(), timeout=30.0)
                if msg.type in (MessageType.QUERY, MessageType.COMMAND):
                    response = await call_freellm(
                        prompt=f"Another agent asks: {msg.payload}\n\nProvide a helpful response based on your expertise.",
                        model=self.model,
                        system=self.system_prompt,
                        max_tokens=min(self.max_tokens, 1024),
                        temperature=self.temperature,
                    )
                    self.broker.route(
                        A2AMessage(
                            source=self.id,
                            target=msg.source,
                            type=MessageType.RESPONSE,
                            payload=response,
                        )
                    )
            except asyncio.TimeoutError:
                pass


# ─── Swarm Patterns ─────────────────────────────────────────────────────────────


class SwarmPattern(str, Enum):
    PARALLEL = "parallel"  # All agents work on subtasks simultaneously
    CHAIN = "chain"  # Agents work sequentially, each building on previous
    DEBATE = "debate"  # Agents propose, critique, and refine
    MAP_REDUCE = "map_reduce"  # Map tasks to agents, reduce results
    COUNCIL = "council"  # Agents vote on decisions
    PIPELINE = "pipeline"  # Fixed pipeline: plan -> code -> test -> review


async def run_parallel_swarm(
    task: str,
    agents: List[Subagent],
    coordinator_prompt: str = "",
) -> dict:
    """All agents work on the same task in parallel. Synthesizer combines results."""
    print(f"\n🐝 PARALLEL SWARM: {len(agents)} agents on: {task[:80]}...")

    # Phase 1: All agents execute in parallel
    coros = [agent.execute(task) for agent in agents]
    results = await asyncio.gather(*coros, return_exceptions=True)

    completed = [r for r in results if isinstance(r, dict)]
    errors = [r for r in results if isinstance(r, Exception)]

    print(f"  ✅ {len(completed)} completed, ❌ {len(errors)} errors")

    # Phase 2: Synthesize
    if coordinator_prompt:
        synth = Subagent(
            "synthesizer", SubagentType.SYNTHESIZER, agents[0].broker, agents[0].model
        )
        combined = "\n\n---\n\n".join(
            f"Agent {r['agent_id']} ({r['agent_type']}):\n{r['result'][:1000]}"
            for r in completed
        )
        synth_result = await synth.execute(
            f"Synthesize these {len(completed)} agent outputs into a unified answer:\n\n{combined}\n\nProvide a comprehensive, well-structured synthesis."
        )
        return {"pattern": "parallel", "results": completed, "synthesis": synth_result}

    return {"pattern": "parallel", "results": completed, "synthesis": None}


async def run_chain_swarm(
    task: str,
    agents: List[Subagent],
) -> dict:
    """Agents work sequentially, each building on the previous result."""
    print(f"\n🔗 CHAIN SWARM: {len(agents)} agents on: {task[:80]}...")

    chain_results = []
    context = ""

    for i, agent in enumerate(agents):
        print(f"  🔗 Step {i + 1}/{len(agents)}: {agent.type.value}")
        result = await agent.execute(
            task, context=f"Previous step output:\n{context[:2000]}"
        )
        chain_results.append(result)
        context = result["result"]

        # Notify next agent via A2A
        if i < len(agents) - 1:
            agent.broker.route(
                A2AMessage(
                    source=agent.id,
                    target=agents[i + 1].id,
                    type=MessageType.COMMAND,
                    payload=f"Chain step {i + 1} complete. Build on this result.",
                )
            )

    print(f"  ✅ Chain complete: {len(chain_results)} steps")

    return {
        "pattern": "chain",
        "results": chain_results,
        "final_output": chain_results[-1]["result"],
    }


async def run_debate_swarm(
    task: str,
    agents: List[Subagent],
    rounds: int = 2,
) -> dict:
    """Agents propose solutions, critique each other, and refine."""
    print(f"\n⚔️ DEBATE SWARM: {len(agents)} agents, {rounds} rounds on: {task[:80]}...")

    debate_log = []

    # Round 1: Proposals
    print("  📝 Round 1: Proposals")
    coros = [agent.execute(task) for agent in agents]
    proposals = await asyncio.gather(*coros, return_exceptions=True)
    valid_proposals = [r for r in proposals if isinstance(r, dict)]
    debate_log.append({"round": 1, "type": "proposal", "results": valid_proposals})

    # Subsequent rounds: Critique and refine
    for round_num in range(2, rounds + 2):
        print(f"  ⚔️ Round {round_num}: Critique & Refine")

        # Create critics from the same agents
        critique_coros = []
        for i, agent in enumerate(agents):
            # Each agent critiques a different proposal
            prop_idx = i % len(valid_proposals)
            proposal_text = valid_proposals[prop_idx]["result"]
            critique_prompt = (
                f"Original task: {task}\n\n"
                f"Proposal to critique:\n{proposal_text[:2000]}\n\n"
                f"Provide constructive criticism and an improved version."
            )
            critique_coros.append(agent.execute(critique_prompt))

        critiques = await asyncio.gather(*critique_coros, return_exceptions=True)
        valid_critiques = [r for r in critiques if isinstance(r, dict)]
        debate_log.append(
            {"round": round_num, "type": "critique", "results": valid_critiques}
        )

        # Use critiques as new proposals for next round
        valid_proposals = valid_critiques

    # Final synthesis
    synth = Subagent(
        "synthesizer", SubagentType.SYNTHESIZER, agents[0].broker, agents[0].model
    )
    all_outputs = "\n\n---\n\n".join(
        f"Round {entry['round']} ({entry['type']}):\n"
        + "\n".join(r["result"][:500] for r in entry["results"])
        for entry in debate_log
    )
    synthesis = await synth.execute(
        f"Synthesize this debate into a final, refined answer:\n\n{all_outputs}\n\n"
        f"Produce the best possible answer incorporating all insights."
    )

    print(f"  ✅ Debate complete: {rounds + 1} rounds")

    return {"pattern": "debate", "debate_log": debate_log, "synthesis": synthesis}


async def run_map_reduce_swarm(
    task: str,
    agents: List[Subagent],
    subtasks: List[str],
) -> dict:
    """Map subtasks to agents, then reduce results."""
    print(f"\n🗺️ MAP-REDUCE SWARM: {len(agents)} agents, {len(subtasks)} subtasks")

    # Map phase
    map_results = []
    for i, subtask in enumerate(subtasks):
        agent = agents[i % len(agents)]
        print(
            f"  📍 Map {i + 1}/{len(subtasks)}: {agent.type.value} -> {subtask[:60]}..."
        )
        result = await agent.execute(subtask)
        map_results.append(result)

    # Reduce phase
    print("  🔻 Reduce phase...")
    combined = "\n\n---\n\n".join(
        f"Subtask: {subtasks[i]}\nResult: {r['result'][:1000]}"
        for i, r in enumerate(map_results)
    )

    synth = Subagent(
        "reducer", SubagentType.SYNTHESIZER, agents[0].broker, agents[0].model
    )
    reduction = await synth.execute(
        f"Combine these subtask results into a unified answer for: {task}\n\n{combined}"
    )

    print("  ✅ Map-reduce complete")

    return {"pattern": "map_reduce", "map_results": map_results, "reduction": reduction}


async def run_council_swarm(
    task: str,
    agents: List[Subagent],
) -> dict:
    """Agents propose and vote on the best solution."""
    print(f"\n🏛️ COUNCIL SWARM: {len(agents)} agents on: {task[:80]}...")

    # Phase 1: Proposals
    print("  📝 Proposals phase")
    coros = [agent.execute(task) for agent in agents]
    proposals = await asyncio.gather(*coros, return_exceptions=True)
    valid_proposals = [r for r in proposals if isinstance(r, dict)]

    # Phase 2: Each agent votes on best proposal
    print("  🗳️ Voting phase")
    proposals_text = "\n\n".join(
        f"Proposal {i + 1} (from {p['agent_id']}):\n{p['result'][:500]}..."
        for i, p in enumerate(valid_proposals)
    )

    vote_coros = []
    for agent in agents:
        vote_prompt = (
            f"Task: {task}\n\n"
            f"Proposals:\n{proposals_text[:3000]}\n\n"
            f"Vote for the best proposal. Reply with ONLY the proposal number (1-{len(valid_proposals)}) "
            f"and a brief reason."
        )
        vote_coros.append(agent.execute(vote_prompt))

    votes = await asyncio.gather(*vote_coros, return_exceptions=True)
    valid_votes = [r for r in votes if isinstance(r, dict)]

    print(f"  ✅ Council complete: {len(valid_votes)} votes cast")

    return {"pattern": "council", "proposals": valid_proposals, "votes": valid_votes}


async def run_pipeline_swarm(
    task: str,
    agents: List[Subagent],
) -> dict:
    """Fixed pipeline: plan -> code -> test -> review -> doc"""
    stages = ["plan", "code", "test", "review", "doc"]
    print(
        f"\n🔄 PIPELINE SWARM: {min(len(agents), len(stages))} stages on: {task[:80]}..."
    )

    pipeline_results = []
    context = ""

    for i, stage in enumerate(stages):
        if i >= len(agents):
            break
        agent = agents[i]
        stage_prompt = f"Pipeline stage '{stage}' for task: {task}\n\nPrevious stage output:\n{context[:2000]}"
        print(f"  🔄 Stage {i + 1}/{len(stages)}: {stage} ({agent.id})")
        result = await agent.execute(stage_prompt)
        pipeline_results.append({"stage": stage, "result": result})
        context = result["result"]

    print(f"  ✅ Pipeline complete: {len(pipeline_results)} stages")

    return {"pattern": "pipeline", "pipeline_results": pipeline_results}


# ─── Swarm Coordinator ──────────────────────────────────────────────────────────


class SwarmCoordinator:
    """Creates and manages the full swarm lifecycle."""

    def __init__(
        self,
        task: str,
        n_agents: int = 10,
        model: str = "free-llm",
        pattern: SwarmPattern = SwarmPattern.PARALLEL,
        agent_types: Optional[List[SubagentType]] = None,
        subtasks: Optional[List[str]] = None,
        debate_rounds: int = 2,
        max_tokens: int = 2048,
        temperature: float = 0.7,
    ):
        self.task = task
        self.n_agents = n_agents
        self.model = model
        self.pattern = pattern
        self.debate_rounds = debate_rounds
        self.max_tokens = max_tokens
        self.temperature = temperature
        self.subtasks = subtasks

        # Default agent type distribution
        if agent_types is None:
            self.agent_types = self._default_type_distribution(n_agents)
        else:
            self.agent_types = agent_types

        self.broker = A2ABroker()
        self.agents: List[Subagent] = []
        self.start_time = 0.0

    def _default_type_distribution(self, n: int) -> List[SubagentType]:
        """Create a diverse type distribution for the swarm."""
        types = [
            SubagentType.CODE,
            SubagentType.RESEARCH,
            SubagentType.REVIEW,
            SubagentType.PLAN,
            SubagentType.SECURITY,
            SubagentType.TEST,
            SubagentType.DEBUG,
            SubagentType.DOC,
            SubagentType.BUILD,
            SubagentType.DEVOPS,
        ]
        return [types[i % len(types)] for i in range(n)]

    def _create_agents(self) -> List[Subagent]:
        """Instantiate the swarm."""
        agents = []
        for i, atype in enumerate(self.agent_types):
            aid = f"agent-{i + 1:03d}-{atype.value}"
            agent = Subagent(
                agent_id=aid,
                agent_type=atype,
                broker=self.broker,
                model=self.model,
                max_tokens=self.max_tokens,
                temperature=self.temperature,
            )
            agents.append(agent)
        return agents

    async def launch(self) -> dict:
        """Launch the swarm and return results."""
        self.start_time = time.time()
        self.agents = self._create_agents()

        print(f"\n{'=' * 60}")
        print("🐝 A2A SWARM HARNESS — Launching")
        print(f"{'=' * 60}")
        print(f"  Task:      {self.task[:100]}")
        print(f"  Agents:    {len(self.agents)}")
        print(f"  Model:     {self.model}")
        print(f"  Pattern:   {self.pattern.value}")
        print(f"  Types:     {', '.join(set(t.value for t in self.agent_types))}")
        print(f"  FreeLLM:   {FREE_LLM_URL}")
        print(f"{'=' * 60}")

        # Subscribe to results topic
        results_q = self.broker.subscribe_topic("swarm_results")

        # Run the appropriate pattern
        if self.pattern == SwarmPattern.PARALLEL:
            result = await run_parallel_swarm(self.task, self.agents)
        elif self.pattern == SwarmPattern.CHAIN:
            result = await run_chain_swarm(self.task, self.agents)
        elif self.pattern == SwarmPattern.DEBATE:
            result = await run_debate_swarm(self.task, self.agents, self.debate_rounds)
        elif self.pattern == SwarmPattern.MAP_REDUCE:
            if not self.subtasks:
                # Auto-decompose with coordinator
                coord = Subagent(
                    "coordinator", SubagentType.COORDINATOR, self.broker, self.model
                )
                decomp = await coord.execute(
                    f"Decompose this task into {len(self.agents)} specific subtasks. "
                    f"Output ONLY a JSON array of strings, no other text.\n\nTask: {self.task}"
                )
                try:
                    # Try to parse JSON from the response
                    text = decomp["result"]
                    # Find JSON array in response
                    start = text.find("[")
                    end = text.rfind("]") + 1
                    if start >= 0 and end > start:
                        self.subtasks = json.loads(text[start:end])
                    else:
                        self.subtasks = [self.task] * len(self.agents)
                except (json.JSONDecodeError, ValueError):
                    self.subtasks = [self.task] * len(self.agents)
            result = await run_map_reduce_swarm(self.task, self.agents, self.subtasks)
        elif self.pattern == SwarmPattern.COUNCIL:
            result = await run_council_swarm(self.task, self.agents)
        elif self.pattern == SwarmPattern.PIPELINE:
            result = await run_pipeline_swarm(self.task, self.agents)
        else:
            result = await run_parallel_swarm(self.task, self.agents)

        elapsed = time.time() - self.start_time

        # Summary
        total_messages = len(self.broker.message_log)
        print(f"\n{'=' * 60}")
        print("🐝 SWARM COMPLETE")
        print(f"{'=' * 60}")
        print(f"  Duration:      {elapsed:.1f}s")
        print(f"  Agents:        {len(self.agents)}")
        print(f"  A2A Messages:  {total_messages}")
        print(f"  Pattern:       {self.pattern.value}")
        print(f"{'=' * 60}")

        result["meta"] = {
            "duration_seconds": elapsed,
            "n_agents": len(self.agents),
            "n_messages": total_messages,
            "model": self.model,
            "pattern": self.pattern.value,
        }

        return result


# ─── CLI ────────────────────────────────────────────────────────────────────────


def main():
    parser = argparse.ArgumentParser(
        description="A2A Swarm Harness — Giant swarms of LLM-powered subagents via FreeLLM",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Patterns:
  parallel     All agents work simultaneously, synthesizer combines (default)
  chain        Agents work sequentially, each building on previous
  debate       Agents propose, critique, and refine through rounds
  map_reduce   Coordinator decomposes task, agents map subtasks, reducer combines
  council      Agents propose solutions and vote on best
  pipeline     Fixed stages: plan -> code -> test -> review -> doc

Examples:
  python a2a_swarm.py --task "Find security issues" --agents 20
  python a2a_swarm.py --task "Write tests" --agents 5 --pattern chain
  python a2a_swarm.py --task "Review architecture" --agents 10 --pattern debate --rounds 3
  python a2a_swarm.py --task "Analyze codebase" --agents 8 --pattern map_reduce
  python a2a_swarm.py --task "Build feature" --agents 5 --pattern pipeline
  python a2a_swarm.py --task "Decide on framework" --agents 15 --pattern council
        """,
    )
    parser.add_argument("--task", "-t", required=True, help="The task for the swarm")
    parser.add_argument(
        "--agents", "-n", type=int, default=10, help="Number of agents (default: 10)"
    )
    parser.add_argument(
        "--model", "-m", default="free-llm", help="LLM model (default: free-llm)"
    )
    parser.add_argument(
        "--pattern",
        "-p",
        default="parallel",
        choices=["parallel", "chain", "debate", "map_reduce", "council", "pipeline"],
        help="Swarm pattern (default: parallel)",
    )
    parser.add_argument(
        "--rounds", "-r", type=int, default=2, help="Debate rounds (default: 2)"
    )
    parser.add_argument(
        "--max-tokens",
        type=int,
        default=2048,
        help="Max tokens per response (default: 2048)",
    )
    parser.add_argument(
        "--temperature", type=float, default=0.7, help="Temperature (default: 0.7)"
    )
    parser.add_argument("--output", "-o", help="Output file for results (JSON)")
    parser.add_argument(
        "--config", "-c", help="Config file (JSON) with swarm parameters"
    )
    parser.add_argument(
        "--url", default="http://localhost:4000", help="FreeLLM proxy URL"
    )
    parser.add_argument(
        "--dry-run", action="store_true", help="Print config and exit without launching"
    )

    args = parser.parse_args()

    global FREE_LLM_URL
    FREE_LLM_URL = args.url

    # Load config if provided
    if args.config:
        with open(args.config) as f:
            config = json.load(f)
        task = config.get("task", args.task)
        n_agents = config.get("agents", args.agents)
        model = config.get("model", args.model)
        pattern = SwarmPattern(config.get("pattern", args.pattern))
        subtasks = config.get("subtasks", None)
        debate_rounds = config.get("rounds", args.rounds)
        max_tokens = config.get("max_tokens", args.max_tokens)
        temperature = config.get("temperature", args.temperature)
    else:
        task = args.task
        n_agents = args.agents
        model = args.model
        pattern = SwarmPattern(args.pattern)
        subtasks = None
        debate_rounds = args.rounds
        max_tokens = args.max_tokens
        temperature = args.temperature

    coordinator = SwarmCoordinator(
        task=task,
        n_agents=n_agents,
        model=model,
        pattern=pattern,
        subtasks=subtasks,
        debate_rounds=debate_rounds,
        max_tokens=max_tokens,
        temperature=temperature,
    )

    if args.dry_run:
        print(
            json.dumps(
                {
                    "task": task,
                    "n_agents": n_agents,
                    "model": model,
                    "pattern": pattern.value,
                    "subtasks": subtasks,
                    "freellm_url": FREE_LLM_URL,
                    "agent_types": [t.value for t in coordinator.agent_types],
                },
                indent=2,
            )
        )
        return

    # Check FreeLLM health
    try:
        resp = httpx.get(f"{FREE_LLM_URL}/health", timeout=5.0)
        if resp.status_code != 200 or "healthy" not in resp.text.lower():
            print(
                f"⚠️  FreeLLM proxy at {FREE_LLM_URL} may not be healthy: {resp.text[:100]}"
            )
    except Exception as e:
        print(f"❌ FreeLLM proxy at {FREE_LLM_URL} is not reachable: {e}")
        print("   Start it with: cd litellm_control_panel && python start.bat")
        sys.exit(1)

    # Launch
    result = asyncio.run(coordinator.launch())

    # Output
    output_file = args.output or f"swarm_result_{int(time.time())}.json"
    with open(output_file, "w") as f:
        json.dump(result, f, indent=2, default=str)
    print(f"\n📄 Results saved to: {output_file}")


if __name__ == "__main__":
    main()
