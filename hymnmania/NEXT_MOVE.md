# ⏰ NEXT MOVE — Tomorrow's Plan

_Written: 2026-09-13 17:45 EDT · Reminder fires 2026-09-14 09:00_

---

## ✅ DONE: the free-credit window CLOSED 2026-09-14 ~11:00 EDT (sprint completed)

**v6 generation is CREDIT-FREE right now.** Timer was `1d 19h 03m` at 2026-09-12 15:55 EDT
→ **ends ≈ 2026-09-14 11:00 EDT**.

Every cover generated before then costs **0 credits**. After that: ~10 credits/generation.

---

## Where the sprint stands right now

```
promo_sprint.py   — RUNNING (leave it running)
  45 / 113 hymns processed
  27 usable   /  18 copyright-blocked  (40% block rate)
  375 clips banked          (all FREE)
  target: 113 hymns x 11 genres = 1,243 covers
```

**Action tomorrow morning: check whether it finished before the window closed.**

```bash
# is it still running?
powershell "Get-CimInstance Win32_Process -Filter \"name='python.exe'\" | Where-Object { \$_.CommandLine -like '*promo_sprint*' }"

# how far did it get?
python -c "import json;d=json.load(open('.promo_sprint.json'));h=d['hymns'];print('hymns',len(h),'clips',sum(sum(len(c) for c in v.get('covers',{}).values()) for v in h.values()))"

tail -20 _sprint.log
```

---

## Decision tree for tomorrow

### 1. If the sprint did NOT finish (or window is closing)
**Restart it immediately in the closing hours** — it resumes from `.promo_sprint.json`
(it skips hymns/genres already banked). Prioritise breath: all 11 genres before any re-runs.

### 2. After the window closes — the monthly engine starts
```
10,000 credits/month (Premier, renews Oct 6)
  ÷ 10 credits per generation        = 1,000 generations/month
  × 2 clips each                     = 2,000 clips
  × ~60% survive the fingerprint gate = ~600 postable covers/month
```
→ ~20 covers/day of new material vs the ~1/day the scheduler posts.
**Generation will not be the bottleneck** — capture time (~4 min/cover) and YouTube's
~100 uploads/day are.

### 3. Then: capture → compose → post the banked covers
The 375+ banked clips cost nothing to capture (MediaRecorder), compose, or post.
This is ~12–20 weeks of daily content at **zero credit cost**.

```bash
# per cover:
python cap_cycle.py <cover_clip_id> "generated/<Hymn>_<genre>_A_cover.mp3"
python -c "import quick_composer as qc; qc.compose('generated/....mp3','<Hymn>','<Genre>')"
python scheduler_v2.py --now 1        # or let the 3 PM task do it
```

### 4. Deferred for later (NOT while the window is open)
- **Speed variants** (0.5×/1.5×/2×/3×) — 5× more covers but lower value (same hymn, re-timed).
  Measured: Gabba 0.5× = 157s@199bpm vs 1.0× = 180s@117bpm. Real but moderate variety.
  Worth doing *after* the promo when we know the credit budget.
- **Re-runs** (same settings) — stochastic, gives genuinely different songs. Free in-window,
  10 cr each after. Good use of leftover free time, low priority vs breadth.
- **Older Magnific batches** (306 video-generator assets in the project vs 36 downloaded).

---

## Current state snapshot

| Thing | Status |
|---|---|
| Suno promo | ⏳ ~17 h left (ends ~Sep 14 11:00 EDT) |
| `promo_sprint.py` | running, 375 clips, 45/113 hymns |
| Credit balance | 9,950 (untouched by the sprint — it's free) |
| Block rate | **40%** (vs 15% I first estimated) |
| Magnific clips | 156 unique in `pipeline_output/magnific_videos/` (36 new from Sep 12) |
| Disk free | 13.3 GB (was 1.7 GB — freed ~12 GB) |
| Scheduler | Mon–Fri 15:00 + backup 20:00 + logon catch-up |
| YouTube limit | ~100 uploads/day (measured) |
| Queue | low — the banked covers will refill it |

## Blocked hymns so far (40% — don't re-add to the pool)
A_Childs_Prayer · Beautiful · Blessed Be The Lord God Almighty · Cares Chorus ·
Come And Sing Praises · Do, Lord · Down In My Heart · Everything's Alright ·
Father I Adore You · Friends · Give Me Oil In My Lamp · Hallelu Hallelu · …

**Pattern: the well-known choruses get fingerprinted; obscure ones pass.**


---

# ✅ RESULTS — sprint finished 2026-09-14 ~11:00 EDT

| | |
|---|---|
| Round 1 (11 genres, first pass) | **1301 clips** |
| Round 2 (re-runs, different songs) | **186 clips** |
| **TOTAL BANKED** | **1487 clips** |
| Usable hymns | 66 |
| Blocked (fingerprint) | 44 (39%) |
| Credits spent | ~55-80 (promo ran to its edge) |
| Value captured | ~7,430 credits ≈ 74% of a month |

State files:
- `.promo_sprint.json`      — round 1 (uploads + 11 genres each)
- `.promo_sprint_r2.json`   — round 2 (second pass per hymn)
- `.promo_sprint_r1_backup.json` — backup

## NEXT ACTIONS (in order)
1. **Capture** the banked covers — free (MediaRecorder, no credits):
   `python cap_cycle.py <cover_clip_id> "generated/<Hymn>_<genre>_A_cover.mp3"`
2. **Compose** beat videos — picks up the 36 new Magnific clips automatically:
   `python -c "import quick_composer as qc; qc.compose('generated/....mp3','<Hymn>','<Genre>')"`
3. **Post** — scheduler (Mon-Fri 15:00) or `python scheduler_v2.py --now N`
4. **Monthly engine** — 10,000 credits ÷ ~10/generation = ~1,000 generations =
   ~2,000 clips = **~600 postable covers/month** after the 39% gate.

**Never re-run `promo_sprint.py` outside a promo window** — it now costs 10 credits
per generation. Use `--round=N` only when generation is free again.
