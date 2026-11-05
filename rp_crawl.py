import urllib.request
import urllib.error
import re
import sys
import concurrent.futures

sys.stdout.reconfigure(encoding="utf-8", errors="replace")

BASE = "https://robertpelloni.com"
UA = {"User-Agent": "Mozilla/5.0 (compatible; site-audit)"}


def get(u, timeout=20):
    try:
        r = urllib.request.urlopen(
            urllib.request.Request(u, headers=UA), timeout=timeout
        )
        return r.status, r.read().decode("utf-8", "replace"), r.geturl()
    except urllib.error.HTTPError as e:
        return e.code, e.read().decode("utf-8", "replace"), u
    except Exception as e:
        return None, str(e), u


# 1) every URL in the sitemap
idx = get(BASE + "/wp-sitemap.xml")[1]
maps = re.findall(r"<loc>([^<]+)</loc>", idx)
urls = []
for m in maps:
    body = get(m)[1]
    urls += re.findall(r"<loc>([^<]+)</loc>", body)
urls = sorted(set(urls))
print(f"sitemap URLs: {len(urls)}")

# 2) taxonomy / archive surfaces Google might know about
extra = []
for path in [
    "/",
    "/page/2/",
    "/page/3/",
    "/page/4/",
    "/page/5/",
    "/page/6/",
    "/page/7/",
    "/page/8/",
    "/feed/",
    "/comments/feed/",
    "/author/robertpelloni/",
    "/2026/",
    "/2026/09/",
    "/2026/08/",
    "/2026/07/",
    "/2025/",
    "/2024/",
]:
    extra.append(BASE + path)

print("\n=== checking sitemap URLs for non-200 ===")
bad = []
with concurrent.futures.ThreadPoolExecutor(max_workers=8) as ex:
    for u, (code, body, final) in zip(urls, ex.map(lambda x: get(x), urls)):
        if code != 200:
            bad.append((code, u, final))
for code, u, final in sorted(bad, key=lambda x: str(x[0])):
    print(f"  {code}  {u}" + (f"  -> {final}" if final != u else ""))
if not bad:
    print("  (all 200)")

print("\n=== checking archives / pagination for status + emptiness (soft-404) ===")
with concurrent.futures.ThreadPoolExecutor(max_workers=8) as ex:
    for u, (code, body, final) in zip(extra, ex.map(lambda x: get(x), extra)):
        if code is None:
            print(f"  ERR  {u}")
            continue
        # crude content measure: number of article-ish entries
        arts = len(re.findall(r"<article", body, re.I))
        text = re.sub(r"<[^>]+>", " ", body)
        text = re.sub(r"\s+", " ", text).strip()
        # strip boilerplate length
        thin = "THIN?" if len(text) < 1200 else ""
        print(f"  {code}  articles={arts:3d}  textlen={len(text):6d} {thin}  {u}")
