import urllib.request
import urllib.error
import re
import sys

sys.stdout.reconfigure(encoding="utf-8", errors="replace")
UA = {"User-Agent": "Mozilla/5.0 (compatible; audit)"}


def probe(u, follow=True):
    class NoRedirect(urllib.request.HTTPRedirectHandler):
        def redirect_request(self, *a, **k):
            return None

    op = (
        urllib.request.build_opener()
        if follow
        else urllib.request.build_opener(NoRedirect)
    )
    try:
        r = op.open(urllib.request.Request(u, headers=UA), timeout=25)
        return r.status, r.read().decode("utf-8", "replace"), r.geturl()
    except urllib.error.HTTPError as e:
        return e.code, e.read().decode("utf-8", "replace"), u
    except Exception as e:
        return None, str(e), u


print("=== 1. bogus front-page pagination (expect 301 -> /) ===")
for u in ["https://robertpelloni.com/page/2/", "https://robertpelloni.com/page/5/"]:
    code, body, final = probe(u, follow=False)
    loc = re.findall(r"(?i)^location:\s*(.+)$", body, re.M)
    print(f"  {code}  {u}  -> {loc[0].strip() if loc else final}")

print()
print("=== 2. blog now paginates (was 178 posts on one page) ===")
for u in [
    "https://robertpelloni.com/posts/",
    "https://robertpelloni.com/posts/page/2/",
    "https://robertpelloni.com/posts/page/3/",
]:
    code, body, _ = probe(u)
    posts = len(re.findall(r'href="https://robertpelloni\.com/\d+-2/"', body))
    canon = re.findall(r'rel="canonical" href="([^"]+)"', body)
    print(
        f"  {code}  {u:44s} posts={posts:3d}  canonical={(canon[0] if canon else '-').replace('https://robertpelloni.com', '')}"
    )

print()
print("=== 3. author archive noindexed ===")
code, body, _ = probe("https://robertpelloni.com/author/robertpelloni/")
rob = re.findall(r'name="robots" content="([^"]+)"', body)
print(f"  {code}  robots={rob[0] if rob else '(none)'}")

print()
print("=== 4. empty date archive (expect 301 -> blog) ===")
code, body, final = probe("https://robertpelloni.com/2026/07/", follow=False)
loc = re.findall(r"(?i)^location:\s*(.+)$", body, re.M)
print(f"  {code}  /2026/07/  -> {loc[0].strip() if loc else final}")

print()
print("=== 5. empty category soft-404 candidate ===")
code, body, _ = probe("https://robertpelloni.com/category/old-stuff/")
rob = re.findall(r'name="robots" content="([^"]+)"', body)
print(f"  {code}  /category/old-stuff/  robots={rob[0] if rob else '(none)'}")

print()
print("=== 6. feed size + noindex ===")
code, body, _ = probe("https://robertpelloni.com/feed/")
print(f"  {code}  /feed/  bytes={len(body)}")

print()
print("=== 7. per-post feed link removed from head? ===")
code, body, _ = probe("https://robertpelloni.com/41901-2/")
feeds = re.findall(
    r'<link[^>]*alternate[^>]*type="application/rss\+xml"[^>]*href="([^"]+)"', body
)
print(f"  feed <link>s in post head: {feeds if feeds else '(none)'}")

print()
print("=== 8. sitemap still valid ===")
code, body, _ = probe("https://robertpelloni.com/wp-sitemap.xml")
print(f"  {code}  child sitemaps={len(re.findall(r'<loc>', body))}")
