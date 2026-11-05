#!/bin/bash
echo "=== Stripe objects (via API) ==="
python3 - <<'PY'
import json, urllib.request, urllib.error
key = None
for line in open("/opt/marketing_agent/.env", encoding="utf-8"):
    if line.startswith("STRIPE_API_KEY="):
        key = line.split("=",1)[1].strip().strip('"').strip("'")
        break
def get(path):
    req = urllib.request.Request("https://api.stripe.com/v1"+path,
        headers={"Authorization":"Bearer "+key, "Stripe-Version":"2024-06-20"})
    return json.loads(urllib.request.urlopen(req, timeout=40).read().decode())

prod = get("/products/prod_VGtTGYu0Pv2KEt")
print(f"  product : {prod['id']}  active={prod['active']}")
print(f"            name    = {prod['name']}")
print(f"            desc    = {prod['description'][:70]}...")
print(f"            sku     = {prod.get('metadata',{}).get('sku')}")

pr = get("/prices/price_1UGLgsPISUNpi4xXPdwzxIDy")
print(f"  price   : {pr['id']}  active={pr['active']}")
print(f"            amount  = ${pr['unit_amount']/100:.2f} {pr['currency'].upper()}")
print(f"            type    = {'recurring' if pr.get('recurring') else 'ONE-TIME'}")

links = get("/payment_links?limit=100")["data"]
mine = [l for l in links if l.get("url","").endswith("5kQcN7b2JeQU91XcMe2Ji05")]
if mine:
    l = mine[0]
    print(f"  link    : {l['id']}  active={l['active']}")
    print(f"            url     = {l['url']}")
    print(f"            redirect= {l.get('after_completion',{}).get('redirect',{}).get('url')}")
PY
