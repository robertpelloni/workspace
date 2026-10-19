"""HymnMania unified scheduler — posts ONE ready track across all platforms.

Uses ONLY the verified flows (2026-09-10):
  YouTube full + Short : post_to_youtube.py (API, quality-gated)
  TikTok               : tt_post.post_video   (port 9222, handles 'Post now' modal)
  Facebook Reel        : fb_reel_post.py      (waits for copyright check to clear)
  Instagram Reel       : ig_cdp_post.post     (keyboard.type caption BEFORE Share)
  Facebook feed (opt)  : daily_scheduler      (link post fallback)

Browser split (IMPORTANT):
  9222 / edge-cdp-profile  -> Facebook, Instagram, TikTok (social logins)
  9333 / .dedicated-edge-profile -> Suno only (cover generation)

Usage:
  python scheduler_v2.py --test        # dry run: show the queue
  python scheduler_v2.py --now         # post the next ready track everywhere
  python scheduler_v2.py --now 3       # post the next 3 tracks
  python scheduler_v2.py --daemon      # run one cycle per day at RUN_HOUR (weekdays)
"""
import os, sys, json, io, time, random, datetime, subprocess, glob
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
sys.stdout.reconfigure(encoding="utf-8", errors="replace")

ROOT = os.path.dirname(os.path.abspath(__file__))
BEAT_DIR = os.path.join(ROOT, "pipeline_output", "beat_videos")
SHORT_DIR = os.path.join(ROOT, "pipeline_output", "shorts")
LOG_FILE = os.path.join(ROOT, ".scheduler_log.json")
SOCIAL_PORT = 9222
RUN_HOUR = 15          # 3 PM local
QUALITY_THRESHOLD = 1000

# ---- YouTube upload budget -------------------------------------------------
# A FULL video and a SHORT both cost the SAME: videos.insert = 1,600 units.
# They share ONE daily pool (quota resets at midnight Pacific Time).
# Default Google quota = 10,000 units/day -> 6 uploads/day.
# This project has historically done 118 uploads in a day (2026-07-23) with a single
# OAuth project, so its quota has clearly been increased. We still cap ourselves to
# stay well clear of the limit; set to 0 for unlimited.
MAX_UPLOADS_PER_DAY = 96      # full + shorts combined (measured platform limit ~99-100)
YT_UPLOAD_COST = 1600         # units per videos.insert

# Daily posting volume: each track = 1 full video + 1 Short (= 2 YouTube uploads)
# plus a Facebook feed post, TikTok, Facebook Reel and Instagram Reel.
# 6 tracks => 6 fulls + 6 shorts = 12 uploads (well under the ~96/100 cap).
TRACKS_PER_RUN = 6

# YouTube gets the volume (6 fulls + 6 shorts); the OTHER platforms stay at their
# previous cadence (ONE post per platform per day) to avoid spam heuristics.
# The first track of each run is the one that also goes to FB feed / TikTok / FB Reel / IG.
SOCIAL_TRACKS_PER_DAY = 1

# Genre mix: psytrance is the channel identity, so 2 of every 3 tracks should be
# psytrance (verified in-tempo - see gen_psytrance_tempo.py).
PSYTRANCE_RATIO = 2      # psytrance-family tracks per 1 non-psy track
FULLON_RATIO = 2         # Full-On tracks per 1 other psy sub-genre

# the psytrance family (matched against the built title)
PSY_FAMILY = ("full-on", "goa trance", "progressive psytrance", "psytrance",
              "darkpsy", "forest psy", "hi-tech", "psychill", "zenonesque")
UPLOAD_COUNTER = None         # set below

# Hymns REMOVED from the pool (see BLOCKED_HYMNS.md):
#   - blocked by Suno ACRCloud copyright fingerprint (uploads rejected)
#   - Just Over The Mountains: passes upload but every cover generates degraded
BLOCKED_HYMNS = {
    "ohappyday", "happyday",
    "kumbayah",
    "brighten",
    "leyenda",
    "justoverthemountains", "jotm",
    "praisehim",
}

# Classical pieces belong to a DIFFERENT channel (see CLASSICAL_PIECES.md) --
# never post them on the hymn channel. Their titles use the "Classical Remix" format.
EXCLUDE_CLASSICAL = True

FFM = r"C:\Users\jakeg\AppData\Local\Microsoft\WinGet\Packages\Gyan.FFmpeg_Microsoft.Winget.Source_8wekyb3d8bbwe\ffmpeg-9.0.1-full_build\bin\ffmpeg.exe"


# ---------------------------------------------------------------- logging
def load_log():
    if os.path.exists(LOG_FILE):
        try:
            return json.load(open(LOG_FILE, encoding="utf-8"))
        except Exception:
            return {}
    return {}


def save_log(log):
    json.dump(log, open(LOG_FILE, "w", encoding="utf-8"), indent=1)


def mark(beat_file, platform, url=""):
    log = load_log()
    e = log.setdefault(beat_file, {"posted": [], "urls": {}})
    if platform not in e["posted"]:
        e["posted"].append(platform)
    if url:
        e["urls"][platform] = url
    e["last"] = datetime.datetime.now().isoformat()
    save_log(log)
    if platform in ("youtube-full", "youtube-short"):
        bump_upload_count()


def _counter_path():
    return os.path.join(ROOT, ".yt_uploads.json")


def uploads_today():
    """Number of YouTube uploads (full + shorts) made today."""
    try:
        d = json.load(open(_counter_path(), encoding="utf-8"))
    except Exception:
        d = {}
    return int(d.get(datetime.date.today().isoformat(), 0))


def bump_upload_count(n=1):
    p = _counter_path()
    try:
        d = json.load(open(p, encoding="utf-8"))
    except Exception:
        d = {}
    k = datetime.date.today().isoformat()
    d[k] = int(d.get(k, 0)) + n
    # keep the file small
    d = {k2: v for k2, v in list(d.items())[-14:]}
    json.dump(d, open(p, "w", encoding="utf-8"), indent=1)


def upload_budget_ok(verbose=True):
    """True if we may still upload today."""
    if not MAX_UPLOADS_PER_DAY:
        return True
    used = uploads_today()
    if used >= MAX_UPLOADS_PER_DAY:
        if verbose:
            print(f"  YouTube daily cap reached ({used}/{MAX_UPLOADS_PER_DAY} uploads; "
                  f"~{used * YT_UPLOAD_COST:,} units). Stopping.")
        return False
    return True


def posted_today():
    """True if any track was successfully posted today (full or short)."""
    today = datetime.date.today().isoformat()
    for e in load_log().values():
        if e.get("last", "").startswith(today):
            return True
    return False


def already(beat_file, platform):
    return platform in load_log().get(beat_file, {}).get("posted", [])


# ---------------------------------------------------------------- quality
def spectral_centroid(f, seconds=25):
    import numpy as np, tempfile
    tmp = tempfile.mktemp(suffix=".f32")
    subprocess.run([FFM, "-y", "-loglevel", "error", "-i", f, "-t", str(seconds),
                    "-ac", "1", "-ar", "48000", "-f", "f32le", tmp], capture_output=True)
    d = np.frombuffer(open(tmp, "rb").read(), dtype=np.float32)
    os.remove(tmp)
    cents = []
    for i in range(0, len(d) - 2048, 2048):
        sp = np.abs(np.fft.rfft(d[i:i + 2048] * np.hanning(2048)))
        fr = np.fft.rfftfreq(2048, 1 / 48000)
        if sp.sum() > 0:
            cents.append((sp * fr).sum() / sp.sum())
    return round(float(np.mean(cents)), 1) if cents else 0


def is_real_cover(beat_file):
    c = spectral_centroid(os.path.join(BEAT_DIR, beat_file))
    return c >= QUALITY_THRESHOLD, c


def not_looped(path):
    """False if the 48s-repeat capture bug is present."""
    try:
        import cap_cycle
        tmp = os.path.join(SHORT_DIR, "_gatecheck.mp3")
        subprocess.run([FFM, "-y", "-loglevel", "error", "-i", path, "-ac", "1",
                        "-ar", "48000", tmp], capture_output=True)
        ls = cap_cycle.loop_score(tmp)
        os.remove(tmp)
        return ls <= 0.9, ls
    except Exception:
        return True, 0.0


def no_mid_gap(path, max_gap=3.0):
    """False if there is a long silence in the middle of the track (stitching artifact).
    Intro/outro fades (first/last 4s) are ignored."""
    import numpy as np, tempfile
    try:
        tmp = tempfile.mktemp(suffix=".f32")
        subprocess.run([FFM, "-y", "-loglevel", "error", "-i", path, "-ac", "1",
                        "-ar", "4000", "-f", "f32le", tmp], capture_output=True)
        d = np.frombuffer(open(tmp, "rb").read(), dtype=np.float32)
        os.remove(tmp)
        rms = [float(np.sqrt(np.mean(d[i * 4000:(i + 1) * 4000] ** 2)))
               for i in range(len(d) // 4000)]
        core = rms[4:-4] if len(rms) > 12 else rms
        run = worst = 0
        for x in core:
            if x < 0.004:
                run += 1
                worst = max(worst, run)
            else:
                run = 0
        return worst < max_gap, worst
    except Exception:
        return True, 0


def is_short(path):
    """True if the video is <=70s (already a short, don't make another)."""
    try:
        FFP = os.path.join(os.path.dirname(FFM), "ffprobe.exe")
        r = subprocess.run([FFP, "-v", "quiet", "-show_entries", "format=duration",
                            "-of", "csv=p=0", path], capture_output=True, text=True)
        return float(r.stdout.strip() or 0) <= 70
    except Exception:
        return False


def uploads_planned(beat_file):
    """How many YouTube uploads this track still needs (full and/or short)."""
    n = 0
    if not already(beat_file, "youtube-full"):
        n += 1
    if not already(beat_file, "youtube-short"):
        n += 1
    return n


# ---------------------------------------------------------------- queue
def channel_titles():
    try:
        import post_to_youtube as p
        yt = p.get_service()
        ch = yt.channels().list(part="contentDetails", mine=True).execute()
        upl = ch["items"][0]["contentDetails"]["relatedPlaylists"]["uploads"]
        titles, pt = set(), None
        for _ in range(60):
            r = yt.playlistItems().list(part="snippet", playlistId=upl,
                                        maxResults=50, pageToken=pt).execute()
            for it in r.get("items", []):
                titles.add(it["snippet"]["title"].lower().replace(" #shorts", ""))
            pt = r.get("nextPageToken")
            if not pt:
                break
        return titles
    except Exception as e:
        print(f"  (channel lookup failed: {str(e)[:50]})")
        return set()


def get_queue(verbose=True):
    """Full-length, real-audio, non-looped beat videos never posted to YouTube."""
    import post_to_youtube as p
    posted = channel_titles()
    log = load_log()
    queue = []
    for b in sorted(os.listdir(BEAT_DIR)):
        if not b.endswith(".mp4") or b.startswith("_"):
            continue
        path = os.path.join(BEAT_DIR, b)
        if is_short(path):
            continue
        # skip hymns removed from the pool (Suno-blocked / degraded)
        bkey = b.lower().replace("_", "").replace("-", "").replace(" ", "")
        if any(k in bkey for k in BLOCKED_HYMNS):
            if verbose:
                print(f"  skip (blocked hymn): {b[:50]}")
            continue
        try:
            t = p.build_title(b)
        except Exception:
            t = None
        if not t or t.lower() in posted:
            continue
        # classical pieces go to a DIFFERENT channel
        if EXCLUDE_CLASSICAL and ("classical remix" in t.lower()):
            if verbose:
                print(f"  skip (classical -> other channel): {b[:50]}")
            continue
        if "youtube-full" in log.get(b, {}).get("posted", []):
            continue
        ok, c = is_real_cover(b)
        if not ok:
            if verbose:
                print(f"  skip (sine/sheet-music, centroid={c}): {b[:50]}")
            continue
        good, ls = not_looped(path)
        if not good:
            if verbose:
                print(f"  skip (48s-loop bug, score={ls}): {b[:50]}")
            continue
        complete, gap = no_mid_gap(path)
        if not complete:
            if verbose:
                print(f"  skip (mid-song silence {gap}s - incomplete/stitched): {b[:50]}")
            continue
        queue.append(b)
    queue = order_for_ratio(queue)
    if verbose:
        import post_to_youtube as _p
        psy = sum(1 for b in queue if "psytrance" in (_p.build_title(b) or "").lower())
        print(f"  queue: {len(queue)} ready track(s) ({psy} psytrance)")
    return queue


def order_for_ratio(queue, psy_ratio=PSYTRANCE_RATIO, fullon_ratio=FULLON_RATIO):
    """Two-level weighting of the posting queue:
       1. psytrance family : other genres        = psy_ratio   : 1
       2. inside the family: Full-On : other psy = fullon_ratio : 1
    """
    import post_to_youtube as p
    psy_full, psy_other, other = [], [], []
    for b in queue:
        t = (p.build_title(b) or "").lower()
        if "full-on" in t:
            psy_full.append(b)
        elif any(k in t for k in PSY_FAMILY):
            psy_other.append(b)
        else:
            other.append(b)

    # level 2 - Full-On vs the rest of the family
    psy, i, j = [], 0, 0
    while i < len(psy_full) or j < len(psy_other):
        for _ in range(fullon_ratio):
            if i < len(psy_full):
                psy.append(psy_full[i]); i += 1
        if j < len(psy_other):
            psy.append(psy_other[j]); j += 1
    psy.extend(psy_full[i:]); psy.extend(psy_other[j:])

    # level 1 - the family vs everything else
    out, k, m = [], 0, 0
    while k < len(psy) or m < len(other):
        for _ in range(psy_ratio):
            if k < len(psy):
                out.append(psy[k]); k += 1
        if m < len(other):
            out.append(other[m]); m += 1
    out.extend(psy[k:]); out.extend(other[m:])
    return out


# ---------------------------------------------------------------- platforms
def make_and_compress_short(beat_file):
    """9:16 60s short, compressed under the 50MB CDP limit."""
    import post_to_youtube as p
    src = os.path.join(BEAT_DIR, beat_file)
    base = os.path.splitext(beat_file)[0]
    raw = os.path.join(SHORT_DIR, base + "_short.mp4")
    if not (os.path.exists(raw) and os.path.getsize(raw) > 100000):
        raw = p.make_short(src, raw)
    if not raw or not os.path.exists(raw):
        return None
    out = os.path.join(SHORT_DIR, base + "_short_compressed.mp4")
    if os.path.exists(out) and os.path.getsize(out) < 50 * 1048576:
        return out
    r = subprocess.run([FFM, "-y", "-loglevel", "error", "-i", raw,
                        "-c:v", "libx264", "-preset", "fast", "-crf", "28",
                        "-c:a", "aac", "-b:a", "128k", "-movflags", "+faststart", out],
                       capture_output=True)
    if os.path.exists(out) and os.path.getsize(out) < 50 * 1048576:
        return out
    return raw


def post_youtube(beat_file, is_short=False):
    import post_to_youtube as p
    src = os.path.join(BEAT_DIR, beat_file)
    title = p.build_title(beat_file)
    # quality gate (same check the CLI uses)
    if not p.quality_gate(src):
        raise RuntimeError("quality gate failed (looped capture)")
    svc = p.get_service()
    if is_short:
        base = os.path.splitext(beat_file)[0]
        out = os.path.join(SHORT_DIR, base + "_short.mp4")
        if not (os.path.exists(out) and os.path.getsize(out) > 100000):
            out = p.make_short(src, out)
        vid = p.upload(svc, out, title, is_short=True)
    else:
        vid = p.upload(svc, src, title)
    mark(beat_file, "youtube-short" if is_short else "youtube-full", f"https://youtu.be/{vid}")
    return vid


def post_tiktok(short_path, beat_file, title, genre):
    from playwright.sync_api import sync_playwright
    import tt_post
    cap = (f"\U0001f300 RESURRECTING BEATS: '{title}' [{genre} / Spiritual EDM] \u26a1\n\n"
           f"Resurrected from the vault! High-energy {genre} energy. Built for festivals, "
           f"vocalists, and live sets.\n\n"
           f"\U0001f3a7 Free Download / License link in bio!\n"
           f"\U0001f4ac Comment '{title.upper()[:14]}' for the untagged link.\n\n"
           f"#ResurrectingBeats #EDM #{genre.replace(' ', '')} #SpiritualEDM #ElectronicMusic "
           f"#Dance #HymnMania #producertok #edmmusic #trancefamily #festivalbeats #unreleasedmusic")
    with sync_playwright() as pw:
        b = pw.chromium.connect_over_cdp(f"http://127.0.0.1:{SOCIAL_PORT}")
        page = b.contexts[0].new_page()
        ok = tt_post.post_video(page, os.path.abspath(short_path), cap)
        b.close()
    return ok


def post_fb_reel(short_path, title, genre, yt):
    r = subprocess.run([sys.executable, os.path.join(ROOT, "fb_reel_post.py"),
                        os.path.abspath(short_path), title, genre, yt or ""],
                       capture_output=True, timeout=420)
    out = (r.stdout or b"").decode("utf-8", errors="replace")
    return ("RESULT: True" in out) or ("published: True" in out) or ("shared with everyone" in out.lower())


def post_instagram(short_path, title, genre, yt):
    import ig_cdp_post as ig
    cap = (f"{title} \u2014 {genre} electronic worship\n\n"
           f"Can this {genre} frequency elevate your spirit? \U0001f447 Drop a like and tell us below!\n\n"
           f"(Full 4K visual journey link in our bio! \U0001f517)\n\n"
           f"#ResurrectingBeats #Hymnmania #SpiritualEDM #{genre.replace(' ', '')} #EDM "
           f"#ElectronicMusic #PsychedelicTrance #WorshipMusic")
    capfile = os.path.join(ROOT, ".ig_auto_cap.txt")
    io.open(capfile, "w", encoding="utf-8").write(cap)
    return ig.post(os.path.abspath(short_path), capfile)


def ensure_browser(port=SOCIAL_PORT, profile=r"C:\Users\jakeg\edge-cdp-profile"):
    """Launch the browser for the social logins if CDP is not already up.

    Also prunes stale tabs: every social run leaves tabs behind, and at 237 tabs the
    browser answers /json/version but `connect_over_cdp` times out after 180 s, which
    silently breaks every TikTok/FB/IG post (hit on 2026-09-16).
    """
    import urllib.request
    try:
        urllib.request.urlopen(f"http://127.0.0.1:{port}/json/version", timeout=4)
        # browser is up - make sure it is not clogged
        try:
            from cleanup_tabs import clean
            clean(port, verbose=False)
        except Exception:
            pass
        return True
    except Exception:
        pass
    print(f"  launching browser on {port}...", flush=True)
    try:
        subprocess.Popen([r"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe",
                          f"--remote-debugging-port={port}", f"--user-data-dir={profile}",
                          "--no-first-run", "--no-default-browser-check",
                          "--disable-features=msEdgeDisableStartupBoost"])
    except Exception as e:
        print(f"  browser launch failed: {str(e)[:60]}")
        return False
    for _ in range(20):
        time.sleep(2)
        try:
            urllib.request.urlopen(f"http://127.0.0.1:{port}/json/version", timeout=3)
            print("  browser ready")
            return True
        except Exception:
            pass
    return False


# ---------------------------------------------------------------- cycle
def nice_title(beat_file):
    import post_to_youtube as p
    t, a, y, cls, g, sp, var = p.detect(beat_file)
    return t or beat_file.replace("_", " ")


def cycle_one(beat_file=None, post_socials=True):
    if beat_file is None:
        q = get_queue()
        if not q:
            print("Nothing to post -> queue empty.")
            return False
        beat_file = q[0]
    if not upload_budget_ok():
        return False
    print(f"  YouTube uploads today: {uploads_today()}/{MAX_UPLOADS_PER_DAY or 'inf'}")
    title = nice_title(beat_file)
    import post_to_youtube as p
    t, a, y, cls, genre, sp, var = p.detect(beat_file)
    genre = genre or "Psytrance"
    print(f"\n=== {title} ({genre}) ===")

    yt_url = ""
    for name, fn in [
        ("youtube-full", lambda: post_youtube(beat_file, False)),
        ("youtube-short", lambda: post_youtube(beat_file, True)),
    ]:
        if already(beat_file, name):
            print(f"  {name}: already done")
            continue
        try:
            vid = fn()
            print(f"  {name}: OK https://youtu.be/{vid}")
            if name == "youtube-full":
                yt_url = f"https://youtu.be/{vid}"
        except Exception as e:
            print(f"  {name}: FAIL {str(e)[:70]}")

    if not post_socials:
        print("  (socials skipped - YouTube only for this track)")
        return True

    short = make_and_compress_short(beat_file)
    print(f"  short: {short}")
    if not short:
        print("  no short clip — skipping socials")
        return True

    if not ensure_browser():
        print("  social browser unavailable — YouTube only this run")
        return True

    if yt_url and not already(beat_file, "fb-feed"):
        try:
            from daily_scheduler import build_post, post_to_facebook
            from playwright.sync_api import sync_playwright
            with sync_playwright() as pw:
                b = pw.chromium.connect_over_cdp(f"http://127.0.0.1:{SOCIAL_PORT}")
                fb = b.contexts[0].new_page()
                fb.goto("https://www.facebook.com/", wait_until="domcontentloaded")
                fb.wait_for_timeout(6000)
                post_text, _ = build_post(os.path.basename(short), title, genre)
                post_to_facebook(fb, post_text, yt_url)
                b.close()
            mark(beat_file, "fb-feed", yt_url)
            print("  fb-feed: OK")
        except Exception as e:
            print(f"  fb-feed: FAIL {str(e)[:60]}")

    for name, fn in [
        ("tiktok", lambda: post_tiktok(short, beat_file, title, genre)),
        ("fb-reel", lambda: post_fb_reel(short, title, genre, yt_url)),
        ("instagram", lambda: post_instagram(short, title, genre, yt_url)),
    ]:
        if already(beat_file, name):
            print(f"  {name}: already done")
            continue
        try:
            ok = fn()
            mark(beat_file, name, "ok" if ok else "")
            print(f"  {name}: {'OK' if ok else 'FAIL'}")
        except Exception as e:
            print(f"  {name}: FAIL {str(e)[:70]}")
    return True


def run_cycle(count=1):
    n = 0
    for _ in range(count):
        if not upload_budget_ok(verbose=(n > 0)):
            break
        try:
            if cycle_one():
                n += 1
            else:
                break
        except Exception as e:
            print(f"cycle error: {str(e)[:80]}")
    print(f"\nCompleted {n} cycle(s). YouTube uploads today: "
          f"{uploads_today()}/{MAX_UPLOADS_PER_DAY or 'inf'}")


if __name__ == "__main__":
    args = sys.argv[1:]
    if "--status" in args:
        used = uploads_today()
        print(f"YouTube uploads today : {used} / {MAX_UPLOADS_PER_DAY or 'unlimited'}")
        print(f"Estimated units used  : {used * YT_UPLOAD_COST:,}  (1,600 per upload)")
        print(f"Default Google quota  : 10,000 units/day = 6 uploads")
        print(f"Observed historical max: 118 uploads in one day (this project has an increase)")
        print(f"Remaining under cap   : {max(0, (MAX_UPLOADS_PER_DAY or 0) - used)}")
        print(f"Queue                 : {len(get_queue(verbose=False))} ready track(s)")
        print(f"Daily target          : {TRACKS_PER_RUN} tracks = {TRACKS_PER_RUN} fulls + {TRACKS_PER_RUN} shorts "
              f"({TRACKS_PER_RUN * 2} YouTube uploads)")
        print(f"Socials (unchanged)   : {SOCIAL_TRACKS_PER_DAY} track/day to FB feed + TikTok + FB Reel + IG")
        print(f"Genre mix             : psy family {PSYTRANCE_RATIO}:1 vs others; inside it, Full-On {FULLON_RATIO}:1")
    elif "--test" in args:
        get_queue(verbose=False)
        q = get_queue()
        for b in q[:15]:
            import post_to_youtube as p
            print("  ", p.build_title(b))
    elif "--catchup" in args:
        # BACKUP RUNNER: only posts if nothing was published today (missed primary run).
        if posted_today():
            print(f"catchup: already posted today ({datetime.date.today()}) - nothing to do")
        else:
            print(f"catchup: no post recorded today - running a full cycle ({TRACKS_PER_RUN} tracks)")
            run_cycle(TRACKS_PER_RUN)
    elif "--daemon" in args:
        print(f"daemon: posting {TRACKS_PER_RUN} tracks/day on weekdays at {RUN_HOUR}:00")
        done_day = None
        while True:
            now = datetime.datetime.now()
            if now.weekday() < 5 and now.hour == RUN_HOUR and done_day != now.date():
                run_cycle(TRACKS_PER_RUN)
                done_day = now.date()
            time.sleep(300)
    else:
        count = TRACKS_PER_RUN
        for a in args:
            if a.isdigit():
                count = int(a)
        print(f"posting {count} track(s) = up to {count * 2} YouTube uploads")
        run_cycle(count)
