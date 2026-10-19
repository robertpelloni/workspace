import mido
import os
import logging

logger = logging.getLogger(__name__)

class HouseStructuralQuantizer:
    def __init__(self, midi_path: str):
        self.midi_path = midi_path

    def quantize(self, output_path, target_bpm=124):
        """Tempo Enforcement, Grid Quantization, 4-on-the-Floor, and Off-Beat Bass"""
        try:
            mid = mido.MidiFile(self.midi_path)
        except Exception as e:
            logger.error(f"Failed to load MIDI {self.midi_path}: {e}")
            return None

        new_mid = mido.MidiFile(ticks_per_beat=mid.ticks_per_beat)

        # Enforce Tempo
        tempo = mido.bpm2tempo(target_bpm)

        # 1. New Kick Track (Channel 10, Note 36)
        kick_track = mido.MidiTrack()
        kick_track.append(mido.MetaMessage('set_tempo', tempo=tempo))
        kick_track.append(mido.MetaMessage('track_name', name='Kick'))

        max_tick = 0
        for track in mid.tracks:
            curr_tick = 0
            for msg in track:
                curr_tick += msg.time
            max_tick = max(max_tick, curr_tick)

        if max_tick <= 0:
            logger.warning(f"MIDI file {self.midi_path} has zero duration. Generating minimal kick.")
            total_beats = 4
        else:
            total_beats = int(max_tick / mid.ticks_per_beat) + 4

        for i in range(total_beats):
            kick_track.append(mido.Message('note_on', note=36, velocity=100, time=0, channel=9))
            kick_track.append(mido.Message('note_off', note=36, velocity=0, time=mid.ticks_per_beat, channel=9))
        new_mid.tracks.append(kick_track)

        # 2. Process Original Tracks (Quantization and Bass Shifting/Staccato)
        for i, track in enumerate(mid.tracks):
            new_track = mido.MidiTrack()
            track_name = getattr(track, 'name', f'Processed {i}')
            new_track.append(mido.MetaMessage('track_name', name=track_name))

            is_bass = 'bass' in track_name.lower() or i == len(mid.tracks) - 1

            # Use absolute timing to avoid delta-math accumulation errors
            events = []
            curr_tick = 0
            for msg in track:
                curr_tick += msg.time
                if msg.type in ['note_on', 'note_off']:
                    events.append({'tick': curr_tick, 'msg': msg})
                elif msg.is_meta and msg.type != 'set_tempo':
                    events.append({'tick': curr_tick, 'msg': msg})

            # Process events
            processed_events = []
            pending_notes = {} # note -> start_tick

            for event in events:
                msg = event['msg']
                tick = event['tick']

                # Quantize
                q = mid.ticks_per_beat // 4
                if q == 0: q = 1
                new_tick = round(tick / q) * q

                if msg.type == 'note_on' and msg.velocity > 0:
                    if is_bass:
                        # Shift to off-beat (add 8th note)
                        new_tick += mid.ticks_per_beat // 2

                    pending_notes[msg.note] = new_tick
                    processed_events.append({'tick': new_tick, 'msg': msg})
                elif msg.type == 'note_off' or (msg.type == 'note_on' and msg.velocity == 0):
                    if msg.note in pending_notes:
                        start_tick = pending_notes.pop(msg.note)
                        if is_bass:
                            # Staccato: force 1/16th note duration
                            new_tick = start_tick + (mid.ticks_per_beat // 4)
                        processed_events.append({'tick': new_tick, 'msg': msg})
                else:
                    processed_events.append({'tick': new_tick, 'msg': msg})

            # Sort by tick
            processed_events.sort(key=lambda x: x['tick'])

            # Convert back to deltas
            last_tick = 0
            for event in processed_events:
                delta = max(0, event['tick'] - last_tick)
                new_track.append(event['msg'].copy(time=delta))
                last_tick = event['tick']

            new_mid.tracks.append(new_track)

        new_mid.save(output_path)
        return output_path
