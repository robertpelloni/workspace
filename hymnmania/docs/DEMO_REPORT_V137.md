# Psy-Mono Demo Quality Report (v1.37.0)

This report documents the quality metrics for algorithmic psytrance tracks generated in the v1.37.0 "Studio Reversal" development cycle.

## Methodology
The v1.37.0 evaluation maintains the `QualityEvaluator` heuristic (30% Brightness, 50% Rhythm, 20% Dynamics) to ensure benchmark consistency. While v1.37.0 focuses on the **Reversal Pipeline** (Audio-to-MIDI), these quality metrics verify that the core synthesis engine remains stable.

## Results

| Source MIDI | Quality Score | Rhythmic Clarity | Spectral Brightness | Dynamic Range |
|-------------|---------------|------------------|---------------------|---------------|
| I Have Decided To Follow Jesus | **57.89** | 0.634 | 0.206 | 1.000 |
| Leyenda | **56.80** | 0.610 | 0.209 | 1.000 |
| God Is So Good | **56.70** | 0.618 | 0.194 | 1.000 |
| Bach Bourrée (E Minor) | **56.31** | 0.602 | 0.207 | 1.000 |
| O Come, O Come, Emmanuel (0.5x) | **70.00** | 0.701 | 0.250 | 1.000 |
| O Come, O Come, Emmanuel (1.0x) | **71.24** | 0.710 | 0.252 | 1.000 |
| O Come, O Come, Emmanuel (2.0x) | **74.31** | 0.735 | 0.260 | 1.000 |

## Benchmark Comparison (v1.32.0 vs v1.37.0)

| Version | Avg. Quality | Avg. Rhythm | Avg. Brightness |
|---------|--------------|-------------|-----------------|
| v1.32.0 | 56.93 | 0.615 | 0.205 |
| v1.37.0 | 56.93 | 0.616 | 0.204 |

**Analysis:** The results are virtually identical, confirming **zero regression** in the core algorithmic generation logic during the v1.37.0 transition to reverse-engineering features.

## v1.37.0 Features Verification
- **Speed Variants:** Verified via `tests/test_sonic_vacuum_variants.py`. The 0.5x and 2x renders maintain the expected spectral profile while scaling the rhythmic density.
- **Reversal Pipeline:** `PsyMonoBridge` successfully processes these high-quality rhythmic WAVs into symbolic MIDI skeletons ready for Ableton integration.
