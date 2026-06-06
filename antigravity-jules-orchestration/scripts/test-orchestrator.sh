#!/bin/bash
# test-orchestrator.sh - Test the Jules Orchestrator API

API_URL="${API_URL:-http://localhost:3000}"

echo "🧪 Testing Jules Orchestrator API"
echo "=================================="
echo ""

# Test 1: Health check
echo "Test 1: Health check..."
response=$(curl -s -o /dev/null -w "% {http_code}" $API_URL/api/v1/health)
if [ "$response" = "200" ]; then
    echo "✅ Health check passed"
else
    echo "❌ Health check failed (HTTP $response)"
    exit 1
fi

# Test 2: Create workflow
echo ""
echo "Test 2: Creating test workflow..."
workflow=$(curl -s -X POST $API_URL/api/v1/workflows/execute \
    -H "Content-Type: application/json" \
    -d '{'
        "template_name": "dependency-update",
        "context": {
            "repo_name": "scarmonit/jules-orchestrator"
        }
    }')

workflow_id=$(echo $workflow | jq -r '.workflow_id')

if [ "$workflow_id" != "null" ]; then
    echo "✅ Workflow created: $workflow_id"
else
    echo "❌ Workflow creation failed"
    echo "$workflow"
    exit 1
fi

# Test 3: Get workflow status
echo ""
echo "Test 3: Checking workflow status..."
sleep 2
status=$(curl -s $API_URL/api/v1/workflows/$workflow_id)
current_status=$(echo $status | jq -r '.status')

if [ "$current_status" != "null" ]; then
    echo "✅ Workflow status: $current_status"
else
    echo "❌ Failed to get workflow status"
    exit 1
fi

# Test 4: Metrics endpoint
echo ""
echo "Test 4: Checking metrics..."
metrics=$(curl -s $API_URL/api/v1/metrics)

if echo "$metrics" | grep -q "workflow_total"; then
    echo "✅ Metrics endpoint working"
else
    echo "❌ Metrics endpoint failed"
    exit 1
fi

echo ""
echo "🎉 All tests passed!"
