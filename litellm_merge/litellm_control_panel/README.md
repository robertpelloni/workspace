# LiteLLM Control Panel v2.0.0

A powerful, autonomous Windows system tray utility for intelligent LLM routing, benchmarking, and proxy management.

LiteLLM Control Panel ensures your high-performance LLM workflows always hit the best available models. It automatically benchmarks free, massive models (>= 100B parameters) across a wide array of providers and dynamically updates your routing configuration.

## 🚀 Key Features

- **Autonomous Two-Group Routing**: Automatically manages `free-llm` (primary) and `free-llm-fallback` groups in your config.
- **Real-time Performance Benchmarking**: Measures TTFT (Time-To-First-Token) using asynchronous streaming.
- **Multi-Provider Ecosystem**:
  - **Cloud Providers**: **GitHub Models**, **Hugging Face**, **NVIDIA NIM**, OpenRouter, Groq, Together AI, DeepInfra, and Cerebras.
  - **Local Providers**: Ollama and LM Studio.
- **Deep Windows Integration**:
  - Smart System Tray icon with dynamic color states (Health, Working, Offline).
  - Native Windows notifications for model switches and health alerts.
  - "Start with Windows" persistence.
- **Operational Tools**:
  - **Main Dashboard**: Full oversight of rankings, scores, and provider health.
  - **Quick Query**: A minimalist chat interface for instant model testing.
  - **Advanced Log Viewer**: Real-time monitoring of LiteLLM proxy output with search/filter.
  - **Maintenance Suite**: Tools to clear skips, manage blacklists, and backup/restore configurations.

## 🛠️ Quick Start

1. **Run `setup.bat`**: Installs all required Python dependencies.
2. **Run `start.bat`**: Launches the control panel in your system tray.

*Configure your API keys for GitHub, Hugging Face, NVIDIA NIM, and others in the **Settings** panel (right-click tray icon).*

## 📐 Adaptive Scoring & Intelligence

The router uses a configurable weighted algorithm to rank models:
- **Parameter Size (60%)**: Favors high-capability models.
- **Context Length (20%)**: Prioritizes larger windows for complex tasks.
- **Latency (20%)**: Penalizes slow response times.

**Smart Features**:
- **Circuit Breaker**: Automatically isolates failing endpoints for 2 hours.
- **Provider Learning**: Flags and skips providers that consistently fail to provide free models.
- **Local Cache**: Reuses local model benchmarks for 15 minutes to save resources.

## ⚙️ Configuration Safety

- **Structure Preservation**: Uses `ruamel.yaml` to ensure your `.hermes` or local LiteLLM config comments and formatting are never lost.
- **Automated Lifecycle**: Control Panel can automatically start and stop the LiteLLM proxy process.

---
*Optimized for high-performance developer environments on Windows.*
