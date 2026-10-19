# TODO

### v1.37.0 - The Studio Reversal
- [x] Implement `export_speed_variants` in `SonicVacuumProcessor` (0.5x, 1x, 2x).
- [x] Update `SunoBrowserAutomation` to loop through speed variants and genre tags.
- [x] Create `hymn_remaker/src/psy_mono_bridge.py` for the Ableton reversal pipeline.
- [x] Integrate `demucs` and `basic-pitch` for audio-to-MIDI in the bridge.
- [x] Add Ableton assembly logic via OSC (`pylive`).

### Immediate Fixes
- [x] Implement LALAL.AI REST API integration as a fall-back for local Demucs.
- [x] Optimize Local MusicGen latency by implementing a quantized model (INT8/FP16).
- [x] Add more complex Markov-chain transition rules to the arpeggiator for "peak climax" variations.

### Enhancements
- [x] Multi-voice vocal harmonization for hip-hop acapellas using ElevenLabs.
- [x] Automated video generation matching the 145 BPM grid with audio-reactive visuals.
- [ ] Real-time "Jam Mode" where the sequencer responds to live MIDI controller input.
