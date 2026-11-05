import urllib.request
import urllib.error
import re
import html
import sys
import difflib

sys.stdout.reconfigure(encoding="utf-8", errors="replace")
UA = {"User-Agent": "Mozilla/5.0 (compatible; audit)"}


def get(u):
    try:
        r = urllib.request.urlopen(urllib.request.Request(u, headers=UA), timeout=25)
        return r.status, r.read().decode("utf-8", "replace"), r.geturl()
    except urllib.error.HTTPError as e:
        return e.code, e.read().decode("utf-8", "replace"), u
    except Exception as e:
        return None, str(e), u


def vis(b):
    b = re.sub(r"<script.*?</script>", " ", b, flags=re.S | re.I)
    b = re.sub(r"<style.*?</style>", " ", b, flags=re.S | re.I)
    return re.sub(r"\s+", " ", html.unescape(re.sub(r"<[^>]+>", " ", b))).strip()


print("=== where does the real blog paginate? ===")
for u in ["/posts/", "/posts/page/2/", "/posts/2/", "/page/2/"]:
    code, body, final = get("https://robertpelloni.com" + u)
    posts = re.findall(r'href="https://robertpelloni\.com/(\d+-2)/"', body)
    canon = re.findall(r'rel="canonical" href="([^"]+)"', body)
    title = re.findall(r"<title[^>]*>(.*?)</title>", body, re.S)
    print(
        f"  {code}  {u:20s} posts_linked={len(posts):3d}  canonical={(canon[0] if canon else '-')[:52]}"
    )

print()
print("=== author archive: duplicate of the blog? ===")
c1, b1, _ = get("https://robertpelloni.com/author/robertpelloni/")
c2, b2, _ = get("https://robertpelloni.com/author/robertpelloni/page/2/")
cp, bp, _ = get("https://robertpelloni.com/posts/")
print(
    f"  author archive      HTTP {c1}  vs /posts/ similarity: {difflib.SequenceMatcher(None, vis(b1), vis(bp)).ratio():.3f}"
)
print(f"  author page/2/      HTTP {c2}")

print()
print("=== empty date archives (404s Google is reporting) ===")
for m in [
    "2026/07",
    "2026/06",
    "2026/05",
    "2026/04",
    "2025/12",
    "2025/01",
    "2024/01",
    "2023/01",
]:
    code, _, _ = get(f"https://robertpelloni.com/{m}/")
    if code != 200:
        print(f"  {code}  /{m}/")

print()
print("=== category / tag archives ===")
for u in ["/category/old-stuff/", "/category/uncategorized/", "/tag/", "/category/"]:
    code, body, _ = get("https://robertpelloni.com" + u)
    posts = len(re.findall(r"<article", body, re.I))
    print(f"  {code}  {u:26s} articles={posts}  textlen={len(vis(body))}")
