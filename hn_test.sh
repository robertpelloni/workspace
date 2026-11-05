#!/bin/bash
echo "=== 1) nginx proxy via localhost (bypasses Cloudflare) ==="
curl -s -o /tmp/ck.json -w "HTTP %{http_code}\n" \
	-X POST https://aimoneymachine.site/api/v1/billing/checkout \
	--resolve aimoneymachine.site:443:127.0.0.1 \
	-H "Content-Type: application/json" \
	-d '{"tier":"HONEST_WORK_DESK_ONBOARDING","seats":1,"price_amount":1000,"success_url":"https://aimoneymachine.site/honest-work-desk?paid=1","cancel_url":"https://aimoneymachine.site/honest-work-desk?cancelled=1"}' \
	-k 2>&1
echo "--- response ---"
head -c 400 /tmp/ck.json
echo
echo
echo "=== 2) direct to the Go service on 8084 ==="
curl -s -o /tmp/ck2.json -w "HTTP %{http_code}\n" \
	-X POST http://127.0.0.1:8084/api/v1/billing/checkout \
	-H "Content-Type: application/json" \
	-d '{"tier":"HONEST_WORK_DESK_ONBOARDING","seats":1,"price_amount":1000,"success_url":"https://aimoneymachine.site/honest-work-desk?paid=1","cancel_url":"https://aimoneymachine.site/honest-work-desk?cancelled=1"}' 2>&1
head -c 400 /tmp/ck2.json
echo
