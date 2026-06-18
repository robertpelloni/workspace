import os
import shutil
from ruamel.yaml import YAML
from ruamel.yaml.comments import CommentedMap, CommentedSeq
import known_models

yaml = YAML()
yaml.preserve_quotes = True
yaml.indent(mapping=2, sequence=4, offset=2)

DEFAULT_CONFIG_PATH = "config.yaml"

# Provider -> freellm prefix + env var mapping
PROVIDER_MAP = {
    "openrouter": {"prefix": "openrouter", "env_key": "OPENROUTER_API_KEY"},
    "groq": {"prefix": "groq", "env_key": "GROQ_API_KEY"},
    "together": {"prefix": "together_ai", "env_key": "TOGETHER_API_KEY"},
    "deepinfra": {"prefix": "deepinfra", "env_key": "DEEPINFRA_API_KEY"},
    "cerebras": {"prefix": "cerebras", "env_key": "CEREBRAS_API_KEY"},
    "github": {
        "prefix": "openai",
        "env_key": "GITHUB_TOKEN",
        "api_base": "https://models.inference.ai.azure.com",
    },
    "gemini": {"prefix": "gemini", "env_key": "GEMINI_API_KEY"},
    "huggingface": {"prefix": "huggingface", "env_key": "HUGGINGFACE_API_KEY"},
    "nvidia": {"prefix": "nvidia_nim", "env_key": "NVIDIA_NIM_API_KEY"},
    "nvidia_nim": {"prefix": "nvidia_nim", "env_key": "NVIDIA_NIM_API_KEY"},
    "ollama": {"prefix": "ollama", "env_key": ""},
    "lm_studio": {
        "prefix": "openai",
        "env_key": "",
        "api_base": "http://localhost:1234/v1",
    },
    "mistral": {"prefix": "mistral", "env_key": "MISTRAL_API_KEY"},
    "codestral": {
        "prefix": "codestral",
        "env_key": "CODESTRAL_API_KEY",
        "api_base": "https://codestral.mistral.ai/v1",
    },
    "cohere": {"prefix": "cohere", "env_key": "COHERE_API_KEY"},
    "sambanova": {"prefix": "sambanova", "env_key": "SAMBANOVA_API_KEY"},
    "fireworks": {"prefix": "fireworks_ai", "env_key": "FIREWORKS_API_KEY"},
    "hyperbolic": {"prefix": "hyperbolic", "env_key": "HYPERBOLIC_API_KEY"},
    "nebius": {"prefix": "nebius", "env_key": "NEBIUS_API_KEY"},
    "cloudflare": {"prefix": "cloudflare", "env_key": "CLOUDFLARE_API_KEY"},
    "opencode_zen": {
        "prefix": "openai",
        "env_key": "",
        "api_base": "https://opencode.ai/zen/v1",
    },
}


# Providers with exhausted/depleted API keys that should never be included
DEAD_PROVIDERS = {"together", "gemini", "nebius"}  # Providers with no API key

# Keywords that identify non-chat models (TTS, ASR, image gen, safety, embedding, etc.)
NON_CHAT_KEYWORDS = {
    "whisper",
    "orpheus",
    "flux",
    "prompt-guard",
    "embed",
    "safety",
    "guard",
    "reward",
    "parse",
    "detect",
    "clip",
    "vision",
    "tts",
    "asr",
    "image-gen",
    "dall",
    "stable-diffusion",
    "midjourney",
    "canopylabs",
    "compound", "compound-mini",
    "compound:",
    "sdxl",
    "codellama",
}


# Models known to be dead/404/nonexistent on specific providers
DEAD_MODELS = {
    "deepseek-ai/deepseek-v3", "deepseek-ai/deepseek-r1",
    "qwen/qwen2.5-72b-instruct",
    "meta-llama/meta-llama-3.1-70b-instruct", "meta-llama/meta-llama-3.1-405b-instruct",
    "meta-llama/llama-3.1-70b-instruct", "meta-llama/llama-3.1-405b-instruct",
    "llama-4-scout-17b-16e-instruct",
    "orpheus-v1-english", "orpheus-arabic-saudi",
    "openai/gpt-oss-120b",
    "accounts/fireworks/models/gpt-oss-120b",
    "accounts/fireworks/models/flux-1-dev-fp8",
    "accounts/fireworks/models/flux-1-schnell-fp8",
    "accounts/fireworks/models/flux-kontext-pro",
    "accounts/fireworks/models/flux-kontext-max",
    "accounts/fireworks/models/kimi-k2p5",
    "accounts/fireworks/models/kimi-k2p6",
    "accounts/fireworks/models/deepseek-v4-pro",
    "accounts/fireworks/models/glm-5p1",
}


def _is_dead_model(model_id: str) -> bool:
    """Check if a model ID matches any entry in DEAD_MODELS (case-insensitive, prefix-stripping)."""
    _dl = {d.lower() for d in DEAD_MODELS}
    mid = model_id.lower()
    bare = mid.split("/", 1)[-1] if "/" in mid else mid
    return mid in _dl or bare in _dl



def _get_context_for_model(model_id: str, provider: str) -> int:
    """Look up context_length from known_models for a given model.

    Uses the lookup function which handles prefix stripping and tail matching.
    Returns the best context_length available, or 0 if unknown.
    """
    # Try with provider prefix first, then without
    for candidate in [f"{provider}/{model_id}", model_id]:
        known = known_models.lookup(candidate)
        if known and known.get("ctx", 0) > 0:
            return known["ctx"]
    # Default: models we know nothing about get 4096 (safe minimum)
    return 4096

def _build_model_entry(
    model_id: str,
    provider: str,
    group_name: str,
    timeout: int = 30,
    api_base: str | None = None,
    context_length: int = 0,
) -> CommentedMap:
    """Build a single model_list entry for the FreeLLM config as a CommentedMap."""
    info = PROVIDER_MAP.get(
        provider, {"prefix": provider, "env_key": f"{provider.upper()}_API_KEY"}
    )

    prefix = info["prefix"]
    # For github, we want the prefix to be 'openai' as per FreeLLM standards for Azure Inference
    if model_id.startswith(prefix + "/"):
        freellm_model = model_id
    else:
        freellm_model = f"{prefix}/{model_id}"

    entry = CommentedMap()
    entry["model_name"] = group_name

    lp = CommentedMap()
    lp["model"] = freellm_model
    lp["timeout"] = timeout
    # Per-model stream timeout: slow providers need more time for streaming chunks
    stream_timeout_providers = {"nvidia_nim", "nvidia", "openrouter", "huggingface", "sambanova"}
    if provider in stream_timeout_providers or timeout > 45:
        lp["stream_timeout"] = max(timeout * 5, 300)  # 5x non-stream, min 5 min

    env_key = info.get("env_key", "")
    if env_key:
        lp["api_key"] = f"os.environ/{env_key}"

    base = api_base or info.get("api_base")
    if base:
        # Resolve Cloudflare account_id placeholder
        if "{account_id}" in base:
            from settings_ui import load_settings

            _settings = load_settings()
            account_id = _settings.get("CLOUDFLARE_ACCOUNT_ID", "")
            if account_id:
                base = base.replace("{account_id}", account_id)
            else:
                base = ""  # Can't build URL without account_id
        if base:
            lp["api_base"] = base

    # Set max_tokens based on context_length to prevent overflow errors
    # (NVIDIA, OpenRouter etc. don't enforce this automatically)
    if context_length and context_length > 0:
        # Leave 256 tokens buffer for prompt overhead; cap output at 16K
        max_out = min(context_length - 256, 16384)
        if max_out > 0:
            lp["max_tokens"] = max_out

    entry["freellm_params"] = lp

    # Add metadata for model_info display
    metadata = CommentedMap()
    metadata["score"] = 0
    metadata["latency"] = 0
    if context_length:
        metadata["context"] = context_length
    entry["model_info"] = metadata

    # Mark providers that don't support function/tool calling
    # This prevents FreeLLM from routing tool-call requests to them
    no_tool_providers = {"nvidia_nim", "nvidia", "cerebras", "cloudflare", "deepinfra"}
    if provider in no_tool_providers:
        metadata["supports_function_calling"] = False

    # For nvidia_nim/nvidia: also set supported_params to exclude tools/tool_choice
    # so FreeLLM strips them before forwarding
    if provider in ("nvidia_nim", "nvidia"):
        lp["supported_params"] = [
            "max_tokens", "temperature", "top_p", "frequency_penalty",
            "presence_penalty", "stop", "n", "stream",
            "response_format", "seed", "logprobs", "top_logprobs",
        ]

    return entry


def read_config(path=DEFAULT_CONFIG_PATH):
    """Read and return the parsed config, or None if it doesn't exist."""
    if not os.path.exists(path):
        return None
    with open(path, "r", encoding="utf-8") as f:
        return yaml.load(f)


def write_config(config, path=DEFAULT_CONFIG_PATH):
    """Write config dict to yaml file."""
    with open(path, "w", encoding="utf-8") as f:
        yaml.dump(config, f)


def get_model_entries(path=DEFAULT_CONFIG_PATH):
    """Parse the config and return structured info about all model entries.
    Returns a list of dicts: {id, provider, group, freellm_model, api_key, api_base, timeout, raw_entry}
    """
    config = read_config(path)
    if not config or "model_list" not in config:
        return []

    entries = []
    for entry in config.get("model_list", []):
        if entry is None:
            continue
        model_name = entry.get("model_name", "")
        lp = entry.get("freellm_params", {})
        freellm_model = lp.get("model", "")

        provider = "unknown"
        model_id = freellm_model
        for prov_key, info in PROVIDER_MAP.items():
            prefix = info["prefix"]
            if freellm_model.startswith(prefix + "/"):
                provider = prov_key
                model_id = freellm_model[len(prefix) + 1 :]
                break

        entries.append(
            {
                "id": model_id,
                "provider": provider,
                "group": model_name,
                "freellm_model": freellm_model,
                "api_key": lp.get("api_key", ""),
                "api_base": lp.get("api_base", ""),
                "timeout": lp.get("timeout", 30),
                "raw_entry": entry,
            }
        )

    return entries


def get_groups(path=DEFAULT_CONFIG_PATH):
    """Return ordered dict of group_name -> list of model entries."""
    entries = get_model_entries(path)
    groups = {}
    group_order = []
    for e in entries:
        g = e["group"]
        if g not in groups:
            groups[g] = []
            group_order.append(g)
        groups[g].append(e)
    return groups, group_order


def apply_ranked_models(
    ranked_models: list,
    path=DEFAULT_CONFIG_PATH,
    primary_group="free-llm",
    fallback_group="free-llm-fallback",
    plain_group="free-llm-plain",
    primary_count=5,
):
    """Write the config merging benchmarked models with existing entries.
    ranked_models: list of dicts with at least: id, provider, latency, score, parameters
    primary_count: top N go into primary_group, rest into fallback_group

    Models from ranked_models are placed by score. Any models already in the
    config that were NOT in this benchmark run are preserved in fallback.
    Preserves router_settings, freellm_settings, and fallbacks structure.
    """
    # Filter out providers with exhausted/depleted API keys
    ranked_models = [
        m for m in ranked_models if m.get("provider", "") not in DEAD_PROVIDERS
    ]
    # Also filter out non-chat models (TTS, ASR, image gen, safety, etc.)
    ranked_models = [
        m
        for m in ranked_models
        if not any(kw in m.get("id", "").lower() for kw in NON_CHAT_KEYWORDS)
    ]

    # Read existing config for settings and existing model entries to preserve
    existing_config = read_config(path)
    router_settings = CommentedMap()
    freellm_settings = CommentedMap()
    existing_entries = {}  # model_id -> raw_entry (for preserving un-benchmarked models)
    if existing_config:
        if existing_config.get("router_settings"):
            router_settings = existing_config["router_settings"]
        if existing_config.get("freellm_settings"):
            freellm_settings = existing_config["freellm_settings"]
        # Collect existing model entries so we can preserve ones not in this benchmark
        for entry in existing_config.get("model_list", []):
            if entry is None:
                continue
            lp = entry.get("freellm_params", {})
            freellm_model = lp.get("model", "")
            if freellm_model:
                existing_entries[freellm_model] = entry

    # Identify which models from ranked_models are already in the config
    ranked_model_ids = set()
    for m in ranked_models:
        info = PROVIDER_MAP.get(
            m.get("provider", ""), {"prefix": m.get("provider", "")}
        )
        prefix = info.get("prefix", m.get("provider", ""))
        model_id = m["id"]
        freellm_model = (
            f"{prefix}/{model_id}"
            if not model_id.startswith(prefix + "/")
            else model_id
        )
        ranked_model_ids.add(freellm_model)

    # Build header comment with probe results
    import datetime

    now = datetime.datetime.now().strftime("%Y-%m-%d")

    comment_lines = [
        f"FreeLLM Config - Updated {now}",
        f"Three groups: {primary_group} (top {primary_count}) + {fallback_group} (tool-compatible) + {plain_group} (non-tool)",
        "Routing: simple-shuffle (picks smart models, not fast small ones)",
        f"Fallback: {primary_group} -> {fallback_group} (plain group {plain_group} for direct use only)",
        "",
        "PROBE RESULTS:",
    ]
    for m in ranked_models:
        ctx = m.get("context_length", "?")
        lat = m.get("latency", 0)
        score = m.get("score", 0)
        comment_lines.append(
            f"  {m['provider']}/{m['id']}  {lat:.1f}s score={score:.1f} ({ctx} ctx)"
        )

    # Filter out models that are effectively unusable
    MAX_LATENCY = 30.0  # seconds â€” models slower than this just time out
    DEAD_CFG_PROVIDERS = {"together", "gemini", "nebius"}  # no API keys
    before_count = len(ranked_models)
    ranked_models = [
        m for m in ranked_models
        if m.get("latency", 0) <= MAX_LATENCY
        and m.get("provider", "") not in DEAD_CFG_PROVIDERS
    ]
    filtered_count = before_count - len(ranked_models)
    if filtered_count:
        comment_lines.append(f"  (filtered {filtered_count} dead/high-latency models)")

    # Split models into tool-compatible and non-tool groups
    NO_TOOL_PROVIDERS = {"nvidia", "nvidia_nim", "cerebras", "cloudflare", "deepinfra"}
    tool_compatible = [m for m in ranked_models if m.get("provider", "") not in NO_TOOL_PROVIDERS]
    plain_only = [m for m in ranked_models if m.get("provider", "") in NO_TOOL_PROVIDERS]

    # Apply provider diversity to primary selection (max 2 per provider)
    MAX_PER_PROVIDER_PRIMARY = 2
    primary_selected = []
    provider_count = {}
    for m in tool_compatible:
        p = m.get("provider", "")
        if provider_count.get(p, 0) < MAX_PER_PROVIDER_PRIMARY:
            primary_selected.append(m)
            provider_count[p] = provider_count.get(p, 0) + 1
        if len(primary_selected) >= primary_count:
            break

    # Fallback = remaining tool-compatible not in primary
    primary_ids = {m["id"] for m in primary_selected}
    fallback_models = [m for m in tool_compatible if m["id"] not in primary_ids]

    # Cap primary_count
    effective_primary = min(primary_count, len(primary_selected))
    if effective_primary < 1 and len(primary_selected) > 0:
        effective_primary = 1

    # Build model_list as CommentedSeq
    model_list = CommentedSeq()

    # -- Primary group (tool-compatible only) --
    model_list.yaml_add_eol_comment("=== PRIMARY GROUP (tool-compatible) ===", 0)
    for i, m in enumerate(primary_selected[:primary_count]):
        timeout = 45 if m.get("latency", 0) > 4.0 else 30
        ctx = m.get("context_length", 0) or _get_context_for_model(
            m["id"], m["provider"]
        )
        entry = _build_model_entry(
            m["id"], m["provider"], primary_group, timeout, context_length=ctx
        )

        lat = m.get("latency", 0)
        score = m.get("score", 0)
        params = m.get("parameters", 0)
        ctx_str = (
            f"{ctx // 1000}K"
            if ctx and isinstance(ctx, (int, float)) and ctx > 0
            else "?"
        )
        comment_text = f"Rank {i + 1}: {m['id']} via {m['provider']} - {ctx_str} ctx, {lat:.1f}s, {params}B, score={score:.0f}"
        # Store actual score/latency/params in model_info
        if "model_info" in entry:
            entry["model_info"]["score"] = round(score, 2)
            entry["model_info"]["latency"] = round(lat, 3)
            entry["model_info"]["params"] = params
            entry["model_info"]["context"] = ctx

        model_list.append(entry)
        model_list.yaml_add_eol_comment(comment_text, i)

    # â”€â”€ Fallback group â”€â”€
    fallback_start = len(model_list)
    for j, m in enumerate(fallback_models):
        timeout = 60 if m.get("latency", 0) > 4.0 else 30
        ctx = m.get("context_length", 0) or _get_context_for_model(
            m["id"], m["provider"]
        )
        entry = _build_model_entry(
            m["id"], m["provider"], fallback_group, timeout, context_length=ctx
        )

        lat = m.get("latency", 0)
        params = m.get("parameters", 0)
        ctx_str = (
            f"{ctx // 1000}K"
            if ctx and isinstance(ctx, (int, float)) and ctx > 0
            else "?"
        )
        comment_text = (
            f"{m['id']} via {m['provider']} - {ctx_str} ctx, {lat:.1f}s, {params}B"
        )
        # Store actual score/latency/params in model_info
        if "model_info" in entry:
            entry["model_info"]["score"] = round(m.get("score", 0), 2)
            entry["model_info"]["latency"] = round(lat, 3)
            entry["model_info"]["params"] = params
            entry["model_info"]["context"] = ctx

        model_list.append(entry)
        model_list.yaml_add_eol_comment(comment_text, fallback_start + j)

    # ── Plain group (non-tool models: nvidia_nim, cerebras, etc.) ──
    plain_start = len(model_list)
    for j, m in enumerate(plain_only):
        timeout = 60 if m.get("latency", 0) > 4.0 else 30
        ctx = m.get("context_length", 0) or _get_context_for_model(
            m["id"], m["provider"]
        )
        entry = _build_model_entry(
            m["id"], m["provider"], plain_group, timeout, context_length=ctx
        )
        lat = m.get("latency", 0)
        score = m.get("score", 0)
        params = m.get("parameters", 0)
        if "model_info" in entry:
            entry["model_info"]["score"] = round(score, 2)
            entry["model_info"]["latency"] = round(lat, 3)
            entry["model_info"]["params"] = params
            entry["model_info"]["context"] = ctx
        model_list.append(entry)
        comment_text = f"{m['id']} via {m['provider']} (no-tool) - {lat:.1f}s, score={score:.0f}"
        model_list.yaml_add_eol_comment(comment_text, plain_start + j)

    # -- Plain group (non-tool models: nvidia, cerebras, etc.) --
    plain_start = len(model_list)
    for j, m in enumerate(plain_only):
        timeout = 60 if m.get("latency", 0) > 4.0 else 30
        ctx = m.get("context_length", 0) or _get_context_for_model(
            m["id"], m["provider"]
        )
        entry = _build_model_entry(
            m["id"], m["provider"], plain_group, timeout, context_length=ctx
        )
        lat = m.get("latency", 0)
        score = m.get("score", 0)
        params = m.get("parameters", 0)
        if "model_info" in entry:
            entry["model_info"]["score"] = round(score, 2)
            entry["model_info"]["latency"] = round(lat, 3)
            entry["model_info"]["params"] = params
            entry["model_info"]["context"] = ctx
        model_list.append(entry)
        comment_text = f"{m['id']} via {m['provider']} (no-tool) - {lat:.1f}s, score={score:.0f}"
        model_list.yaml_add_eol_comment(comment_text, plain_start + j)

    # Preserve existing models that were NOT in this benchmark run
    preserved_count = 0
    for freellm_model, entry in existing_entries.items():
        if freellm_model not in ranked_model_ids:
            # Skip dead providers (also catches variant prefixes like together_ai/)
            if any(p in freellm_model for p in DEAD_PROVIDERS):
                continue
            # Skip non-chat models
            if any(kw in freellm_model.lower() for kw in NON_CHAT_KEYWORDS):
                continue
            # Skip dead models
            if _is_dead_model(freellm_model):
                continue
            # Skip models with extreme latency (effectively dead)
            mi = entry.get("model_info", {})
            if mi and mi.get("latency", 0) > 30.0:
                continue
            # Skip models that were never benchmarked (score=0, latency=0)
            if mi and mi.get("score", 0) == 0 and mi.get("latency", 0) == 0:
                continue
            entry["model_name"] = fallback_group
            model_list.append(entry)
            preserved_count += 1
    if preserved_count:
        print(f"Preserved {preserved_count} existing models not in this benchmark.")

    # Ensure all known good models from our DB are present in the config
    # even if they weren't in the benchmark or existing config
    current_models_in_config = set()
    for entry in model_list:
        if entry is None:
            continue
        lp = entry.get("freellm_params", {})
        if lp:
            current_models_in_config.add(lp.get("model", ""))
    injected_count = 0
    MAX_FORCE_INJECT = 10  # Don't bloat the fallback group
    for freellm_id, spec in known_models.all_models().items():
        if injected_count >= MAX_FORCE_INJECT:
            break
        prov = spec.get("provider", "")
        if prov in DEAD_PROVIDERS:
            continue
        # Also skip if the freellm_model string contains a dead provider
        info = PROVIDER_MAP.get(prov, {"prefix": prov})
        prefix = info.get("prefix", prov)
        if any(p in prefix for p in DEAD_PROVIDERS):
            continue
        # Skip non-chat models (TTS, ASR, image gen, etc.)
        if any(kw in freellm_id.lower() for kw in NON_CHAT_KEYWORDS):
            continue
        # Skip tiny models (< 7B params)
        params = spec.get("params", 0)
        if params > 0 and params < 7:
            continue
        # Skip models with no context info
        if not spec.get("ctx", 0):
            continue
        info = PROVIDER_MAP.get(prov, {"prefix": prov})
        prefix = info.get("prefix", prov)
        # Calculate the actual freellm_model string that will be generated
        base_id = freellm_id.split("/", 1)[-1] if "/" in freellm_id else freellm_id
        target_model_name = (
            f"{prefix}/{base_id}"
            if not base_id.startswith(prefix + "/")
            else base_id
        )
        if target_model_name in current_models_in_config:
            continue
        # Only inject if we have the provider's API key mapped
        env_key = info.get("env_key", "")
        if not env_key:
            continue  # Local providers like ollama - skip auto-injection
        # Build entry from known model spec
        known_ctx = spec.get("ctx", 0)
        new_entry = _build_model_entry(
            base_id, prov, fallback_group,
            timeout=30,
            context_length=known_ctx,
        )
        model_list.append(new_entry)
        injected_count += 1
    if injected_count:
        print(f"Injected {injected_count} known good models from database.")

    # Build full config as CommentedMap
    config = CommentedMap()
    config["model_list"] = model_list

    # Router settings (preserve or default)
    if not router_settings:
        router_settings = CommentedMap(
            {
                "routing_strategy": "simple-shuffle",
                "cooldown_time": 30,
                "allowed_fails": 2,
                "num_retries": 2,
                "timeout": 30,
                "enable_pre_call_checks": False,
                "ignore_cooldown_on_fallbacks": True,
            }
        )
    else:
        # Always force this to False to prevent startup health check failures
        router_settings["enable_pre_call_checks"] = False

    config["router_settings"] = router_settings

    # FreeLLM settings (preserve or default)
    if not freellm_settings:
        freellm_settings = CommentedMap(
            {
                "drop_params": True,
                "num_retries": 2,
                "request_timeout": 30,
                "allowed_fails": 2,
                "cooldown_time": 30,
            }
        )

    # Ensure fallbacks are set
        freellm_settings["fallbacks"] = [{primary_group: [fallback_group]}]
        # Ensure critical timeout settings are present (upgrade old configs)
        if "stream_timeout" not in freellm_settings:
            freellm_settings["stream_timeout"] = 300  # 5 min for streaming
        if "request_timeout" not in freellm_settings or freellm_settings.get("request_timeout", 0) < 60:
            freellm_settings["request_timeout"] = 60  # 60s for non-streaming
        config["freellm_settings"] = freellm_settings

    # Port setting
    config["port"] = 4000

    # Add header comment
    header = "\n".join(comment_lines) + "\n"
    config.yaml_set_start_comment(header)

    # Backup existing config before overwriting
    if os.path.exists(path):
        shutil.copy2(path, path + ".bak")

    write_config(config, path)
    print(
        f"Applied {len(ranked_models)} models to {path} (primary={effective_primary}, fallback={len(ranked_models) - effective_primary})"
    )


def reorder_primary(
    models_in_primary: list,
    path=DEFAULT_CONFIG_PATH,
    primary_group="free-llm",
    fallback_group="free-llm-fallback",
):
    """Reorder models between primary and fallback groups without re-benchmarking.

    models_in_primary: list of model_id strings that should be in the primary group
    All other models go to fallback.

    This is for user-driven reordering: move a model up to primary, or down to fallback.
    """
    entries = get_model_entries(path)
    if not entries:
        print("No model entries found in config.")
        return

    # Split into primary and fallback based on user's selection
    primary_entries = [
        e
        for e in entries
        if e["id"] in models_in_primary or e["freellm_model"] in models_in_primary
    ]
    fallback_entries = [e for e in entries if e not in primary_entries]

    # Rebuild config preserving settings
    existing_config = read_config(path)
    router_settings = (
        existing_config.get("router_settings", CommentedMap())
        if existing_config
        else CommentedMap()
    )
    freellm_settings = (
        existing_config.get("freellm_settings", CommentedMap())
        if existing_config
        else CommentedMap()
    )

    model_list = CommentedSeq()
    for i, e in enumerate(primary_entries):
        entry = e["raw_entry"]
        entry["model_name"] = primary_group
        model_list.append(entry)
        model_list.yaml_add_eol_comment(f"Primary: {e['freellm_model']}", i)

    for j, e in enumerate(fallback_entries):
        entry = e["raw_entry"]
        entry["model_name"] = fallback_group
        model_list.append(entry)

    config = CommentedMap()
    config["model_list"] = model_list
    config["router_settings"] = router_settings
    config["freellm_settings"] = freellm_settings
    config["freellm_settings"]["fallbacks"] = [{primary_group: [fallback_group, "free-llm-plain"]}]

    # Backup and write
    if os.path.exists(path):
        shutil.copy2(path, path + ".bak")

    write_config(config, path)
    print(
        f"Reordered: {len(primary_entries)} primary, {len(fallback_entries)} fallback"
    )


def ensure_config_exists(path=DEFAULT_CONFIG_PATH):
    """Creates a basic FreeLLM config if it doesn't exist."""
    if not os.path.exists(path):
        config = CommentedMap()
        model_list = CommentedSeq()
        entry = CommentedMap(
            {
                "model_name": "free-llm",
                "freellm_params": CommentedMap(
                    {
                        "model": "openrouter/nvidia/nemotron-3-super-120b-a12b:free",
                        "api_key": "os.environ/OPENROUTER_API_KEY",
                        "timeout": 30,
                    }
                ),
            }
        )
        model_list.append(entry)
        config["model_list"] = model_list
        config["router_settings"] = CommentedMap(
            {
                "routing_strategy": "simple-shuffle",
                "cooldown_time": 30,
                "allowed_fails": 2,
                "num_retries": 2,
                "timeout": 30,
                "enable_pre_call_checks": False,
                "ignore_cooldown_on_fallbacks": True,
            }
        )
        config["freellm_settings"] = CommentedMap(
            {
                "drop_params": True,
                "num_retries": 2,
                "request_timeout": 30,
                "allowed_fails": 2,
                "cooldown_time": 30,
                "fallbacks": [{"free-llm": ["free-llm-fallback"]}],
            }
        )
        write_config(config, path)


# Legacy compatibility
def apply_model_to_freellm(model_id, provider_name, path=DEFAULT_CONFIG_PATH):
    """Legacy: updates a single model entry. Prefer apply_ranked_models for full config management."""
    print(
        "Note: apply_model_to_freellm is deprecated. Use apply_ranked_models for full config management."
    )
    ensure_config_exists(path)
    config = read_config(path)
    if config and "model_list" in config and len(config["model_list"]) > 0:
        info = PROVIDER_MAP.get(
            provider_name,
            {"prefix": provider_name, "env_key": f"{provider_name.upper()}_API_KEY"},
        )
        prefix = info["prefix"]
        freellm_model = (
            f"{prefix}/{model_id}"
            if not model_id.startswith(prefix + "/")
            else model_id
        )
        config["model_list"][0]["freellm_params"]["model"] = freellm_model
        if info.get("env_key"):
            config["model_list"][0]["freellm_params"]["api_key"] = (
                f"os.environ/{info['env_key']}"
            )
        if info.get("api_base"):
            config["model_list"][0]["freellm_params"]["api_base"] = info["api_base"]
        write_config(config, path)
        print(f"Updated first model entry to {freellm_model}")


if __name__ == "__main__":
    test_path = r"C:\Users\hyper\.hermes\freellm-config.yaml"
    groups, order = get_groups(test_path)
    print(f"Groups: {order}")
    for g in order:
        print(f"\n  {g}:")
        for e in groups[g]:
            print(
                f"    {e['freellm_model']} (provider={e['provider']}, timeout={e['timeout']})"
            )
