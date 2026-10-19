import mido
import os

class HouseStructuralQuantizer:
    def __init__(self, midi_path: str):
        self.midi_path = midi_path

    def quantize(self, output_path, target_bpm=124):
        """Tempo Enforcement, Grid Quantization, 4-on-the-Floor, and Off-Beat Bass"""
        mid = mido.MidiFile(self.midi_path)
        new_mid = mido.MidiFile(ticks_per_beat=mid.ticks_per_beat)

        # Enforce Tempo
        tempo = mido.bpm2tempo(target_bpm)

        # 1. New Kick Track (Channel 10, Note 36)
        kick_track = mido.MidiTrack()
        kick_track.append(mido.MetaMessage('set_tempo', tempo=tempo))
        kick_track.append(mido.MetaMessage('track_name', name='Kick'))

        # Calculate total duration in beats
        max_tick = 0
        for track in mid.tracks:
            curr_tick = 0
            for msg in track:
                curr_tick += msg.time
            max_tick = max(max_tick, curr_tick)

        total_beats = int(max_tick / mid.ticks_per_beat) + 4
        for i in range(total_beats):
            kick_track.append(mido.Message('note_on', note=36, velocity=100, time=0, channel=9))
            kick_track.append(mido.Message('note_off', note=36, velocity=0, time=mid.ticks_per_beat, channel=9))
        new_mid.tracks.append(kick_track)

        # 2. Process Original Tracks (Quantization and Bass Shifting)
        for i, track in enumerate(mid.tracks):
            new_track = mido.MidiTrack()
            new_track.append(mido.MetaMessage('track_name', name=f'Processed {i}'))

            curr_tick = 0
            is_bass = 'bass' in track.name.lower() or i == len(mid.tracks) - 1

            for msg in track:
                if msg.is_meta:
                    if msg.type == 'set_tempo': continue # Override
                    new_track.append(msg)
                elif msg.type in ['note_on', 'note_off']:
                    # Quantize to nearest 16th note (mid.ticks_per_beat / 4)
                    q = mid.ticks_per_beat // 4
                    abs_time = curr_tick + msg.time
                    quantized_abs_time = round(abs_time / q) * q

                    if is_bass and msg.type == 'note_on':
                        # Shift to off-beat (add 8th note = mid.ticks_per_beat / 2)
                        quantized_abs_time += mid.ticks_per_beat // 2

                    # Note: Simplified delta timing logic
                    # In a real implementation, we'd maintain an event list and sort
                    new_msg = msg.copy(time=max(0, quantized_abs_time - curr_tick))
                    new_track.append(new_msg)
                    curr_tick = quantized_abs_time
                else:
                    new_track.append(msg)
            new_mid.tracks.append(new_track)

        new_mid.save(output_path)
        return output_path
