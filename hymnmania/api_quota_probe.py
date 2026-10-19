"""Measure the API QUOTA side (separate from YouTube's ~100/day upload limit).

RESULT (2026-09-12): this approach is limited in practice - `search.list` is
rate-limited to roughly 100-125 requests before the API starts returning
HTTP 429 (Too Many Requests), so it cannot burn enough quota to reach
`quotaExceeded`. Kept for reference only.

What we DO know about the API quota (measured via uploads):
  99 videos.insert calls succeeded = 158,400 units consumed, with NO quotaExceeded.
  => the project's API quota is at least ~158,400 units/day (default is 10,000,
     which would have stopped us at 6 uploads).
  => 100 full videos/day = 160,000 units FITS in the API quota.
  The binding limit is YouTube's ~100 uploads/day per-channel platform limit
  (error: uploadLimitExceeded), not the API quota.

  python api_quota_probe.py [max_searches]
"""
import sys, time
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
import post_to_youtube as p

MAX = int(sys.argv[1]) if len(sys.argv) > 1 else 2000
yt = p.get_service()
COST = 100  # search.list units

ok = 0
t0 = time.time()
for i in range(1, MAX + 1):
    try:
        yt.search().list(part="snippet", q="psytrance hymn", maxResults=1, type="video").execute()
        ok += 1
        if i % 25 == 0:
            print(f"  {i} searches OK (~{i * COST:,} units burned this run)", flush=True)
    except Exception as e:
        msg = str(e)
        if "quotaExceeded" in msg or "dailyLimitExceeded" in msg:
            print(f"\n*** API QUOTA EXHAUSTED after {ok} searches ***")
            print(f"    this run burned ~{ok * COST:,} units")
            break
        print(f"  search {i}: other error: {msg[:120]}")
        time.sleep(1)
print(f"\nelapsed {time.time() - t0:.0f}s")
