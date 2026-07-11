import mido
import os
import json

class SymbolicNormalizer:
    def __init__(self, midi_path: str):
        self.midi_path = midi_path

    def normalize(self, output_path):
        """Velocity Flattening and Performance Purge"""
        mid = mido.MidiFile(self.midi_path)
        new_mid = mido.MidiFile()

        for track in mid.tracks:
            new_track = mido.MidiTrack()
            for msg in track:
                if msg.is_meta:
                    # Keep only essential meta messages
                    if msg.type in ['set_tempo', 'time_signature', 'key_signature', 'track_name']:
                        new_track.append(msg)
                elif msg.type in ['note_on', 'note_off']:
                    # Force velocity 100 for note_on, 0 for note_off
                    if msg.type == 'note_on':
                        new_msg = msg.copy(velocity=100)
                    else:
                        new_msg = msg.copy(velocity=0)
                    new_track.append(new_msg)
                # Ignore pitch_wheel, control_change, etc.

            if len(new_track) > 0:
                new_mid.tracks.append(new_track)

        new_mid.save(output_path)

        # Companion JSON config
        config = {
            "influence_type": "melody_chords",
            "style_target": "electronic_deep_house",
            "original_file": os.path.basename(self.midi_path)
        }
        config_path = output_path.replace(".mid", "_config.json")
        with open(config_path, 'w') as f:
            json.dump(config, f, indent=4)

        return output_path
