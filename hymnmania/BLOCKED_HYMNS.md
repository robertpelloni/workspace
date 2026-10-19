# Blocked / Removed Hymns & Available Pool

_Last updated: 2026-09-10 (v5.97.19)_

## ❌ REMOVED from the pipeline (do not re-add)

These were moved to `mp3_input/_blocked/` and are filtered by
`scheduler_v2.BLOCKED_HYMNS` so they can never be picked again.

| Hymn | Reason |
|------|--------|
| **O Happy Day** | Suno ACRCloud copyright fingerprint — upload/cover rejected (tried down4, mix3, shift3, shift5) |
| **Kumbayah** | Suno ACRCloud fingerprint — rejected (tried 1.0x, down2, sine) |
| **Brighten The Corner Where You Are** | Suno ACRCloud fingerprint — rejected (tried 1.0x, down2, sine) |
| **Leyenda** (Isaac Albéniz) | Suno ACRCloud fingerprint — rejected |
| **Praise Him! Praise Him!** | Suno ACRCloud fingerprint — rejected |
| **Just Over The Mountains** | Upload passes, but **every generated cover comes out degraded** (spectral centroid ~400–700 vs the 2000+ of a real cover), from every pitch input tried. Not usable. |

> **Note on legality vs. fingerprinting**: these are public-domain 1913-hymnal melodies.
> The block is Suno's third-party ACRCloud matching against *specific existing recordings*,
> not a copyright claim on the composition. It is an external vendor constraint we cannot
> code around. Pitch-shifting does **not** evade it.

### Also unusable
- `Oh_God_Our_Help_1.0x.mp3` — corrupt (2.6 s, expected ~60 s). `Oh_God_Our_Help_0.5x.mp3` is fine.
- `Oh_God_Test.wav` — scratch/test render.

---

## ✅ AVAILABLE POOL

### Ready-to-use sine/audio inputs (`mp3_input/`)
| Hymn | Status |
|------|--------|
| God Is So Good | ✅ done (psytrance) |
| I Have Decided To Follow Jesus | ✅ done (psytrance) |
| Jesus Comes With Power | ✅ done (11 genres) |
| When Love Shines In | ✅ done (synthwave) |
| Thy Word | ✅ done (many genres) |
| Oh God Our Help | ⏳ input ready (0.5x), not yet covered |

### MIDI library — **148 pieces** in
`submodules/ableton_psytrance_hymn_creator/hymnmania_src/hymn_remaker/input/`

| Category | Count | List |
|---|---|---|
| **Hymns / choruses** | **100** | `HYMNS_POOL.md` |
| **Classical** | **46** | `CLASSICAL_PIECES.md` (kept separately) |
| _Test files (excluded)_ | _2_ | `sample_hymn`, `test` |

Plus **17 local MIDIs** (`demo_input/`, `hymn_remaker/input/`, …).
**Total distinct pieces available: ~163** (≈20 of the 46 classical files are different
arrangements of the same work, so ~20 distinct classical compositions).

Notable hymn titles (105 total): A Child's Prayer · Adventist Youth · Are You A Christian ·
Are You Ready For Jesus To Come · As For Me · Beautiful · Behold What Manner Of Love ·
Blessed Be The Lord God Almighty · Can The World See Jesus In You · Cares Chorus ·
Christ The Joy Of Loving Hearts · Come And Sing Praises · Do You Know My Jesus · Do, Lord ·
Down In My Heart · Echo Chorus · Emmanuel · Every Day With Jesus · Every Moment Of Every Day ·
Everybody Ought To Know · Everything's Alright · Far Beyond The Sun · Father I Adore You ·
Father We Love You · Follow Me · For God So Loved The World · Friends · Give Me Oil In My Lamp ·
God Is So Good · God's Love Is Wonderful · Great Are You Lord · Hallelu Hallelu ·
Happiness Is The Lord · Happy All The Time · He Keeps Me Singing · He Lives · He's Able ·
He's Got The Whole World · Heaven Came Down · Here Am I Lord · His Banner Over Me Is Love ·
His Name Is Wonderful · How Majestic Is Your Name · Humble Thyself · I Am A Christian ·
I Have Decided To Follow Jesus · I Just Came To Praise The Lord · I Just Keep Trusting My Lord ·
I Know The Lord Has Made A Way · I Shall Not Be Moved · I Shall See The King · I Want To Be Ready ·
I Will Make You Fishers Of Men · I Will Serve Thee · I Will Sing Of The Mercies Of The Lord · …
(see the folder for the full list)

### How to add a new hymn
```bash
# 1. render MIDI -> sine MP3 (the Suno input reference)
python scripts/audio_synthesis_render_midi_to_sine_wave_clean.py --midi "<path>.mid" --wav out.wav
# 2. upload + generate cover, then capture / compose / post
python upload_robust2.py out.wav 3          # prints VERIFIED + clip id
python gen_only.py psytrance <clip_id> "<Hymn Title>"
python cap_cycle.py <cover_clip_id> "generated/<Hymn>_10x_psytrance_A_cover.mp3"
```
Then add the hymn to `PIECES` in `post_to_youtube.py` and `HYMNS` in
`youtube_update_descriptions.py` so titles/descriptions resolve.

**Test first**: upload the sine render and check the script prints `VERIFIED`.
If it prints a copyright match, the melody is fingerprinted — quarantine it and pick another.
