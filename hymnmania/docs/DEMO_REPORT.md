# Psy-Mono Demo Quality Report (v1.32.0)

This report documents the quality metrics for the first batch of algorithmic psytrance tracks generated from traditional hymn and classical MIDI sources.

## Methodology
Tracks were generated using the `PsyGenerator` (loop mode, 145 BPM) and rendered using the native C++ FluidSynth engine. Quality was assessed using the `QualityEvaluator` heuristic (30% Brightness, 50% Rhythm, 20% Dynamics).

## Results

| Source MIDI | Quality Score | Rhythmic Clarity | Spectral Brightness | Dynamic Range |
|-------------|---------------|------------------|---------------------|---------------|
| I Have Decided To Follow Jesus | **57.89** | 0.63 | 0.21 | 1.00 |
| Leyenda | **56.80** | 0.61 | 0.21 | 1.00 |
| God Is So Good | **56.70** | 0.62 | 0.19 | 1.00 |
| Bach Bourrée (E Minor) | **56.31** | 0.60 | 0.21 | 1.00 |

## Analysis
- **Dynamic Range:** All tracks achieved a perfect 1.0 dynamic range score, indicating excellent contrast between the driving psy-kick/bass and melodic elements.
- **Rhythmic Clarity:** Scores averaged ~0.62, confirming that the 16th-note "psy-roll" is cleanly defined and quantized.
- **Spectral Brightness:** Scores were relatively low (~0.20), suggesting that the default SoundFont lacks the high-frequency "sizzle" and FM squelches characteristic of peak-time psytrance.
- **Overall:** The pipeline is structurally sound. Future improvements should focus on "Texture Mapping" (AI sound design) to elevate the spectral profile.
