import mido
import os
import json
import logging

logger = logging.getLogger(__name__)

class SymbolicNormalizer:
    def __init__(self, midi_path: str):
        self.midi_path = midi_path

    def normalize(self, output_path):
        """Velocity Flattening and Performance Purge"""
        try:
            mid = mido.MidiFile(self.midi_path)
        except Exception as e:
            logger.error(f"Failed to load MIDI {self.midi_path}: {e}")
            return None

        new_mid = mido.MidiFile(ticks_per_beat=mid.ticks_per_beat)

        for i, track in enumerate(mid.tracks):
            new_track = mido.MidiTrack()
            for msg in track:
                if msg.is_meta:
                    # Keep only essential meta messages
                    if msg.type in ['set_tempo', 'time_signature', 'key_signature', 'track_name']:
                        new_track.append(msg.copy())
                elif msg.type in ['note_on', 'note_off']:
                    # Force velocity 100 for note_on with velocity > 0, velocity 0 for others
                    # Standard note_on with velocity 0 is treated as note_off
                    if msg.type == 'note_on' and msg.velocity > 0:
                        new_msg = msg.copy(velocity=100)
                    else:
                        new_msg = msg.copy(velocity=0)
                    new_track.append(new_msg)
                # Ignore pitch_wheel, control_change, etc.

            if len(new_track) > 0:
                new_mid.tracks.append(new_track)

        if len(new_mid.tracks) == 0:
            logger.warning(f"No tracks produced for {self.midi_path}. Adding dummy track.")
            new_mid.tracks.append(mido.MidiTrack())

        new_mid.save(output_path)

        # Companion JSON config
        config = {
            "influence_type": "melody_chords",
            "style_target": "electronic_deep_house",
            "original_file": os.path.basename(self.midi_path)
        }
        config_path = output_path.replace(".mid", "_config.json")
        try:
            with open(config_path, 'w') as f:
                json.dump(config, f, indent=4)
        except Exception as e:
            logger.error(f"Failed to write config {config_path}: {e}")

        return output_path
