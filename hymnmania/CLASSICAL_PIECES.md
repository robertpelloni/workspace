# Classical Pieces — separate pool (46 MIDI files)

_Last updated: 2026-09-10 (v5.97.21)_

> ⚠️ **THESE BELONG TO A DIFFERENT CHANNEL — NOT HymnMania / Resurrecting Beats.**
> This file is just an inventory for reference. The HymnMania scheduler **excludes** them:
> `scheduler_v2.EXCLUDE_CLASSICAL = True` skips any beat video whose title contains
> `Classical Remix`. Classical tracks already composed under `pipeline_output/beat_videos/`
> (Toccata, Canon in D, Clair de Lune, etc.) are skipped by the hymn scheduler.

Kept **separate from the hymn pool** (see `HYMNS_POOL.md`).
Source: `submodules/ableton_psytrance_hymn_creator/hymnmania_src/hymn_remaker/input/`

> Many entries are the **same work in different arrangements** (piano / guitar / organ /
> string quartet / voices), so these 46 files represent roughly **20 distinct compositions**.

---

## Johann Sebastian Bach — 29 file(s)

- `Notebook2-16-March`
- `Toccata-and-Fugue-Dm`
- `bach-badinerie-flute-piano`
- `bach-badinerie-piano-solo`
- `bach-bourree-in-e-minor-guitar`
- `bach-bourree-in-e-minor-oboe-and-bassoon`
- `bach-bourree-in-e-minor-piano`
- `bach-cello-suite-no1-prelude`
- `bach-cello-suite-no1-prelude-piano`
- `bach-cello-suite-no1-prelude-viola`
- `bach-fugue-g-minor-organ`
- `bach-fugue-g-minor-organ-piano`
- `bach-fugue-g-minor-organ-string-quartet`
- `bach-fugue-g-minor-organ-voices`
- `bach-prelude-in-cm-guitar`
- `bach-prelude-in-cm-piano`
- `book1-fugue02`
- `book1-fugue10`
- `book1-fugue14`
- `book1-fugue24`
- `book1-fugue24-string-quartet`
- `book1-prelude01`
- `book1-prelude02`
- `book1-prelude03`
- `book1-prelude06`
- `book1-prelude14`
- `book1-prelude24`
- `book2-fugue02`
- `book2-prelude02`

## Johannes Brahms — 4 file(s)

- `brahms-st-anthony-chorale-theme-orchestral`
- `brahms-st-anthony-chorale-theme-piano-solo`
- `brahms-st-anthony-chorale-theme-trio`
- `brahms-st-anthony-chorale-theme-two-pianos`

## Carl Philipp Emanuel Bach — 3 file(s)

- `cpe-bach-la-caroline`
- `cpe-bach-solfeggietto`
- `cpe-bach-sonata6-1-f-minor-allegro-di-molto`

## Edward Elgar — 5 file(s)

- `edward-elgar-enigma-variations-nimrod-for-organ`
- `edward-elgar-enigma-variations-nimrod-for-piano`
- `edward-elgar-salut-d-amour-cello-piano`
- `edward-elgar-salut-d-amour-piano-solo`
- `edward-elgar-salut-d-amour-violin-piano`

## George Frideric Handel — 1 file(s)

- `handel-dead-march-from-saul-organ`

## Antonio Vivaldi — 1 file(s)

- `vivaldi-estro-armonico-no11-2-organ`

## Isaac Albeniz — 2 file(s)

- `isaac-albeniz-espana-tango-op165-no2`
- `leyenda`

## Other — 1 file(s)

- `osterreichische-bundeshymne`

---

### Notes
- **`leyenda`** is also on the BLOCKED list (Suno ACRCloud fingerprint rejects it — an extremely
  widely-recorded guitar piece). Kept for completeness only; do not generate covers from it.
- `Toccata-and-Fugue-Dm` — Bach's Toccata already has beat videos/shorts on the channel from an
  earlier batch; check for duplicates before re-generating.
- Classical pieces post with the `[Genre] Classical Remix - [Piece] ([Composer], [Year])` title
  format (handled automatically by `post_to_youtube.detect()`), not the hymn format.
- **Excluded test files** (not real pieces): `sample_hymn`, `test`.
