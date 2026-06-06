#!/bin/bash
# LiteLLM Proxy v6 Watchdog - keeps the proxy running
# Usage: nohup bash ~/.hermes/litellm-watchdog.sh &

ACTIVATE="source /home/hyper/.hermes/venv-litellm/bin/activate"
ENV="source /home/hyper/.hermes/.env"
CONFIG="/home/hyper/.hermes/litellm-config.yaml"
LOG="/tmp/litellm_watchdog.log"
PORT=4000

while true; do
    # Check if proxy is responding
    if curl -s -m 3 "http://localhost:$PORT/v1/models" 2>/dev/null | grep -q "free-llm"; then
        sleep 30
        continue
    fi

    echo "$(date): Proxy down, restarting..." >> "$LOG"

    # Kill any stale processes
    pkill -f "litellm --config" 2>/dev/null
    sleep 2

    # Start proxy
    eval "$ACTIVATE && $ENV && nohup /home/hyper/.hermes/venv-litellm/bin/litellm --config $CONFIG --port $PORT --host 0.0.0.0 </dev/null >> $LOG 2>&1 &"

    # Wait for startup
    for i in $(seq 1 20); do
        if curl -s -m 3 "http://localhost:$PORT/v1/models" 2>/dev/null | grep -q "free-llm"; then
            echo "$(date): Proxy restarted successfully" >> "$LOG"
            break
        fi
        sleep 1
    done

    sleep 10
done
