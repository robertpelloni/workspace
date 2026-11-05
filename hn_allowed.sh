#!/bin/bash
echo "=== allowedOrigin ==="
grep -n -B4 -A 28 "func allowedOrigin" /opt/marketing_agent/internal/web/server.go
