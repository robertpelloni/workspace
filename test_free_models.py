#!/usr/bin/env python3
"""
Free Model Discovery and Testing Script
- Queries well-known inference providers for free models
- Tests models for availability and latency
- Sorts by score and latency
- Generates LiteLLM fallback configuration
"""

import json
import os
import subprocess
import sys
import time
from datetime import datetime

import requests
import yaml

# Well-known inference providers with free tiers
PROVIDERS = {
    "openrouter": {
        "base_url": "https://openrouter.ai/api/v1",
        "api_key_env": "OPENROUTER_API_KEY",
        "models_endpoint": "/models",
        "name": "OpenRouter",
    },
    "huggingface": {
        "base_url": "https://api-inference.huggingface.co",
        "api_key_env": "HF_API_KEY",
        "models_endpoint": None,  # No public model list endpoint
        "name": "HuggingFace Inference API",
    },
    "groq": {
        "base_url": "https://api.groq.com/openai/v1",
        "api_key_env": "GROQ_API_KEY",
        "models_endpoint": "/models",
        "name": "Groq",
    },
    "together": {
        "base_url": "https://api.together.xyz/v1",
        "api_key_env": "TOGETHER_API_KEY",
        "models_endpoint": "/models",
        "name": "Together AI",
    },
    "cerebras": {
        "base_url": "https://api.cerebras.ai/v1",
        "api_key_env": "CEREBRAS_API_KEY",
        "models_endpoint": "/models",
        "name": "Cerebras",
    },
    "nebius": {
        "base_url": "https://api.studio.nebius.ai/v1",
        "api_key_env": "NEBIUS_API_KEY",
        "models_endpoint": "/models",
        "name": "Nebius AI Studio",
    },
}


def load_existing_freellm_config(path: str) -> list:
    """Load existing models from freellm-config.yaml"""
    try:
        with open(path, "r") as f:
            config = yaml.safe_load(f)
        return config.get("model_list", [])
    except Exception as e:
        print(f"Warning: Could not load existing config: {e}")
        return []


def query_provider_models(provider_name: str, provider_config: dict) -> list:
    """Query a provider for their available models"""
    api_key = os.getenv(provider_config["api_key_env"])
    if not api_key:
        print(f"  ⚠️  No API key for {provider_name} (env: {provider_config['api_key_env']})")
        return []

    if not provider_config.get("models_endpoint"):
        print(f"  ℹ️  {provider_name} has no public model list endpoint")
        return []

    url = provider_config["base_url"] + provider_config["models_endpoint"]
    headers = {"Authorization": f"Bearer {api_key}"}

    try:
        print(f"  Querying {provider_name}...")
        response = requests.get(url, headers=headers, timeout=30)
        response.raise_for_status()
        data = response.json()

        models = []
        if "data" in data:
            for model in data["data"]:
                model_id = model.get("id", "")
                # Try to identify free models
                is_free = any(
                    indicator in model_id.lower()
                    for indicator in ["free", ":free", "flash", "nano", "mini", "rapid"]
                )
                if is_free or provider_name in ["groq", "cerebras"]:  # These are mostly free
                    models.append(
                        {
                            "provider": provider_name,
                            "model_id": model_id,
                            "is_free": is_free,
                            "context_window": model.get("context_window", None),
                        }
                    )
        print(f"  ✓ Found {len(models)} candidate models from {provider_name}")
        return models
    except Exception as e:
        print(f"  ✗ Error querying {provider_name}: {e}")
        return []


def test_model_endpoint(model_id: str, provider: str, config: dict) -> dict:
    """Test a model endpoint for availability and latency"""
    api_key = os.getenv(config["api_key_env"])
    if not api_key:
        return {"available": False, "latency": None, "error": "No API key"}

    url = config["base_url"] + "/chat/completions"
    headers = {
        "Authorization": f"Bearer {api_key}",
        "Content-Type": "application/json",
    }

    payload = {
        "model": model_id,
        "messages": [{"role": "user", "content": "Hi"}],
        "max_tokens": 5,
    }

    start = time.time()
    try:
        response = requests.post(url, headers=headers, json=payload, timeout=15)
        latency = time.time() - start

        if response.status_code == 200:
            return {"available": True, "latency": latency, "error": None}
        else:
            return {
                "available": False,
                "latency": latency,
                "error": f"HTTP {response.status_code}",
            }
    except requests.Timeout:
        return {"available": False, "latency": None, "error": "Timeout"}
    except Exception as e:
        return {"available": False, "latency": None, "error": str(e)}


def calculate_score(model_info: dict) -> float:
    """Calculate a composite score for a model"""
    # Higher is better: context window, availability
    # Lower is better: latency
    base_score = 0.0

    if model_info.get("available"):
        base_score += 1.0

    latency = model_info.get("latency")
    if latency:
        # Score inversely proportional to latency (max 2 points for <1s)
        base_score += max(0, 2.0 - latency)

    context = model_info.get("context_window", 0) or 0
    if context:
        # Up to 1 point for large context (128k+)
        base_score += min(1.0, context / 131072)

    return base_score


def generate_litellm_config(top_models: list, output_path: str):
    """Generate LiteLLM proxy config with top 5 models as fallback chain"""
    config = {
        "model_list": [],
        "litellm_settings": {
            "drop_params": True,
            "num_retries": 3,
            "request_timeout": 60,
        },
        "router_settings": {
            "routing_strategy": "simple-shuffle",
        },
    }

    # Add top 5 models as fallback chain
    for i, model in enumerate(top_models[:5]):
        model_name = f"free-model-{i+1}"
        model_entry = {
            "model_name": model_name,
            "litellm_params": {
                "model": model["full_id"],
                "timeout": 30,
                "max_tokens": 4096,
            },
            "model_info": {
                "score": model["score"],
                "latency": model["latency"],
                "context": model.get("context_window", None),
            },
        }

        # Add API key if available
        provider = model["provider"]
        api_key_env = PROVIDERS.get(provider, {}).get("api_key_env")
        if api_key_env:
            model_entry["litellm_params"]["api_key"] = (
                f"os.environ/{api_key_env}"
            )

        config["model_list"].append(model_entry)

    # Create fallback group
    if top_models:
        fallback_models = [f"free-model-{i+1}" for i in range(min(5, len(top_models)))]
        config["litellm_settings"]["context_window_fallbacks"] = [
            {model_group: fallback_models[1:]} for model_group in fallback_models
        ]

    with open(output_path, "w") as f:
        yaml.dump(config, f, default_flow_style=False, sort_keys=False)

    print(f"\n✓ Generated LiteLLM config: {output_path}")


def main():
    print("=" * 60)
    print("Free Model Discovery and Testing")
    print("=" * 60)

    # Step 1: Load existing freellm config
    print("\n1. Loading existing freellm-config.yaml...")
    existing_models = load_existing_freellm_config(
        "/mnt/c/Users/hyper/workspace/freellm/freellm-config.yaml"
    )
    print(f"   Found {len(existing_models)} existing model entries")

    # Step 2: Query providers for models
    print("\n2. Querying inference providers for free models...")
    all_models = []
    for provider_name, provider_config in PROVIDERS.items():
        models = query_provider_models(provider_name, provider_config)
        all_models.extend(models)

    print(f"\n   Total candidate models: {len(all_models)}")

    # Step 3: Test models for availability and latency
    print("\n3. Testing models for availability and latency...")
    tested_models = []
    for i, model in enumerate(all_models[:20]):  # Test top 20 candidates
        print(
            f"   Testing [{i+1}/{len(all_models[:20])}] {model['provider']}/{model['model_id']}..."
        )
        provider_config = PROVIDERS.get(model["provider"])
        if not provider_config:
            continue

        result = test_model_endpoint(
            model["model_id"], model["provider"], provider_config
        )

        tested_models.append(
            {
                **model,
                "full_id": f"{model['provider']}/{model['model_id']}",
                "available": result["available"],
                "latency": result["latency"],
                "error": result["error"],
            }
        )

    # Step 4: Calculate scores and sort
    print("\n4. Calculating scores and sorting...")
    for model in tested_models:
        model["score"] = calculate_score(model)

    # Sort by: available first, then score (desc), then latency (asc)
    tested_models.sort(
        key=lambda x: (
            -int(x["available"]),  # Available first
            -x["score"],  # Higher score first
            x["latency"] if x["latency"] else float("inf"),  # Lower latency first
        )
    )

    # Step 5: Display results
    print("\n" + "=" * 60)
    print("TOP 10 FREE MODELS (sorted by score & latency)")
    print("=" * 60)
    for i, model in enumerate(tested_models[:10]):
        status = "✓" if model["available"] else "✗"
        # Build a formatted line safely without nested quotes
        if model.get('latency') is not None:
            line = f"{i+1:2d}. [{status}] {model['full_id']:<50} Score: {model['score']:.2f} Latency: {model['latency']:.3f}s"
        else:
            line = f"{i+1:2d}. [{status}] {model['full_id']:<50} Score: {model['score']:.2f} Latency: N/A"
        print(line)

    # Step 6: Generate LiteLLM config
    print("\n5. Generating LiteLLM configuration...")
    top_5 = [m for m in tested_models if m["available"]][:5]
    if top_5:
        generate_litellm_config(
            top_5, "/mnt/c/Users/hyper/workspace/litellm/top-free-models.yaml"
        )
    else:
        print("   ⚠️  No available models found to generate config")

    # Save results
    results = {
        "timestamp": datetime.now().isoformat(),
        "total_tested": len(tested_models),
        "available": len([m for m in tested_models if m["available"]]),
        "top_5": [
            {
                "model": m["full_id"],
                "provider": m["provider"],
                "score": m["score"],
                "latency": m["latency"],
            }
            for m in top_5
        ],
    }

    with open("/tmp/model_test_results.json", "w") as f:
        json.dump(results, f, indent=2)

    print("\n✓ Results saved to /tmp/model_test_results.json")
    print("\nDone!")


if __name__ == "__main__":
    main()