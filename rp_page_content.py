import urllib.request
import re
import html
import sys
import difflib

sys.stdout.reconfigure(encoding="utf-8", errors="replace")
UA = {"User-Agent": "Mozilla/5.0 (compatible; audit)"}


def get(u):
    return (
        urllib.request.urlopen(urllib.request.Request(u, headers=UA), timeout=25)
        .read()
        .decode("utf-8", "replace")
    )


def visible(b):
    b = re.sub(r"<script.*?</script>", " ", b, flags=re.S | re.I)
    b = re.sub(r"<style.*?</style>", " ", b, flags=re.S | re.I)
    t = html.unescape(re.sub(r"<[^>]+>", " ", b))
    return re.sub(r"\s+", " ", t).strip()


a = get("https://robertpelloni.com/")
b = get("https://robertpelloni.com/page/2/")
c = get("https://robertpelloni.com/page/3/")
va, vb, vc = visible(a), visible(b), visible(c)

print("=== / visible text (first 1200) ===")
print(va[:1200])
print()
print("=== /page/2/ visible text (first 1200) ===")
print(vb[:1200])
print()
print("=== similarity ===")
print(f"  / vs /page/2/ : {difflib.SequenceMatcher(None, va, vb).ratio():.4f}")
print(f"  /page/2/ vs /page/3/: {difflib.SequenceMatcher(None, vb, vc).ratio():.4f}")
print()
# how many actual post permalinks are linked?
for name, body in ((" /", a), (" /page/2/", b), (" /page/3/", c)):
    posts = re.findall(r'href="https://robertpelloni\.com/(\d+-2)/"', body)
    print(f"  post links on {name}: {len(posts)} -> {posts[:6]}")
