import urllib.request
import urllib.error
import re
import sys

sys.stdout.reconfigure(encoding="utf-8", errors="replace")
UA = {"User-Agent": "Mozilla/5.0 (compatible; audit)"}


def probe(u, follow=True):
    class NR(urllib.request.HTTPRedirectHandler):
        def redirect_request(self, *a, **k):
            return None

    op = urllib.request.build_opener() if follow else urllib.request.build_opener(NR)
    try:
        r = op.open(urllib.request.Request(u, headers=UA), timeout=25)
        return r.status, r.read().decode("utf-8", "replace"), r.geturl()
    except urllib.error.HTTPError as e:
        return e.code, e.read().decode("utf-8", "replace"), u
    except Exception as e:
        return None, str(e), u


def robots_of(body):
    m = re.findall(
        r"""<meta[^>]*name=['"]robots['"][^>]*content=['"]([^'"]+)""", body, re.I
    )
    return m


def canon_of(body):
    m = re.findall(r"""rel=['"]canonical['"][^>]*href=['"]([^'"]+)""", body, re.I)
    return m


print("=== robots meta per surface (expect noindex on author/empty) ===")
for u in [
    "/",
    "/posts/",
    "/author/robertpelloni/",
    "/category/old-stuff/",
    "/category/uncategorized/",
    "/41901-2/",
    "/?s=test",
]:
    code, body, _ = probe("https://robertpelloni.com" + u)
    rs = robots_of(body)
    dup = "  <-- DUPLICATE METAS!" if len(rs) > 1 else ""
    print(f"  {code}  {u:30s} {rs}{dup}")

print()
print("=== date archives (expect 301 -> /posts/) ===")
for u in ["/2026/07/", "/2025/01/", "/2024/01/"]:
    code, body, final = probe("https://robertpelloni.com" + u, follow=False)
    loc = re.findall(r"(?i)^location:\s*(.+)$", body, re.M)
    print(f"  {code}  {u:14s} -> {loc[0].strip() if loc else final}")

print()
print("=== canonicals ===")
for u in [
    "/posts/",
    "/posts/page/2/",
    "/author/robertpelloni/",
    "/category/uncategorized/",
    "/41901-2/",
]:
    code, body, _ = probe("https://robertpelloni.com" + u)
    print(
        f"  {u:32s} -> {[c.replace('https://robertpelloni.com', '') for c in canon_of(body)]}"
    )

print()
print("=== feed sizes ===")
for u in ["/feed/", "/comments/feed/"]:
    code, body, _ = probe("https://robertpelloni.com" + u)
    print(f"  {code}  {u:18s} bytes={len(body)}")

print()
print("=== per-post feed (was discovered via head link) ===")
code, body, _ = probe("https://robertpelloni.com/41901-2/feed/")
print(f"  {code}  /41901-2/feed/  (no longer linked from head)")
