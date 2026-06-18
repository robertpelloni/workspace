"""
Known Good Models -- authoritative specs for models that don't self-report.

Providers frequently omit parameter counts and context window sizes from
their API metadata. This file is the single source of truth for model
specifications that the Control Panel uses to ensure these models are
always ranked correctly.

Update this dictionary as new frontier/free models are discovered.
"""

# key: freellm_model string (as it appears in config/API calls)
# values: params (billions), ctx (tokens), provider

KNOWN_MODELS = {
    # -- GitHub Models (Azure Inference) --
    # Only models confirmed available on models.inference.ai.azure.com
    "github/Meta-Llama-3.1-405B-Instruct": {"params": 405, "ctx": 128000, "provider": "github"},
    "github/Meta-Llama-3.1-8B-Instruct": {"params": 8, "ctx": 131072, "provider": "github"},
    "github/gpt-4o": {"params": 175, "ctx": 128000, "provider": "github"},
    "github/gpt-4o-mini": {"params": 8, "ctx": 128000, "provider": "github"},

    # -- OpenRouter Free Models (confirmed active 2025-06) --
    "openrouter/google/gemma-4-31b-it:free": {"params": 27, "ctx": 131072, "provider": "openrouter"},
    "openrouter/google/gemma-4-26b-a4b-it:free": {"params": 26, "ctx": 131072, "provider": "openrouter"},
    "openrouter/nvidia/nemotron-3-super-120b-a12b:free": {"params": 120, "ctx": 4096, "provider": "openrouter"},
    "openrouter/nvidia/nemotron-3-nano-30b-a3b:free": {"params": 30, "ctx": 4096, "provider": "openrouter"},
    "openrouter/openai/gpt-oss-120b:free": {"params": 120, "ctx": 131072, "provider": "openrouter"},
    "openrouter/openai/gpt-oss-20b:free": {"params": 20, "ctx": 131072, "provider": "openrouter"},
    "openrouter/z-ai/glm-4.5-air:free": {"params": 14, "ctx": 131072, "provider": "openrouter"},

    # -- NVIDIA NIM Models (tested working 2025-06) --
    "nvidia/meta/llama-3.3-70b-instruct": {"params": 70, "ctx": 128000, "provider": "nvidia"},
    "nvidia/meta/llama-3.1-8b-instruct": {"params": 8, "ctx": 128000, "provider": "nvidia"},
    "nvidia/mistralai/mistral-large-3-675b-instruct-2512": {"params": 675, "ctx": 128000, "provider": "nvidia"},
    "nvidia/mistralai/mistral-small-4-119b-2603": {"params": 119, "ctx": 128000, "provider": "nvidia"},
    "nvidia/mistralai/ministral-14b-instruct-2512": {"params": 14, "ctx": 128000, "provider": "nvidia"},
    "nvidia/nvidia/llama-3.3-nemotron-super-49b-v1": {"params": 49, "ctx": 4096, "provider": "nvidia"},
    "nvidia/nvidia/llama-3.3-nemotron-super-49b-v1.5": {"params": 49, "ctx": 4096, "provider": "nvidia"},
    "nvidia/nvidia/nemotron-3-super-120b-a12b": {"params": 120, "ctx": 4096, "provider": "nvidia"},
    "nvidia/openai/gpt-oss-120b": {"params": 120, "ctx": 131072, "provider": "nvidia"},
    "nvidia/openai/gpt-oss-20b": {"params": 20, "ctx": 131072, "provider": "nvidia"},
    "nvidia/qwen/qwen3-next-80b-a3b-instruct": {"params": 80, "ctx": 131072, "provider": "nvidia"},
    "nvidia/qwen/qwen3.5-122b-a10b": {"params": 122, "ctx": 131072, "provider": "nvidia"},
    "nvidia/moonshotai/kimi-k2.6": {"params": 200, "ctx": 131072, "provider": "nvidia"},
    "nvidia/nvidia/nvidia-nemotron-nano-9b-v2": {"params": 9, "ctx": 4096, "provider": "nvidia"},

    # -- Groq Models (current, not decommissioned) --
    "groq/llama-3.3-70b-versatile": {"params": 70, "ctx": 128000, "provider": "groq"},
    "groq/llama-3.1-8b-instant": {"params": 8, "ctx": 131072, "provider": "groq"},

    # -- Cerebras Models --
    "cerebras/llama-3.3-70b": {"params": 70, "ctx": 131072, "provider": "cerebras"},
    "cerebras/llama3.1-8b": {"params": 8, "ctx": 131072, "provider": "cerebras"},

    # -- DeepInfra Models --
    "deepinfra/meta-llama/Meta-Llama-3.1-405B-Instruct": {"params": 405, "ctx": 131072, "provider": "deepinfra"},
    "deepinfra/meta-llama/Meta-Llama-3.1-70B-Instruct": {"params": 70, "ctx": 131072, "provider": "deepinfra"},
    "deepinfra/Qwen/Qwen2.5-72B-Instruct": {"params": 72, "ctx": 131072, "provider": "deepinfra"},
    "deepinfra/deepseek-ai/DeepSeek-V3": {"params": 671, "ctx": 65536, "provider": "deepinfra"},
    "deepinfra/deepseek-ai/DeepSeek-R1": {"params": 671, "ctx": 65536, "provider": "deepinfra"},

    # -- HuggingFace Models --
    "huggingface/meta-llama/Llama-3.1-405B-Instruct": {"params": 405, "ctx": 131072, "provider": "huggingface"},
    "huggingface/meta-llama/Llama-3.1-70B-Instruct": {"params": 70, "ctx": 131072, "provider": "huggingface"},
    "huggingface/deepseek-ai/DeepSeek-V3": {"params": 671, "ctx": 65536, "provider": "huggingface"},

    # -- Together Models --
    "together/meta-llama/Meta-Llama-3.1-405B-Instruct-Turbo": {"params": 405, "ctx": 131072, "provider": "together"},
    "together/meta-llama/Meta-Llama-3.1-70B-Instruct-Turbo": {"params": 70, "ctx": 131072, "provider": "together"},

    # -- Mistral La Plateforme --
    "mistral/mistral-large-latest": {"params": 123, "ctx": 128000, "provider": "mistral"},
    "mistral/mistral-medium-latest": {"params": 35, "ctx": 128000, "provider": "mistral"},
    "mistral/mistral-small-latest": {"params": 22, "ctx": 128000, "provider": "mistral"},
    "mistral/open-mistral-nemo": {"params": 12, "ctx": 128000, "provider": "mistral"},
    "mistral/codestral-latest": {"params": 22, "ctx": 256000, "provider": "mistral"},

    # -- Codestral (separate endpoint) --
    "codestral/codestral-latest": {"params": 22, "ctx": 256000, "provider": "codestral"},

    # -- Cohere --
    "cohere/command-a-03-2025": {"params": 111, "ctx": 288000, "provider": "cohere"},
    "cohere/command-a-plus-05-2026": {"params": 111, "ctx": 128000, "provider": "cohere"},
    "cohere/command-a-reasoning-08-2025": {"params": 111, "ctx": 128000, "provider": "cohere"},
    "cohere/command-a-translate-08-2025": {"params": 111, "ctx": 8992, "provider": "cohere"},
    "cohere/command-a-vision-07-2025": {"params": 111, "ctx": 128000, "provider": "cohere"},
    "cohere/command-r-plus-08-2024": {"params": 104, "ctx": 128000, "provider": "cohere"},
    "cohere/command-r-08-2024": {"params": 52, "ctx": 128000, "provider": "cohere"},
    "cohere/c4ai-aya-expanse-32b": {"params": 32, "ctx": 128000, "provider": "cohere"},

    # -- SambaNova Cloud --
    "sambanova/DeepSeek-V3.1": {"params": 671, "ctx": 65536, "provider": "sambanova"},
    "sambanova/DeepSeek-V3.2": {"params": 671, "ctx": 65536, "provider": "sambanova"},
    "sambanova/gpt-oss-120b": {"params": 120, "ctx": 131072, "provider": "sambanova"},
    "sambanova/Llama-4-Maverick-17B-128E-Instruct": {"params": 400, "ctx": 1048576, "provider": "sambanova"},
    "sambanova/Meta-Llama-3.3-70B-Instruct": {"params": 70, "ctx": 128000, "provider": "sambanova"},
    "sambanova/MiniMax-M2.7": {"params": 456, "ctx": 65536, "provider": "sambanova"},
    "sambanova/gemma-3-12b-it": {"params": 12, "ctx": 128000, "provider": "sambanova"},
    "sambanova/gemma-4-31B-it": {"params": 31, "ctx": 128000, "provider": "sambanova"},

    # -- Cloudflare Workers AI --
    "cloudflare/@cf/openai/gpt-oss-120b": {"params": 120, "ctx": 4096, "provider": "cloudflare"},
    "cloudflare/@cf/nvidia/nemotron-3-120b-a12b": {"params": 120, "ctx": 4096, "provider": "cloudflare"},
    "cloudflare/@cf/moonshotai/kimi-k2.5": {"params": 200, "ctx": 4096, "provider": "cloudflare"},
    "cloudflare/@cf/moonshotai/kimi-k2.6": {"params": 200, "ctx": 4096, "provider": "cloudflare"},
    "cloudflare/@cf/meta/llama-3.3-70b-instruct-fp8-fast": {"params": 70, "ctx": 4096, "provider": "cloudflare"},
    "cloudflare/@cf/qwen/qwen3-30b-a3b-fp8": {"params": 30, "ctx": 4096, "provider": "cloudflare"},
    "cloudflare/@cf/qwen/qwq-32b": {"params": 32, "ctx": 4096, "provider": "cloudflare"},
    "cloudflare/@cf/deepseek-ai/deepseek-r1-distill-qwen-32b": {"params": 32, "ctx": 4096, "provider": "cloudflare"},
    "cloudflare/@cf/mistralai/mistral-small-3.1-24b-instruct": {"params": 24, "ctx": 4096, "provider": "cloudflare"},
    "cloudflare/@cf/meta/llama-4-scout-17b-16e-instruct": {"params": 109, "ctx": 4096, "provider": "cloudflare"},
    "cloudflare/@cf/google/gemma-4-26b-a4b-it": {"params": 26, "ctx": 4096, "provider": "cloudflare"},

    # -- OpenCode Zen (free, no key needed) --
    "opencode_zen/big-pickle": {"params": 120, "ctx": 4096, "provider": "opencode_zen"},
    "opencode_zen/nemotron-3-super-free": {"params": 120, "ctx": 4096, "provider": "opencode_zen"},
    "opencode_zen/deepseek-v4-flash-free": {"params": 671, "ctx": 65536, "provider": "opencode_zen"},
    "opencode_zen/mimo-v2.5-free": {"params": 200, "ctx": 4096, "provider": "opencode_zen"},
    "opencode_zen/qwen3.6-plus-free": {"params": 200, "ctx": 4096, "provider": "opencode_zen"},
    "opencode_zen/minimax-m2.5-free": {"params": 456, "ctx": 65536, "provider": "opencode_zen"},

    # -- Ollama / LM Studio (local) --
    "ollama/llama3.3:70b": {"params": 70, "ctx": 128000, "provider": "ollama"},
    "ollama/deepseek-r1:671b": {"params": 671, "ctx": 65536, "provider": "ollama"},
    "ollama/qwen2.5:72b": {"params": 72, "ctx": 131072, "provider": "ollama"},

    # -- Gemini (Google AI Studio) --
    "gemini/gemini-2.5-pro": {"params": 0, "ctx": 2000000, "provider": "gemini"},
    "gemini/gemini-2.5-flash": {"params": 0, "ctx": 1000000, "provider": "gemini"},
    "gemini/gemini-2.0-flash": {"params": 0, "ctx": 1000000, "provider": "gemini"},
    "gemini/gemini-1.5-pro": {"params": 0, "ctx": 2000000, "provider": "gemini"},
    "gemini/gemini-1.5-flash": {"params": 0, "ctx": 1000000, "provider": "gemini"},
}


def lookup(freellm_model: str) -> dict | None:
    """Look up a model by its full freellm model string.

    Tries: exact match, then stripping provider prefix, then tail match.
    Returns {"params": int, "ctx": int, "provider": str} or None.
    """
    # Exact match
    if freellm_model in KNOWN_MODELS:
        return KNOWN_MODELS[freellm_model]

    # Try stripping provider prefixes
    for prefix in ("openrouter/", "nvidia_nim/", "github/", "groq/",
                   "together/", "deepinfra/", "cerebras/", "huggingface/",
                   "ollama/", "openai/", "lm_studio/", "gemini/",
                   "mistral/", "codestral/", "cohere/", "sambanova/",
                   "fireworks/", "hyperbolic/", "nebius/", "cloudflare/",
                   "opencode_zen/"):
        if freellm_model.startswith(prefix):
            stripped = freellm_model[len(prefix):]
            if stripped in KNOWN_MODELS:
                return KNOWN_MODELS[stripped]
            # Try the reverse: the stripped name might match a key that uses
            # a different prefix
            for known_id, info in KNOWN_MODELS.items():
                if known_id.endswith("/" + stripped) or known_id.endswith(stripped):
                    return info

    # Tail match: model_id ends with a known key
    model_tail = freellm_model.split("/")[-1] if "/" in freellm_model else freellm_model
    for known_id, info in KNOWN_MODELS.items():
        known_tail = known_id.split("/")[-1] if "/" in known_id else known_id
        if model_tail == known_tail:
            return info
        if freellm_model.endswith(known_tail):
            return info

    return None


def add_model(freellm_model: str, params: int, ctx: int, provider: str):
    """Add or update a model in the known models dict at runtime."""
    KNOWN_MODELS[freellm_model] = {"params": params, "ctx": ctx, "provider": provider}


def remove_model(freellm_model: str):
    """Remove a model from the known models dict at runtime."""
    KNOWN_MODELS.pop(freellm_model, None)


def all_models() -> dict:
    """Return the full known models dictionary."""
    return dict(KNOWN_MODELS)
