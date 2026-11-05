import urllib.request
import re
import sys
import hashlib

sys.stdout.reconfigure(encoding="utf-8", errors="replace")
UA = {"User-Agent": "Mozilla/5.0 (compatible; audit)"}


def get(u):
    r = urllib.request.urlopen(urllib.request.Request(u, headers=UA), timeout=25)
    return r.read().decode("utf-8", "replace")


def links(body):
    return re.findall(r'href="https://robertpelloni\.com/([^"#?]+)/"', body)


seen = {}
for p in range(1, 6):
    u = (
        f"https://robertpelloni.com/page/{p}/"
        if p > 1
        else "https://robertpelloni.com/"
    )
    b = get(u)
    ls = links(b)
    h = hashlib.md5(b.encode()).hexdigest()[:12]
    canon = re.findall(r'rel="canonical" href="([^"]+)"', b)
    seen[p] = (h, ls, canon[0] if canon else None)
    print(
        f"page {p}: md5={h}  links={len(ls)}  canonical={canon[0] if canon else None}"
    )

print()
print("=== do page2 and page3 share the same post set? ===")
s2, s3 = set(seen[2][1]), set(seen[3][1])
common = s2 & s3
print(f"  page2 unique links: {len(s2)}")
print(f"  page3 unique links: {len(s3)}")
print(f"  overlap: {len(common)}")
if common:
    print("  sample overlap:", sorted(common)[:8])

print()
print("=== post titles per page (first 6) ===")
for p in (1, 2, 3):
    u = (
        f"https://robertpelloni.com/page/{p}/"
        if p > 1
        else "https://robertpelloni.com/"
    )
    b = get(u)
    titles = re.findall(r'class="entry-title"[^>]*>\s*<a[^>]*>(.*?)</a>', b, re.S)
    if not titles:
        titles = re.findall(
            r'<h[12][^>]*class="[^"]*entry-title[^"]*"[^>]*>(.*?)</h[12]>', b, re.S
        )
    titles = [re.sub(r"<[^>]+>", "", t).strip()[:58] for t in titles][:6]
    print(f"  --- page {p} ({len(titles)} shown) ---")
    for t in titles:
        print("     ", t)
