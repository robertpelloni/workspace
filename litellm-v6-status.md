# LiteLLM Proxy v6 - Status and Configuration

## Proxy Status: RUNNING
- URL: http://localhost:4000/v1 (WSL) / http://172.21.116.32:4000/v1 (Windows)
- Models: 46 total (44 healthy, 2 temporarily unhealthy)
- Watchdog: Active (auto-restarts if proxy dies)

## Model Groups
| Group | Count | Purpose | Provider Priority |
|-------|-------|---------|-------------------|
| free-llm | 26 | Primary routing | Ollama Cloud -> NVIDIA NIM |
| free-llm-or | 11 | OpenRouter fallback | OpenRouter :free models |
| free-llm-thinking | 9 | Reasoning models | Ollama Cloud -> NIM -> OR |

## Providers
| Provider | Models | Status | Endpoint |
|----------|--------|--------|----------|
| NVIDIA NIM | 22 | Free, often overloaded | integrate.api.nvidia.com/v1 |
| Ollama Cloud | 11 | Free, reliable | ollama.com/v1 |
| OpenRouter | 13 | Free :free tier | openrouter.ai/api/v1 |
| Cline | 0 | No REST API (VS Code only) | - |
| OpenCode Zen | 0 | 403 Forbidden | - |
| Kilocode | 0 | No REST API (VS Code only) | - |

## Fast-Fail Configuration
- num_retries=0: Never retry, immediate fallback
- allowed_fails=1: One failure = instant cooldown
- disable_cooldowns=True: Fallback chain never breaks
- cooldown_time=5s: Quick recovery window
- request_timeout=6s: Fast dead model detection
- routing_strategy=latency-based-routing: Picks fastest healthy model

## Fallback Chains
- free-llm -> free-llm-or (NIM+Ollama down -> OpenRouter catches)
- free-llm-thinking -> free-llm (thinking down -> direct models)
- free-llm-or -> free-llm (OR down -> try NIM+Ollama)
- default: free-llm-or

## Bugs Fixed From v5
1. nvidia_nim/ prefix hangs -> openai/ + api_base
2. ollama/ prefix uses wrong endpoint -> openai/ + api_base
3. num_retries=3 wasted 90s+ per failure -> num_retries=0
4. All models in cooldown broke fallback -> disable_cooldowns=True
5. ignore_cooldown_on_fallbacks unsupported -> disable_cooldowns=True
6. enable_pre_call_checks crashed on unknown models -> disabled
7. model_prices lookup failed -> model_info.mode=chat on all
8. request_timeout=120 waited forever -> request_timeout=6

## Start/Stop
- Start proxy: bash ~/.hermes/start-litellm.sh
- Start watchdog: nohup bash ~/.hermes/litellm-watchdog.sh &
- Test proxy: python3 ~/.hermes/test-litellm.py
- Health check: curl -s http://localhost:4000/health
- Stop proxy: pkill -f "litellm --config"

## Config Files
- Main config: ~/.hermes/litellm-config.yaml
- Alt config: ~/.hermes/litellm_config.yaml (synced copy)
- Start script: ~/.hermes/start-litellm.sh
- Watchdog: ~/.hermes/litellm-watchdog.sh
- Test suite: ~/.hermes/test-litellm.py
- Env vars: ~/.hermes/.env
- Logs: /tmp/litellm_run.log
