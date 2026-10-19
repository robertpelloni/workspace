import os
import sys
import argparse
import mido
import numpy as np
from scipy.io import wavfile

def render_midi_as_sine(midi_path, wav_path, speed=1.0, sample_rate=44100):
    """Render MIDI file note events directly to clean sine wave PCM audio."""
    mid = mido.MidiFile(midi_path)
    events = []
    current_time = 0.0
    for msg in mid:
        current_time += msg.time / speed
        if msg.type == "note_on" and msg.velocity > 0:
            events.append({"type": "note_on", "note": msg.note, "velocity": msg.velocity, "time": current_time})
        elif msg.type == "note_off" or (msg.type == "note_on" and msg.velocity == 0):
            events.append({"type": "note_off", "note": msg.note, "time": current_time})

    notes = []
    active_notes = {}
    for ev in events:
        note = ev["note"]
        if ev["type"] == "note_on":
            if note in active_notes:
                s = active_notes[note]
                notes.append({"note": note, "start": s["time"], "end": ev["time"], "velocity": s["velocity"]})
            active_notes[note] = ev
        elif ev["type"] == "note_off" and note in active_notes:
            s = active_notes.pop(note)
            notes.append({"note": note, "start": s["time"], "end": ev["time"], "velocity": s["velocity"]})

    total_duration = current_time
    for note, s in active_notes.items():
        notes.append({"note": note, "start": s["time"], "end": total_duration, "velocity": s["velocity"]})

    if not notes:
        raise ValueError("No note events detected in MIDI file.")

    max_time = max(n["end"] for n in notes) + 0.5
    audio = np.zeros(int(max_time * sample_rate), dtype=np.float32)

    for n in notes:
        freq = 440.0 * (2.0 ** ((n["note"] - 69) / 12.0))
        s0 = int(n["start"] * sample_rate)
        s1 = int(n["end"]   * sample_rate)
        dur = s1 - s0
        if dur <= 0:
            continue
        t = np.arange(dur) / sample_rate
        amp = (n["velocity"] / 127.0) * 0.15
        env = np.ones(dur, dtype=np.float32)
        fl = min(int(0.01 * sample_rate), dur // 2)
        if fl > 0:
            env[:fl] = np.linspace(0, 1, fl)
            env[-fl:] = np.linspace(1, 0, fl)
        audio[s0:s1] += amp * np.sin(2.0 * np.pi * freq * t) * env

    peak = np.max(np.abs(audio))
    if peak > 0:
        audio = audio / peak * 0.9

    os.makedirs(os.path.dirname(os.path.abspath(wav_path)), exist_ok=True)
    wavfile.write(wav_path, sample_rate, (audio * 32767).astype(np.int16))
    print(f"Rendered WAV sine audio successfully: {wav_path}")

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--midi", required=True, help="Input MIDI path")
    parser.add_argument("--wav", required=True, help="Output WAV path")
    parser.add_argument("--speed", type=float, default=1.0, help="Tempo scale multiplier")
    args = parser.parse_args()
    render_midi_as_sine(args.midi, args.wav, args.speed)

if __name__ == "__main__":
    main()
