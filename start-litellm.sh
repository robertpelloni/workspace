#!/bin/bash
# Start LiteLLM proxy v6 - multi-provider + aggressive fast-fail
set -a
source /home/hyper/.hermes/.env 2>/dev/null
set +a

VENV=/home/hyper/.hermes/venv-litellm/bin/activate
CONFIG=/home/hyper/.hermes/litellm-config.yaml
LOG=/tmp/litellm_run.log
PORT=4000

source "$VENV"

# Kill any existing litellm proxy
pkill -f "litellm --config" 2>/dev/null
sleep 2

# Verify config is valid YAML
python3 -c "import yaml; yaml.safe_load(open('$CONFIG'))" || {
    echo "ERROR: Config is invalid YAML"
    exit 1
}

# Start proxy
echo "Starting LiteLLM proxy on port $PORT..."
nohup litellm --config "$CONFIG" --port "$PORT" --host 0.0.0.0 </dev/null >> "$LOG" 2>&1 &
PID=$!
echo "PID=$PID"

# Wait for startup
for i in $(seq 1 15); do
    if curl -s -m 2 "http://localhost:$PORT/v1/models" 2>/dev/null | grep -q "free-llm"; then
        echo "LiteLLM proxy started (PID=$PID) on http://0.0.0.0:$PORT"
        echo "  free-llm -> Primary (NIM + Ollama Cloud)"
        echo "  free-llm-or -> OpenRouter fallback"
        echo "  free-llm-thinking -> Reasoning models"
        exit 0
    fi
    sleep 1
done

echo "ERROR: Proxy failed to start within 15s"
tail -20 "$LOG"
exit 1
